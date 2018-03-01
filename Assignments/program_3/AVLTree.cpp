//****************************************************************************
// Title: Crazy Word Creator
// Files: AVLTree.cpp, AVLTree.h, BSTree.cpp, BSTree.h,
//		  generate_words.cpp, tenthousandwords.txt, analyze_trees.cpp,
//		  adjectives.txt, adverbs.txt, animals.txt, nouns.txt, verbs.txt
// Semester: Spring 2018
// Author: Yujin Yoshimura
// Email: yujinyoshimura@gmail.com
// Description: This program allows to do following. 
//			  Part 1:
//			  - creates 10000 crazy words without duplicates
//			  - each crazy words consist of 3 word parts
//			  - each crazy words consist of adjectives, nouns, animals
//			  - created words are stored in a file
//			  Part 2:
//			  - compare the performance of AVL Tree and Binary Search Tree
//			  - adjectives, adverbs, animals, nouns, verbs are inserted
//			  - then, read the word parts from the list of 10000 crazy words
//			  - search for each word parts in both trees
//			  - then count the number of comparisons made
//			  - at the same time, identify the type of the word part
//			  - finally displays the summary
//****************************************************************************

#include <iostream>
#include <fstream>
#include <time.h>
#include "AVLTree.h"

//https://visualgo.net/en/bst

using namespace std;

//************************************************************************
// Method Name:	AVLTree
// Parameter:	none
// Returns:		none
// Called by:	upon creation of an object
// Description:
// 		Constructor
//************************************************************************
AVLTree::AVLTree() {
	root = NULL;
}

//************************************************************************
// Method Name:	~AVLTree
// Parameter:	none
// Returns:		none
// Called by:	upon destruction of an object
// Description:
// 		Destructor
//************************************************************************
AVLTree::~AVLTree() {

}

//************************************************************************
// Method Name:	insert
// Parameter:	string to be placed in binary tree
// Returns:		none
// Called by:	public
// Description:
//		Creates a new node and assigns the passed in value to it.
//		Subsequently calls insert to actually travers the binary tree
//		and link the node inproper location. 
//		This method is overloaded to distinguish with the private method.
//************************************************************************
void AVLTree::insert(string word, string type) {
	node *newNode;
	
	if (search(word) == 0) {
		newNode = new node(word, type);
		insert(root, newNode);
		computeAvlValues(root);
	}
}

//************************************************************************
// Method Name:	search
// Parameter:	string to look for
// Returns:		int
// Called by:	public, insert
// Description:
//		Traverses a binary tree looking for a node with a key value,
//		then returns the number of comparisons made.
//		if a node is not found in the tree, returns 0.
//************************************************************************
int AVLTree::search(string word) {
	node *nodePtr = root;
	int comparison = 0;

	while (nodePtr) {
		comparison++;
		if (nodePtr->value == word)
			return comparison;
		else if (word < nodePtr->value)
			nodePtr = nodePtr->left;
		else
			nodePtr = nodePtr->right;
	}
	return 0;
}

//************************************************************************
// Method Name:	showPreorder
// Parameter:	none
// Returns:		none
// Called by:	public
// Description:
// 		Traverses a binary tree by preorder.
//************************************************************************
void AVLTree::showPreorder() {
	preorder(root);
}

//************************************************************************
// Method Name:	showInorder
// Parameter:	none
// Returns:		none
// Called by:	public
// Description:
// 		Traverses a binary tree by inorder.
//************************************************************************
void AVLTree::showInorder() {
	inorder(root);
}

//************************************************************************
// Method Name:	showPostorder
// Parameter:	none
// Returns:		none
// Called by:	public
// Description:
// 		Traverses a binary tree by postorder.
//************************************************************************
void AVLTree::showPostorder() {
	postorder(root);
}

//************************************************************************
// Method Name:	remove
// Parameter:	string of node to be deleted
// Returns:		none
// Called by:	public
// Description:
// 		Actually removes a node from a tree by pointer manipulation and
// 		frees the memory.
//		This method is overloaded to distinguish with the private method.
//************************************************************************
void AVLTree::remove(string word) { 
	root = remove(root, word);
}

//************************************************************************
// Method Name:	treeHeight
// Parameter:	none
// Returns:		int
// Called by:	public
// Description:
// 		returns the height of the tree.
//************************************************************************
int AVLTree::treeHeight() {
	return height(root);
}

