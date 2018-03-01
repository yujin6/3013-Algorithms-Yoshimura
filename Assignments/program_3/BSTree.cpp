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

#include "BSTree.h"
using namespace std;

//************************************************************************
// Method Name:	BSTree
// Parameter:	none
// Returns:		none
// Called by:	upon creation of an object
// Description:
// 		Constructor
//************************************************************************
BSTree::BSTree()
{
	root = NULL;
}

//************************************************************************
// Method Name:	~BSTree
// Parameter:	none
// Returns:		none
// Called by:	upon destruction of an object
// Description:
// 		Destructor
//************************************************************************
BSTree::~BSTree()
{
}

//************************************************************************
// Method Name:	count
// Parameter:	none
// Returns:		int
// Called by:	public
// Description:
//		Counts the number of nodes.
//		This method is overloaded to distinguish with the private method.
//************************************************************************
int BSTree::count()
{
	return count(root);
}

//************************************************************************
// Method Name:	insert
// Parameter:	2 strings
// Returns:		none
// Called by:	public
// Description:
//		inserts a node.
//		This method is overloaded to distinguish with the private method.
//************************************************************************
void BSTree::insert(string word, string type)
{
	node *temp = new node(word, type);
	if (search(word, type) == 0) {
		insert(root, temp);
	}
}

//************************************************************************
// Method Name:	search
// Parameter:	string to be searched, string to be returned for type
// Returns:		int
// Called by:	public
// Description:
//		Traverses a binary tree looking for a node with a key value,
//		then returns the number of comparisons made.
//		if a node is not found in the tree, returns 0.
//************************************************************************
int BSTree::search(string word, string &type) {
	node *nodePtr = root;
	int comparison = 0;

	while (nodePtr) {
		comparison++;
		if (nodePtr->value == word) {
			type = nodePtr->type;
			return comparison;
		}
		else if (word < nodePtr->value)
			nodePtr = nodePtr->left;
		else
			nodePtr = nodePtr->right;
	}
	type = "";
	return 0;
}

//************************************************************************
// Method Name:	deleteNode
// Parameter:	string
// Returns:		none
// Called by:	public
// Description:
//		deletes a node with following rules:
//		- if a node has no child, simply deletes itself.
//		- if a node has only left child, it bypasses to the left child.
//		- if a ndoe has only right child, it bypasses to the right child.
//		- if a node has both children, look for its successor / predecessor
//		  then replace the node with its successor / predecessor.
//		This method is overloaded to distinguish with the private method.
//************************************************************************
void BSTree::deleteNode(string key)
{
	root = deleteNode(root, key);
}

//************************************************************************
// Method Name:	minValue
// Parameter:	none
// Returns:		none
// Called by:	public
// Description:
//		prints a successor of root.
//		if a successor does not exist, then prints a predecessor of root.
//		if neither successor and predecessor do not exist, prints root.
//************************************************************************
void BSTree::minValue()
{
	print_node(minValueNode(root), "minVal");
}

//************************************************************************
// Method Name:	height
// Parameter:	int
// Returns:		int
// Called by:	public
// Description:
// 		returns the height of the tree.
//		This method is overloaded to distinguish with the private method.
//************************************************************************
int BSTree::height(int key)
{
	if (key > 0)
	{
		//find node
	}
	else
	{
		return height(root);
	}
	return 0;
}

//************************************************************************
// Method Name:	top
// Parameter:	none
// Returns:		string
// Called by:	public
// Description:
// 		returns the value of the root.
//************************************************************************
string BSTree::top()
{
	if (root)
		return root->value;
	else
		return "";
}

//************************************************************************
// Method Name:	printLevelOrder
// Parameter:	none
// Returns:		none
// Called by:	public
// Description:
//		Function to line by line print level order traversal a tree.
//************************************************************************
void BSTree::printLevelOrder()
{
	cout << "Begin Level Order===================\n";
	int h = height(root);
	int i;
	for (i = 1; i <= h; i++)
	{
		printGivenLevel(root, i);
		cout << "\n";
	}
	cout << "End Level Order===================\n";
}

//************************************************************************
// Method Name:	GraphVizOut
// Parameter:	string
// Returns:		none
// Called by:	public
// Description:
//		Recieves a filename to place the GraphViz value into.
//		It then calls the above two graphviz methods to create a value file
//		that can be used to visualize your expression tree.
//************************************************************************
void BSTree::GraphVizOut(string filename)
{
	ofstream VizOut;
	VizOut.open(filename);
	VizOut << "Digraph G {\n";
	GraphVizGetIds(root, VizOut);
	GraphVizMakeConnections(root, VizOut);
	VizOut << "}\n";
	VizOut.close();
}

//************************************************************************
// Method Name:	count
// Parameter:	pointer to node
// Returns:		int
// Called by:	count(recursion), count(public)
// Description:
//		Counts the number of nodes.
//		This method is overloaded to distinguish with the public method.
//************************************************************************
int BSTree::count(node *root)
{
	if (!root)
	{
		return 0;
	}
	else
	{
		return 1 + count(root->left) + count(root->right);
	}
}

//************************************************************************
// Method Name:	insert
// Parameter:	2 pointers to nodes(pass by reference)
// Returns:		none
// Called by:	insert(recursion), insert(public)
// Description:
//		inserts a node.
//		This method is overloaded to distinguish with the public method.
//************************************************************************
void BSTree::insert(node *&root, node *&temp)
{
	if (!root)
	{
		root = temp;
	}
	else
	{
		if (temp->value < root->value)
		{
			insert(root->left, temp);
		}
		else
		{
			insert(root->right, temp);
		}
	}
}

