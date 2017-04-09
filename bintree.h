/*
Rizky Ramdhani
CSS502
Assignment 4
bintree.h - Header file for BinTree class from Assignment 2.
Header file has been modified to work with Assignment 4 implementation.
*/

#pragma once
#include "nodedata.h"
#include <iostream>
#include <vector>

/*
//---------------------------------------------------------------------------
							BinTree
ADT of a Binary Search Tree that uses Nodes to store NodeData objects
BinTree has average case O(long n) retrieval, removal, and insertion.
BinTree is not a self-balancing tree, so worst case is O(n).

Features:
-Determine whether BinTree is empty
-Equality comparisons between BinTrees
-Insert NodeData into BinTree
-Remove NodeData from BinTree
-Retrieve NodeData from BinTree
-Display tree structure in a sideways fashion
-Get minimum and maximum NodeData objects from the BinTree
-Get height of a given NodeData in the BinTree
-Move contents of BinTree into a sorted NodeData* array
-Move contents from a sorted NodeData* array into BinTree

Implementation:
-Tree is implemented using pointers contained in the private Node struct
-Node contains a pointer to left and child Node, and a pointer to a NodeData
 object.
-NodeData handles output to console as well as comparisons between NodeData
 objects.
-The left subtree will always contain NodeData values smaller than the root,
 and the right subtree contains NodeData values larger than the NodeData 
 at the root.
-BinTree is not responsible for deallocating dynamic memory contained in
 NodeData.
//---------------------------------------------------------------------------
*/

class BinTree {

	//outputs contents of tree using inorder traversal
	friend ostream & operator<<(ostream &out, const BinTree &tree);

//---------------------------------------------------------------------------
public:
	
	BinTree(); // constructor
	BinTree(const BinTree &other); // copy constructor
	virtual ~BinTree(); // destructor, calls makeEmpty()
	bool isEmpty() const; // true if tree is empty, otherwise false

	// deallocate all memory to make the tree empty, so isEmpty returns true
	virtual void makeEmpty();
	BinTree& operator=(const BinTree &other);  //assignment operator

	//equality operator, calls equals()
	bool operator==(const BinTree &other) const;  
	bool operator!=(const BinTree &other) const; //inequality operator

	//inserts NodeData into BinTree if not a duplicate value.
	bool insert(NodeData *data);

	//Removes NodeData from BinTree and returns the NodeData by reference
	//It is the responsibility of the client to delete the NodeData
	bool remove(const NodeData &data, NodeData *&retrieve);

	//Determines whether NodeData is in the tree, returns the found
	//NodeData by reference.
	bool retrieve(const NodeData &data, NodeData *&retrieve) const;

	//Determines whether BinTree passed in argument is equal to this
	//BinTree
	bool equals(const BinTree &other) const;
	void displaySideways() const; // provided, displays the tree sideways
	NodeData * getMinimum() const;  //returns minimum NodeData in BinTree
	NodeData * getMaximum() const;  //returns maximum NodeData in BinTree

	//returns the height of the given NodeData in the tree.
	//returns 0 if NodeData is not found.
	int getHeight(const NodeData &data) const; 

	//Moves the contents of BinTree into a sorted NodeData* array.
	void bstreeToArray(NodeData* array[]);

	//Moves the contents from a sorted NodeData* array into BinTree
	void arrayToBSTree(NodeData* array[]);

    //Returns a vector of pointers to Objects stored in BinTree in sorted
    //order.
    vector<Object *> toSortedVector() const;

//---------------------------------------------------------------------------
private:
	struct Node {
		NodeData* data; // pointer to data object
		Node* left; // left subtree pointer
		Node* right; // right subtree pointer
	};
	Node* root; // root of the tree
	
	//helper function for output operator
	void inorderHelper(ostream &out, Node *root) const;
	void sideways(Node*, int) const;  //helper for displaySideways()
	void makeEmptyHelper(Node *&root);  //Helper function for makeEmpty()

	//Helper function to copy the contents of a BinTree to this BinTree
	void copyHelper(Node *&root, const Node *other); 

	//Helper function for equals()
	bool equalsHelper(Node *root, Node *other) const;  
	bool insertHelper(Node *&root, Node *&node); //Helper function insert()

	//Helper function for remove()
	bool removeHelper(const NodeData &data, NodeData *&retrieve, Node *&root);

	//Helper function for retrieve()
	bool retrieveHelper(const NodeData &data, NodeData *&retrieve, 
		Node *root) const;

	//Helper function for getMinimum()
	NodeData * getMinimumHelper(Node *root) const;

	//Helper function for getMaximum()
	NodeData * getMaximumHelper(Node *root) const;	

	//Returns Node* that contains NodeData passed in argument, 
	//nullptr otherwise
	Node * findNode(const NodeData &data, Node *root) const;

	//Returns the height of a given Node, returns 0 if Node is nullptr
	int getHeightOfNode(Node *root) const;

	//Helper function for bstreeToArray()
	void bstreeToArrayHelper(NodeData* array[], int &index, Node *&root);
	
	//Helper function for arrayToBSTree()
	void arrayToBSTreeHelper(NodeData * array[], int first, int last, 
		Node *&root);

    //Helper function for toSortedVector()
    void toSortedVectorHelper(vector<Object *> &vector, Node *root) const;
};

