/*
Rizky Ramdhani
CSS502
Assignment 4
libitemfactory.cpp - Implementation for LibItemFactory
*/

#include "libitemfactory.h"
#include "childrensbook.h"
#include "fictionbook.h"
#include "periodical.h"

//---------------------------------------------------------------------------
//Assignment Operator
LibItemFactory & LibItemFactory::operator=(const LibItemFactory &)
{
    return *this;
}

//---------------------------------------------------------------------------
//create
//Creates a new instance of a LibItem object that depends on the CatalogType
//Parameters:
//  -type: Enum CatalogType 
LibItem * LibItemFactory::create(CatalogType type) const
{
    //LibItem *result;
    switch (type)
    {
    case Y:
        return new ChildrensBook();
        break;
    case F:
        return new FictionBook();
        break;
    case P:
        return new Periodical();
        break;
    default:
        return nullptr;
        break;
    }
}

//---------------------------------------------------------------------------
//create
//Creates a new instance of a LibItem object that depends on the char
//argument
//Parameters:
//  -type: (char) the type of LibIten 
LibItem * LibItemFactory::create(char type) const
{    
    switch (type)
    {
    case 'Y':
        return new ChildrensBook();
        break;
    case 'F':
        return new FictionBook();
        break;
    case 'P':
        return new Periodical();
        break;
    default:
        return nullptr;
        break;
    }    
}
