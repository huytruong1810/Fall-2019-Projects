/* CS211 –Programming Practicum
 * Programming Project 3: 
 * Maze Solving
 * Description: this program produces a path (if possible)
 * through a 2D maze using the depth-first search algorithm. 
 * This program takes input from a file where the filename 
 * should be given in the command line arguments.
*/

/* Author: Truong Nguyen Huy
 * UIN: 655471929
 * NetID: thuyng2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE   1
#define FALSE  0

/* global variable for debug mode */
int debugMode;

/* --------------------------------------------------------------------------
 * Stack definition */
typedef struct StackNodeStruct
{
	int x, y;
	int r, l, u, d;
	struct StackNodeStruct* next;
} NODE;

/* return 1 if stack is empty and 0 if otherwise */
int empty (NODE* hd)
{
	if (hd == NULL) return 1;
	return 0;
}

/* initialize a new stack node and return it*/
NODE* init (int X, int Y)
{
	NODE* newNode = (NODE*) malloc (sizeof(NODE)); 
        newNode->x = X; 
        newNode->y = Y; 
	newNode->next = NULL;
        return newNode; 
}

/* push a new node onto stack */
void push (NODE** hd, int X, int Y)
{
	NODE* temp = init (X, Y);
	if (!empty (*hd)) temp->next = *hd;
	*hd = temp;
	if (debugMode) printf ("(%d, %d) is pushed.\n", X, Y);
}

/* return the top x value in stack */
int top_x (NODE* hd)
{
	if (empty (hd)) exit(0);
	return hd->x;
}

/* return the top y value in stack */
int top_y (NODE* hd)
{
	if (empty (hd)) exit(0);
	return hd->y;
}

/* pop off the top node of the stack */
void pop (NODE** hd)
{
	if (empty (*hd)) exit(0);
	NODE* temp = *hd;
	if (debugMode) printf ("(%d, %d) is popped.\n", top_x (*hd), top_y (*hd));
	*hd = temp->next;
	free (temp);
}

/* clear the whole stack */
void reset (NODE** hd)
{
	while (!empty (*hd))
		pop (hd);
}

/* print the nodes in stack in reverse order */
void displayReverse (NODE* cur)
{
	if (cur == NULL) return;
	displayReverse (cur->next);
	printf ("(%d, %d) ", top_x (cur), top_y (cur));
}

/* --------------------------------------------------------------------------
 * Maze definition */
typedef struct mazeStruct
{
	char** arr;  /* allows for a maze of size 30x30 plus outer walls */
	int xsize, ysize;
	int xstart, ystart;
	int xend, yend;
} maze;

/* --------------------------------------------------------------------------
 * main */
