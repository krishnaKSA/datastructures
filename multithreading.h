#ifndef MULTITHREADING_H
#define MULTITHREADING_H

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "sourcecode/circularbuffer.h"


using namespace std;
using namespace NCircularBuffer;

//namespace
namespace multithreading
{
	//class semaphore
	class semaphore
	{
	private:
		mutable std::mutex data_mutex; //mutex. mutuable since used in the getSize() const function
		std::condition_variable data_condVariable; //event handling across threads
		uint8_t data_available; //data availability

	public:

		//constructor
		explicit semaphore(uint8_t available)
		{
			data_available = available;
		}

		void wait()
		{
			//Get the unique lock, so that other threads can't get the lock 
			std::unique_lock<std::mutex> lock(data_mutex);

			//if no data/space available to consume or store , wait for it until its available
			while (data_available == 0)
			{
				//this conditional_variable is used to signaling between the threads 
				data_condVariable.wait(lock); //this internally release the lock, and wait for the notification.
			}

			//once, notified get the lock again , and reduce the data_available.	
			--data_available;

			//unique lock is released here
		}

		void notifyall()
		{
			//since we are going to notify, lockguard is sufficient
			std::lock_guard<std::mutex> lock(data_mutex); //similar to data_mutex.lock() but no unlock requires here

			//if data available, notify to all
			//increment the data_available
			if (data_available++ == 0)
			{
				//this conditional_variable is used to signaling between the threads 
				data_condVariable.notify_all();
			}

			//lock is released here
		}

		void notifyone()
		{
			//since we are going to notify, lockguard is sufficient
			std::lock_guard<std::mutex> lock(data_mutex); //similar to data_mutex.lock() but no unlock requires here

			//if data available, notify to all
			if (data_available++ == 0)
			{
				//this conditional_variable is used to signaling between the threads 
				data_condVariable.notify_one();
			}

			//lock is released here
		}

		uint8_t getsize() const
		{
			std::lock_guard<std::mutex> lock(data_mutex);
			return data_available;
		}

	};	


	std::mutex l_mutex;
	semaphore available(10); //number of free positions
	semaphore filled(0);     //number of filled positions	
	CCircularBuffer<int>* cBuffer = CCircularBuffer<int>::getCircularBuffer();
	
	//producer class
	class CProducer
	{
	private:
		uint8_t produced_data;
		uint8_t num_of_trails; //number of items to produce
	public:
		//constructor
		CProducer(uint8_t trails) :num_of_trails(trails), produced_data(10)
		{
		}

		//thread function
		void operator()()
		{
			for (uint8_t index = 0; index < num_of_trails; index++)
			{
				//produce data
				++produced_data;

				//check the available slot to fill the data from producer side
				available.wait();
				{
					std::lock_guard<std::mutex> lock(l_mutex);
					//push to the circular buffer
					cBuffer->push(produced_data);
				}

				//call notifyall to the filled object.
				filled.notifyall();
			}
		}
	};

	//consumer class
	class CConsumer
	{
	private:
		uint8_t num_of_trails;
		uint8_t consumerId;
	public:
		//constructor
		CConsumer(uint8_t trails, uint8_t id) :num_of_trails(trails), consumerId(id)
		{
		}

		//thread function
		void operator()()
		{
			for (uint8_t index = 0; index < num_of_trails; index++)
			{
				//check any data available to consume
				filled.wait();
				{
					std::lock_guard<std::mutex> lock(l_mutex);
					printf("consumerId: %d", consumerId);
					cout <<" consumed data : " << cBuffer->pop() << endl;
				}
				//call notifyall to the available object.
				available.notifyall();
			}
		}
	};

	void testProducerConsumer()
	{
		//create instance for producer and consumer
		CProducer producer(12);
		CConsumer consumer1(3, 0);
		CConsumer consumer2(5, 1);
		CConsumer consumer3(2, 2);

		//create threads
		//start consumer first then producer
		thread cons1{ consumer1 };
		thread cons2{ consumer2 };
		thread cons3{ consumer3 };
		thread prod{ producer };

		//join the threads
		prod.join();
		cons1.join();
		cons2.join();
		cons3.join();
	}
}

#endif