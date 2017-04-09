/*
Rizky Ramdhani
CSS502
Assignment 4
catalog.h - Header file for Catalog
*/

#pragma once

#include "hashtable.h"
#include "bintree.h"
#include "enums.h"
#include <ostream>

/*
//---------------------------------------------------------------------------
                               Catalog

Abstract Data Type to contain LibItems.  Maintains collection with sorted
order and has retrieval of O(1).  Responsible for deallocating dynamic memory
in collection.

Features:
-Insertion, Removal
-Retrieval, Contains
-toSortedVector

Implementation:
Uses a combination of a HashTable
and a Binary Search Tree to store elements.  Both the HashTable and the
Binary Search Tree contain pointers to the same LibItem objects in heap.
HashTable is used to provide O(1) retrieval.  Binary Search Tree BinTree
is used keep the collection of LibItems in sorted order based on the
individual LibItems ordering.  Because a Binary Search Tree is used,
insertion and removal are O(log n) with worst case scenario O(n). BinTree
is not a self-balancing tree.

Catalog is responsible for deallocating dynamic memory objects contained
in the collection by emptying the internal data structures.
While both HashTable and BinTree point to the same objects in the heap,
ONLY HashTable is responsible for deallocating dynamic memory objects
contained in the collection.

//---------------------------------------------------------------------------
*/

class LibItem;

class Catalog
{
    friend ostream & operator<<(ostream &, const Catalog &);

public:
    Catalog();  //Default constructor
    ~Catalog();  //Destructor
    Catalog(const Catalog &); //Copy constructor
    Catalog & operator=(const Catalog &);  //Assignment operator

    //MUTATORS
    bool insert(LibItem &);  //Insert LibItem into Catalog
    bool remove(LibItem *);  //Remove LibItem from Catalog
    void setType(CatalogType);  //Setter for type

    //ACCESSORS
    int getCount() const;  //Return count of elements in Catalog
    CatalogType getCatalogType() const;  //getter for type

    //Determine whether LibItem is in Catalog
    bool contains(const LibItem &) const;  

    //Return a pointer to LibItem in Catalog
    LibItem * getItem(const LibItem &) const;

    //Return a sorted vector of pointers to LibItems in Catalog
    vector<LibItem *> toSortedVector() const;

private:
    HashTable table;  //HashTable
    BinTree tree;  //Binary Search Tree
    CatalogType type;  //Type of LibItems
};
