#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <vector>

using std::vector;
using std::string;
using std::ostream;

class Menu {
private:
    vector<std::string> option_list; // the option list represented by vector of strings
    string top_message; //the opening message
    string bottom_message; //the closing message

public:
    Menu() = default; //defaulted default constructor

    //The "Big Three":
    Menu(const Menu&) = default; //defaulted copy constructor
    virtual ~Menu() = default; //defaulted destructor
    Menu& operator=(const Menu&) = default; //defaulted assignment operator

    //insertion operator overload as a friend member:
    friend ostream& operator <<(ostream&, const Menu&);

    //an "insert" method inserting a new line to the option list
    //at a certain position
    void insert(int, string);

    //a "push_back" method adding supplied line to the end
    //of the option list
    void push_back(string);

    //removes the line at a certain position from the option list
    void remove(int);

    //returns the number of lines in the option list (size of the option list):
    int size() const;

    //removes the last line from the option list:
    void pop_back();

    //returns the line at a certain position
    string get(int);

    //returns a string representation of this menu
    std::string toString() const;

    //displays this menu and then reads
    //and returns a valid line number
    int read_option_number();

    //sets top message
    void set_top_message(std::string);

    //sets bottom message
    void set_bottom_message(std::string);

    //sets top message to empty text
    void clear_top_message();

    //sets bottom message to empty text
    void clear_bottom_message();

    //determines if this menu' option list is empty
    bool isEmpty() const;
};
#endif /* MENU_H */