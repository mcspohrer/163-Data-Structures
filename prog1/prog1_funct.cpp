/*Matthew Spohrer
CS163 Homework 1
PSU ID # 958566579 */

//this is where the functions will be implemented
#include "prog1.h"
using namespace std;

//deletes all songs with fewer likes than a user supplied amount
int catalog::less_delete(int cutoff)
{
	artist_node * current = head; 
	song_node * ptr = current->song_head; 
	song_node * prev_ptr = current->song_head; 
	if (!head) return 0;

	while (current) {
		ptr = current->song_head;

		if (!current->song_head->next && current->song_head->data.likes < cutoff) delete current->song_head; 
		
		while (ptr) {	
			if (ptr->data.likes < cutoff) {
				ptr = ptr->next;
				delete prev_ptr->next;
				prev_ptr->next = ptr;
			} else {
				prev_ptr = ptr;
				ptr = ptr->next;
			}
		}
		
		current = current->next;		
	}
	return 1;
}

//calls the member function that deletes all the songs with fewer than a user supplied number of likes
int less_delete(catalog & manager)
{
	int cutoff;
	
	cout << "\n\nAt least how many likes would you like each song to have? Integers only, please.\n\n";
	cin >> cutoff;
	cin.ignore(100, '\n');
	return manager.less_delete(cutoff);
}
					
//allows you to edit the likes and views of an artist's songs.
int catalog::edit_song(char art_name[], char song_name[], int likes, int views)
{
	artist_node * current = head;
	song_node * ptr = current->song_head;
	
	if (!head) return 0;
	while (strcmp(art_name, current->data.name) != 0) {
		if (!current) return 0;
		current = current->next;
	}
	
	if (!current->song_head) return 1;
	
	while (strcmp(ptr->data.title, song_name) != 0 ) {
		if (!ptr) return 1;
		ptr = ptr->next;
	}
	
	ptr->data.likes = likes;
	ptr->data.views = likes;
	
	return 3;
}
	
		
	
//gets name of artist and song to be edited.
int edit_song(catalog & manager)
{	
	char temp[SIZE]; 
        char * art_name; 
	char * song_name;
	int like, view = 0;

	cout << "\n\nWhat is the name of the artist you would like to see the songs for? Please enter the name exactly as it appeard in the directory!\n\n"; 
	cin.get(temp, SIZE, '\n'); 
	cin.ignore(100, '\n'); 
	art_name = new char[strlen(temp)+1]; 
	strcpy(art_name, temp);
      
	cout << "\n\nWhat is the name of the song you would like to edit? Please enter the name exactly as it was entered!\n\n"; 
	cin.get(temp, SIZE, '\n'); 
	cin.ignore(100, '\n'); 
	song_name = new char[strlen(temp)+1]; 
	strcpy(song_name, temp);

	cout << "\n\nWhat would you like the likes to be? numbers only, please.\n";
	cin >> like;
	cin.ignore(100, '\n');

	cout << "\n\nWhat would you like the views to be? Numbers only, please.\n";
	cin >> view;
	cin.ignore(100, '\n');

	return manager.edit_song(art_name, song_name, like, view);
}
	 
//delegetese the user's choice to the appropriate functions to accomplish appropriate goals
int delegator(catalog & manager, int & user_choice)
{
	int success = 0;
	if (user_choice == 1) 
	{ 
		success = add_artist(manager);
		if (success == 0){ 
			user_choice = 0;
			cout << "\n\nYou entered a duplicate name."; 
		} 
	}

	if (user_choice == 2)
	{
		success = delete_artist(manager);
		if (success == 0) {
			user_choice = 0;
			cout << "\n\nThat artist doesn't exist.";
		}
	}

	if (user_choice == 3) {
		success = add_song(manager);
		if (success == 1) {
			cout << "\n\nThis artist doesn't exist!\n\n";
			user_choice = 0;
		}
		if (success == 0) {
			cout<< "\n\nThis song already exists!\n\n";
			user_choice = 0;
		}
	}
	if (user_choice == 4) {
		success = edit_song(manager);
		if (success == 0) { 
			cout << "\n\nThis artist doesn't exist!\n\n"; 
			user_choice = 0; 
		} 
		if (success == 0) { 
			cout<< "\n\nThis song already exists!\n\n"; 
			user_choice = 0; 
		}
	}
		 
	if (user_choice == 5) {
		success = display_songs(manager);
		if (success == 1) {
			cout << "\n\nThat artist doesn't exist!\n\n";
			user_choice = 0;
		}
	}

	if (user_choice == 6) {	
		success = display_artist(manager); 
		if (success == 0) { 
			user_choice = 0; 
			cout << "\n\nYou haven't signed any artists yet. Stop being lazy and do some work!"; 
		} 
	}
	if (user_choice == 7) {
		success = less_delete(manager);
		if (success == 0) {
			user_choice = 0;
			cout <<"\n\nNo artist are in your list yet.\n\n";
		}
	}
	return 0;		
}

