#ifndef AVLBALANCEDTREE_H
#define AVLBALANCEDTREE_H

#include <iostream>
#include "queueusinglinkedlist.h"
#include "stacksinglelinkedlist.h"

using namespace std;

/* AVL balanced binary search tree class*/
template <typename T> class avlbalancedbts
{
private:

	/* node */
	template <typename U>class Node
	{
	public:

		Node<T>* left; //left tree
		Node<T>* right; //right tree
		T data;  //data
		int height; //height of the tree
		int bf; //balance factor

		//constructor
		Node() :left(nullptr), right(nullptr) 
		{
		}
	};

	//root node
	Node<T>* root;

public:
	//constructor
	avlbalancedbts() :root(nullptr) 
	{
	}

	//add element
	void addrecursive(T elem)
	{
		//if the element is already found, return
		if (findelement(root, elem))
		{
			return;
		}

		//add element
		root = addrecursive(root, elem);
	}

	//recursive call to add the element to the tree
	Node<T>* addrecursive(Node<T>* node, T elem)
	{
		//if node is null, add new node and return new node
		if (node == nullptr)
		{
			//new node creation
			Node<T>* new_node = new Node<T>();
			new_node->data = elem;
			node = new_node;
		}
		else
		{
			//if element value is less than node value, then traverse the left sub tree
			if (elem < node->data)
			{
				node->left = addrecursive(node->left, elem);
			}
			else
			{
				//if element value is greater than node value, then traverse the right sub tree
				node->right = addrecursive(node->right, elem);
			}
		}

		//find balance factor of the node
		findbalancefactor(node);

		//balance the tree and return the node
		return balance(node);
	}

	//balance the tree
	Node<T>* balance(Node<T>* node)
	{
		if (node == nullptr)
			return nullptr;

		//left side heavy tree
		if (node->bf == -2) 
		{
			//rightrotation
			if (node->left->bf <= 0)
			{
				return leftleftrotation(node); 
			}
			else
			{
				//leftright rotation
				return leftrightrotation(node);
			}
		}
		//right side heavy tree
		else if (node->bf == +2) 
		{
			//balance factor is greater or equal to zero
			if (node->right->bf >= 0)
			{
				//leftrotation similar to rightright rotation
				return rightrightrotation(node); 
			}
			else
			{
				//rightleft rotation
				return rightleftrotation(node);
			}
		}
		//if bf is 0 (or) -1 (or) 1
		return node;
	}

	//left left rotation equal to right rotation
	Node<T>* leftleftrotation(Node<T>* node)
	{
		//right rotation
		return rightrotation(node);
	}

	//right right rotation equal to left rotation
	Node<T>* rightrightrotation(Node<T>* node)
	{
		//left rotation
		return leftrotation(node);
	}

	//right left rotation
	Node<T>* rightleftrotation(Node<T>* node)
	{
		node->right = rightrotation(node->right);
		return leftrotation(node);
	}

	//left right rotation
	Node<T>* leftrightrotation(Node<T>* node)
	{
		node->left = leftrotation(node->left);
		return rightrotation(node);
	}

	//left rotation
	Node<T>* leftrotation(Node<T>* node)
	{
		Node<T>* newparent = node->right;
		node->right = newparent->left;
		newparent->left = node;

		//find balance factor of the node
		findbalancefactor(node);

		//find balance factor of new parent
		findbalancefactor(newparent);

		return newparent;
	}

	//right rotation
	Node<T>* rightrotation(Node<T>* node)
	{
		Node<T>* newparent = node->left;
		node->left = newparent->right;
		newparent->right = node;

		//find balance factor of the node
		findbalancefactor(node);

		//find balance factor of new parent
		findbalancefactor(newparent);

		return newparent;
	}

	//find the balance factor of the node
	void findbalancefactor(Node<T>* node)
	{
		if (node == nullptr)
		return;
		
		int lh, rh;
		lh = rh = 0;

		//left node height
		if (node->left)
		{
			lh = node->left->height;
		}

		//right node height
		if (node->right)
		{
			rh = node->right->height;
		}

		//node height is maximum of left and right sub tree
		node->height = std::max(lh, rh) + 1;

		//balance factor is difference between the height if the right and left subtree
		node->bf = rh - lh;
	}

	//add the element iterative method
	void add(T elem)
	{
		Node<T>* new_node = new Node<T>();
		new_node->data = elem;

		//root node creation
		if (root == nullptr)
		{
			root = new_node;
		}
		else //traverse the tree and add element accordingly 
		{
			Node<T>* node = root;

			//traverse till leaf node
			while (node != nullptr)
			{
				//if the element value is less than the node's data
				if (elem < node->data) //travese left sub tree
				{
					//if the left node is null, assign the newnode as left node
					if (node->left == nullptr)
					{
						node->left = new_node;
						return;
					}
					else
					{
						//traverse the left sub tree
						node = node->left;
					}
				}
				//if the element value is greater than the node's data
				else if (elem > node->data)
				{
					//if the right node is null, assign the newnode as right node
					if (node->right == nullptr)
					{
						node->right = new_node;
						return;
					}
					else
					{
						//traverse the right sub tree
						node = node->right;
					}
				}
			}
		}
	}

	//print level order traversal of the tree
	void print_levelordertraversal()
	{
		if (root == nullptr)
		{
			return;
		}

		Node<T>* node = root;

		cout << "level order traversal "<<endl;

		//create queue 
		//Here, used custom queue created using linked list
		queuelist<Node<T>*>* queue = new queuelist<Node<T>*>();

		//add the node to the queue
		queue->enqueue(node);

		//iterate till queue becomes empty
		while (!queue->isEmpty())
		{
			//remove the element from the queue
			node = queue->dequeue();

			if (node == nullptr)
			{
				cout << "null   ";
			}
			else
			{
				cout <<"data "<< node->data << " bf = " << node->bf << " height = " << node->height << endl;

				//If left node is valid
				if (node->left)
				{
					//add left node to the queue
					queue->enqueue(node->left);
				}
				//If right node is valid
				if (node->right)
				{
					//add right node to the queue
					queue->enqueue(node->right);
				}
			}
		}

		cout << endl;
	}

	//remove the element
	void remove(T elem)
	{
		if (root == nullptr)
		{
			cout << "no element in BTS" << endl;
			return;
		}
		else
		{
			//if element is found
			if (findelement(root, elem))
			{
				//recursive remove function
				root = remove(root, elem);
			}
			else
			{
				cout << "element not found in BTS" << endl;
			}
		}
	}

	//find the element from the tree
	bool findelement(Node<T>* node, T elem)
	{
		//traverse till the node is valid
		while (node)
		{
			//element is same node's data
			if (node->data == elem)
			{
				return true;
			}
			//if the element value is less than the node data, traverse on the left tree
			else if (node->data > elem)
			{
				node = node->left;
			}
			else
			{
				//traverse the right tree
				node = node->right;
			}
		}
		return false;
	}

	//recursive method to remove the element
	Node<T>* remove(Node<T>* node, T elem)
	{
		if (node == nullptr)
		{
			return nullptr;
		}

		Node<T>* temp = nullptr;

		//if the element value is less than the node data, traverse on the left tree
		if (elem < node->data)
		{
			//left tree traversal
			node->left = remove(node->left, elem);
		}
		else if (elem > node->data)
		{
			//right tree traversal
			node->right = remove(node->right, elem);
		}
		else
		{
			//if both the left and right node is null, then delete the node
			if (node->left == nullptr && node->right == nullptr)
			{
				delete node;
				node = nullptr;
			}
			//if only right node is null
			else if (node->right == nullptr)
			{
				//assign the node->left as node
				temp = node;
				node = node->left;
				//delete node
				delete temp;
				temp = nullptr;
			}
			//if only left node is null
			else if (node->left == nullptr)
			{
				//assign the node->right as node
				temp = node;
				node = node->right;
				//delete node
				delete temp;
				temp = nullptr;

			}
			else
			{
				//if both left and right node is valid, find the min node from the right tree
				temp = findminnode(node->right);

				if (temp)
				{
					node->data = temp->data;
				}
				//traverse through the right tree to remove the data
				node->right = remove(node->right, temp->data);
			}

		}
		//find the balance factor after the remove 
		findbalancefactor(node);

		//balance the tree
		return balance(node);
	}

	//find min node of the right subtree
	Node<T>* findminnode(Node<T>* node)
	{
		Node<T>* mindata = nullptr;

		//if node is null
		if (node == nullptr)
			return mindata;

		mindata = node;

		//traverse till leaf node
		while (node != nullptr)
		{
			//node data value is less than mindata value
			if (mindata->data > node->data)
			{
				mindata = node;
			}
			//since finding minimum, traverse through left sub tree
			node = node->left;

		}
		return mindata;
	}

	//find the maximum value by traverse through right sub tree
	Node<T>* findmaxnode(Node<T>* node)
	{
		//node is null
		if (node == nullptr)
		{
			return nullptr;
		}

		Node<T>* maxdata = node;

		//traverse till leaf node
		while (node != nullptr)
		{
			//node data value is greater than maxdata value
			if (maxdata->data < node->data)
			{
				maxdata = node;
			}
			//since finding maximum, traverse through right sub tree
			node = node->right;

		}
		return maxdata;
	}

	//find height of the BST
	int height()
	{
		return height(root);
	}

	//recursive function to find the height of the node
	int height(Node<T>* node)
	{

		if (node == nullptr)
		{
			return 0;
		}
		else
		{
			//max between right and left node
			return std::max(height(node->left), height(node->right)) + 1;
		}
	}

	//print preorder 
	void print_preordertraversal()
	{
		if (root != nullptr)
		{
			Node<T>* node = root;

			//create stack
			//here created stack using custom stack built by linkedlist
			liststack<Node<T>*>* stack = new liststack<Node<T>*>();

			//push the root node to the stack
			stack->push(node);
			cout << " pre order  ";

			//traverse till the stack is empty
			while (!stack->isEmpty())
			{
				//Get the top element from the stack
				node = stack->top();
				//remove the top element from the stack
				stack->pop();
				cout << node->data << " ";

				//if right node is valid, push the right node first
				if (node->right)
				{
					stack->push(node->right);
				}
				//if left node is valid, push the left node 
				if (node->left)
				{
					stack->push(node->left);
				}
				//traverse the left tree
				node = node->left;
			}
			delete stack;
		}
		cout << endl;
	}

	//print inorder 
	void print_inordertraversal()
	{
		if (root != nullptr)
		{
			Node<T>* node = root;

			//create stack
			//here created stack using custom stack built by linkedlist
			liststack<Node<T>*>* stack = new liststack<Node<T>*>();
			
			cout << " in order  ";

			//traverse till the stack is empty
			while (!stack->isEmpty() || node != nullptr)
			{
				if (node)
				{
					//push the node
					stack->push(node);
					//traverse through the left tree
					node = node->left;
				}
				else
				{
					//get the top element from the stack
					node = stack->top();
					//remove the top element from the stack
					stack->pop();
					cout << node->data << " ";

					//traverse through the right tree
					node = node->right;
				}
			}
			delete stack;
		}
		cout << endl;
	}
};


