//****************************************************************************
// Title: Binary Search Tree
// Files: main.cpp, BSTree.cpp, BSTree.h
// Semester: Spring 2018
// Author: Yujin Yoshimura
// Email: yujinyoshimura@gmail.com
// Description: This program allows to do following for a binary search tree. 
//			  - create a binary search tree
//			  - count the number of nodes in the tree
//			  - insert a node into the tree
//			  - delete a node from the tree
//			  - find root's successor of the tree
//			  - get the height of the tree
//			  - get root's data of the tree
//			  - print the tree
//****************************************************************************

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct node
{
	int data;
	node *left;
	node *right;
	node()
	{
		data = -1;
		left = NULL;
		right = NULL;
	}
	node(int x)
	{
		data = x;
		left = NULL;
		right = NULL;
	}
};

class BSTree
{
private:
	node *root;

	//************************************************************************
	// Name: count
	// Parameter: pointer to node
	// Returns: int
	// Called by: count(recursion), count(public)
	// Description:
	//		Counts the number of nodes.
	//		This method is overloaded to distinguish with the public method.
	//************************************************************************
	int count(node *root);

	//************************************************************************
	// Name: insert
	// Parameter: 2 pointers to nodes(pass by reference)
	// Returns: none
	// Called by: insert(recursion), insert(public)
	// Description:
	//		inserts a node.
	//		This method is overloaded to distinguish with the public method.
	//************************************************************************
	void insert(node *&root, node *&temp);

	//************************************************************************
	// Name: print_node
	// Parameter: pointer to node, string
	// Returns: none
	// Called by: deleteNode(private), printGivenLevel(private), minValue
	// Description:
	//		prints a node's data and its children.
	//************************************************************************
	void print_node(node *n, string label = "");

	//************************************************************************
	// Name: minValueNode
	// Parameter: pointer to node
	// Returns: pointer to node
	// Called by: deleteNode(private), minValue
	// Description:
	//		returns a successor of a given node.
	//		if a successor does not exist, then returns a predecessor of a node.
	//		if neither successor and predecessor do not exist, returns itself.
	//************************************************************************
	node *minValueNode(node *root);

	//************************************************************************
	// Name: deleteNode
	// Parameter: pointer to node(pass by reference), int
	// Returns: pointer to node
	// Called by: deleteNode(recursion), deleteNode(public)
	// Description:
	//		deletes a node with following rules:
	//		- if a node has no child, simply deletes itself.
	//		- if a node has only left child, it bypasses to the left child.
	//		- if a ndoe has only right child, it bypasses to the right child.
	//		- if a node has both children, look for its successor / predecessor
	//		  then replace the node with its successor / predecessor.
	//		This method is overloaded to distinguish with the public method.
	//************************************************************************
	node *deleteNode(node *&root, int key);

	//************************************************************************
	// Name: height
	// Parameter: pointer to node
	// Returns: int
	// Called by: height(recursion), height(public), printLevelOrder
	// Description:
	// 		returns the height of the tree.
	//		This method is overloaded to distinguish with the public method.
	//************************************************************************
	int height(node *root);

	//************************************************************************
	// Name: printGivenLevel
	// Parameter: pointer to node, int
	// Returns: none
	// Called by: printGivenLevel(recursion), printLevelOrder
	// Description:
	// 		Print nodes at a given level.
	//************************************************************************
	void printGivenLevel(node *root, int level);

	//************************************************************************
	// Name: GraphVizGetIds
	// Parameter: pointer to node, ofstream(pass by reference)
	// Returns: none
	// Called by: GraphVizGetIds(recursion), GraphVizOut
	// Description:	
	//		Method to help create GraphViz code so the expression tree can
	//		be visualized. This method prints out all the unique node id's
	//		by traversing the tree.
	//		Recivies a node pointer to root and performs a simple recursive
	//		tree traversal.
	//************************************************************************
	void GraphVizGetIds(node *nodePtr, ofstream &VizOut);

	//************************************************************************
	// Name: GraphVizMakeConnections
	// Parameter: pointer to node, ofstream(pass by reference)
	// Returns: none
	// Called by: GraphVizMakeConnections(recursion), GraphVizOut
	// Description:	
	//		This method is partnered with the above method, but on this pass it
	//		writes out the actual data from each node.
	//		Don't worry about what this method and the above method do, just
	//		use the output as your told:)
	//************************************************************************
	void GraphVizMakeConnections(node *nodePtr, ofstream &VizOut);

public:

	//************************************************************************
	// Name: BSTree
	// Parameter: none
	// Returns: none
	// Called by: upon creation of an object
	// Description:
	// 		Constructor
	//************************************************************************
	BSTree();

	//************************************************************************
	// Name: ~BSTree
	// Parameter: none
	// Returns: none
	// Called by: upon destruction of an object
	// Description:
	// 		Destructor
	//************************************************************************
	~BSTree();

	//************************************************************************
	// Name: count
	// Parameter: none
	// Returns: int
	// Called by: public
	// Description:
	//		Counts the number of nodes.
	//		This method is overloaded to distinguish with the private method.
	//************************************************************************
	int count();

	//************************************************************************
	// Name: insert
	// Parameter: int
	// Returns: none
	// Called by: public
	// Description:
	//		inserts a node.
	//		This method is overloaded to distinguish with the private method.
	//************************************************************************
	void insert(int x);

	//************************************************************************
	// Name: deleteNode
	// Parameter: int
	// Returns: none
	// Called by: public
	// Description:
	//		deletes a node with following rules:
	//		- if a node has no child, simply deletes itself.
	//		- if a node has only left child, it bypasses to the left child.
	//		- if a ndoe has only right child, it bypasses to the right child.
	//		- if a node has both children, look for its successor / predecessor
	//		  then replace the node with its successor / predecessor.
	//		This method is overloaded to distinguish with the private method.
	//************************************************************************
	void deleteNode(int key);

	//************************************************************************
	// Name: minValue
	// Parameter: none
	// Returns: none
	// Called by: public
	// Description:
	//		prints a successor of root.
	//		if a successor does not exist, then prints a predecessor of root.
	//		if neither successor and predecessor do not exist, prints root.
	//************************************************************************
	void minValue();

	//************************************************************************
	// Name: height
	// Parameter: int
	// Returns: int
	// Called by: public
	// Description:
	// 		returns the height of the tree.
	//		This method is overloaded to distinguish with the private method.
	//************************************************************************
	int height(int key = -1);

	//************************************************************************
	// Name: top
	// Parameter: none
	// Returns: int
	// Called by: public
	// Description:
	// 		returns the data of the root.
	//************************************************************************
	int top();

	//************************************************************************
	// Name: printLevelOrder
	// Parameter: none
	// Returns: none
	// Called by: public
	// Description:
	//		Function to line by line print level order traversal a tree.
	//************************************************************************
	void printLevelOrder();

	//************************************************************************
	// Name: GraphVizOut
	// Parameter: string
	// Returns: none
	// Called by: public
	// Description:
	//		Recieves a filename to place the GraphViz data into.
	//		It then calls the above two graphviz methods to create a data file
	//		that can be used to visualize your expression tree.
	//************************************************************************
	void GraphVizOut(string filename);
};
