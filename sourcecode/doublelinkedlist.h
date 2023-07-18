#include <iostream>

using namespace std;

/* Double linked list class */
template <typename T> class doublelinkedlist
{
private:
	int m_size;	 //size of the list

	//data structure Node class
	template <typename U> class Node
	{
	public:
		T data;
		Node<T>* prev_node;
		Node<T>* next_node;
		//constructor of the node
		Node() :prev_node(nullptr), next_node(nullptr) {}
	};
	//head pointer
	Node<T>* m_head;

public:
	//constructor
	doublelinkedlist():m_size(0),m_head(nullptr) {}

	//add element
	void add(T elem);
	void addatfirst(T elem);
	void addatlast(T elem);
	void addat(int pos, T elem);
	void removefirst();
	void removelast();
	void removeat(int pos);
	void printlist();
};

//Add element at the first node
template <typename T>void doublelinkedlist<T>::addatfirst(T elem)
{
	//create new node
	Node<T>* new_node = new Node<T>();
	new_node->data = elem;

	//check empty list
	if (m_head == nullptr)
	{
		//assign new node as head node
		m_head = new_node;
		//increase the list size
		++m_size;
	}
	else
	{
		//create new node
		Node<T>* curr_node = m_head;
		curr_node->prev_node = new_node;
		new_node->next_node = curr_node;
		//add new node as head node
		m_head = new_node;
		//increase the list size
		++m_size;
	}
}

//add the element at the last index
template <typename T>void doublelinkedlist<T>::addatlast(T elem)
{
	//if the list is null, then add the element as first node
	if (m_head == nullptr)
	{
		addatfirst(elem);
	}
	else
	{
		//create new node
		Node<T>* new_node = new Node<T>();
		new_node->data = elem;

		Node<T>* curr_node = m_head;
		//iterate till the last node
		while (curr_node->next_node != nullptr)
		{
			curr_node = curr_node->next_node;
		}
		//add node at the end
		curr_node->next_node = new_node;
		new_node->prev_node = curr_node;
		//increase the list size
		++m_size;
	}
}

//add the element at the specific location
template <typename T>void doublelinkedlist<T>::addat(int pos, T elem)
{
	//validate the input parameter
	if (pos > m_size)
	{
		cerr << "addat()  pos not in the range = " << pos << endl;
		return;
	}
	//if list is empty, then add the element in the first node
	if (m_head == nullptr)
	{
		addatfirst(elem);
	}//if list has one element, add the new element at the end
	else if (m_head->next_node == nullptr)
	{
		addatlast(elem);
	}
	else
	{
		Node<T>* current_node = m_head;
		Node<T>* previous_node = nullptr;
		int index = 1;
		//iterate till the position
		while (index != pos)
		{
			index++;
			previous_node = current_node;
			current_node = current_node->next_node;
		}

		//create new node
		Node<T>* new_node = new Node<T>();
		new_node->data = elem;
		
		//insert new node at desired position
		new_node->prev_node = previous_node;
		new_node->next_node = current_node;
		current_node->prev_node = new_node;
		previous_node->next_node = new_node;
		//increase the list size
		++m_size;
	}
}

//add the element at the end
template <typename T> void doublelinkedlist<T>::add(T elem)
{
	addatlast(elem);
}

//remove the first element
template <typename T> void doublelinkedlist<T>::removefirst()
{
	//if list is empty, return 
	if (m_head == nullptr)
	{
		cerr << " removefirst - empty list " << endl;
		return;
	}
	else
	{
		//List has only one element
		if (m_head->next_node == nullptr)
		{
			delete m_head;
			m_head = nullptr;
			m_size = 0; //set the size as zero
		}
		else
		{
			Node<T>* new_node = m_head->next_node;
			new_node->prev_node = nullptr;
			//assign the new node as head node
			m_head = new_node;
			//decrease the size
			--m_size;
		}
	}
}

//remove the last node
template <typename T> void doublelinkedlist<T>::removelast()
{
	//if list is empty
	if (m_head == nullptr)
	{
		cerr << " empty list - removelast" << endl;
		return;
	}
	//if list has only one element
	if (m_head->next_node == nullptr)
	{
		delete m_head;
		m_size = 0;
		m_head = nullptr;
	}
	else
	{
		Node<T>* curr_node = m_head;
		Node<T>* prev_node = nullptr;
		//iterate till the last node
		while (curr_node->next_node != nullptr)
		{
			prev_node = curr_node;
			curr_node = curr_node->next_node;
		}
		if (prev_node) {
			prev_node->next_node = nullptr;
		}
		//delete last node
		delete curr_node;
		//decrease the size
		m_size--;

	}
}

//remove the element at given position
template <typename T> void doublelinkedlist<T>::removeat(int pos)
{
	//list is empty
	if (m_head == nullptr)
	{
		cerr << " empty list :: removeat() " << endl;
		return;
	}
	//invalid input parameter
	if (pos > m_size)
	{
		cerr << " pos is invalid ::removeat = " << pos << endl;
		return;
	}

	//remove the first node
	if (1 == pos) //first element
	{
		removefirst();
	}//pos is size of the list
	else if (pos == m_size)
	{
		removelast();
	}
	else
	{
		int index = 1;
		Node<T>* current_node = m_head;
		Node<T>* previous_node = nullptr;

		//iterate till the desire position
		while (index != pos && current_node->next_node!=nullptr)
		{
			previous_node = current_node;
			current_node = current_node->next_node;
			index++;
		}
		Node<T>* temp_node = current_node;

		current_node = current_node->next_node;
		previous_node->next_node = current_node;
		current_node->prev_node = previous_node;

		//delete the node
		delete temp_node;
		
		//decrease the list size
		--m_size;
	}
}
//print list
template <typename T>void doublelinkedlist<T>::printlist()
{
	if (m_head == nullptr)
	{
		cout << "empty double linked list" << endl;
		return;
	}
	cout << "double linked list" << endl;
	Node<T>* node = m_head;
	while (node)
	{
		cout << node->data << "->";
		node = node->next_node;
	}
	cout << "nullptr"<<endl;
}