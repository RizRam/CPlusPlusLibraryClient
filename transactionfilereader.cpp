/*
Rizky Ramdhani
CSS502
Assignment 4
transactionfilereader.cpp - Implementation File for TransactionFileReader
*/

#include "transactionfilereader.h"
#include "librarian.h"
#include "displayerror.h"
#include <iostream>
#include <sstream>

using namespace std;

//---------------------------------------------------------------------------
//Constructor
TransactionFileReader::TransactionFileReader(
    string fileName, Librarian *librarian)
{
    this->fileName = fileName;
    this->librarian = librarian;
}

//---------------------------------------------------------------------------
//Destructor
//Does not deallocate dynamic memory
TransactionFileReader::~TransactionFileReader()
{
    this->librarian = nullptr;
}

//---------------------------------------------------------------------------
//Copy constructor
//shallow copy
TransactionFileReader::TransactionFileReader(
    const TransactionFileReader &other)
{
    this->fileName = other.fileName;
    this->librarian = other.librarian;
}

//---------------------------------------------------------------------------
//Assignment operator
//shallow copy
TransactionFileReader & TransactionFileReader::operator=(
    const TransactionFileReader &other)
{
    if (this != &other)
    {
        this->fileName = other.fileName;
        this->librarian = other.librarian;
    }
    return *this;
}

//---------------------------------------------------------------------------
//parseAndPopulateLibrarian
//Parses the input file and fills Librarians's transaction queue with new
//Transaction objects made with TransactionFactory and the data provided by
//the input file.
//Example Input:
//  D
//  H 1000
//  C 8888 F H Forster E. M., The Longest Journey,
//  C 1111 P H 2010 1 Communications of the ACM,
//  C 1111 Y H Danny Dunn & the Homework Machine, Williams Jay,
//  R 8000 F H Kerouac Jack, On the Road,
void TransactionFileReader::parseAndPopulateLibrarian() const
{
    if (librarian == nullptr) return;  //no librarian

    ifstream inFile(fileName);
    if (!inFile)  //Validate input file
    {
        //Create DisplayError
        string message = "Invalid command file";
        DisplayError *error = new DisplayError(message);
        librarian->addTransaction(error);

        error = nullptr;

        return;
    }

    while (!inFile.eof())
    {
        Transaction *command = nullptr;
        //read command type
        char c, next;
        inFile >> c;

        if (inFile.eof()) return;
        next = inFile.get();  //get and remove space after command type

        //create Transaction
        command = factory.create(static_cast<TransactionType>(c));
        if (command != nullptr)  //valid command code
        {
            command->setDataFromFile(inFile);  //set Transaction data

            //check for setData errors in Transaction
            string errorMessage = command->getErrorMessage();
            if (errorMessage != string())  //error occurred
            {
                //set command to DisplayError
                Transaction *temp = command;  //assign command to temp
                command = new DisplayError(errorMessage);

                //delete temp
                delete temp;
                temp = nullptr;
            }

            command->setLibrary(librarian->getLibrary());  //assign library
            librarian->addTransaction(command);  //add to transaction queue
        }
        else  //invalid command code
        {
            stringstream message;
            message << "Invalid command code (" << c << ").";

            DisplayError *error = new DisplayError(message.str());
            librarian->addTransaction(error);
            error = nullptr;

            //read to end of the line if not already at end of line
            if (next != '\n')
            {
                string s;
                getline(inFile, s);
            }
        }

        command = nullptr;
    }
}


