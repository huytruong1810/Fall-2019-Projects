#include "header.h"

int debugMode = FALSE;

// prints the commands
void printCommands()
{
 printf ("The commands for this program are:\n\n");
 printf ("q - to quit the program\n");
 printf ("? - to list the accepted commands\n");
 printf ("or any infix mathematical expression using operators of (), *, /, +, -\n");
}

// retrieves the values from inputted stacks
// evaluates the expression then updates the Values stack
void PopAndEval (MyStack& Values, MyStack& Operators)
{
	Token result;
	// get the operator from top of Operators stack
	char op = Operators.top().getOperator();
	Operators.pop();  // pop it off
	if (Values.isEmpty())
		return;
	// get the first value from top of Values stack
	int x = Values.top().getValue();
	Values.pop();  // pop it off
	if (Values.isEmpty())
		return;
	// get the second value from top of Values stack
	int y = Values.top().getValue();
	Values.pop();  // pop it off
	
	// perform evaluation
	switch (op)  
	{  
		case '+':
			result.setToValue (y + x);
			break;  
		case '-':
			result.setToValue (y - x);
			break; 
		case '*':
			result.setToValue (y * x);
			break; 
		case '/':
			result.setToValue (y / x);
			break; 
		default:
		  printf ("***Invalid value***\n");
	}
	
	// push the result value onto Values stack
	Values.push (result);
}

// processes the inputted infix or postfix expression
void processExpression (Token inputToken, TokenReader *tr)
{
 /**********************************************/
 /* Declare both stack head pointers here      */
 MyStack Values, Operators; 
	
 /* Loop until the expression reaches its End */
 // While (the current token is not the EndOfLine Token)
 while (inputToken.equalsType(EOLN) == false)
 {
	/* The expression contain a VALUE */
	if (inputToken.equalsType(VALUE))
	{
	 /* make this a debugMode statement */
	 if (debugMode)
	  printf ("Val: %d, ", inputToken.getValue());

	 // add code to perform this operation here
	 Values.push (inputToken);
	}

	/* The expression contains an OPERATOR */
	else if (inputToken.equalsType(OPERATOR))
	{
	 /* make this a debugMode statement */
	 if (debugMode)
	  printf ("OP: %c, ", inputToken.getOperator());

	 // add code to perform this operation here
	 switch (inputToken.getOperator())
	 {
		// if the current operator is an Open Parenthesis
		case '(':
		 // push the Open Parenthesis onto the Operators stack
		 Operators.push (inputToken);
		 break;
		// if the current operator is + or -
		case '+':
		case '-':
			// while the Operators stack is not empty 
			// and the top of the Operators stack is +, -, * or /
			while (!Operators.isEmpty() && 
						 (Operators.top().getOperator() == '+' ||
							Operators.top().getOperator() == '-' ||
							Operators.top().getOperator() == '*' ||
							Operators.top().getOperator() == '/'))
			 PopAndEval (Values, Operators); // evaluate the expressions
			// push the current operator on the Operators stack
			Operators.push (inputToken);
			break;
		 // if the current operator is * or /
		 case '*':
		 case '/':
			// while the Operators stack is not empty
			// and the top of the Operators stack is * or /
			while (!Operators.isEmpty() &&
						 (Operators.top().getOperator() == '*' ||
							Operators.top().getOperator() == '/'))
			  PopAndEval (Values, Operators); // evaluate the expressions
			// push the current operator on the Operators stack
		  Operators.push (inputToken);
			break;
		 // if the current operator is a Closing Parenthesis
		 case ')':
			// while the Operators stack is not empty
			// and the top of the Operators stack is not an Open Parenthesis
			while (!Operators.isEmpty() &&
							Operators.top().getOperator() != '(')
				PopAndEval (Values, Operators); // evaluate the expressions
			// if the Operators stack is empty
			if (Operators.isEmpty())
				printf ("Error\n"); // print an error message
			// else, pop the Open Parenthesis from the Operators stack
			else
				Operators.pop();
			break;
		 default:
		  printf ("***Invalid input***\n");
	 }
	}

	/* get next token from input */
	inputToken = tr->getNextToken ();
 }
 /* The expression has reached its end */

 // add code to perform this operation here
 // while the Operators stack is not empty
 while (!Operators.isEmpty())
	 PopAndEval (Values, Operators); // keep evaluate the expressions

 // print out the final value on the Values stack
 printf ("\nThe top value of the stack at the result of the expresion: %d", Values.top().getValue());
	
 Values.pop(); // pop it off
 // if that value is not the final one, print error message
 if (!Values.isEmpty())
		printf("\nError: unknown expression.\n");
 
 // clean the stacks
 Values.reset();
 Operators.reset();
	
 printf ("\n");
}

// main
int main(int argc, char *argv[])
{
    /***************************************************************/
    /* Add code for checking command line arguments for debug mode */
		if (argc > 1)
		{
			if (strcmp(argv[1], "-d") == 0) 
			{
				debugMode = TRUE; // turn on debugMode
				printf ("Debug mode is turned on.\n");
			}
		}

    Token inputToken;
    TokenReader tr;

    printf ("Starting Expression Evaluation Program\n\n");
    printf ("Enter Expression: ");


    inputToken = tr.getNextToken ();

    while (inputToken.equalsType(QUIT) == false)
    {
      /* check first Token on Line of input */
      if(inputToken.equalsType(HELP))
      {
       printCommands();
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(ERROR))
      {
       printf ("Invalid Input - For a list of valid commands, type ?\n");
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(EOLN))
      {
       printf ("Blank Line - Do Nothing\n");
       /* blank line - do nothing */
      }
      else
      {
       processExpression(inputToken, &tr);
      }

      printf ("\nEnter Expression: ");
      inputToken = tr.getNextToken ();
    }

  printf ("Quitting Program\n");
  return 1;
}