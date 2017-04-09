/****************************************************************************
* Ben Pittman - David Nixon - Mike Chavez - Rizky Ramdhani
* CS 502A Winter 2017
* HW 4
* checkin.h - Header file for CheckIn
*****************************************************************************/

#pragma once

#include "transaction.h"

/*
//---------------------------------------------------------------------------
                                      CheckIn

A Transaction Object used in Command Pattern.  Inherits from Transaction 
abstract class.  Talks to library to check in library items from patrons.
//---------------------------------------------------------------------------
*/

class LibItem;
class Patron;

class CheckIn : public Transaction {

public:
    CheckIn();  //Default constructor
	CheckIn(const CheckIn &); // copy constructor
	~CheckIn(); // destructor
    CheckIn& operator=(const CheckIn &);  //assignment operator

    //MUTATORS
    void setItem(LibItem *); //setter for item
    void setPatron(Patron *);  //setter for patron

    //sets data from input file
    void setDataFromFile(ifstream &) override;

	// performs a check-in transaction
	void execute() const; 

private:
	LibItem *item; // pointer to Library Item that will be checked-ins
	Patron *patron; // pointer to Patron who will check-in 
};

