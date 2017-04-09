/*
Rizky Ramdhani
CSS502
Assignment 4
catalog.cpp - Implementation file for Catalog
*/

#include "catalog.h"
#include "libitem.h"

//---------------------------------------------------------------------------
//Default constructor
Catalog::Catalog() 
{
    type = CatalogType::U;
}

//---------------------------------------------------------------------------
//Destructor
Catalog::~Catalog() {}

//---------------------------------------------------------------------------
//Copy constructor
//Performs shallow copy
Catalog::Catalog(const Catalog &other)
{
    this->table = other.table;
    this->tree = other.tree;
    this->type = other.type;
}

//---------------------------------------------------------------------------
//Assignment Operator
//Performs shallow copy
Catalog & Catalog::operator=(const Catalog &other)
{
    if (this != &other) //check if same memory addres
    {
        this->table = other.table;
        this->tree = other.tree;
        this->type = other.type;
    }

    return *this;
}

//---------------------------------------------------------------------------
//insert
//Inserts LibItem into Catalog
//Parameters:
//  -item: (LibItem) item to be inserted into Catalog.  Must be valid item.
//Return:
//  true if insertion was successful, returns false is unsuccessful or
//  if Catalog already contains the item.
bool Catalog::insert(LibItem &item)
{
    //HashTable insertion
    if (table.insert(item))  //if hashtable insertion is successful
    {
        //Tree insertion
        NodeData *temp = new NodeData();
        temp->setData(&item);
        return tree.insert(temp);
    }

    return false;
}

//---------------------------------------------------------------------------
//remove
//Removes LibItem from Catalog.  If removed, LibItem memory in Catalog will
//be deallocated.
//Parameters:
//  -item: (LibItem *) item to be removed from Catalog.
//Return:
//  true if item is removed from Catalog or item was not already in the
//  catalog.
bool Catalog::remove(LibItem *item)
{
    //Tree Removal
    NodeData *junk;
    NodeData nd;
    nd.setData(item);
    if (tree.remove(nd, junk))  //if tree removal successful
    {
        junk = nullptr;  //not responsible for deallocating memory

        //Table removal and deallocation
        return table.remove(*item);
    }
    
    return false;
}

//---------------------------------------------------------------------------
//Setter for type
//Parameters:
//  -type: (CatalogType) to b
void Catalog::setType(CatalogType type)
{
    this->type = type;
}

//---------------------------------------------------------------------------
//getCount
//Returns the current number of LibItems in Catalog
//Return:
//  (int) number of elements in Catalog
int Catalog::getCount() const
{
    return table.getCount();
}

//---------------------------------------------------------------------------
//Getter for type
//Return:
//  (CatalogType) the type of LibItems stored in this Catalog
 CatalogType Catalog::getCatalogType() const
{
    return type;
}

//---------------------------------------------------------------------------
//contains
//Determines whether Catalog contains LibItem passed in argument.
//Parameters:
//  -item: (LibItem) to be found in Catalog
//Return:
//  true if item is in Catalog, false otherwise.
bool Catalog::contains(const LibItem &item) const
{
    return getItem(item) != nullptr;
}

//---------------------------------------------------------------------------
//getItem
//Returns a pointer to LibItem in Catalog that equals the LibItem passed
//in the argument.  Uses internal HashTable for O(1) retrieval.
//Parameters:
//  item: (LibItem) to retrieve from Catalog
//Return:
//  Pointer to LibItem found in Catalog.  If LibItem is not found, return
//  nullptr.
LibItem * Catalog::getItem(const LibItem &item) const
{
    return static_cast<LibItem *>(table.getKey(item));  //safely cast to LibItem
}

//---------------------------------------------------------------------------
//toSortedVector
//Returns a sorted vector of pointers to LibItem elements in Catalog.
//Uses internal binary search tree traversal to populate the vector.
//Return:
//  vector<LibItem *>
vector<LibItem*> Catalog::toSortedVector() const
{
    vector<LibItem *> result;

    vector<Object *> temp = tree.toSortedVector();

    for (Object *o : temp)
    {
        result.push_back(static_cast<LibItem *>(o));  //safely cast to LibItem
    }

    return result;    
}

//---------------------------------------------------------------------------
//Output operator
ostream & operator<<(ostream &out, const Catalog &c)
{
    vector<LibItem *> temp = c.toSortedVector();
    for (LibItem *li : temp)
    {
        out << "\t" << *li << endl;
    }

    return out;
}
