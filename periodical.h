/******************************************************************************
* Ben Pittman - David Nixon - Mike Chavez - Rizky Ramdhani
* CS 502A Winter 2017
* HW 4
* periodical.h - Header file for Periodical 
******************************************************************************/

#pragma once

#include "libitem.h"

using namespace std;

/*
//---------------------------------------------------------------------------
                                    Periodical
A data class used to represent Periodicals in a library.  Inherits from
LibItem class.

Features:
    -overrides Object's virtual print and getHashCode methods
    -getters and setters
    -comparison operators

Implementation:
    -Uses month, year and title to generate the instance's unique hash code.
    -Does not deallocate dynamic memory
//---------------------------------------------------------------------------
*/

class Periodical : public LibItem 
{

public:
    //Constructor
    Periodical();  //Default constructor
    Periodical(string title, CatalogType type, Format format, 
        int year, int month, int inventory);  //Constructor
    ~Periodical() {};  //Destructor
    Periodical(const Periodical&);  //Copy constructor
    Periodical& operator=(const Periodical&);  //Assignment operator

    //Comparison operators
    bool operator==(const Object&) const override;
    bool operator!=(const Object&) const override;
    bool operator<(const Object&) const override;
    bool operator>(const Object&) const override;
    bool operator<=(const Object&) const override;
    bool operator>=(const Object&) const override;

    //MUTATORS
    bool setYear(int);  //setter for year
    bool setMonth(int);  //setter for month

    //set data members using data from specific input file
    void setDataFromInitFile(ifstream &) override;

    //set data memebers using data from specific input file
    void setDataFromCommandFile(ifstream &) override;

    //ACCESSORS
    int getYear();  //getter for year
    int getMonth();  //getter for month

    //returns a unique integer to be used in HashTable hash()
    int getHashCode() const; 

    //overridden method
    //prints the content of this Periodical
    virtual ostream & print(ostream &) const override;

protected:
    int year;  //year published
    int month;  //month published

};

