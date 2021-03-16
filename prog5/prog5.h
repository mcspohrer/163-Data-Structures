/*Matthew Spohrer
PSU ID 958566579
CS163 PMW 5*/

#include <cctype>
#include <iostream>
#include <cstring>

const int SIZE = 201;

//struct for the vertex of the adjacency list for the graph
struct vertex
{
	vertex();
	~vertex();
	char * todo;
        struct node * head;
	bool vis;
	void remove_all(node *&);
};

//struct for the nodes that will hold the pointers in the adjacency list
struct node
{
	node();
	~node();
	vertex * adj;
	node * next;
};

//class to manage the graph
class table
{
	public:
		table();//constructor for the graph
		~table();//destructor for the node
		int add(); //adds a vertex to the adj list, returns -1 if vertex already exists and -2 if the adjacency list is full
		int display();//displays all the stuff to do
		int link();//adds edges to the edge list of a vertex
		int dft(); //wrapper to call the displaying depth first traversal
	private:
		vertex * adj_list;
		int list_size;
		int dft(vertex *);//function to display, using recursion and iteration
		int display(node *);//recursively displays the edge list
};

int get_choice();//determines what the client would like to do
