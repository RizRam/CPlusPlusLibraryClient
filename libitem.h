/******************************************************************************
* Ben Pittman - David Nixon - Mike Chavez - Rizky Ramdhani
* CS 502A Winter 2017
* HW 4
* libitem.h - Header file for LibItem
******************************************************************************/

#pragma once

#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include "object.h"
#include "enums.h"

using namespace std;

/*
//---------------------------------------------------------------------------
                                   LibItem
Abstract class that represents items stored and managed in Library.
Inherits from Object abstract superclass.
Features:
    -getters and setters
    -comparison operators
    -Keeps track of all Patrons who currently have this LibItem checked out
Implementation
    -Uses STL list<Patron *> to keep track of Patrons
    -Does not deallocate Patrons contained in the list.
//---------------------------------------------------------------------------
*/

class Patron;

class LibItem : public Object {

public:
    //constructor
    LibItem();
    LibItem(string theTitle, CatalogType type, Format format, int inventory,
        int availableInventory);
    virtual ~LibItem();  //destructor
    LibItem(const LibItem&);  //copy constructor
    LibItem& operator=(const LibItem&);  //assignment operator

    //MUTATORS
    bool setTitle(string);  //sets title
    bool setTotalInventory(int);  //set total inventory
    bool setAvailableInventory(int);  //set available inventory
    bool setFormat(Format);  //set format
    bool setType(CatalogType);  //set CatalogType

    bool checkIn(Patron *);  //check in from Patron
    bool checkOut(Patron *);  //check out to Patron

    //set data members using data from specific input file
    virtual void setDataFromInitFile(ifstream &) = 0;

    //set data memebers using data from specific input file
    virtual void setDataFromCommandFile(ifstream &) = 0;
    
    //ACCESSORS
    string getTitle() const;  //returns title
    int getTotalInventory() const;  //returns total inventory
    int getAvailableInventory() const;  //returns available inventory
    Format getFormat() const; //return Format
    CatalogType getType() const;  //return type

protected:
    int availableInventory;  //available for check out
    int totalInventory;  //total inventory
    string title;  //title of LibItem
    Format format;  //format of item (hardcover, etc.)
    CatalogType type;  //type of item (fiction, etc.)

    // List of Patrons who currently have a book checked out
    list<Patron*> patronList;

private:
    void clearPatronList();  //clears the contents of patronList
};




