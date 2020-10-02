#include "header.h"

/* -----------------------------------------------------------------------------------
 * FNODE public member functions */

// default constructor
FNODE::FNODE()
{
	name = NULL;
	next = NULL;
}

// set the name of the node
void FNODE::setName (char* str)
{
	name = str;
}

// set the next pointer of the node
void FNODE::setNext (FNODE* ptr)
{
	next = ptr;
}

// returns name of the node
char* FNODE::getName()
{
	return name;
}

// returns next pointer of the node
FNODE* FNODE::getNext()
{
	return next;
}

/* -----------------------------------------------------------------------------------
 * FList public member functions */

// default constructor
FList::FList()
{
	head = NULL;
}

// destructor
FList::~FList()
{
  clear();
}

// Removes the first node of the list
void FList::pop()
{
	// if head is null, return
	if (head == NULL)
		return;
	
	// else, remove the first node
	FNODE* temp = head;
	head = temp->getNext();
	delete temp;
}

// Deletes all items in the list
void FList::clear()
{
	while (head != NULL)
		pop();
}

// append a new file to the list
void FList::insertFile (char* str)
{
	// make the new node
	FNODE* newNode = new FNODE();
	newNode->setName (str);
	newNode->setNext (head);
	head = newNode; // append it in
}

// delete a node with specified 
// value from the list
void FList::deleteFile (char* str)
{
	// if head is null then return
	if (head == NULL)
		return;

	// if head has the value
	if (strcmp (head->getName(), str) == 0)
	{
		FNODE* temp = head;
		// move the head forward
		head = head->getNext();
		// delete the node
		delete temp;
		return;
	}

	FNODE* cur = head;
	FNODE* prev = NULL;

	while (cur != NULL)
	{
		// if node is found
		if (strcmp (cur->getName(), str) == 0)
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

// returns true if the node is already
// in the list; otherwise, return false
bool FList::fileExist (char* str)
{
	// if head is null, return false
	if (head == NULL)
		return FALSE;

	// else, tranverse the list
	FNODE* temp = head;

	while (temp != NULL)
	{
		// if node is encountered
		if (strcmp (temp->getName(), str) == 0)
				return TRUE; // return true
		temp = temp->getNext(); // go to next node
	}
	
	// reach here means node is not found 
	return FALSE; // return false
}