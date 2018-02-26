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
#include <string>
#include <vector>
#include "AVLTree.h"
using namespace std;

class BSTree
{
public:
	BSTree();
	~BSTree();
	int count();
	void insert(string word, string type);
	int search(string word, string &type);
	void deleteNode(string key);
	void minValue();
	int height(int key = -1);
	string top();
	void printLevelOrder();
	void GraphVizOut(string filename);

private:
	node *root;
	int count(node *root);
	void insert(node *&root, node *&temp);
	void print_node(node *n, string label = "");
	node *minValueNode(node *root);
	node *deleteNode(node *&root, string key);
	int height(node *root);
	void printGivenLevel(node *root, int level);
	void GraphVizGetIds(node *nodePtr, ofstream &VizOut);
	void GraphVizMakeConnections(node *nodePtr, ofstream &VizOut);
};