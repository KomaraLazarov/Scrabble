/**
*
* Solution to course project # <7>
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @author <Nikola Lazarov>
* @idnumber <5MI0600332>
* @compiler <GCC>
*
* <Scrabble game>
*
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

const char FILE_NAME[] = "WordsDictionary.txt";
const unsigned WORD_MAX_LENGTH = 100;
const unsigned ENGLISH_LETTERS_COUNT = 26;

void freeArray(char* word)
{
	delete[] word;
}

void freeMatrix(char** words, unsigned wordsCount)
{
	for (size_t i = 0; i < wordsCount; i++)
	{
		freeArray(words[i]);
	}
	delete[] words;
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

bool isWordMadeUpOfTheLetters(const char* letters, unsigned lettersCount, const char* enteredWord)
{
	if (!letters || !enteredWord)
	{
		return false;
	}

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

	delete[] checkLetters;
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

unsigned calculatePointsForWord(const char* word)
{
	return getLength(word);
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

void printLetters(const char* letters, unsigned lettersCount)
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

int readWordsFromFile(const char* fileName, char**& words, unsigned& wordsCount)
{
	if (!fileName)
	{
		return 0;
	}

	ifstream myFile(fileName);
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

bool addWord(char**& words, unsigned& wordsCount)
{
	cout << "Enter word: ";
	char* newWord = new char[WORD_MAX_LENGTH + 1];
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
		return true;
	}
	cout << "Word already exists!" << endl;
	return false;
}

void changeGameSettings(unsigned& lettersCount, unsigned& gameRounds)
{
	char option = ' ';
	cout << endl;
	cout << "Choose what to change (letters count / game rounds): ";
	cin >> option;
	if (option == 'a')
	{
		unsigned updateCount = 0;
		cout << "Change count of letters to: ";
		cin >> updateCount;
		lettersCount = updateCount;
	}
	else if (option == 'b')
	{
		unsigned updateRounds = 0;
		cout << "Change count of rounds to: ";
		cin >> updateRounds;
		gameRounds = updateRounds;
	}
	else
	{
		cout << "Invalid input!" << endl;
	}
}

void startGame(const char* const* words, unsigned wordsCount, unsigned lettersCount, unsigned gameRounds)
{
	unsigned score = 0;
	char* letters = new char[lettersCount + 1];
	char* enteredWord = nullptr;
	for (size_t i = 1; i <= gameRounds; i++)
	{
		cout << endl;
		cout << "Round " << i << ". ";
		cout << "Available letters: ";
		generateRandomLetters(letters, lettersCount);

		while (true)
		{
			printLetters(letters, lettersCount);

			enteredWord = new char[WORD_MAX_LENGTH + 1];
			cin >> enteredWord;
			if (getLength(enteredWord) > WORD_MAX_LENGTH)
			{
				cout << "Invalid input! Max word length is " << WORD_MAX_LENGTH << " symbols!" << endl;
				continue;
			}

			if (isWordMadeUpOfTheLetters(letters, lettersCount, enteredWord) && findWordInDictionary(words, wordsCount, enteredWord))
			{
				score += calculatePointsForWord(enteredWord);

				break;
			}

			cout << "Invalid word. Try again with: ";
		}

		if (i != gameRounds)
		{
			cout << "Your points so far are: " << score << endl;
		}
	}
	cout << endl;
	cout << "GAME OVER!" << endl;

	cout << "Your total points are: " << score << endl;
	cout << "Returning to menu." << endl;
	freeArray(letters);
	freeArray(enteredWord);
}

void showMenuDesign()
{
	cout << " ______________________________________________" << endl
		 << "|                                              |" << endl
		 << "|                 Scrabble game                |" << endl
		 << "|______________________________________________|" << endl
		 << "|                                              |" << endl
		 << "|                   MAIN MENU                  |" << endl
		 << "|                                              |" << endl
		 << "|  1. START NEW GAME                           |" << endl
		 << "|                                              |" << endl
		 << "|  2. SETTINGS:                                |" << endl
		 << "|    a. CHOOSE COUNT OF LETTERS (DEFAULT - 10) |" << endl
		 << "|    b. CHOOSE COUNT OF ROUNDS (DEFAULT - 10)  |" << endl
		 << "|                                              |" << endl
		 << "|  3. ENTER A NEW WORD                         |" << endl
		 << "|                                              |" << endl
		 << "|  4. EXIT                                     |" << endl
		 << "|______________________________________________|" << endl
		 << endl
		 << "Choose from the menu: ";
}

void selectingMenuFunctionality(char** words, unsigned wordsCount)
{
	unsigned functionalityNumber = 0, gameRounds = 10, lettersCount = 10;
	bool areThereAddedWords = false;

	while (true)
	{
		showMenuDesign();

		cin >> functionalityNumber;

		switch (functionalityNumber)
		{
		case 1:
			startGame(words, wordsCount, lettersCount, gameRounds);
			break;
		case 2:
			changeGameSettings(lettersCount, gameRounds); 
			break;
		case 3:
			areThereAddedWords = addWord(words, wordsCount);
			break;
		case 4:
			if (areThereAddedWords)
			{
				writeWordInFile(FILE_NAME, words, wordsCount);
			}
			return;
		default:
			cout << "Incorrect imput! Try again!" << endl;
			break;
		}
	}
}

int main()
{
	char** words = nullptr;
	unsigned wordsCount = 0;

	srand(time(NULL));
	readWordsFromFile(FILE_NAME, words, wordsCount);
	selectingMenuFunctionality(words, wordsCount);

	freeMatrix(words, wordsCount);
}
