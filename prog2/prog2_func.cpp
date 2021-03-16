/*Matthew Spohrer
PSU ID 958566579
CS 163 Program2*/

#include "prog2.h"
using namespace std;

//writes the names removed from the promo list to an external data file
int stack::write(info & to_write)
{
	ofstream file_out;

	file_out.open("promo.txt", ios::app);
	if (file_out) file_out << "Name: " << to_write.name << "  Email: " << to_write.email << endl;
	file_out.close();
	file_out.clear();
	return 1;
}
	
//wrapper to call the member display so it can use the head pointer
int stack::display()
{
	return display(head);
}

//pops the top stack by decrementing the index, returns 0 if there are no entries
int stack::pop()
{
	s_node * temp;

	if (!head) return 0;

	peek();
	
	if (top_index > 1) {
		write(head->data[top_index-1]);
		--top_index;
		return 1;
	}

	if (top_index == 1 && !head->next) {
		write(head->data[top_index-1]);
		delete [] head->data;
		delete head;
		head = NULL;
		top_index = 0;
		return 1;
	}

	if (top_index == 1 && head->next) {
		write(head->data[top_index-1]);
		temp = head->next;
		delete [] head->data;
		delete head;
		head = NULL;
		head = temp;
		top_index = size;
		return 1;
	}
	return 1;
}

//peeks at the top of the stack, showing the inforation of the last added person, returns 0 if no entries
int stack::peek()
{
	if (!head) return 0;

	cout << "\nName: " << head->data[top_index-1].name
	     << "\nEmail: " << head->data[top_index-1].email << endl << endl;

	return 1;
}

//displays all the people in the stack
int stack::display(s_node * head)
{
	if (!head) return 0;
	for (int i = size-1; i>=0; --i) {
		if (head->data[i].name) {
			cout << "\nName: " << head->data[i].name;
			cout << "\nEmail: " << head->data[i].email;
		}
	}
	if (head->next) return display(head->next);
	return 1;
}

//pushes the data from the queue onto the top of the stack.
int stack::push(info & to_add)
{
	s_node * temp = NULL;
	temp = head;
	if (top_index == size) {
		head = new s_node;
		head->data = new info[size];
		head->next = temp;
		top_index = 0;
	}
	head->data[top_index].name = new char[strlen(to_add.name)+1];		
	strcpy(head->data[top_index].name, to_add.name);
	head->data[top_index].email = new char[strlen(to_add.email)+1];
	strcpy(head->data[top_index].email, to_add.email);
	++top_index;

	return 0;
}

//initializes the stack's LLL with a dynamically allocated array of the size entered by the user
int stack::initialize(int usize)
{
	size = usize;
	head = new s_node;
	head->data = new info[size];
	return 0;
}

//checks if the LLL of the stack is empty
bool stack::is_empty()
{
	if (!head) return true;
	return false;
}

//wrapper taht calls the dequeue member function, returns 0 if there is nothing to dequeue, 1 if removed the last person, and 2 if just successful.
int queue::dequeue(stack & s_promo)
{
	node * temp = NULL;
	int size = 0;
	info s_temp;

	if (!rear) return 0;

	if (rear->data.email && s_promo.is_empty()) {
		cout << "\n\nWhat size would you like the array for the stack to be? please enter integers only\n";
		cin >> size;
		cin.ignore(100, '\n');
		s_promo.initialize(size);
	}	

	if (rear->next == rear) {
		peek();
		if (rear->data.email) {
			s_temp.name = new char[strlen(rear->data.name)+1];
			strcpy(s_temp.name, rear->data.name);
			s_temp.email = new char[strlen(rear->data.email)+1];
			strcpy(s_temp.email, rear->data.email);
			s_promo.push(s_temp);
		}
		delete rear;
		rear = NULL;
		return 1;
	} else {
		peek();
		if (rear->next->data.email) {
			s_temp.name = new char[strlen(rear->next->data.name)+1];
			strcpy(s_temp.name, rear->next->data.name);
			s_temp.email = new char[strlen(rear->next->data.email)+1];
			strcpy(s_temp.email, rear->next->data.email);
			s_promo.push(s_temp);
		}
		temp = rear->next->next;
		delete rear->next;
		rear->next = temp;
	}
	return 2;
}
	

//wrapper that takes a calls the peek member function
int queue::peek()
{
	if (!rear) return 0;

	if (rear->next == rear) cout << "\n\nName: " << rear->data.name << "\nParty Size: " << rear->data.size << "\nSpecial Seating instructions: " << rear->data.special;
	else cout << "\n\nName: " << rear->next->data.name << "\nParty Size: " << rear->next->data.size << "\nSpecial Seating instructions: " << rear->next->data.special;

	return 1;
}

//member function that displays all names recursively, returning the number of parties waiting to be sat
int queue::display(node * front)
{
	if (!front) return 0;

	cout << "\nName: " << front->data.name << endl;
	
	return display(front->next) + 1;
}
	
//wrapper function that calls the display function, passing the rear node to the member function
int queue::display()
{
	int count = 0;
	node * temp = NULL;

	if (!rear) return 0;
	if (rear->next == rear) {
		cout << "\n\nName: " << rear->data.name;
		return 1;
	}
	
	temp = rear->next;
	rear->next = NULL;
	count = display(temp);
	rear->next = temp;

	return count;
}
	
//gets the data to add to the queue and adds it to the begining
int queue::enqueue(node *& rear, node *& to_add)
{
	node * temp = NULL;

	if(!rear){
		rear = to_add;
		rear->next = rear;
		return 1;
	}

	if (rear->next == rear) {
		temp = rear;
		rear->next = to_add;
		rear = rear->next;
		rear->next = temp;
		return 1;
	}

	temp = rear->next;
	rear->next = to_add;
	rear = rear->next;
	rear->next = temp;

	return 1;

}
	
