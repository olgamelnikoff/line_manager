#include <iostream>
#include <string>
#include <ostream>
#include <vector>
#include "Menu.h"

using std::cout;
using std::cin;
using std::endl;
using std::to_string;
using std::ostream;
using std::size_t;
using std::out_of_range;
using std::string;

//Overloading operator << using toString() function
ostream& operator <<(ostream& output, const Menu& m) {
    output << m.toString() << endl;
    return output;
}

//an "insert" method inserting a new option at position "index - 1
//using the "insert" method of the "vector" class template
void Menu::insert(int index, string option) {

    //index entered by user should be less than or equal to the option list size, but not less
    //than 1
    if ((index >= 1) && (index <= this->option_list.size())) {

        vector <string>::iterator iter;
        iter = this->option_list.begin();
        iter += (index - 1);
        option_list.insert(iter, option);

        //printing a message confirming that the option has been inserted
        cout << "Option \"" << option << "\" inserted successfully!\n" << endl;
    }

    //if index entered by user is beyond the vector size, display an error message
    else {
        cout << "Invalid menu position " << index
            << ". It must be in the range [1,"
            << this->option_list.size() << "]." << endl;
    }
}

// a "push_back" method adding supplied line to the end
// of the option list using the "push_back" method of the "vector" class template
void Menu::push_back(string newOption) {

    //adding the new option to the end of the option list
    option_list.push_back(newOption);

}

//removing an option from the list at position "index - 1",
//using the "erase" method of the "vector" class template
void Menu::remove(int index) {

    //index entered by user should be less or equal to the option list size, but not less
    //than 1
    if ((index >= 1) && (index <= this->option_list.size())) {
        vector <string>::iterator iter;
        iter = this->option_list.begin();
        iter += (index - 1);
        this->option_list.erase(iter);
    }

    //if index entered by user is beyond the menu size, display an error message
    else {
        cout << "Invalid menu position " << index
            << ". It must be in the range [1,"
            << this->option_list.size() << "]." << endl;
    }
}

//returns the number of options in the options list 
//(size of the option list) using the "size" method of the "vector" class template
int Menu::size() const {
    return this->option_list.size();
}
//removes the last option from the list
//using the "pop_back" method of the "vector" class template
void Menu::pop_back() {

    //displaying an error if the list is empty.
    if (isEmpty()) {
        cout << "Error: nothing to pop back. The list is empty.";
    }

    //clearing the last position in the option list
    else {
        this->option_list.pop_back();
    }
}

//returns the option at position 'k - 1'
string Menu::get(int k) {
    
    //'k' entered by user should be less or equal to count, but not less
    //than 1
    if (k < 1 || k > this->option_list.size()) {
        throw out_of_range("No such option");
    }
    return option_list[k - 1];
}

//returns a string representation of this menu

string Menu::toString() const {

    //introducing a string variable to hold
    //the entire menu
    string stringRepOfMenu;

    //appending string objects one-by-one to the stringRepOfMenu
    stringRepOfMenu.append(top_message);
    stringRepOfMenu.append("\n");

    //Adding menu options from option list to the stringRepOfMenu
    //using a for-loop
    for (int i{ 0 }; i < this->option_list.size(); ++i) {

        //first, converting the number i to a regular string
        string numberAsString = to_string(i + 1);

        stringRepOfMenu.append("  ");

        //adding the number of the current option to the Menu
        stringRepOfMenu.append(numberAsString);
        stringRepOfMenu.append(":  ");

        //adding the current option itself to the Menu
        stringRepOfMenu.append(option_list[i]);
        stringRepOfMenu.append("\n");
    }

    //adding the rest of the Menu to the stringRepOfMenu
    stringRepOfMenu.append(bottom_message);
    stringRepOfMenu.append("\n");
    stringRepOfMenu.append("??");

    //returning the final string representation of menu
    return stringRepOfMenu;
}

//displays this menu and then reads
//and returns a valid option number
int Menu::read_option_number() {

    //first, returning the menu representation using toString()
    cout << this->toString() << endl;

    //introducing a variable to hold the user entry
    int userEntry;
    cin >> userEntry;

    //code to process various types entered by user:
    //a) if the user enters an integer (e.g., 1), the input is OK
    //b) if the user enters an integer followed by another type (e.g., 1text), the integer is extracted
    //so the input is OK
    //c) if the user starts input with a type that is not an integer (e.g., text1), an error is output
    //and the user is prompted to enter the number again.

    string bad_data;

    if (!cin)
    {
        cin.clear();
        string bad_data;
        getline(cin, bad_data);
        cout << "Incorrect input " << userEntry
            << "Please enter an integer number." << endl;

        //in case of incorrect user input, calling the method again
        userEntry = read_option_number();
    }

    getline(cin, bad_data);

    //if the index entered by user is beyond count, displaying
    //an error message and printing the menu again
    //for the user to make another choice

    if (this->option_list.size() > 0 && ((userEntry > this->option_list.size()) || userEntry < 1)) {
        cout << "Invalid choice " << userEntry
            << ". It must be in the range [1, "
            << this->option_list.size() << "]." << endl;

        //in case of incorrect user input, calling the method again
        userEntry = read_option_number();
    }
    return userEntry;
}

//setting the top message
void Menu::set_top_message(string topMessage) {
    this->top_message.assign(topMessage);

}

//setting the bottom message
void Menu::set_bottom_message(string bottomMessage) {
    this->bottom_message.assign(bottomMessage);

}

//clearing the top message
void Menu::clear_top_message() {
    this->top_message.clear();
}

//clearing the bottom message
void Menu::clear_bottom_message() {
    this->bottom_message.clear();
}

//determines if this menu's option list is empty
bool Menu::isEmpty() const {
    if (this->option_list.empty()) {
        return true;
    }
    return false;
}