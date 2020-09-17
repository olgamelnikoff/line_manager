#include "Menu.h"
#include "MiniDB.h"
#include "LineManager.h"
#include <string>

using std::cout;
using std::endl;
using std::cerr;

int main()
{
    LineManager tm;
    tm.run();

    //Testing the MiniDB class
    
    //MiniDB<string> db;

    //Testing the std::logic_error (when the database is empty):
    
    /*db.prev();
    db.next();
    db.moveToFirst();
    db.moveToLast();
    db.getCurrentIndex();
    db.moveToIndex(5);
    db.getValue();
    db.remove();*/

    //Testing the std::logic_error (when the database is not empty):
    
    /*db.insert("Apple");
    db.prev();
    db.next();
    db.moveToFirst();
    db.moveToLast();
    db.moveToIndex(5);
    db.remove();
    cout << db.getValue() << endl;*/
    
    
    //Testing methods without logic errors
    /*db.append("Apple");
    db.append("Melon");
    db.append("Grapes");
    db.append("Watermelon");
    db.toString();
    cout << "db size is " << db.size() << endl;
    db.moveToFirst();
    cout << db.getCurrentIndex() << endl;
    db.moveToLast();
    cout << db.getValue() << endl;
    db.moveToIndex(2);
    cout << db.getValue() << endl;
    db.insert("Mango");
    cout << db.getValue() << endl;
    db.prev();
    cout << db.getValue() << endl;
    db.next();
    cout << db.getValue() << endl;
    db.remove();
    db.toString();*/

    return 0;
}