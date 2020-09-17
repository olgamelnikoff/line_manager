#ifndef LineManager_H
#define LineManager_H

#include <iostream>
#include <list>
#include <iterator>
#include <exception>
#include "Menu.h"
#include "MiniDB.h"

using std::ifstream;

class LineManager
{
	////insertion operator overload as a friend member:
	//friend ostream& operator <<(ostream&, const Menu&);

	//an object of MiniDB<std::string> representing a database of string items
	MiniDB<std::string> db;

	//an object of Menu representing a partial menu to be displayed 
	//only when the database is or becomes empty
	Menu partial_menu;

	//an object of Menu representing a full menu to be displayed 
	//when the database is not empty
	Menu full_menu;

	//upper and lower spans used when spans of lines
	//are output above and below cp
	size_t upper_span = 2;
	size_t lower_span = 2;

	//a boolean to test if the database
	//was saved to a file
	bool dbSaved = false;

	//a vector of options containing all the possible options
	//to be included in partial_menu and full_menu
	std::vector<std::string> options
	{
		"Append input from the keyboard",
		"Insert input from the keyboard",
		"Append input from text file",
		"Insert input from text file",
		"Print the current line",
		"Print a span of lines around the current position",
		"Set the length of upper or lower line spans",
		"Print all",
		"Move the current line",
		"Delete the current line",
		"Write mini-database to file",
		"Quit"
	};

private:
	//private methods representing each of the menu options
	void build_Partial_Menu(); //creates the partial menu object
	void build_Full_Menu();	   //creates the full menu object
	void display_Partial_Menu(); //displays the partial menu object
	void display_Full_Menu(); //displays the full menu object
	void partial_menu_choice(int); //assigns a certain method to the user's choice from the partial menu
	void full_menu_choice(int); //assigns a certain method to the user's choice from the full menu
	bool opening_text_file(ifstream&);//a helping method that determines 
									  //whether the file indicated by user can be opened
	void append_from_keyboard(); //appends the input entered by the user from the keyboard to the database
	void insert_from_keyboard(); //inserts the input entered by the user from the keyboard into the database
	void append_from_textfile(); //appends the input from a file to the database
	void insert_from_textfile(); //inserts the input from a file to the database
	void print_line(); //prints the current line
	void print_span(); //prints a span of lines around the current position
	void set_spans(); //sets the lentgh of upper or lower line spans
	void print_all(); // prints all the lines in the database
	void move_current_line(); //moves the current line to the line indicated by the user
	void delete_current_line(); //deletes the current line from the database
	void write_db_to_file(); //writes a database to a file
	void quit(); //terminates the program

public:
	LineManager() = default; //defaulted default constructor

	//The "Big Three":
	LineManager(const LineManager&) = default; //defaulted copy constructor
	virtual ~LineManager() = default; //defaulted destructor
	LineManager& operator=(const LineManager&) = default; //defaulted assignment operator

	void run(); //launches a menu-driven interactive session 
				//that allows the user to select various operations
};
#endif /*LineManager_H*/




