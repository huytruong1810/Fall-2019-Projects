#include "header.h"

/* -----------------------------------------------------------------------------------
 * Island public member functions */

// default constructor
Island::Island()
{
	visited = false;
}

// clear the adjacency list of the island
void Island::clearAdjList()
{
	adjList.clear();
}

// set the visited status of the island
void Island::setStatus (bool status)
{
  visited = status;
}

// inserts an edge to the adjacency list
void Island::insertEdgeTo (int val)
{
	adjList.insertValue (val);
}

// deletes an edge from the adjacency list
void Island::deleteEdgeTo (int val)
{
	adjList.deleteValue (val);
}

// returns the island's status
// (visited or not)
bool Island::getStatus()
{
	return visited;
}

// returns the list of adjacent
// islands to this island
MyList Island::getAdjList()
{
	return adjList;
}