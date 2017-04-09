/*
Rizky Ramdhani
CSS502
Assignment 4
displayerror.h - Header file for DisplayError
*/

#pragma once

#include "transaction.h"
#include <iostream>
#include <string>

using namespace std;

/*
//---------------------------------------------------------------------------
                            DisplayError

A Transaction Object used in Command Pattern.  Inherits from Transaction
abstract class.  Displays error messages in console, designed to work with
Librarian class.
//---------------------------------------------------------------------------
*/

class DisplayError : public Transaction
{
public:
    DisplayError(); //Default Constructor
    DisplayError(string); //constructor
    ~DisplayError();  //Destructor
    DisplayError(const DisplayError &); //Copy Constructor
    DisplayError & operator=(const DisplayError &); //Assignment Operator

    void setMessage(string);  //setter for message

    void execute() const override;  //execute override

protected:
    string message;  //used to store error messages
};
