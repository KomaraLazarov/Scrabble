#include <iostream>
#include <fstream>

using namespace std;

const char FILE_NAME[] = "WordsDictionary.txt";

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
	char** words = nullptr;
	unsigned wordsCount = 0;

	readFile(FILE_NAME, words, wordsCount);
}
