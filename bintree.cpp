/*
Rizky Ramdhani
CSS502
Assignment 4
bintree.cpp - Implementation file for BinTree class from Assignment 2.
Implementation file has been modified to work with Assignment 4 
implementation.
*/

#include "bintree.h"

//---------------------------------------------------------------------------
//Default constructor
//Sets root to nullptr.
BinTree::BinTree()
{
	root = nullptr;
}

//---------------------------------------------------------------------------
//Copy constructor
//Instantiates BinTree object and deep copies the contents of other BinTree 
//to this BinTree using copyHelper()
BinTree::BinTree(const BinTree &other) : BinTree()
{
	//copy tree (deep copy)
	copyHelper(this->root, other.root);	
}

//---------------------------------------------------------------------------
//Assignment operator
//Deep copies the contents of other BinTree to this BinTree 
//using copyHelper()
BinTree & BinTree::operator=(const BinTree &other)
{
	//check to see if they're not the same address
	if (this != &other) {
		makeEmpty();  //empty the current tree

		copyHelper(this->root, other.root);  //copy the content of other
	}

	return *this;
}

//---------------------------------------------------------------------------
//copyHelper
//Recursive function to deep copy the contents of other Node to this Node
//Parameters:
//	root - Node* to copy to
//  other - Node* to copy from
void BinTree::copyHelper(Node *&root, const Node *other)
{
	//base cases
	if (other == nullptr) return;  //no Node to copy
								   
	//create copy of data
	NodeData *data = new NodeData(*other->data);

	//create new Node to insert
	Node *node = new Node();
	node->data = data;

	root = node;  //assign Node to root

	//traverse children
	copyHelper(root->left, other->left);
	copyHelper(root->right, other->right);
}

//---------------------------------------------------------------------------
//Destructor
//Calls makeEmpty()
BinTree::~BinTree()
{
	makeEmpty();
}

//---------------------------------------------------------------------------
//isEmpty
//Returns true if contents of this BinTree is empty, false otherwise
bool BinTree::isEmpty() const
{
	return root == nullptr;
}

//---------------------------------------------------------------------------
//makeEmmpty
//Deletes the contents of this BinTree, deallocating all dynamic memory and
//sets root to nullptr using makeEmptyHelper()
void BinTree::makeEmpty()
{
	makeEmptyHelper(root);
}

void BinTree::makeEmptyHelper(Node *&root)
{
	//base case: if root is null
	if (root == nullptr) return;

	//makeEmpty the children first
	makeEmptyHelper(root->left);
	makeEmptyHelper(root->right);

	//if root is a leaf, delete the Node
	if (root->left == nullptr && root->right == nullptr)
	{
		//delete data, then the Node
		delete root->data;
        root->data = nullptr;
		delete root;
		root = nullptr;
		return;
	}
}

//---------------------------------------------------------------------------
//Equality operator
//Returns true if structure and content of this BinTree equals other BinTree,
//false otherwise.
bool BinTree::operator==(const BinTree &other) const
{
	return equals(other);
}

//---------------------------------------------------------------------------
//Inequality operator
//Returns true if structure and content of thei BinTree does not equal
//other BinTree, false otherwise.
bool BinTree::operator!=(const BinTree &other) const
{
	return !(equals(other));
}

//---------------------------------------------------------------------------
//insert
//Inserts NodeData into BinTree using insertHelper() if it does not already 
//exist in BinTree
//Parameters:
//	data - NodeData* to be inserted into BinTree
//Return:
//	true - if insertion is successful
//  false - NodeData value already exists in BinTree
bool BinTree::insert(NodeData *data)
{
	//Create new Node to insert data
	Node *node = new Node();
	node->data = data;
    node->left = nullptr;
    node->right = nullptr;
	return insertHelper(root, node);
}

