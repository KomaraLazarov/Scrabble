#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

const char FILE_NAME[] = "WordsDictionary.txt";
const unsigned WORD_MAX_LENGTH = 100;
const unsigned ENGLISH_LETTERS_COUNT = 26;

int compareWords(const char* firstWord, const char* secondWord)
{
	if (!firstWord || !secondWord)
	{
		return 0;
	}

	while ((*firstWord) && (*firstWord == *secondWord))
	{
		firstWord++;
		secondWord++;
	}

	return *firstWord - *secondWord;
}

unsigned calculatePointsForWord(char* word)
{
	if (!word)
	{
		return 0;
	}

	unsigned result = 0;
	while (*word)
	{
		result++;
		word++;
	}

	return result;
}

bool findWordInDictionary(const char* const* words, unsigned wordsCount, const char* enteredWord)
{
	unsigned left = 0;
	unsigned right = wordsCount - 1;

	while (left <= right)
	{
		unsigned mid = left + (right - left) / 2;
		int wordsDifference = compareWords(enteredWord, words[mid]);

		if (wordsDifference == 0)
		{
			return true;
		}

		if (wordsDifference < 0)
		{
			right = mid - 1;
		}
		else
		{
			left = mid + 1;
		}
	}

	return false;
}

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

int readWordsFromFile(const char filename[], char**& words, unsigned& wordsCount)
{
	ifstream myFile(filename);

	if (!myFile.is_open())
	{
		return 1;
	}

	myFile >> wordsCount;

	words = new char* [wordsCount];

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

unsigned getLength(const char* currentWord)
{
	if (!currentWord)
	{
		return 0;
	}

	unsigned result = 0;
	while (*currentWord)
	{
		result++;
		currentWord++;
	}

	return result;
}

int writeAWordInFile(const char filename[], const char* const* words, unsigned wordsCount)
{
	ofstream myFile(filename);

	myFile.clear();

	if (!myFile.is_open())
	{
		return 1;
	}

	myFile << wordsCount << endl;

	for (size_t i = 0; i < wordsCount; i++)
	{
		myFile << getLength(words[i]) << " ";
		myFile << words[i] << endl;
	}

	myFile.close();
	return 0;
}

int newAddedWordIndex(const char* const* words, unsigned wordsCount, const char* newWord)
{
	unsigned left = 0, mid = 0;
	unsigned right = wordsCount - 1;

	while (left <= right)
	{
		mid = left + (right - left) / 2;

		int wordsDifference = compareWords(newWord, words[mid]);

		if (wordsDifference == 0)
		{
			return -1;
		}

		if (wordsDifference < 0)
		{
			right = mid - 1;
		}
		else
		{
			left = mid + 1;
		}
	}

	return mid;
}

void addWord(char**& words, unsigned& wordsCount)
{
	char* newWord = new char[WORD_MAX_LENGTH];
	cin >> newWord;

	unsigned newWordIndex = newAddedWordIndex(words, wordsCount, newWord);

	if (newWordIndex != -1)
	{
		wordsCount++;
		char** updatedDictionary = new char* [wordsCount];
		for (size_t i = 0; i <= newWordIndex; i++)
		{
			updatedDictionary[i] = words[i];
		}
		updatedDictionary[newWordIndex + 1] = newWord;
		for (size_t j = newWordIndex + 2; j <= wordsCount; j++)
		{
			updatedDictionary[j] = words[j - 1];
		}

		words = updatedDictionary;
		cout << "Word added successfully!";
	}
	else
	{
		cout << "Word already exists!";
	}
}

int main()
{
	srand(time(NULL));
	char** words = nullptr;
	unsigned wordsCount = 0, score = 0;

	char* arr = new char[11];
	generateRandomLetters(arr, 10);

	readWordsFromFile(FILE_NAME, words, wordsCount);

	char* enteredWord = new char[WORD_MAX_LENGTH];
	cin >> enteredWord;

	if (findWordInDictionary(words, wordsCount, enteredWord))
	{
		score += calculatePointsForWord(enteredWord);
	}
	else
	{
		// TODO - repeate again
	}

	cout << score << endl;

	addWord(words, wordsCount);
	writeAWordInFile(FILE_NAME, words, wordsCount);
}
