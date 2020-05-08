#define _CRT_SECURE_NO_DEPRECATE
#include "utilities.h"
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

const char WORDFILENAME[] = "C:/CS31/stars/mywordfile.txt";

void eliminateIndex(char x[], int index) //removes the element in the cstring x at the given index
{
	char arr[7]; //intializes a c string 
	for (int i = 0, j = 0; i < 7; i++) //the loop goes through cstring that was an argument and has a counter j
	{
		if (i != index) //if i is not the index, then the temporary cstring adds the element  
		{
			arr[j] = x[i];
			j++;
		}
	}
	strcpy(x, arr); // the temporary c string is copied into the given c string
}

int runOneRound(const char wordList[][7], int nWords, int wordNum) //runs one round of the game
{
	
	char secret[7];
	char temp[7];
	int result = 0;
	bool answer = true;
	bool notLowercase = false;
	bool notInList = true;

	if (wordNum < 0 || wordNum >= nWords) //if the index of the secret word is greater than the total number of words in the list or negative
		result = -1;
	else
	{
		int tries = 1; //the number of attempts to guess the secret word
		int index = 0;
		int stars = 0; //characters that are the same at the same index of the secret and probe word
		int planets = 0; //characters that are the same but at different indexes of the secret and probe word

		strcpy(secret, wordList[wordNum]);
		//cout << "The secret word is " << secret << "." << endl; //for testing purposes

		while ((answer)) //whle the user does not guess the secret word
		{
			char tempProbe[7];
			char tempSecret[7];
			strcpy(tempSecret, secret);

			planets = 0; //after every attempt stars, planets and the index are reinitialized
			stars = 0;
			index = 0;

			cout << "Probe word: ";
			char probe[1000];
			cin.getline(probe, 1000);
			strcpy(tempProbe, probe);

			for (int c = 0; c < strlen(probe); c++) //this for loop checks to see if any of the elements in the probe c string are not lowercase 
			{
				if (probe[c] < 'a' || probe[c] > 'z') //checks every character in the probe word to see if it is lowercase
				{
					notLowercase = true;
					break;
				}
				else
					notLowercase = false;
			}

			for (int x = 0; x < nWords; x++)
			{
				strcpy(temp, wordList[x]); //checks ever word in the list to compare with the probe word
				if (strcmp(probe, temp))
					notInList = true;
				else
				{
					notInList = false; //if the word is in the list notInList is false and breaks out of the loop
					break;
				}
			}

			if (strlen(probe) > 6 || strlen(probe) < 4) //if the probe word is not 4 to 6 letters
				cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
			else if (notLowercase) //if the probe word is not all lowercase
				cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
			else if (notInList) //if the probe word is not in the list
				cout << "I don't know that word." << endl;
			else
			{
				if (strcmp(secret, probe)) //true if the secret and probe word are not the same
				{
					
					while (secret[index] != '\0')
					{
						if (secret[index] == probe[index])
						{
							stars++; //increments stars everytime the characters at the same index are equal
							eliminateIndex(tempProbe, index); //eliminates this index from tempProbe and tempSecret
							eliminateIndex(tempSecret, index);

						}
						index++;
					}
					for (int i = 0; i < strlen(tempSecret); i++)  //uses tempSecret and tempProbe to not use a star character with a planet character
					{
						for (int j = 0; j < strlen(tempProbe); j++)
						{
							if(i == j)
							{
								planets += 0; //if the indexes are the same, it is not a planet but a star
							}
							else if (tempSecret[i] == tempProbe[j])
							{
								planets++; // else planets is incermented 
								break; //so one character is not used twice as a planet
							}
						}
					}
					tries++;
					cout << "Stars: " << stars << ", ";
					cout << "Planets: " << planets << endl;
					
				}
				else
				{
					answer = false;
				}

			}
		}
		result = tries; //returns the number of tries it takes for the user to get the word right
	}
	return result;
}

int main()
{

	char wordList[9000][7];
	int maxWords = 2;
	int nWords = getWords(wordList, maxWords, WORDFILENAME);

	if (nWords < 1 || nWords > maxWords)
		cout << "No words were loaded, so I can't play the game." << endl;
	else
	{
		cout << "How many rounds do you want to play? "; //asks the user how many rounds they want to play
		int rounds;
		cin >> rounds;
		cin.ignore(10000, '\n');

		if (rounds < 0)
			cout << "The number of rounds must be positive.";
		else
		{
			int x = 1;
			int totalTries = 0;
			double average = 0;
			int minimum = 0;
			int maximum = 0;
			cout << endl;
			while (x <= rounds) //loops through how many rounds the user wants to play
			{
				int wordNum = randInt(0, maxWords - 1); //chooses the element of the secret word
				
				cout << "Round " << x << endl;
				char secretWord[7];
				strcpy(secretWord, wordList[wordNum]);
				cout << "The secret word is " << strlen(secretWord) << " letters long." << endl;
				int num = runOneRound(wordList, nWords, wordNum); //runs one round of the game
				
				if (num == -1)
					cout << "PROGRAM FAILED" << endl;
				if (num == 1) //if the user gets the right word in one try
					cout << "You got it in " << num << " try." << endl;
				else //if the user gets the right word in more than one try
					cout << "You got it in " << num << " tries." << endl;

				totalTries += num;
				average = ((double)totalTries) / x;

				if (x == 1) //checks to see what the minimum number of tries are for all the rounds 
					minimum = num;
				else if (num < minimum)
					minimum = num;
				else
					minimum += 0;

				if (x == 1) //checks to see what the maximum number of tries are for all the rounds
					maximum = num;
				else if (num > minimum)
					maximum = num;
				else
					maximum += 0;

				cout << "Average: " << fixed << setprecision(2) << average << ", minimum: " << minimum << ", maximum: " << maximum << endl << endl;
				x++;
			}

		}
	}




	/*if (n == 2)
	{
		cout << "getWords successfully found the file and read its two words." << endl;
		cout << "You're ready to start working on Project 5." << endl;
	}
	else if (n == -1)
		cout << "The path to your file of words is probably incorrect" << endl;
	else
		cout << "getWords found the file, but loaded " << n
		<< " words instead of 2" << endl;*/


}