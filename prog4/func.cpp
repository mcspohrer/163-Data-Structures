//Matthew Spohrer
//PSU ID 958566579
//CS163 prog 4

#include "prog4.h"
using namespace std;

//reads in the data from the external data file then stores it on the BST
int read(table & BST)
{
	ifstream file_in;
	file_in.open("website.txt");
	char array[SIZE];
	int file= 0;
	info * temp = new info;

	if (!file_in) return 0;
	file_in.get(array, SIZE, '|');
	file_in.ignore(100, '|');
	if (temp->topic) delete [] temp->topic;
	temp->topic = new char[strlen(array)+1];
	strcpy(temp->topic, array);

	while(file_in && !file_in.eof()) {

		if (file_in.peek() == '|') file_in.ignore();
		else {
			file_in.get(array, SIZE, '|');
			file_in.ignore(100, '|');
			if (temp->keyword) delete [] temp->keyword;
			temp->keyword = new char[strlen(array)+1];
			strcpy(temp->keyword, array);
		};

		if (file_in.peek() == '|') file_in.ignore();
		else {
			file_in.get(array, SIZE, '|');
			file_in.ignore(100, '|');
			if (temp->URL) delete [] temp->URL;
			temp->URL = new char[strlen(array)+1];
			strcpy(temp->URL, array);
		};

		if (file_in.peek() == '|') file_in.ignore();
		else {
			file_in.get(array, SIZE, '|');
			file_in.ignore(100, '|');
			if (temp->summary) delete [] temp->summary;
			temp->summary = new char[strlen(array)+1];
			strcpy(temp->summary, array);
		};

		if (file_in.peek() == '|') file_in.ignore();
		else {
			file_in.get(array, SIZE, '|');
			file_in.ignore(100, '|');
			if (temp->review) delete [] temp->review;
			temp->review = new char[strlen(array)+1];
			strcpy(temp->review, array);
		};

		file_in >> temp->rating;
		file_in.ignore(100, '\n');

		file = BST.add(*temp);

		
		if (file_in.peek() == '|') file_in.ignore();
		else {
			file_in.get(array, SIZE, '|');
			file_in.ignore(100, '|');
			if (temp->topic) delete [] temp->topic;
			temp->topic = new char[strlen(array)+1];
			strcpy(temp->topic, array);
		};
	}
	
	file_in.close();
	file_in.clear();
	delete temp;
	return file;
}

//private member function which deletes the topics of the user's choice
int table::remove_topic(node *& root, char * topic)
{
	if (!root) return -4;
	remove_topic(root->left, topic);
	remove_node_topic(root, topic);

	//if (!root) return -4;
	remove_topic(root->right, topic);
	remove_node_topic(root, topic);

	return 0;
}

//wrapper that calls the private member function to delete all websites with a matching topic.
int table::remove_topic(char * topic)
{
	if (!root) return -4;
	return remove_node_topic(root, topic);
}

//gets the topic of the websites to delete from the client. passed it to the member functions in control of deleteing.
int get_topic(table & BST)
{
	int num = 0;
	char array[SIZE];
	char * temp_topic = NULL;

	cout << "\n\nWhat is the topic of the websites you would like to delete?\n";
	cin.get(array, SIZE, '\n'); cin.ignore(100, '\n');
	if (temp_topic) delete [] temp_topic;
	temp_topic = new char[strlen(array)+1];
	strcpy(temp_topic, array);
	num = BST.remove_topic(temp_topic);
	if (temp_topic) delete temp_topic;
	temp_topic = NULL;
	return num;
}

//removes all websites with a particular topic
int table::remove_node_topic(node *& temp, char * key)
{
	node * hold = NULL;

	if (!temp) return -4;

	if ((!temp->left)&&(!temp->right)&&(strcmp(temp->data.topic, key) == 0)) {
		delete temp;
		temp = NULL;
		return 1;
	} else if ((!temp->right) &&(temp->left)&&(strcmp(temp->data.topic, key) ==0)) {
		hold = temp->left; 
		temp->left = NULL;
		delete temp;
		temp = hold;
		return remove_node_topic(temp, key);
	} else if ((temp->right)&&(!temp->left)&&(strcmp(temp->data.topic, key) == 0)){
		hold = temp->right;
		temp->right = NULL;
		delete temp;
		temp = hold;
		return remove_node_topic(temp, key);
	} else {
		node * current = temp->right;
		if((current)&&(!current->left)&&(strcmp(temp->data.topic, key) == 0)){
			temp->data.copy(current->data);
			temp->right = current->right;
			current->right = NULL;
			delete current;
			current = NULL;
			return remove_node_topic(temp, key);
		} else if((strcmp(temp->data.topic, key) == 0)){
			node * prev = NULL;
			while (current->left) {
				prev = current;
				current = current->left;
			}
			temp->data.copy(current->data);
			prev->left = current->right;
			current->right = NULL;
			delete current;
			current = NULL;	
			return remove_node_topic(temp, key);
		}
	}
	return remove_node_topic(temp->left, key) + remove_node_topic(temp->right, key);
}

