#include <string>
#include <fstream>
#include <cstdlib>
#include "LineManager.h"

using std::cin;
using std::ofstream;

//building the partial menu object
//using the "options" vector
void LineManager::build_Partial_Menu()
{
	partial_menu.set_top_message("\nChoose one of the following options");
	for (int i = 0; i < 4; ++i)
	{
		partial_menu.push_back(options[i]);
	}
	partial_menu.push_back("Quit");
	partial_menu.set_bottom_message("Enter an option number");
}

//building the full menu object
//using the "options" vector
void LineManager::build_Full_Menu()
{
	full_menu.set_top_message("\nChoose one of the following options");
	for (const auto& opt: options)
	{
		full_menu.push_back(opt);
	}
	full_menu.set_bottom_message("Enter an option number");
}

//a method to display the full menu object
void LineManager::display_Full_Menu()
{
	full_menu.toString();
}

//a method to display the partial menu object
void LineManager::display_Partial_Menu()
{
	partial_menu.toString();
}

//a method that invokes a function according
//to the user's choice for the partial menu
void LineManager::partial_menu_choice(int choice)
{
	if (choice == 1)
	{
		append_from_keyboard();
	}

	else if (choice == 2)
	{
		insert_from_keyboard();
	}

	else if (choice == 3)
	{
		append_from_textfile();
	}

	else if (choice == 4)
	{
		insert_from_textfile();
	}

	else if (db.isEmpty() && choice == 5)
	{
		exit(EXIT_FAILURE);
	}
}

//a method that invokes a function according
//to the user's choice for the full menu
void LineManager::full_menu_choice(int choice)
{
	//the method for the partial menu is invoked first
	//as the partial and full menus are the same 
	//for choices 1-4
	partial_menu_choice(choice);

	//methods belonging only to the full menu
	if (choice == 5)
	{
		print_line();
	}

	else if (choice == 6)
	{
		print_span();
	}

	else if (choice == 7)
	{
		set_spans();
	}

	else if (choice == 8)
	{
		print_all();
	}

	else if (choice == 9)
	{
		move_current_line();
	}

	else if (choice == 10)
	{
		delete_current_line();
	}

	else if (choice == 11)
	{
		write_db_to_file();
	}

	else if (choice == 12)
	{
		quit();
	}
}

//Below are methods assigned
//to each of the user's choices

//repeatedly prompts for and reads a text line from the keyboard
//and appends it at the end of the database;
//to end the input entry, the user must enter a single dot (.)
//character on a line by itself.
void LineManager::append_from_keyboard()
{
	string userEntry;
	cout << "To end input, enter a single dot and press enter" << endl;
	while (userEntry != ".")
	{
		getline(cin, userEntry);

		if (userEntry != ".")
		{
			db.append(userEntry);
		}
	}
	//since the input has not been saved to a file,
	//the dbSaved variable is set to "false"
	dbSaved = false;
}

//repeatedly prompts for and reads a text line from the keyboard
//and inserts it at cp; to end the input entry, the user must 
//enter a single dot (.) character on a line by itself.
void LineManager::insert_from_keyboard()
{
	//If there is only one line entered,
	//the "insert" method of "MiniDB" class template is used
	string firstUserEntry;
	cout << "To end input, enter a single dot and press enter" << endl;
	getline(cin, firstUserEntry);
	db.insert(firstUserEntry);
	
	//If there are several lines entered,
	//each subsequent line is appended to the input
	//as a separate database entry
	string subsequentUserEntry;
	while (subsequentUserEntry != ".")
	{
		getline(cin, subsequentUserEntry);

		//If the cp points to the last element of the database,
		//the "append" method of "MiniDB" class template is used
		if (subsequentUserEntry != "." && (db.getCurrentIndex() == db.size() - 1))
		{
			db.append(subsequentUserEntry);
		}

		//By default, the cp is set to the next position,
		//and the "insert" method of "MiniDB" class template is used
		else if (subsequentUserEntry != ".")
		{
			db.next();
			db.insert(subsequentUserEntry);
		}
	}
	//since the input has not been saved to a file,
	//the dbSaved variable is set to "false"
	dbSaved = false;
}

