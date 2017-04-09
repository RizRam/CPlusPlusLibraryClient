/*
Rizky Ramdhani
CSS502
Assignment 4
checkout.cpp - Implementation file for CheckOut
*/

#include "checkout.h"
#include "patron.h"
#include "patronfactory.h"
#include "libitem.h"
#include "libitemfactory.h"
#include "library.h"
#include <sstream>

//---------------------------------------------------------------------------
//Default constructor
CheckOut::CheckOut() : Transaction()
{
    this->item = nullptr;
    this->patron = nullptr;
}

//---------------------------------------------------------------------------
//Copy constructor
CheckOut::CheckOut(const CheckOut &other) : Transaction(other)
{
    this->item = other.item;
    this->patron = other.patron;
}

//---------------------------------------------------------------------------
//Destructor
//Responsible for deallocating Patron and LibItem objects passed in
//constructor
CheckOut::~CheckOut()
{
    delete item;
    item = nullptr;

    delete patron;
    patron = nullptr;

    library = nullptr;
}

//---------------------------------------------------------------------------
//Assignment operator
CheckOut & CheckOut::operator=(const CheckOut &other)
{
    if (this != &other) //check if same memory address
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
//  -item: (LibItem*) Pointer to LibItem to be assigned to this object
void CheckOut::setItem(LibItem *item)
{
    this->item = item;
}

//---------------------------------------------------------------------------
//setPatron
//Sets patron to Patron passed in argument
//Parameters:
//  -patron: (Patron*) Pointer to Patron to be assigned to this object
void CheckOut::setPatron(Patron *patron)
{
    this->patron = patron;
}

//---------------------------------------------------------------------------
//setDataFromFile
//Sets data members using content from input file.
//Example Input:
//  8888 F H Forster E. M., The Longest Journey,
//  1111 P H 2010 1 Communications of the ACM,
//  1111 Y H Danny Dunn & the Homework Machine, Williams Jay,
//Parameters:
//  -inFile: (ifstream) input file used for parsing. input file must be valid
void CheckOut::setDataFromFile(ifstream &inFile)
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

        string s;
        getline(inFile, s);  //read to the end of line

                             //delete patron
        delete patron;
        patron = nullptr;

        return;
    }
}

//---------------------------------------------------------------------------
//execute
//Calls Library to CheckOut
void CheckOut::execute() const
{
    //Ensure all variables are not nullptr
    if (library == nullptr || item == nullptr || patron == nullptr)
        return;

    //check format code
    Format f = item->getFormat();
    if (!isValidFormat(f))
    {
        cout << "Invalid format code ("
            << static_cast<char>(f) << ")." << endl;

        return;
    }    

    //Find item and patron in Library
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

    if (actualItem->checkOut(actualPatron))  //check in patron from item
    {
        actualPatron->checkOut(actualItem);  //check in item from patron
    }

    actualItem = nullptr;
    actualPatron = nullptr;
}


