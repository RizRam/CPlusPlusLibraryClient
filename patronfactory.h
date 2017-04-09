/******************************************************************************
 * Ben Pittman - David Nixon - Mike Chavez - Rizky Ramdhani
 * CS 502A Winter 2017
 * HW 4
 * patronfactory.h - Header file for PatronFactory
 * A class that creates empty Patron objects.  Factory has no ownership to the
 * objects it creates.
 ******************************************************************************/

#pragma once

 /*
 //---------------------------------------------------------------------------
                                    PatronFactory

 A factory class to generate empty Patron objects.

 //---------------------------------------------------------------------------
 */

class Patron;

class PatronFactory {
public:
   PatronFactory(); // constructor
   PatronFactory(const PatronFactory& otherPatronFactory); // copy constructor
   ~PatronFactory(); // destructor
   PatronFactory & operator=(const PatronFactory &); // assignment operator   
   
   Patron * create(int) const;  //returns a pointer to an empty Patron object   
};
