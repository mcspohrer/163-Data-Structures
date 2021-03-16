/*Matthew Spohrer
PSU ID# 958566579
CS163 Program2 homework*/

#include "prog2.h"
using namespace std;

int main ()
{
	int user_choice = 0;
	queue waitlist;
	stack s_promo;
	while (user_choice != 9)
	{
		user_choice = get_choice();
		delegator(user_choice, waitlist, s_promo);
	}

	return 0;
}
