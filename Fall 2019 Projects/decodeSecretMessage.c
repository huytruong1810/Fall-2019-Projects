/* Name: Truong Nguyen Huy
* UIN: 655471929
* netID: thuyng2
* Project 2: Decoding a Secret Message
*/

/* This program reads in an encrypted message 
* and outputs the decoded message based
* on an alphabet and a dummy alphabet
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TRUE 1
#define FALSE 0

int DebugMode;

/* stack definition */
typedef struct { 
  int top; 
  int capacity; 
  char* array; 
} Stack; 

/* initialize a stack */
Stack* init ( int Cap) 
{ 
  if ( DebugMode) printf ("Initializing a stack...\n");

  Stack* stack = ( Stack*) malloc ( sizeof( Stack)); 
  stack->capacity = Cap; 
  stack->top = -1; 
  stack->array = ( char*) malloc ( stack->capacity * sizeof( char));

  if ( DebugMode) printf ("Done.\n");
  return stack; 
} 

/* check if stack is full */ 
bool is_full ( Stack* stack) 
{ 
  if ( stack->top == stack->capacity - 1) return true;
  return false;
} 

/* check if stack is empty */
bool is_empty ( Stack* stack) 
{ 
  /* if the top of the stack is -1, then stack is empty */
  if ( stack->top == -1) return true;
  /* else it is not */
  return false;
} 

/* return the top item in stack */ 
int top ( Stack* stack) 
{
  if ( is_empty( stack)) return 0;
  return stack->array[ stack->top]; 
} 

/* remove the top item from stack */ 
int pop ( Stack* stack) 
{
  if ( is_empty( stack)) 
  {
    if ( DebugMode) printf ("Stack is empty. Exiting pop...\n");
    return 0;
  }
  else 
  {
    if ( DebugMode) printf ("%c is popped.\n", stack->array[ stack->top]);
    return stack->array[ stack->top--];
  } 
} 

/* remove all items in the stack */
void clear ( Stack* stack)
{
  if ( DebugMode) printf ("Clearing stack...\n");

  /* while stack is not empty */
  while ( !( is_empty ( stack)))
  {
    /* keep on poping off the items */
    pop ( stack);
  }

  if ( DebugMode) printf ("Cleared.\n");
}

/* call push function to be used in transferStackData function */
void push ( Stack* stack, char ch);

/* transfer items from one stack to another */
void transferStackData ( Stack* fromStack, Stack* toStack)
{
  /* while fromStack is not empty */
  while ( !( is_empty ( fromStack)))
  {
    /* keep on transferring items over to toStack */
    if ( DebugMode) printf ("Pushing %c in source stack onto destination stack...\n", top ( fromStack));
    push ( toStack, top ( fromStack));
    /* and popping each item off */
    if ( DebugMode) printf ("Popping %c in source stack...\n", top ( fromStack));
    pop ( fromStack);
  }
}

/* grow the stack capacity */
void grow ( Stack* stack, char ch)
{
  int keep;
  if ( DebugMode)
  {
    printf ("--Growing stack...\n");
    printf ("The old size of stack is: %d.\n", stack->capacity);
    keep = stack->capacity;
  }

  /* initialize a temporary stack */
  Stack* tempStack = init ( stack->capacity);
  /* transfer the items from stack to the temporary one */
  printf ("-Transferring items from stack to temporary...\n");
  transferStackData ( stack, tempStack);
  /* change stack capacity */
  stack = init ( stack->capacity + 4);
  /* move items back */
  printf ("-Transferring items from temporary back to stack...\n");
  transferStackData ( tempStack, stack);

  /* remove the temporary stack */
  free ( tempStack);

  if ( DebugMode)
  {
    printf ("The new size of stack is: %d.\n", stack->capacity);
    printf ("Number of element copied is: %d.\n", keep);
    printf ("--Done.\n");
  }
}

/* push a character onto stack */ 
void push ( Stack* stack, char ch) 
{
  /* if the stack is full, grow its capacity and push the character onto it */
  if ( is_full ( stack)) grow ( stack, ch);
  /* else, just push the character onto the stack */
  stack->array[ ++stack->top] = ch;

  if ( DebugMode) printf ("%c is added.\n", ch);
} 