//member function taht goes through and displays all of an artist's songs. returns 1 if the artis doesnt exist and 0 if there are no songs to display
int catalog::display_songs(char art_name[])
{
	artist_node * current = head;
	song_node * ptr = NULL;
	if (!head) return 1;
	if (!current->song_head) return 0;

	while (current) {
		if (strcmp(current->data.name, art_name) == 0) {
			ptr = current->song_head;	
			while (ptr) {
				cout << "\nSong Title:" << ptr->data.title;
				cout << "    Song Length:" << ptr->data.length;
				cout << "\nSong Likes:" << ptr->data.likes;
				cout << "    Song Views:" << ptr->data.views;
				cout << "\n\n\n";
				ptr = ptr->next;
			}
			return 3;
		}
		current=current->next;
	}
	return 1;
}

//called from public, gets the name of the artist to output songs for and passes it to the member function
int display_songs(catalog & manager)
{
	char temp[SIZE];
	char * art_name;

	cout << "\n\nWhat is the name of the artist you would like to see the songs for? Please enter the name exactly as it appeard in the directory!\n\n";
	cin.get(temp, SIZE, '\n');
	cin.ignore(100, '\n');
	//if (art_name) delete [] art_name
	art_name = new char[strlen(temp)+1];
	strcpy(art_name, temp);
	cout << "Name: " << art_name;
	return manager.display_songs(art_name);
}
	
//copies from the new song to the data member of the song_node struct
int catalog::copy_song(song & new_song,song_node *& song_new)
{
	if (song_new->data.artist) delete [] song_new->data.artist;
	song_new->data.artist = new char[strlen(new_song.artist) +1];
	strcpy(song_new->data.artist, new_song.artist);

	if (song_new->data.title) delete [] song_new->data.title; 
	song_new->data.title = new char[strlen(new_song.title) +1]; 
	strcpy(song_new->data.title, new_song.title);

	if (song_new->data.length) delete [] song_new->data.length; 
	song_new->data.length = new char[strlen(new_song.length) +1]; 
	strcpy(song_new->data.length, new_song.length);

	song_new->data.likes = new_song.likes;

	song_new->data.views = new_song.views;
	return add_song(song_new);
}

//an actual wrapper function designed to call the copy function and adds the song to the artist's node.
int catalog::add_song_wrapper(song & new_song, song_node *& song_new)
{
	
	copy_song(new_song, song_new);
	return add_song(song_new);
}
	
