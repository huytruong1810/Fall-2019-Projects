#include "header.h"

/* -----------------------------------------------------------------------------------
 * ArchipelagoExpedition class definition */

class ArchipelagoExpedition
{
 private:
		Island* network;
		int size;
		FList fileList;
		
		// depth first search helper function
		void depthFirstSearchHelper (int x, int y)
		{
			// mark all islands as unvisited
			markUnvisit();
			if (dfs (x, y))
				printf ("You can get from island %d to island %d in one or more ferry rides.\n", x, y);
			else
				printf ("You can NOT get from island %d to island %d in one or more ferry rides.\n", x, y);
		}

		// depth first search function
		bool dfs (int a, int b)
		{
			// loop through the adjacency islands of island a
			MyList adjIslands = network[a - 1].getAdjList();
			for (int i = 0; i < adjIslands.getNumberOfCurrentsValues(); ++i)
			{
				int c = adjIslands.getNthValue (i);
				// if the island b is found, return true
				if (c == b)
					return TRUE;
				// else if not found, mark each island travel through as visited
				if (network[c - 1].getStatus() == FALSE)
				{
					network[c - 1].setStatus (TRUE);
					// recursive call of dfs
					if (dfs (c, b))
						return TRUE;
				}
			}
			// reach here means b is not reachable from a
			return FALSE;
		}
	
		// return the shortest path from x to y if 
		// y is reachable from x
		MyStack breadthFirstSearch (int x, int y)
		{
			// mark all islands as unvisited
			markUnvisit();
			
			// set all previous locations to -1
			int prevLocationList [size];
			for (int i = 0; i < size; ++i)
				prevLocationList[i] = -1;
			
			MyQueue IslandQueue;
			MyStack pathList;
			
			// push x into the queue
			IslandQueue.pushBack (x);
			
			// call bfs
			if (bfs (y, IslandQueue, prevLocationList))
			{
				printf ("You can get from island %d to island %d in one or more ferry rides.\n", x, y);
				int curIsland = y;
				pathList.pushFront (curIsland);
				// loop through all the island in previous list and save them in stack
				do
				{
					curIsland = prevLocationList[curIsland - 1];
					pathList.pushFront (curIsland);
				}
				while (curIsland != x);
			}
			else
				printf ("You can NOT get from island %d to island %d in one or more ferry rides.\n", x, y);
			
			// return the path list
			return pathList;
		}
	
		// breadth first search function
		bool bfs (int b, MyQueue IslandQueue, int* prevLocationList)
		{
			while (!IslandQueue.isEmpty())
			{
				// let island a be the island at front of queue
				int a = IslandQueue.getFront();
				IslandQueue.popFront();
				
				// loop through the adjacency islands of island a
				MyList adjIslands = network[a - 1].getAdjList();
				for (int i = 0; i < adjIslands.getNumberOfCurrentsValues(); ++i)
				{
					int c = adjIslands.getNthValue (i);
					// if an adjacency island is not visited
					if (network[c - 1].getStatus() == FALSE)
					{
						// mark is as visited
						network[c - 1].setStatus (TRUE);
						// set previous location of that island to island a
						prevLocationList[c - 1] = a;
						// if island b is found, return true
						if (c == b)
							return TRUE;
						// else, push that island into the queue
						IslandQueue.pushBack (c);
					}
				}
			}
			// reach here means b is not reachable
			return FALSE;
		}
  
 public:
		// Default constructor
		ArchipelagoExpedition()
		{
			size = 10;
			network = new Island[size];
		}

		// destructor
		virtual ~ArchipelagoExpedition()
		{
			for (int i = 0; i < size; ++i)
				network[i].clearAdjList();
			delete[] network;
		}

		// Mark all islands as unvisited
		void markUnvisit()
		{
			for (int i = 0; i < size; ++i)
				network[i].setStatus (false);
		}

		// The main loop for reading in input
		void processCommandLoop (FILE* inFile)
		{
			char  buffer[300];
			char* input;

			input = fgets ( buffer, 300, inFile );   // get a line of input

			// loop until all lines are read from the input
			while (input != NULL)
			{
				// process each line of input using the strtok functions 
				char* command;
				command = strtok (input , " \n\t");

				printf ("*%s*\n", command);

				if ( command == NULL )
					printf ("Blank Line\n");

				else if ( strcmp (command, "q") == 0) 
					return;

				else if ( strcmp (command, "?") == 0) 
					showCommands();

				else if ( strcmp (command, "s") == 0) 
					doShortestPath ();
				
				else if ( strcmp (command, "t") == 0) 
					doTravel ();

				else if ( strcmp (command, "r") == 0) 
					doResize ();

				else if ( strcmp (command, "i") == 0) 
					doInsert ();

				else if ( strcmp (command, "d") == 0) 
					doDelete ();

				else if ( strcmp (command, "l") == 0) 
					doList ();

				else if ( strcmp (command, "f") == 0) 
					doFile ();

				else if ( strcmp (command, "#") == 0) 
					;

				else
					printf ("Command is not known: %s\n", command);

				input = fgets ( buffer, 300, inFile );   // get the next line of input

			}
		}

