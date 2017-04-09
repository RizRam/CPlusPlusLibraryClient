/******************************************************************************
* Ben Pittman - David Nixon - Mike Chavez - Rizky Ramdhani
* CS 502A Winter 2017
* HW 4
* patronfilereader.h - Header for PatronFileReader
******************************************************************************/

#pragma once

#include "patronfactory.h"
#include <string>

using namespace std;

/*
//---------------------------------------------------------------------------
                                 PatronFileReader
A class used to parse through an input text file and populate a Library class
with Patron objects described in the text file.

Implementation:
    -Constructor requires the filepath of the input text file as well as
     a pointer to a Library object.
    -Input file must be formatted specifically in order to function.
        -one line per patron
        -Example line:
            2000 Bear Bertha
    -Uses patronFactory to instantiate new Patron objects.
    -PatronFileReader does not have ownership of Patron objects it creates,
     and does not deallocate dynamic memory.
//---------------------------------------------------------------------------
*/

class Library;

class PatronFileReader {

public:
    PatronFileReader(string fileName, Library *);  //Constructor
    ~PatronFileReader();  //Destructor
    PatronFileReader(const PatronFileReader &);  //Copy constructor
    PatronFileReader& operator=(const PatronFileReader &); //Assignment operator

    void populatePatrons() const;  //Populates Library with Patron objects
    
private:
    string fileName;  //name of file
    Library *library;  //reference to library object
    PatronFactory factory;  //factory class used to instantiate Patrons
};