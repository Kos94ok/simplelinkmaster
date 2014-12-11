
#include "main.h"

void e_dialogBox::e_roundBoxToGrid()
{
	e_boxPosX = a_math::round((float)e_boxPosX / GRID_STEP) * GRID_STEP;
	e_boxPosY = a_math::round((float)e_boxPosY / GRID_STEP) * GRID_STEP;
}

void dialogInfo::e_adjustBoxToText()
{
	int oldSizeX = e_boxSizeX, oldSizeY = e_boxSizeY;
	int maxSizeX = 240, maxSizeY = 60;
	maxSizeX = max(maxSizeX, getVisualOffsetX(e_boxTitle.length(), e_boxTitle, 24) + GRID_STEP);
	// Looking for the longest string
	for (int i = 0; i < g_descriptionStringsUsed; i++)
	{
		maxSizeX = max(maxSizeX, getVisualOffsetX(g_descriptionText[i].length(), g_descriptionText[i], 24) + GRID_STEP);
	}

	e_boxSizeX = maxSizeX;
	e_boxSizeY = 60 + g_descriptionStringsUsed * GRID_STEP;

	e_boxSizeX = a_math::round((float)(e_boxSizeX + 5) / GRID_STEP) * GRID_STEP;

	// Looking for own ID
	int myId = -1;
	for (int i = 0; i < gl_dialogInfoCounter; i++)
	{
		if (&gl_dialogInfo[i] == this) { myId = i; }
	}
	if (myId == -1) { return; }
	// Checking for border-based links
	for (int y = 0; y < gl_dialogInfoCounter; y++)
	{
		for (int x = 0; x < gl_dialogInfo[y].hook_amount; x++)
		{
			if (&gl_dialogInfo[y] == this)
			{
				if (abs(gl_dialogInfo[y].e_hook_pointAposX[x] - oldSizeX) <= 10) { gl_dialogInfo[y].e_hook_pointAposX[x] += (e_boxSizeX - oldSizeX); }
				if (abs(gl_dialogInfo[y].e_hook_pointAposY[x] - oldSizeY) <= 10) { gl_dialogInfo[y].e_hook_pointAposY[x] += (e_boxSizeY - oldSizeY); }
			}
			else if (&gl_dialogInfo[gl_dialogInfo[y].hook_actionId[x]] == this)
			{
				if (abs(gl_dialogInfo[y].e_hook_pointBposX[x] - oldSizeX) <= 10) { gl_dialogInfo[y].e_hook_pointBposX[x] += (e_boxSizeX - oldSizeX); }
				if (abs(gl_dialogInfo[y].e_hook_pointBposY[x] - oldSizeY) <= 10) { gl_dialogInfo[y].e_hook_pointBposY[x] += (e_boxSizeY - oldSizeY); }
			}
		}
	}
}

dialogInfo::dialogInfo()
{
	isValid = false;
	e_isVisible = true;
	e_boxPosX = 0;
	e_boxPosY = 0;
	e_boxSizeX = 240;
	e_boxSizeY = 60;
	hook_amount = 0;
	for (int i = 0; i < LINK_LIMIT; i++)
	{
		hook_actionId[i] = -1;
	}
	g_descriptionStringsUsed = 0;
	for (int i = 0; i < 128; i++)
	{
		g_descriptionText[i] = L"";
	}
}

void dialogInfo::init(int myId, int myType)
{
	std::wstring wbuf;
	isValid = true;
	type = myType;

	std::wstring closingbracket = L"]";
	if (myType == DIALOGTYPE_INFO) { wbuf = L"dialogInfo"; }
	else if (myType == DIALOGTYPE_ACTION) { wbuf = L"dialogAction"; }
	else if (myType == DIALOGTYPE_TELEPORT) { wbuf = L"dialogTP"; }
	else if (myType == DIALOGTYPE_VARIABLE) { wbuf = L"dialogVar"; }
	else if (myType == DIALOGTYPE_CONDITION) { wbuf = L"dialogCond"; }
	else if (myType == DIALOGTYPE_IMAGE) { wbuf = L"dialogImage"; }
	else if (myType == DIALOGTYPE_SOUND) { wbuf = L"dialogSound"; }
	e_boxTitle = wbuf;
	e_boxPosX = (-camera::viewportOffsetX + camera::resolutionX / 2 - e_boxSizeX / 2);
	e_boxPosY = (-camera::viewportOffsetY + camera::resolutionY / 2 - e_boxSizeY / 2);
	for (int i = 0; i < g_descriptionStringsUsed; i++) { g_descriptionText[i] = L""; }
	g_descriptionStringsUsed = 0;
	e_adjustBoxToText();
	e_roundBoxToGrid();
	e_updateDrawInfo();
}

