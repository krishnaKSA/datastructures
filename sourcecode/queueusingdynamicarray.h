#include <iostream>
using namespace std;

#define MAX_CAPACITY 10

/* queue class using dynamic array*/
template <typename T> class queueArray
{
private:
	T* queue; //queue data pointer
	int size; //size of the queue
	int capacity; //capacity of the queue
	int front; //front element of the queue
	int rear; //last element of the queue

public:
	//constructor
	queueArray() :queue(nullptr), size(0), capacity(MAX_CAPACITY), front(-1), rear(-1)
	{	
		//create the dynamic array based on the MAX_CAPACITY 
		queue = new T[capacity];
	}

	queueArray(int cap) :queue(nullptr), size(0), capacity(cap), front(-1), rear(-1)
	{
		//create the dynamic array based on the capacity 
		queue = new T[capacity];
	}

	//return true, if size of the queue is zero
	bool isEmpty()
	{
		return (size == 0) ? true : false;
	}

	//add the element to queue
	void enqueue(T elem)
	{
		//adding first element
		if (isEmpty())
		{
			front = 0; //front updated to 0
			queue[++rear] = elem; //update rear value
			size++; //increase the size
		}
		else
		{
			//if size reached to max capacity
			if (size == capacity)
			{
				cerr << "queue is full" << endl;
				return;

			}
			rear = ((rear+1) % capacity);
			queue[rear] = elem;
			size++;
		}
	}

	//get the first element
	T peekfirst()
	{
		if (isEmpty())
		{
			cerr << "queue is empty " << endl;
			return -1;
		}
		else
		{
			return queue[front];
		}
	}

	//remove the element from the queue
	T dequeue()
	{
		if (isEmpty())
		{
			cerr << "queue is empty " << endl;
			return -1;
		}
		else
		{
			T data = queue[front];
			//if front and rear points to the same index, then empty the queue
			if (front == rear)
			{
				front = rear = -1;
				size=0;				
			}
			else
			{				
				size--;
				front++;
			}
			return data;
		}
		return -1;
	}

	//utility function to print the elements of the queue
	void printlist()
	{
		cout << " queue ";
		for (int i = 0; i < size; i++)
		{
			cout << queue[i] << "->";
		}
		cout << endl;
	}

};

/* unit testing */
template <typename T> class queuearraytest
{
public:
	void testexecution()
	{
		queueArray<T>* queue = new queueArray<T>();

		cout<<"queue is empty = "<<queue->isEmpty()<<endl;
		queue->enqueue(10);
		cout << "dequeu element = " << queue->dequeue() << endl;
		cout << "dequeu element = " << queue->dequeue() << endl;
		queue->enqueue(20);
		queue->printlist();

		cout<<"dequeu element = "<<queue->dequeue()<<endl;
		cout << " first element " << queue->peekfirst() << endl;;
		queue->enqueue(30);
		queue->enqueue(40);
		queue->enqueue(50);
		queue->enqueue(60);
		queue->enqueue(70);
		cout << "dequeu element = " << queue->dequeue() << endl;
		cout << "dequeu element = " << queue->dequeue() << endl;
		cout << "dequeu element = " << queue->dequeue() << endl;
		cout << "dequeu element = " << queue->dequeue() << endl;
		cout << "dequeu element = " << queue->dequeue() << endl;
		cout << "dequeu element = " << queue->dequeue() << endl;
		cout << "dequeu element = " << queue->dequeue() << endl;

		queue->enqueue(1);
		queue->enqueue(2);
		queue->enqueue(3);
		queue->enqueue(4);
		queue->enqueue(5);
		queue->enqueue(6);
		queue->enqueue(7);
		queue->enqueue(8);
		queue->enqueue(9);
		queue->enqueue(10);

		cout << "dequeu element = " << queue->dequeue() << endl;
		cout << "dequeu element = " << queue->dequeue() << endl;
		cout << "dequeu element = " << queue->dequeue() << endl;
		cout << "dequeu element = " << queue->dequeue() << endl;
		cout << "dequeu element = " << queue->dequeue() << endl;

		queue->enqueue(11);
		queue->enqueue(12);
		queue->enqueue(13);
		queue->enqueue(14);
		queue->enqueue(15);
		queue->printlist();
		queue->enqueue(11);
		queue->printlist();
		queue->enqueue(12);
		queue->printlist();
		queue->enqueue(13);
		queue->enqueue(14);
		queue->enqueue(15);

		queue->printlist();
		cout << "dequeu element = " << queue->dequeue() << endl;
		cout << "dequeu element = " << queue->dequeue() << endl;
		cout << "dequeu element = " << queue->dequeue() << endl;
		cout << "dequeu element = " << queue->dequeue() << endl;
		cout << "dequeu element = " << queue->dequeue() << endl;
		queue->printlist();
	}
};