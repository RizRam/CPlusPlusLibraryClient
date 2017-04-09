/******************************************************************************
* Ben Pittman - David Nixon - Mike Chavez - Rizky Ramdhani
* CS 502A Winter 2017
* HW 4
* fictionbook.h - Header file for FictionBook
******************************************************************************/

#pragma once

#include "book.h"

using namespace std;

/*
//---------------------------------------------------------------------------
                                FictionBook
Class that represents fiction books to be stored in Library.
Inherits from Book abstract class.

Features:
    -getter and setter methods
    -comparison operators
    -overrides Object's print and  getHashCode functions

Implementation:
    -Uses title and author to determine an instance's unique hash code
    -Does not deallocate dynamic memory

//---------------------------------------------------------------------------
*/

class FictionBook : public Book {

public:
    //Constructor
    FictionBook();
    FictionBook(string title, CatalogType type, Format format,
        string author, int year, int inventory);
    ~FictionBook() {};  //Destructor
    FictionBook(const FictionBook &);  //Copy constructor
    FictionBook& operator=(const FictionBook &);  //Assignment operator

    //Comparison operators
    bool operator<(const Object &) const override;
    bool operator>(const Object &) const override;
    bool operator<=(const Object &) const override;
    bool operator>=(const Object &) const override;

    //set data members using data from specific input file
    void setDataFromInitFile(ifstream &) override;

    //set data memebers using data from specific input file
    void setDataFromCommandFile(ifstream &) override;

    //return the hashcode to be used in HashTable hash() function
    int getHashCode() const override;
};