//************************************************************************
// Method Name:	print_node
// Parameter:	pointer to node, string
// Returns:		none
// Called by:	deleteNode(private), printGivenLevel(private), minValue
// Description:
//		prints a node's value and its children.
//************************************************************************
void BSTree::print_node(node *n, string label)
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
// Method Name:	minValueNode
// Parameter:	pointer to node
// Returns:		pointer to node
// Called by:	deleteNode(private), minValue
// Description:
//		returns a successor of a given node.
//		if a successor does not exist, then returns a predecessor of a node.
//		if neither successor and predecessor do not exist, returns itself.
//************************************************************************
node* BSTree::minValueNode(node *root)
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
// Method Name:	deleteNode
// Parameter:	pointer to node(pass by reference), string
// Returns:		pointer to node
// Called by:	deleteNode(recursion), deleteNode(public)
// Description:
//		deletes a node with following rules:
//		- if a node has no child, simply deletes itself.
//		- if a node has only left child, it bypasses to the left child.
//		- if a ndoe has only right child, it bypasses to the right child.
//		- if a node has both children, look for its successor / predecessor
//		  then replace the node with its successor / predecessor.
//		This method is overloaded to distinguish with the public method.
//************************************************************************
node *BSTree::deleteNode(node *&root, string key)
{
	if (!root)
	{
		return NULL;
	}
	if (key < root->value)
	{
		cout << "going left" << endl;
		root->left = deleteNode(root->left, key);
	}
	else if (key > root->value)
	{
		cout << "going right" << endl;
		root->right = deleteNode(root->right, key);
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
		node *temp = minValueNode(root);

		print_node(temp, "minvaluenode");

		// Copy the inorder successor's content to this node
		root->value = temp->value;

		// Delete the inorder successor
		root->right = deleteNode(root->right, temp->value);
	}
	return root;
}

//************************************************************************
// Method Name:	height
// Parameter:	pointer to node
// Returns:		int
// Called by:	height(recursion), height(public), printLevelOrder
// Description:
// 		returns the height of the tree.
//		This method is overloaded to distinguish with the public method.
//************************************************************************
int BSTree::height(node *root)
{
	if (!root)
	{
		return 0;
	}
	else
	{
		int left = height(root->left);
		int right = height(root->right);
		if (left > right)
		{
			return left + 1;
		}
		else
		{
			return right + 1;
		}
	}
}

//************************************************************************
// Method Name:	printGivenLevel
// Parameter:	pointer to node, int
// Returns:		none
// Called by:	printGivenLevel(recursion), printLevelOrder
// Description:
// 		Print nodes at a given level.
//************************************************************************
void BSTree::printGivenLevel(node *root, int level)
{
	if (root == NULL)
		return;
	if (level == 1)
	{
		print_node(root);
	}
	else if (level > 1)
	{
		printGivenLevel(root->left, level - 1);
		printGivenLevel(root->right, level - 1);
	}
}

//************************************************************************
// Method Name:	GraphVizGetIds
// Parameter:	pointer to node, ofstream(pass by reference)
// Returns:		none
// Called by:	GraphVizGetIds(recursion), GraphVizOut
// Description:	
//		Method to help create GraphViz code so the expression tree can
//		be visualized. This method prints out all the unique node id's
//		by traversing the tree.
//		Recivies a node pointer to root and performs a simple recursive
//		tree traversal.
//************************************************************************
void BSTree::GraphVizGetIds(node *nodePtr, ofstream &VizOut)
{
	static int NullCount = 0;
	if (nodePtr)
	{
		GraphVizGetIds(nodePtr->left, VizOut);
		VizOut << "node" << nodePtr->value
			<< "[label=\"" << nodePtr->value << "\\n"
			//<<"Add:"<<nodePtr<<"\\n"
			//<<"Par:"<<nodePtr->parent<<"\\n"
			//<<"Rt:"<<nodePtr->right<<"\\n"
			//<<"Lt:"<<nodePtr->left<<"\\n"
			<< "\"]" << endl;
		if (!nodePtr->left)
		{
			NullCount++;
			VizOut << "nnode" << NullCount << "[label=\"X\",shape=point,width=.15]" << endl;
		}
		GraphVizGetIds(nodePtr->right, VizOut);
		if (!nodePtr->right)
		{
			NullCount++;
			VizOut << "nnode" << NullCount << "[label=\"X\",shape=point,width=.15]" << endl;
		}
	}
}

//************************************************************************
// Method Name:	GraphVizMakeConnections
// Parameter:	pointer to node, ofstream(pass by reference)
// Returns:		none
// Called by:	GraphVizMakeConnections(recursion), GraphVizOut
// Description:	
//		This method is partnered with the above method, but on this pass it
//		writes out the actual value from each node.
//		Don't worry about what this method and the above method do, just
//		use the output as your told:)
//************************************************************************
void BSTree::GraphVizMakeConnections(node *nodePtr, ofstream &VizOut)
{
	static int NullCount = 0;
	if (nodePtr)
	{
		GraphVizMakeConnections(nodePtr->left, VizOut);
		if (nodePtr->left)
			VizOut << "node" << nodePtr->value << "->"
			<< "node" << nodePtr->left->value << endl;
		else
		{
			NullCount++;
			VizOut << "node" << nodePtr->value << "->"
				<< "nnode" << NullCount << endl;
		}
		if (nodePtr->right)
			VizOut << "node" << nodePtr->value << "->"
			<< "node" << nodePtr->right->value << endl;
		else
		{
			NullCount++;
			VizOut << "node" << nodePtr->value << "->"
				<< "nnode" << NullCount << endl;
		}
		GraphVizMakeConnections(nodePtr->right, VizOut);
	}
}
