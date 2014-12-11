
#include "main.h"

void input::removeMarkerCharacters(std::wstring *buf)
{
	int find;
	// New line
	do 
	{
		find = buf->find(L"/n");
		if (find != -1) { buf->erase(find, find + 2); }
	}
	while (find != -1);
}

void input::removeAllMarkerCharacters(std::wstring *buf)
{
	int find;
	// New line
	do 
	{
		find = buf->find(L"/n");
		if (find != -1) { buf->erase(find, find + 2); }
	}
	while (find != -1);
	// Bold
	do 
	{
		find = buf->find(L"|b|");
		if (find != -1) { buf->erase(find, find + 3); }
	}
	while (find != -1);
	// Underlined
	do 
	{
		find = buf->find(L"|u|");
		if (find != -1) { buf->erase(find, find + 3); }
	}
	while (find != -1);
	// Italic
	do 
	{
		find = buf->find(L"|i|");
		if (find != -1) { buf->erase(find, find + 3); }
	}
	while (find != -1);
}

int input::parseColorCode(wchar_t a, wchar_t b)
{
	int A, B;
	// Table for A
	if (a == '0') { A = 0; }		else if (a == '1') { A = 1; }	else if (a == '2') { A = 2; }	else if (a == '3') { A = 3; }
	else if (a == '4') { A = 4; }	else if (a == '5') { A = 5; }	else if (a == '6') { A = 6; }	else if (a == '7') { A = 7; }
	else if (a == '8') { A = 8; }	else if (a == '9') { A = 9; }	else if (a == 'a') { A = 10; }	else if (a == 'b') { A = 11; }
	else if (a == 'c') { A = 12; }	else if (a == 'd') { A = 13; }	else if (a == 'e') { A = 14; }	else if (a == 'f') { A = 15; }
	// Table for B
	if (b == '0') { B = 0; }		else if (b == '1') { B = 1; }	else if (b == '2') { B = 2; }	else if (b == '3') { B = 3; }
	else if (b == '4') { B = 4; }	else if (b == '5') { B = 5; }	else if (b == '6') { B = 6; }	else if (b == '7') { B = 7; }
	else if (b == '8') { B = 8; }	else if (b == '9') { B = 9; }	else if (b == 'b') { B = 10; }	else if (b == 'b') { B = 11; }
	else if (b == 'c') { B = 12; }	else if (b == 'd') { B = 13; }	else if (b == 'e') { B = 14; }	else if (b == 'f') { B = 15; }
	// Calculating
	return A * 16 + B;
}