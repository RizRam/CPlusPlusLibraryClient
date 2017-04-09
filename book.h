/******************************************************************************
* Ben Pittman - David Nixon - Mike Chavez - Rizky Ramdhani
* CS 502A Winter 2017
* HW 4
* book.h - Header file for Book
******************************************************************************/

#pragma once

#include "libitem.h"

using namespace std;

/*
//---------------------------------------------------------------------------
                                    Book
Abstract class that represents Books stored in a library.  Inherits from
LibItem class.
Features:
    -Getters and Setters
    -Comparison operators
    -Print
//---------------------------------------------------------------------------
*/

class Book : public LibItem {

public:
    //constructor
    Book();
    Book(string title, CatalogType type, Format format, string author, 
         int theYear, int inventory);
    virtual ~Book() {}  //destructor
    Book(const Book&);  //copy constructor
    Book& operator=(const Book&);  //assignment operator

    virtual bool operator==(const Object&) const override;
    virtual bool operator!=(const Object&) const override;

    //MUTATORS
    bool setAuthor(string);  //set Author
    bool setYear(int);  //set year

    //ACCESSORS
    string getAuthor() const;  //return author
    int getYear() const;  //return year

    virtual ostream & print(ostream &) const;  //prints the contents of Book

protected:
    string author;
    int year;

    string getFormatAsString(Format) const;
};



