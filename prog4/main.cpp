//Matthew Spohrer
//PSU ID 958566579
//CS163 prog4

#include "prog4.h"
using namespace std;

//main .cpp to manage the binary search tree
int main()
{
	table BST;
	int choice = 0, result = 0;
	int read_suc = 0;

	while (read_suc == 0) {
		read_suc = read(BST);
		if (read_suc == 0) cout << "\nUh Oh! We need an adult! There was an issue reading in the file!\n";
	}

	while (choice != 9) {
		choice = get_choice();
		if (choice == 1) result = get_new(BST);	
		if (choice == 2) result = get_topic(BST);	
		if (choice == 3) result = get_key(BST);	
		if (choice == 4) result = BST.display();
		if (choice == 5) result = display_one(BST);
		if (result == -1) cout << "\n\nThat keyword is already being used, please try to enter the information in again with a different keyword.\n\n";	
		if (result == -2) cout << "\n\nThere were no websites to display, enter some data!!!\n\n";
		if (result == -3) cout << "\n\nThat keyword could not be found, please try again.\n\n";	
		if (result == -4) cout << "\n\nThat topic could not be found, please try again.\n\n";	
	}
	
	return 0;
}
