/****************************************************************************
* Ben Pittman - David Nixon - Mike Chavez - Rizky Ramdhani
* CS 502A Winter 2017
* HW 4
* transaction.h - Header file for Transaction
*****************************************************************************/

#pragma once

#include <fstream>

using namespace std;

/*
//---------------------------------------------------------------------------
                                Transaction
Abstract class used in Command pattern implementation of Library system.

Features:
-setter for reference to Library
-contains a pure virtual execute method

Implementation:
-Does not deallocate dynamic memory
//---------------------------------------------------------------------------
*/

class Library;

class Transaction {

public:
    Transaction(); //default constructor
    Transaction(const Transaction &t); //copy constructor
    virtual ~Transaction(); // destructor
    Transaction & operator=(const Transaction &other); //assignment operator

    void setLibrary(Library *library); //library setter

    //virtual method to set member data from input file
    virtual void setDataFromFile(ifstream &) {};

    // pure virtual method for executing a transaction
    virtual void execute() const = 0;

    string getErrorMessage() const;  //getter for error

protected:
    Library *library;  //reference to Library

    //stores any function error messages for later output
    //if error is string() means no error has occurred
    string error;  
};