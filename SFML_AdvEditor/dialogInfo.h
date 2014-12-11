
#include <string.h>

#include "define.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class e_dialogBox
{
public:
	bool isValid;

	bool e_isVisible;
	bool e_isHovered;
	int e_boxSizeX;
	int e_boxSizeY;
	int e_boxPosX;
	int e_boxPosY;

	void e_roundBoxToGrid();
	std::wstring e_boxTitle;
	sf::Text e_boxTitleDraw;
};

class dialogInfo : public e_dialogBox
{
public:
	static int entryPoint;
	static int bsodPoint;
	int globalId; 

	int type;
	sf::Color g_descriptionColor[128];
	std::wstring g_descriptionText[128];
	sf::Text e_descriptionDraw[128];
	int g_descriptionStringsUsed;

	int var_value;
	int hook_amount;
	int hook_actionId[LINK_LIMIT];
	int e_hook_pointAposX[LINK_LIMIT];
	int e_hook_pointAposY[LINK_LIMIT];
	int e_hook_pointBposX[LINK_LIMIT];
	int e_hook_pointBposY[LINK_LIMIT];

	void init(int myId = -1, int myType = DIALOGTYPE_INFO);
	void e_adjustBoxToText();
	void e_moveLinkToId(int id);
	void g_descrLenAdjust();
	void e_updateDrawInfo();
	bool isInRegion(int startX, int startY, int stopX, int stopY);
	static int findDialogInfoBoxInPoint(int x, int y, int myType = DIALOGTYPE_ANY);
	static void updateVisibility();
	dialogInfo();
};