/****************************************************************************
* Ben Pittman - David Nixon - Mike Chavez - Rizky Ramdhani
* CS 502A Winter 2017
* HW 4
* transactionfactory.h - Header file for TransactionFactory
*****************************************************************************/

#pragma once

#include "enums.h"

using namespace std;

/*
//---------------------------------------------------------------------------
                                Transaction Factory
A factory class used to instantiate empty derived Transaction objects

Implementation:
-Does not have ownership of Transaction objects instantiated.
-Does not deallocate dynamic memory
//---------------------------------------------------------------------------
*/

class Transaction;

class TransactionFactory {

public:
	TransactionFactory(); // default constructor
	TransactionFactory(const TransactionFactory &other); // copy constructor
	~TransactionFactory(); // destructor
    TransactionFactory& operator=(const TransactionFactory &other);

    //creates an empty Transaction object
    Transaction * create(TransactionType) const;  
};