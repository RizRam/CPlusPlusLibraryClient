/*
Rizky Ramdhani
CSS502
Assignment 4
transaction.cpp - Implementation file for Transaction
*/

#include "transaction.h"
#include "library.h"

//---------------------------------------------------------------------------
//Default Constructor
Transaction::Transaction()
{
    this->library = nullptr;
    error = string();
}

//---------------------------------------------------------------------------
//Copy constructor
//shallow copy
Transaction::Transaction(const Transaction &other)
{
    this->library = other.library;
    this->error = other.error;
}

//---------------------------------------------------------------------------
//Destructor
//Not responsible for deallocating Library
Transaction::~Transaction() 
{
    this->library = nullptr;
}

//---------------------------------------------------------------------------
//assignment operator
//shallow copy
Transaction & Transaction::operator=(const Transaction & other) 
{
    if (this != &other)
    {
        this->library = other.library;
        this->error = other.error;
    }

    return *this;
}

//---------------------------------------------------------------------------
//setLibrary
//Setter for library
//Parameters:
//  -library: (Library) Pointer to Library to be set into this object.
void Transaction::setLibrary(Library * library)
{
    this->library = library;
}

//---------------------------------------------------------------------------
//getErrorMessage
//Getter for errorMessage
//Return:
//  (string) the contents of error message
string Transaction::getErrorMessage() const
{
    return error;
}
