/* CS 211, Programming Project 1 */
/* Name: Truong Nguyen Huy */
/* NetID: thuyng2 */
/* UIN: 655471929 */

#include <stdio.h>
#include <stdlib.h>

/* make copy of an array */
void makeArrayCopy (int fromArray[], int toArray[], int size)
{
 int i;
 for (i = 0 ; i < size; i++)
 {
  toArray[i] = fromArray[i];
 }
}

/* sort the array in ascending order */
void myFavoriteSort (int arr[], int size)
{
 int i, j;
 for (i = 0; i < size - 1; i++)
 {
  for (j = 0; j < size - i - 1; j++)
  {
   /* if value is larger than the next one */
   if (arr[j] > arr[j+1])
   {
    /* then swap the two values */
    int temp = arr[j];
    arr[j] = arr[j+1];
    arr[j+1] = temp;
   }
  }
 }
}

/* return two value whose sum is equal to target value */
int TwoSumFunction (int arr[], int size, int target, int *index1, int *index2)
{
 int low = 0;
 int high = size - 1;
 int sum;
	
 /* loop until the pointers are at the same place */
 while (low != high)
 {
  sum = arr[low] + arr[high];
  
  /* if sum is smaller than target, shift low to the right */
  if (sum < target) low++;
  /* if sum is larger than target, shift high to the left */
  else if (sum > target) high--;
  /* if sum is equal to target, return 1 and the pointers */
  else
  {
   *index1 = low;
   *index2 = high;
   return 1;
  }
 }
	
 return -1;
}

/* main function */
int main (int argc, char** argv)
{
 int index1, index2, val, size, i = 0;
 int *darr;
 int *darr2;
 int allocated = 100;
 darr = (int *) malloc (allocated * sizeof(int));
	
 /* prompt the user for input */
 printf ("Enter in a list of numbers ito be stored in a dynamic array.\n");
 printf ("End the list with the terminal value of -999\n");
 /* loop until the user enters -999 */
 scanf ("%d", &val);
 while (val != -999)
   {
    darr[i] = val;
    i++;
    
    /* if array size exceed allocated value */
    if (i == (allocated - 1))
    {
     int *temp = darr;
     /* double the size */
     allocated *= 2;
     /* remake the array darr */
     darr = (int *) malloc (allocated * sizeof(int));
     /* tranfer data over */
     makeArrayCopy (temp, darr, allocated);
     /* free up temp */
     free (temp);
    }
    /* get next value */
    scanf ("%d", &val);
   }

 /* preparation for the second loop */
 size = i;	
 darr2 = (int *) malloc (allocated * sizeof(int));

 /* call function to make a copy of the array of values */
 makeArrayCopy (darr, darr2, allocated);
 /* call function to sort one of the arrays */
 myFavoriteSort (darr2, size);
	
 /* loop until the user enters -999 */
 printf ("Enter in a list of numbers to use for searching.  \n");
 printf ("End the list with a terminal value of -999\n");
 scanf ("%d", &val);
 while (val != -999)
 {
  /* call function to perform target sum operation */
  int result = TwoSumFunction (darr2, size, val, &index1, &index2);
  /* print out info about the target sum results  */
  if (result == 1)
  {
   printf ("Positions of the two values that sum up to be %d are: %d and %d.\n", val, index1, index2);
  }
  else printf ("No positions are found.\n");
  /* get next value */
  scanf ("%d", &val);
 }

 /* print Good bye and end the program */
 printf ("Good bye\n");
 return 0;
}


