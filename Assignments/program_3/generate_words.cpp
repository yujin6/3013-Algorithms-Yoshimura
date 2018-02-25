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

void exportString(string crazy_word, int i);

int main() {
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
			exportString(crazy_word, i);
			i++;
		}
	}

	system("pause");
	return 0;
}

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

void initializeOutputFile() {
	string filename = "tenthousandwords.txt";
	ofstream file(filename, ios_base::trunc);
	if (file.is_open())
	{ 
		file.close();
	}
	else { cout << "Unable to open file." << endl; }
}

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

string pickAdjective() {
	string filename = "adjectives.txt";
	int number_of_lines = 15571;
	int random = rand() % number_of_lines;

	return pickRandom(filename, random);
}

string pickNoun() {
	string filename = "nouns.txt";
	int number_of_lines = 53737;
	int random = rand() % number_of_lines;

	return pickRandom(filename, random);
}

string pickAnimal() {
	string filename = "animals.txt";
	int number_of_lines = 235;
	int random = rand() % number_of_lines;

	return pickRandom(filename, random);
}

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

void exportString(string crazy_word, int i) {
	string filename = "tenthousandwords.txt";
	ofstream file(filename, ios_base::app);

	if (file.is_open()) {
		cout << i << ": " << crazy_word + "\n";
		file << crazy_word + "\n";
		file.close();
	}
	else { cout << "Unable to open file." << endl; }
}
