/*
Rizky Ramdhani
CSS502
Assignment 4
patronfilereader.h - Implementation file for PatronFileReader
*/

#include "patronfilereader.h"
#include "patron.h"
#include "library.h"
#include <fstream>
#include <iostream>

using namespace std;

//---------------------------------------------------------------------------
//Constructor
PatronFileReader::PatronFileReader(string fileName, Library *library)
{
    this->fileName = fileName;
    this->library = library;
}

//---------------------------------------------------------------------------
//Destructor
//Does not deallocate dynamic memory
PatronFileReader::~PatronFileReader()
{
    library = nullptr;
}

//---------------------------------------------------------------------------
//Copy constructor
//shallow copy
PatronFileReader::PatronFileReader(const PatronFileReader &other)
{
    this->fileName = other.fileName;
    this->library = other.library;
}

//---------------------------------------------------------------------------
//Assignment operator
//shallow copy
PatronFileReader & PatronFileReader::operator=(const PatronFileReader &other)
{
    if (this != &other)
    {
        this->fileName = other.fileName;
        this->library = other.library;
    }

    return *this;
}

//---------------------------------------------------------------------------
//populatePatrons
//Parses the contents of data referenced in fileName and populates library
//with new Patron objects
void PatronFileReader::populatePatrons() const
{
    if (library == nullptr) return;  //if there is no library

    ifstream inFile(fileName);

    //validate input file
    if (!inFile)
    {
        cout << "Invalid patron init file.";
        return;
    }

    while (!inFile.eof())
    {
        int ID;
        inFile >> ID;
        
        if (inFile.eof()) return;

        Patron *patron = factory.create(ID);
        patron->setDataFromFile(inFile);

        if (!library->addPatron(*patron))  //failed adding patron
        {
            delete patron;
        }

        patron = nullptr;
    }
}