//************************************************************************
// Method Name:	doDumpTree
// Parameter:	address of a node
// Returns:		none
// Called by:	public, doDumpTree(recursion), dumpTree
// Description:
// 		Private method to show the basic pointer structure of the tree. 
// 		Initially written to help with debugging.
//************************************************************************
void AVLTree::doDumpTree(node *nodePtr)
{
	if (nodePtr) {
		cout << "Add:    " << nodePtr << "\n"
			<< "Parent->" << nodePtr->parent << "\n"
			<< "Val:    " << nodePtr->value << "\n"
			<< "Avl:    " << nodePtr->avlValue << "\n"
			<< "Left->  " << nodePtr->left << "\n"
			<< "Right-> " << nodePtr->right << "\n\n";

		doDumpTree(nodePtr->left);
		doDumpTree(nodePtr->right);
	}
}

//************************************************************************
// Method Name:	dumpTree
// Parameter:	none
// Returns:		none
// Called by:	public
// Description:
// 		Public method to show the basic pointer structure of the tree. 
// 		Initially written to help with debugging.
//************************************************************************
void AVLTree::dumpTree() {
	cout << "---------------------------------" << endl;
	cout << "Root:   " << root << "\n";
	doDumpTree(root);
};

//************************************************************************
// Method Name:	graphVizGetIds
// Parameter:	address of a node, ofstream
// Returns:		void
// Called by:	public, graphVizGetIds(recursion), graphVizOut
// Description:
// 		Method to help create GraphViz code so the expression tree can 
// 		be visualized. This method prints out all the unique node id's
// 		by traversing the tree.
// 		Recivies a node pointer to root and performs a simple recursive 
// 		tree traversal.
//************************************************************************
void AVLTree::graphVizGetIds(node *nodePtr, ofstream &VizOut) {
	static int NullCount = 0;
	if (nodePtr) {
		graphVizGetIds(nodePtr->left, VizOut);
		VizOut << "node" << nodePtr->value
			<< "[label=\"" << nodePtr->value << "\\n"
			<< "Avl:" << nodePtr->avlValue << "\\n"
			//<<"Add:"<<nodePtr<<"\\n"
			//<<"Par:"<<nodePtr->parent<<"\\n"
			//<<"Rt:"<<nodePtr->right<<"\\n"
			//<<"Lt:"<<nodePtr->left<<"\\n"
			<< "\"]" << endl;
		if (!nodePtr->left) {
			NullCount++;
			VizOut << "nnode" << NullCount << "[label=\"X\",shape=point,width=.15]" << endl;
		}
		graphVizGetIds(nodePtr->right, VizOut);
		if (!nodePtr->right) {
			NullCount++;
			VizOut << "nnode" << NullCount << "[label=\"X\",shape=point,width=.15]" << endl;
		}
	}
}

//************************************************************************
// Method Name:	graphVizMakeConnections
// Parameter:	address of a node, ofstream
// Returns:		void
// Called by:	public, graphVizMakeConnections(recursion), graphVizOut
// Description:
// 		This method is partnered with the above method, but on this pass it 
// 		writes out the actual data from each node.
// 		Don't worry about what this method and the above method do, just
// 		use the output as your told:)
//************************************************************************
void AVLTree::graphVizMakeConnections(node *nodePtr, ofstream &VizOut) {
	static int NullCount = 0;
	if (nodePtr) {
		graphVizMakeConnections(nodePtr->left, VizOut);
		if (nodePtr->left)
			VizOut << "node" << nodePtr->value << "->" << "node" << nodePtr->left->value << endl;
		else {
			NullCount++;
			VizOut << "node" << nodePtr->value << "->" << "nnode" << NullCount << endl;
		}

		if (nodePtr->right)
			VizOut << "node" << nodePtr->value << "->" << "node" << nodePtr->right->value << endl;
		else {
			NullCount++;
			VizOut << "node" << nodePtr->value << "->" << "nnode" << NullCount << endl;
		}

		graphVizMakeConnections(nodePtr->right, VizOut);
	}
}

