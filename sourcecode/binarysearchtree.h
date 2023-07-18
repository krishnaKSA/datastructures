#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <iostream>
#include "queueusinglinkedlist.h"
#include "stacksinglelinkedlist.h"

using namespace std;

/* Binary search tree class */
template <typename T> class binarysearchtree
{
private:
	//Node class
	template <typename U> class Node
	{
	public:
		Node<T>* left; //left tree
		Node<T>* right; //right tree
		T data; //element
		//constructor
		Node() :left(nullptr), right(nullptr)
		{
		}
	};

	Node<T>* root; //root node of the BST

public:
	//constructor
	binarysearchtree():root(nullptr)
	{
	}

	//recursive method to add the element
	void addrecursive(T elem)
	{
		if (findelement(root,elem))
		{
			return;
		}
		//call this recursive function
		root = addrecursive(root, elem);
	}
	//recusrive call to add element
	Node<T>* addrecursive(Node<T>* node, T elem)
	{
		//if node is null
		if (node == nullptr)
		{
			//create new node and return it
			Node<T>* node = new Node<T>();
			node->data = elem;
			return node;
		}
		else
		{
			//element is less than the node element , then traverse the left tree
			if (elem < node->data)
			{
				node->left = addrecursive(node->left, elem);
			}
			else
			{
				//element is greater than the node element , then traverse the right tree
				node->right = addrecursive(node->right, elem);
			}
		}
		return node;
	}

	//add the elemenet in the iterative method
	void add(T elem)
	{
		//create new node
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

			//travese the tree
			while (node != nullptr)
			{
				if (elem < node->data) //travese left tree, if element is less than the node data
				{
					if (node->left == nullptr)
					{
						node->left = new_node;
						return;
					}
					else
					{
						node = node->left;
					}
				}
				else if(elem > node->data) //traverse the right tree, if element is greater than the node data
				{
					if (node->right == nullptr)
					{
						node->right = new_node;
						return;
					}
					else
					{
						node = node->right;
					}
				}
			}
		}
	}
	//level order traversal
	void print_levelordertraversal()
	{
		if (root == nullptr)
			return;
		
		Node<T>* node = root;

		cout << "level order traversal ";
		//use the custom queue designed from linked list
		queuelist<Node<T>*>* queue = new queuelist<Node<T>*>();

		//add the root node to the queue
		queue->enqueue(node);

		//traverse until queue is empty
		while (!queue->isEmpty())
		{	
			 //get the node
			 node = queue->dequeue();
			 if (node == nullptr)
			 {
				 cout << "null   ";
			 }
			 else
			 {
				 //print the node value
				 cout << node->data << " ";
				 //if node's left node is valid
				 if (node->left)
				 {
					 //add the left node to the queue for traversal
					 queue->enqueue(node->left);
				 }
				 //if node's right node is valid
				 if (node->right)
				 {
					 //add the right node to the queue for traversal
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
			cout << "no element in bst" << endl;
			return;
		}
		else
		{
			//element is found
			if (findelement(root, elem))
			{
				root = remove(root, elem);
			}
			else cout << "element not found in bst" << endl;
		}
	}

	//find the element
	bool findelement(Node<T>* node, T elem)
	{
		//travese till the node is not nullptr
		while (node)
		{
			//element is same as node->data
			if (node->data == elem)
			{
				return true;
			}
			else if (node->data > elem)
			{
				//element is less than node->data , traverse the left tree
				node = node->left;
			}
			else
			{
				//element is greater than node->data , traverse the right tree
				node = node->right;
			}
		}
		return false;
	}

	//Recurive call to remove the element from the tree
	Node<T>* remove(Node<T>* root, T elem)
	{
		//base condition, node is nullptr
		if (root == nullptr)
		{
			return nullptr;
		}

		Node<T>* node = root;
		Node<T>* temp = nullptr;

		if (elem < node->data)
		{
			//element is less than node->data , traverse the left tree
			node->left = remove(node->left, elem);
		}
		else if(elem > node->data)
		{
			//element is greater than node->data , traverse the right tree
			node->right = remove(node->right, elem);
		}
		else
		{
			//if node's both right and left tree is empty, then delete node
			if (node->left == nullptr && node->right == nullptr)
			{
				delete node;
				node = nullptr;
			}
			//if node's right tree is only empty
			else if (node->right == nullptr )
			{
				temp = node;
				//then assign the node's left tree to node
				node = node->left;
				//delete node
				delete temp;
				temp = nullptr;
			}
			//if node's left tree is only empty
			else if (node->left == nullptr )
			{
				temp = node;
				//then assign the node's right tree to node
				node = node->right;
				//delete node
				delete temp;
				temp = nullptr;

			}
			else
			{
				//if node's both righ and left trees are not nullptr, 
				//find the min value node from right sub tree
				temp = findminnode(node->right);
				
				if (temp)
				{
					//assign the right sub tree min node value to the node->data
					node->data = temp->data;
				}
				//traverse right sub tree to remove the element
				node->right = remove(node->right, elem);
			}

		}
		return node;
	}

	//find min node by traverse through left sub tree
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
			return nullptr;

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

	//preorder display
	void print_preordertraversal()
	{
		if (root != nullptr)
		{
			Node<T>* node = root;

			//create stack by custom stack using linked list
			liststack<Node<T>*> *stack = new liststack<Node<T>*>();

			//push the root node
			stack->push(node);

			cout << " pre order  ";
			//traverse till stack is empty
			while (!stack->isEmpty())
			{
				//get the top node
				node = stack->top();
				//remove the top node
				stack->pop();
				//print the node value
				cout << node->data << " ";

				//Push the right subtree first
				if (node->right)
				{
					stack->push(node->right);
				}

				//second, push the left subtree
				if (node->left)
				{
					stack->push(node->left);
				}
				//traverse through the left sub tree
				node = node->left;
			}
			delete stack;
		}
		cout << endl;
	}

	void print_inordertraversal()
	{
		if (root != nullptr)
		{
			Node<T>* node = root;

			//create stack by custom stack using linked list
			liststack<Node<T>*>* stack = new liststack<Node<T>*>();

			cout << " in order  ";
			while (!stack->isEmpty() || node !=nullptr)
			{
				//if node is not nullptr, push the node to the stack
				if (node)
				{					
					stack->push(node);
					//traverse through left sub tree
					node = node->left;
				}
				else
				{
					//get the top element
					node = stack->top();

					//remove the top element
					stack->pop();

					//print the data
					cout << node->data << " ";

					//traverse through right sub tree
					node = node->right;
				}
			}
			delete stack;
		}
		cout << endl;
	}
};


template <typename T> class testbinarysearchtree
{
public:
	void testexecution()
	{
		binarysearchtree<int>* bst = new binarysearchtree<int>();

		bst->add(10);
		bst->add(9);
		bst->add(7);
		bst->add(16);
		bst->add(18);
		bst->add(15);
		bst->add(5);
		bst->add(40);
		bst->add(20);

		bst->print_levelordertraversal();
		bst->print_inordertraversal();
		bst->print_preordertraversal();
		bst->print_levelordertraversal();

		cout << "height of the bst === " << bst->height() << endl;

		bst->remove(5);
		bst->remove(9);
		bst->remove(18);
		bst->remove(0);
		bst->print_levelordertraversal();

		cout << endl << endl;
		binarysearchtree<int>* bst1 = new binarysearchtree<int>();

		cout << "bst1 height " << bst1->height() << endl;
		bst1->addrecursive(10);
		cout << "bst1 height " << bst1->height() << endl;
		bst1->addrecursive(5);
		cout << "bst1 height " << bst1->height() << endl;
		bst1->addrecursive(19);
		cout << "bst1 height " << bst1->height() << endl;
		bst1->addrecursive(23);
		bst1->addrecursive(7);
		bst1->print_levelordertraversal();
	}
};

#endif