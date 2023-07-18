#ifndef _STACK_USING_ARRAY_H
#define _STACK_USING_ARRAY_H

#include <iostream>
using namespace std;

#define MAX_ARRAY_SIZE 10

/* stack class usign array */
template <typename T> class stackarr
{
private:
	T arr[10]; //static array
	int size;
	int index;

	//helper functions
	inline void increaseSize()
	{
		++size;
	}
	inline void decreaseSize()
	{
		--size;
	}

public:
	//constructor
	stackarr() :size(0),index(-1) 
	{
	}

	//push element to the stack
	void push(T elem)
	{
		//when max size reached
		if (MAX_ARRAY_SIZE == size)
		{
			cerr << "stack reached max size" << endl;
		}
		else
		{
			arr[++index] = elem;
			increaseSize();
		}
	}

	//Get the  top element of the stack
	T top()
	{
		if (!isEmpty())
		{
			//return the data from the array
			return arr[index];
		}
		else
		{
			//if stack is empty
			cerr << "Top(): empty stack" << endl;
		}
		return INT_MIN;
	}

	//remove the top element from the stack
	T pop()
	{
		T data;
		//if the data is not empty
		if (!isEmpty())
		{
			data = arr[index];
			--index; //decrease the index
			decreaseSize();
			return data; 
		}
		else
		{
			cerr << "pop(): empty stack" << endl;
		}
		return INT_MIN;
	}

	//get the size of the stack
	int getsize()
	{
		return size;
	}
	//return true if stack is empty
	bool isEmpty()
	{
		return (size == 0) ? true : false;
	}
};

/* unit testing */
template <typename T>class stackarrtest
{
public:
	void testexecution()
	{
		stackarr<T>* stack_a = new stackarr<T>();
		
		cout << "size of stack = " << stack_a->getsize() << endl;
		cout << "is stack empty = " << stack_a->isEmpty() << endl;
		cout << " pop element " << stack_a->pop() << endl;
		cout << " top element " << stack_a->top() << endl;
		stack_a->push(10);
		stack_a->push(20);
		 stack_a->push(30);
		stack_a->push(40);
		stack_a->push(50);
		 stack_a->push(60);
		cout << " pop element " << stack_a->top() << endl;
		cout << " top element " << stack_a->pop() << endl;
		cout << " pop element " << stack_a->top() << endl;
		cout << " top element " << stack_a->pop() << endl;
		cout << " pop element " << stack_a->top() << endl;
		cout << " top element " << stack_a->pop() << endl;
		cout << " pop element " << stack_a->top() << endl;
		cout << " top element " << stack_a->pop() << endl;
		cout << " pop element " << stack_a->top() << endl;
		cout << " top element " << stack_a->pop() << endl;
		cout << " pop element " << stack_a->top() << endl;
		cout << " top element " << stack_a->pop() << endl;
		cout << " pop element " << stack_a->top() << endl;
		cout << " top element " << stack_a->pop() << endl;
	}
};

#endif