#include <iostream>
#include "doublelinkedlist.h"

using namespace std;

void doublelinkedlist_test()
{
	doublelinkedlist<int>* list = new doublelinkedlist<int>();

	list->addatlast(10);
	list->addatfirst(20);
	list->add(40);
	list->addat(2, 50);
	list->addat(100, 4);

	list->printlist();

	list->removeat(100);
	list->removeat(2);
	list->printlist();
	list->removefirst();
	list->printlist();
	list->removelast();
	list->printlist();
	list->removefirst();
	list->printlist();
}