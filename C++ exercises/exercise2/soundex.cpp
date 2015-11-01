#include <iostream>
#include "soundex.h"
#include <cctype>
#include <cstring>

using namespace std;

char digitmap(char letter)
{
	if (letter == 'b' || letter == 'f' || letter == 'p' || letter == 'v')
		return '1';
	if (letter == 'c' || letter == 'g' || letter == 'j' || letter == 'k' || letter == 'q' || letter == 's' || letter == 'x' || letter == 'z')
		return '2';
	if (letter == 'd' || letter == 't')
		return '3';
	if (letter == 'l')
		return '4';
	if (letter == 'm' || letter == 'n')
		return '5';
	if (letter == 'r')
		return '6';
	return '0';
}

void encode(const char *surname, char *soundex)
{
	soundex[0] = surname[0];
	int i = 1, j=1;
	while (j<4 && surname[i] != '\0')
	{
		for (char k = '1'; k <= '6'; k++)
		{
			if (digitmap(surname[i]) == k)
			{
				if (digitmap(surname[i - 1]) != k)
				{
					soundex[j] = k;
					j++;
				}
			}
		}
		i++;
	}
	while (j < 4)
	{
		soundex[j] = '0';
		j++;
	}
}

bool compare(const char *one, const char *two)
{
	if (one[0] == '\0')
		return true;
	if (one[0] == two[0])
		if (compare(one+1, two+1))
			return true;
	return false;
}

int count(const char *surname, const char *sentence)
{
	int number = 0;
	char soundex1[4], soundex2[4];
	encode(surname, soundex1);
	int i = 0;
	while (sentence[i] != '\0')
	{
		if (sentence[i] == soundex1[0])
		{
			int j = 1;
			while (isalpha(sentence[i + j]))
			{
				j++;
			}
			char temp[80];
			for (int k = 0; k < j; k++)
			{
				temp[k] = sentence[i + k];
			}
			temp[j] = '\0';
			encode(temp, soundex2);
			cout << temp << endl;
			cout << soundex2 << endl;
			cout << soundex1 << endl;
			cout << compare(soundex1, soundex2) << endl;
			cout << strlen(soundex1) << " " << strlen(soundex2) << endl << endl;
			if (!strcmp(soundex1, soundex2))
			{
				number++;
			}
		}
		i++;
	}
	return number;
}