		void showCommands()
		{
		 printf ("The commands for this project are:\n");
		 printf ("  q \n");
		 printf ("  ? \n");
		 printf ("  # \n");
		 printf ("  s <int1> <int2> \n");
		 printf ("  t <int1> <int2> \n");
		 printf ("  r <int> \n");
		 printf ("  i <int1> <int2> \n");
		 printf ("  d <int1> <int2> \n");
		 printf ("  l \n");
		 printf ("  f <filename> \n");
		}

		void doTravel ()
		{
		 int val1 = 0;
		 int val2 = 0;

		 // get an integer value from the input
		 char* next = strtok (NULL, " \n\t");
		 printf("%s\n", next);
		 if ( next == NULL )
		 {
			 printf ("Integer value expected\n");
			 return;
		 }
		 val1 = atoi ( next );
		 if ( val1 == 0 && strcmp (next, "0") != 0)
		 {
			 printf ("Integer value expected\n");
			 return;
		 }

		 // get another integer value from the input
		 next = strtok (NULL, " \n\t");

		 printf("%s\n", next);
		 if ( next == NULL )
		 {
			 printf ("Integer value expected\n");
			 return;
		 }
		 val2 = atoi ( next );
		 if ( val2 == 0 && strcmp (next, "0") != 0)
		 {
			 printf ("Integer value expected\n");
			 return;
		 }

		 /* check if val1 is within the array */
		 if (val1 > size || val1 - 1 < 0)
		 {
			 printf ("\tERROR: %d does not exist in our island network.\n", val1);
			 return;
		 }

		 /* check if val2 is within the array */
		 if (val2 - 1 > size || val2 - 1 < 0)
		 {
			 printf ("\tERROR: %d does not exist in our island network.\n", val2);
			 return;
		 }

		 printf ("Performing the Travel Command from %d to %d\n", 
							val1, val2);
		 depthFirstSearchHelper (val1, val2);
		}
	
		void doShortestPath ()
		{
		 int val1 = 0;
		 int val2 = 0;

		 // get an integer value from the input
		 char* next = strtok (NULL, " \n\t");
		 printf("%s\n", next);
		 if ( next == NULL )
		 {
			 printf ("Integer value expected\n");
			 return;
		 }
		 val1 = atoi ( next );
		 if ( val1 == 0 && strcmp (next, "0") != 0)
		 {
			 printf ("Integer value expected\n");
			 return;
		 }

		 // get another integer value from the input
		 next = strtok (NULL, " \n\t");

		 printf("%s\n", next);
		 if ( next == NULL )
		 {
			 printf ("Integer value expected\n");
			 return;
		 }
		 val2 = atoi ( next );
		 if ( val2 == 0 && strcmp (next, "0") != 0)
		 {
			 printf ("Integer value expected\n");
			 return;
		 }

		 /* check if val1 is within the array */
		 if (val1 > size || val1 - 1 < 0)
		 {
			 printf ("\tERROR: %d does not exist in our island network.\n", val1);
			 return;
		 }

		 /* check if val2 is within the array */
		 if (val2 - 1 > size || val2 - 1 < 0)
		 {
			 printf ("\tERROR: %d does not exist in our island network.\n", val2);
			 return;
		 }

		 printf ("Performing the Shortest Path Command from %d to %d\n", 
							val1, val2);
		 // get the path list from val1 to val2
		 MyStack pathList = breadthFirstSearch (val1, val2);
			
		 // if the path list is empty, break out of function
		 if (pathList.isEmpty())
			 return;
		 // else, display it
		 pathList.list();
		 printf ("\n");
		}

		void doResize ()
		{
		 int val1 = 0;

		 // get an integer value from the input
		 char* next = strtok (NULL, " \n\t");
		 printf("%s\n", next);
		 if ( next == NULL )
		 {
			 printf ("Integer value expected\n");
			 return;
		 }
		 val1 = atoi ( next );

		 // check if val1 is not greater than 0
		 if (val1 < 1)
		 {
			 printf ("\tERROR: Integer must be greater than 0.\n");
			 return;
		 }

		 printf ("Performing the Resize Command with %d\n", val1);

		 // empty all adjacency lists of all islands
		 for (int i = 0; i < size; ++i)
		 {
			 network[i].clearAdjList();
		 }
		 delete[] network;

		 // grow the network according to val1
		 size = val1;
		 network = new Island[size];
		}

