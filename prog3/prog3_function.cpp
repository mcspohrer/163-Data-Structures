//Matthew Spohrer
//PSUID 958566579
//CS163 prog3

//this file will contain all the functions for the hash table.
#include "prog3.h"
using namespace std;

//delegates to the client's choice
int delegator(table & hash_table, int choice) 
{
	int result = 0;


	return result;
}

//recursively traverses the array of the hash table, calling the function taht traverses the each index of the array, deleting the nodes with a rating of 1
int table::remove()
{
	int remove_suc = 0;

	for (int i=0; i < hash_size; ++i) {
		if (hash_table[i]) remove_suc = remove(hash_table[i]);
	}
		
	return remove_suc;
}

//gets the pointer to the first node of a particular index of the managing hash table array then recursively traverses the LLL of that index, deleting anyhting with a rating of 1 star or lower
int table::remove(hnode *& current)
{
	hnode * temp = NULL;

	if (current->data.rating == 1 && !current->next) {
		delete current;
		
		current = NULL;
		return 1;
	} else 	if (!current->next) return 0;

	temp = current->next;

	if (current->next->data.rating == 1 && temp && !temp->next) {
		delete current->next;
		current->next = NULL;
		return 1;
	} else if (current->next->data.rating == 1 && temp->next) {
		temp = temp->next;
		delete current->next;
		current->next = temp;
		return 1;
	}
	
	return remove(current->next);
}

//passed the url and topic of the website wanting to be changed, finds the website and edits the rating and review accordingly, returns 5 if can't find the website
int table::edit(info & to_edit)
{
	hnode ** index = (hash_table + hash_function(to_edit.topic_name));
	hnode * temp = NULL;

	if (!index) return 5;
	else temp = *index;

	return edit(to_edit, temp);

}

//finds the struct with the correct topic name and url and copies the new data entered by the client into it.
int table::edit(info & to_edit, hnode * temp)
{
	if (!temp) return 5;
	
	if (strcmp(temp->data.topic_name, to_edit.topic_name) == 0 && strcmp(temp->data.website, to_edit.website) == 0) {
		delete [] temp->data.review;
		strcpy(temp->data.review, to_edit.review);
		temp->data.rating = to_edit.rating;
		return 1;
	}

	return edit(to_edit, temp->next);
}

//gets the topic and url of the website to be edited and the new information from the user and sends it all to the edit member function
int edit(table & hash_table)
{
	char temp[SIZE];
	info to_edit;

	cout << "\nWhat is the topic of the website you are looking for?\n";
	cin.get(temp, SIZE, '\n'); cin.ignore(150, '\n');

	if (to_edit.topic_name) delete [] to_edit.topic_name;
	to_edit.topic_name = new char[strlen(temp)+1];
	strcpy(to_edit.topic_name, temp);

	cout << "\nWhat is the URL of the website you are looking for?\n";
	cin.get(temp, SIZE, '\n'); cin.ignore(150, '\n');
	
	if (to_edit.website) delete [] to_edit.website; 
	to_edit.website = new char[strlen(temp)+1];
	strcpy(to_edit.website, temp);

	cout << "\nWhat would you like the new review for the website to be?\n";
	cin.get(temp, SIZE, '\n'); cin.ignore(150, '\n');
	
	if (to_edit.review) delete [] to_edit.review; 
	to_edit.review = new char[strlen(temp)+1];
	strcpy(to_edit.review, temp);
	
	cout << "\nWhat would you like the new rating for the website to be?\n";
	cin >> to_edit.rating; cin.ignore(100, '\n');
	
	return hash_table.edit(to_edit);
}