//a boolean helping method that prompts for 
//and reads the name of a text file;
//if the file cannot be opened, an error message is displayed,
//but the program continues
bool LineManager::opening_text_file(ifstream& fin)
{
	cout << "Enter input filename:" << endl;
	string filename;
	getline(cin, filename);
	fin.open(filename);

	if (fin) return true;

	else
	{
		cout << "Could not open the file " << filename << endl;
		fin.clear();
		return false;
	}
}

//if the file was opened,
//the method reads the lines in that file and appends them
//to the end of the database
void LineManager::append_from_textfile()
{
	ifstream fin;
	if (opening_text_file(fin))
	{
		string line;
		while (getline(fin, line))
		{
			db.append(line);
		}
	}

	//since the input has not been saved to a file,
	//the dbSaved variable is set to "false"
	dbSaved = false;
}
//if the file was opened,
//the method reads the lines in that file and inserts them
//to the current position
void LineManager::insert_from_textfile()
{
	ifstream fin;
	if (opening_text_file(fin))
	{
		//If there is only one line in the file,
		//the "insert" method of "MiniDB" class template is used
		string firstLine;
		getline(fin, firstLine);
		db.insert(firstLine);

		//If there are several lines in the file,
		//each subsequent line is appended to the intput
		//as a separate database entry
		string line;
		while (getline(fin, line))
		{
			//If the cp points to the last element of the database,
			//the "append" method of "MiniDB" class template is used
			if (db.getCurrentIndex() == db.size() - 1)
			{
				db.append(line);
			}

			//By default, the cp is set to the next position,
			//and the "insert" method of "MiniDB" class template is used
			else
			{
				db.next();
				db.insert(line);
			}
		}
	}

	//since the input has not been saved to a file,
	//the dbSaved variable is set to "false"
	dbSaved = false;
}

//prints the line represented by the current line
void LineManager::print_line()
{
	cout << (db.getCurrentIndex() + 1) << ": " << db.getValue() << endl;
}

//prints upper_span lines above the current line, followed by the line 
//at the current line, and followed by lower_span lines below the current 
//line; the last line printed will become the new current line
void LineManager::print_span()
{
	string current_line = db.getValue();
	size_t current_index = db.getCurrentIndex();
	int converted_upper_span = static_cast<int> (upper_span);

	//first, indices of the very first line in the upper span
	//and the very last line in the lower span are found
	int upper_span_index = current_index - converted_upper_span;
	int lower_span_index = current_index + lower_span;

	//if the upper span index is less than 0,
	//it becomes 0
	if (upper_span_index < 0)
	{
		upper_span_index = 0;
	}

	//if the lower span index exceeds position
	//of the last element, it becomes 
	//index of last element
	if (lower_span_index > db.size() - 1)
	{
		lower_span_index = db.size() - 1;
	}

	//printing a span of lines around current position
	for (size_t i = upper_span_index; i <= lower_span_index; ++i)
	{
		db.moveToIndex(i);

		//if the span starts at 0,
		//the "**: BOF" indication is printed
		if (i == 0)
		{
			cout << "**: BOF" << endl;
		}
		cout << (db.getCurrentIndex() + 1) << ": " << db.getValue() << endl;

		//if the span ends at last position of the database
		//the "**: EOF" indication is printed
		if (i == db.size() - 1)
		{
			cout << "**: EOF" << endl;
		}
	}
}

