#include <iostream>
#include <string>
#include <cctype>
#include <sstream>
#include <cassert>
using namespace std;

char encodeNote(int octave, char noteLetter, char accidentalSign)
{
	// This check is here solely to report a common CS 31 student error.
	if (octave > 9)
	{
		cerr << "********** encodeNote was called with first argument = "
			<< octave << endl;
	}

	// Convert Cb, C, C#/Db, D, D#/Eb, ..., B, B#
	//      to -1, 0,   1,   2,   3, ...,  11, 12

	int note;
	switch (noteLetter)
	{
	case 'C':  note = 0; break;
	case 'D':  note = 2; break;
	case 'E':  note = 4; break;
	case 'F':  note = 5; break;
	case 'G':  note = 7; break;
	case 'A':  note = 9; break;
	case 'B':  note = 11; break;
	default:   return ' ';
	}
	switch (accidentalSign)
	{
	case '#':  note++; break;
	case 'b':  note--; break;
	case ' ':  break;
	default:   return ' ';
	}

	// Convert ..., A#1, B1, C2, C#2, D2, ... to
	//         ..., -2,  -1, 0,   1,  2, ...

	int sequenceNumber = 12 * (octave - 2) + note;

	string keymap = "Z1X2CV3B4N5M,6.7/A8S9D0FG!H@JK#L$Q%WE^R&TY*U(I)OP";
	if (sequenceNumber < 0 || sequenceNumber >= keymap.size())
		return ' ';
	return keymap[sequenceNumber];
}

bool hasCorrectSyntax(string song)
{
	bool result = true;
	for (int i = 0; i < song.size(); i++)//checks through cases where the syntax of the song string is not correct
	{

		if (song[i] != 'A' && song[i] != 'B' && song[i] != 'C' && song[i] != 'D' && song[i] != 'E' && song[i] != 'F' && song[i] != 'G' && song[i] != 'b' && song[i] != '#' && (!isdigit(song[i])) && song[i] != '/')// has to be an uppercase letter, sign, digit, or /
		{
			result = false;
		}
		if (isalpha(song[i]) && isdigit(song[i + 1]) && (song[i + 2] == 'b' || song[i + 2] == '#'))
		{
			result = false;
		}
		if ((song[0] == 'b' || song[0] == '#' || isdigit(song[0])))// if "#D" then it returns false
		{
			result = false;
		}

		if (isdigit(song[i]) && isdigit(song[i + 1]))// checks to see if the octave is onl form 0-9
		{
			result = false;
		}
		if ((song[i] == '#' && song[i + 1] == 'b') || (song[i] == 'b' && song[i + 1] == '#'))// chechs to see if there are accidental signs right next to each other
		{
			result = false;
		}
		if (song[i] == ' ')// checks to see if there is a space in the song string which is not right syntax
		{
			result = false;
			break;
		}
		if (song[song.size() - 1] != '/')
		{
			result = false;
		}
		if (song[i] == ' ')
			result = false;
		if (song[i] == '/' && isdigit(song[i + 1]))// checks to see if there is a number after a beat
			result = false;
	}
	return result;
}

bool isPlayable(string song)
{
	int answer = true;
	if (!hasCorrectSyntax(song))
		answer = false;
	else if (hasCorrectSyntax(song))
	{
	
			
		for (int j = 0; j < song.size(); j++) //this loop goes through songs and lloks for unplayable notes returning false if unplayable
		{
			if (song[j] == 'C' && song[j + 1] == '6')
			{
				song[j] = 'B';
				song[j + 1] = '#';
				song[j + 2] = '5';
			}
			if (song[j] == '0' || song[j] == '1' || song[j] == '6' || song[j] == '7' || song[j] == '8' || song[j] == '9')
			{
				answer = false;
			}
			if ((song[j] == 'C') && (song[j + 1] == 'b') && (song[j + 2] == '2'))
			{
				answer = false;
			}
		}

	}
	return answer;

}

int accidentals(string song)
{
	int accidentals = 0;
	for (int i = 0; i < song.size(); i++)
	{
		if (song[i] == 'b' || song[i] == '#')
			accidentals;
	}
	return accidentals;
}

int octaves(string song)
{
	int octaves = 0;
	for (int i = 0; i < song.size(); i++)
	{
		if (isdigit(song[i]))
			octaves++;
	}
	return octaves;
}


