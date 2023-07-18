#include <iostream>
#include "stackusingarray.h"
#include "linkedList.h"
#include "stacksinglelinkedlist.h"
#include "queueusingdynamicarray.h"
#include "queueusinglinkedlist.h"
#include "binaryheap.h"
#include "binarysearchtree.h"
#include "AVLbalancedtree.h"
#include "trie.h"

using namespace std;

extern void doublelinkedlist_test();

int main()
{
	//stackarrtest<int> test;
	//test.testexecution();

	//stacklisttest<int> teststacklist;
	//teststacklist.testexecution();

	//linkedListest<int>* testlinkedlist = new linkedListest<int>();
    //testlinkedlist->testexecution();

	queuearraytest<int>* queuetest = new queuearraytest<int>();
	//queuetest->testexecution();

	queuelinkedlisttest<int>* queuelisttest = new queuelinkedlisttest<int>();
	//queuelisttest->testexecution();

	testbinarysearchtree<int>* testBST = new testbinarysearchtree<int>();
	//testBST->testexecution();

	testbinaryheap<int>* testheap = new testbinaryheap<int>();
	testheap->testexecution();

	//testavlbalancedbts<int> testbts;
	//testbts.testexecution();

	//testavlbalancedbts<int> testavl;
	//testavl.testexecution();

	//testtrie test;
	//test.testexecution();

	//doublelinkedlist_test();
}

