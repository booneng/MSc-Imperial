#pragma once
void encode(const char *surname, char *soundex);
bool compare(const char *one, const char *two);
int count(const char *surname, const char *sentence);
char digitmap(char letter);