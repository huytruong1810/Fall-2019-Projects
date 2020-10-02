#include "header.h"

/*--------------------------------------------------------------------------
 * doXXXX() functions */

/* Add the order to the order list using the given order 
 * and name specifying the group is waiting in the restaurant */
void doAdd (NODE** Head)
{
 /* get number of burgers ordered from input */
 int NumBurgers = getPosInt();
 if (NumBurgers < 0)
   {
    printf ("Error: Add command requires an integer value of at least 0\n");
    printf ("Add command is of form: a <# burgers> <# salads> <name>\n");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    return;
   }

  /* get number of salads ordered from input */
 int NumSalads = getPosInt(); 
 if (NumSalads < 0)
   {
    printf ("Error: Add command requires an integer value of at least 0\n");
    printf ("Add command is of form: a <# burgers> <# salads> <name>\n");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    return;
   }  

 /* get group name from input */
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: Add command requires a name to be given\n");
    printf ("Add command is of form: a <# burgers> <# salads> <name>\n");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    return;
   }

 printf ("Adding In-restaurant order for \"%s\": %d burgers and %d salads\n", name,NumBurgers ,NumSalads);
  
 // add code to perform this operation here
 
 NODE* cur = *Head;
 // if order already exist in queue, exit
 if (doesNameExist (cur, name))
 {
	 printf ("Error: order already exist.\nNo action is taken.\n");
	 return;
 }
 // else, add the order to the queue and set status to in-restaurant
 addToList (Head, name, NumBurgers, NumSalads, TRUE);
}

/* Add the order to the order list using the given order 
 * and name specifying the order as a call ahead order */
void doCallAhead (NODE** Head)
{
 /* get number of burgers ordered from input */
 int NumBurgers = getPosInt();
 if (NumBurgers < 0)
   {
    printf ("Error: Call-ahead command requires an integer value of at least 0\n");
    printf ("Call-ahead command is of form: c <# burgers> <# salads> <name>\n");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    return;
   }

  /* get number of salads ordered from input */
 int NumSalads = getPosInt(); 
 if (NumSalads < 0)
   {
    printf ("Error: Call-ahead command requires an integer value of at least 0\n");
    printf ("Call-ahead command is of form: c <# burgers> <# salads> <name>\n");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    return;
   }  


 /* get group name from input */
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: Call-ahead command requires a name to be given\n");
    printf ("Call-ahead command is of form: c <# burgers> <# salads> <name>\n");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    return;
   }

 printf ("Adding Call-ahead order for \"%s\": %d burgers and %d salads\n", name,NumBurgers ,NumSalads);

 // add code to perform this operation here
 
 NODE* cur = *Head;
 // if order already exist in queue, exit
 if (doesNameExist (cur, name))
 {
	 printf ("Error: order already exist.\nNo action is taken.\n");
	 return;
 }
 // else, add the order to the queue and set status to call-ahead
 addToList (Head, name, NumBurgers, NumSalads, FALSE);
}

/* Mark the call ahead orderusing the given name as waiting in the restaurant */
void doWaiting (NODE* cur)
{
 /* get order name from input */
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: Waiting command requires a name to be given\n");
    printf ("Waiting command is of form: w <name>\n");
    printf ("  where: <name> is the name of the group that is now waiting\n");
    return;
   }

 // add code to perform this operation here
 
 // if queue is empty, exit
 if (cur == NULL)
 {
	 printf ("Error: list is empty.\nNo action is taken.\n");
	 return;
 }

 // else if order does exist in queue
 if (doesNameExist (cur, name))
 {
	 // get the order with specified name
	 while (strcmp (cur->Name, name) != 0)
	 {
		 if (debugMode)
		{
			printf ("Order tranversed through: \n");
			displayOrderInfo (cur);
		}
		 
		 cur = cur->Next;
	 }
	 // update the order's status
	 if (updateStatus (cur, name))
		 printf ("Call-ahead order \"%s\" is now waiting in the restaurant\n", name);
	 // if order is already in restaurant, print error message
	 else printf ("Error: order is not call-ahead.\nNo action is taken.\n");
 }
 // else, print error message
 else printf ("Error: order is not found.\nNo action is taken.\n");
}

/* Retrieve and remove the first order on the order list
 * that is waiting in the restaurant and contains less 
 * than or equal to number of prepared burgers and salads */
