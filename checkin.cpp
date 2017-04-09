/*
Rizky Ramdhani
CSS502
Assignment 4
checkin.cpp - Implementation file for CheckIn
*/

#include "checkin.h"
#include "patron.h"
#include "patronfactory.h"
#include "libitem.h"
#include "libitemfactory.h"
#include "library.h"
#include <sstream>

//---------------------------------------------------------------------------
//Default constructor
CheckIn::CheckIn() : Transaction() 
{
    item = nullptr;
    patron = nullptr;
}

//---------------------------------------------------------------------------
//Copy constructor
CheckIn::CheckIn(const CheckIn &other) : Transaction(other)
{
    this->item = other.item;
    this->patron = other.patron;
}

//---------------------------------------------------------------------------
//Destructor
//Responsible for deallocating Patron LibItem objects
CheckIn::~CheckIn()
{
    delete patron;
    patron = nullptr;

    delete item;
    item = nullptr;

    library = nullptr;
}

//---------------------------------------------------------------------------
//Assignment operator
CheckIn & CheckIn::operator=(const CheckIn &other)
{
    if (this != &other)
    {
        Transaction::operator=(other);
        this->item = other.item;
        this->patron = other.patron;
    }

    return *this;
}

//---------------------------------------------------------------------------
//setItem
//Sets item to LibItem passed in argument
//Parameters:
//  -item: (LibItem*) pointer to LibItem to be assigned to this object
void CheckIn::setItem(LibItem *item)
{
    this->item = item;
}

//---------------------------------------------------------------------------
//setPatron
//Sets patron to Patron passed in argument
//Parameters:
//  -patron: (Patron*) Pointer to Patron to be assigned to this object
void CheckIn::setPatron(Patron *patron)
{
    this->patron = patron;
}

//---------------------------------------------------------------------------
//setDataFromFile
//Sets data members using content from an input file
//Example Input:
//  8888 F H Forster E. M., The Longest Journey,
//  1111 P H 2010 1 Communications of the ACM,
//  1111 Y H Danny Dunn & the Homework Machine, Williams Jay,
//Parameters:
//  -inFile: (ifstream) input file used for parsing.
void CheckIn::setDataFromFile(ifstream &inFile)
{
    //set patron
    int patronID;
    inFile >> patronID;

    PatronFactory pf;
    patron = pf.create(patronID);

    //set item
    char type, format;
    inFile >> type >> format;
    inFile.get();  //get space before next token

    LibItemFactory lif;
    item = lif.create(type);
    
    if (item != nullptr)  //type code valid
    {
        item->setDataFromCommandFile(inFile);  //set data
        item->setFormat(static_cast<Format>(format));  //set format
    }
    else  //incorrect type code
    {
        stringstream message;
        message << "Incorrect Library Item type code ("
            << type << ").";

        error = message.str();

        //delete patron
        delete patron;
        patron = nullptr;

        string s;
        getline(inFile, s);  //read to the end of line

        return;
    }
}

//---------------------------------------------------------------------------
//execute
//Calls library to check in LibItem and Patron referenced in CheckIn
void CheckIn::execute() const
{
    //Ensure all variables are not nullptr
    if (library == nullptr || item == nullptr || patron == nullptr)
        return;

    //Check format code
    Format f = item->getFormat();
    if (!isValidFormat(f))
    {
        cout << "Invalid format code ("
            << static_cast<char>(f) << ")." << endl;

        return;
    }

    //Check if patron and item exist in library
    LibItem *actualItem = library->findLibraryItem(*item);
    Patron *actualPatron = library->findPatron(*patron);

    if (actualItem == nullptr)  //item not found
    {
        string s = "Item";

        if (item != nullptr) s = item->getTitle();

        cout << s << " does not exist in the system." << endl;
        return;
    }

    if (actualPatron == nullptr)  //patron not found
    {
        cout << "Patron ID ("
            << patron->getPatronID()
            << ") does not exist in the system."
            << endl;
        return;
    }

    if (actualItem->checkIn(actualPatron))  //check in patron from item
    {
        actualPatron->checkIn(actualItem);  //check in item from patron
    }

    actualItem = nullptr;
    actualPatron = nullptr;
}
