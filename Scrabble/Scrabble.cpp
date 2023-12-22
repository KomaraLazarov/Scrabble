#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

const char FILE_NAME[] = "WordsDictionary.txt";
const unsigned WORD_MAX_LENGTH = 100;
const unsigned ENGLISH_LETTERS_COUNT = 26;

void printGeneratedLetters(const char* letters, unsigned lettersCount)
{
	for (size_t i = 0; i < lettersCount; i++)
	{
		cout << letters[i] << " ";
	}
	cout << endl;
}

void generateRandomLetters(char* letters, unsigned lettersCount)
{
	for (size_t i = 0; i < lettersCount; i++)
	{
		int number = rand() % ENGLISH_LETTERS_COUNT;
		letters[i] = number + 'a';
	}
	letters[lettersCount] = '\0';

	printGeneratedLetters(letters, lettersCount);
}

int readFile(const char filename[], char**& words, unsigned& wordsCount)
{
	ifstream myFile(filename);

	if (!myFile.is_open())
	{
		return 1;
	}

	myFile >> wordsCount;

	words = new char*[wordsCount];
	for (size_t i = 0; i < wordsCount; i++)
	{
		unsigned lenOfWord;
		myFile >> lenOfWord;
		words[i] = new char[lenOfWord + 1];
		myFile >> words[i];
	}

	myFile.close();
	return 0;
}

int main()
{
	srand(time(NULL));
	char** words = nullptr;
	unsigned wordsCount = 0;

	char* arr = new char[11];
	generateRandomLetters(arr, 10);

	readFile(FILE_NAME, words, wordsCount);
}
