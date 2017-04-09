/*
Rizky Ramdhani
CSS502
Assignment 4
main.cpp - Driver and simple tests for Assignment 4
*/

#include "library.h"
#include "childrensbook.h"
#include "fictionbook.h"
#include "periodical.h"
#include "displayinventory.h"


//Test LibItem 
void LibItemTest()
{
    ChildrensBook *temp;
    temp = new ChildrensBook();
    temp->setFormat(HC);
    temp->setType(Y);
    temp->setTitle("test title");
    temp->setAuthor("test author");
    temp->setTotalInventory(5);
    temp->setAvailableInventory(1);
    temp->setYear(2001);

    cout << *temp << endl;

    delete temp;
    temp = nullptr;

    FictionBook book = FictionBook("fiction title", F, HC, "fiction author", 2000, 5);
    cout << book << endl;
}

void LibItemRetrieveTestHelper(const LibItem& item, const Library &library)
{
    LibItem *temp = library.findLibraryItem(item);
    if (temp != nullptr)
        cout << *temp << endl;
    else
        cout << "NOT FOUND" << endl;

    temp = nullptr;
}

//Test retrieval of LibItem from Library
void LibItemRetriveTest()
{
    Library library = Library("data4books.txt", "data4patrons.txt");
    DisplayInventory display;
    display.setLibrary(&library);
    display.execute();

    //Y Butterworth Emma Macalik, As the Waltz was Ending, 1982
    ChildrensBook c;
    c.setAuthor("Butterworth Emma Macalik");
    c.setTitle("As the Waltz was Ending");
    c.setType(Y);

    //Y Seuss Dr., Horton hears a Who, 1954
    ChildrensBook c2;
    c2.setAuthor("Seuss Dr.");
    c2.setTitle("Horton hears a Who");
    c2.setType(Y);

    //F Kerouac Jack, On the Road, 1955
    FictionBook f;
    f.setAuthor("Kerouac Jack");
    f.setTitle("On the Road");
    f.setType(F);

    //F Daheim Mary, Fowl Prey, 1991
    FictionBook f2;
    f2.setAuthor("Daheim Mary");
    f2.setTitle("Fowl Prey");
    f2.setType(F);

    //P Communications of the ACM, 1 2010
    Periodical p;
    p.setTitle("Communications of the ACM");
    p.setMonth(1);
    p.setYear(2010);
    p.setType(P);

    //P Sigart Bulletin, 7 2009
    Periodical p2;
    p2.setTitle("Sigart Bulletin");
    p2.setMonth(7);
    p2.setYear(2009);
    p2.setType(P);
    
    LibItemRetrieveTestHelper(c, library);
    LibItemRetrieveTestHelper(c2, library);
    LibItemRetrieveTestHelper(f, library);
    LibItemRetrieveTestHelper(f2, library);
    LibItemRetrieveTestHelper(p, library);
    LibItemRetrieveTestHelper(p2, library);
}

//Test Patron output
void PatronTest()
{
    Patron temp(1000);
    temp.setFirstName("Fake");
    temp.setLastName("Fake");

    cout << temp << endl;
}

//Test Retrieving Patron
void PatronRetrieveTest()
{
    Library library = Library("data4books.txt", "data4patrons.txt");

    Patron temp(9999);
    temp.setFirstName("Mickey");
    temp.setLastName("Duck");

    cout << temp << endl;

    Patron *found = library.findPatron(temp);

    if (found != nullptr)
        cout << *found << endl;
    else
        cout << "Patron not found." << endl;
    
}

//Test Commands
void CommandsTest()
{
    Library library = Library("data4books.txt", "data4patrons.txt");
    library.readCommands("commandstest2.txt");
}

//Execuites requirements of Assignment 4
void executeProgram()
{
    Library library = Library("data4books.txt", "data4patrons.txt");
    library.readCommands("data4commands.txt");
}

int main() 
{
    //LibItemTest();
    //LibItemRetriveTest();
    
    //PatronTest();
    //PatronRetrieveTest();

    //CommandsTest();

    executeProgram();

    //system("PAUSE");
    return 0;
}


