
#include "define.h"

class input
{
public:
	static bool autoChangeLine;
	static int maxVisualOffset;
	static void addNewDialogInfoLine();
};

int getVisualOffsetX(int number, std::wstring target, int charsize);
int getVisualOffsetY(int number, std::wstring target, int charsize);