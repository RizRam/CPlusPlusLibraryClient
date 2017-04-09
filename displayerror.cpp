/*
Rizky Ramdhani
CSS 502
Assignment 4
displayerror.cpp - Implementation file for DisplayError
*/

#include "displayerror.h"
#include <iostream>

//---------------------------------------------------------------------------
//Default constructor
DisplayError::DisplayError() : Transaction() 
{
    message = string();
}

//---------------------------------------------------------------------------
//Constructor
DisplayError::DisplayError(string message) : Transaction()
{
    this->message = message;
}

//---------------------------------------------------------------------------
//Destructor
DisplayError::~DisplayError() {}

//---------------------------------------------------------------------------
//Copy constructor
DisplayError::DisplayError(const DisplayError &other) : Transaction(other)
{
    this->message = other.message;
}

//---------------------------------------------------------------------------
//Assignment Operator
DisplayError & DisplayError::operator=(const DisplayError &other)
{
    if (this != &other)
    {
        Transaction::operator=(other);
        this->message = other.message;
    }
    
    return *this;
}

//---------------------------------------------------------------------------
//setMessage
//setter for message
//Parameters:
//  -s: (string) error message to be displayed in console
void DisplayError::setMessage(string s)
{
    message = s;
}

//---------------------------------------------------------------------------
//execute
//Displays message in console
void DisplayError::execute() const
{
    cout << message << endl;
}


