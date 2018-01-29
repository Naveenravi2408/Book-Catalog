/*
 * Book.cpp
 *
 *  Created on: Sep 30, 2017
 *      Author: naveen
 */

#include "Book.h"
#include <string>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

/*
 * Default constructor
 */
Book::Book()
{
	isbn = "";
	last = "";
	first = "";
	category = "NONE";
}

/*
 * Constructor
 */
Book::Book(string isbn_num, string last_name, string first_name, string title_is, string category_is)
{
	isbn = isbn_num;
	last = last_name;
	first = first_name;
	title = title_is;
	category = category_is;
}

/*
 * Constructor when only isbn is given as input
 */
Book::Book(string isbn_num)
{
	isbn = isbn_num;
	last = "";
	first = "";
	title = "";
	category = "";
}

/*
 * Destructor
 */
Book::~Book()
{}

/*
 * Getter
 * @return the isbn number
 */
string Book::get_isbn() const
{
	return isbn;
}

/*
 * Getter
 * @return the last name
 */
string Book::get_last() const
{
	return last;
}

/*
 * Getter
 * @return the first name
 */
string Book::get_first() const
{
	return first;
}

/*
 * Getter
 * @return the book title
 */
string Book::get_title() const
{
	return title;
}

/*
 * Getter
 * @return the category type
 */
string Book::get_category() const
{
	return category;
}

/*
 * Overloaded output stream operator
 * @param ostream the output stream
 * @param bk the book to output
 * @return the output stream
 */
ostream& operator <<(ostream& outs, const Book& bk)
{
	outs << "Book{ISBN=" << bk.isbn << ", last=" << bk.last << ", first=" << bk.first
			<< ", title=" << bk.title << ", category=" << bk.category << "}";
	return outs;
}

/*
 * Overloaded input stream extraction operator. Reads from a .in file
 * @param istream the input stream
 * @param bk the book to input
 * @return the input stream
 */
istream& operator >>(istream& ins, Book& bk)
{
	string temp;

	getline(ins, bk.isbn, ' ');
	getline(ins, bk.isbn, ',');

	getline(ins, bk.last, ',');
	getline(ins, bk.first, ',');

	getline(ins, bk.title, ',');

	ins >> bk.category;

	return ins;
}