/* check if the string is meaningful */
bool checkValid ( char* str, Stack* stack)
{
  if ( DebugMode) printf ("----Checking meaningful string...\n");

  int i, j;
  int inAlphabet = 0;
  int inDummyAlphabet = 0;
  char curr;
  char alphabet[ 4] = {'a', 'b', 'c', 'd'};
  char dummyAlphabet[ 4] = {'m', 'n', 'o', 'p'};

  /* loop through the string */
  for ( i = 0; i < strlen( str); ++i)
  {
    /* let curr hold individual characters in the string */
    curr = str[ i];
    /* if the character matches any letter in the alphabet */
    if ( curr == 'a' || curr == 'b' || curr == 'c' || curr == 'd')
    {
      /* push it onto stack */
      push ( stack, curr);
    }

    /* loop through the dummy alphabet */
    for ( j = 0; j < 4; ++j)
    {
      /* if the character matches any letter in the dummy alphabet */
      if ( ( curr == dummyAlphabet[ j]) && ( !is_empty( stack)) && ( top ( stack) == alphabet[ j]))
        {
          /* pop the top off of stack */
          pop ( stack);
        }
      else if ( ( curr == dummyAlphabet[ j]) && ( !is_empty( stack)) && ( top( stack) != alphabet[ j])) return false;
    }
  }

  if ( DebugMode) printf ("----Done.\n");
  /* if stack is empty, return true */
  if ( is_empty( stack)) return true;
  /* else return false */
  return false;
}

/* remove the extra letters in the string to obtain the decoded string*/
char* RemoveExtraLetter ( char* str)
{
  if ( DebugMode) printf ("----Removing extra letters...\n");

  char* resultStr;
  char* tempStr;
  resultStr = ( char*) malloc ( strlen( str) * sizeof( char));
  char curr;
  int i;

  /* loop through the string to add accepted character into the result string */
  for ( i = 0; i < strlen( str); ++i)
  {
    /* assign individual characters in the string */
    curr = str[ i];
    /* if the character matches any letter in the alphabet */
    if ( curr == 'a' || curr == 'b' || curr == 'c' || curr == 'd')
    {
      /* let a temporary string hold the result string */
      tempStr = ( char*) malloc ( strlen( resultStr) * sizeof( char));
      strcpy( tempStr, resultStr);
      /* add the accepted character at the end of temporary string */
      tempStr[ strlen( resultStr)] = curr;
      /* assign completed temporary string to the result string */
      resultStr = tempStr;
    }
  } 

  if ( DebugMode) printf ("----Done.\n");
  return resultStr;
}

/* main */
int main(int argc, char const *argv[])
{
  DebugMode = FALSE;
  int i;
  for ( i = 0; i < argc; ++i)
  {
    if ( strcmp ( argv[ i], "-d") == 0)
    {
      DebugMode = TRUE;
      printf ("\nDebug Mode is on.\n");
    }
  }

  char input[300];

  /* set up an infinite loop */
  while (1)
  {
    /* get line of input from standard input */
    printf ("\nEnter input to check or q to quit\n");
    fgets(input, 300, stdin);

    /* remove the newline character from the input */
    int i = 0;
    while (input[i] != '\n' && input[i] != '\0')
    {
      i++;
    }
    input[i] = '\0';

    /* check if user enter q or Q to quit program */
    if ( (strcmp (input, "q") == 0) || (strcmp (input, "Q") == 0) )
    break;

    printf ("\nMessage is: %s\n", input);

    /*Start tokenizing the input into words separated by space
    We use strtok() function from string.h*/
    /*The tokenized words are added to an array of words*/
    char delim[] = " ";
    char* ptr = strtok(input, delim);
    char* wordList[15];
    char* str;
    int size = 4;

    /* j will be used to store the size of wordList */
    int j = 0;

    /* store everything into wordList */
    while (ptr != NULL)
    {	
      wordList[j++] = ptr;
      ptr = strtok(NULL, delim);
    }

    char decodedMessage[ j];

    /*Run the algorithm to decode the message*/
    /*Loop through every word in the wordList*/
    for ( i = 0; i < j; ++i)
    {
      /* initialize a stack to be used in checkValid */
      Stack* stack;
      stack = init ( size);

      str = wordList[ i];

      /* check if the string is meaningful */
      if ( checkValid ( str, stack))
      {
        /* if it is, remove the extra letters */
        str = RemoveExtraLetter ( str);
        /* store the decoded string into decodedMessage */ 
        strcat( decodedMessage, str);
        strcat( decodedMessage, " ");
      }
    }

    printf ("\nDecoded message is: %s\n", decodedMessage);
  }

  printf ("\nGoodbye\n");
  return 0;
}