//recursively traverses BST to find a website with a specific keyword
int table::remove_node(node *& temp, char * key)
{
	node * hold = NULL;

	if (!temp) return -3;

	if(!temp->left && !temp->right && strcmp(temp->data.keyword, key) == 0) {
		delete temp;
		temp = NULL;
	} else if (!temp->right && temp->left && strcmp(temp->data.keyword, key) ==0 ) {
		hold = temp->left; 
		temp->left = NULL;
		delete temp;
		temp = hold;
	} else if (temp->right && !temp->left && strcmp(temp->data.keyword, key) == 0) {
		hold = temp->right;
		temp->right = NULL;
		delete temp;
		temp = hold;
	} else {
		node * current = temp->right;
		if (current && !current->left && strcmp(temp->data.keyword, key) == 0) {
			temp->data.copy(current->data);
			temp->right = current->right;
			current->right = NULL;
			delete current;
			current = NULL;
		} else if (strcmp(temp->data.keyword, key) == 0) {
			node * prev = NULL;
			while (current->left) {
				prev = current;
				current = current->left;
			}
			temp->data.copy(current->data);
			prev->left = current->right;
			current->right = NULL;
			delete current;
			current = NULL;
		}
	}
	if (temp && strcmp(key, temp->data.keyword) < 0) remove_node(temp->left, key);
	else if (temp && strcmp(key, temp->data.keyword) > 0) remove_node(temp->right, key);
	return 1;
}
	
//wrapper to call the provate mem func that deletes the appropriate node
int table::remove_key(char * key)
{



	return remove_node(root, key);
}

//gets the keyword of the website the client would like to delete
int get_key(table & BST)
{
	char * key = NULL;
	char temp[SIZE];
	int num = 0;

	cout << "\n\nWhat is the keyword of the website you would like deleted?\n";
	cin.get(temp, SIZE, '\n'); cin.ignore(100, '\n');

	if (key) delete [] key;
	key = new char[strlen(temp)+1];
	strcpy(key, temp);
	num = BST.remove_key(key);
	if (key) delete key;
	key = NULL;
	return num;
}
//displays the information for a single website, using the reetrieve function
int display_one(table & BST)
{
	char array[SIZE];
	info my_info;
	int suc = 0;

	cout << "\n\nWhat is the keyword of the website you would like to look up?\n";
	cin.get(array, SIZE, '\n'); cin.ignore(100,'\n');
	if (my_info.keyword) delete [] my_info.keyword;
	my_info.keyword = new char[strlen(array) +1];
	strcpy(my_info.keyword, array);		
	
	suc = BST.retrieve(my_info);

	if (suc == 1) {

		cout << "\nKeyword: " << my_info.keyword << "\nTopic: "  << my_info.topic << "\nURL: " << my_info.URL << "\nSummary: " << my_info.summary 
		     << "\nReview: " <<my_info.review << "\nRating: " << my_info.rating << endl << endl;
	}
	//delete my_info;
	return suc;
}

//wrapper to pass root to the retrieve member function
int table::retrieve(info & my_info)
{
	return retrieve(root, my_info);
}

//retrieves a specific by keyword website node
int table::retrieve(node *& root, info & my_info)
{
	if (!root) return -3;
	
	
	if (strcmp(root->data.keyword, my_info.keyword) == 0) my_info.copy(root->data);

	if (strcmp(my_info.keyword, root->data.keyword) < 0) retrieve(root->left, my_info);
	else if (strcmp(my_info.keyword, root->data.keyword) > 0) retrieve(root->right, my_info);

	return 1;
}

//displays all the data in sorted order
int table::display(node * root)
{
	if (!root) return -2;

	display(root->left);
	cout << "\nKeyword: " << root->data.keyword << "\nTopic: "  << root->data.topic << "\nURL: " << root->data.URL << "\nSummary: " << root->data.summary 
	     << "\nReview: " <<root->data.review << "\nRating: " << root->data.rating << endl << endl;
	display(root->right);

	return 1;
}

//wrapper to call the display function
int table::display()
{
	cout << "\n\n\nHere is a list of the websites you have entered, sorted by the keyword entered:\n";

	return display(root);
}
//allows for a deep copy of the information
int info::copy(info & to_copy)
{	
	if (topic) delete [] topic;
	if (keyword) delete [] keyword;
	if (URL) delete [] URL;
	if (summary) delete [] summary;
	if (review) delete [] review;

	if (to_copy.topic) {
		topic = new char[strlen(to_copy.topic)+1];
		strcpy(topic, to_copy.topic);
	}
	
	if (to_copy.keyword) {
		keyword = new char[strlen(to_copy.keyword)+1];
		strcpy(keyword, to_copy.keyword);
	}

	if (to_copy.URL) {
		URL = new char[strlen(to_copy.URL)+1];
		strcpy(URL, to_copy.URL);
	}

	if (to_copy.summary) {
		summary = new char[strlen(to_copy.summary)+1];
		strcpy(summary, to_copy.summary);
	}

	if (to_copy.review) {
		review = new char[strlen(to_copy.review)+1];
		strcpy(review, to_copy.review);
	}

	if (to_copy.rating) rating = to_copy.rating;

	return 1;
}