int encodeSong(string song, string& instructions, int& badBeat)
{
	int value = 0;
	int beats = 1;//counter for the place where badBeat occurs
	int number = 0;
	string temp = "";

	if (!hasCorrectSyntax(song)) //when the string does not have correct syntax
		value = 1;

	else if (!isPlayable(song) && hasCorrectSyntax(song))//when the song has good syntax but not playable
	{
		for (int c = 0; c < song.size(); c++)
		{
			if (song[c] == '/')
				beats++;
			if (song[c] == '0' || song[c] == '1' || song[c] == '6' || song[c] == '7' || song[c] == '8' || song[c] == '9') //checks if its playable 
			{
				badBeat = beats;
				break;
			}
			else if ((song[c] == 'C' && (song[c + 1] == 'b' && song[c + 2] == '2')))
			{
				badBeat = beats;
				break;
			}
		}
		value = 2;
	}


	else if (isPlayable(song))//this is case number one where the song is playable
	{   
		instructions = "";  //we cannot assume that the instructions comes empty so this initialises instructions to an empty string
																					
		for (int k = 0; k != song.size(); k++) 
		{
			if (song[k] == '/' && song[k + 1] == '/')
			{
				instructions += ' ';//adding a space for two slashes
			}

			if (isupper(song[k])) //the character has to be an uppercase note for the rest of the if statements to work
			{

				if ((song[k + 1] == '#' || song[k + 1] == 'b') && !isdigit(song[k + 2])) {
					temp += encodeNote(4, song[k], song[k + 1]);   //when there is no digit in the note the default value is in octave four
					number++;
				}

				else if (isdigit(song[k + 1]))
				{
					int c = (int)song[k + 1] - '0';
					temp += encodeNote(c, song[k], ' ');
					number++;
				}

				else if ((song[k + 1] == '#' || song[k + 1] == 'b') && isdigit(song[k + 2])) {
					int c = song[k + 2] - '0';//this changes the character digit value into a integer which is needed as a parameter for the function encodeNote 
					temp += encodeNote(c, song[k], song[k + 1]);
					number++;
				}


				//checks if the note has no accidental sign and no octave. Example: A, B, F (Default octave of 4 given)
				else {
					temp += encodeNote(4, song[k], ' ');//when the note consists of only a uppercaseletter
					number++;
				}
			}
		
			if (song[k + 1] == '/')
			{
				if (number >= 2)//if it is a chord is adds a bracket at the end and inserts an open bracket before the first note
				{
					instructions += "[" + temp + "]";//instructions adds temp with brackets if its a chord								
					temp = "";// reset temp to an empty string again
					number = 0;// reset number to 0
				}
				else {
					instructions += temp;//adds temp string to instructions if not chord without brackets
					temp = "";//resets temp to an empty string again
				}
			}
			if (song[k] == '/') 
			{
				number = 0;
			}
		
		}
		value = 0;
	}

	return value;
}
int main()
{
	assert(hasCorrectSyntax("D5//D/"));
	assert(!hasCorrectSyntax("D5//Z/"));
	string instrs;
	int badb;
	instrs = "xxx"; badb = -999; // so we can detect whether these get changed
	assert(encodeSong("DADDA/", instrs, badb) == 0 && instrs == "[HQHHQ]");
	assert(encodeSong("D5//D/", instrs, badb) == 0 && instrs == "R H"  &&  badb == -999);
	instrs = "xxx"; badb = -999; // so we can detect whether these get changed
	assert(encodeSong("D5//Z/", instrs, badb) == 1 && instrs == "xxx"  &&  badb == -999);
	assert(encodeSong("D5//D8/", instrs, badb) == 2 && instrs == "xxx"  &&  badb == 3);
	assert(encodeSong("C/C/G/G/A/A/G/", instrs, badb) == 0 && instrs == "GGLLQQL");
	assert(encodeSong("D3/F#3/A3/D4//D3F#3A3D4/", instrs, badb) == 0 && instrs == ".8DH [.8DH]");
	assert(encodeSong("G3B3DD5//G/A/A3B/C5/B3D5//G//G//CE5//C5/D5/E5/F#5/B3G5//G//G/", instrs, badb) == 0 && instrs == "[SFHR] LQ[DW]E[FR] L L [GT] ERT*[FU] L L");
	assert(encodeSong("//", instrs, badb) == 0 && instrs == " ");
	assert(encodeSong("", instrs, badb) == 0 && instrs == "");
	cerr << "All tests succeeded" << endl;
}