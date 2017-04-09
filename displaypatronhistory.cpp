/*
Rizky Ramdhani
CSS502
Assignment 4
displaypatronhistory.cpp - Implementation file for DisplayPatronHistory
*/

#include "displaypatronhistory.h"
#include "patron.h"
#include "library.h"
#include "patronfactory.h"

//---------------------------------------------------------------------------
//Default Constructor
DisplayPatronHistory::DisplayPatronHistory() : Transaction()
{
    patron = nullptr;
}

//---------------------------------------------------------------------------
//Copy constructor
//Shallow copy
DisplayPatronHistory::DisplayPatronHistory(
    const DisplayPatronHistory &other) : Transaction(other)
{
    this->patron = other.patron;
}

//---------------------------------------------------------------------------
//Destructor
//Responsible for deallocating dynamic Patron object stored in memory
DisplayPatronHistory::~DisplayPatronHistory()
{
    delete patron;
    patron = nullptr;
    library = nullptr;
}

//---------------------------------------------------------------------------
//Assigment operator
//Shallow copy
DisplayPatronHistory & DisplayPatronHistory::operator=(
    const DisplayPatronHistory & other)
{
    if (this != &other) //check if same memory address
    {
        Transaction::operator=(other);
        this->patron = other.patron;
    }

    return *this;
}

//---------------------------------------------------------------------------
//setPatron
//sets Patron passed in argument to patron
//Parameters:
//  -patron: (Patron*) Pointer to Patron to be assigned to this object
void DisplayPatronHistory::setPatron(Patron *patron)
{
    this->patron = patron;
}

//---------------------------------------------------------------------------
//setDataFromFile
//sets data member using contents from input file
//Example Input
//  1111
//Parameters:
//  -inFile: (ifstream) input file to be read from. input file must be valid
void DisplayPatronHistory::setDataFromFile(ifstream &inFile)
{
    int patronID;
    inFile >> patronID;

    PatronFactory pf;
    patron = pf.create(patronID);
}

//---------------------------------------------------------------------------
//execute
//Calls library to display Patron history
void DisplayPatronHistory::execute() const
{
    //get actual Patron
    Patron *actualPatron = library->findPatron(*patron);
    if (actualPatron == nullptr)  //if Patron not found
    {
        cout << "Patron does not exist in the system." << endl;
        return;
    }

    //display patron
    cout << *actualPatron << endl;

    actualPatron = nullptr;
}