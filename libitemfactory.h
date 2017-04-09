/******************************************************************************
* Ben Pittman - David Nixon - Mike Chavez - Rizky Ramdhani
* CS 502A Winter 2017
* HW 4
* libitemfactory.h - Header file for LibItemFactory
******************************************************************************/

#pragma once

#include "enums.h"
#include "libitem.h"

/*
//---------------------------------------------------------------------------
                                LibItemFactory
Class used in Factory pattern to instantiate empty LibItem derived objects
Does not have ownership of instantiated objects.
//---------------------------------------------------------------------------
*/

using namespace std;

class LibItemFactory {
public:
    LibItemFactory() {}  //Default Constructor
    ~LibItemFactory() {}  //Destuctor
    LibItemFactory(const LibItemFactory &) {} //Copy Constructor
    LibItemFactory & operator=(const LibItemFactory &);  //Assignment Operator 

    //creates a new empty LibItem object
    LibItem * create(CatalogType type) const;  
    LibItem * create(char type) const;
};
