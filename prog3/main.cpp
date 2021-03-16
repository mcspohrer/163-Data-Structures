//Matthew Spohrer
//PSU ID 958566579
//CS163 Prog3

#include "prog3.h"
using namespace std;


//main .cpp file to manage the hash table
int main ()
{
	int read_suc = 0, choice = 0, result = 0;
	table hash_table;
	info * matches = NULL;
	int num = 0;
	char * topic = NULL;

	while (read_suc == 0) {
		read_suc = read(hash_table);
		if (read_suc == 0) cout << "\nUh Oh! We need an adult! There was an issue with reading in the file!\n";
	}
	
	while (choice != 9) {
		choice = get_choice();
		if (choice == 1) result = get_new(hash_table);
		if (choice == 2) result = edit(hash_table);
		if (choice == 3) result = hash_table.remove();
		if (choice == 4) result = display_topic(hash_table);
		if (choice == 5) result = hash_table.display_all();
		if (choice == 6) {
			result = retrieve(topic, matches, num, hash_table);
			if (result == 0) cout <<"\n\nNo websites were found with that topic.\n\n";
			if (result != 0) cout << endl << endl << num << " websites were found with that topic name.\n\n";
		}
		if (result == 5) cout << "\nThe website doesn't exist, maybe you entered the topic name or URL incorrectly?\n";
		if (result == 4) cout << "\nSadly, there were no website with that topic to display yet.\n";
		if (result == 2) cout << "\nSadly, no websites have been entered yet.\n";
		if (result == 1) cout << "\nSuccess!! The programmer finally did something right!\n";
	}
	undo(hash_table);

	return 0;
}
