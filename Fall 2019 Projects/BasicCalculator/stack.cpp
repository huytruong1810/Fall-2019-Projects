#include "header.h"

// initialize the stack
MyStack::MyStack()
{
	capacity = 2;
	arr = new Token[capacity];
	inUse = -1;
}

// return true if the stack has no members
bool MyStack::isEmpty() 
{ 
	if (inUse < 0)
		return true;
	return false;
}

// add the data to the top of stack; grow dynamic array if needed
void MyStack::push (Token data) 
{
	// if the stack is full, grow it
	if (inUse == (capacity - 1))
		grow ();

	inUse++;
	arr[inUse] = data;
} 

// return the data value on the top of the stack
void MyStack::pop() 
{ 
	if (inUse > -1)
	{
		inUse--;
	}
} 

// remove the data value from the top of the stack
Token MyStack::top() 
{ 
	if (inUse > -1)
		return arr[inUse];
}

// “clear” the stack to remove any values it contains 
void MyStack::reset()
{
	delete arr;
	capacity = 2;
	inUse = -1;
}