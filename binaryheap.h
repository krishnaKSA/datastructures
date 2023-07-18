#include <iostream>
#include <vector>
using namespace std;

/* class binary heap (priority queue) */
/* This class implemented for MAX_HEAP */
template <typename T> class binaryheap
{
private:
	int heaptype; //Max heap or min heap. This class implemented for MAX_HEAP 
	vector<T> heap; //heap datastructure 

 
    public:
	//constructor
	binaryheap(int type) :heaptype(type) {}

	//parameterised constructor
	binaryheap(T *arr, int _size)
	{
		if (_size != 0)
		{
			for (int i=0; i<_size;i++)
			{
				//push all the elements to the vector
				heap.push_back(arr[i]);
			}
		}

		//heapify
		for (int i = (_size / 2) - 1; i >= 0; i--)
		{
			sink(i);
		}
	}

	//add the element
	void add(T elem)
	{
		int m_size = (int)heap.size();

		//add element at the back
		heap.push_back(elem);

		if (m_size != 0)
		{
			//heapify, when adding the element call swim function to heapify the array
			swim(m_size);
		}
	}

	//swim when adding the elements
	void swim(int index)
	{
		//Note: Swim process check the data value with its parent node's data. If the node data is greater than its parent node, then swap the data with the
		// parent node , and continue the swim process with parent node to satisfy the heap property.
		int parent_index = (index - 1) / 2;

		//iterate the process untill the 0th index or parentNode's value is greater than child node
		while ((parent_index >= 0) && (heap[parent_index] < heap[index]))
		{
			//swap the values
			T temp = heap[index];
			heap[index] = heap[parent_index];
			heap[parent_index] = temp;

			//start the swim process again
			index = parent_index;
			parent_index = (index - 1) / 2;
		}
	}

	//remove the element
	void remove(T elem)
	{
		//get the index of the element
		int index  = findelement(elem);

		if (index != -1)
		{
			//swap the delete node value with the last node value
			int indexoflastelement = heap.size() - 1;
			T temp = heap[index];
			heap[index] = heap[indexoflastelement];
			heap[indexoflastelement] = temp;

			//erase the last node
			heap.erase(heap.end()-1);

			//do sink to heapify 
			sink(index);

			//If no change happened in the sink process, the node data stays at the same index
			//then, do swim to heapify
			if (elem == heap[index])
			{
				swim(index);
			}
		}
		else
		{
			cerr << "element not found in the heap" << endl;
		}

	}

	//get the element index
	int findelement(T elem)
	{
		int index = 0;
		for (index = 0; index < heap.size(); index++)
		{
			if (heap[index] == elem)
			{
				return index;
			}
		}
		return -1;
	}

	//heapify when data removed
	void sink(int index)
	{
		//Note: sink process starts with the parent index, and check whether the data in the parent node is greater than its child node.
		//if data is lesser, then it will swap data with the child node, and continue the sink process from the child node index in which swap 
		//happened. this process continues till the last parent node index to maintain the heap property
		if ((index >= 0) && (index <heap.size()))
		{
			int leftchild = (2 * index) + 1; //left child node = 2*i+1
			int rightchild = (2 * index) + 2; //right child node = 2*i+2

			int swap_index = INT_MIN;

			//if the right child node data is greater than the node data, then swap the right with node data value
			if ((rightchild < heap.size()) && (heap[rightchild] > heap[leftchild]) )
			{					 
					if (heap[rightchild] > heap[index])
					{
						swap_index = rightchild;						
					}
		
			}//if the left child node data is greater than the node data, then swap the left with node data value
			else if (leftchild < heap.size()) 
			{
				    if (heap[leftchild] > heap[index])
					{
						swap_index = leftchild;
					}								
			}

			//swap the data
			if (swap_index != INT_MIN)
			{
				T temp = heap[index];
				heap[index] = heap[swap_index];
				heap[swap_index] = temp;
				//continue the sink process
				sink(swap_index);
			}

		}
	}

	void printheap()
	{
		cout << "print heap " << endl;
		for (int i = 0; i < heap.size(); i++)
		{
			cout << heap[i] << " , ";
		}
		cout << endl;
	}


	bool isHeap()
	{
		int n = heap.size();
		vector<int> arr = heap;
		// Start from root and go till the last internal
		// node
		for (int i = 0; i <= (n - 2) / 2; i++)
		{
			// If left child is greater, return false
			if (arr[2 * i + 1] > arr[i])
				return false;

			// If right child is greater, return false
			if (((2 * i + 2) < n) && (arr[2 * i + 2] > arr[i]))
				return false;
		}
		return true;
	}

};

template <typename T> class testbinaryheap
{
public:
	void testexecution()
	{
		binaryheap<int>* heap = new binaryheap<int>(1);

		heap->add(1);
		heap->add(10);
		heap->add(20);
		heap->add(32);
		heap->add(4);
		heap->add(50);
		heap->add(6);
		heap->add(7);
		heap->printheap();
		heap->remove(50);
		heap->isHeap();
		heap->printheap();
		heap->remove(32);
		heap->isHeap();
		heap->printheap();
		heap->remove(20);
		heap->isHeap();
		heap->printheap();
		heap->remove(10);
		heap->isHeap();
		heap->printheap();
		cout << " " << heap->isHeap() << endl;

		int arr[] = { 10,56,2,45,97,67,45,89,0,1 };
		binaryheap<int>* heap_1 = new binaryheap<int>(arr, 10);
		heap_1->printheap();
		cout << " " << heap->isHeap() << endl;
	}
};