/******************************************************************************
 * Ben Pittman - David Nixon - Mike Chavez - Rizky Ramdhani
 * CS 502A Winter 2017
 * HW 4
 * librarian.h - Header file for Librarian
 ******************************************************************************/

#pragma once

#include <list>
#include "transaction.h"
#include "transactionfactory.h"

using namespace std;

/*
//---------------------------------------------------------------------------
                                Librarian
A class used in Command Pattern implementation of the Library 
system (Invoker).  This class manages a queue of Transaction objects
and these objects execute commands on the Library.  Commands are executed in
FIFO fashion.
Implementation:
    -Uses STL List<Transaction *> for its queue.  Which is a doubly linked
     list.  O(1) insertion and removal.
    -This class is responsible for deallocating dynamic Transaction memory
     objects contained within it.
    -Transaction objects will be automatically deallocated once they are
     executed
//---------------------------------------------------------------------------
*/

class Library;

class Librarian {
public:
   Librarian(Library *); // constructor takes a Library
   Librarian(const Librarian &); // copy constructor
   ~Librarian(); // destructor
   Librarian & operator=(const Librarian &); // assignment operator

   // executes all transactions in the transactionQueue in order
   void executeAll();

   void execute();  //executes the next Transaction in queue;
   
   //adds a Transaction Object to the queue.
   bool addTransaction(Transaction *trans);

   void setLibrary(Library *);  //setter for library

   Library * getLibrary() const; //returns a pointer to Library
   
private:
   Library *library;  //reference to Library

   //Queue of Transaction Objects for execution
   list<Transaction *> transactionQueue;  

   //clears the contents of transaction queue
   void clearTransactionQueue();  
};











