#/******************************************************************************
* Ben Pittman - David Nixon - Mike Chavez - Rizky Ramdhani
* CS 502A Winter 2017
* HW 4
* transactionfilereader.h - Header file for TransactionFileReader
******************************************************************************/

#pragma once

#include "transactionfactory.h"
#include <fstream>

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
    -Uses PatronFactory, LibItemFactory, and TransactionFactory to instantiate
     Transaction objects.
//---------------------------------------------------------------------------
*/

class Librarian;
class Transaction;
class LibItem;
class ChildrensBook;
class FictionBook;
class Periodical;

class TransactionFileReader {

public:
    TransactionFileReader(string fileName, Librarian *); //Constructor
    ~TransactionFileReader();  //Destructor
    TransactionFileReader(const TransactionFileReader&);  //Copy Constructor

    //Assignment operator
    TransactionFileReader& operator=(const TransactionFileReader&);

    //Parses input file and populates Librarian with Transactions
    void parseAndPopulateLibrarian() const; 
    //void parseAndPopulateLibrarianAlt() const;

private:

    string fileName;  //filePath of input file
    Librarian *librarian;  //reference to Librarian

    //factory to create empty Transaction objects
    TransactionFactory factory;  

    //Transaction * createCheckIn(ifstream &) const;  //instantiate CheckIn
    //Transaction * createCheckOut(ifstream &) const;  //instantiate CheckOut

    ////instantiate DisplayPatronHistory
    //Transaction * createPatronHistory(ifstream &) const;

    ////instantiate DisplayInventory
    //Transaction * createDisplay() const;

    //LibItem * createLibItem(ifstream &) const;  

    ////set the member data of ChildrensBook with contents of input file
    //void setChildrensBookData(ChildrensBook *, ifstream &) const;

    ////set the member data of FictionBook with contents of input file
    //void setFictionBookData(FictionBook *, ifstream &) const;

    ////set the member data of Periodical with contents of input file
    //void setPeriodicalData(Periodical *, ifstream &) const;
};