template <typename T> class testavlbalancedbts
{
public:
	void testexecution()
	{
		avlbalancedbts<int>* bts = new avlbalancedbts<int>();

		bts->addrecursive(10);
		bts->addrecursive(9);
		bts->addrecursive(7);
		bts->addrecursive(16);
		bts->addrecursive(18);
		bts->addrecursive(15);
		bts->addrecursive(5);
		bts->addrecursive(40);
		bts->addrecursive(20);

		bts->print_levelordertraversal();
		bts->print_inordertraversal();
		bts->print_preordertraversal();
		bts->print_levelordertraversal();

		cout << "height of the BTS === " << bts->height() << endl;

		bts->remove(5);
		bts->remove(9);
		bts->remove(18);
		bts->remove(0);
		bts->print_levelordertraversal();

		cout << endl << endl;
		avlbalancedbts<int>* bts1 = new avlbalancedbts<int>();

		cout << "bts1 height " << bts1->height() << endl;
		bts1->addrecursive(10);
		cout << "bts1 height " << bts1->height() << endl;
		bts1->addrecursive(5);
		cout << "bts1 height " << bts1->height() << endl;
		bts1->addrecursive(19);
		cout << "bts1 height " << bts1->height() << endl;
		bts1->addrecursive(23);
		bts1->addrecursive(7);
		bts1->print_levelordertraversal();
	}
};

#endif