//reads in the data to a temp info object, passes that object to the insert member function of the table class
int read(table & hash_table)
{
	ifstream file_in;
	file_in.open("websites.txt");
	char array[SIZE];
	int file = 0;
	info temp;	

	if (!file_in) return 0;

	file_in.get(array, SIZE, '|');
	file_in.ignore(100, '|');
	if (temp.topic_name) delete [] temp.topic_name;
	temp.topic_name = new char[strlen(array)+1];
	strcpy(temp.topic_name, array);

	while (file_in && !file_in.eof()) {
		
		if (file_in.peek() == '|') file_in.ignore();
		else {
			file_in.get(array, SIZE, '|');
			file_in.ignore(100, '|');
			if (temp.website) delete [] temp.website;
			temp.website = new char[strlen(array)+1];
			strcpy(temp.website, array);
		};

		if (file_in.peek() == '|') file_in.ignore();
		else {
			file_in.get(array, SIZE, '|');
			file_in.ignore(100, '|');
			if (temp.summary) delete [] temp.summary;
			temp.summary = new char[strlen(array)+1];
			strcpy(temp.summary, array);
		};

		if (file_in.peek() == '|') file_in.ignore();
		else {
			file_in.get(array, SIZE, '|');
			file_in.ignore(100, '|');
			if (temp.review) delete [] temp.review;
			temp.review = new char[strlen(array)+1];
			strcpy(temp.review, array);
		};

		file_in >> temp.rating;
		file_in.ignore(100, '\n');

		file = hash_table.insert(temp);

		if (file_in.peek() == '|') file_in.ignore();
		else {
			file_in.get(array, SIZE, '|');
			file_in.ignore(100, '|');
			if (temp.topic_name) delete [] temp.topic_name;
			temp.topic_name = new char[strlen(array)+1];
			strcpy(temp.topic_name, array);
		};
	}
	
	file_in.close();
	file_in.clear();

	return file;
}

//gets the topic the user would like to display 
int display_topic(table & hash_table)
{
	char temp[SIZE];
	char * topic = NULL;

	cout << "\nWhat is the name of the topic you would like to look up?\n";
	cin.get(temp, SIZE, '\n'); cin.ignore(150, '\n');

	if (topic) delete [] topic; 
	topic = new char[strlen(temp)+1];
	strcpy(topic, temp);
	
	return hash_table.display_topic(topic);
}

//wrapper, gets the info entered by the client, passes it to the member function to display
int table::display_topic(char * topic)
{
	hnode ** current = (hash_table + hash_function(topic));
	hnode * temp = NULL;

	if (!current) return 4;
	else temp = *current;

	return display_topic(temp, topic);
}

//recursively checks if the node topic is the same as the sought after topic.
int table::display_topic(hnode * temp, char * topic)
{
	if (!temp) return 4;

	if (strcmp(temp->data.topic_name, topic) == 0) {
		cout <<	"\n\nTopic of the website: " << temp->data.topic_name << "        URL: " << temp->data.website 
		     << "     Rating: " << temp->data.rating << "\nSummary: " << temp->data.summary << "\nReview: " << temp->data.review;
		return 1;
	}

	return display_topic(temp->next, topic);
}

// the number of sought after websites of the specified topic and calls the member function to retrieve them
bool retrieve(char * topic, info *& matches, int & num, table & hash_table)
{
	char temp[SIZE];

	cout << "\nWhat is the name of the topic you would like to look up?\n";
	cin.get(temp, SIZE, '\n'); cin.ignore(150, '\n');

	if (topic) delete [] topic; 
	topic = new char[strlen(temp)+1];
	strcpy(topic, temp);
	

	return hash_table.retrieve(topic, matches, num);
}

//finds any matching node and adds them to the array
bool table::find_match(char * topic, info *& matches, int & num)
{
	int i = 0;
	hnode ** current = (hash_table + hash_function(topic));
	hnode * temp = NULL;

	if (!current) return false;
	temp = *current;
	while (temp) {
		if (strcmp(temp->data.topic_name, topic) == 0) {
			matches[i].copy(temp->data);
			++i;
		}
		temp = temp->next;
	}
	return true;
}

