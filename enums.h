/*
Rizky Ramdhani
CSS 502
Assignment 4
enums.h - contains enums and static constants to be used in Assignment 4
*/

#pragma once  //unsure if this is needed

#include <string>

using namespace std;

//Number of Catalogs stored in Library.  Each Catalog stores a different
//type of Library Items.  Could also be interpreted as total number of
//supporeted LibraryItem types.
static const int NUM_CATALOGS = 3;

//The starting inventory for Book objects when they are instantiated into
//Library
static const int DEFAULT_BOOK_INVENTORY = 5;

//The starting inventory for Periodical objects when they are instantiated 
//to Library
static const int DEFAULT_PERIODICAL_INVENTORY = 1;

//Enum to describe the type of LibItem
enum CatalogType 
{ 
    Y,  //Children's Books
    F,  //Fiction Books
    P,  //Periodicals
    U  //Undefined
};

//Array of valid CatalogType values
static const CatalogType VALID_CATALOGTYPES[]{ Y, F, P };

static string getCatalogTypeString(CatalogType type)
{
    switch (type)
    {
    case Y:
        return "Children's Book";
        break;
    case F:
        return "Fiction";
        break;
    case P:
        return "Periodical";
        break;
    default:
        return "Uncategorized";
        break;
    }
}

//Enum to describe format of LibItem
enum Format 
{
    HC = 'H',  //Hardcover
    SC = 'S',  //Softcover
    DG = 'D',  //Digital
    UD         //Undefined
};

//Number of valid Format values
static const int NUM_VALID_FORMAT = 3;

//Check if Format is valid
static const bool isValidFormat(Format f)
{
    switch (f)
    {
    case HC:
        return true;
        break;
    case SC:
        return true;
        break;
    case DG:
        return true;
        break;
    default:
        return false;
        break;
    }
}

//Enum of Transaction types
enum TransactionType
{
    C = 'C',  //Check Out
    R = 'R',  //Return / Check In
    H = 'H',  //Patron history
    D = 'D'   //Display inventory
};

//Display constants used to help with formatting console outputs
static const int PATRON_ID_WIDTH = 6;
static const int CHECKOUT_WIDTH = 10;
static const int TITLE_WIDTH = 29;
static const int AUTHOR_WIDTH = 19;
static const int YEAR_WIDTH = 4;
static const int FORMAT_WIDTH = 8;
static const int MONTH_WIDTH = 7;
static const int TYPE_WIDTH = 15;