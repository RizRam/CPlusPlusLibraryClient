/*
Rizky Ramdhani
CSS502
Assignment 4
libitem.cpp - Implementation for Library
*/

#include "library.h"
#include "libItemfilereader.h"
#include "patronfilereader.h"
#include "transactionfilereader.h"
#include <iomanip>

//---------------------------------------------------------------------------
//Constructor
Library::Library(string catalogFile, string peopleFile) : 
    librarian(Librarian(this))
{
    //Assign CatalogTypes
    for (int i = 0; i < NUM_CATALOGS; i++)
    {
        libraryCatalog[i].setType(VALID_CATALOGTYPES[i]);
    }

    initializeCatalogs(catalogFile);  
    initializePatrons(peopleFile);
}

//---------------------------------------------------------------------------
//Copy constructor
//Performs shallow copy
Library::Library(const Library &other) : librarian(other.librarian)
{
    this->patronDB = other.patronDB;
    
    for (int i = 0; i < NUM_CATALOGS; i++)
    {
        this->libraryCatalog[i] = other.libraryCatalog[i];
    }
}

//---------------------------------------------------------------------------
//Destructor
Library::~Library() {}

//---------------------------------------------------------------------------
//Assignment Operator
//Performs shallow copy
Library & Library::operator=(const Library &other)
{
    if (this != &other) //check if the same memory address
    {
        this->librarian = other.librarian;
        this->patronDB = other.patronDB;

        for (int i = 0; i < NUM_CATALOGS; i++)
        {
            this->libraryCatalog[i] = other.libraryCatalog[i];
        }
    }

    return *this;
}

//---------------------------------------------------------------------------
//initializeCatalogs
//Populates Library with LibItem objects specified
//by the contents of the file referenced by the file path in the argument.
//Parameters:
//  datafile: (string)specifies the path of the input file. Data file must be
//            a valid path to a valid input file.
void Library::initializeCatalogs(string datafile)
{
    LibItemFileReader fileReader = LibItemFileReader(datafile, this);
    fileReader.populateItems();
}

//---------------------------------------------------------------------------
//initializePatrons
//Populates this Library with Patron objects specified by the contents
//of the datafile referenced by the file path in the argument.
//Parameters:
//  peopleFile: (string)specifies the path of the input file.  PeopleFile must
//              be a valid path to a valid input file.
void Library::initializePatrons(string peopleFile)
{
    PatronFileReader fileReader = PatronFileReader(peopleFile, this);
    fileReader.populatePatrons();
}

//---------------------------------------------------------------------------
//readCommands
//Processes a set of commands to Library specified by the input file 
//passed in the argument.
//Parameters:
//  transactionFile: (string)specifies the path of the input file.
//                   transactionFile must be a valid path to a vaild input
//                   file.
void Library::readCommands(string transactionsFile)
{
    TransactionFileReader fileReader = 
        TransactionFileReader(transactionsFile, &librarian);
    fileReader.parseAndPopulateLibrarian();
    librarian.executeAll();
}

//---------------------------------------------------------------------------
//insertLibraryItem
//Insert LibItem passed in argument to 
//Parameters:
//  item: (LibITem) to be inserted into Library
//Return:
//  true if item was successfully inserted, false otherwise.
bool Library::insertLibraryItem(LibItem &item)
{
    if (&item == nullptr) return false;
    return libraryCatalog[item.getType()].insert(item);
}

//---------------------------------------------------------------------------
//addPatron
//adds a Patron to Library
//Parameters:
//  patron: (Patron) to be added to Library
//Return:
//  true if patron was successfully added to Library, false otherwise.
bool Library::addPatron(Patron &patron)
{
    if (&patron == nullptr) return false;
    return patronDB.insert(patron);
}

//---------------------------------------------------------------------------
//findLibraryItem
//Returns a pointer to LibItem contained in this library's system.
//Parameters:
//  -item: (LibItem) to find in this Library's system.
//Return:
//  A pointer to LibItem in Library that matches LibItem in argument.
//  Returns a nullptr if no LibItem in Library matches argument.
LibItem * Library::findLibraryItem(const LibItem &item) const
{
    if (&item == nullptr) return nullptr;
    return libraryCatalog[item.getType()].getItem(item);
}

//---------------------------------------------------------------------------
//findPatron
//Returns a pointer to Patron contained in this library's system
//Parameters:
//  -patron: (Patron) to find in this Library's system.
//Return:
//  A pointer to Patron in Library that matches Patron in argument.
//  Returns nullptr if no Patron in Library matches argument.
Patron * Library::findPatron(const Patron &patron) const
{
    if (&patron == nullptr) return nullptr;
    return static_cast<Patron *>(patronDB.getKey(patron));  //cast to Patron*
}

//---------------------------------------------------------------------------
//getCatalogs
//getter for libraryCatalog
//Return:
//  (const Catalog[const])  Returns a const pointer to libraryCatalog
//  with const Catalog elements.  Catalog elements may not be modified.
const Catalog * const Library::getCatalogs() const
{
    return libraryCatalog;
}


