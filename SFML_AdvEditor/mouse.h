
#include <string>
#include "define.h"

class mouse
{
public:
	static bool buttonClick;

	static int attachId;
	static int attachDialogInfoBox;
	static int selectDialogInfoBox;
	static int attachDialogLink;
	static int selectDialogLink;
	static int attachDialogLinkPoint;

	static int multiSelCounter;
	static int multiSelDialog[SELECTION_LIMIT];
	static int multiSelAttachOffsetX[SELECTION_LIMIT];
	static int multiSelAttachOffsetY[SELECTION_LIMIT];

	static int selectTool;
	static int prevTool;
	
	static int attachOffsetX;
	static int attachOffsetY;
	static int lastKnownPosX;
	static int lastKnownPosY;
};

class linker
{
public:
	static bool pointAfound;
	static int linkType;

	static int pointAposX;
	static int pointAposY;
	static int linkInfoId;
};

class textTool
{
public:
	static int editField;
	static int editCaretChar;
	static int editCaretLine;
	static std::wstring buffer;
	static int editTarget;

	static float editCaretTimer;
	static bool editCaretDisplay;
};