int main (int argc, char **argv)
{
	maze m1, visit; /* visit is a mirror maze of m1 */
	int xpos, ypos;
	int i, j, x, y, readSuccess, found;

	FILE *src;
	
	/* set debug mode to off */
	debugMode = FALSE;
	for (i = 0 ; i < argc ; ++i) 
	{
		/* if "-d" argument is met then turn on debug mode */
		if ( strcmp (argv[i], "-d") == 0 ) {
			debugMode = TRUE;
			printf ("Debug mode is on.\n");
			break;
		}
	}
	
	/* check for valid argument input and try to open the input file. */
	if (argc > 3) /* if there are more than 3 arguments */
	{
		printf ("Too many given file names or more than 1 debug argument.\n");
		exit (-1);
	}
	else if (argc == 3) /* if there are 3 argument */
	{
		if (!debugMode) /* if not in debug mode */
		{
			printf ("Too many given file names.\n");
			exit (-1);
		}
		else /* else if in debug mode */
		{
			/* if 2nd argument is debug trigger */
			if (strcmp (argv[1], "-d") == 0)
				/* then 3rd one whould be file name */
				src = fopen (argv[2], "r");
			/* if not then 1st one is file name */
			else src = fopen (argv[1], "r");
		}
	}
	else if (argc == 2) /* if there are 2 argument */
	{
		if (debugMode) /* if in debug mode */
		{
			printf ("No file name is found.\n");
			exit (-1);
		}
		/* if not in debug mode then file name is given at 1st argument */
		else src = fopen (argv[1], "r");
	}
	else
	{
		printf ("Usage: %s <input file name>\n", argv[0]);
		exit (-1);
	}
	
	/* read in the size, starting and ending positions in the maze */
	readSuccess = 0; /* turn off trigger for successful readings */ 
	/* maze's size reading */
	while (fscanf (src, "%d %d", &m1.xsize, &m1.ysize) != EOF)
	{
		/* if size is smaller than 1 */
		if (m1.xsize < 1 || m1.ysize < 1)
		{
			printf ("STANDARD ERROR\n=> Invalid: Maze sizes must be greater than 0\n");
			/* test next input */
			continue;
		}
		/* else, finish this reading and go to next one */
		break;
	}
	/* start coordinate reading */
	while (fscanf (src, "%d %d", &m1.xstart, &m1.ystart) != EOF)
	{
		/* if start coordinate is out of valid range */
		if (m1.xstart < 1 || m1.xstart > m1.xsize)
		{
			printf ("STANDARD ERROR\n=> Invalid: row %d is outside range from %d to %d\n", m1.xstart, 1, m1.xsize);
			/* test next input */
			continue;
		}
		if (m1.ystart < 1 || m1.ystart > m1.ysize)
		{
			printf ("STANDARD ERROR\n=> Invalid: column %d is outside range from %d to %d\n", m1.ystart, 1, m1.ysize);
			/* test next input */
			continue;
		}
		/* else, finish this reading and go to next one */
		break;
	}
	/* last reading - end coordinate reading */
	while (fscanf (src, "%d %d", &m1.xend, &m1.yend) != EOF)
	{
		/* if end coordinate is out of valid range */
		if (m1.xend < 1 || m1.xend > m1.xsize)
		{
			printf ("STANDARD ERROR\n=> Invalid: row %d is outside range from %d to %d\n", m1.xend, 1, m1.xsize);
			/* test next input */
			continue;
		}
		if (m1.yend < 1 || m1.yend > m1.ysize)
		{
			printf ("STANDARD ERROR\n=> Invalid: column %d is outside range from %d to %d\n", m1.yend, 1, m1.xsize);
			/* test next input */
			continue;
		}
		/* else, all readings are successful
		 * so turn on trigger */
		readSuccess = 1;
		/* finish this reading */
		break;
	}
	/* if file ends before getting 3 valid lines of input */
	if (!readSuccess)
	{
		printf ("STANDARD ERROR\nQuitting the program...\n");
		exit (-1);
	}
	/* else, all readings are done successfully
	 * so print them out to verify each input */
	printf ("size: %d, %d\n", m1.xsize, m1.ysize);
	printf ("start: %d, %d\n", m1.xstart, m1.ystart);
	printf ("end: %d, %d\n", m1.xend, m1.yend);
	
	/* let size of mirroring maze equal to that of the original one */
	visit.xsize = m1.xsize;
	visit.ysize = m1.ysize;
	
	/* allocate memory for the dynamic 2-D array mazes */
	m1.arr = (char**) malloc ((m1.xsize + 2) * sizeof (char*));
	visit.arr = (char**) malloc ((m1.xsize + 2) * sizeof(char*));
	for (i = 0; i < (m1.xsize + 2); ++i)
	{
		m1.arr[i] = (char*) malloc ((m1.ysize + 2) * sizeof(char));
		visit.arr[i] = (char*) malloc ((m1.ysize + 2) * sizeof(char));
	}
	
	/* initialize the maze to empty 
	 * and visit maze to unvisited */
	for (i = 0; i < m1.xsize+2; i++)
	 for (j = 0; j < m1.ysize+2; j++)
	 {
		 m1.arr[i][j] = '.';
		 visit.arr[i][j] = 'u';
	 }

	/* mark the borders of the maze with *'s */
	for (i=0; i < m1.xsize+2; i++)
	{
		m1.arr[i][0] = '*';
		m1.arr[i][m1.ysize+1] = '*';
	}
	for (i=0; i < m1.ysize+2; i++)
	{
		m1.arr[0][i] = '*';
		m1.arr[m1.xsize+1][i] = '*';
	}

	/* mark the starting and ending positions in the maze */
	m1.arr[m1.xstart][m1.ystart] = 's';
	m1.arr[m1.xend][m1.yend] = 'e';

	/* check if the blocked positions are valid and 
	 * mark them in the maze with *'s */
	while (fscanf (src, "%d %d", &xpos, &ypos) != EOF)
	{
		/* if the bloked coordinate block the start or end postions */
		if (xpos == m1.xstart && ypos == m1.ystart)
		{
			printf ("STANDARD ERROR\n=> Invalid: attempting to block starting position\n");
			/* test next input */
			continue;
		}
		if (xpos == m1.xend && ypos == m1.yend)
		{
			printf ("STANDARD ERROR\n=> Invalid: attempting to block ending position\n");
			/* test next input */
			continue;
		}
		
		/* if the blocked coordinate is out of valid range */
		if (xpos < 1 || xpos > m1.xsize)
		{
			printf ("STANDARD ERROR\n=> Invalid: row %d is outside range from %d to %d \n", xpos, 1, m1.xsize);
			/* test next input */
			continue;
		}
		if (ypos < 1 || ypos > m1.ysize)
		{
			printf ("STANDARD ERROR\n=> Invalid: column %d is outside range from %d to %d \n", ypos, 1, m1.ysize);
			/* test next input */
			continue;
		}
		
		/* else if them are valid, mark them in the maze */
		m1.arr[ xpos][ ypos] = '*';
	}


	/* print out the initial maze */
	for (i = 0; i < m1.xsize+2; i++)
	{
		for (j = 0; j < m1.ysize+2; j++)
			printf ("%c", m1.arr[i][j]);
	 	printf("\n");
	}
	
	NODE* Path;
	/* push the start position onto path */
	Path = init (m1.xstart, m1.ystart);
	/* mark start position as visited */
	visit.arr[m1.xstart][m1.ystart] = 'v';
	
	found = 0; /* set found to 0 (false) */
	/* loop through the path stack until it is empty */
	while (!empty (Path))
	{
		/* if the end coordinate is visited */
		if (visit.arr[m1.xend][m1.yend] == 'v')
		{
			found = 1; /* set found to 1 (true) */
			break; /* break out of loop */
		}
		
		/* get the coordinate on top of path stack */
		x = top_x (Path);
		y = top_y (Path);
		/* check right neighbor */
		if (visit.arr[x + 1][y] != 'v' && m1.arr[x + 1][y] != '*' )
		{
			push (&Path, x + 1, y);
			visit.arr[x + 1][y] = 'v';
			continue;
		}
		/* check left neighbor */
		if (visit.arr[x - 1][y] != 'v' && m1.arr[x - 1][y] != '*' )
		{
			push (&Path, x - 1, y);
			visit.arr[x - 1][y] = 'v';
			continue;
		}
		/* check above neighbor */
		if (visit.arr[x][y - 1] != 'v' && m1.arr[x][y - 1] != '*' )
		{
			push (&Path, x, y - 1);
			visit.arr[x][y - 1] = 'v';
			continue;
		}
		/* check below neighbor */
		if (visit.arr[x][y + 1] != 'v' && m1.arr[x][y + 1] != '*' )
		{
			push (&Path, x, y + 1);
			visit.arr[x][y + 1] = 'v';
			continue;
		}
		
		/* if all neighbors are invalid to move to
		 * then pop that coordinate off */
		pop (&Path);
	} /* end of while loop */
	
	printf ("\n");
	if (!found) /* if a solution is found */
		printf ("The maze has no solution.\n");
	else
	{
		printf ("End is reached with the path: \n");
		/* display the path */
		displayReverse (Path);
	}
	printf ("\n");
	
	/* deallocate the dynamic 2-D array mazes */
	for (i = 0; i < (m1.xsize + 2); ++i)
	{
		free (m1.arr[i]);
		free (visit.arr[i]);
	}
	free (m1.arr);
	free (visit.arr);
	
	/* turn off debug mode before clearing the stack */
	debugMode = FALSE;
	reset (&Path);

	fclose (src);
}