void doRetrieve (NODE** Head)
{
 /* get info of prepared food ready on the counter from input */
 int PreparedBurgers = getPosInt();
 if (PreparedBurgers < 0)
   {
    printf ("Error: Retrieve command requires an integer value of at least 0\n");
    printf ("Retrieve command is of form: r <# burgers> <# salads>\n");
    printf ("  where: <# burgers> is the number of burgers waiting on the counter for pick up\n");
    printf ("         <# saladss> is the number of salads waiting on the counter for pick up\n");
    return;
   }

 int PreparedSalads = getPosInt();
 if (PreparedSalads < 0)
   {
    printf ("Error: Retrieve command requires an integer value of at least 0\n");
    printf ("Retrieve command is of form: r <# burgers> <# salads>\n");
    printf ("  where: <# burgers> is the number of burgers waiting on the counter for pick up\n");
    printf ("         <# saladss> is the number of salads waiting on the counter for pick up\n");
    return;
   }   

 clearToEoln();
 printf ("Retrieve (and remove) the first group that can pick up the order of %d burgers and %d salads\n", PreparedBurgers ,PreparedSalads);

 // add code to perform this operation here
 
 // if queue is empty, exit
 if (*Head == NULL)
 {
	 printf ("Error: list is empty.\nNo action is taken.\n");
	 return;
 }
	
 // else if the going-to-be-retrieved order is the first order
 if (PreparedBurgers >= (*Head)->numBurg &&
	 PreparedSalads >= (*Head)->numSalad &&
	 (*Head)->IRS)
 {
	 NODE* temp = *Head;
	 printf ("Order named %s has been removed.\n", temp->Name);
	 *Head = (*Head)->Next;
	 free (temp);
	 return;
 }
 
 NODE* cur = *Head;
 // reach here means the order is not the first one
 cur = (*Head)->Next;
 NODE* prev = *Head;
 while (cur != NULL)
 {
	 if (debugMode)
	 {
		 printf ("Order tranversed through: \n");
		 displayOrderInfo (cur);
	 } 
	 
	 if (PreparedBurgers >= cur->numBurg &&
		 PreparedSalads >= cur->numSalad &&
		 cur->IRS)
	 {
		 printf ("Order named \"%s\" has been removed.\n", retrieveAndRemove (prev));
		 return;
	 }
	 // update prev to be the order previous to cur
	 prev = cur;
	 // go to next order
	 cur = cur->Next;	 
 }

 // reach here means order is not in queue
 printf ("Error: order is not found.\nNo action is taken.\n");
}

/* List total number of orders that are in the order 
 * list in front of the order specified by the given name
 * and display all those orders */
void doList (NODE* Head)
{
 /* get order name from input */
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: List command requires a name to be given\n");
    printf ("List command is of form: l <name>\n");
    printf ("  where: <name> is the name of the order to inquire about\n");
    return;
   }

 // add code to perform this operation here
 
 // if queue is empty, exit
 if (Head == NULL)
 {
	 printf ("Error: list is empty.\nNo action is taken.\n");
	 return;
 }
	
 // else if order does exist in queue
 if (doesNameExist (Head, name))
 {
	 NODE* cur = Head;
	 // get the order with specified name
	 while (strcmp (cur->Name, name) != 0)
	 {
		 if (debugMode)
		 {
			 printf ("Order tranversed through: \n");
			 displayOrderInfo (cur);
		 } 
		 
		 cur = cur->Next;
	 }
	 // display the number of order ahead and those order's information
	 printf ("There are %d orders ahead of \"%s\".\n", countOrdersAhead (Head, cur), name);
	 if (countOrdersAhead (Head, cur) == 0) return;
	 printf ("Order for \"%s\" is behind the following orders:\n", name);
	 displayOrdersAhead (Head, cur);
 }
 // else, print error message
 else printf ("Error: order is not found.\nNo action is taken.\n");
}

/* Display the total number of orders in the orderlist. Also 
 * display the names, order details and in-restaurant status of 
 * all orders in the order list in order from first to last */
void doDisplay (NODE* Head)
{
 clearToEoln();
 printf ("Display information about all orders\n");

 // add code to perform this operation here
 
 // if queue is empty, exit
 if (Head == NULL)
 {
	 printf ("Error: list is empty.\nNo action is taken.\n");
	 return;
 }
	
 // else, display all order in queue
 printf ("There is/are %d order(s).\n", lenQueue (Head));
 displayListInformation (Head);
}

/* Give an estimated waiting time based on the order list knowing 
 * preparing burgers will take 10 minutes and preparing salads takes 5 */
void doEstimateTime (NODE* Head)
{
 /* get order name from input */
 
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: List command requires a name to be given\n");
    printf ("List command is of form: t <name>\n");
    printf ("  where: <name> is the name of the order to inquire about\n");
    return;
   }


 // add code to perform this operation here  
  
 // if queue is empty, exit
 if (Head == NULL)
 {
	 printf ("Error: list is empty.\nNo action is taken.\n");
	 return;
 }

 // else if order does exist in queue
 if (doesNameExist (Head, name))
 {
	 NODE* cur = Head;
	 // get the order with specified name
	 while (strcmp (cur->Name, name) != 0)
	 {
		 if (debugMode)
		{
			printf ("Order tranversed through: \n");
			displayOrderInfo (cur);
		}
		 
		 cur = cur->Next;
	 }
	 // display the estimated waiting time
	 printf ("The estimated waiting time is: %d minutes.\n", displayWaitingTime (Head, cur));
 }
 // else, print error message
 else printf ("Error: order is not found.\nNo action is taken.\n");
}
