/*
 * Book.h
 *
 *  Created on: Sep 30, 2017
 *      Author: naveen
 */

#ifndef BOOK_H_
#define BOOK_H_

#include <string>
using namespace std;

/**
 * The Book class.
 */
class Book
{
public:

	//Constructors
    Book();
    Book(string isbn);
    Book(string isbn, string last, string first, string title, string category);

    //Destructor
    ~Book();

    // Getters
    string get_isbn() const;
    string get_last() const;
    string get_first() const;
    string get_title() const;
    string get_category() const;

    // Overloaded I/O stream operators
    friend istream& operator >> (istream& ins, Book& bk);
    friend ostream& operator << (ostream& outs, const Book& bk);

private:
    string isbn;  // ISBN-Number
    string first; // first name
    string last;  // last name
    string title; // title of the book
    string category; // category of the book
};

#endif /* BOOK_H_ */
