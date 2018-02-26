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
#include "AVLTree.h"
using namespace std;

bool displayWarning();
void initializeOutputFile();
string pickRandom(string filename, int random);
string pickAdjective();
string pickNoun();
string pickAnimal();
bool isCreatedString(string crazy_word);
void outputString(string crazy_word, int i);

int main1() {
	string crazy_word;
	string subject;
	srand(2342);
	int i = 0;

	if (!displayWarning()) {
		return 0;
	}
	initializeOutputFile();
	while (i < 10000) {
		if (rand() % 2 >= 1) {
			subject = pickNoun();
		}
		else {
			subject = pickAnimal();
		}
		crazy_word = pickAdjective() + " " + pickAdjective() + " " + subject;
		if (!isCreatedString(crazy_word)) {
			outputString(crazy_word, i);
			i++;
		}
	}

	system("pause");
	return 0;
}

//************************************************************************
// Function Name:	displayWarning
// Parameter:		none
// Returns:			bool
// Called by:		main
// Description:
// 		Prevents running the program by accident, as it takes time.
//************************************************************************
bool displayWarning() {
	char z;
	cout << "This program will generate 10000 crazy words." << endl;
	cout << "It may take about 10 hours, depending on your machine." << endl;
	cout << "Are you sure you want to run this program? [Y/N]" << endl;
	cin >> z;
	if (z == 'Y' || z == 'y') {
		return true;
	}
	else {
		return false;
	}
}

//************************************************************************
// Function Name:	initializeOutputFile
// Parameter:		none
// Returns:			none
// Called by:		main
// Description:
// 		Opens output file and clear all data.
//************************************************************************
void initializeOutputFile() {
	string filename = "tenthousandwords.txt";
	ofstream file(filename, ios_base::trunc);
	if (file.is_open())
	{ 
		file.close();
	}
	else { cout << "Unable to open file." << endl; }
}

//************************************************************************
// Function Name:	pickRandom
// Parameter:		string, int
// Returns:			string
// Called by:		pickAdjective, pickNoun, pickAnimal
// Description:
// 		Opens input file, traverse up to the line with given random number
// 		then read that line as a random pick of a word.
//************************************************************************
string pickRandom(string filename, int random) {
	filename = "word_files\\" + filename;
	string line;
	ifstream file(filename);
	int i = 0;

	if (file.is_open()) {
		while (getline(file, line)) {
			i++;
			if (random == i) {
				return line;
			}
		}
		file.close();
	}
	else { cout << "Unable to open file." << endl; }

	return "";
}

//************************************************************************
// Function Name:	pickAdjective
// Parameter:		none
// Returns:			string
// Called by:		main
// Description:
// 		Picks random adjective.
//************************************************************************
string pickAdjective() {
	string filename = "adjectives.txt";
	int number_of_lines = 15571;
	int random = rand() % number_of_lines;

	return pickRandom(filename, random);
}

//************************************************************************
// Function Name:	pickNoun
// Parameter:		none
// Returns:			string
// Called by:		main
// Description:
// 		Picks random noun.
//************************************************************************
string pickNoun() {
	string filename = "nouns.txt";
	int number_of_lines = 53737;
	int random = rand() % number_of_lines;

	return pickRandom(filename, random);
}

//************************************************************************
// Function Name:	pickAnimal
// Parameter:		none
// Returns:			string
// Called by:		main
// Description:
// 		Picks random animal.
//************************************************************************
string pickAnimal() {
	string filename = "animals.txt";
	int number_of_lines = 235;
	int random = rand() % number_of_lines;

	return pickRandom(filename, random);
}

//************************************************************************
// Function Name:	isCreatedString
// Parameter:		string
// Returns:			bool
// Called by:		main
// Description:
// 		Tells whether the crazy word has already been created or not.
//************************************************************************
bool isCreatedString(string crazy_word) {
	string filename = "tenthousandwords.txt";
	string line;
	ifstream file(filename);

	if (file.is_open()) {
		while (getline(file, line)) {
			if (line == crazy_word) {
				return true;
			}
		}
		file.close();
	}
	else { cout << "Unable to open file." << endl; }
	return false;
}

//************************************************************************
// Function Name:	outputString
// Parameter:		string, int
// Returns:			none
// Called by:		main
// Description:
// 		Opens output file by append and write the crazy word out.
//************************************************************************
void outputString(string crazy_word, int i) {
	string filename = "tenthousandwords.txt";
	ofstream file(filename, ios_base::app);

	if (file.is_open()) {
		cout << i << ": " << crazy_word + "\n";
		file << crazy_word + "\n";
		file.close();
	}
	else { cout << "Unable to open file." << endl; }
}
