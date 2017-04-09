/*
Rizky Ramdhani
CSS502
Assignment 4
childrensbook.cpp - Implementation for ChildrensBook
*/

#include "childrensbook.h"
//---------------------------------------------------------------------------
//Default Constructor
ChildrensBook::ChildrensBook(): Book() 
{
    type = CatalogType::Y;
    format = Format::HC;
}

//---------------------------------------------------------------------------
//Constructor
ChildrensBook::ChildrensBook(string title, CatalogType type, Format format, 
    string author, int year, int inventory) : Book(title, type, format,
    author, year, inventory) {}

//---------------------------------------------------------------------------
//Copy constructor
//Performs shallow copy
ChildrensBook::ChildrensBook(const ChildrensBook &other) : Book(other) {}

//---------------------------------------------------------------------------
//Assignment operator
//Performs shallow copy
ChildrensBook & ChildrensBook::operator=(const ChildrensBook &other)
{
    if (this != &other) //if memory address is not the same
    {
        Book::operator=(other);
    }

    return *this;
}

//---------------------------------------------------------------------------
//Less than operator
//Comparison is made first by title, then author.
//Return:
//  true if this ChildrensBook is less than other ChildrensBook, false
//  otherwise.
bool ChildrensBook::operator<(const Object &object) const
{
    //cast to ChildrensBook
    const ChildrensBook &other = static_cast<const ChildrensBook &>(object);
    if (this->title == other.title)
    {
        return this->author < other.author;
    }
    else
    {
        return this->title < other.title;
    }
}

//---------------------------------------------------------------------------
//Greater than operator
//Comparison is made first by title, then author.
//Return:
//  true if this ChildrensBook is greater than other ChildrensBook,
//  false otherwise.
bool ChildrensBook::operator>(const Object &other) const
{
    return other < *this;
}

//---------------------------------------------------------------------------
//Less than or equal operator
//Comparison is made first by title, then author.
//Return:
//  true if this ChildrensBook is less than or equal to other ChildrensBook,
//  false otherwise.
bool ChildrensBook::operator<=(const Object &other) const
{
    return !(*this > other);
}

//---------------------------------------------------------------------------
//Greater than or equal operator
//Comparison is made first by title, then author.
//Return:
//  true if this ChildrensBook is greater than or equal 
//  to other ChildrensBook, false otherwise.
bool ChildrensBook::operator>=(const Object &other) const
{
    return !(*this < other);
}

//---------------------------------------------------------------------------
//createChildrensBook
//Sets data members of ChildrensBook using content from an input file.
//Example Input:
//  Heide Florence Parry, Treehorn's Wish, 1984
//Parameters:
//  -inFile: (ifstream) input file to be read from.  Input is a valid input  
void ChildrensBook::setDataFromInitFile(ifstream &inFile)
{
    getline(inFile, author, ',');  //read author
    inFile.get();  //get space before title
    getline(inFile, title, ',');  //read title
    inFile >> year;  //read year
    string s;
    getline(inFile, s);
}

//---------------------------------------------------------------------------
//setChildrensBookData
//sets the data of ChildrensBook using data parsed from input file
//Example input:
//  Danny Dunn & the Homework Machine, Williams Jay,
//Parameters:
//  -inFile: (ifstream) input file
void ChildrensBook::setDataFromCommandFile(ifstream &inFile)
{
    getline(inFile, title, ',');  //title
    inFile.get();  //space
    getline(inFile, author, ',');  //author
}

//---------------------------------------------------------------------------
//getHashCode()
//  returns a hash code that is determined by converting the title and author
//  values to an integer.
//Return:
//  a unique int value for this object to be used in HashTable's hash().
int ChildrensBook::getHashCode() const
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

    return (titleInt * 7) + (authorInt * 11);
}
