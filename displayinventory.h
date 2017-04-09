/****************************************************************************
* Ben Pittman - David Nixon - Mike Chavez - Rizky Ramdhani
* CS 502A Winter 2017
* HW 4
* displayinventory.h - Header file for DisplayInventory
*****************************************************************************/

#pragma once

#include "transaction.h"
#include "enums.h"

/*
//---------------------------------------------------------------------------
                                    DisplayInventory

A Transaction class used in Command Pattern.  Inherits from Transaction
abstract class.  Talks to Library to execute display of Library's catalogs
//---------------------------------------------------------------------------
*/

class DisplayInventory : public Transaction {
public:
	DisplayInventory(); // default constructor
	DisplayInventory(const DisplayInventory &); // copy constructor
    ~DisplayInventory(); // destructor
    DisplayInventory& operator=(const DisplayInventory& other);

	// displays the library's inventory
	void execute() const; 

private:
    //prints columns based on CatalogType
    void printColumns(CatalogType) const;
};