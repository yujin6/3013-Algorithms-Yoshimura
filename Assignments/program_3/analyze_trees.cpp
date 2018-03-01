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
#include <ctime>
using namespace std;

//bool displayWarningMessage();
//string setFilename();
bool checkArgument(int argc);
void loadAll(AVLTree &avl, BSTree &bs);
int load(AVLTree &avl, BSTree &bs, string type);
void outputString(string line, int count, ofstream &myfile);
void outputSummary(int avl, int bs, int adj, int adv, int animal, int noun, int verb);

int main(int argc, char **argv) {
	AVLTree avl;
	BSTree bs;
	string filename;
	string word, type;
	int avl_count = 0;
	int bs_count = 0;
	int adj_count = 0;
	int adv_count = 0;
	int animal_count = 0;
	int noun_count = 0;
	int verb_count = 0;
	
	//if (!displayWarningMessage()) {
	//	return 0;
	//}
	//filename = setFilename();

	if (!checkArgument(argc)) {
		exit(0);
	}
	filename = argv[1];

	loadAll(avl, bs);

	ifstream file(filename);

	if (file.is_open()) {
		while (file >> word) {
			avl_count += avl.search(word);
			bs_count += bs.search(word, type);
			if (type == "adjective")
				adj_count++;
			else if (type == "adverb")
				adv_count++;
			else if (type == "animal")
				animal_count++;
			else if (type == "noun")
				noun_count++;
			else if (type == "verb")
				verb_count++;
		}
		file.close();
	}
	else { cout << "Unable to open file." << endl; }

	outputSummary(avl_count, bs_count, adj_count, adv_count, animal_count, noun_count, verb_count);

	system("pause");
	return 0;
}

////************************************************************************
//// Function Name:	displayWarningMessage
//// Parameter:		none
//// Returns:			bool
//// Called by:		main
//// Description:
//// 		Prevents running the program by accident, as it takes time.
////************************************************************************
//bool displayWarningMessage() {
//	char z;
//	cout << "This program will analyze word parts of 10000 crazy words." << endl;
//	cout << "It may take about 1 hour, depending on your machine." << endl;
//	cout << "Are you sure you want to run this program? [Y/N]" << endl;
//	cin >> z;
//	if (z == 'Y' || z == 'y') {
//		return true;
//	}
//	else {
//		return false;
//	}
//}
//
////************************************************************************
//// Function Name:	setFilename
//// Parameter:		none
//// Returns:			string
//// Called by:		main
//// Description:
//// 		Allows user to choose an input file or use default input file.
////************************************************************************
//string setFilename() {
//	char z;
//	string filename;
//
//	cout << "Do you want to use a default input file for the 10000 crazy words? [Y/N]" << endl;
//	cin >> z;
//	if (z == 'Y' || z == 'y') {
//		filename = "tenthousandwords.txt";
//	}
//	else {
//		cout << "Please enter the filename." << endl;
//		cin >> filename;
//	}
//	return filename;
//}

//************************************************************************
// Function Name:	loadAll
// Parameter:		reference to AVLTree, reference to BSTree
// Returns:			none
// Called by:		main
// Description:
// 		Count command line args and make sure a file name is on the line
// 		to run this file.
//************************************************************************
bool checkArgument(int argc) {
	if (argc < 2) {
		cout << "You need an input file!\n";
		cout << "Usage: comparison filename.txt\n";
		system("pause");
		return false;
	}
	else {
		return true;
	}
}

//************************************************************************
// Function Name:	loadAll
// Parameter:		reference to AVLTree, reference to BSTree
// Returns:			none
// Called by:		main
// Description:
// 		Loads words from all input files into both AVL tree and BS tree.
//************************************************************************
void loadAll(AVLTree &avl, BSTree &bs) {
	cout << endl << load(avl, bs, "adjective") << " adjectives are loaded." << endl;
	cout << endl << load(avl, bs, "adverb") << " adverbs are loaded." << endl;
	cout << load(avl, bs, "animal") << " animals are loaded." << endl;
	cout << endl << load(avl, bs, "noun") << " nouns are loaded." << endl;
	cout << endl << load(avl, bs, "verb") << " verbs are loaded." << endl;
}

//************************************************************************
// Function Name:	load
// Parameter:		reference to AVLTree, reference to BSTree, string
// Returns:			int
// Called by:		loadAll
// Description:
// 		Loads words from one input file into both AVL tree and BS tree.
//************************************************************************
int load(AVLTree &avl, BSTree &bs, string type) {
	string filename = "word_files/" + type + "s.txt";
	string word;
	ifstream file(filename);
	int i = 0;

	if (file.is_open()) {
		while (file >> word) {
			avl.insert(word, type);
			bs.insert(word, type);
			i++;
			if (i % 1000 == 0) {
				cout << ".";
			}
		}
		file.close();
	}
	else { cout << "Unable to open file." << endl; }

	return i;
}

//************************************************************************
// Function Name:	outputString
// Parameter:		string, int, reference to ofstream
// Returns:			none
// Called by:		outputSummary
// Description:
// 		Opens output file and writes out summary.
// 		Displays the summary to the console at the same time.
//************************************************************************
void outputString(string line, int count, ofstream &myfile) {
	cout << line + to_string(count) + "\n";
	myfile << line + to_string(count) + "\n";
}

//************************************************************************
// Function Name:	outputSummary
// Parameter:		7 integers
// Returns:			none
// Called by:		main
// Description:
// 		Opens output file and writes out summary.
// 		Displays the summary to the console at the same time.
//************************************************************************
void outputSummary(int avl, int bs, int adj, int adv, int animal, int noun, int verb) {
	string filename = "analysis.out";
	ofstream myfile(filename);

	if (myfile.is_open()) {
		cout << endl << "Summary:" << endl;
		outputString("BST Comparisons = ", bs, myfile);
		outputString("AVL Comparisons = ", avl, myfile);
		outputString("Number of Adjectives = ", adj, myfile);
		outputString("Number of Adverbs = ", adv, myfile);
		outputString("Number of Animals = ", animal, myfile);
		outputString("Number of Nouns = ", noun, myfile);
		outputString("Number of Verbs = ", verb, myfile);
		myfile.close();
	}
	else { cout << "Unable to open file." << endl; }

}
