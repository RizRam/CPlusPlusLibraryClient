/****************************************************************************
* Ben Pittman - David Nixon - Mike Chavez - Rizky Ramdhani
* CS 502A Winter 2017
* HW 4
* hashtable.h
* Abstract Class Template that provides the functionality of a HashTable
* Features:
*   -Contains accessors for capacity, count
*   -contains()
*   -getKey()
*   -toArray()
*   -insertion and removal
* Implementation:
*   -Uses an array to store elements
*   -array capacity is determined by a maximum load factor of 0.5.  
*    Meaning that if the (number of elements / capacity of the array) is 
*    greater than 0.5, then the array is resized to a larger capacity 
*    of at least double the current capacity to the nearest prime 
*    and each element is then reinserted / rehashed into the larger array.
*   -Capacity is always a prime number to reduce the frequency of collisions 
*    during insertion.
*   -Collision is handled by open addressing, elements are stored directly
*    in the internal array.
*   -Index position is determined by hash() + dist(# of collision). 
*    Where hash is the initial index value determined by Object's 
*    getHashCode() and dist(# of collision) is the step size of the next
*    position to check after a collision occurs.
*   -HashTable WILL DEALLOCATE dynamic memory contained within its collection
****************************************************************************/

#pragma once

#include "object.h"

//factor to decide whether internal array needs to be resized.
static const double MAX_LOAD_FACTOR = 0.5;

//default capacity
static const int DEFAULT_CAPACITY = 211;

class HashTable {

public:
    HashTable();  //default Constructor
    HashTable(const HashTable &other);  //copy constructor
    ~HashTable();  //destructor

    HashTable& operator=(const HashTable &other);  //assignment operator    

    //ACCESSORS
    int getCapacity() const;  //return capacity of the HashTable
    int getCount() const;  //return the number of elements in the HashTable

    //returns whether element is inside the HashTable
    bool contains(const Object&) const;  

    //returns object in HashTable that matches the key passed in the argument
    virtual Object * getKey(const Object&) const;

    //MUTATORS
    bool insert(Object&);  //Adds an item into the HashTable
    bool remove(const Object&);  //Remove item from the HashTable

private:
    Object **arr;  //array of Object*, internal data structure for HashTable
    int capacity;  //capacity of arr
    int count;  //total elements in arr

    //returns the initial index position in arr for content evaluation
    int virtual hash(const Object &) const;  

    //dist function to determine the next index position to evaluate
    //after a collision.
    int virtual dist(int) const;

    //get an index position in array based on the hash value and 
    //the number of collisions evaluated so far.
    int getIndex(int h, int coll) const;

    void resize(int n); //resizes the array and rehash
    int getNextCapacity();  //get the next valid capacity to resize array
    int findNextPrime(int n);  //Finds the next prime number ascending.
    bool isPrime(int n);  //determines whether n is a prime number.

    //deletes all alements in arr and deallocates dynamic memory 
    //object stored in array
    void clearArray();  
};
