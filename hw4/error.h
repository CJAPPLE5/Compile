#ifndef ERROR
#define ERROR
#include<iostream>
#include<string>
#include<map>
#include<string.h>
#include<fstream>
#include"variable.h"

using namespace std;

int isadd(char c)
{
	return c == '+' || c == '-';
}

int ismul(char c)
{
	return c == '*' || c == '/';
}

int isalpha(char c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_');
}

int isnum(char c)
{
	return c >= '0' && c <= '9';
}

enum errors has_error()
{
	if (symbol == CHARCON) {
		if (isadd(token[0]) || ismul(token[0]) ||
			isalpha(token[0]) || isnum(token[0])) {
			return NOERROR;
		}
		else {
			return ILLEGALWORD;
		}
	}
	else if (symbol == STRCON) {
		for (int i = 0; i < strlen(token); i++) {
			if (!(token[i] == 32 || token[i] == 33 ||
				(token[i] >= 35 && token[i] <= 126))) {
				return ILLEGALWORD;
			}
		}
		return NOERROR;
	}
}

#endif
