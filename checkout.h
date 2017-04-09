/****************************************************************************
* Ben Pittman - David Nixon - Mike Chavez - Rizky Ramdhani
* CS 502A Winter 2017
* HW 4
* checkout.h - Header file for CheckOut
*****************************************************************************/

#pragma once

#include "transaction.h"

/*
//---------------------------------------------------------------------------
                                    CheckOut

An Object used in Command Pattern.  Inherits from Transaction abstract class.
Talks to Library to execute check outs of LibItems to Patrons.
//---------------------------------------------------------------------------
*/

class Patron;
class LibItem;

class CheckOut : public Transaction {

public:
    CheckOut();  //Default constructor
	CheckOut(const CheckOut &); // copy constructor
	~CheckOut(); // destructor
    CheckOut & operator=(const CheckOut &other);  //Assignment operator

    //MUTATORS
    void setItem(LibItem *);  //setter for item
    void setPatron(Patron *);  //setter for Patron

    //set data members using input file
    void setDataFromFile(ifstream &) override;

	// performs a check-out transaction
	void execute() const; 

private:
	LibItem* item; // pointer to Library Item that will be checked-in
	Patron* patron; // pointer to Patron who will check-in 
};