/*
Rizky Ramdhani
CSS502
Assignment 4
libitem.cpp - Implementation for LibItem
*/

#include "libitem.h"
#include "patron.h"
//---------------------------------------------------------------------------
//Default constructor
LibItem::LibItem() : LibItem(string(), CatalogType::U, Format::UD, 0, 0) {}

//---------------------------------------------------------------------------
//Constructor
LibItem::LibItem(string theTitle, CatalogType type, Format format,
    int inventory, int availableInventory) : Object()
{
    title = theTitle;
    this->type = type;
    this->format = format;
    totalInventory = inventory;
    this->availableInventory = availableInventory;
}

//---------------------------------------------------------------------------
//Destructor
//Sets all Patron* in patronList to nullptr.  LibItem is not responsible
//for deallocating dynamic memory.  Calls clearPatronList().
LibItem::~LibItem()
{
    clearPatronList();
}

//---------------------------------------------------------------------------
//Copy constructor
//shallow copy
LibItem::LibItem(const LibItem &other) : Object(other)
{
    title = other.title;
    type = other.type;
    format = other.format;
    totalInventory = other.totalInventory;
    availableInventory = other.availableInventory;

    //copy patronList

    //clear patronList
    clearPatronList();

    //iterate and copy contents
    for (Patron *p : other.patronList)
    {
        patronList.push_back(p);
    }
}

//---------------------------------------------------------------------------
//Assignment operator
//shallow copy
LibItem & LibItem::operator=(const LibItem &other)
{
    if (this != &other)  //not the same object in memory
    {
        title = other.title;
        type = other.type;
        format = other.format;
        totalInventory = other.totalInventory;
        availableInventory = other.availableInventory;

        //copy patronList

        clearPatronList();

        for (Patron *p : other.patronList)
        {
            patronList.push_back(p);
        }        
    }

    return *this;
}

//---------------------------------------------------------------------------
//setTitle
//sets title
//Parameters:
//  -title: (string) new title of LibItem
//Returns:
//  true if title is successfully changed, false otherwise.
bool LibItem::setTitle(string title)
{
    this->title = title;
    return true;
}

//---------------------------------------------------------------------------
//setTotalInventory
//sets totalInventory to amount in argument
//Parameters:
//  -inventory: (int) new total inventory, must be a positive integer
//Returns:
//  true if inventory amount is valid, false otherwise.
bool LibItem::setTotalInventory(int inventory)
{
    //validate argument
    if (inventory >= 0 && inventory >= availableInventory)
    {
        totalInventory = inventory;
        return true;
    }
    
    return false;
}

//---------------------------------------------------------------------------
//setAvailableInventory
//sets the available inventory to amount in argument
//Parameters:
//  -inventory: (int) new available inventory.  Must be a positive integer
//              less than or equal to total inventory
//Return:
//  true if inventory is a valid amount, false otherwise.
bool LibItem::setAvailableInventory(int inventory)
{
    //validate argument
    if (inventory >= 0 && inventory <= totalInventory)
    {
        availableInventory = inventory;
        return true;
    }
    
    return false;
}

//---------------------------------------------------------------------------
//setFormat
//sets format of LibItem to Format passed in argument.
//Parameters:
//  -format: (Format) new format of LibItem
//Returns:
//  true if format is successfully set, false otherwise.
bool LibItem::setFormat(Format format)
{
    this->format = format;
    return true;
}

//---------------------------------------------------------------------------
//setType
//sets CatalogType to type passed in argument
//Parameters:
//  -type: (CatalogType) new CatalogType of LibItem
//Return:
//  true if type is successfully set, false otherwise.
bool LibItem::setType(CatalogType type)
{
    this->type = type;
    return true;
}

//---------------------------------------------------------------------------
//checkIn
//Removes Patron from patronList and updates inventory.  
//Does not deallocate memory.
//Parameters:
//  -patron: (Patron *) pointer to patron to be removed from patronList.
//Return:
//  true if patron is successfully removed from patronList.  Returns false,
//  otherwise
bool LibItem::checkIn(Patron *patron)
{
    if (patron == nullptr) return false;

    //all copies are already checked in.
    if (availableInventory == totalInventory)
    {
        cout << "All library copies are checked in." << endl;
        return false;
    }

    //Iterate through patron list, if found remove from patronList
    //and update inventory
    for (Patron *p : patronList)
    {
        if (*p == *patron)
        {
            patronList.remove(patron);
            availableInventory++;
            return true;
        }
    }

    //patron not found
    cout << patron->getFirstName() << " " << patron->getLastName()
        << " did not check out " << title << endl;
    return false;
}

//---------------------------------------------------------------------------
//checkIn
//Adds Patron to patronList and update inventory.
//Parameters:
//  -patron: (Patron *) pointer to patron to be added to patronList.
//Return:
//  true if patron is successfully added to patronList.  Returns false,
//  otherwise
bool LibItem::checkOut(Patron *patron)
{
    if (patron == nullptr) return false;

    //if no copies are available
    if (availableInventory == 0)
    {
        cout << title 
             << " has no available inventory for check out." << endl;
        return false;
    }

    patronList.push_back(patron);
    availableInventory--;  //decrease available inventory
    
    return true;
}

//---------------------------------------------------------------------------
//getTitle
//Return (string)title of LibItem
string LibItem::getTitle() const
{
    return title;
}

//---------------------------------------------------------------------------
//getTotalInventory
//Return (int)total inventory of LibItem
int LibItem::getTotalInventory() const
{
    return totalInventory;
}

//---------------------------------------------------------------------------
//getAvailableInventory
//Return (int)available inventory of LibItem
int LibItem::getAvailableInventory() const
{
    return availableInventory;
}

//---------------------------------------------------------------------------
//getFormat
//Return (Format)format of LibItem
Format LibItem::getFormat() const
{
    return format;
}

//---------------------------------------------------------------------------
//getType
//Return (CatalogType)type of LibItem
CatalogType LibItem::getType() const
{
    return type;
}

//---------------------------------------------------------------------------
//clearPatronList
//clears the contents of patronList.  Is not responsible for deallocating
//dynamic memory Patron objects contained in patronList.
void LibItem::clearPatronList()
{
    while (!patronList.empty())
    {
        Patron *&temp = patronList.front();
        temp = nullptr;
        patronList.pop_front();
    }
}
