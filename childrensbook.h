/******************************************************************************
* Ben Pittman - David Nixon - Mike Chavez - Rizky Ramdhani
* CS 502A Winter 2017
* HW 4
* childrensbook.h - Header file for ChildrensBook
******************************************************************************/

#pragma once

#include "book.h"

/*
//---------------------------------------------------------------------------
                                    ChildrensBook

Class that represents Children's Books in a library.  Inherits from Book
abstract class.

Features:
    -Getters and Setters
    -Comparison operators
    -overrides Object's getHashCode() function.

Implementation:
    -Uses title and author to determine an instance's unique hash code.
    -Does not deallocate dynamic memory.
//---------------------------------------------------------------------------
*/

using namespace std;

class ChildrensBook : public Book {

public:
    //constructor
    ChildrensBook();
    ChildrensBook(string title, CatalogType type, Format format, 
        string author, int year, int inventory);
    ~ChildrensBook() {};  //destructor
    ChildrensBook(const ChildrensBook&);  //copy constructor
    ChildrensBook& operator=(const ChildrensBook&);  //assignment operator

    //comparison operators
    bool operator<(const Object&) const override;
    bool operator>(const Object&) const override;
    bool operator<=(const Object&) const override;
    bool operator>=(const Object&) const override;

    //set data members using data from specific input file
    void setDataFromInitFile(ifstream &) override;

    //set data memebers using data from specific input file
    void setDataFromCommandFile(ifstream &) override;

    //return the hashcode to be used in HashTable hash() function
    int getHashCode() const;
};