bool BinTree::insertHelper(Node *&root, Node *&node)
{
	//base cases
	if (root == nullptr)  //insert node at this root
	{
		root = node;
		return true;
	}

	if (*root->data == *node->data)  //duplicate data
	{
		return false;
	}
	
	//Traverse children
	//go to left child
	if (*node->data < *root->data) 
	{
		return insertHelper(root->left, node);
	}
	else //go to right child
	{
		return insertHelper(root->right, node);
	}
}

//---------------------------------------------------------------------------
//remove
//Removes Node containing data from BinTree using removeHelper(), 
//returns the NodeData found in BinTree by reference passed in the argument.  
//It is the responsibility of the client to delete the retrieved NodeData.
//Parameters:
//	data - NodeData to be removed from BinTree
//  retrieve - NodeData removed from BinTree.  Passed by reference.
bool BinTree::remove(const NodeData &data, NodeData *&retrieve)
{
	return removeHelper(data, retrieve, root);
}

bool BinTree::removeHelper(const NodeData &data, NodeData *&retrieve, 
	Node *&root)
{
	//base cases
	if (root == nullptr) return false;  //data not found

	//Data found
	if (*root->data == data)
	{
		retrieve = root->data; //set retrieve to NodeData found

		//Adjust tree to remove NodeData

		//if root is a leaf, just delete the node
		if (root->left == nullptr && root->right == nullptr)
		{
            delete root->data;
            root->data = nullptr;
			delete root;
			root = nullptr;
		}
		//if left child is null and right child is not null, 
		//replace Node with right child
		else if (root->left == nullptr && root->right != nullptr)
		{
			root = root->right;
		}
		//if left child is not null, and right child is null,
		//replace Node with left child
		else if (root->left != nullptr && root->right == nullptr)
		{
			root = root->left;
		}
		//neither children is null, replace data with maximum NodeData of
		//left child, then remove maximum Node.
		else
		{
			//find maximum NodeData from left subtree
			NodeData *replacement = getMaximumHelper(root->left);

			//recursively remove the maximum NodeData value 
			//from left subtree.
			removeHelper(*replacement, root->data, root->left);
		}

		return true;
	}

	//Current Node does not contain data, traverse children
	if (data < *root->data)  //traverse left child
	{
		return removeHelper(data, retrieve, root->left);
	}
	else  //traverse right child
	{
		return removeHelper(data, retrieve, root->right);
	}
}

//---------------------------------------------------------------------------
//retrieve
//Determines whether BinTree contains data and returns the NodeData in the
//BinTree by reference. Uses retrieveHelper()
//Parameters:
//	data - NodeData to find in BinTree
//	retrieve - NodeData found in BinTree; passed by reference.
//Return:
//	true if data is in Bintree, false otherwise
bool BinTree::retrieve(const NodeData &data, NodeData *&retrieve) const
{
	return retrieveHelper(data, retrieve, root);
}

bool BinTree::retrieveHelper(const NodeData &data, NodeData *&retrieve, Node *root) const
{
	//base case
	if (root == nullptr) return false;  //data not found

	if (*root->data == data)  //Node found
	{
		retrieve = root->data;  //set retrieve to the NodeData at Node
		return true;
	}

	//Traverse children
	if (data < *root->data) {  //traverse left child
		return retrieveHelper(data, retrieve, root->left);
	}
	else  //treverse right child
	{
		return retrieveHelper(data, retrieve, root->right);
	}
}

//---------------------------------------------------------------------------
//equals
//Determines whether this BinTreee has the same structure and contents as
//other BinTree using equalsHelper()
//Parameters:
//	other - BinTree to compare against.
//Return:
//  true - structure and contents of this BinTree is the same as other
//		   BinTree, false otherwise.
bool BinTree::equals(const BinTree &other) const
{
	if (this == &other) return true;  //if the same memory address
	return equalsHelper(root, other.root);
}

