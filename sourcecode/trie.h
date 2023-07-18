#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

/* trie class */
class trie
{	
public:

	//trienode class
	class trienode
	{
		public:
			char m_ch; //char which node holds it

			bool m_endofstring; //end of string

			//trie class should have 26 pointers (characters in alphabets) to point the child nodes, 
			//as it takes more memory also not all the child nodes are used, instead of creating the 26 pointer nodes
			//used unordered_map to hold child nodes.
			//unorderemap is based on hash table, it doesn't store sorted values. 

			unordered_map<char, trienode*> child;  

			int count; //num of shared prefix for different words

			//constructor
			trienode() : m_ch{ '\0' }, m_endofstring(false), count(0)
			{
			}

			trienode(char ch) :m_ch(ch), m_endofstring(false),count(0) 
			{
			}

			//add character as child of the current node
			void addchild(char ch, trienode* node)
			{
				child.insert({ ch,node });
			}
	};

	//head trienode
	trienode* m_head;

	//constructor
	trie()
	{
		m_head = new trienode();
	}

	//insert new word
	void insert(string text)
	{
		//check head
		if (m_head != nullptr)
		{
			trienode* node = m_head;
			trienode* nextnode = nullptr;

			//text is valid
			if (!text.empty())
			{
				//iterate through each character of the text
				for (char ch : text)
				{
					//find place to add new string
					auto _startnode = node->child.find(ch);
					
					//if character is already exist, then startnode is valid
					if (node->child.end() != _startnode)
					{
						//go to the trienode of the character
						nextnode = _startnode->second;
					}
					else
					{
						//if char is not present , then add the new char as child of the current node
						nextnode = new trienode(ch);
						node->addchild(ch, nextnode);
					}
					//increment the prefix
					nextnode->count += 1;
					node = nextnode;
				}
				//once the word is inserted, add endofstring flag
				node->m_endofstring = true;
				
			}
		}
	}

	//search the text
	bool search(string text)
	{
		bool ret_value = false;

		//if node doesn't have child node to search
		if (m_head->child.empty())
		{
			cout << "no data available" << endl;
		}
		else if (text.empty())
		{
			cout << "search text is empty" << endl;
		}
		else
		{
			trienode* node = m_head;

			//iterate through all the characters
			for (char ch : text)
			{
				auto search = node->child.find(ch);

				if (search != node->child.end())
				{
					//if char is found, go to child node and continue the search till the last char
					node = search->second;
				}
				else
				{
					//character in the text is not found 
					return false;
				}
			}
			if (node->m_endofstring)
			{
				ret_value = true;
			}
		}

		return ret_value;
	}

	//delete the string
	bool deletestring(string text)
	{
		bool isdeleted = false;

		//empty child tree
		if (m_head->child.empty())
		{
			cout << "empty tree" << endl;
			return false;
		}
		else if (text.empty())
		{
			cout << "empty string" << endl;
			return false;
		}
		else
		{
			trienode* node = m_head;
			trienode* nextnode = nullptr;

			for (char ch : text)
			{
				auto search = node->child.find(ch);

				//if char is found, go to child node and continue till the last char
				if (search != node->child.end())
				{
					nextnode = search->second;
					//reduce the prefix count
					nextnode->count--;

					//if no other word is shring this char 
					if (nextnode->count <= 0)
					{					
						//nextnode = node;						
						node->child.erase(ch);
						
						return true;
					}
					node = nextnode;
				}
				else
				{
					return false;
				}
				
			}
		}
		return true;
	}

};

class testtrie
{
public:

	void testexecution()
	{
		trie* m_trie = new trie();

		cout << "search word rat = "<<m_trie->search("rat") << endl;
		cout << "search word empty = "<<m_trie->search("") << endl;

		m_trie->insert("catride");
		cout << "search word cat = " << m_trie->search("cat") << endl;
		cout << "search word catride = " << m_trie->search("catride") << endl;
		m_trie->insert("cab");
		m_trie->insert("rat");

		cout << "search word ratt = " << m_trie->search("ratt") << endl;
		m_trie->insert("ratt");
		cout << "search word ratt = " << m_trie->search("ratt") << endl;
		m_trie->insert("rats");

		cout << "delte string rat = " << m_trie->deletestring("rat") << endl;
		cout << "delte string ratt = " << m_trie->deletestring("ratt") << endl;
		cout << "delte string rats = " << m_trie->deletestring("rats") << endl;
		cout << "delte string cas = " << m_trie->deletestring("cas") << endl;
	}
};
