/*Matthew Spohrer
CS 163 Homework 1
PSU ID # 958566579*/

#include "prog1.h"
using namespace std;

int main()
{
	int user_choice = 0;
	catalog manager;
	while (user_choice == 0) {
		user_choice = choice();
		delegator(manager, user_choice);
		user_choice = 0;
	}
	return 0;
}
