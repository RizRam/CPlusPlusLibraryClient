/******************************************************************************
 * Ben Pittman - David Nixon - Mike Chavez - Rizky Ramdhani
 * CS 502A Winter 2017
 * HW 4
 * library.h - Header file for Library
 ******************************************************************************/

#pragma once

#include <string>

using namespace std;

/*
//---------------------------------------------------------------------------
                                 Library
A class that contains collections of LibItems and Patrons and provides
external access to the elements it contains. 

Features:
    -Insertion and retrieval of LibItems and patrons
    -Display of contents (entire catalog, or individual Patron)
    -Initialize contained elements using input text files.
    -Execute commands provided by a text file.
Implementation:
    -Stores Patron using HashTable
    -Stores LibItem objects using Catalog class
    -Different types of LibItems are stored in different Catalogs which is
     stored into a simple hashtable.  LibItems are hashed into Catalaogs
     according to their CatalogType data member.
    -Uses LibItemFileReader and PatronFileReader classes to parse input
     files to populate collections.
    -Uses TransactionFileReader class to parse commands/transactions from
     an input file.
    -Librarian class manages a queue of the transactions read from input
     file for execution.
    -Library is responsible for deallocating dynamic memory contained
    -in its collections.
//---------------------------------------------------------------------------
*/

#include "patron.h"
#include "libitem.h"
#include "hashtable.h"
#include "catalog.h"
#include "librarian.h"


class Library {
public:
    Library(string catalogFile, string peopleFile); // constructor
    Library(const Library &); // copy constructor
    ~Library(); // destructor
    Library & operator=(const Library &); // assignment operator
   
    // initializeCatalog is called by the constructor and could
    // be called again if we need to add more items to the library:
    void initializeCatalogs(string datafile);

    //Populates patronDB from a file given in the argument
    void initializePatrons(string peopleFile);

    // method to execute commands from a transation file
    // like check out books, display patron history:
    void readCommands(string transactionsFile);

    // to insert a single item:
    bool insertLibraryItem(LibItem &);

    //insert Patron into collection
    bool addPatron(Patron &);
   
    // gives us a pointer to the library item from the title:
    LibItem * findLibraryItem(const LibItem &item) const;
   
    // gives us a pointer to the Patron from her ID:
    Patron * findPatron(const Patron &) const;

    //getter for libraryCatalog
    const Catalog * const getCatalogs() const;  


private:
   
    // an array of catalogs. Currently there are 3 catalogs:
    // Children's books, Fiction, and periodicals.
    Catalog libraryCatalog[NUM_CATALOGS];

    // database of all library patrons:
    HashTable patronDB;

    Librarian librarian;  //Manages transaction queue
};