int dialogInfo::findDialogInfoBoxInPoint(int x, int y, int myType)
{
	// Selected box goes first
	int a = mouse::selectDialogInfoBox;
	if (a != -1 && gl_dialogInfo[a].e_boxPosX < x && gl_dialogInfo[a].e_boxPosX + gl_dialogInfo[a].e_boxSizeX > x
			&& gl_dialogInfo[a].e_boxPosY < y && gl_dialogInfo[a].e_boxPosY + gl_dialogInfo[a].e_boxSizeY > y)
	{
		if (myType == DIALOGTYPE_ANY || gl_dialogInfo[a].type == myType) { return a; }
	}
	// Other boxes go second
	for (int i = gl_dialogInfoCounter - 1; i > -1; i--)
	{
		if (gl_dialogInfo[i].e_boxPosX < x && gl_dialogInfo[i].e_boxPosX + gl_dialogInfo[i].e_boxSizeX > x
			&& gl_dialogInfo[i].e_boxPosY < y && gl_dialogInfo[i].e_boxPosY + gl_dialogInfo[i].e_boxSizeY > y)
		{
			if (myType == DIALOGTYPE_ANY || gl_dialogInfo[i].type == myType) { return i; }
		}
	}
	return -1;
}

void dialogInfo::updateVisibility()
{
	int screenX = -camera::viewportOffsetX - camera::resolutionX / 2 / camera::viewportZoom + camera::resolutionX / 2;
	int screenY = -camera::viewportOffsetY - camera::resolutionY / 2 / camera::viewportZoom + camera::resolutionY / 2;
	int screenFarX = screenX + camera::resolutionX / camera::viewportZoom;
	int screenFarY = screenY + camera::resolutionY / camera::viewportZoom;
	// Checking
	for (int i = 0; i < gl_dialogInfoCounter; i++)
	{
		gl_dialogInfo[i].e_isVisible = true;
		if (gl_dialogInfo[i].e_boxPosX + gl_dialogInfo[i].e_boxSizeX < screenX || gl_dialogInfo[i].e_boxPosX > screenFarX
			|| gl_dialogInfo[i].e_boxPosY + gl_dialogInfo[i].e_boxSizeY < screenY || gl_dialogInfo[i].e_boxPosY > screenFarY)
		{
			gl_dialogInfo[i].e_isVisible = false;
		}
	}
}

void dialogInfo::e_moveLinkToId(int id)	{}
void dialogInfo::g_descrLenAdjust() {}

bool dialogInfo::isInRegion(int startX, int startY, int stopX, int stopY)
{
	bool advancedChecking = true;	int checkStep = 1;
	int i;
	// Fixing the region
	if (startX > stopX) { i = startX;	startX = stopX;		stopX = i; }
	if (startY > stopY) { i = startY;	startY = stopY;		stopY = i; }
	// Optimization
	int sizeX = stopX - startX;
	int sizeY = stopY - startY;
	int boxPosX = e_boxPosX + e_boxSizeX;
	int boxPosY = e_boxPosY + e_boxSizeY;
	// Main checking
	if (isPointInRegion(e_boxPosX, e_boxPosY, startX, startY, sizeX, sizeY)) { return true; }
	if (isPointInRegion(e_boxPosX + e_boxSizeX, e_boxPosY, startX, startY, sizeX, sizeY)) { return true; }
	if (isPointInRegion(e_boxPosX + e_boxSizeX, e_boxPosY + e_boxSizeY, startX, startY, sizeX, sizeY)) { return true; }
	if (isPointInRegion(e_boxPosX, e_boxPosY + e_boxSizeY, startX, startY, sizeX, sizeY)) { return true; }
	//if (e_boxPosX > startX && e_boxPosX < stopX && e_boxPosY > startY && e_boxPosY < stopY) { return true; }
	//if (e_boxPosX + e_boxSizeX > startX && e_boxPosX + e_boxSizeX < stopX && e_boxPosY > startY && e_boxPosY < stopY) { return true; }
	//if (e_boxPosX + e_boxSizeX > startX && e_boxPosX + e_boxSizeX < stopX && e_boxPosY + e_boxSizeY > startY && e_boxPosY + e_boxSizeY < stopY) { return true; }
	//if (e_boxPosX > startX && e_boxPosX < stopX && e_boxPosY + e_boxSizeY > startY && e_boxPosY + e_boxSizeY < stopY) { return true; }

	// Advanced checking
	if (advancedChecking)
	{
		for (int x = e_boxPosX; x < e_boxPosX + e_boxSizeX; x += checkStep)
		{
			if (isPointInRegion(x, e_boxPosY, startX, startY, sizeX, sizeY)) { return true; }
			if (isPointInRegion(x, boxPosY, startX, startY, sizeX, sizeY)) { return true; }
		}
		for (int y = e_boxPosY; y < e_boxPosY + e_boxSizeY; y += checkStep)
		{
			if (isPointInRegion(e_boxPosX, y, startX, startY, sizeX, sizeY)) { return true; }
			if (isPointInRegion(boxPosX, y, startX, startY, sizeX, sizeY)) { return true; }
		}
	}
	return false;
}

void dialogInfo::e_updateDrawInfo()
{
	e_boxTitleDraw.setFont(gl_mainFont);
	e_boxTitleDraw.setString(e_boxTitle);
	e_boxTitleDraw.setCharacterSize(24);
	e_boxTitleDraw.setColor(sf::Color(0, 0, 0));
	e_boxTitleDraw.setPosition(10, 3);
	for (int i = 0; i < g_descriptionStringsUsed; i++)
	{
		e_descriptionDraw[i].setFont(gl_mainFont);
		e_descriptionDraw[i].setString(g_descriptionText[i]);
		e_descriptionDraw[i].setCharacterSize(24);
		e_descriptionDraw[i].setColor(sf::Color(0, 0, 0));
	}
}