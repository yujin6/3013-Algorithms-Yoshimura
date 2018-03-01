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
#include <vector>
using namespace std;

const int MAXWORDS = 10000;

bool displayWarning();
void initializeOutputFile();
void loadAll(vector<string> &adjectives, vector<string> &animals, vector<string> &nouns);
void load(vector<string> &v, string type);
int pickWordLength();
string pickRandom(vector<string> &v);
bool isAnimal();
bool isCreatedString(vector<string> v, string crazy_word);
void displayProgress(string crazy_word, int i);
void outputStrings(vector<string> v);

int main1() {
	vector<string> adjectives;
	vector<string> nouns;
	vector<string> animals;
	vector<string> crazy;
	string crazy_word;
	string subject;
	int length;
	int i = 0;

	srand(2342); // seeds random number

	if (!displayWarning()) {
		return 0;
	}
	initializeOutputFile();
	loadAll(adjectives, animals, nouns);

	while (i < MAXWORDS) {
		length = pickWordLength();
		while (length > 1) {
			crazy_word = crazy_word + pickRandom(adjectives) + " ";
			length--;
		}
		if (isAnimal()) {
			subject = pickRandom(nouns);
		}
		else {
			subject = pickRandom(animals);
		}
		crazy_word = crazy_word + subject;
		if (!isCreatedString(crazy, crazy_word)) {
			crazy.push_back(crazy_word);
			displayProgress(crazy_word, i);
			i++;
		}
		crazy_word = "";
	}

		outputStrings(crazy);

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
	cout << "It may take about 20 minutes, depending on your machine." << endl;
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
// Function Name:	loadAll
// Parameter:		reference to 3 vectors of string
// Returns:			none
// Called by:		main
// Description:
// 		Loads words from all input files into vectors of string.
//************************************************************************
void loadAll(vector<string> &adjectives, vector<string> &animals, vector<string> &nouns) {
	load(adjectives, "adjective");
	cout << endl << adjectives.size() << " adjectives are loaded." << endl;
	load(animals, "animal");
	cout << animals.size() << " animals are loaded." << endl;
	load(nouns, "noun");
	cout << endl << nouns.size() << " nouns are loaded." << endl;
}

//************************************************************************
// Function Name:	load
// Parameter:		reference to vector of string, string
// Returns:			none
// Called by:		loadAll
// Description:
// 		Loads words from one input file into vector of string.
//************************************************************************
void load(vector<string> &v, string type) {
	string filename = "word_files/" + type + "s.txt";
	string word;
	ifstream file(filename);
	int i = 0;

	if (file.is_open()) {
		while (file >> word) {
			v.push_back(word);
			i++;
			if (i % 1000 == 0) {
				cout << ".";
			}
		}
		file.close();
	}
	else { cout << "Unable to open file." << endl; }
}

//************************************************************************
// Function Name:	pickWordLength
// Parameter:		none
// Returns:			int between 3-5
// Called by:		main
// Description:
// 		Picks number of word parts randomly.
//************************************************************************
int pickWordLength() {
	return 3 + rand() % 3;
}

//************************************************************************
// Function Name:	pickRandom
// Parameter:		vector of string
// Returns:			string
// Called by:		main
// Description:
// 		Picks random word from a given vector of string.
//************************************************************************
string pickRandom(vector<string> &v) {
	int random = rand() % v.size();

	return v[random];
}

//************************************************************************
// Function Name:	isAnimal
// Parameter:		none
// Returns:			bool
// Called by:		main
// Description:
// 		Picks whether the last word part is either noun or animal.
// 		Returns true if animal is chosen. Returns false otherwise.
//************************************************************************
bool isAnimal() {
	if (rand() % 2 >= 1) {
		return true;
	}
	else {
		return false;
	}
}

//************************************************************************
// Function Name:	isCreatedString
// Parameter:		vector of string, string
// Returns:			bool
// Called by:		main
// Description:
// 		Tells whether the crazy word has already been created or not.
//************************************************************************
bool isCreatedString(vector<string> v, string crazy_word) {
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == crazy_word) {
			return true;
		}
	}
	return false;
}

//************************************************************************
// Function Name:	displayProgress
// Parameter:		string, int
// Returns:			none
// Called by:		main
// Description:
// 		Shows the crazy word generated with the index number.
//************************************************************************
void displayProgress(string crazy_word, int i) {
	cout << i << ": " << crazy_word + "\n";
}

//************************************************************************
// Function Name:	outputStrings
// Parameter:		vector of string
// Returns:			none
// Called by:		main
// Description:
// 		Opens output file and write the crazy word out.
//************************************************************************
void outputStrings(vector<string> v) {
	string filename = "tenthousandwords.txt";
	ofstream myfile(filename);

	if (myfile.is_open()) {
		for (int i = 0; i < v.size(); i++) {
			myfile << v[i] + "\n";
		}
		myfile.close();
	}
	else { cout << "Unable to open file." << endl; }
}
