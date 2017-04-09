/*
Rizky Ramdhani
CSS502
Assignment 4
book.cpp - Implementation file for Book class
*/

#include "book.h"
#include <iomanip>

//---------------------------------------------------------------------------
//Default constructor
Book::Book() : LibItem()
{
    totalInventory = DEFAULT_BOOK_INVENTORY;
    availableInventory = DEFAULT_BOOK_INVENTORY;
}

//---------------------------------------------------------------------------
//Constructor
Book::Book(string title, CatalogType type, Format format, string author,
    int year, int inventory) : LibItem(title, type, format, inventory,
        inventory)
{
    this->author = author;
    this->year = year;
}

//---------------------------------------------------------------------------
//Copy constructor
Book::Book(const Book &other) : LibItem(other)
{
    this->author = other.author;
    this->year = other.year;
}

//---------------------------------------------------------------------------
//Assignment operator
Book & Book::operator=(const Book &other)
{
    if (this != &other)  //if not the same memory address
    {
        LibItem::operator=(other);
        author = other.author;
        year = other.year;
    }

    return *this;
}

//---------------------------------------------------------------------------
//Equality operator
//Return:
//  true if all private data members of this and other are the same,
//  including the contents of patronList, false otherwise
bool Book::operator==(const Object &object) const
{
    //cast to Book
    const Book &other = static_cast<const Book &>(object);

    if (this->title != other.title) return false;
    if (this->author != other.author) return false;

    return true;
}

//---------------------------------------------------------------------------
//Inequality operator
//Returns:
//  true if private members of this and other are not equal including the
//  contents of patronList, false otherwise.
bool Book::operator!=(const Object &other) const
{
    return !(this->operator==(other));
}

//---------------------------------------------------------------------------
//setAuthor
//Sets author to string passed in argument
//Parameters:
//  -author: (string) new author to be assigned to Book
//Return:
//  true if author was successfully set, false otherwise.
bool Book::setAuthor(string author)
{
    this->author = author;
    return true;
}

//---------------------------------------------------------------------------
//setYear
//Sets year to int passed in argument
//Parameters:
//  -year: (int) year to be assigned to Book.  
//         Year must be an integer greater than 0.
//Return:
//  true if year was successfully set, false otherwise.
bool Book::setYear(int year)
{
    if (year > 0)
    {
        this->year = year;
        return true;
    }

    return false;
}

//---------------------------------------------------------------------------
//getAuthor
//get method for author
//Return:
//  returns a string representation of this Book's author
string Book::getAuthor() const
{
    return author;
}

//---------------------------------------------------------------------------
//getYear
//get method for year
//Return:
//  returns int representing the year the Book was published.
int Book::getYear() const
{
    return year;
}

//---------------------------------------------------------------------------
//print
//Overridden function to print the contents of this Book
ostream & Book::print(ostream &out) const
{
    out << left << setw(TITLE_WIDTH) << title.substr(0, TITLE_WIDTH - 2)
        << left << setw(AUTHOR_WIDTH) << author.substr(0, AUTHOR_WIDTH - 2)
        << right << setw(YEAR_WIDTH) << year
        << right << setw(FORMAT_WIDTH) << getFormatAsString(format)
        << "  (" << availableInventory << "/" << totalInventory << ")";

    return out;
}

//---------------------------------------------------------------------------
//getFormatAsString
//Returns a string representation of Format to be printed
string Book::getFormatAsString(Format f) const
{
    switch (f)
    {
    case HC:
        return "HC";
        break;
    case SC:
        return "SC";
        break;
    case DG:
        return "D";
        break;
    default:
        return string();
        break;
    }
}