//************************************************************************
// Method Name:	graphVizOut
// Parameter:	string
// Returns:		void
// Called by:	public
// Description:
// 		Recieves a filename to place the GraphViz data into.
// 		It then calls the above two graphviz methods to create a data file
// 		that can be used to visualize your expression tree.
//************************************************************************
void AVLTree::graphVizOut(string filename)
{
	ofstream VizOut;
	VizOut.open(filename);
	graphVizGetIds(root, VizOut);
	graphVizMakeConnections(root, VizOut);
	VizOut.close();

}

//************************************************************************
// Method Name:	leftHeavy
// Parameter:	address of a node
// Returns:		true if heavy
// Called by:	rotateLeft
// Description:
// 		Compares the subtrees of a node to see which is taller.
//************************************************************************
bool AVLTree::leftHeavy(node *nodePtr)
{
	return height(nodePtr->left)>height(nodePtr->right);
}

//************************************************************************
// Method Name:	rightHeavy
// Parameter:	address of a node
// Returns:		true if heavy
// Called by:	rotateRight
// Description:
// 		Compares the subtrees of a node to see which is taller.
//************************************************************************
bool AVLTree::rightHeavy(node *nodePtr)
{
	return height(nodePtr->right)>height(nodePtr->left);

}

//************************************************************************
// Method Name:	insert
// Parameter:	reference to the root, and a reference to the new node
// Returns:		none
// Called by:	insert(recursion), insert(public)
// Description:
// 		Inserts a node into a binary tree.
//		This method is overloaded to distinguish with the public method.
//************************************************************************
void AVLTree::insert(node *&nodePtr, node *&newNode) {

	if (nodePtr == NULL) {
		nodePtr = newNode;
	}
	else if (newNode->value <= nodePtr->value) {
		newNode->parent = nodePtr;
		insert(nodePtr->left, newNode);

	}
	else {
		newNode->parent = nodePtr;
		insert(nodePtr->right, newNode);
	}

}

//************************************************************************
// Method Name:	preorder
// Parameter:	reference to the node
// Returns:		none
// Called by:	preorder(recursion), showPreorder
// Description:
// 		Traverses a binary tree by preorder.
//************************************************************************
void AVLTree::preorder(node *nodePtr) {
	if (nodePtr) {
		cout << nodePtr->value << " " << "(" << nodePtr->avlValue << ") ";
		preorder(nodePtr->left);
		preorder(nodePtr->right);
	}
}

//************************************************************************
// Method Name:	inorder
// Parameter:	reference to the node
// Returns:		none
// Called by:	inorder(recursion), showInorder
// Description:
// 		Traverses a binary tree by inorder.
//************************************************************************
void AVLTree::inorder(node *nodePtr) {
	if (nodePtr) {
		inorder(nodePtr->left);
		cout << nodePtr->value << " " << "(" << nodePtr->avlValue << ") ";
		inorder(nodePtr->right);
	}
}

//************************************************************************
// Method Name:	postorder
// Parameter:	reference to the node
// Returns:		none
// Called by:	postorder(recursion), showPostorder
// Description:
// 		Traverses a binary tree by postorder.
//************************************************************************
void AVLTree::postorder(node *nodePtr) {
	if (nodePtr) {
		postorder(nodePtr->left);
		postorder(nodePtr->right);
		cout << nodePtr->value << " " << "(" << nodePtr->avlValue << ") ";
	}
}

//************************************************************************
// Method Name:	remove
// Parameter:	address of node to be deleted
// Returns:		reference to the node
// Called by:	remove(recursion), remove(public)
// Description:
// 		Actually removes a node from a tree by pointer manipulation and
// 		frees the memory.
//		This method is overloaded to distinguish with the public method.
//************************************************************************
node* AVLTree::remove(node*& root, string key)
{
	if (!root)
	{
		return NULL;
	}
	if (key < root->value)
	{
		cout << "going left" << endl;
		root->left = remove(root->left, key);
	}
	else if (key > root->value)
	{
		cout << "going right" << endl;
		root->right = remove(root->right, key);
	}
	else
	{
		if (root->left == NULL)
		{
			node *temp = root->right;
			delete root;
			return temp;
		}
		else if (root->right == NULL)
		{
			node *temp = root->left;
			delete root;
			return temp;
		}

		// node with two children: Get the inorder successor (smallest
		// in the right subtree)
		node *temp = predSuccessor(root);

		printNode(temp, "predSuccessor");

		// Copy the inorder successor's content to this node
		root->value = temp->value;

		// Delete the inorder successor
		root->right = remove(root->right, temp->value);
	}
	return root;
}

