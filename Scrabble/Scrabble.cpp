#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

const char FILE_NAME[] = "WordsDictionary.txt";
const unsigned WORD_MAX_LENGTH = 100;
const unsigned ENGLISH_LETTERS_COUNT = 26;
const unsigned EXIT_NUMBER = 4;

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

bool isWordMadeUpOfTheLetters(char* letters, const char* enteredWord) // TODO: IF THIS HELP ARRAY USEFULL
{
	if (!letters || !enteredWord)
	{
		return false;
	}

	unsigned lettersCount = getLength(letters);
	int* checkLetters = new int[lettersCount] {0};
	unsigned currentWordCount = getLength(enteredWord);
	unsigned count = 0;
	while (*enteredWord)
	{
		for (size_t i = 0; i < lettersCount; i++)
		{
			if (*enteredWord == letters[i] && !checkLetters[i])
			{
				checkLetters[i] = 1;
				count++;
				break;
			}
		}
		enteredWord++;
	}

	return count == currentWordCount;
}

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

void generateRandomLetters(char*& letters, unsigned lettersCount)
{
	for (size_t i = 0; i < lettersCount; i++)
	{
		int number = rand() % ENGLISH_LETTERS_COUNT;
		letters[i] = number + 'a';
	}
	letters[lettersCount] = '\0';
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

int writeWordInFile(const char filename[], const char* const* words, unsigned wordsCount)
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
		cout << "Word added successfully!" << endl;
	}
	else
	{
		cout << "Word already exists!" << endl;
	}
}

void changeGameSettings(unsigned& lettersCount, unsigned& gameRounds)
{
	char option = ' ';
	cin >> option;
	if (option == 'a')
	{
		unsigned updateCount = 0;
		cout << "Change count of letters: ";
		cin >> updateCount;
		lettersCount = updateCount;
	}
	else if (option == 'b')
	{
		unsigned updateRounds = 0;
		cout << "Change count of rounds: ";
		cin >> updateRounds;
		gameRounds = updateRounds;
	}
}
// TODO : CONST ** CHECK !!!
void startGame(char* letters, char** words, unsigned wordsCount, unsigned score, unsigned lettersCount, unsigned gameRounds)
{
	char* enteredWord = nullptr;
	for (size_t i = 1; i <= gameRounds; i++)
	{
		cout << "Round " << i << ". ";
		cout << "Available letters: ";
		generateRandomLetters(letters, lettersCount);
		printGeneratedLetters(letters, lettersCount);

		while (true)
		{
			enteredWord = new char[WORD_MAX_LENGTH];
			cin >> enteredWord;

			if (isWordMadeUpOfTheLetters(letters, enteredWord) && findWordInDictionary(words, wordsCount, enteredWord))
			{
				score += calculatePointsForWord(enteredWord);
				break;
			}

			cout << "Invalid word. Try again with: ";
			printGeneratedLetters(letters, lettersCount);
		}

		cout << "Your points so far are: " << score << endl;
	}
	cout << "Your total points are: " << score << endl;
}
void menuDesign()
{
	cout << " _____________________________________________" << endl;
	cout << "|                                             |" << endl;
	cout << "|                 Scrabble game               |" << endl;
	cout << "|_____________________________________________|" << endl;
	cout << "|                                             |" << endl;
	cout << "|                   MAIN MENU                 |" << endl;
	cout << "|                                             |" << endl;
	cout << "|  1. START NEW GAME                          |" << endl;
	cout << "|                                             |" << endl;
	cout << "|  2. SETTINGS:                               |" << endl;
	cout << "|   a. CHOOSE COUNT OF LETTERS (DEFAULT - 10) |" << endl;
	cout << "|   b. CHOOSE COUNT OF ROUNDS (DEFAULT - 10)  |" << endl;
	cout << "|                                             |" << endl;
	cout << "|  3. ENTER A NEW WORD                        |" << endl;
	cout << "|                                             |" << endl;
	cout << "|  4. EXIT                                    |" << endl;
	cout << "|_____________________________________________|" << endl;
}
void selectingMenuFunctionality(char* letters, char** words, unsigned wordsCount, unsigned score,
	unsigned lettersCount, unsigned gameRounds)
{
	unsigned numberOfFunctionality = 0;

	while (true)
	{
		cin >> numberOfFunctionality;
		if (numberOfFunctionality == EXIT_NUMBER)
		{
			break;
		}

		switch (numberOfFunctionality)
		{
		case 1:
			startGame(letters, words, wordsCount, score, lettersCount, gameRounds);
			break;
		case 2:
			changeGameSettings(lettersCount, gameRounds); // TODO: CHANGE THIS NAME MAYBE AND CHECK IF I WILL SEPARATE THIS FUNC
			break;
		case 3:
			addWord(words, wordsCount);
			writeWordInFile(FILE_NAME, words, wordsCount);
			break;

		default:
			break;
		}

		menuDesign();
	}
}

int main()
{
	menuDesign();

	srand(time(NULL));
	char** words = nullptr;
	unsigned wordsCount = 0, score = 0, lettersCount = 10, gameRounds = 10;
	char* letters = new char[lettersCount + 1];

	// TODO: Make the returning in the menu after ending
	// TODO: DELETE DYNAMIC ARRAYS

	readWordsFromFile(FILE_NAME, words, wordsCount); // TODO: IF THIS MUST BE HERE
	selectingMenuFunctionality(letters, words, wordsCount, score, lettersCount, gameRounds);
}
