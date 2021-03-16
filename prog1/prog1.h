/*Matthew Spohrer
PSU ID#: 958566579
Program CS 163*/

//this is the header frile for the LLL ADT for prog1.it includes the structs and the class interfaces

#include <iostream>
#include <cstring>
#include <cctype>

const int SIZE = 151; //constant size for user inputs for arrays before being allocated dynamically

//struct used for all the song info
struct song
{
	song();
	~song();
	char * artist;
	char * title;
	char * length;
	int views;
	int likes;
};

//node used for the songs by an artist in the artist's LLL
struct song_node
{
	song data;
	song_node * next;
};

//struct used to contain artist's name
struct artist
{
	artist();
	~artist();
	char * name;
	char * story;
	char * description;
};

//struct used for the node for the artist's name in the general, managing LLL
struct artist_node
{
	artist data;
	artist_node * next;
	song_node * song_head;
};

//the class is being used to keep the data private and using the functions to access the data.
class catalog
{
	public:
		catalog();
		~catalog();
		int add_artist(artist &); //copies data entered by user to be used in the managing class, returns 0 if duplicate.
		int insert(artist_node *&, artist_node *&); //inserts the new artist into the managing LLL, returns 0 if duplicate
		int display_artist(); //returns 0 if empty list
		int del_artist(char []); //deletes an artist's node, deallocating the memory for it, returns 0 if artist doesn't exist
		int add_song(song_node *&);//returns 0 if song already exists, adds a song to the artist's LLL
		int add_song_wrapper(song &, song_node *&);//wrapper that gets called from the public function to call the copy function and add_song function.
		int edit();//returns 0 if song doesn't exist, edits song's data
		int display_songs(char []); //displays all the songs and their information by an artist, ranked by popularity, returns 0 if artist doesn't exist
		int del_under(int); //deletes all the songs of all the artists with under the user supplied number of views. returns 0 if none were deleted
		int delete_artist(artist_node *&, char []); //maybe this is actually a wrapper program designed to allow me to use recursion, returns 0 if artist doesn't exist
		int copy_song(song &, song_node *&);//copies the song from a temporary variable to a sond node.
		int organizer(artist_node *&); // organizes the song by each artist by number of likes. returns 0 if no artists, 2 if no songs to organize.
		int edit_song(char [], char [], int, int); //edits the likes and views of the song. returns 0 if no srtists, 1 if no songs. 
		int less_delete(int cutoff);//deletes all songs with the numbers of likes below a user supplied number. returns 0 if no artists, 1 if no songs
	private:
		artist_node * head;
};	

int choice(); //gets user choice for action, returns 0 if user choice not an option
int add_artist(catalog & manager); //gets the info from the user and sends it to the catalogue class
int display_artist(catalog & manager); //wrapper that allows the class to display all its goods
int delete_artist(catalog & manager); //wrapper to delete a node from the LLL. Returns 0 if the artist doesn't exist
int delegator(catalog & manager, int & user_choice); // delegates to the appropriate functions as chosen by the user. returns 0 if failed.
int add_song(catalog &); //gets info from user and passes it to the member function of the catalog class. returns 1 if song already exists and 0 if artist doesn't exit
int display_songs(catalog & manager); //gets the name of the artist to have songs displayed, returns 1 if artist doesn't exist
int edit_song(catalog & manager); // gets which artist to alter, returns 0 if no artists, 1 if no songs.
int less_delete(catalog & manager);//gets the minimum number of likes the user would like each song to have and calls the member function that deletes all songs with less
