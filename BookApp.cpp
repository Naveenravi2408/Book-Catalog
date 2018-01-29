#include "Book.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

void start(char const command, istream &input, vector<Book>& catalog);

int add_book(istream &input, vector<Book>& catalog);   // for "+"
void get_info(istream &input, vector<Book>& catalog);  // for "?"
int remove_book(istream &input, vector<Book>& catalog); // for "-"

bool search_author(string author_name, const vector<Book>& catalog); // linear search
bool search_category(string category_type, const vector<Book>& catalog); // linear search
int find_book_by_isbn(const string isbn, const vector<Book>& catalog);  // binary search

void find_book_by_author(string author, const vector<Book>& catalog);
void find_book_by_category(string category, const vector<Book>& catalog);

const string INPUT_FILE_NAME = "commands.in";

/**
 * The main. Open the command input file and loop to process commands.
 */
int main()
{
    // Open the input file.
    ifstream input;
    input.open("commands.in");
    if (input.fail())
    {
        cout << "Failed to open " << INPUT_FILE_NAME<< endl;
        return -1;
    }

    vector<Book> catalog;  // book catalog

    char command;
    input >> command;  // read the first command

    /**
     * Loop to read commands until the end of file.
     */
    while (!input.fail())
    {
        cout << endl << command << " ";
        start(command, input, catalog);		//function which processes the operation of each command
        input >> command;					//read the next command
    }
    return 0;
}


/*
 * Start processing the extracted command from the file
 * @param command is the input command
 * @param istream is the input data stream
 * @param catalog is the vector of info about books stored
 */
void start(char const command, istream &input, vector<Book>& catalog)
{
	string isbn;
	Book bk;

	//Evaluate the command
	switch(command)
	{
	case '+':
		add_book(input, catalog);
		break;

	case '-':
		remove_book(input, catalog);
		break;

	case '?':
		get_info(input, catalog);
		break;

	default:
		input >> isbn;
		cout << "*** Invalid command ***"<<endl;
		break;
	}
}

/*
 * "+ operator"
 * Read the new book and add it to the catalog vector
 * as and when a book is inserted sort it in ascender order of isbn
 * @param istream the input data stream
 * @param catalog the vector of book records
 * @param isbn is the book ISBN number
 * @param index checks the index value during sorting
 */
int add_book(istream &input, vector<Book>& catalog)
{
	int index;
	string isbn;
	Book bk;
	input >> bk;          //read the new book to be inserted
	isbn = bk.get_isbn();

	if(catalog.size() == 0)    // the first element of the vector (catalog)
	{
		catalog.push_back(bk);
		index = 0;
		cout <<"Inserted at index "<<index<< ": "<< catalog[index] <<endl;
		return index;
	}

	// check  if the new isbn is greater than all the other isbn in the catalog
	// increment index until a lesses isbn is found in the catalog
	for(index=0; (index< catalog.size())&&(isbn > catalog[index].get_isbn()); index++)

	// check for a duplicate isbn
	for(unsigned int i=0; i<catalog.size(); i++)
		{
			if(isbn == catalog[i].get_isbn())
			{
				cout <<"Inserted at index "<<index+1<< ": "<< catalog[index+1]<<endl;
				cout << "*** Duplicate ISDN ***" << endl;
				return index;
			}
		}

	// Insert the new book
	catalog.insert(catalog.begin() + index, bk);
	cout <<"Inserted at index "<<index<< ": "<< catalog[index]<<endl;
	return index;
}

/*
 * Fetch the information about the book according to the search input
 * @param istream the input data stream
 * @param catalog is the vector of all the book records
 * @param isbn is the ISBN number of the book
 */
void get_info(istream &input, vector<Book>& catalog)
{
	string temp;
	getline(input, temp); // read the entire line after "?"

	if(temp.empty())   // check if the line after "?" is empty
	{
		// if empty print all the books in the catalog
		cout << "All books in the catalog:"<<endl;
			for(unsigned int i=0; i<catalog.size(); i++)
				{
					cout <<catalog[i] << endl;
				}
	}

	// if there is a statement after "?"
	else{

		// check if the statement has a string "author"
		if (temp.find("author") != string::npos)
		{
			bool author_found = false;
			int pos = temp.find("=");
			string author_name = temp.substr(pos+1);
			author_found = search_author(author_name, catalog); // linear search to see if the required author is in the catalog
			if(author_found == true)
			{
				find_book_by_author(author_name,catalog);  // search the catalog for the book which belongs to the above author
			}
			else {
				cout<< "Author name " << author_name << " not present in the directory" << endl;
			}
		}

		// check if the statement has a string "category"
		else if (temp.find("category") != string::npos)
		{
			bool category_found = false;
			int pos = temp.find("=");
			string category_type = temp.substr(pos+1);
			category_found = search_category(category_type, catalog); // linear search to see if the required category is in the catalog
			if(category_found == true)
			{
				find_book_by_category(category_type,catalog); // search the entire catalog for this category
			}
			else {
				cout<< "Category type " << category_type << " not present in the directory" << endl;
			}
		}

		// check if the statement has a string "isbn"
		else if (temp.find("isbn") != string::npos)
		{
			int pos = temp.find("=");
			string sub = temp.substr(pos+1);
			int val = find_book_by_isbn(sub, catalog);  //Binary search to see if the required isbn is in the catalog

			cout << "Book with ISBN " << sub <<":" << endl;
			if (val != -1)
			{
			cout << catalog[val] << endl;
			}
		}
		else{
			cout << temp << " Invalid search criteria" << endl;
		}
	}
}

