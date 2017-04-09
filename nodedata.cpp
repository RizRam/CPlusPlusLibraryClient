/*
Rizky Ramdhani
CSS502
Assignment 4
Nodedata.cpp - Implementation file for NodeData from Assignment 2.
Implementation file is modified to work with Assignment 4 implementation.
*/

#include "nodedata.h"

//------------------- constructors/destructor  -------------------------------
NodeData::NodeData() { data = nullptr; }                         // default

NodeData::~NodeData() { data = nullptr; }

NodeData::NodeData(const NodeData& nd) { data = nd.data; }  // copy

//------------------------- operator= ----------------------------------------
NodeData& NodeData::operator=(const NodeData& rhs) {
   if (this != &rhs) {
      data = rhs.data;
   }
   return *this;
}

Object * NodeData::getData() const
{
    return data;
}

void NodeData::setData(Object *o)
{
    data = o;
}

//------------------------- operator==,!= ------------------------------------
bool NodeData::operator==(const NodeData& rhs) const {
   return *data == *rhs.data;
}

bool NodeData::operator!=(const NodeData& rhs) const {
   return *data != *rhs.data;
}

//------------------------ operator<,>,<=,>= ---------------------------------
bool NodeData::operator<(const NodeData& rhs) const {
   return *data < *rhs.data;
}

bool NodeData::operator>(const NodeData& rhs) const {
   return *data > *rhs.data;
}

bool NodeData::operator<=(const NodeData& rhs) const {
   return *data <= *rhs.data;
}

bool NodeData::operator>=(const NodeData& rhs) const {
   return *data >= *rhs.data;
}


//-------------------------- operator<< --------------------------------------
ostream& operator<<(ostream& output, const NodeData& nd) {
   output << *nd.data;
   return output;
}