bool BinTree::equalsHelper(Node *root, Node *other) const
{
	//base cases
	if (root == nullptr && other == nullptr) return true; //both nullptr 
	if (root != nullptr && other == nullptr) return false; //one nullptr
	if (root == nullptr && other != nullptr) return false;  //one nullptr
	if (*root->data != *other->data) return false;  //data does not match
		
	 //Current Node data matches	
	//Check children
	bool leftCheck = equalsHelper(root->left, other->left);
	bool rightCheck = equalsHelper(root->right, other->right);

	return (leftCheck && rightCheck);
}

//---------------------------------------------------------------------------
// displaySideways 
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
void BinTree::displaySideways() const {
	sideways(root, 0);
}

void BinTree::sideways(Node* current, int level) const {
	if (current != nullptr) {
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--) {
			cout << "    ";
		}

		cout << *current->data << endl;        // display information of object
		sideways(current->left, level);
	}
}

//---------------------------------------------------------------------------
//getMinimum
//Returns the minimum NodeData* in the BinTree using getMinimumHelper()
NodeData * BinTree::getMinimum() const
{
	return getMinimumHelper(root);
}

NodeData * BinTree::getMinimumHelper(Node * root) const
{
	//base cases
	if (root == nullptr) return nullptr; //tree is empty

	//leftmost (minimum) Node found in tree.
	if (root->left == nullptr) return root->data;  

    //traverse left child
	return getMinimumHelper(root->left);
}

//---------------------------------------------------------------------------
//getMaximum
//Returns the maximum NodeData in the BinTree using getMaximumHelper()
NodeData * BinTree::getMaximum() const
{
	return getMaximumHelper(root);
}

NodeData * BinTree::getMaximumHelper(Node *root) const
{
	//base case
	if (root == nullptr) return nullptr;  //tree is empty

	//rightmost (maximum) Node found in tree.
	if (root->right == nullptr) return root->data;

	//traverse right child
	return getMaximumHelper(root->right);
}

//---------------------------------------------------------------------------
//getHeight
//Returns the height of Node containing data in BinTree.
//The height of a node is the the maximum length from a leaf to the node.
//Parameters:
//	data - query NodeData
//Return:
//  int - if BinTree contains Node whose NodeData equals data,
//		  return its height in BinTree.  Return a height of 1 if Node found 
//		  is at leaf, 0 if no Node is found in BinTree.
int BinTree::getHeight(const NodeData & data) const
{
	//find Node with data
	Node *found = findNode(data, root);
	if (found == nullptr)  //Node not found
		return 0;
	else
		return getHeightOfNode(found);
}

//---------------------------------------------------------------------------
//findNode
//Returns a pointer to a Node whose NodeData is equal to data.
//Traversal is done as if BinTree is a general binary tree and not a binary
//search tree.
//Parameters:
//	data - query NodeData
//	root - (Node) root of tree to be searched
//Returns:
//	pointer to a Node whose NodeData equals data, returns nullptr if no Node
//  is found.
BinTree::Node * BinTree::findNode(const NodeData &data, Node *root) const
{
	//base cases
	if (root == nullptr) return nullptr;  //Node not found

	if (*root->data == data) return root;  //Node found

	//Traverse Children
	Node *leftCheck = findNode(data, root->left);
	if (leftCheck != nullptr)  //Node found in left subtree
	{
		return leftCheck;
	}
	else  //Node not found in left subtree
	{
		//return the value of right subtree whether found or not
		return findNode(data, root->right);
	}	
}

//---------------------------------------------------------------------------
//getHeightOfNode
//return the height of a node.  Height is the maximum length from a leaf to
//the node.
//Parameter:
//	root - Node/tree whose height is to be determined
//Return:
//  int - The height of root in BinTree.  The height of a leaf is 1.
//		  The height of an empty tree is 0.
int BinTree::getHeightOfNode(Node *root) const
{
	//base cases
	if (root == nullptr) return 0;

	//find height of children
	int leftCheck = getHeightOfNode(root->left);
	int rightCheck = getHeightOfNode(root->right);

	//find larger height
	int larger = (leftCheck > rightCheck) ? leftCheck : rightCheck;

	return 1 + larger;
}

