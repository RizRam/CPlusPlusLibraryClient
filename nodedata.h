/*
Rizky Ramdhani
CSS502
Assignment 4
Nodedata.h - Header file for NodeData from Assignment 2.
Header file is modified to work with Assignment 4 implementation.
*/

#pragma once

#include <iostream>
#include "object.h"
using namespace std;

//---------------------------------------------------------------------------
//                              NodeData
//class to be used exclusively with BinTree to store data (Object*).
//Features:
//  -comparison operators
//  -output to console
//NodeData is not responsible for deallocating dynamic memory stored in data.
//---------------------------------------------------------------------------

class NodeData {
   friend ostream & operator<<(ostream &, const NodeData &);

public:
    NodeData();          // default constructor, data is set to an empty string
    ~NodeData();          
    NodeData(const NodeData &);         // copy constructor
    NodeData& operator=(const NodeData &);

    Object * getData() const; //getter for data

    // returns true if the data is set, false when bad data.        
    void setData(Object *);      // data is set to parameter

    // comparison operators
    bool operator==(const NodeData &) const;
    bool operator!=(const NodeData &) const;
    bool operator<(const NodeData &) const;
    bool operator>(const NodeData &) const;
    bool operator<=(const NodeData &) const;
    bool operator>=(const NodeData &) const;

private:
    Object *data;   //data stored in NodeDota
};

