
#include "define.h"

class input
{
public:
	static void removeMarkerCharacters(std::wstring *buf);
	static void removeAllMarkerCharacters(std::wstring *buf);
	static int parseColorCode(wchar_t a, wchar_t b);
};