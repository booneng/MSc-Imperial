#include <iostream>
#include "soundex.h"
using namespace std;

int main()
{
	char soundex[4];
	encode("Jackson", soundex);
	cout << soundex << endl;
	int i;
	i = count("Leeson", "Linnings, Lesson, Lesson, Lemon.");
	cout << i << endl;
	return 0;
}