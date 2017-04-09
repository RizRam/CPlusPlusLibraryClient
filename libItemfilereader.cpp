/*
Rizky Ramdhani
CSS502
Assignment 4
libitemfilereader.cpp - Implementation file for LibItemFileReader
*/

#include "libItemfilereader.h"
#include "library.h"
#include<fstream>
#include<iostream>

using namespace std;

//---------------------------------------------------------------------------
//Constructor
LibItemFileReader::LibItemFileReader(string fileName, Library * library)
{
    this->fileName = fileName;
    this->library = library;
}

//---------------------------------------------------------------------------
//Destructor
//Does not deallocate dynamic memory
LibItemFileReader::~LibItemFileReader()
{
    library = nullptr;
}

//---------------------------------------------------------------------------
//Copy constructor
//Shallow copy
LibItemFileReader::LibItemFileReader(const LibItemFileReader &other)
{
    this->fileName = other.fileName;
    this->library = other.library;
}

//---------------------------------------------------------------------------
//Assigment operator
//Shallow copy
LibItemFileReader & LibItemFileReader::operator=(
    const LibItemFileReader &other)
{
    if (this != &other)
    {
        this->fileName = other.fileName;
        this->library = other.library;
    }

    return *this;
}

//---------------------------------------------------------------------------
//populateItems
//Reads from fileName and populates the contents of Library with LibItem(s)
//void LibItemFileReader::populateItems() const
void LibItemFileReader::populateItems() const
{
    if (library == nullptr) return;
    
    ifstream inFile(fileName);
    if (!inFile)
    {
        cout << "Invalid Library Items input file." << endl;
        return;
    }

    while (!inFile.eof())
    {
        LibItem *item = nullptr;
        char type;
        inFile >> type;

        if (inFile.eof()) return;

        inFile.get();  //ignore space before author

        item = factory.create(type);  //instantiate LibItem
        if (item != nullptr)  //type code is correct
        {
            item->setDataFromInitFile(inFile);
            if (!library->insertLibraryItem(*item))
            {
                //if insertion failes
                delete item;
            }
        }        

        item = nullptr;
    }
}