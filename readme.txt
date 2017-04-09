Rizky Ramdhani
CSS 502
Assignment 4
readme.txt - READ ME

//-----------------------------------------------------------------------------
1.  State of Program

    Everything works as specified in the assignment.

2.  HashTables

    -HashTable: A HashTable class I coded that uses an array of Object* for
		implementation.  Object is a superclass that all data classes
		inherit from. (hashtable.h)

    -Catalog:	A Collection class that stores LibItem objects.
		Uses a combination of BinTree (BST) and HashTable class 
		to store LibItems (provides O(1) retrieval and 
		O(log n) insertion). (catalog.h)
    
    -PatronDB:	A HashTable object that stores Patron instances. (library.h)

    -libraryCatalogs:	A simple HashTable that stores Catalog objects.
			Hashes on CatalogType enum defined in "enums.h".
			(library.h)

3.  Read book data

    The Book init file is passed into the constructor of Library (library.h)

    ->Library::Library(string catalogFile, string peopleFile),
	which calls 

    ->Library::initializeCatalogs(string datafile).
	This function instantiates a LibItemFileReader, which takes in
	a reference to Library as well as the file path, and then calls

    ->LibItemFileReader::populateItems().
	This function parses the data file and instantiates new LibItem
	objects using LibItemFactory.  Polymorphism is used to set the data.
	populateItems() also inserts the new objects into library by calling

    ->Library::insertLibraryItem(LibItem &item).
	Item's CatalogType is used to hash into libraryCatalog in Library
	to obtain the proper Catalog for insertion.

    ->Catalog::insert(LibItem &item)
	Inserts into Catalog's Hashtable by calling

    ->HashTable::insert(Object &o).
	If this insertion is successful, then a new NodeData is created
	setting item into NodeData's data member followed by a call to

    ->BinTree::insert(NodeData *data)
	to complete insertion to Catalog.

4.  Read command data

    Library (library.h) has a function called 
    
    ->Library::readCommands(string transactionFile), 
	which instantiates a TransactionFileReader object.

    ->TransactionFileReader::parseAndPopulateLibrarian()
	is then called to parse the input file, generate Transaction objects
	with the help of the TransactionFactory class, and insert the
	Transactions into a Transaction manager class called Librarian using

    ->Librarian::addTransaction(Transaction *trans).
	This function adds pointers to Transaction objects to a queue of
	Transaction pointers.  Transactions are executed in a FIFO manner
	by calling either

    ->Librarian::execute() or Librarian::executeAll().
	Either method takes Transactions in Librarians queue and calls that
	Transaction's 

    ->virtual Transaction::execute().

5.  Dirty little secrets

    Switches:
    My program uses polymorphism to avoid having switches when parsing
    through the input files.  There are switch commands, but they reside
    within my Factory classes.  Some switch commands are used to aid in
    the displays to help generate the correct column headers as well as
    validate enum values that are not consecutive.

    The switches in the factory are unavoidable since my factories
    instantiate objects into the heap and return a pointer to the objects,
    rather than returning copies of objects.

    The display switches do not violate the open-closed design principle,
    because I don't believe that my data classes should know how to
    display a collection of themselves.  The data class should only know
    how to display itself.
    
    Misc:
    My Transaction classes also act as their own exception, because
    I needed to find a way to pass errors that occur when setting data
    members, higher up the chain.  I feel it works elegantly with
    the TransactionFileReader and the Librarian classes, but I also feel
    that the Transaction classes are performing a service outside of their
    scope.

    I know that classes that have ownership of the elements or data members
    within them (Library, Librarian, CheckIn, CheckOut, etc.). Should perform 
    deep copies of those elements in the copy constructor and the assigment 
    operator.  Unfortunately, due to time constraints, only shallow copies are
    performed in these classes.

6.  Proud Features

    -My program is well documented, I feel that it's fairly easy to follow 
     along and the code itself can act as its own documentation.

    -I coded a fully functional HashTable class that uses quadratic probing
     for collision resolution.  It is able to resize itself to a new capacity
     if the load factor is too high.  The new capacity will always be a prime 
     number (the prime number calculation is not the most efficient but it
     works well enough for my purposes).

    -My program is also highly scalable. Other than changing the format of
     the input file (which is the result of avoiding switches), adding new
     features means minimal changes to the current functions.

     For example:

     If you wanted to add a new type of library item, all you
     have to do is:
	-Create the new data class using the proper inheritances.
	-Add two lines to the LibItemFactory::create()
	-Modify "enums.h" (Contains enums and constants) to accomodate the 
	 new type.

     If you wanted to implement an Undo feature to the commands:
	-Modify Librarian (Transaction Manager) to include a stack to move 
	 Transaction objects into after they have been executed.
	-Modify Librarian logic to work with the undo stack
	-Modify Transaction objects to have undo() as well as execute()

     If you wanted to implement a GUI or menu system:
	-Code GUI or menu.
	-Use existing Command Pattern design and implementation (e.g. link
	 Transaction objects and Librarian to buttons).
	-Pass a reference to Library or Librarian.
	-No need to modify existing code.

    -I'm also proud of the execution of the Command Pattern in the program.
     I've provided enough safe access to the members in Library so that
     additional functionality can be implemented with Transaction objects
     rather than additional functions to the Library class.

    -NO MEMORY LEAKS!
