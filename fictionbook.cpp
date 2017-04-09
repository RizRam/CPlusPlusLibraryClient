/*
Rizky Ramdhani
CSS502
Assignment 4
fictionbook.cpp - Implementation file for FictionBook
*/

#include "fictionbook.h"
//---------------------------------------------------------------------------
//Default constructor
FictionBook::FictionBook() : Book()
{
    type = CatalogType::F;
    format = Format::HC;
}

//---------------------------------------------------------------------------
//Constructor
FictionBook::FictionBook(string title, CatalogType type, Format format,
    string author, int year, int inventory) : Book(title, type, format,
        author, year, inventory) {}

//---------------------------------------------------------------------------
//Copy constructor
//shallow copy
FictionBook::FictionBook(const FictionBook &other) : Book(other) {}

//---------------------------------------------------------------------------
//Assignment operator
//shallow copy
FictionBook & FictionBook::operator=(const FictionBook &other)
{
    if (this != &other) //if not the same memory address
    {
        Book::operator=(other);
    }

    return *this;
}

//---------------------------------------------------------------------------
//Less than operator
//Comparison is made first by author, then title.
//Return:
//  true if this FictionBook is less than other FictionBook, false otherwise
bool FictionBook::operator<(const Object &object) const
{
    //cast to FictionBook
    const FictionBook &other = static_cast<const FictionBook &>(object);

    if (this->author == other.author)
    {
        return this->title < other.title;
    }
    else
    {
        return this->author < other.author;
    }
}

//---------------------------------------------------------------------------
//Greater than operator
//Comparison is made first by author, then title.
//Return:
//  true if this FictionBook is greater than other FictionBook, 
//  false otherwise
bool FictionBook::operator>(const Object &other) const
{
    return other < *this;
}

//---------------------------------------------------------------------------
//Less than or equal to operator
//Comparison is made first by author, then title.
//Return:
//  true if this FictionBook is less than or equal to other FictionBook, 
//  false otherwise
bool FictionBook::operator<=(const Object &other) const
{
    return !(*this > other);
}

//---------------------------------------------------------------------------
//Greater than or equal to operator
//Comparison is made first by author, then title.
//Return:
//  true if this FictionBook is greater than or equal to other FictionBook, 
//  false otherwise
bool FictionBook::operator>=(const Object &other) const
{
    return !(*this < other);
}


//---------------------------------------------------------------------------
//setDataFromInitFile
//Sets the member data of FictionBook using data read from an input file.
//Example Input:
//  Daheim Mary, Fowl Prey, 1991
//Parameters:
//  -inFile: (ifstream) input file to be read from.  Input is a valid input
//           file.
void FictionBook::setDataFromInitFile(ifstream &inFile)
{
    getline(inFile, author, ',');  //read author
    inFile.get();  //get space before author
    getline(inFile, title, ',');  //read title
    inFile >> year;  //read year

    string s;
    getline(inFile, s);  //read to the end of the line
}

//---------------------------------------------------------------------------
//setDataFromCommandFile
//sets the data of FictionBook using data parsed from command input file
//Example input:
//   Forster E. M., The Longest Journey,
//Parameters:
//  -inFile: (ifstream) input file
void FictionBook::setDataFromCommandFile(ifstream &inFile)
{
    //Parse
    getline(inFile, author, ',');  //author
    inFile.get();  //space
    getline(inFile, title, ',');  //title
}

//---------------------------------------------------------------------------
//getHashCode()
//  returns a hash code that is determined by converting the title and author
//  values to an integer.
//Return:
//  a unique int value for this object to be used in HashTable's hash().
int FictionBook::getHashCode() const
{
    int titleInt = 0;
    for (char c : title)
    {
        titleInt += c;
    }

    int authorInt = 0;
    for (char c : author)
    {
        authorInt += c;
    }

    return (titleInt * 11) + (authorInt * 7);
}