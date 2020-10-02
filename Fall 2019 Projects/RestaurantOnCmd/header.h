/* CS211 –Programming Practicum
 * Programming Project 4: 
 * Fast Food Order Management
 * Description: this program "implements a food ordering 
 * system used in a fast food restaurant. This restaurant 
 * only serves burgers and salads and when people want to 
 * order food, they give their name and food choices to the 
 * cashier and then wait until those in front of them have 
 * been served."
*/

/* Author: Truong Nguyen Huy
 * UIN: 655471929
 * NetID: thuyng2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*--------------------------------------------------------------------------
 * enum definition */
typedef enum {FALSE = 0, TRUE, NO = 0, YES} boolean;

/*--------------------------------------------------------------------------
 * global variable for debug mode */
int debugMode;

/*--------------------------------------------------------------------------
 * queue definition */
typedef struct QueueNodeStruct
{
	char* Name; /* order's name */
	int numBurg; /* number of burgers ordered */
	int numSalad; /* number of salad ordered */
	boolean IRS; /* in-restaurant status */
	struct QueueNodeStruct* Next;
} NODE;

/*--------------------------------------------------------------------------
 * user interface functions */
int main (int argc, char **argv);
void clearToEoln ();
int getNextNWSChar ();
int getPosInt ();
char *getName ();
void printCommands ();

/*--------------------------------------------------------------------------
 * doXXXX() functions */
void doAdd (NODE** Head);
void doCallAhead (NODE** Head);
void doWaiting (NODE* cur);
void doRetrieve (NODE** Head);
void doList (NODE* Head);
void doDisplay (NODE* Head);
void doEstimateTime (NODE* Head);

/*--------------------------------------------------------------------------
 * queue implementation functions */
int lenQueue (NODE* cur);
void displayOrderInfo (NODE* cur);
void addToList (NODE** Head, char* name, int numburg, int numsalad, boolean irs);
boolean doesNameExist (NODE* cur, char* name);
boolean updateStatus (NODE* cur, char* name);
char* retrieveAndRemove (NODE* prev);
int countOrdersAhead (NODE* Head, NODE* cur);
void displayOrdersAhead (NODE* Head, NODE* cur);
void displayListInformation (NODE* Head);
int displayWaitingTime (NODE* Head, NODE* cur);
