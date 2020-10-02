#include "header.h"

/* -----------------------------------------------------------------------------------
* MyQueue public member functions */

MyQueue::MyQueue()
{
	// do nothing
}

void MyQueue::pushBack (int val)
{
	// make the new node
	MyNode* newNode = new MyNode();
	newNode->setNum (val);
	newNode->setNext (NULL);

	if (getHead() == NULL)
	{
		setHead (newNode);
		return;
	}

	MyNode* tail = getHead();
	while (tail->getNext() != NULL)
		tail = tail->getNext();

	tail->setNext (newNode);
}

int MyQueue::getFront()
{
	return getHead()->getNum();
}

void MyQueue::popFront()
{
	pop();
}

/* -----------------------------------------------------------------------------------
* MyStack public member functions */

MyStack::MyStack()
{
	// do nothing
}

void MyStack::pushFront (int val)
{
	insertValue (val);
}

int MyStack::getFront()
{
	return getHead()->getNum();
}

void MyStack::popBack()
{
	if (getHead() == NULL)
		return;

	MyNode* tail = getHead();
	while (tail->getNext() != NULL)
		tail = tail->getNext();

	delete tail;
}