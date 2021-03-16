//Matthew Spohrer
//PSU ID : 958566579
//Program 2 header

//this is the header file for program 2 which will store data in a queue and a stack and write to an external data file

#include <iostream>
#include <cstring>
#include <cctype>
#include <fstream>

const int SIZE = 151; //constant to read in from the user to be used with dynamically allocated arrays

	
//struct to help manage the data for the party 
struct party 
{ 
	party(); 
	~party(); 
	char * name; 
	int size; 
	char * special; 
	char promo; 
	char * email; 
};

//struct for the promotional stuff
struct info
{
	info();
	~info();
	char * name;
	char * email;
};

//struct for the node for the stack
struct s_node
{
	info * data;
	s_node * next;
};

//data node for the CLL 
struct node 
{ 
	party data; 
	node * next; 
}; 

//class that manages the stack to print out the last customers to come in and choose to receive promotional stuff
class stack
{
	public:
		stack();
		~stack();
		bool is_empty();// checks if the LLL of the stack is empty, returns true if it is, false if it isn't
		int push(info &);//pushes the data from the dequeue to the top of the stack.
		int initialize(int);//sets up the first node with an array if there is no LLL
		int display();//wrapper to call the display function to print recursively
		int display(s_node *);//displays all the people who have wanted to receive promotional stuff, return 0 if nothing to display
		int pop(); // pop member function, removes top stack, calls write function to write removes stack info to an external data file, returns 0 if no stack
		int peek(); //lists the top item of the stack, returning 0 is there is no stack
		int write(info &); //writes the info to an external data file
	private:
		s_node * head;	
		int top_index;
		int size;
};

//class that manages the queue
class queue
{
	public:
		queue();
		~queue();
		int enqueue(node *&, node *&); //inserts the newly entered name to the waitlist
		int enqueue(party &); //wrapper function that receives the newly entered data and calls the function to insert the data at the front of the queue
		int dequeue(stack &); //dequeues the oldest entry in the CLL, returns 0 if list is empty, 1 if empty after dequeue, 2 if successful
		int display(); //wrapper to call the display function
		int display(node *); //recursively displays all the names of the parties waiting to be sat and the number of parties to be sat
		int peek(); //takes a peek at the lead party, returns 1 if successful, 0 if noone is waiting
	private:
		node * rear;
	
};

int to_add(); //gets the info of the party to be added to the waitlist.
int get_choice(); //prompts the user to choose why they want to use the program. returns 1 to add to wait list, 2 to seat the first people on the wait list,3 to send out promotional stuff
int delegator(int user_choice, queue & waitlist, stack & s_promo); //delegates the program to do as the user chooses
