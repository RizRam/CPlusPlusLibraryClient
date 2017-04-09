/*
Rizky Ramdhani
CSS502
Assignment 4
displayinventory.cpp - Implementation file for DisplayInventory
*/

#include "displayinventory.h"
#include "library.h"
#include <iomanip>

//---------------------------------------------------------------------------
//Default constructor
DisplayInventory::DisplayInventory() : Transaction() {}

//---------------------------------------------------------------------------
//Copy constructor
//Performs shallow copy
DisplayInventory::DisplayInventory(const DisplayInventory &other) :
    Transaction(other) {}

//---------------------------------------------------------------------------
//Destructor
//Does not deallocate library
DisplayInventory::~DisplayInventory()
{
    library = nullptr;
}

//---------------------------------------------------------------------------
//Assignment operator
//Performs 
DisplayInventory & DisplayInventory::operator=(const DisplayInventory &other)
{
    if (this != &other)  //check if same memory address
    {
        Transaction::operator=(other);
    }

    return *this;
}

//---------------------------------------------------------------------------
//execute()
//Calls Library to display the contents of its Catalogs
void DisplayInventory::execute() const
{
    const Catalog * const catalogs = library->getCatalogs();

    for (int i = 0; i < NUM_CATALOGS; i++)
    {
        const Catalog &curr = catalogs[i];

        //Print header
        cout << getCatalogTypeString(curr.getCatalogType())
            << "  (" << curr.getCount() << ")" << endl;

        printColumns(curr.getCatalogType()); //print columns
        
        cout << catalogs[i] << endl;  //print Catalog
    }
}

//---------------------------------------------------------------------------
//printColumns
//prints the appropriate columns for output, depending on the Type of LibItem
void DisplayInventory::printColumns(CatalogType type) const
{
    if (type == Y || type == F)
    {
        cout << "\t"
            << left << setw(TITLE_WIDTH) << "TITLE"
            << left << setw(AUTHOR_WIDTH) << "AUTHOR"
            << right << setw(YEAR_WIDTH) << "YEAR"
            << right << setw(FORMAT_WIDTH) << "  FORMAT"
            << "  IVNTR" << endl;
    }
    else if (type == P)
    {
        cout << "\t"
            << left << setw(TITLE_WIDTH) << "TITLE"
            << left << setw(MONTH_WIDTH) << "MONTH"
            << right << setw(YEAR_WIDTH) << "YEAR"
            << right << "  IVNTR" << endl;
    }
}
