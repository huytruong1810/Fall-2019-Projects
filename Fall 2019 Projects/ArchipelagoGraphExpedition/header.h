/* CS211 –Programming Practicum
 * Programming Project 6:
 * "This program represents an archipelago expedition.  
 * This expedition will use an array of linked lists as 
 * its primary storage structure. This type of storage 
 * structure is typically called an “adjacency list”.
 * 
 * Welcome to the paradise! You have traveled to a beautiful archipelagoin 
 * the Pacific Ocean and you are planning your great expedition. 
 * These group of remote islands are accessible with ferry rides.  
 * Each island has a unique number. If there’s a ferry ride from 
 * Island X to Island Y, the network depicting the archipelago will 
 * have an “edge” from X to Y."
*/

/* Author: Truong Nguyen Huy
 * UIN: 655471929
 * NetID: thuyng2
*/

#include <cstdio>
#include <cstring>
#include <cstdlib>
#define TRUE 1
#define FALSE 0

/* -----------------------------------------------------------------------------------
 * MyNode class definition */
class MyNode
{
	private:
		int num;
		MyNode* next;
	
	public:
		MyNode();
		void setNum (int val);
		void setNext (MyNode* ptr);
		int getNum();
		MyNode* getNext();
};

/* -----------------------------------------------------------------------------------
 * MyList class definition */
class MyList
{
	private:
		MyNode* head;
	
	public:
		MyList();
		void insertValue (int val);
		void deleteValue (int val);
		int getNumberOfCurrentsValues();
		int getNthValue (int N);
		void list();
		void pop();
		void clear();
		bool nodeExist (int val);
};

/* -----------------------------------------------------------------------------------
 * FNODE class definition */
class FNODE
{
	private:
		char* name;
		FNODE* next;
	
	public:
		FNODE();
		void setName (char* str);
		void setNext (FNODE* ptr);
		char* getName();
		FNODE* getNext();
};

/* -----------------------------------------------------------------------------------
 * FList class definition */
class FList
{
	private:
		FNODE* head;
	
	public:
		FList();
		virtual ~FList();
		void pop();
		void clear();
		void insertFile (char* str);
		void deleteFile (char* str);
		bool fileExist (char* str);
};

/* -----------------------------------------------------------------------------------
 * Island class definition */
class Island
{
	private:
		bool visited;
		MyList adjList;
	
	public:
		Island();
		void clearAdjList();
		void setStatus (bool status);
		void insertEdgeTo (int val);
		void deleteEdgeTo (int val);
		bool getStatus();
		MyList getAdjList();
};

/* -----------------------------------------------------------------------------------
 * main */
int main (int argc, char** argv);