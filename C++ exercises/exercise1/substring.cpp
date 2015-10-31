#include <iostream>
#include "substring.h"
#include <cstring>

using namespace std;

int substring_position(const char *string1, const char *string2)
{
	if (!is_prefix(string1, string2))
		return -1;
	if (string1[0] == '\0')
		return 0;
	int i = 0;
	while (string2[i] != '\0')
	{
		if (string1[0] == string2[i])
		{
			if (substring_position(string1 + 1, string2+i+1) == 0)
				return i;
		}
		i++;
	}
}

bool is_prefix(const char *string1, const char *string2)
{
	if (string1[0] == '\0')
		return true;
	if (string2[0] == '\0')
		return false;
	if (string1[0] != '\0')
	{
		if (string1[0] == string2[0])
			if (is_prefix(string1 + 1, string2 + 1))
				return true;
		if (is_prefix(string1, string2 + 1))
			return true;
	}
	return false;
}

