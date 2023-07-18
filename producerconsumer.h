#ifndef PRODUCERCONSUMER_H
#define PRODUCERCONSUMER_H
//include declarations
#include <iostream>
#include <semaphore>
#include <mutex>
#include <thread>
#include <queue>

//Note:Counting semaphore available in C++20

//namespace declarations
using namespace std;

#define Cplusplus20 0

#if Cplusplus20
//namespace
namespace boundedbuffer
{
    //MAX slots
    const uint8_t MAX_SLOTS = 10;

    //couting semaphore declarations
    std::counting_semaphore<MAX_SLOTS>
        availableSlots{MAX_SLOTS},
        filledSlots{ 0 };

    //mutex
    std::mutex resourceMutex;

    //Shared memory resource
    queue<int> cBuffer;

    //global data
    uint8_t gdata = 0;

    //producer thread function
    void producerThreadFn()
    {
        //this for loop is only for testing purpose to limit the number of cycles
        for (uint8_t idx = 0; idx < MAX_SLOTS; idx++)
        { 
            //1. produce the data
            gdata++;

            //2.Check for the free slot
            availableSlots.acquire();
            {
                std::lock_guard<std::mutex> lock(resourceMutex);
                cBuffer.push(gdata);
            }
            filledSlots.release();
        }

    }
    //consumer thread function
    void consumerThreadFn()
    {
        //this for loop is only for testing purpose to limit the number of cycles
        for (uint8_t idx = 0; idx < 2; idx++)
        {
            //1.check for the empty buffer
            filledSlots.acquire();
            {
                std::lock_guard<std::mutex> lock(resourceMutex);
                //2. If buffer is not empty, consume the data
                cout << "Consumed data = " << cBuffer.front() << endl;
                cBuffer.pop();

                //3. Inform the producer about the free slot
                availableSlots.release();
            }
        }
    }

    //test function
    void test()
    {
        //create threads
        thread producer(&producerThreadFn);
        thread consumer1(&consumerThreadFn);
        thread consumer2(&consumerThreadFn);
        thread consumer3(&consumerThreadFn);
        thread consumer4(&consumerThreadFn);

        //join threads, consumers first
        consumer1.join();
        consumer2.join();
        consumer3.join();
        consumer4.join();
        producer.join();
    }

}
#endif
#endif