//adds the new website to the BST
int table::add(node *& root, info * to_add)
{
	
	if (!root) {
		root = new node;
		root->data.copy(*to_add);
		return 1;
	}
	
	if (strcmp(to_add->keyword, root->data.keyword) == 0) return -1;
	if (strcmp(to_add->keyword, root->data.keyword) < 0 ) return add(root->left, to_add);
	else if (strcmp(to_add->keyword, root->data.keyword) > 0) return add(root->right, to_add);	

	return 1;
}

//wrapper to call the private member function to add
int table::add(info & to_add)
{
	return add(root, &to_add);
}

//gets the information for a new website to be inserted from the client 
int get_new(table & BST)
{
	info to_add;
	char temp[SIZE], ans = 'y';

	do {
		cout << "\n\nWhat is the topic of the website to be added?\n";
		cin.get(temp, SIZE, '\n'); cin.ignore(150, '\n');
		to_add.topic = new char[strlen(temp)+1];
		strcpy(to_add.topic, temp);

		cout << "\n\nWhat is the keyword of the website to be added?\n";
		cin.get(temp, SIZE, '\n'); cin.ignore(150, '\n');
		to_add.keyword = new char[strlen(temp)+1];
		strcpy(to_add.keyword, temp);

		cout << "\n\nWhat is the URL of the website to be added?\n";
		cin.get(temp, SIZE, '\n'); cin.ignore(150, '\n');
		to_add.URL = new char[strlen(temp)+1];
		strcpy(to_add.URL, temp);

		cout << "\n\nWhat is the summary of the website to be added?\n";
		cin.get(temp, SIZE, '\n'); cin.ignore(150, '\n');
		to_add.summary = new char[strlen(temp)+1];
		strcpy(to_add.summary, temp);

		cout << "\n\nWhat is the review of the website to be added?\n";
		cin.get(temp, SIZE, '\n'); cin.ignore(150, '\n');
		to_add.review = new char[strlen(temp)+1];
		strcpy(to_add.review, temp);

		cout << "\n\nWhat is the rating of the website (1-5, 1 means you almost quit internetting because "
		     << "of this site and 5 being the best, restoring your faith in the internet)\n";
		cin >> to_add.rating; cin.ignore(150, '\n');

		cout << "\n\nYou have entered:\n" << to_add.topic << endl << to_add.keyword<< endl
		     << to_add.URL << endl << to_add.summary << endl << to_add.review << endl << to_add.rating;
		cout << "\n\nIs this information correct? y or n\n";
		cin >> ans; cin.ignore(150, '\n');
		ans = tolower(ans);

	} while (ans!= 'y');

	return BST.add(to_add);
}

//asks and returns what the user would like to use the program four
int get_choice()
{
	int choice = 0;
	
	do {
		cout <<"\n\nWelcome to the biggest and bestest(hopefully) program this side of the mighty Mississip! Please enter what you would like to do today (integers only):\n\n\n"
		     <<"1)Enter a new website\n2)Remove all websites with the topic of your choosing\n3)Remove a specific website of your choosing, found by the keyword\n"
		     <<"4)Display all the websites, sorted by their keywords\n5)Display a single website's information, looked up by the keyword\n9)Exit the program\n";
		cin >> choice; cin.ignore(100, '\n');
		if (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice !=5 && choice != 9) cout << "\n\nYou think you're so cool trying to break this program?!?! Try again you jerk!\n\n";
	} while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice !=5 && choice != 9);
	
	return choice;
}
//destructor for table class
table::~table()
{
	if (root) delete root;	
	root = NULL;
}

//destructor for node
node::~node()
{

	if (right) delete right;
	right = NULL;
	if (left) delete left;	
	left = NULL;
}
//constructor for node
node::node()
{
	right = NULL;
	left = NULL;	
}

//constructor for the table class
table::table()
{
	root = NULL;
}

//destructor for the info struct
info::~info()
{
	if (topic) delete [] topic;
	topic = NULL;
	if (keyword) delete [] keyword;
	keyword = NULL;
	if (URL) delete [] URL;
	URL = NULL;
	if (summary) delete [] summary;
	summary = NULL;
	if (review) delete [] review;
	review = NULL;
	//rating = '\0';
}

//constructor for the info struct
info::info()
{
	topic = NULL;
	keyword = NULL;
	URL = NULL;
	summary = NULL;
	review = NULL;
	rating = 0;
}
