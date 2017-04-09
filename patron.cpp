/*
Rizky Ramdhani
CSS502
Assignment 4
patron.cpp - Implementation for Patron
*/

#include "patron.h"
#include "libitem.h"
#include <iomanip>

//---------------------------------------------------------------------------
//Constructor
//Parameters:
//  -ID: (int) the ID of this Patron
Patron::Patron(int ID) : Object() 
{
    this->patronID = ID;
}

//---------------------------------------------------------------------------
//Constructor
Patron::Patron(int ID, string firstName, string lastName) : Object()
{
    this->patronID = ID;
    this->firstName = firstName;
    this->lastName = lastName;
}

//---------------------------------------------------------------------------
//Destructor
//Not responsible for deallocating dynamic memory LibItem objects in
//history.  Calls clearHistory().
Patron::~Patron()
{
    clearHistory();
}

//---------------------------------------------------------------------------
//Copy constructor
//shallow copy
Patron::Patron(const Patron &other) : Object(other)
{
    this->patronID = other.patronID;
    this->firstName = firstName;
    this->lastName = lastName;

    //copy history

    //clear history
    clearHistory();

    //iterate and copy
    for (CheckOutRecord cor : other.history)
    {
        this->history.push_back(cor);
    }
}

//---------------------------------------------------------------------------
//Assignment operator
//shallow copy
Patron & Patron::operator=(const Patron &other)
{
    if (this != &other)  //if not the same memory address
    {
        Object::operator=(other);

        this->patronID = other.patronID;
        this->firstName = firstName;
        this->lastName = lastName;

        //copy history

        //clear history
        clearHistory();

        for (CheckOutRecord cor : other.history)
        {
            this->history.push_back(cor);
        }
    }

    return *this;
}

//---------------------------------------------------------------------------
//Equality operator
//Return:
//  true if this patronID equals other patronID, false otherwise.
bool Patron::operator==(const Object &object) const
{
    //cast to Patron
    const Patron& other = static_cast<const Patron&>(object);
    return this->patronID == other.patronID;
}

//---------------------------------------------------------------------------
//Inequality operator
//Return:
//  true if this patronID does not equal other patronID, false otherwise.
bool Patron::operator!=(const Object &other) const
{
    return !(*this == other);
}

//---------------------------------------------------------------------------
//Less than operator
//Uses patronID for comparison
//Return:
//  return true if this Patron is less than other Patron, false otherwise.
bool Patron::operator<(const Object &object) const
{
    //cast to Patron
    const Patron& other = static_cast<const Patron&>(object);
    return this->patronID < other.patronID;
}

//---------------------------------------------------------------------------
//Greater than operator
//Uses patronID for comparison
//Return:
//  return true if this Patron is greater than other Patron, false otherwise.
bool Patron::operator>(const Object &other) const
{
    return other < *this;
}

//---------------------------------------------------------------------------
//Less than or equal to operator
//Uses patronID for comparison
//Return:
//  return true if this Patron is less than or equal to other Patron,
//  false otherwise.
bool Patron::operator<=(const Object &other) const
{
    return !(*this > other);
}

//---------------------------------------------------------------------------
//Greater than or equal to operator
//Uses patronID for comparison
//Return:
//  return true if this Patron is greater than or equal to other Patron,
//  false otherwise.
bool Patron::operator>=(const Object &other) const
{
    return !(*this < other);
}

//---------------------------------------------------------------------------
//setFirstName
//Parameters:
//  -firstName: (string) to be assigned to firstName.
//Return:
//  true if firstName was successfully assigned, false otherwise.
bool Patron::setFirstName(string firstName)
{
    this->firstName = firstName;

    return true;
}

//---------------------------------------------------------------------------
//setLastName
//Parameters:
//  -lastName: (string) to be assigned to lastName.
//Return:
//  true if lastName was successfully assigned, false otherwise.
bool Patron::setLastName(string lastName)
{
    this->lastName = lastName;

    return true;
}

//---------------------------------------------------------------------------
//checkIn
//removes item from Patron's history.
//Parameters:
//  -item: (LibItem *) pointer to LibItem that needs to be checked in.
//Return:
//  true if item was successfully checked in, false otherwise.
bool Patron::checkIn(LibItem *item)
{
    if (item == nullptr) return false;

    //Check to see if Patron has a record of item
    for (CheckOutRecord &cor : history)
    {
        if (*cor.item == *item) //Library Item found
        {
            CheckOutRecord temp;
            temp.item = item;
            temp.checkOut = false;

            history.push_back(temp);
            return true;
        }
    }

    return false;  //item not found, not checked out to Patron
}

//---------------------------------------------------------------------------
//checkOut
//add item for check out to check out history list
//Parameters:
//  -item: (LibItem *) LibItem to be checked out to Patron
//Returns:
//  true if check out was successful, false otherwise.
bool Patron::checkOut(LibItem *item)
{
    if (item == nullptr) return false;

    //Create CheckOutRecord
    CheckOutRecord temp;
    temp.item = item;
    temp.checkOut = true;

    //Add temp to history
    history.push_back(temp);

    return true;
}

//---------------------------------------------------------------------------
//setDataFromFile
//sets the data members of Patron using the content from an input file.
//Example input:
//  2000 Bear Bertha
//Parameters:
//  -inFile: (ifstream) input file to be read from.  Must be valid file.
void Patron::setDataFromFile(ifstream &inFile)
{
    inFile >> lastName >> firstName;  //assign first and last name
    
    string s;
    getline(inFile, s);  //read until the end of line.
}

//---------------------------------------------------------------------------
//getPatronID()
//Return:
//  (int) patronID of Patron
int Patron::getPatronID() const
{
    return patronID;
}

//---------------------------------------------------------------------------
//getFirstName()
//Return:
//  (string) first name of Patron
string Patron::getFirstName() const
{
    return firstName;
}

//---------------------------------------------------------------------------
//getLastName()
//Return:
//  (string) last name of Patron
string Patron::getLastName() const
{
    return lastName;
}

//---------------------------------------------------------------------------
//getHashCode()
//Uses patronID to determine hash value.
//Return:
//  (int) a unique integer to be used in HashTable's hash() function.
int Patron::getHashCode() const
{
    return patronID;
}

//---------------------------------------------------------------------------
//print
//Prints a description of this Patron, including Patron's check out history
ostream & Patron::print(ostream &out) const
{
    out << left << setw(PATRON_ID_WIDTH) << patronID
        << left << lastName << ", " << firstName << ":" << endl;
    

    if (history.size() > 0)
    {
        for (CheckOutRecord cor : history)
        {
            string c;
            if (cor.checkOut)
            {
                c = "CheckOut";
            }
            else
            {
                c = "Return";
            }
            out << "  " << left << setw(CHECKOUT_WIDTH) << c
                << *cor.item << endl;
        }
    }
    else
    {
        out << "  ***Empty check out record.***" << endl;
    }


    return out;
}

//---------------------------------------------------------------------------
//clearHistory
//clears the contents of history.  Not responsible for deallocating dynamic
//LibItem objects referenced in CheckOutRecord.
void Patron::clearHistory()
{
    while (!history.empty())
    {
        CheckOutRecord &cur = history.front();
        cur.checkOut = false;
        cur.item = nullptr;

        history.pop_front();
    }
}
