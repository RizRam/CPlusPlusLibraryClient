/*
Rizky Ramdhani
CSS502
Assignment 4
periodical.cpp - Implementation file for Periodical
*/

#include "periodical.h"
#include <iomanip>

//---------------------------------------------------------------------------
//Default Constructor
Periodical::Periodical() : LibItem()
{
    type = CatalogType::P;
    totalInventory = DEFAULT_PERIODICAL_INVENTORY;
    availableInventory = DEFAULT_PERIODICAL_INVENTORY;
    format = Format::HC;
}

//---------------------------------------------------------------------------
//Constructor
Periodical::Periodical(string title, CatalogType type, Format format,
    int year, int month, int inventory) : LibItem(title, type, format, 
    inventory, inventory)
{
    this->year = year;
    this->month = month;
}

//---------------------------------------------------------------------------
//Copy constuctor
//performs shallow copy
Periodical::Periodical(const Periodical &other) : LibItem(other) 
{
    this->year = other.year;
    this->month = other.month;
}

//---------------------------------------------------------------------------
//Assignment operator
//performs shallow copy
Periodical & Periodical::operator=(const Periodical &other)
{
    if (this != &other) //check if the same memory address
    {
        LibItem::operator=(other);
        this->year = other.year;
        this->month = other.month;
    }

    return *this;
}

//---------------------------------------------------------------------------
//setYear
//setter for year
//Parameters:
//  -year: (int) year to be assigned to this Periodical.  Year must be an
//         integer greater than 0
//Return:
//  true if year is valid and successfully set, false otherwise.
bool Periodical::setYear(int year)
{
    if (year > 0)
    {
        this->year = year;
        return true;
    }

    return false;
}

//---------------------------------------------------------------------------
//setMonth
//setter for month
//Parameters:
//  -month: (int) month to be assigned to this Periodical.  
//          where 1 <= month <= 12.
//Return:
//  true if month is valid and successfully set, false otherwise.
bool Periodical::setMonth(int month)
{
    if (month >= 1 && month <= 12)
    {
        this->month = month;
        return true;
    }

    return false;
}

//---------------------------------------------------------------------------
//setDataFromInitFile
//sets the member data of Periodical using the contents of init input file.
//Example input:
//  Vegetarian Times, 1 2010
//Parameters:
//  -inFile: (ifstream) input file to be read from.  Input is a valid input
//           file.
void Periodical::setDataFromInitFile(ifstream &inFile)
{
    getline(inFile, title, ','); //title
    inFile.get();  //space before month
    inFile >> month >> year;

    string s;
    getline(inFile, s);  //read to end of line   
}

//---------------------------------------------------------------------------
//setDataFromCommandFile
//sets the data of Periodical using data parsed from command input file
//Example input:
//   2010 1 Communications of the ACM,
//Parameters:
//  -inFile: (ifstream) input file
void Periodical::setDataFromCommandFile(ifstream &inFile)
{
    //Parse
    inFile >> year >> month;  //year month
    inFile.get();  //space
    getline(inFile, title, ',');  //title
}

//---------------------------------------------------------------------------
//getYear
//getter method for year
//Return:
//  (int)year Periodical was published
int Periodical::getYear()
{
    return year;
}

//---------------------------------------------------------------------------
//getMonth
//getter method for month
//Return:
//  (int)month Periodical was published
int Periodical::getMonth()
{
    return month;
}

//---------------------------------------------------------------------------
//print
//Overridden function to print the contents of this Periodical
ostream & Periodical::print(ostream &out) const
{
    out << left << setw(TITLE_WIDTH) << title
        << left << setw(MONTH_WIDTH) << month
        << right << setw(YEAR_WIDTH) << year
        << "  (" << availableInventory << "/" << totalInventory << ")";

    return out;
}

//---------------------------------------------------------------------------
//Equality operator
//Return:
//  true if all private data members of this Periodical equal other Periodical
//  data members, including the contents of patronList.
bool Periodical::operator==(const Object &object) const
{
    //cast to Periodical
    const Periodical &other = static_cast<const Periodical &>(object);

    if (this->year != other.year) return false;
    if (this->month != other.month) return false;
    if (this->title != other.title) return false;

    return true;
}

//---------------------------------------------------------------------------
//Inequality operator
//Return:
//  true if any private data members of this Periodical does not equal
//  other Periodical data members, including the contents of PatronList
bool Periodical::operator!=(const Object &other) const
{
    return !(*this == other);
}

//---------------------------------------------------------------------------
//Less than operator
//Comparison is made first by date (year, then month), then by title.
//Return:
//  true if this Periodical is less than other Periodical, false otherwise.
bool Periodical::operator<(const Object &object) const
{
    //cast to Periodical
    const Periodical &other = static_cast<const Periodical &>(object);

    if (this->year == other.year && this->month == other.month)
    {
        return this->title < other.title;
    }
    else
    {
        if (this->year == other.year)
        {
            return this->month < other.month;
        }
        else
        {
            return this->year < other.year;
        }
    }
}

//---------------------------------------------------------------------------
//Greater than operator
//Comparison is made first by date (year, then month), then by title.
//Return:
//  true if this Periodical is greater than other Periodical,
//  false otherwise.
bool Periodical::operator>(const Object &other) const
{
    return other < *this;
}

//---------------------------------------------------------------------------
//Less than or equal to operator
//Comparison is made first by date (year, then month), then by title.
//Return:
//  true if this Periodical is less than or equal to other Periodical,
//  false otherwise.
bool Periodical::operator<=(const Object &other) const
{
    return !(*this > other);
}

//---------------------------------------------------------------------------
//Greater than operator
//Comparison is made first by date (year, then month), then by title.
//Return:
//  true if this Periodical is greater than or equal to other Periodical,
//  false otherwise.
bool Periodical::operator>=(const Object &other) const
{
    return !(*this < other);
}

//---------------------------------------------------------------------------
//getHashCode()
//  returns a hash code that is determined by converting the title, year,
//  and month values to an integer.
//Return:
//  a unique int value for this object to be used in HashTable's hash().
int Periodical::getHashCode() const
{
    int titleInt = 0;
    for (char c : title)
    {
        titleInt += c;
    }

    int yearInt = year * 7;
    int monthInt = month * 3;

    return (titleInt * 11) + yearInt + monthInt;
}