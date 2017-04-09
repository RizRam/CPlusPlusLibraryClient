/*
Rizky Ramdhani
CSS502
Assignment 4
hashtable.h - Implementation file for HashTable
*/

#include "hashtable.h"

//---------------------------------------------------------------------------
//Default constructor
HashTable::HashTable()
{
    arr = new Object* [DEFAULT_CAPACITY];
    count = 0;
    capacity = DEFAULT_CAPACITY;

    //initialize arr
    for (int i = 0; i < capacity; i++)
    {
        arr[i] = nullptr;
    }
}

//---------------------------------------------------------------------------
//Copy constructor
//Performs shallow copy
HashTable::HashTable(const HashTable & other)
{
    //copy contents of other
    this->count = other.count;
    this->capacity = other.capacity;
    
    //copy arr

    //delete current array
    clearArray();
    arr = new Object*[capacity];

    for (int i = 0; i < capacity; i++)
    {
        this->arr[i] = other.arr[i];
    }

}

//---------------------------------------------------------------------------
//Destructor
//Deallocates all dynamic memory Objects in internal array.  
//Calls clearArray().
HashTable::~HashTable()
{
    clearArray();
}

//---------------------------------------------------------------------------
//Assignment Operator
//Performs shallow copy
HashTable & HashTable::operator=(const HashTable & other)
{
    if (this != &other)  //check if same memory address
    {
        //copy contents of other
        this->count = other.count;
        this->capacity = other.capacity;

        //copy arr

        //delete current array
        clearArray();
        arr = new Object*[capacity];

        for (int i = 0; i < capacity; i++)
        {
            this->arr[i] = other.arr[i];
        }
    }

    return *this;
}

//---------------------------------------------------------------------------
//getCapacity
//getter for capacity
//Return:
//  (int) capacity of internal array
int HashTable::getCapacity() const
{
    return capacity;
}

//---------------------------------------------------------------------------
//getCount
//getter for count
//Return:
//  (int) count of the number of elements stored in HashTable
int HashTable::getCount() const
{
    return count;
}

//---------------------------------------------------------------------------
//contains
//Determines whether HashTable contains Object passed in argument.  Uses
//Object's equality operator for comparison.
//Parameters:
//  -key: (Object) to be found in HashTable
//Return:
//  true if HashTable contains key, false otherwise.
bool HashTable::contains(const Object &key) const
{
    return getKey(key) != nullptr;
}

//---------------------------------------------------------------------------
//getKey
//Retrieves a pointer to Object stored in HashTable that equals Object
//passed in the argument.  Uses the equality operator of Object 
//for comparison.
//Parameters:
//  -key: (Object) to retrieve in HashTable
//Return:
//  pointer to Object that equals Object passed in argument.  If no Object
//  is found, returns nullptr.
Object * HashTable::getKey(const Object &key) const
{
    //Get initial position
    int h = hash(key);
    int collision = 0;
    int index = getIndex(h, collision);

    //Iterate to find key
    while (arr[index] != nullptr && collision < count)
    {
        if (*arr[index] == key)  //key found
        {
            return arr[index];
        }

        //update collision and index
        collision++;
        index = getIndex(h, collision);
    }

    return nullptr;
}

//---------------------------------------------------------------------------
//insert
//Insert an Object into HashTable.  Average case insertion is O(1), but if,
//the new count / capacity exceeds LOAD_FACTOR, then the array is resized
//to ensure that the count / capacity does not exceed LOAD_FACTOR. 
//Parameters:
//  -o: (Object) to be inserted into HashTable
//Return:
//  true if Object was successfully inserted, false if Object already exists
//  in HashTable
bool HashTable::insert(Object &o)
{
    double loadFactor = (double)((count + 1) / capacity);

    //Check Load Factor
    if (loadFactor > MAX_LOAD_FACTOR)//exceeds load factor
    {
        capacity = getNextCapacity();
        resize(capacity);
    }

    //Get initial position
    int h = hash(o);
    int collision = 0;
    int index = getIndex(h, collision);

    //Iterate to find empty position
    while (arr[index] != nullptr && collision < count)
    {
        if (*arr[index] == o)  //already exists in HashTable
        {
            return false;
        }

        collision++;
        index = getIndex(h, collision);
    }

    //position found.
    arr[index] = &o;

    count++;
    return true;
}

