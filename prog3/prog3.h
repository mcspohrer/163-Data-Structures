//Matthew Spohrer
//PSU ID 958566579
//CS163 prog3

//header file to program 3
#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>

const int SIZE =1201;

//struct to handle all the new data to be entered.
struct info
{
	info();
	~info();
	char * topic_name;
	char * website;
	char * summary;
	char * review;
	int rating;
	int copy(info &); //copies the info over
};
	
//node to store the website data in
struct hnode
{
	info data;
	hnode * next;
};

//class to manage the hash table
class table
{
	public:
		table(int size = 521);
		~table();
		int insert(info &);
		int display_all(); //displays all the data, unsorted, of all the nodes, returning 2 if there is no data to display 
		int display_topic(hnode * temp, char * topic);//recursively displays the node's data if the topics match
		int display_topic(char * topic);//wrapper that calls on the display_topic member function
		int edit(info &);//receives the websote to be edited, gets the index of where the website is located then passes that to the function that will edit, returns 5 if website couldn't be found
		int edit(info &, hnode *);//receives the website info to change, finds the website in the index passed to it, then edits the node's info to match the new review and rating
		int remove();//wrapper to call the member function that removes all the websites with a rating of 1
		int remove(hnode **);//goes through each index of the hash table and deletes anything with a rating below 1;
		int remove(hnode *&);//recursively traverses the LLL of the index of the array, removing any website with a rating of 1.
		bool retrieve(char * topic, info *& matches, int & num);//retieves the nodes with the sought after topic name, returns true if successful, false if unsuccessful
		bool find_match(char * topic, info *& matches, int & num);//finds any matches and stores them in the array, returns 0 if no matches
		void undo();
	private:
		hnode ** hash_table; //dynamically allocated array of head pointers.

		int hash_size;
		int hash_function(char *);
		
};

bool retrieve(char *, info *&, int &, table &); //wrapper function that gets the number of websites and the topic of the websites sought after.
int display_topic(table &); //gets the size of the array to hold the websites and the topic name to be searched for from the client then callls the 
int get_choice(); //asks the client what they would like to do with the program
int delegator(table &, int); //once the choice is inputted from the client, this function will delegateto the corresponding member functions.
int read(table & );//reads in all the data stored in the external data file;
int get_new(table &);//gets data for a new website and sends it to the class member function.
int get_size(table &);// gets the size of the hash table from the user and sends it to the table class.
int read(table &); //read in the data from the external data file and stores it into the hash table
int edit(table &);//gets the new rating and review for a specific website with a specific topic name from the user
void undo(table &); //deletes hash table

