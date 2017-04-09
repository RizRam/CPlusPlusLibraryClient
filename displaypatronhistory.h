/****************************************************************************
* Ben Pittman - David Nixon - Mike Chavez - Rizky Ramdhani
* CS 502A Winter 2017
* HW 4
* displaypatronhistory.h
* DisplayPatronHistory instructs the library to execute its function for 
* displaying a given patron's transaction history with the library. The 
* constructor instantiates a pointer to a Patron object containing the info 
* for the patron whose history will be displayed.
*
* Features:
*	-Execute, a method to instruct the library to display a patron's history
*****************************************************************************/
#pragma once

#include "transaction.h"

/*
//---------------------------------------------------------------------------
                                DisplayPatronHistory

A Transaction class used in Command Pattern.  Inherits from Transaction
abstract class.  Retrieves a patron from Library and outputs its check out
history.
//---------------------------------------------------------------------------
*/

class Patron;

class DisplayPatronHistory : public Transaction {
public:
    DisplayPatronHistory();  //Default Constructor
	DisplayPatronHistory(const DisplayPatronHistory &other); // copy constructor
	~DisplayPatronHistory(); // destructor
    DisplayPatronHistory& operator=(const DisplayPatronHistory &other);

    //MUTATORS
    void setPatron(Patron *);  //setter for patron

    //set data from input file
    void setDataFromFile(ifstream &) override;

	// displays the patron's history
	void execute() const; 

private:
    Patron *patron;  //Patron history to be displayed
};