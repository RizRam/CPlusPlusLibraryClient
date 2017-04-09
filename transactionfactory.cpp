/*
Rizky Ramdhani
CSS502
Assignment 4
transactionfactory.cpp - Impementation file for TransactionFactory
*/

#include "transactionfactory.h"
#include "librarian.h"
#include "checkout.h"
#include "checkin.h"
#include "displayinventory.h"
#include "displaypatronhistory.h"
#include "transaction.h"

//---------------------------------------------------------------------------
//Default Constructor
TransactionFactory::TransactionFactory() {}

//---------------------------------------------------------------------------
//Copy Constructor
TransactionFactory::TransactionFactory(const TransactionFactory & other) {}

//---------------------------------------------------------------------------
//Destructor
TransactionFactory::~TransactionFactory() {}

//---------------------------------------------------------------------------
//Assignment operator
TransactionFactory & TransactionFactory::operator=(
    const TransactionFactory & other)
{
    return *this;
}

//---------------------------------------------------------------------------
//create
//Creates a new derived class of Transaction depending on the argument.
//Parameters:
//  -type: TransactionType enum that designates which derived class 
//         to instantiate
//Returns:
//  A pointer to a newly created Transaction object.
Transaction * TransactionFactory::create(TransactionType type) const
{
    switch (type)
    {
    case C:
        return new CheckOut();
        break;
    case R:
        return new CheckIn();
        break;
    case H:
        return new DisplayPatronHistory();
        break;
    case D:
        return new DisplayInventory();
        break;
    default:
        return nullptr;
        break;
    }
}