//retrieves the sought after data
bool table::retrieve(char * topic, info *& matches, int & num)
{
	hnode ** current = (hash_table + hash_function(topic));
	hnode * temp = NULL;
	bool res = 0;

	if (!current) return false;
	else {
		
		temp = *current;
		if (!temp) return false;
		while (temp) {
			if (strcmp(temp->data.topic_name, topic) == 0) ++num;
		}
		matches = new info[num];
		res = find_match(topic, matches, num);
	}
	return res;
}
	
//displays all of the entries in an insorted order
int table::display_all()
{
	hnode * to_show = NULL;
	int num = 0;
	
	for (int i = 0; i < hash_size; ++i) {
		if (hash_table[i]) {
			to_show = hash_table[i];
			while (to_show) {
				cout <<	"\n\nTopic of the website: " << to_show->data.topic_name << "        URL: " << to_show->data.website 
				     << "     Rating: " << to_show->data.rating << "\nSummary: " << to_show->data.summary << "\nReview: " << to_show->data.review;
				to_show = to_show->next;
				++num;
			}
		}
	}

	if (num == 0) return 2;
	return 1;
}	
	
//copies the info struct over
int info::copy(info & to_copy)
{
	if (!to_copy.topic_name && !to_copy.website && !to_copy.summary && !to_copy.review && !to_copy.rating) {
		cout << "\nThere was no data to copy, dummy.";
		return 0;
	}

	if (topic_name) delete [] topic_name;
	if (website) delete [] website;
	if (summary) delete [] summary;
	if (review) delete [] review;

	if (to_copy.topic_name) {
		topic_name = new char[strlen(to_copy.topic_name)+1];
		strcpy(topic_name, to_copy.topic_name);
	}

	if (to_copy.website) {
		website = new char[strlen(to_copy.website)+1];
		strcpy(website, to_copy.website);
	}

	if (to_copy.summary) {
		summary = new char[strlen(to_copy.summary)+1];
		strcpy(summary, to_copy.summary);
	}

	if (to_copy.review) {
		review = new char[strlen(to_copy.review)+1];
		strcpy(review,to_copy.review);
	}

	if (to_copy.rating) rating = to_copy.rating;

	return 1;
}
//table class member function that sends the topic name through the hash function and copies the data to the hash table.
int table::insert(info & to_add)
{
	hnode ** to_insert = (hash_table + hash_function(to_add.topic_name));

	if (!*to_insert) {
		*to_insert = new hnode;
		(*to_insert)->data.copy(to_add);
		(*to_insert)->next = NULL;
	} else {
		hnode * temp = *to_insert;
		*to_insert = new hnode;
		(*to_insert)->data.copy(to_add);
		(*to_insert)->next = temp;
	}
	return 1;	
}

//gets the new infor from the client to be added to the hash table
int get_new(table & hash_table)
{
	info to_add;
	char temp[SIZE], ans = 'y';

	do {
		cout << "\n\n\nWhat is the name of the topic of the website?\n";
		cin.get(temp, SIZE, '\n'); cin.ignore(150, '\n');
		if (to_add.topic_name) delete [] to_add.topic_name;
		to_add.topic_name = new char[strlen(temp)+1];
		strcpy(to_add.topic_name, temp);
 
		cout << "\n\n\nWhat is the website url?\n";
		cin.get(temp, SIZE, '\n'); cin.ignore(150, '\n');
		if (to_add.website) delete [] to_add.website;
		to_add.website = new char[strlen(temp)+1];
		strcpy(to_add.website, temp);

		cout << "\n\n\nWhat is the summary of the website?\n";
		cin.get(temp, SIZE, '\n'); cin.ignore(150, '\n');
		if (to_add.summary) delete [] to_add.summary;
		to_add.summary = new char[strlen(temp)+1];
		strcpy(to_add.summary, temp);
 
		cout << "\n\n\nWhat is the review of the website?\n";
		cin.get(temp, SIZE, '\n'); cin.ignore(150, '\n');
		if (to_add.review) delete [] to_add.review;
		to_add.review = new char[strlen(temp)+1];
		strcpy(to_add.review, temp);

		cout << "\n\n\nWhat is the rating of the website (1-5, 1 being garbage, 5 being the best of the best)?\n";
		cin >> to_add.rating; cin.ignore(150, '\n');

		cout << "\n\nYou have entered:\n" << to_add.topic_name << endl << to_add.website << endl << to_add.summary << endl << to_add.review << endl << to_add.rating << endl;
		cout << "\nIs this correct? y or n\n";
		cin >> ans; cin.ignore(100, '\n');
		ans = tolower(ans);

	} while (ans != 'y');
	return hash_table.insert(to_add);
}