//---------------------------------------------------------------------------
//bstreeToArray
//Moves the contents of BinTree into NodeData* array using inorder traversal.
//Tree is left empty once the operation is complete.  
//Uses bstreeToArrayHelper().
//Parameters:
//	array - NodeData*[] to copy to.
//			array is assumed to be large enough to contain all the elements
//			in BinTree and all of its elements are initialized to nullptr.
void BinTree::bstreeToArray(NodeData* array[])
{
	int index = 0;  //current index of array for elements to be moved to.
	bstreeToArrayHelper(array, index, root);
}

void BinTree::bstreeToArrayHelper(NodeData* array[], int &index, 
	Node *&root)
{
	//base cases
	if (root == nullptr) return;

	//traverse left child
	bstreeToArrayHelper(array, index, root->left);

	//Do operations on current Node

	array[index] = root->data; //set array at current index to the NodeData
	index++;  //increment index
	root->data = nullptr;  //set data at Node to nullptr

	//traverse right child
	bstreeToArrayHelper(array, index, root->right);

	//delete current Node after children traversal.
    delete root->data;
    root->data = nullptr;
	delete root;
	root = nullptr;
}

//---------------------------------------------------------------------------
//arraytoBSTree
//Moves the contents of a sorted NodeData* array into BinTree, whose contents
//will be left with all nullptr.  Uses arrayToBSTreeHelper()
//Parameters:
//	array - NodeData*[] to copy from.  It is assumed that array will be in
//			sorted order, elements in array that do not contain NodeData*
//			are set to nullptr, and indexes containing NodeData*
//			are continuous starting from index 0 (no elements containing
//			nullptr between, elements that contain NodeData*).
void BinTree::arrayToBSTree(NodeData * array[])
{
	makeEmpty();  //empty BinTree

	//find last
	int last = 0;
	int arraySize = 100;
	//iterate through array to find the last index where element
	//in array is not nullptr
	while (last < arraySize && array[last] != nullptr)
	{
		last++;
	}

	//call helper function, use last - 1, which is the last element in
	//array which is not nullptr.
	arrayToBSTreeHelper(array, 0, last - 1, root);
}

void BinTree::arrayToBSTreeHelper(NodeData * array[], int first, int last, 
	Node *& root)
{
	//base case
	if (first > last) return;

	//get value to insert
	int median = (first + last) / 2;  //get median value

	//assign root a new Node value containing NodeData at array[median]
	root = new Node();
	root->data = array[median];

	//set value at array[median] to nullptr
	array[median] = nullptr;

	//recursive calls
	arrayToBSTreeHelper(array, first, median - 1, root->left);
	arrayToBSTreeHelper(array, median + 1, last, root->right);
}

//---------------------------------------------------------------------------
//toSortedVector
//Returns a sorted vector of pointers to Object elements in BinTree.
//Uses toSortedVectorHelper()
//Return:
//  vector of Object *
vector<Object *> BinTree::toSortedVector() const
{
    vector<Object *> result;

    toSortedVectorHelper(result, root);

    return result;
}

void BinTree::toSortedVectorHelper(vector<Object*>& vector, Node *root) const
{
    if (root == nullptr) return;  //base case

    //inorder traversal

    toSortedVectorHelper(vector, root->left);

    vector.push_back(root->data->getData());

    toSortedVectorHelper(vector, root->right);
}

//---------------------------------------------------------------------------
//output operator
//Displays the contents of BinTree using inorder traversal
//using inorderHelper()
//i.e. 1 2 3 4 5 6
ostream & operator<<(ostream & out, const BinTree &tree)
{
	tree.inorderHelper(out, tree.root);
	out << endl;
	return out;
}

void BinTree::inorderHelper(ostream &out, Node *root) const
{
	//base cases
	if (root == nullptr) return;

	//traverse left child
	inorderHelper(out, root->left);

	//output
	out << *root->data << " ";

	//traverse right child
	inorderHelper(out, root->right);
}


