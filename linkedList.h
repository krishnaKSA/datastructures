#include <iostream>
using namespace std;

/*single linkedlist class */
template <typename T> class linkedList
{
private:
    /* create node class */
	template <typename T> class Node
	{
		public:
			T data; //data
			Node<T>* next;	//next pointer
			//constructor
			Node() :next(nullptr) 
	        {
			} 
	};
	int m_size; //size of the linked list
	Node<T>* m_head; //head pointer
	Node<T>* m_tail; //tail pointer

	//helper functions
	inline void increaseListSize()
	{
		m_size++;
	}
	inline void decreaseListSize()
	{
		m_size--;
	}

public:
    
	//constructor
	linkedList():m_head(nullptr),m_tail(nullptr),m_size(0) 
	{		
	}
	
	//get size of the linked list
	int getsize()
	{
		return m_size;
	}
    
	//check whether linked list is empty
	bool isEmpty()
	{
		return (0 == m_size)?true:false;
	}
    
	//Add elements to the list
	void add(T elem)
	{
		addlast(elem);
	}
    
	//Add element in the first node(head node)
	void addfirst(T elem)
	{
		Node<T>* new_node = new Node<T>();
		new_node->data = elem;
		if (nullptr == m_head)
		{      
			//If head node is nullptr, assign newnode as head node
			m_head = new_node;
			m_tail = m_head;
		}
		else
		{   
			//If head is not empty, assign the new node next pointer is head node, and
			//new node as head node.
			new_node->next = m_head;
			m_head = new_node;
	
		}
		increaseListSize(); //increase the size of the list
	}
    
	//Add element at end of the list
	void addlast(T elem)
	{
		//if the head pointer is null, create the first element
		if (nullptr == m_head)
		{
			addfirst(elem);
		}
		else 
		{
			//create new node
			Node<T>* new_node = new Node<T>();
			new_node->data = elem;

			Node<T>* curr_node = m_head;
            //Travese till the last node
			while (nullptr != curr_node->next)
			{
				curr_node = curr_node->next;
			}
			//add the new node at the end of the list
			curr_node->next = new_node;
			m_tail = new_node; //assign the new node as tail node
			increaseListSize(); //increase the size of the list
		}
	}
    
	//add the element in the specific location
	void addat(int pos, T elem)
	{
		//validate the position parameter
		if ((0 >= pos) || (pos > m_size))
		{
			cerr << "invalid pos " << pos << endl;
			return;
		}
		//If the pos is 1, then add the element as first 
		if (1 == pos)
		{
			addfirst(elem);
		}
		else if (pos == m_size)
		{      
			//if the position value is size of the list, then add the element at end of the list
			addlast(elem);
		}
		else
		{
			//create new node
			Node<T>* new_node = new Node<T>();
			new_node->data = elem;

			Node<T>* curr_node = m_head;
			int index = 1;
                        //iterate till the position
			while (index != (pos - 1))
			{
				curr_node = curr_node->next;
			}
			//add the element
			new_node->next = curr_node->next;
			curr_node->next = new_node;
			increaseListSize();
		}
	}
    
	//get the first element of the linked list
	T peekfirst()
	{
		//if the list is empty, throw error
		if (isEmpty())
		{
			throw runtime_error("Empty list");
		}
		//return the first element
		return m_head->data;
	}
    
	//get the last element of the linked list
	T peeklast()
	{
		//if the list is empty, throw error
		if (isEmpty())
		{
			throw runtime_error("Empty list");
		}
		//return the last element
		return m_tail->data;
	}
    
	//remove the first node
	void removefirst()
	{
		if (isEmpty())
		{
			throw runtime_error("Empty list");
		}
		else
		{
			//head node point to the head node->next 
			Node<T>* node = m_head;
			m_head = m_head->next;
			delete node; //delete the node
			decreaseListSize(); //reduce the size of the list
			if (isEmpty()) //If the list is empty
			{
				m_head = nullptr;
				m_tail = nullptr;
			}
		}
	}
    
	//remove the last node
	void removelast()
	{
		if (isEmpty())
		{
			throw runtime_error("Empty list");
		}
		else
		{
			Node<T>* node = m_head;
			Node<T>* prev = m_head;
			//travese till last node
			while (node->next != nullptr)
			{
				prev = node;
				node = node->next;
			}
			prev->next = nullptr;
			delete node; //delete the last node
			m_tail = prev; //assign the prev node as tail node
			decreaseListSize(); //reduce the size
			if (isEmpty()) //if the list is empty
			{
				m_head = nullptr;
				m_tail = nullptr;
			}

		}
	}
    
	//remove at the given position
	void removeat(int pos)
	{
		if (isEmpty())
		{
			throw runtime_error("Empty list");
	        }//validate the input parameter
		else if ((0 >= pos) || (pos > m_size))
		{
			throw runtime_error("invalid position");
		}
		else
		{
			if (1 == pos) //if position is 1, remove first element
			{
				removefirst();
			}
			else if (m_size == pos) //If the position is size of the list, remove the last element
			{
				removelast();
			}
			else
			{
				Node<T>* curr = m_head;
				int index = 1;
				while (index != (pos - 1))
				{
					curr = curr->next;
				}
				//iterate to reach the position
				if (curr->next)
				{
					curr->next = curr->next->next;
				}
				else
				{
					curr->next = nullptr;
				}
				decreaseListSize(); //reduce the list size

				if (isEmpty()) //if the size is 0, delete the head and tail pointer
				{
					m_head = nullptr;
					m_tail = nullptr;
				}
			}
		}
	}
    
	//Utility function to print the list
	void printlist()
	{
		Node<T>* list = m_head;
		cout << "single list :: ";
		while (nullptr != list)
		{
			cout << list->data << "->";
			list = list->next;
		}
		cout << endl;
	}

};

template <typename T> class linkedListest
{	
public:
	void testexecution()
	{
		linkedList<T>* list = new linkedList<T>();

		list->add(20);
		list->addfirst(10);
		list->addlast(30);
		list->addat(3, 40);
		
		list->printlist();
		cout << "peek first  " << list->peekfirst() << endl;
		cout << "peek last  " << list->peeklast() << endl;
		list->removefirst();
		list->printlist();
		list->removelast();
		list->printlist();
		list->removeat(2);
		list->printlist();

		list->addlast(30);
		list->printlist();
		list->addat(3, 40);
		list->printlist();
		list->addfirst(10);
		list->printlist();
		cout << "peek first  " << list->peekfirst() << endl;
		cout << "peek last  " << list->peeklast() << endl;

	}

};