//************************************************************************
// Method Name:	predSuccessor
// Parameter:	reference to root
// Returns:		reference to a node
// Called by:	remove(private)
// Description:
// 		Identifies the successor of a given node.
//************************************************************************
node* AVLTree::predSuccessor(node *root)
{
	node *current = root;

	if (root->right)
	{
		current = root->right;
		while (current->left != NULL)
		{
			current = current->left;
		}
	}
	else if (root->left)
	{
		current = root->left;
		while (current->right != NULL)
		{
			current = current->right;
		}
	}

	return current;
}

//************************************************************************
// Method Name:	printNode
// Parameter:	reference to a node, string to be labeled
// Returns:		none
// Called by:	remove(private)
// Description:
// 		Prints the node's value and its relative position in the tree.
//************************************************************************
void AVLTree::printNode(node *n, string label = "")
{
	if (label != "")
	{
		cout << "[" << label << "]";
	}
	cout << "[[" << n << "][" << n->value << "]]\n";
	if (n->left)
	{
		cout << "\t|-->[L][[" << n->left << "][" << n->left->value << "]]\n";
	}
	else
	{
		cout << "\t\\-->[L][null]\n";
	}
	if (n->right)
	{
		cout << "\t\\-->[R][[" << n->right << "][" << n->right->value << "]]\n";
	}
	else
	{
		cout << "\t\\-->[R][null]\n";
	}
}

//************************************************************************
// Method Name:	height
// Parameter:	address of the root of the tree
// Returns:		int
// Called by:	treeHeight, avlValue, leftHeavy, rightHeavy
// Description:
// 		returns the height of the tree.
//************************************************************************
int AVLTree::height(node *nodePtr) {
	int left_height = 0;
	int right_height = 0;
	if (nodePtr == NULL)
		return 0;
	else {
		left_height = height(nodePtr->left);
		right_height = height(nodePtr->right);
	}
	if (left_height>right_height)
		return 1 + left_height;
	else
		return 1 + right_height;
}

//************************************************************************
// Method Name:	avlValue
// Parameter:	address of a node
// Returns:		int
// Called by:	computeAvlValues
// Description:
// 		Private method to calculate the avl value of a node.
//************************************************************************
int AVLTree::avlValue(node *nodePtr)
{
	return height(nodePtr->right) - height(nodePtr->left);
}

//************************************************************************
// Method Name:	computeAvlValues
// Parameter:	address of a node
// Returns:		void
// Called by:	computeAvlValues(recursion), rotateLeft, rotateRight
// Description:
// 		Private method to calculate the avl values of the entire tree.
//************************************************************************
void AVLTree::computeAvlValues(node *&nodePtr)
{
	if (nodePtr) {
		computeAvlValues(nodePtr->left);
		computeAvlValues(nodePtr->right);
		nodePtr->avlValue = avlValue(nodePtr);
		if (nodePtr->avlValue > 1) {
			rotateLeft(nodePtr);
		}
		else if (nodePtr->avlValue < -1) {
			rotateRight(nodePtr);
		}
	}
}

//************************************************************************
// Method Name:	rotateLeft
// Parameter:	address of a node
// Returns:		void
// Called by:	computeAvlValues, rotateRight
// Description:
// 		Private method to perform a left rotation from a given position in a tree.
//************************************************************************
void AVLTree::rotateLeft(node *&SubRoot)
{
	if (leftHeavy(SubRoot->right)) {
		rotateRight(SubRoot->right);
	}

	node *Temp;

	Temp = SubRoot->right;
	SubRoot->right = Temp->left;
	Temp->left = SubRoot;
	SubRoot = Temp;

	computeAvlValues(SubRoot);
}

//************************************************************************
// Method Name:	rotateRight
// Parameter:	address of a node
// Returns:		void
// Called by:	computeAvlValues, rotateRight
// Description:
// 		Private method to perform a right rotation from a given position in a tree.
//************************************************************************
void AVLTree::rotateRight(node *&SubRoot)
{
	if (rightHeavy(SubRoot->left)) {
		rotateLeft(SubRoot->left);
	}

	node *Temp;

	Temp = SubRoot->left;
	SubRoot->left = Temp->right;
	Temp->right = SubRoot;
	SubRoot = Temp;

	computeAvlValues(SubRoot);
}
