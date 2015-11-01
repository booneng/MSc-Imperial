#include <iostream>
#include "soundex.h"
using namespace std;

int main()
{
	char soundex[10];
	encode("Jackson", soundex);
	cout << soundex << endl;
	int i;
	i = count("Leeson", "Lesson, Lesson, Lesson, Lemon.");
	cout << "number is " << i << endl;
	return 0;
}
