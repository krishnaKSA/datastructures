#ifndef _STACK_SINGLE_LINKEDLIST_H
#define _STACK_SINGLE_LINKEDLIST_H

#include "linkedList.h"

/* Stack class using linked list */
template <typename T> class liststack
{
	linkedList<T>* stack; //linkedlist

public:

	//constructor
	liststack()
	{
		stack = new linkedList<T>();
	}

	//push the data to the stack
	void push(T elem)
	{
		//add the data as last element in the stack.
		stack->addlast(elem);
	}
	
	//Get the top element in the stack.
	T top()
	{
		if (stack->isEmpty())
		{
			cout << "empty list" << endl;
			//return -1;
		}
		//get the last element of the linked list
		return stack->peeklast();
	}
	//pop the last element in the stack
	void pop()
	{
		if (stack->isEmpty())
		{
			cout << "empty list" << endl;
			return;
		}
		//remove the last element from the linked list
		stack->removelast();
	}
	//get the number of elements in the stack
	int getsize()
	{
		//return the size of the linked list
		return stack->getsize();
	}
	//Check stack is empty or not
	bool isEmpty()
	{
		//return true, if linkedlist is empty
		return stack->isEmpty();
	}

};

template <typename T>class stacklisttest
{
public:
	void testexecution()
	{
		liststack<T>* stack_a = new liststack<T>();

		cout << "size of stack = " << stack_a->getsize() << endl;
		cout << "is stack empty = " << stack_a->isEmpty() << endl;
		cout << " pop element when list is empty" << endl;
		stack_a->pop();
		cout << " top element when list is empty =  " << stack_a->top() << endl;
		stack_a->push(10);
		stack_a->push(20);
		stack_a->push(30);
		stack_a->push(40);
		stack_a->push(50);
		stack_a->push(60);
		cout << " top element " << stack_a->top() << endl;
		cout << " pop element " << endl;
		stack_a->pop();
		cout << " top element " << stack_a->top() << endl;
		cout << " pop element " << endl;
		stack_a->pop();
		cout << " top element " << stack_a->top() << endl;
		cout << " pop element " << endl;
		stack_a->pop();
		cout << " top element " << stack_a->top() << endl;
		cout << " pop element " << endl;
		stack_a->pop();
		cout << " top element " << stack_a->top() << endl;
		cout << " pop element " << endl;
		stack_a->pop();
		cout << " top element " << stack_a->top() << endl;
		cout << " pop element " << endl;
		stack_a->pop();
		cout << " top element when list is empty " << stack_a->top() << endl;
		cout << " pop element when list is empty" << endl;
		stack_a->pop();
	}
};


#endif