//adds a song to an artist's library, returns 0 if song name already exists or 1 if the artist doesn't exist.
int catalog::add_song(song_node *& song_new)
{
	song_node * song_ptr = NULL;
	artist_node * current = head;
	song_node * prev = NULL;
	if (!head) return 1;

	while (strcmp(current->data.name, song_new->data.artist) != 0)
	{
		current=current->next;
		if (!current) return 1;
	}
	song_ptr = current->song_head;
	if (!current->song_head)
	{
		current->song_head=song_new;
		return 3;
	}   
	if (song_new->data.likes > song_ptr->data.likes) {
		if (strcmp(song_new->data.title,current->song_head->data.title) == 0) return 0;
		song_new->next = current->song_head;
		current->song_head = song_new; 
		return 3;
	}
	while (song_ptr)
	{
		if (strcmp(song_new->data.title,song_ptr->data.title) == 0) return 0;
		if (song_new->data.likes >  song_ptr->data.likes)  {
			song_new->next = song_ptr;
			prev->next= song_new;
			return 3;
		}
		prev = song_ptr;
		song_ptr = song_ptr->next;
	}
	prev->next = song_new;
	song_new->next = NULL;
	return 3;
}
	
	
//gets the song info from the user through main and reallocates memory for the two arrays. Passes the info to the class member functions. 
int add_song(catalog & manager)
{
	song new_song;
	char temp[SIZE];
	char ans = 'n';
	song_node * song_new;
	song_new = new song_node;
	do {
		

		cout << endl << endl << "What is the name of the artist  you would like to add a song to? Please enter it exactly it has been stored" 
		     << " (spaces, uppercase, lower case, symbols).\n"; 
		cin.get(temp, SIZE, '\n'); 
		cin.ignore (150, '\n'); 
		if (new_song.artist) delete [] new_song.artist; 
		new_song.artist = new char[strlen(temp)+1]; 
		strcpy(new_song.artist, temp); 

		cout << endl << endl << "What is the name of the song  you would like to add? Please enter it exactly as you would like it stored" 
		     << " (spaces, uppercase, lower case, symbols).\nPlease don't try to add the same song, as well!\n"; 
		cin.get(temp, SIZE, '\n'); 
		cin.ignore (150, '\n'); 
		if (new_song.title) delete [] new_song.title; 
		new_song.title = new char[strlen(temp)+1]; 
		strcpy(new_song.title, temp); 

		cout << "\n\nWhat is the length of this song?\n"; 
		cin.get(temp, SIZE, '\n'); 
		cin.ignore(100, '\n'); 
		if (new_song.length) delete [] new_song.length; 
		new_song.length = new char[strlen(temp)+1]; 
		strcpy(new_song.length, temp); 

		cout << "\n\nHow many likes has this song gotten? Numerical answers only, please.\n"; 
		cin >> new_song.likes; 
		cin.ignore(100, '\n'); 
		
		cout << "\n\nHow many views has this song gotten? Numerical answers only, please.\n"; 
		cin >> new_song.views;
		cin.ignore(100, '\n'); 

		cout << "\n\n\nIs this correct? y or n :\n " << new_song.title << endl << new_song.length << endl << new_song.likes << endl << new_song.views <<endl;
		cin >> ans;
		cin.ignore(100, '\n');
		ans = tolower(ans);


	} while (ans == 'n');
	return manager.add_song_wrapper(new_song, song_new);	
}
	
//memeber function that looks for the artist to delete and deletes it
int catalog::delete_artist(artist_node *& head, char name[])
{
	artist_node * previous = NULL;
	artist_node * current = head;

	if (!head){ 
		cout << "\n\nYou have no artists signed.";
		return 0;
	}	
	while (current) {
		if (strcmp(head->data.name, name) == 0 && !head->next) {
			delete head;
			head = NULL;
			return 1;
		} else if (strcmp(head->data.name, name) == 0 && head->next) {
			current = current->next;
			delete head;
			head = current;
		} else if (strcmp(current->data.name,name) == 0) {
			current = current->next;
			delete previous->next;
			previous->next = current;
			return 1;
		}
		previous = current;
		current = current->next;
	}		
		
	return 1;
}


//wrapper, maybe, class member function calls the member function that recursively looks for the artist and deletes it 
int catalog::del_artist(char name[])
{
	return delete_artist(head, name);
}

//wrapper function to delete an artist that also gets the name of the artist to delete
int delete_artist(catalog & manager)
{
	char temp[SIZE];
	artist del_artist;
	
	cout << "\n\nWhat is the name of the artist you'd like to delete? Make sure all the cases"
	     << " spaces, and symbols are correct.\n";
	cin.get(temp, SIZE, '\n');
	cin.ignore(150, '\n');
	if (del_artist.name) delete [] del_artist.name;
	del_artist.name = new char[strlen(temp)+1];
	strcpy(del_artist.name,temp);
	
	return manager.del_artist(del_artist.name);
}
	
//wraper function to display all the artists, returns 0 if there are no artists
int display_artist(catalog & manager)
{
	cout << "Here's the list of all the signed artists:\n";
	return manager.display_artist(); 
}

//displays all the atists in alphabetical order, returns 0 if its an empty list
int catalog::display_artist()
{
	artist_node * ptr = head;

	if (!head) return 0;
		
	while (ptr) 
	{
		cout << "Artist :" << ptr->data.name << endl << "Story  :" << ptr->data.story << endl << "Description: " << ptr->data.description << endl << endl;
		ptr = ptr->next;
	}
	return 1;	
}
	