//gets the info the client entered, copies it, then passes it to the member function that adds it to the list
int queue::enqueue(party & to_add)
{
	node * temp = NULL;
	temp = new node;

	temp->data.name = new char[strlen(to_add.name)+1];
	strcpy(temp->data.name, to_add.name); 

	temp->data.size = to_add.size; 

	temp->data.special = new char[strlen(to_add.special)+1]; 
	strcpy(temp->data.special, to_add.special); 

	if (to_add.email) {
		temp->data.email = new char[strlen(to_add.email)+1]; 
		strcpy(temp->data.email, to_add.email); 
	}
	return enqueue(rear, temp);
}

//gets party member info from the client
int add_wait(queue & waitlist)
{
	char temp[SIZE], ans = 'y';
	party to_add;
	
	do {
		cout << "\n\n\nWhat is the name of the party you would like to add to the end of the waitlist?\n";
		cin.get(temp, SIZE, '\n');
		cin.ignore(150, '\n');
		if (to_add.name) delete [] to_add.name;
		to_add.name = new char[strlen(temp)+1];
		strcpy(to_add.name, temp);

		cout << "\n\nWhat is the size of the party? Integers only, please.\n";
		cin >> to_add.size;
		cin.ignore(100, '\n');

		cout << "\n\nAre there any special seating instructions? If none, please enter \"none\"\n";
		cin.get(temp, SIZE, '\n');
		cin.ignore(151, '\n');
		if (to_add.special) delete [] to_add.special;
		to_add.special = new char[strlen(temp)+1];
		strcpy(to_add.special,temp);

		cout << "\n\nWould the party like to receive promotional items? y or n\n";
		cin >> to_add.promo;
		cin.ignore(100, '\n');
		
		if (toupper(to_add.promo) == 'Y') {
			cout << "\n\nWhat is the email address of the party member to receive promo items?\n";
			cin.get(temp, SIZE, '\n');
			cin.ignore(150, '\n');
			if (to_add.email) delete [] to_add.email;
			to_add.email = new char[strlen(temp)+1];
			strcpy(to_add.email, temp);
		}

		/*cout << "\n\nYou have entered:\n" << to_add.name << endl << to_add.size << endl << to_add.special << endl;
		if (to_add.email) cout << to_add.email << endl;
		cout << "\n\nIs this information correct? y or n\n";
		cin >> ans;
		cin.ignore(100, '\n');
		ans = tolower(ans);i*/

	} while (ans != 'y');
	return waitlist.enqueue(to_add);
}

//delegates work to the appropriate functions
int delegator(int user_choice, queue & waitlist, stack & s_promo)
{
	int ret = 0;

	if (user_choice == 1) ret = add_wait(waitlist);
	
	if (user_choice == 2) { 
		ret = waitlist.dequeue(s_promo);
		if (ret == 0) cout << "\nThere was no one waiting you weirdo!\n";
		if (ret == 1) cout << "\nYou now have no one on your wait list.\n";
	}

	if (user_choice == 3) {
		ret = waitlist.peek();
		if (ret == 0) cout << "\nYou have no one waiting!\n\n";
	}

	if (user_choice == 4) {
		ret = waitlist.display();
		if (ret == 0) cout << "\nYou have no parties waiting to be sat, maybe rethink your menu!\n\n\n";
		else cout << "\nYou have " << ret << " waiting to be sat. Better hurry up!\n\n";
	}
	
	if (user_choice == 5) {
		ret = s_promo.display();
		if (ret == 0) cout << "\n\nNo one has been added to the list yet.\n\n";
	}	

	if (user_choice == 6) {
		ret = s_promo.pop();
		if (ret == 0) cout << "\n\nNo one has been added to the list yet.\n\n";
	}	

	if (user_choice == 7) {
		ret = s_promo.peek();
		if (ret == 0) cout << "\n\nNo one has been added to the list yet.\n\n";
	}	

	return ret;
}

//gets what the user wants to do 
int get_choice()
{
	int choice = 0;
	
	do {
		cout << "\n\nWhat would you like to do right now? Please enter one of the following:\n1 to add a name to the end of the waitlist\n"
		     << "2 to seat the first name of the waitlist\n3 to take a peek at the next party to be seated\n"
		     << "4 to display the number of parties in line to be sat and the names of all the parties\n"
		     << "5 to print all the people to be sent promotional stuff\n6 to list the people to receive promo stuff and remove them from the list"
		     << "\n7 to take a look at the last person added to the list of people to receive promotional stuff\n9 to quit\n";
		cin >> choice;
		cin.ignore (100, '\n');

		if (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 &&  choice != 6 && choice != 7 && choice != 9) {
			cout << "\nYou clearly did not follow the rules, try again.\n";
			choice = 0;
		}
	} while (choice == 0);
	
	return choice;
}

//destructor for the stack
stack::~stack()
{
	delete head;
}

//constructot for stack
stack::stack()
{
	head = NULL;
	top_index = 0;
	size = 0;
}

//destructor for queue
queue::~queue()
{
	delete rear;
}

//constructot for queue
queue::queue()
{
	rear = NULL;
}

//destructory for the promo struct
info::~info()
{
	if (name) delete [] name;
	if (email) delete [] email;
}

//constructor to initialize all the data for the promo struct
info::info()
{
	name = NULL;
	email = NULL;
}

//destructory for the party struct
party::~party()
{
	if (name) delete [] name;
	if (email) delete [] email;
	if (special) delete [] special;
}

//constructor to initialize all the data for the party struct
party::party()
{
	name = NULL;
	promo = 'n';
	email = NULL;
	size = 0;
	special = NULL;
}	
