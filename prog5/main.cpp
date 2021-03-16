/*Matthew Spohrer
PSUID 958566579
CS163 HMW 5*/

#include "prog5.h"
using namespace std;

int main()
{
	int choice = 0, num = 0;
	table graph;
	
	num = graph.add();
	if (num == -1) cout << "\n\nA task already exists by that name, please try again.\n";
	if (num == -2) cout << "\n\nUnfortunately, you have entered more tasks than you have allotted for.\n";
	while (choice != 9) {
		choice = get_choice();
		if (choice == 1) num = graph.link();
		if (choice == 2) num = graph.display();
		if (choice == 3) num = graph.dft();
		if (num == -3) cout << "\n\nNo tasks have been added yet!\n";
		if (num == -4) cout << "\n\nNo match could be found in the graph for the entries, please reenter exactly as originally entered.\n";
		num = 0;
	}

	return 0;
}