//adds the newly entered artist to the LLL by copying the new data to current
int catalog::add_artist(artist & new_artist)
{
	artist_node * current = NULL;
	current = new artist_node;

	current->data.name = new char[strlen(new_artist.name)+1]; 
	strcpy(current->data.name, new_artist.name);

	current->data.story = new char[strlen(new_artist.story)+1];
	strcpy(current->data.story, new_artist.story);
	
	current->data.description = new char[strlen(new_artist.description)+1];
	strcpy(current->data.description, new_artist.description);

	return insert(head, current);
}		

//inserts the new node into the managing LLL, returns 0 if the name to add is a duplicate
int catalog::insert(artist_node *& head, artist_node *& current)
{
	if (!head) 
	{
		head=current;
		head->next = NULL;
		return 1;
	}

	if (strcmp(current->data.name, head->data.name) == 0) return 0;
	
	if (!head->next) {
		if (current->data.name > head->data.name) {
			head->next = current;
			current->next = NULL;

		}
		else {
			current->next = head;
			head = current;
			head->next->next = NULL;
		}
		return 1;
	}	

	if (head->next->data.name > current->data.name){
		current->next = head;
		head = current;
		return 1;
	}
		
	return insert(head->next, current);
}
//from main, gets the info for the new artist from the user and passes it to the publice member function add_artist
int add_artist(catalog & manager)
{
	char temp[SIZE], ans = 'n';
	artist new_artist;
	do {
		cout << endl << endl 
		     << "What is the name of the artist you would like to add? Please enter it exactly as you would like it stored"
		     << " (spaces, uppercase, lower case, symbols).\n";
		cin.get(temp, SIZE, '\n');
		cin.ignore (150, '\n'); 
		if (new_artist.name) delete [] new_artist.name;
		new_artist.name = new char[strlen(temp)+1];
		strcpy(new_artist.name, temp);

		cout << "\n\nWhat is the top story about this artist?\n";
		cin.get(temp, SIZE, '\n');
		cin.ignore(100, '\n');
		if (new_artist.story) delete [] new_artist.story;
		new_artist.story = new char[strlen(temp)+1];
		strcpy(new_artist.story, temp);

		cout << "\n\nWhen did the artist join the label and what is the genre the artist plays in?\n";
		cin.get(temp,SIZE, '\n');
		cin.ignore(100, '\n');
		if (new_artist.description) delete [] new_artist.description;
		new_artist.description = new char[strlen(temp)+1];
		strcpy(new_artist.description, temp);

		
		cout << "\n\nIs this correct (y or n):\n" << new_artist.name << endl << new_artist.story << endl << new_artist.description << endl;
		cin >> ans;
		cin.ignore(100, '\n');
		ans = tolower(ans);
	} while (ans == 'n');
	return manager.add_artist(new_artist);
}	

//asks the user what they want to do
int choice()
{
	int choice = 0;
	do{
		cout << "\n\nWhat would you like to do today? Please enter:\n1 to add an artist\n"
		     << "2 to delete an artist\n3 to add a song to an artist's list of songs\n"
		     << "4 to edit the number of likes and views for a song\n5 to display all the songs for a particular artist\n"
		     << "6 to diplay all the artists\n7 to delete all the lesser liked songs.\n";
		cin >> choice;
		cin.ignore(100, '\n');
		if (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7)
		{
			cout << "\n\nThat's not an option! Try again.\n\n";
			choice = 0;
		}
	}while (choice == 0);
	return choice;
}			

//constructor for the song struct
song::song()
{
	artist = NULL;
	title = NULL;
	length = NULL;
	views = 0;
	likes = 0;
}

//destructo for the song struct
song::~song()
{
	if (artist) delete [] artist;
	if (title) delete [] title;
	if (length) delete [] length;
	title = length = NULL;
}

//constructor for the artist struct
artist::artist()
{
	name = NULL;
	story = NULL;
	description = NULL;
}
//destructor for the artist struct, deallocates dynamic memore
artist::~artist()
{
	if (name) delete [] name;
	if (story) delete [] story;
	if (description) delete [] description;
	name = story = description = NULL;

}

//destructor for the catalogue class, deallocates all dynamic memory
catalog::~catalog()
{
	artist_node * temp;
	while (head){
		temp = head->next;
		delete head;
		head = temp;
	}
}

//default constructor for the class
catalog::catalog()
{
	head=NULL;
}


