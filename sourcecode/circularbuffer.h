#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include <iostream>
#include "stdio.h"
#include "stdlib.h"
#include <memory>

using namespace std;

/* circular buffer uses the fixed array. When the number of the elements reaches the maximum size of the array,
old data will be replaced by the new data. Always data will be added in the back index. Always data will get read from the 
front index.*/

/* namespace of the circular buffer*/
namespace NCircularBuffer
{
    const uint8_t MAXSIZEOFARRAY = 10; //configurable value 

    //Circular buffer
    template<typename T>
    class CCircularBuffer
    {
        //static pointer
        static CCircularBuffer* circularBuffer; //singleton instance of the class. This makes all the clients points to the same object.

        //inline declration available from C++17
        //static CCircularBuffer* circularBuffer = nullptr;

        //data pointer
        shared_ptr<T[]> bufferData; //declared as shared ptr , so that when all the clients deferences, pointer will be deleted desturctor of the shared ptr. 
        uint8_t maxSize; //maximum size of the buffer
        uint8_t front; //write index
        uint8_t back; //read index
        uint8_t bufferSize; //size of the buffer

        public:

        //function to get the object of the circular buffer        
        static CCircularBuffer* getCircularBuffer()
        {
            if(0 == circularBuffer)
            {
                circularBuffer = new CCircularBuffer<T>();
            }
            return circularBuffer;
        }

        //constructor
        CCircularBuffer():front(0),back(0),bufferSize(0)
        {
            //init values            
            maxSize = MAXSIZEOFARRAY;
            if(MAXSIZEOFARRAY > 0)
            {              
                //create the memory
                bufferData =  shared_ptr<T[]> (new T[maxSize]);
            }
            else
            {
                std::cerr<<"constructor failed "<<endl;
            }
        }

        //Push the element
        void push(T data)
        {
            //data push always happens at back index
            bufferData[back] = data;            
            //if the bufferSize reaches the max, it stays there.
            if(bufferSize < maxSize)
            {
                bufferSize++;
            }
            //when max size reached, reset the back index to beginning.
            if(isFull())
            {
                back = (back+1) % maxSize;

                //change the front index value when the buffer reaches MAX size.
                //It reset the front index to read from the most old data.
                front = back;
            }
            else
            {
                //increment the back index
                back = (back+1) % maxSize;
            }
        }

        //Get the old/first data
        T pop()
        {
            //No data available then return -1.
            if(isEmpty())
            return -1;

            //get the most old data using front index.
            T data = bufferData[front];

            //increment the front index
            front  = (front+1) % maxSize;

            //decrease the bufferSize only if the size greater than zero
            if(bufferSize > 0)
            {
                bufferSize--;
            }

            return data;
        }

        //Get the number of elements in the buffer
        uint8_t getSize()
        {
            printf("size of the buffer = %d \n", bufferSize);
            return bufferSize;
        }

        //check any data is in buffer
        bool isEmpty()
        {
            return (bufferSize == 0) ? (true) : (false);
        }

        //check the full status of the buffer
        bool isFull()
        {
            return (bufferSize == maxSize) ? (true) : (false);
        }

        //utility function to print the elements in the buffer
        void printBuffer()
        {
            uint8_t size = getSize();
            if (size > 0)
            {
                uint8_t index = front;
                uint8_t count = 0;
                cout << "buffer ";
                while (count < bufferSize)
                {
                    cout << " " << bufferData[index];
                    index = (index+1) % maxSize;
                    count++;
                }
                cout << endl;
            }
            else
            {
                cout << "empty buffer " << endl;
            }
        }

    };

    //static variable declaration
    template<typename T> CCircularBuffer<T>* CCircularBuffer<T>::circularBuffer = 0;

    //Unit testing
    void unitTesting_CircuarBuffer()
    {
        CCircularBuffer<int>* cBuffer = CCircularBuffer<int>::getCircularBuffer();
        cout<<"Buffer empty status "<<cBuffer->isEmpty() << endl;

        cBuffer->push(10);
        cBuffer->push(20);
        cBuffer->push(30);
        cBuffer->push(40);
        cBuffer->push(50);
        cBuffer->push(60);
        cBuffer->push(70);
        cBuffer->push(80);

        cBuffer->getSize();

        cBuffer->push(90);
        cBuffer->push(100);
        cout<<"Buffer Full status "<<cBuffer->isFull() << endl;
        cBuffer->printBuffer();
        cBuffer->push(110);
        cBuffer->push(120);
        cout<<"Buffer Full status "<<cBuffer->isFull() << endl;
        cBuffer->getSize();
        cBuffer->printBuffer();

        cBuffer->pop();
        cBuffer->pop();
        cBuffer->pop();
        cBuffer->getSize();
        cBuffer->printBuffer();


        cBuffer->pop();
        cBuffer->pop();
        cBuffer->pop();
        cBuffer->getSize();
        cBuffer->printBuffer();

        cBuffer->push(10);
        cBuffer->push(20);
        cBuffer->push(30);
        cBuffer->push(40);
        cBuffer->push(50);
        cBuffer->push(60);
        cout<<"Buffer Full status "<<cBuffer->isFull();
        cBuffer->getSize();
        cBuffer->printBuffer();
    }
};
#endif
