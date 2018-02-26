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

#pragma once
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>

using namespace std;

struct node {
	string value;
	string type;
	node *left;
	node *right;
	node *parent;
	int avlValue;
	node(string word, string wordtype) {
		value = word;
		type = wordtype;
		left = right = parent = NULL;
		avlValue = 0;
	}
};

class AVLTree {
public:
	AVLTree();
	~AVLTree();
	void insert(string, string);
	int search(string);
	void showPreorder();
	void showInorder();
	void showPostorder();
	void remove(string word);
	int  treeHeight();
	void doDumpTree(node *);
	void dumpTree();
	void graphVizGetIds(node *, ofstream &);
	void graphVizMakeConnections(node *, ofstream &);
	void graphVizOut(string);

private:
	node *root;
	bool rightHeavy(node *);
	bool leftHeavy(node *);
	void insert(node *&, node *&);
	void preorder(node *);
	void inorder(node *);
	void postorder(node *);
	node* remove(node*&, string);
	node* predSuccessor(node*);
	void printNode(node *, string);
	int  height(node *);
	int  avlValue(node *);
	void computeAvlValues(node *&);
	void rotateLeft(node *&);
	void rotateRight(node *&);
};