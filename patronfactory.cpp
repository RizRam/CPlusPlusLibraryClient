/*
Rizky Ramdhani
CSS502
Assignment 4
patronfactory.cpp - Implementation file for PatronFactory
*/

#include "patronfactory.h"
#include "patron.h"

//---------------------------------------------------------------------------
//Default constructor
PatronFactory::PatronFactory() {}

//---------------------------------------------------------------------------
//Copy constructor
PatronFactory::PatronFactory(const PatronFactory & otherPatronFactory) {}

//---------------------------------------------------------------------------
//Destructor
PatronFactory::~PatronFactory() {}

//---------------------------------------------------------------------------
//Assignment Operator
PatronFactory & PatronFactory::operator=(const PatronFactory &)
{
    return *this;
}

//---------------------------------------------------------------------------
//create
//Returns a pointer a new Patron object.  Factory has no ownership of
//newly created object.
Patron * PatronFactory::create(int ID) const
{
    return new Patron(ID);
}