//---------------------------------------------------------------------------
//remove
//Removes Object from HashTable and deallocates Object from memory.
//Parameters:
//    -o: (Object) to be removed from HashTable
//Return:
//  true if Object was successfully removed from HashTable or if Object is
//  not in the HashTable.
bool HashTable::remove(const Object &o)
{
    //Get initial position
    int h = hash(o);
    int collision = 0;
    int index = getIndex(h, collision);

    while (arr[index] != nullptr && collision < count)
    {
        if (*arr[index] == o)  //Object found
        {
            delete arr[index];
            arr[index] = nullptr;

            count--;
            return true;
        }

        collision++;
        index = getIndex(h, collision);
    }

    return true;
}

//---------------------------------------------------------------------------
//hash
//Obtains a hash value of Object passed in argument used to determine index
//position in array.
//Parameters:
//  -o: (Object) to be evaluated
//Return:
//  (int) the hash value of Object passed in argument. 
//  (Must be positive integer)
int HashTable::hash(const Object &o) const
{
    int result = o.getHashCode();
    if (result < 0)
        result *= -1;

    return result;
}

//---------------------------------------------------------------------------
//dist
//Determines the step size between the initial index position and the current
//index position to be evaluated based on the amount of collisions that 
//has already occured.  Uses formula dist(i) = i^2. Where i is the number of
//collisions.
//Parameters:
//  -collision: (int) the number of collisions.  Must be a positive integer.
//              negative collision numbers treated as 0 collisions.
//Return:
//  (int) the step size
int HashTable::dist(int collision) const
{
    //argument validation
    if (collision < 0) collision = 0;

    return collision * collision;
}

//---------------------------------------------------------------------------
//getIndex
//Returns an index position in internal array based on the values of hash()
//and collisions passed in the argument.
//Formula: index = (hash() + dist(collisions)) % capacity;
//Parameters:
//  -h: (int) hash value
//  -coll: (int) number of collisions
//Return:
//  (int) the index position in internal array.
int HashTable::getIndex(int h, int coll) const
{
    int result = h + dist(coll);
    return result % capacity;
}

//---------------------------------------------------------------------------
//resize
//Resizes internal array capacity to integer passed passed in argument.
//O(n) operation.
void HashTable::resize(int n)
{
    Object **old = arr;
    int oldCapacity = capacity;

    //Initialize new array
    capacity = n;
    count = 0;
    arr = new Object*[capacity];

    for (int i = 0; i < capacity; i++)
    {
        arr[i] = nullptr;
    }

    //Reinsert values from old array
    for (int i = 0; i < oldCapacity; i++)
    {
        if (old[i] != nullptr)  //if there is an element
        {
            insert(*old[i]);  //insert into HashTable
        }
    }

    //delete old array without deallocating element memory
    delete[] old;
    old = nullptr;
}

//---------------------------------------------------------------------------
//getNextCapacity
//Find the next valid capacity value to resize the array.
//Formula:  2c < k = p.  The next capacity (k) is greater than twice 
//          the current capacity(p) and equals a prime number(p).
//Return:
//  (int) the next valid capacity.
int HashTable::getNextCapacity()
{
    return findNextPrime((capacity * 2) + 1);
}

//---------------------------------------------------------------------------
//findNextPrime
//Finds the next prime number.  Does not handle integer overflow.
//Parameter:
//  -n: (int) the value the prime number must be larger than.
//      Must be a positive integer.
//Return:
//  (int) next prime value.
int HashTable::findNextPrime(int n)
{
    if (n == 0) return 1;
    if (n == 1) return 2;

    if (n % 2 == 0) n++;  //if even number, increment to odd number.

    while (!isPrime(n))
    {
        n += 2;  //only evaluate odd values
    }  

    return n;
}

//---------------------------------------------------------------------------
//isPrime
//Determines whether n is a prime number.
//Parameter:
//  -n: (int) value to be evaluated.  n must be at least 3.
//Return:
//  true if n is a prime number, false otherwise.
bool HashTable::isPrime(int n)
{
    for (int i = 3; true; i += 2)  //only evaluate odd divisors
    {
        int q = n / i;
        if (q < i)
            return true;
        if (n == q * i)
            return false;  
    }

    return true;
}

//---------------------------------------------------------------------------
//clearArray
//Deallocates all dynamic memory in internal array.
//Resets count and capacity to 0.
void HashTable::clearArray()
{
    //Iterate and deallocate Object*
    for (int i = 0; i < capacity; i++)
    {
        delete arr[i];
        arr[i] = nullptr;
    }

    //set arr to nullptr
    delete[] arr;
    arr = nullptr;

    //reset count and capacity
    count = 0;
    capacity = 0;
}