		void doInsert ()
		{
		 int val1 = 0;
		 int val2 = 0;

		 // get an integer value from the input
		 char* next = strtok (NULL, " \n\t");
		 printf("%s\n", next);
		 if ( next == NULL )
		 {
			 printf ("Integer value expected\n");
			 return;
		 }
		 val1 = atoi ( next );
		 if ( val1 == 0 && strcmp (next, "0") != 0)
		 {
			 printf ("Integer value expected\n");
			 return;
		 }

		 // get another integer value from the input
		 next = strtok (NULL, " \n\t");

		 printf("%s\n", next);
		 if ( next == NULL )
		 {
			 printf ("Integer value expected\n");
			 return;
		 }
		 val2 = atoi ( next );
		 if ( val2 == 0 && strcmp (next, "0") != 0)
		 {
			 printf ("Integer value expected\n");
			 return;
		 }

		 /* check if val1 is within the array */
		 if (val1 > size || val1 - 1 < 0)
		 {
			 printf ("\tERROR: %d does not exist in our island network.\n", val1);
			 return;
		 }

		 /* check if val2 is within the array */
		 if (val2 - 1 > size || val2 - 1 < 0)
		 {
			 printf ("\tERROR: %d does not exist in our island network.\n", val2);
			 return;
		 }

		 /* check if val2 already exist in network */
		 if (network[val1 - 1].getAdjList().nodeExist (val2))
		 {
			 printf ("\tERROR: Edge from %d to %d already existed.\n", val1, val2);
			 return;
		 }

		 printf ("Performing the Insert Command from %d to %d\n", 
							val1, val2);
		 network[val1 - 1].insertEdgeTo (val2);
		}

		void doDelete ()
		{
		 int val1 = 0;
		 int val2 = 0;

		 // get an integer value from the input
		 char* next = strtok (NULL, " \n\t");
		 printf("%s\n", next);
		 if ( next == NULL )
		 {
			 printf ("Integer value expected\n");
			 return;
		 }
		 val1 = atoi ( next );
		 if ( val1 == 0 && strcmp (next, "0") != 0)
		 {
			 printf ("Integer value expected\n");
			 return;
		 }

		 // get another integer value from the input
		 next = strtok (NULL, " \n\t");

		 printf("%s\n", next);
		 if ( next == NULL )
		 {
			 printf ("Integer value expected\n");
			 return;
		 }
		 val2 = atoi ( next );
		 if ( val2 == 0 && strcmp (next, "0") != 0)
		 {
			 printf ("Integer value expected\n");
			 return;
		 }

		 /* check if val1 is within the array */
		 if(val1 > size || val1 - 1 < 0)
		 {
			 printf ("\tERROR: %d does not exist in our island network.\n", val1);
			 return;
		 }

		 /* check if val2 is within the array */
		 if(val2 - 1 > size || val2 - 1 < 0)
		 {
			 printf ("\tERROR: %d does not exist in our island network.\n", val2);
			 return;
		 }

		 printf ("Performing the Delete Command from %d to %d\n", 
							val1, val2);
		 network[val1 - 1].deleteEdgeTo (val2);
		}

		void doList ()
		{
		 for (int i = 0; i < size; ++i)
		 {
			 printf ("%d has an edge to ", i + 1);
			 network[i].getAdjList().list();
			 printf ("\n");
		 }
		}

		void doFile ()
		{
		 // get a filename from the input
		 char* fname = strtok (NULL, " \n\t");
		 if ( fname == NULL )
		 {
			 printf ("Filename expected\n");
			 return;
		 }

		 printf ("Performing the File command with file: %s\n", fname);

		 // next steps:  (if any step fails: print an error message and return ) 
		 //  1. verify the file name is not currently in use
		 //  2. open the file using fopen creating a new instance of FILE*
		 //  3. recursively call processCommandLoop() with this new instance of FILE* as the parameter
		 //  4. close the file when processCommandLoop() returns

		 if (fileList.fileExist (fname))
		 {
			 printf ("\t\n\nERROR: %s currently in use.\n\n", fname);
			 return;
		 }

		 fileList.insertFile (fname);
		 FILE* inFile = fopen (fname, "r");
		 if (inFile == NULL)
		 {
			 printf ("\tERROR: File does not exist");
			 return;
		 }
		 processCommandLoop (inFile);
		 fileList.deleteFile (fname);

		 fclose (inFile);
		}
};

/* -----------------------------------------------------------------------------------
 * main */
int main (int argc, char** argv)
{
  // set up the variable inFile to read from standard input
  FILE* inFile = stdin;

  // set up the data needed for the island adjcency list
  ArchipelagoExpedition islandData;
   
  // call the method that reads and parses the input
  islandData.showCommands();
  printf ("\nEnter commands at blank line\n");
  printf ("    (No prompts are given because of f command)\n");
  islandData.processCommandLoop (inFile);
	
	fclose (inFile);
	
  printf ("Goodbye\n");
  return 0;
}