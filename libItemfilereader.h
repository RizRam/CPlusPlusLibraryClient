/******************************************************************************
* Ben Pittman - David Nixon - Mike Chavez - Rizky Ramdhani
* CS 502A Winter 2017
* HW 4
* libitemfilereader.h - Header file for LibItemFileReader
******************************************************************************/

#pragma once

#include "libitemfactory.h"
#include<string>

using namespace std;

/*
//---------------------------------------------------------------------------
                                LibItemFileReader
Class used to read and parse and input file and populate Library's catalogs
with LibItem objects.
Implementation:
    -Uses LibItemFactory to instantiate empty LibItem derived objects.
    -Parses through input file to set the data of the instantiated objects.
    -Contains a reference to Library to insert the objects into the
     Library's catalogs.
    -Does not have ownership of newly created LibItems
    -LibItemFileReader does not deallocate dynamic memory.
//---------------------------------------------------------------------------
*/

class Library;
class LibItem;

class LibItemFileReader {

public:
    LibItemFileReader(string fileName, Library *library);  //Constructor
    ~LibItemFileReader();  //Destructor
    LibItemFileReader(const LibItemFileReader&);  //Copy constructor

    //Assignment operator
    LibItemFileReader & operator=(const LibItemFileReader&);  

    void populateItems() const; //populates library with LibItem(s)

private:
    LibItemFactory factory;
    string fileName;  //name of file
    Library *library;  //reference to Library
};
