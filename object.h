

/****************************************************************************
* Ben Pittman - David Nixon - Mike Chavez - Rizky Ramdhani
* CS 502A Winter 2017
* HW 4
* object.h - Header file for Object
****************************************************************************/

#pragma once

#include <iostream>

using namespace std;

/*
//---------------------------------------------------------------------------
                                Object
Abstract superclass that all data classes (Patron, Periodical, etc.)
inherit from.  All functions in this class are pure virtual.  Contains no
data members.
Features:
    -prints description of this object to console
    -comparison operators
    -get hash code (unique int of each instance)
//---------------------------------------------------------------------------
*/

class Object {
public:
    //output operator
    friend ostream & operator<<(ostream &out, const Object& o) 
    {
        return o.print(out);
    }

    Object() {} //default constructor
    Object(const Object&) {} //copy constructor
    virtual ~Object() {} //destructor
    Object & operator=(const Object &)  //assignment operator
    {
        return *this;
    }

    //pure virtual function
    //returns an ostream that prints the contents of Object
    virtual ostream & print(ostream &) const = 0;

    //pure virtual function
    //returns a unique hash code for each object of Object
    virtual int getHashCode() const = 0;

    //pure virtual functions
    //comparison operators
    virtual bool operator<(const Object&) const = 0;
    virtual bool operator>(const Object&) const = 0;  
    virtual bool operator==(const Object&) const = 0;
    virtual bool operator!=(const Object&) const = 0;
    virtual bool operator<=(const Object&) const = 0;
    virtual bool operator>=(const Object&) const = 0;
};



