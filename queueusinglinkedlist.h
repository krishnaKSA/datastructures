#ifndef _QUEUE_USING_LINKEDLIST_H
#define _QUEUE_USING_LINKEDLIST_H

#include <iostream>

using namespace std;

/* Quque using linked list */

template <typename T> class queuelist
{
	linkedList<T>* queue; //linkedlist
	int size; //size of the quque

public:
	//constructor
	queuelist():size(0)
	{
		queue = new linkedList<T>(); //create linkedlist with the desired data type
	}

	//add the element 
	void enqueue(T elem)
	{
		//add the element at end of the list
		queue->addlast(elem);
	}

	//remove the element from the queue
	T dequeue()
	{
		//if queue is empty, return the null
		if (isEmpty())
		{
			cout << "empty list" << endl;
			return 0;
		}
		else
		{
			//get the first element from the queue
			T data = queue->peekfirst();
			//remove the first element from the queue
			queue->removefirst();
			return data;
		}

	}

	//get the first elemene inserted from the queue
	T peekfirst()
	{
		if (isEmpty())
		{
			cout << "empty list" << endl;
			return -1;
		}
		else
		{
			//get the first element from the linked list
			return queue->peekfirst();			
		}

	}

	//return true , if the linked list is empty
	bool isEmpty()
	{
		return (queue->isEmpty() ? true : false);
	}

	//Utility function 
	void printlist()
	{
		if (isEmpty())
		{
			cout << "empty list " << endl;
		}
		else
		{
			queue->printlist();
		}
	}
};

/*unit testing */
template <typename T> class queuelinkedlisttest
{
public:
	void testexecution()
	{
		queuelist<T>* queue = new queuelist<T>();

		cout << "queue is empty = " << queue->isEmpty() << endl;
		queue->enqueue(10);
		cout << "dequeu element = " << queue->dequeue() << endl;
		cout << "dequeu element = " << queue->dequeue() << endl;
		queue->enqueue(20);
		queue->printlist();

		cout << "dequeu element = " << queue->dequeue() << endl;
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
		queue->enqueue(11);
		queue->enqueue(12);
		queue->enqueue(13);
		queue->enqueue(14);
		queue->enqueue(15);

		queue->printlist();
	}
};

#endif