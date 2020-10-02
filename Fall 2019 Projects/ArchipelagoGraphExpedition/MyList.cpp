#include "header.h"

/* -----------------------------------------------------------------------------------
 * MyNode public member functions */

// default constructor
MyNode::MyNode()
{
	num = -1;
	next = NULL;
}

// set the number of the node
void MyNode::setNum (int val)
{
	num = val;
}

// set the next pointer of the node
void MyNode::setNext (MyNode* ptr)
{
	next = ptr;
}

// returns number of the node
int MyNode::getNum()
{
	return num;
}

// returns next pointer of the node
MyNode* MyNode::getNext()
{
	return next;
}

/* -----------------------------------------------------------------------------------
 * MyList public member functions */

// default constructor
MyList::MyList()
{
	head = NULL;
}

// append a new node to the list
void MyList::insertValue (int val)
{
	// make the new node
	MyNode* newNode = new MyNode();
	newNode->setNum (val);
	newNode->setNext (head);
	head = newNode; // append it in
}

// delete a node with specified 
// value from the list
void MyList::deleteValue (int val)
{
	// if head is null then return
	if (head == NULL)
		return;

	// if head has the value
	if (head->getNum() == val)
	{
		MyNode* temp = head;
		// move the head forward
		head = head->getNext();
		// delete the node
		delete temp;
		return;
	}

	MyNode* cur = head;
	MyNode* prev = NULL;

	while (cur != NULL)
	{
		// if node is found
		if (cur->getNum() == val)
		{
			// re-link the list 
			// skipping that node
			prev->setNext (cur->getNext());
			// delete the node
			delete cur;
			return;
		}

		prev = cur;
		cur = cur->getNext();
	}

	// reach here means node with
	// value is not found, return
	return;
}

// returns the number of values in the list
int MyList::getNumberOfCurrentsValues()
{
	int result = 0; // counter variable
	MyNode* temp = head;

	// loop until fall off the list
	while (temp != NULL)
	{
		result++; // increment result
		temp = temp->getNext(); // go to next node
	}

	return result;
}

// returns the value at Nth position
int MyList::getNthValue (int N)
{
	// if the Nth position is outside of the list
	if (N > getNumberOfCurrentsValues() - 1)
		return -1;

	MyNode* temp = head;

	// loop until reaches Nth position
	while (N != 0)
	{
		temp = temp->getNext(); // go to next node
		N--; // decrement N
	}

	return temp->getNum();
}

// print all the items in the list
void MyList::list()
{
	MyNode* temp = head;
	while (temp != NULL)
	{
		printf ("%d ", temp->getNum());
		temp = temp->getNext();
	}
}

// Removes the first node of the list
void MyList::pop()
{
	// if head is null, return
	if (head == NULL)
		return;
	
	// else, remove the first node
	MyNode* temp = head;
	head = temp->getNext();
	delete temp;
}

// Deletes all items in the list
void MyList::clear()
{
	while (head != NULL)
		pop();
}

// returns true if the node is already
// in the list; otherwise, return false
bool MyList::nodeExist (int val)
{
	// if head is null, return false
	if (head == NULL)
		return FALSE;

	// else, tranverse the list
	MyNode* temp = head;

	while (temp != NULL)
	{
		// if node is encountered
		if (temp->getNum() == val)
				return TRUE; // return true
		temp = temp->getNext(); // go to next node
	}
	
	// reach here means node is not found 
	return FALSE; // return false
}