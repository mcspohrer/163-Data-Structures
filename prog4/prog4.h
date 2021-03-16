//Matthew Spohrer
//PSU ID 958566579
//CS163 prog4

#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>

const int SIZE = 250;

//struct to handle all the data
struct info
{
	info();
	~info();

	char * topic;
	char * keyword;
	char * URL;
	char * summary;
	char * review;
	int rating;

	int copy(info &);//allows for a deep copy of data
};

//struct for the BST node
struct node
{
	node();
	~node();
	info data;
	node * left;
	node * right;
};

//class to handle everything. keeps data private
class table
{
	public:
		table();
		~table();
		int add(info &);//inserts the new data into the BST, returns -1 if keyword already exists
		int display(); //wrapper to call the member function that displaye recursively
		int remove_key(char * key);//calls the remove function in the private section of the class
		int remove_topic(char *);//gets passed the topic then calls the private member funtion to remove, passing the topic name and root
		int retrieve(info &); //wrapper that calls the private member function that retrieves the specific website (for the remove single option)

	private:
		node * root;
		int display(node *); //recursively displays the BST.
		int add(node *&, info *);//recursively traverses the BST to and adds where it needs to
		int remove_topic(node *&, char *);//recursively traverses the BST, deleting nodes with matching topics along the way.
		int remove_node(node *&, char *);//calls the retrieve function and actually removes the appropriate node
		int remove_node_topic(node *& temp, char * key);//removes all the nodes with a matching topic
		int retrieve(node *&, info &); //compares key words and copies over if they match
};

int get_choice(); //asks the client what they would like to do then returns their choice as an integer
int get_new(table &);//gets the information from the client for the new website, calls on the member function add, returns the value passed to it from the member function
int get_key(table &);//gets the keyword to be removed
int read(table &);//reads in the data from the external data file
int get_topic(table &); //hhhgets the topic of the websites to be deleted form the uxlient. Passes them to the member function to delete
int display_one(table &);//displays a single node using the retrieve function