//prompts the user to enter an integer 
//to set the length of upper / lower spans
//(see details in comments below)
void LineManager::set_spans()
{

	string current_line = db.getValue();
	int current_index = db.getCurrentIndex();

	//code to process various types entered by user:
	//a) if the user enters an integer (e.g., 1), the input is OK
	//b) if the user enters an integer followed by another type (e.g., 1text), the integer is extracted
	//so the input is OK
	//c) if the user starts input with a type that is not an integer (e.g., text1), an error is output
	//and the user is prompted to enter the number again.

	int userEntry;
	cout << "What's the length of the span" << endl;
	cin >> userEntry;
	string bad_data;

	if (!cin)
	{
		cin.clear();
		string bad_data;
		getline(cin, bad_data);
		cout << "Incorrect input " << userEntry << "Please try again." << endl;

		//in case of incorrect user input, calling the method again
		set_spans();
	}

	getline(cin, bad_data);

	//If the integer n entered by the user is < 0, 
	//the temporary_upper_span is set to -n
	//until it is proven that n is valid
	if (userEntry < 0)
	{
		size_t temp_upper_span = -(userEntry);

		int converted_temp_upper_span = static_cast<int> (temp_upper_span);
		int temp_upper_span_index = current_index - converted_temp_upper_span;

		//if the new upper span index is less than 0,
		//n is invalid
		if (temp_upper_span_index < 0)
		{
			//if the current upper_span index is 0,
			//an error is output
			if (current_index == 0)
			{
				cout << "No upper span can be added because current position "
					<< "is the first position on the list ";
			}

			else {
				//if the current upper_span index is less than 0,
				//an error is output, and the recommended number
				//for upper_span is printed 
				cout << "That's a large span of lines. Max is "
					<< current_index << endl;
			}
		}

		//if the new upper span index is more than 0,
		//n is valid so the upper_span becomes equal to -n.
		else
		{
			upper_span = -(userEntry);
		}

	}

	//If the integer n entered by the user is > 0, 
	//the temporary_lower_span is set to n
	//until it is proven that n is valid
	else if (userEntry > 0)
	{
		size_t temp_lower_span = userEntry;
		size_t temp_lower_span_index = current_index + temp_lower_span;

		//if the new lower span index exceeds position
		//of the last element, n is invalid
		if (temp_lower_span_index > db.size() - 1)
		{

			size_t max_allowed_lower_span = (db.size() - 1) - (current_index);

			//if the current lower_span index corresponds to 
			//the last position on the list, an error is output
			if (max_allowed_lower_span == 0)
			{
				cout << "No lower span can be added because current position "
					<< "is the last position on the list ";
			}

			//if the current lower_span index exceeds 
			//the last position on the list, an error is output
			//and the recommended number for lower_span is printed 
			else
			{
				cout << "That's a large span of line. Max is "
					<< max_allowed_lower_span << endl;
			}
		}

		//if the new lower span index is less than index
		//of the last element, n is valid and the lower_span 
		//becomes equal to n.
		else
		{
			lower_span = userEntry;
		}
	}

	//If the integer n entered by the user is equal to 0, 
	//both upper_span and lower_span are set to 0.
	else
	{
		upper_span = 0;
		lower_span = 0;
	}
}

//prints all the lines in the database
//preceding each line with the index of that line;
//the "toString" method of "MiniDB" class template is used;
//the last line printed will become the new
//current line
void LineManager::print_all()
{
	db.toString();
	db.prev();
}

//prompts for and reads a 1-based integer line index (n)
//and the makes the corresponding 0-based index the current line
void LineManager::move_current_line()
{

	//code to process various types entered by user:
	//a) if the user enters an integer (e.g., 1), the input is OK
	//b) if the user enters an integer followed by another type (e.g., 1text), the integer is extracted
	//so the input is OK
	//c) if the user starts input with a type that is not an integer (e.g., text1), an error is output
	//and the user is prompted to enter the number again.
	int userEntry;
	cout << "which line to move to?" << endl;
	cin >> userEntry;
	string bad_data;

	if (!cin)
	{
		cin.clear();
		string bad_data;
		getline(cin, bad_data);
		cout << "Incorrect input " << userEntry
			<< "Please enter an integer. " << endl;

		//in case of incorrect user input, calling the method again
		move_current_line();
	}

	getline(cin, bad_data);

	//if n is invalid, an error is output, 
	//but the program continues running 
	if (userEntry < 1 || userEntry > db.size())
	{
		cout << "Incorrect input. The number should be in range "
			<< "[1, " << db.size() << "]." << endl;
	}

	else
	{
		db.moveToIndex(userEntry - 1);
	}
}

