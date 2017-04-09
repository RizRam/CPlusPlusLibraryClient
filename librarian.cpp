/*
Rizky Ramdhani
CSS502
Assignment 4
librarian.cpp - Implementation file for Librarian
*/

#include "librarian.h"
#include "library.h"

//---------------------------------------------------------------------------
//Constructor
Librarian::Librarian(Library *library)
{
    this->library = library;
}

//---------------------------------------------------------------------------
//Copy constructor
//Performs shalow copy
Librarian::Librarian(const Librarian &other)
{
    this->library = other.library;
    
    //copy transaction queue

    clearTransactionQueue();  //clear queue

    for (Transaction *t : other.transactionQueue)
    {
        //copy Transaction
        transactionQueue.push_back(t);
    }
}

//---------------------------------------------------------------------------
//Destructor
//Responsible for deallocating dynamic memory contained in transactionQueue
Librarian::~Librarian()
{
    clearTransactionQueue();
    library = nullptr;

}
//---------------------------------------------------------------------------
//Assignment operator
//Performs shallow copy
Librarian & Librarian::operator=(const Librarian &other)
{
    if (this != &other) //check if same memory address
    {
        this->library = other.library;

        //copy transaction queue

        clearTransactionQueue();  //clear queue

        for (Transaction *t : other.transactionQueue)
        {
            //copy Transaction
            transactionQueue.push_back(t);
        }
    }

    return *this;
}

//---------------------------------------------------------------------------
//executeAll
//Executes all Transaction objects in transaction queue until queue is empty.
//transactionQueue is emptied as the function executes and dynamic memory is
//deallocated.
void Librarian::executeAll()
{
    while (!transactionQueue.empty())
    {
        execute();
    }
}

//---------------------------------------------------------------------------
//execute
//calls execute on the Transaction in the front of the Transaction queue.
//deallocates the Transaction once execute is finished.
void Librarian::execute()
{
    //obtain element at front
    Transaction *temp = transactionQueue.front();
    transactionQueue.pop_front();

    temp->execute();  //execute transaction

    //deallocate Transaction
    delete temp;
    temp = nullptr;
}

//---------------------------------------------------------------------------
//addTransactions
//Insert a Transaction object into transactionQueue.
//Parameters:
//  -trans: (Transaction*) A pointer to Transaction object that is to be
//          inserted into Librarian's transactionQueue.
//Returns:
//  true if insertion was successful, false otherwise.
bool Librarian::addTransaction(Transaction *trans)
{
    if (trans == nullptr) return false;

    transactionQueue.push_back(trans);
    return true;
}

//---------------------------------------------------------------------------
//setLibrary
//Sets the Library passed in the argument to this object's Library
//Parameters:
//  -library: (Library*) Pointer to Library to be assigned to this Librarian
void Librarian::setLibrary(Library *library)
{
    this->library = library;
}

//---------------------------------------------------------------------------
//getLibrary
//getter function for library
//Return:
//  A pointer to Librarian's Library.
Library * Librarian::getLibrary() const
{
    return library;
}

//---------------------------------------------------------------------------
//clearTransactionQueue()
//clears the contents of transactionQueue.  Deallocates dynamic Transaction
//objects.
void Librarian::clearTransactionQueue()
{
    while (!transactionQueue.empty())
    {
        delete transactionQueue.front();
        transactionQueue.pop_front();
    }
}