//get's the user choice
int get_choice()
{
	int choice = 0;

	while (choice == 0) {
		cout << "\n\nBesides go to the bar and slack off, what would you like to do today? Please enter one of the following numbers:\n1) Enter a new website's information\n"
		     << "2) Edit a website's review and rating\n3) Remove all the dumb websites (with a rating of 1)\n4) Display all the websites from a particular topic"
		     << "\n5) Display all websites stored with us so far\n6)Retrieve all the websites with the topic name of your choice?\n9) Exit program.\n";
		cin >> choice;
		cin.ignore(100, '\n');
		if (choice != 2 && choice != 1 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 9) {
			cout << "\n\nAre you trying to break me? You entered an invalid number, you invalid! Let's try this again.\n\n";
			choice = 0;
		}
	};
	
	return choice;
}

//hash function that returns the hash value for the topic name passed to it
int table::hash_function(char * key)
{
	char * end = (key + strlen(key));
	char * current = (key);
	int hash_value = 0;

	while (current < end) {
		hash_value += ((*current*2)^2);
		++current;
	}
	
	return hash_value % hash_size;
}
void table::undo()
{
	
	hnode * current = NULL;
	hnode * temp = NULL;
	
	for (int i = 0; i < hash_size; ++i) {
		if (hash_table[i]) {
			
			current = hash_table[i];
			if (!current) return;
			if (!current->next) {
				delete current;
				current=NULL;
			}
			if (current->next) {
				temp = current->next;
				delete current;
				current->next = temp;
			}
		}
	}
}
void undo(table & hash_table)
{
	hash_table.undo();
}
//destrucotr for the table class
table::~table()
	
{
	hnode * current = NULL;
	hnode * temp = NULL;
	
	for (int i = 0; i < hash_size; ++i) {
		if (hash_table[i]) {
			
			current = hash_table[i];
			if (!current) return;
			if (!current->next) {
				delete current;
				current=NULL;
			}
			if (current->next) {
				temp = current->next;
				delete current;
				current->next = temp;
			}
	}
	
}

/*
	hnode ** current = hash_table;
	hnode ** end = (hash_table + hash_size);
	hnode * temp = *current;
	hnode * ptr = NULL;

	while (current < end) {
		if (temp) {
		while (temp) {
			if (!temp->next) delete temp;
				else { 
					ptr = temp->next;
					delete temp;
					temp->next = ptr;
				}
			}	
		}
		++current;
	}
}
*/
}
//constructor for the table class
table::table(int size)
{
	hash_size = size;
	
	hash_table = new hnode * [hash_size];
	hnode ** current = hash_table;
	hnode ** end = (hash_table + size);

	while (current < end) {
		*current = NULL;
		++current;
	}
}

//destructor for the info class
info::~info()
{
	if (topic_name) delete [] topic_name;
	if (website) delete [] website;
	if (summary) delete [] summary;
	if (review) delete [] review;
}
	
//constructor for the info to be added
info::info()
{
	topic_name = NULL;
	website = NULL;
	summary = NULL;
	review = NULL;
	rating = 0;
}
