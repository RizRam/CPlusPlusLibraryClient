/******************************************************************************
* Ben Pittman - David Nixon - Mike Chavez - Rizky Ramdhani
* CS 502A Winter 2017
* HW 4
* patron.h - Header file for Patron
******************************************************************************/

#pragma once

#include <string>
#include <list>
#include <fstream>
#include "object.h"

using namespace std;

class LibItem;

/*
//---------------------------------------------------------------------------
                                Patron
Data class used to represent Patrons to the Library.  Inherits from Object.

Features:
    -getters and setters
    -comparison operators
    -get hash code  (unique int for each instance)
    -keeps track of check out and check in records of the Patron
    -output contents to console, including all recoreds of checkouts
Implementation:
    -Requires ID to instantiate.
    -patronID is read-only
    -overrides Object's virtual print method.
    -returns the patronID for unique hash code.
    -stores patron check out history using STL list<CheckOutRecord>
    -CheckOutRecord is a protected internal struct that stores a pointer
     to LibItem that was checked out and a flag that determines whether the
     item is still currently being checked out.
    -Patron does not deallocate the dynamic LibItem memory object stored
     in the list<CheckOutRecord>.
//---------------------------------------------------------------------------
*/

class Patron : public Object {
public:
    //Constructor
    Patron(int ID);  //Constructor
    Patron(int ID, string firstName, string lastName);
    ~Patron();  //Destructor
    Patron(const Patron&);  //Copy constructor
    Patron& operator=(const Patron&);  //Assignment operator

    //Comparison operators
    virtual bool operator==(const Object&) const override;
    virtual bool operator!=(const Object&) const override;
    virtual bool operator<(const Object&) const override;
    virtual bool operator>(const Object&) const override;
    virtual bool operator<=(const Object&) const override;
    virtual bool operator>=(const Object&) const override;

    //MUTATORS
    bool setFirstName(string firstName);  //setter for firstName
    bool setLastName(string lastName);  //setter for lastName
    bool checkIn(LibItem *);  //check in a LibItem
    bool checkOut(LibItem *);  //check out a LibItem
    void setDataFromFile(ifstream &);  //set data members using input file.

    //ACCESSORS
    int getPatronID() const;  //setter for patronID
    string getFirstName() const;  //setter for firstName
    string getLastName() const;  //setter for lastName

    //returns a unique integer to be used in HashTable hash()
    int getHashCode() const;  

    //prints the contents of Patron
    ostream & print(ostream &) const;

protected:

//---------------------------------------------------------------------------
//                          CheckOutRecord
//struct to store a Patron's individual check out record
    struct CheckOutRecord 
    {
        LibItem* item;  //Library Item checked out

        //flag to show whether item was checked out or returned
        bool checkOut;  
    };
//---------------------------------------------------------------------------


    // data members of a patron
    int patronID;  //read-only
    string firstName;
    string lastName;

    //list of CheckOutRecord, stores most recent Check outs in the front
    //of the list.
    list<CheckOutRecord> history;

    void clearHistory();  //clears the contents of history
    
};

