#ifndef MiniDB_H
#define MiniDB_H

#include <iostream>
#include <list>
#include <iterator>
#include <exception>

using std::cout;
using std::endl;

template <typename T>

class MiniDB {
	std::list<T> db_store; //the list representing the mini database
	typename std::list<T>::iterator current_position; //the iterator representing the current position

public:
	//defaulted default constructor
	MiniDB<T>() = default;

	//defaulted "Big Three" (copy constructor, assignment operator and destructor)
	virtual ~MiniDB<T>() = default;
	MiniDB<T>(const MiniDB&) = default;
	MiniDB& operator = (const MiniDB&) = default;

	//Methods representing operations on the database.
	//See description of each as a comment to a corresponding implementation below. 
	size_t size() const;
	void insert(const T& item);
	void append(const T& item);
	void prev();
	void next();
	T remove();
	void moveToFirst();
	void moveToLast();
	size_t getCurrentIndex() const;
	void moveToIndex(size_t index);
	const T& getValue() const;
	bool isEmpty() const;
	void toString();
};

template <typename T>

//returns the number of items in the database
//using the "size" method of the "list" class template
size_t MiniDB<T>:: size() const
{
	return this->db_store.size();
}

template <typename T>
//inserts a given item at where "cp" points at,
//and then resets cp to point at the new item
void MiniDB<T>::insert(const T& item)
{
	//if the database is empty, use "push_back" method
	//of the "list" class template
	//and then set cp to point at the new item
	if (db_store.empty())
	{
		db_store.push_back(item);
		current_position = db_store.end();
		current_position--;
	}

	//if the database is not empty, use "insert" method
	//of the "list" class template
	//and then set cp to point at the new item
	else
	{
		db_store.insert(current_position, item);
		current_position--;
	}
}

template <typename T>
//appends a given item at the end of the list
//using "push_back" method of the "list" class template
//and then resets cp to point at the new item
void MiniDB<T>::append(const T& item)
{
	db_store.push_back(item);
	current_position = db_store.end();
	current_position--;
}

template <typename T>
//moves cp one step backward
void MiniDB<T>::prev()
{
	try {
		if (!db_store.empty() && (db_store.begin()!= current_position))
		{
			current_position--;
		}

		else
		{
			//if the database is empty, 
			//an error is output
			if (db_store.empty())
			{
				throw std::logic_error("Cannot complete the operation. The database is empty.");
			}

			//if the cp points to the first position,
			//an error is output
			else
			{
				throw std::logic_error("Cannot complete the operation. The cp points to the first position.");
			}
		}
	}

	catch (std::logic_error& e)
	{
		cout << e.what() << endl;
	}
}

template <typename T>
//moves cp one step forward
void MiniDB<T>::next()
{
	try
	{
		if (!db_store.empty() && (--db_store.end() != current_position))
		{
			current_position++;
		}

		else
		{
			//if the database is empty, 
			//an error is output
			if (db_store.empty())
			{
				throw std::logic_error("Cannot complete the operation. The database is empty.");
			}

			//if the cp points to the last position,
			//an error is output
			else
			{
				throw std::logic_error("Cannot complete the operation. The cp points to the last position.");
			}
		}
	}

	catch (std::logic_error& e)
	{
		cout << e.what() << endl;
	}

}

template <typename T>
//removes and returns the item cp points at
T MiniDB<T>::remove()
{
	try
	{
		if (!db_store.empty())
		{
			T valueToRemove = *current_position;

			//if there is only one item,
			//the database becomes empty,
			//and the cp is reset to db_store.end()
			if (db_store.size() == 1)
			{
				this->db_store.clear();
			}

			//if cp corresponds to the last item,
			//it is reset to point at the item
			//before the one removed
			else if ((*current_position) == db_store.back())
			{
				current_position--;
				this->db_store.pop_back();
			}

			//default case: cp is is reset
			//to point at the item after the one removed
			else
			{
				current_position = db_store.erase(current_position);
			}

			return valueToRemove;
		}

		//if the database is empty, 
		//an error is output
		else
		{
			throw std::logic_error("Cannot complete the operation. The database is empty.");
		}
	}

	catch (std::logic_error& e)
	{
		cout << e.what() << endl;
	}

}

template <typename T>

//resets cp to represent the position
//of the first item in the database
void MiniDB<T>::moveToFirst()
{
	try
	{
		if (!db_store.empty())
		{
			current_position = this->db_store.begin();
		}

		//if the database is empty, 
		//an error is output
		else
		{
			throw std::logic_error("Cannot complete the operation. The database is empty.");
		}
	}

	catch (std::logic_error& e)
	{
		cout << e.what() << endl;
	}
}

template <typename T>
//resets cp to represent the position
//of the last item in the database
void MiniDB<T>::moveToLast()
{
	try
	{
		if (!db_store.empty())
		{
			current_position = db_store.end();
			current_position--;
		}

		//if the database is empty, 
		//an error is output
		else
		{
			throw std::logic_error("Cannot complete the operation. The database is empty.");
		}
	}

	catch (std::logic_error& e)
	{
		cout << e.what() << endl;
	}
}

template <typename T>
//returns the index of the item
//that cp points at; uses 0-based indexing
size_t MiniDB<T>::getCurrentIndex() const
{
	try
	{
		if (!db_store.empty())
		{
			typename std::list<T>::const_iterator first = db_store.begin();
			typename std::list<T>::const_iterator second = current_position;
			return std::distance(first, second);
		}

		else
		{
			//if the database is empty, 
			//an error is output
			throw std::logic_error("Cannot complete the operation. The database is empty.");
		}
	}

	catch (std::logic_error& e)
	{
		cout << e.what() << endl;
	}
}

template <typename T>
//sets cp to represent the item at the specified index;
//using "advance" uses 0-based indexing
void MiniDB<T>::moveToIndex(size_t index)
{
	try
	{
		if (!db_store.empty() && (index < this->db_store.size()))
		{
			if (index == 0)
			{
				current_position = this->db_store.begin();
			}

			else {
				current_position = this->db_store.begin();

				for (size_t i = 0; i < index; ++i)
				{
					advance(current_position, 1);
				}
			}
		}

		else
		{
			//if the database is empty, 
			//an error is output
			if (db_store.empty())
			{
				throw std::logic_error("Cannot complete the operation. The database is empty.");
			}

			//if the index exceeds the size of the database,
			//an error is output
			else
			{
				throw std::logic_error("Cannot complete the operation. The index exceeds the number of elements in the database.");
			}
		}
	}

	catch (std::logic_error& e)
	{
		cout << e.what() << endl;
	}
}

template <typename T>
//returns the value at the current position
const T& MiniDB<T>:: getValue() const
{
	try
	{
		if (!db_store.empty())
		{
			return *current_position;
		}

		else
		{
			//if the database is empty, 
			//an error is output
			throw std::logic_error("Cannot complete the operation. The database is empty.");
		}
	}

	catch (std::logic_error& e)
	{
		cout << e.what() << endl;
	}
}

template <typename T>
//an additional method of boolean type
//to test if the database is empty
bool MiniDB<T>:: isEmpty() const
{
	return db_store.empty();

}

template <typename T>
//prints all lines in the database
//preceding each line with the 1-based index of that line
void MiniDB<T>::toString()
{
	for (current_position = this->db_store.begin(); current_position != this->db_store.end(); ++current_position)
	{
		cout << (getCurrentIndex() + 1) << ": " << *current_position << endl;
	}
}
#endif /*MiniDB_H*/