/*
 * "-" operator
 * Remove the book in the catalog
 * check for the given isbn number in the catalog and remove the book
 * if the given isbn is not found in the catalog print "book not found"
 * @param istream the input data stream
 * @param catalog is the vector of all the book records
 */
int remove_book(istream &input, vector<Book>& catalog)
{
	string isbn;
	unsigned int i;
	input >> isbn;
	for (i=0; i<catalog.size(); i++)  // search entire catalog for the given isbn
			{
				if(isbn == catalog[i].get_isbn())  // if the given isbn matches the isbn in the catalog
				{
					cout << "Removed "<<catalog[i] <<endl;
					catalog.erase(catalog.begin() + i);
					return i;
				}
			}
	if(i == catalog.size()) // if there is no match in the catalog for the given isbn
	{
		cout << "Removed Book{ISBN="<<isbn<<", last=, first=, title=, category=none}"<< endl;
		cout << "*** Book not found ***"<<endl;
		return i;
	}
	return i;
}

/**
 * Find the book in the catalog with the given ISBN.
 * Used binary search.
 * @param isbn the ISBN.
 * @param catalog the vector of book records.
 * @return the vector index of the book if found, else return -1.
 */
int find_book_by_isbn(const string isbn, const vector<Book>& catalog)
{
	int low = 0;
	int high = catalog.size()-1;

	while (low <= high)
	{
		int mid = (low + high)/2;  // get the midpoint of the subrange

		if(isbn == catalog[mid].get_isbn())  // found the target value
		{
			return mid;
		}

		else if (isbn < catalog[mid].get_isbn())  // search the first half
		{
			high = mid - 1;
		}
		else{
			low = mid+1;           // search the second half
		}
	}
	return -1;          // target value is not in the vector
	}

/*
 * linear search for the given author
 * if author match found then return bool value true else return false
 * @param author_name is the name of the author to be searched
 * @param catalog is the vector of catalog which contains all the books
 */
bool search_author(string author_name, const vector<Book>& catalog)
{
	bool author_found = false;
		for(unsigned int i=0; i<catalog.size(); i++) // linear search the entire catalog
		{
			if(author_name == catalog[i].get_last()) // if match found
			{
				author_found = true;
				return author_found;
			}
		}
	return author_found;
}

/*
 * After confirming the existance of the author in the catalog
 * search the entire catalog for the books of the author
 * @param author name of the author
 * @param catalog is the vector of catalog which contains all the books
 */
void find_book_by_author(string author, const vector<Book>& catalog)
{
	cout << "Books by author " << author << ":" <<endl;
	for(unsigned int i=0; i<catalog.size(); i++)  // search the catalog for books with the required author name
				{
					if(author == catalog[i].get_last()) // if match found print out the books
					{
						cout << catalog[i]<<endl;
					}
				}
}

/*
 * linear search for the given category
 * if category match found then return bool value true else return false
 * @param Category_type is the type of category to be searched
 * @param catalog is the vector of catalog which contains all the books
 */
bool search_category(string category_type, const vector<Book>& catalog)
{
	bool category_found = false;
	for(unsigned int i=0; i<catalog.size(); i++) // linear search the entire catalog for the required category
	{
		if(category_type == catalog[i].get_category()) // if required match found
		{
			category_found = true;
			return category_found;
		}
	}
	return category_found;
}

/*
 * After confirming the existance of the required category in the catalog
 * search the entire catalog for the books of a particular category
 * @param category is the type of the category
 * @param catalog is the vector of catalog which contains all the books
 */
void find_book_by_category(string category, const vector<Book>& catalog)
{
	cout << "Books in category " << category <<":" <<endl;
	for(unsigned int i=0; i<catalog.size(); i++)  // search the entire catalog with the required category
			{
				if(category == catalog[i].get_category()) // if match found print all the books related to that category
				{
					cout << catalog[i]<<endl;
				}
			}
}





