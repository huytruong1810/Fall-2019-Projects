#include "header.h"

/*--------------------------------------------------------------------------
 * queue implementation functions */

/* Returns the length of the queue */
int lenQueue (NODE* cur)
{
	if (cur == NULL) return 0;
	return 1 + lenQueue (cur->Next);
}

/* Displays the information of an order */
void displayOrderInfo (NODE* cur)
{
	/* else, print out all the information of the order */
	printf ("Name: %s\nBurg: %d\nSalad: %d\n", cur->Name, cur->numBurg, cur->numSalad);
	printf ("In-restaurant: ");
	if (cur->IRS) printf ("YES\n\n");
	else printf ("NO\n\n");
}

/* Adds new node to the end of queue. 
 * Used when input a and c commands */
void addToList (NODE** Head, char* name, int numburg, int numsalad, boolean irs) 
{
	/* initialized a new order */
    NODE* newNode = (NODE*) malloc (sizeof (NODE));
	newNode->Name = name;
	newNode->numBurg = numburg;
	newNode->numSalad = numsalad;
	newNode->IRS = irs;
    newNode->Next = NULL;
	
	/* if queue is empty, head is the new node */
	if (*Head == NULL)
	{
		*Head = newNode;
		return;
	}
	/* else, */
	NODE* Tail = *Head;
	/* get the tail of the queue */
	while (Tail->Next != NULL)
	{
		if (debugMode)
		{
			printf ("Order tranversed through: \n");
			displayOrderInfo (Tail);
		}
		
		Tail = Tail->Next;
	}
	/* add the order into the queue */
	Tail->Next = newNode;
	Tail->Next->Next = NULL;
}

/* Returns true if name exists in queue and false if not.  
 * Used when input a, c, w, t and l commands */
boolean doesNameExist (NODE* cur, char* name)
{
	while (cur != NULL)
	{
		if (debugMode)
		{
			printf ("Order tranversed through: \n");
			displayOrderInfo (cur);
		}
		
		/* if name is encountered, return true */
		if (strcmp (cur->Name, name) == 0) return TRUE;
		/* go to next order */
		cur = cur->Next;
	}
	/* reach here means name does not exist in queue */
	return FALSE;
}

/* Marks call ahead order as in-restaurant. 
 * Returns FALSE if that order is already 
 * marked as being in the restaurant.  
 * Used when input w command */
boolean updateStatus (NODE* cur, char* name)
{
	if (cur->IRS) return FALSE;
	cur->IRS = TRUE;
	return TRUE;
}

/* Finds the first in-restaurant order matching 
 * order prepared for pick up at the counter.  
 * Returns the name of group.  
 * Removes group from the queue.  
 * Used when input r command */
char* retrieveAndRemove (NODE* prev)
{
	NODE* keep = prev->Next;
	/* keep the name of that group */
	char* removedGroup = keep->Name;
	/* unlink the group */
	prev->Next = prev->Next->Next;
	/* remove the group from memory */
	free (keep);
	/* return the name of removed group */
	return removedGroup;
}

/* Returns the number of orders ahead of a specified order.  
 * Used when input l command */
int countOrdersAhead (NODE* Head, NODE* cur)
{
	int numOrder = 0;
	/* loop until cur is encountered */
	while (Head != cur)
	{
		if (debugMode)
		{
			printf ("Order tranversed through: \n");
			displayOrderInfo (Head);
		}
		
		/* increments count */
		numOrder++;
		/* go to next order */
		Head = Head->Next;
	}
	return numOrder;
}

/* Returns the estimated waiting time for the specific name.
 * Used when input t command */
int displayWaitingTime (NODE* Head, NODE* cur)
{
	int time = 0;
	while (Head != cur)
	{
		if (debugMode)
		{
			printf ("Order tranversed through: \n");
			displayOrderInfo (Head);
		}
		
		/* keeps adding up the time */
		time += Head->numBurg * 10 + Head->numSalad * 5;
		/* go to next order */
		Head = Head->Next;
	}
	/* return waiting time */
	return time;
}

/* Traverses down the queue until a specified order.
 * Prints out every order on the way.  
 * Used when input l command */
void displayOrdersAhead (NODE* Head, NODE* cur)
{
	int headerNum = 1;
	while (Head != cur)
	{
		if (debugMode)
		{
			printf ("Order tranversed through: \n");
			displayOrderInfo (Head);
		}
		
		/* keeps printing order's information */
		printf ("%d. %d burger(s) and %d salad(s)\n", headerNum, Head->numBurg, Head->numSalad);
		/* increment the header number */
		headerNum++;
		/* go to next order */
		Head = Head->Next;
	}
}

/* Prints out every order's information in the queue.
 * Used when input d command */
void displayListInformation (NODE* cur)
{
	/* loop until end of queue */
	while (cur != NULL)
	{
		/* print out order's information */
		printf ("Name: %s\nBurg: %d\nSalad: %d\n", cur->Name, cur->numBurg, cur->numSalad);
		printf ("In-restaurant: ");
		if (cur->IRS) printf ("YES\n\n");
		else printf ("NO\n\n");
		/* go to next order */
		cur = cur->Next;
	}
}