//removes the current line from the database
//using the "remove" method of "MiniDB" class template
//according to this method:
//a) if the database had only 1 line, it becomes empty;
//b) if current line corresponded to the last item,
//it becomes reset to point at the item before the one removed
//c) in default case, cp starts pointing at the item after the one removed
void LineManager::delete_current_line()
{
	db.remove();
	cout << "removing the current line ..." << endl;

	//since the changes have not been saved to a file,
	//the dbSaved variable is set to "false"
	dbSaved = false;
}

//prompts for and reads the name of a text file;
//writes the lines in the database to the specified file
void LineManager::write_db_to_file()
{
	ofstream fin;
	cout << "Enter input filename:" << endl;
	string filename;
	getline(cin, filename);
	fin.open(filename);

	//after the file has been opened,
	//the database is written into it line-by-line
	//using a for-loop
	if (fin)
	{
		//writing all lines, except for the last one, into the file
		db.moveToFirst();
		for (int i{ 0 }; i < db.size() - 1; ++i)
		{
			fin << db.getValue() << "\n";
			db.next();
		}

		//writing the last line into the file
		fin << db.getValue() << "\n";
		
		//since the input has been saved to a file,
		//the dbSaved variable is set to "true"
		dbSaved = true;
	}

	//if the file cannot be opened, an error message is displayed,
	//but the program continues
	else
	{
		cout << "Could not open the file " << filename << endl;
		fin.clear();
	}
}

//Terminates the program
void LineManager::quit()
{
	string userEntry;

	//If the database has been modified since it was last saved,
	//the user is asked if they want to save changes to the file
	if (dbSaved == false)
	{
		cout << "Do you want to save changes to a file? Start your answer with Y or y if yes. " << endl;
	cin >> userEntry;
	
		//If the user starts their answer with Y or y, the database is saved to the file;
		//otherwise, the program terminates.
		if (userEntry.at(0) == 'y' || userEntry.at(0) == 'Y')
		{
			write_db_to_file();
		}

		else
		{
			cout << "goodbye" << endl;
			exit(EXIT_FAILURE);
		}
	}

	//If the database has not been modified since it was last saved,
	//the program terminates
	else
	{
		cout << "goodbye" << endl;
		exit(EXIT_FAILURE);
	}
}

//the "run" method launching a menu-driven session 
//where the user can selecct operations that execute interactively
void LineManager::run()
{
	cout << "Welcome to LineManager!" << endl;
	cout << "=======================" << endl;
	int choice{ 0 };
	build_Partial_Menu();
	build_Full_Menu();

	//a loop that iterates until the user selects "Quit"
	while (true)
	{
		//if the database is empty, the partial menu is displayed
		if (db.isEmpty())
		{
			display_Partial_Menu();

			//the user makes a choice that invokes one of the functions
			//described above; the user is prompted to select more options
			//until they decide to select ""Quit", in which case the program terminates
			choice = partial_menu.read_option_number();
			partial_menu_choice(choice);
		}

		//if the database is not empty, the full menu is displayed
		while (!db.isEmpty())
		{
			display_Full_Menu();

			//the user makes a choice that invokes one of the functions
			//described above; the user is prompted to select more options
			//until they decide to select ""Quit", in which case the program terminates
			choice = full_menu.read_option_number();
			full_menu_choice(choice);
		}
	}
}