
#include "main.h"

void button::init()
{
	texID = TEX_EMPTY;
	posX = 0;
	posY = 0;
	sizeX = 350;
	sizeY = 60;

	action = MENU_NOTHING;
	nextMenu = MENU_NOTHING;
	hovered = false;
	textCenter = false;
}

void button::move(int newX, int newY)
{
	posX = newX;
	posY = newY;
}

void button::remove()
{
	int myId = -1;
	for (int i = 0; i < 64; i++)
	{
		if (this == &UI::btn[i]) { myId = i; }
	}
	if (myId == -1) { printf("[button::remove]: Can not find object ID. Returning.\n"); return; }

	for (int i = myId; i < UI::buttonCounter - 1; i++)
	{
		UI::btn[i] = UI::btn[i + 1];
	}
	UI::buttonCounter -= 1;
}

void slider::init()
{
	posX = 0;
	posY = 0;
	sizeX = 350;
	sizeY = 60;

	sliderValue = 0.50f;
	sliderMinValue = 0.00f;
	sliderMaxValue = 1.00f;
	sliderDivision = 0.01f;
}

void slider::move(int newX, int newY)
{
	posX = newX;
	posY = newY;
}

void slider::remove()
{
	int myId = -1;
	for (int i = 0; i < 64; i++)
	{
		if (this == &UI::sld[i]) { myId = i; }
	}
	if (myId == -1) { printf("[slider::remove]: Can not find object ID. Returning.\n"); return; }

	for (int i = myId; i < UI::sliderCounter - 1; i++)
	{
		UI::sld[i] = UI::sld[i + 1];
	}
	UI::sliderCounter -= 1;
}

int UI::addButton()
{
	UI::btn[UI::buttonCounter].init();
	UI::buttonCounter += 1;

	return UI::buttonCounter - 1;
}

int UI::findButtonInPoint(int i_posX, int i_posY)
{
	for (int i = 0; i < UI::buttonCounter; i++)
	{
		if (i_posX > UI::btn[i].posX && i_posX < UI::btn[i].posX + UI::btn[i].sizeX
			&& i_posY > UI::btn[i].posY && i_posY < UI::btn[i].posY + UI::btn[i].sizeY)
		{
			return i;
		}
	}
	return -1;
}

void UI::displayMenu(int level)
{
	int search = -1;
	int info = -1;
	// Main menu
	if (level == MENU_MAIN)
	{
		// Create
		int search;
		if (UI::displayingMenu != MENU_CREATE)
		{
			search = UI::addButton();
			UI::btn[search].nextMenu = MENU_CREATE;
			UI::btn[search].move(camera::resolutionX - 350, 50);
			UI::btn[search].text = L"File";
			UI::btn[search].sizeX = 300;
			UI::btn[search].sizeY = 40;
			UI::btn[search].textCenter = true;
		}
		// Add object
		if (UI::displayingMenu != MENU_ADDOBJECT)
		{
			search = UI::addButton();
			UI::btn[search].nextMenu = MENU_ADDOBJECT;
			UI::btn[search].move(camera::resolutionX - 350, 100);
			UI::btn[search].text = L"Add object";
			UI::btn[search].sizeX = 300;
			UI::btn[search].sizeY = 40;
			UI::btn[search].textCenter = true;
		}
		// Tools
		if (UI::displayingMenu != MENU_TOOLS)
		{
			search = UI::addButton();
			UI::btn[search].nextMenu = MENU_TOOLS;
			UI::btn[search].move(camera::resolutionX - 350, 150);
			UI::btn[search].text = L"Tools";
			UI::btn[search].sizeX = 300;
			UI::btn[search].sizeY = 40;
			UI::btn[search].textCenter = true;
		}
		// Other
		if (UI::displayingMenu != MENU_OTHER)
		{
			search = UI::addButton();
			UI::btn[search].nextMenu = MENU_OTHER;
			UI::btn[search].move(camera::resolutionX - 350, 200);
			UI::btn[search].text = L"Other";
			UI::btn[search].sizeX = 300;
			UI::btn[search].sizeY = 40;
			UI::btn[search].textCenter = true;
		}

		// Close menu
		search = UI::addButton();
		UI::btn[search].nextMenu = MENU_NOTHING;
		UI::btn[search].move(camera::resolutionX - 350, camera::resolutionY - 100);
		UI::btn[search].text = L"Close menu";
		UI::btn[search].sizeX = 300;		UI::btn[search].sizeY = 40;
		UI::btn[search].textCenter = true;

		// Close menu
		search = UI::addButton();
		UI::btn[search].action = MENU_EXIT;
		UI::btn[search].nextMenu = MENU_NOTHING;
		UI::btn[search].move(camera::resolutionX - 350, camera::resolutionY - 50);
		UI::btn[search].text = L"Close editor";
		UI::btn[search].sizeX = 300;		UI::btn[search].sizeY = 40;
		UI::btn[search].textCenter = true;

		search = UI::addButton();
		UI::btn[search].nextMenu = MENU_NOTHING;
		UI::btn[search].move(camera::resolutionX - 50, 0);
		UI::btn[search].text = L"";
		UI::btn[search].sizeX = 50;
		UI::btn[search].sizeY = camera::resolutionY;
		UI::btn[search].textCenter = true;

		// Setting the menu level
		UI::menuLevel = MENU_MAIN;
		UI::lastMenuLevel = UI::menuLevel;
	}
	else if (level == MENU_CREATE)
	{
		UI::displayingMenu = MENU_CREATE;
		UI::displayMenu(MENU_MAIN);

		// Back
		int search = UI::addButton();
		UI::btn[search].nextMenu = MENU_MAIN;
		UI::btn[search].move(camera::resolutionX - 350, 50);
		UI::btn[search].text = L"File";
		UI::btn[search].sizeX = 300;	UI::btn[search].sizeY = 40;
		UI::btn[search].textCenter = true;

		// Create
		search = UI::addButton();
		UI::btn[search].nextMenu = MENU_NOTHING;
		UI::btn[search].action = MENU_ACTION_CLEARMODULE;
		UI::btn[search].move(camera::resolutionX - 550, 50);
		UI::btn[search].text = L"Create";
		UI::btn[search].sizeX = 200;	UI::btn[search].sizeY = 40;
		UI::btn[search].textCenter = false;

		// Save
		search = UI::addButton();
		UI::btn[search].nextMenu = MENU_NOTHING;
		UI::btn[search].action = MENU_ACTION_SAVEMODULE;
		UI::btn[search].move(camera::resolutionX - 550, 100);
		UI::btn[search].text = L"Save";
		UI::btn[search].sizeX = 200;	UI::btn[search].sizeY = 40;
		UI::btn[search].textCenter = false;

		// Load
		search = UI::addButton();
		UI::btn[search].nextMenu = MENU_NOTHING;
		UI::btn[search].action = MENU_ACTION_LOADMODULE;
		UI::btn[search].move(camera::resolutionX - 550, 150);
		UI::btn[search].text = L"Load";
		UI::btn[search].sizeX = 200;	UI::btn[search].sizeY = 40;
		UI::btn[search].textCenter = false;

		UI::menuLevel = MENU_CREATE;
		UI::lastMenuLevel = MENU_MAIN;
		UI::displayingMenu = 0;
	}
	else if (level == MENU_ADDOBJECT)
	{
		UI::displayingMenu = MENU_ADDOBJECT;
		UI::displayMenu(MENU_MAIN);

		// Back
		int search = UI::addButton();
		UI::btn[search].nextMenu = MENU_MAIN;
		UI::btn[search].move(camera::resolutionX - 350, 100);
		UI::btn[search].text = L"Add object";
		UI::btn[search].sizeX = 300;	UI::btn[search].sizeY = 40;
		UI::btn[search].textCenter = true;

		// dialogInfo
		search = UI::addButton();
		UI::btn[search].nextMenu = MENU_ADDOBJECT;
		UI::btn[search].action = MENU_ACTION_CREATEINFO;
		UI::btn[search].move(camera::resolutionX - 550, 100);
		UI::btn[search].text = L"Info";
		UI::btn[search].sizeX = 200;	UI::btn[search].sizeY = 40;
		UI::btn[search].textCenter = false;

		// dialogAction
		search = UI::addButton();
		UI::btn[search].nextMenu = MENU_ADDOBJECT;
		UI::btn[search].action = MENU_ACTION_CREATEACTION;
		UI::btn[search].move(camera::resolutionX - 550, 150);
		UI::btn[search].text = L"Action";
		UI::btn[search].sizeX = 200;	UI::btn[search].sizeY = 40;
		UI::btn[search].textCenter = false;

		// dialogTeleport
		search = UI::addButton();
		UI::btn[search].nextMenu = MENU_ADDOBJECT;
		UI::btn[search].action = MENU_ACTION_CREATETELEPORT;
		UI::btn[search].move(camera::resolutionX - 550, 200);
		UI::btn[search].text = L"Teleport";
		UI::btn[search].sizeX = 200;	UI::btn[search].sizeY = 40;
		UI::btn[search].textCenter = false;

		// dialogVariable
		search = UI::addButton();
		UI::btn[search].nextMenu = MENU_ADDOBJECT;
		UI::btn[search].action = MENU_ACTION_CREATEVARIABLE;
		UI::btn[search].move(camera::resolutionX - 550, 250);
		UI::btn[search].text = L"Variable";
		UI::btn[search].sizeX = 200;	UI::btn[search].sizeY = 40;
		UI::btn[search].textCenter = false;

		// dialogCondition
		search = UI::addButton();
		UI::btn[search].nextMenu = MENU_ADDOBJECT;
		UI::btn[search].action = MENU_ACTION_CREATECONDITION;
		UI::btn[search].move(camera::resolutionX - 550, 300);
		UI::btn[search].text = L"Condition";
		UI::btn[search].sizeX = 200;	UI::btn[search].sizeY = 40;
		UI::btn[search].textCenter = false;

		// dialogImage
		search = UI::addButton();
		UI::btn[search].nextMenu = MENU_ADDOBJECT;
		UI::btn[search].action = MENU_ACTION_CREATEIMAGE;
		UI::btn[search].move(camera::resolutionX - 550, 350);
		UI::btn[search].text = L"Image";
		UI::btn[search].sizeX = 200;	UI::btn[search].sizeY = 40;
		UI::btn[search].textCenter = false;
		
		// dialogSound
		search = UI::addButton();
		UI::btn[search].nextMenu = MENU_ADDOBJECT;
		UI::btn[search].action = MENU_ACTION_CREATESOUND;
		UI::btn[search].move(camera::resolutionX - 550, 400);
		UI::btn[search].text = L"Sound";
		UI::btn[search].sizeX = 200;	UI::btn[search].sizeY = 40;
		UI::btn[search].textCenter = false;

		UI::menuLevel = MENU_ADDOBJECT;
		UI::lastMenuLevel = UI::menuLevel;
		UI::displayingMenu = 0;
	}
	else if (level == MENU_TOOLS)
	{
		UI::displayingMenu = MENU_TOOLS;
		UI::displayMenu(MENU_MAIN);

		// Back
		int search = UI::addButton();
		UI::btn[search].nextMenu = MENU_MAIN;
		UI::btn[search].move(camera::resolutionX - 350, 150);
		UI::btn[search].text = L"Tools";
		UI::btn[search].sizeX = 300;	UI::btn[search].sizeY = 40;
		UI::btn[search].textCenter = true;

		// Selection
		search = UI::addButton();
		UI::btn[search].nextMenu = MENU_TOOLS;
		UI::btn[search].action = MENU_ACTION_SELECTNOTHING;
		UI::btn[search].move(camera::resolutionX - 550, 150);
		UI::btn[search].text = L"Selection";
		UI::btn[search].sizeX = 200;	UI::btn[search].sizeY = 40;
		UI::btn[search].textCenter = false;

		// Linker
		search = UI::addButton();
		UI::btn[search].nextMenu = MENU_TOOLS;
		UI::btn[search].action = MENU_ACTION_SELECTLINKER;
		UI::btn[search].move(camera::resolutionX - 550, 200);
		UI::btn[search].text = L"Linker";
		UI::btn[search].sizeX = 200;	UI::btn[search].sizeY = 40;
		UI::btn[search].textCenter = false;

		// Text
		search = UI::addButton();
		UI::btn[search].nextMenu = MENU_TOOLS;
		UI::btn[search].action = MENU_ACTION_SELECTTEXT;
		UI::btn[search].move(camera::resolutionX - 550, 250);
		UI::btn[search].text = L"Text";
		UI::btn[search].sizeX = 200;	UI::btn[search].sizeY = 40;
		UI::btn[search].textCenter = false;

		// Marker: Entry Point
		search = UI::addButton();
		UI::btn[search].nextMenu = MENU_TOOLS;
		UI::btn[search].action = MENU_ACTION_SELECTENTRY;
		UI::btn[search].move(camera::resolutionX - 550, 325);
		UI::btn[search].text = L"Entry Point";
		UI::btn[search].sizeX = 200;	UI::btn[search].sizeY = 40;
		UI::btn[search].textCenter = false;

		// Marker: Success
		search = UI::addButton();
		UI::btn[search].nextMenu = MENU_TOOLS;
		UI::btn[search].action = MENU_ACTION_SELECTSUCCESS;
		UI::btn[search].move(camera::resolutionX - 550, 375);
		UI::btn[search].text = L"Success";
		UI::btn[search].sizeX = 200;	UI::btn[search].sizeY = 40;
		UI::btn[search].textCenter = false;

		// Marker: Failure
		search = UI::addButton();
		UI::btn[search].nextMenu = MENU_TOOLS;
		UI::btn[search].action = MENU_ACTION_SELECTFAILURE;
		UI::btn[search].move(camera::resolutionX - 550, 425);
		UI::btn[search].text = L"Failure";
		UI::btn[search].sizeX = 200;	UI::btn[search].sizeY = 40;
		UI::btn[search].textCenter = false;

		UI::menuLevel = MENU_TOOLS;
		UI::lastMenuLevel = UI::menuLevel;
		UI::displayingMenu = 0;
	}
	else if (level == MENU_OTHER)
	{
		UI::displayingMenu = MENU_OTHER;
		UI::displayMenu(MENU_MAIN);

		// Back
		int search = UI::addButton();
		UI::btn[search].nextMenu = MENU_MAIN;
		UI::btn[search].move(camera::resolutionX - 350, 200);
		UI::btn[search].text = L"Other";
		UI::btn[search].sizeX = 300;	UI::btn[search].sizeY = 40;
		UI::btn[search].textCenter = true;

		// Copy
		search = UI::addButton();
		UI::btn[search].nextMenu = MENU_OTHER;
		UI::btn[search].action = MENU_ACTION_COPYOBJECTS;
		UI::btn[search].move(camera::resolutionX - 550, 200);
		UI::btn[search].text = L"Copy";
		UI::btn[search].sizeX = 200;	UI::btn[search].sizeY = 40;
		UI::btn[search].textCenter = false;

		// Delete
		search = UI::addButton();
		UI::btn[search].nextMenu = MENU_OTHER;
		UI::btn[search].action = MENU_ACTION_DELETEOBJECTS;
		UI::btn[search].move(camera::resolutionX - 550, 250);
		UI::btn[search].text = L"Delete";
		UI::btn[search].sizeX = 200;	UI::btn[search].sizeY = 40;
		UI::btn[search].textCenter = false;

		// Test
		search = UI::addButton();
		UI::btn[search].nextMenu = MENU_OTHER;
		UI::btn[search].action = MENU_ACTION_QUICKTEST;
		UI::btn[search].move(camera::resolutionX - 550, 325);
		UI::btn[search].text = L"Quick test";
		UI::btn[search].sizeX = 200;	UI::btn[search].sizeY = 40;
		UI::btn[search].textCenter = false;

		// Redo
		search = UI::addButton();
		UI::btn[search].nextMenu = MENU_OTHER;
		UI::btn[search].action = MENU_ACTION_REDO;
		UI::btn[search].move(camera::resolutionX - 550, 400);
		UI::btn[search].text = L"Ctrl + Y";
		UI::btn[search].sizeX = 200;	UI::btn[search].sizeY = 40;
		UI::btn[search].textCenter = false;

		// Undo
		search = UI::addButton();
		UI::btn[search].nextMenu = MENU_OTHER;
		UI::btn[search].action = MENU_ACTION_UNDO;
		UI::btn[search].move(camera::resolutionX - 550, 450);
		UI::btn[search].text = L"Ctrl + Z";
		UI::btn[search].sizeX = 200;	UI::btn[search].sizeY = 40;
		UI::btn[search].textCenter = false;

		UI::menuLevel = MENU_OTHER;
		UI::lastMenuLevel = UI::menuLevel;
		UI::displayingMenu = 0;
	}
	else if (level == MENU_NOTHING)
	{
		UI::menuLevel = MENU_NOTHING;
		// Open menu
		search = UI::addButton();
		UI::btn[search].nextMenu = UI::lastMenuLevel;
		UI::btn[search].move(camera::resolutionX - 50, 0);
		UI::btn[search].text = L"";
		UI::btn[search].sizeX = 50;
		UI::btn[search].sizeY = camera::resolutionY;
		UI::btn[search].textCenter = true;
	}
}

void UI::buttonCallback(int id, sf::RenderWindow &winHandle)
{
	int tpChosen = 0;
	int tpsFound = 0;
	if (id == -1) { return; }
	UI::buttonCounter = 0;

	// Close the editor
	if (UI::btn[id].action == MENU_EXIT) { winHandle.close(); }
	// Remember level
	if (UI::btn[id].action == MENU_REMEMBER) { UI::lastMenuLevel = UI::menuLevel; }
	// Clear module
	else if (UI::btn[id].action == MENU_ACTION_CLEARMODULE) { UI::menuClearModule(); }
	// Load module
	else if (UI::btn[id].action == MENU_ACTION_LOADMODULE) { UI::menuLoadModule(); }
	// Save module
	else if (UI::btn[id].action == MENU_ACTION_SAVEMODULE) { UI::menuSaveModule(); }
	// Create object
	else if (UI::btn[id].action == MENU_ACTION_CREATEINFO) { UI::menuCreateDialog(DIALOGTYPE_INFO, winHandle); }
	else if (UI::btn[id].action == MENU_ACTION_CREATEACTION) { UI::menuCreateDialog(DIALOGTYPE_ACTION, winHandle); }
	else if (UI::btn[id].action == MENU_ACTION_CREATETELEPORT) { UI::menuCreateDialog(DIALOGTYPE_TELEPORT, winHandle); }
	else if (UI::btn[id].action == MENU_ACTION_CREATEVARIABLE) { UI::menuCreateDialog(DIALOGTYPE_VARIABLE, winHandle); }
	else if (UI::btn[id].action == MENU_ACTION_CREATECONDITION) { UI::menuCreateDialog(DIALOGTYPE_CONDITION, winHandle); }
	else if (UI::btn[id].action == MENU_ACTION_CREATEIMAGE) { UI::menuCreateDialog(DIALOGTYPE_IMAGE, winHandle); }
	else if (UI::btn[id].action == MENU_ACTION_CREATESOUND) { UI::menuCreateDialog(DIALOGTYPE_SOUND, winHandle); }
	// Select tool
	else if (UI::btn[id].action == MENU_ACTION_SELECTNOTHING) { mouse::selectTool = TOOL_NOTHING; }
	else if (UI::btn[id].action == MENU_ACTION_SELECTLINKER) { mouse::selectTool = TOOL_LINKER; }
	else if (UI::btn[id].action == MENU_ACTION_SELECTTEXT) { mouse::selectTool = TOOL_TEXT; }
	else if (UI::btn[id].action == MENU_ACTION_SELECTENTRY) { mouse::selectTool = TOOL_MARKER_ENTRY; }
	else if (UI::btn[id].action == MENU_ACTION_SELECTSUCCESS) { mouse::selectTool = TOOL_MARKER_SUCCESS; }
	else if (UI::btn[id].action == MENU_ACTION_SELECTFAILURE) { mouse::selectTool = TOOL_MARKER_FAILURE; }
	// Other
	else if (UI::btn[id].action == MENU_ACTION_COPYOBJECTS) { UI::copyObjects(winHandle); }
	else if (UI::btn[id].action == MENU_ACTION_DELETEOBJECTS) { UI::deleteObjects(); }
	else if (UI::btn[id].action == MENU_ACTION_QUICKTEST) { UI::quickTest(winHandle); }
	else if (UI::btn[id].action == MENU_ACTION_REDO) { myUndo::moveToNextBackup(); }
	else if (UI::btn[id].action == MENU_ACTION_UNDO)
	{
		if (!myUndo::undoChain) { myUndo::createBackupPoint(); myUndo::undoChain = true; myUndo::currentBackup -= 1; }
		myUndo::moveToPrevBackup();
	}

	// Displaying menus
	UI::displayMenu(UI::btn[id].nextMenu);
	// Checking button hoverover
	UI::buttonHoverover(winHandle);
}

void UI::buttonHoverover(sf::RenderWindow &winHandle)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(winHandle);
	// Clearing hoverovers
	for (int i = 0; i < UI::buttonCounter; i++) { UI::btn[i].hovered = false; }
	// Checking for new one
	int search = UI::findButtonInPoint(mousePos.x, mousePos.y);
	if (search != -1) { UI::btn[search].hovered = true; }
}

void UI::dialogHoverover(sf::RenderWindow &winHandle)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(winHandle);
	camera::applyTransformI(mousePos);
	// Clearing hoverovers
	for (int i = 0; i < gl_dialogInfoCounter; i++) { gl_dialogInfo[i].e_isHovered = false; }
	// Checking for new one
	for (int i = 0; i < gl_dialogInfoCounter; i++)
	{
		if (isPointInRegion(mousePos.x, mousePos.y, gl_dialogInfo[i].e_boxPosX, gl_dialogInfo[i].e_boxPosY, gl_dialogInfo[i].e_boxSizeX, gl_dialogInfo[i].e_boxSizeY))
		{
			gl_dialogInfo[i].e_isHovered = true;
		}
	}
}

void UI::menuClearModule()
{
	mouse::selectTool = TOOL_NOTHING;
	for (int i = 0; i < gl_dialogInfoCounter; i++)
	{
		gl_dialogInfo[i].hook_amount = 0;
	}
	gl_dialogInfoCounter = 0;
}

void UI::menuSaveModule(bool encode)
{
	std::wstring buf;
	if (!(mouse::selectTool == TOOL_TEXT && textTool::editField == EDITFIELD_GLOBAL && textTool::editTarget == EDITTARGET_SAVEPATH))
	{
		mouse::prevTool = mouse::selectTool;
		mouse::selectTool = TOOL_TEXT;
		textTool::editField = EDITFIELD_GLOBAL;
		textTool::editTarget = EDITTARGET_SAVEPATH;
		textTool::buffer = save::path;
		textTool::editCaretLine = -1;
		textTool::editCaretChar = textTool::buffer.length();
	}
	else
	{
		buf = L"Modules\\" + save::path;
		saveModule(buf, true, encode);
		mouse::selectTool = mouse::prevTool;
		textTool::editField = EDITFIELD_NOTHING;
		textTool::editTarget = EDITTARGET_NOTHING;
	}
}

void UI::menuLoadModule(bool decode)
{
	std::wstring buf;
	if (!(mouse::selectTool == TOOL_TEXT && textTool::editField == EDITFIELD_GLOBAL && textTool::editTarget == EDITTARGET_LOADPATH))
	{
		mouse::prevTool = mouse::selectTool;
		mouse::selectTool = TOOL_TEXT;
		textTool::editField = EDITFIELD_GLOBAL;
		textTool::editTarget = EDITTARGET_LOADPATH;
		textTool::buffer = save::path;
		textTool::editCaretLine = -1;
		textTool::editCaretChar = textTool::buffer.length();
	}
	else
	{
		buf = L"Modules\\" + save::path;
		loadModule(buf, decode);
		mouse::selectTool = mouse::prevTool;
		textTool::editField = EDITFIELD_NOTHING;
		textTool::editTarget = EDITTARGET_NOTHING;
	}
}

void UI::menuCreateDialog(int type, sf::RenderWindow &winHandle)
{
	// Checking overflow
	if (gl_dialogInfoCounter >= OBJECT_LIMIT - 1) { MessageBox(winHandle.getSystemHandle(), L"Object limit reached.", L"Error", MB_OK | MB_ICONERROR); return; }
	// Creating object
	myUndo::createBackupPoint();
	gl_dialogInfo[gl_dialogInfoCounter].init(gl_dialogInfoCounter, type);
	gl_dialogInfoCounter += 1;
}

void logic::replaceDecimal(std::wstring &str, std::wstring from, std::wstring to)
{
	int search;
	do
	{
		search = str.find(from);
		if (search != -1)
		{
			str.replace(search, 1, to);
		}
	}
	while (search != -1);
}

float logic::wtof(std::wstring &str)
{
	float pointResult = 0.00f, commaResult = 0.00f;
	std::wstring buf = str;
	logic::replaceDecimal(buf, L".", L",");
	std::wstringstream(buf) >> commaResult;
	logic::replaceDecimal(buf, L",", L".");
	std::wstringstream(buf) >> pointResult;

	if (pointResult != 0) { return pointResult; }
	else { return commaResult; }
}

void UI::copyObjects(sf::RenderWindow &winHandle)
{
	// Checking overflow
	if (gl_dialogInfoCounter + mouse::multiSelCounter>= OBJECT_LIMIT - 2) { MessageBox(winHandle.getSystemHandle(), L"Object limit reached.", L"Error", MB_OK | MB_ICONERROR); return; }
	// Creating objects
	myUndo::createBackupPoint();
	int copiedId = mouse::selectDialogInfoBox;
	// Creating a list of old selection objects
	int oldSel[SELECTION_LIMIT];
	int newSelOffset[SELECTION_LIMIT];
	for (int i = 0; i < mouse::multiSelCounter; i++)
	{
		oldSel[i] = mouse::multiSelDialog[i];
	}
	oldSel[mouse::multiSelCounter] = mouse::selectDialogInfoBox;
	// Copying the selection
	for (int i = -1; i < mouse::multiSelCounter; i++)
	{
		if (i > -1) { copiedId = mouse::multiSelDialog[i]; }
		// Init
		gl_dialogInfo[gl_dialogInfoCounter].init(gl_dialogInfoCounter, gl_dialogInfo[copiedId].type);
		// Copy
		gl_dialogInfo[gl_dialogInfoCounter] = gl_dialogInfo[copiedId];
		gl_dialogInfo[gl_dialogInfoCounter].e_boxPosX += 20;
		gl_dialogInfo[gl_dialogInfoCounter].e_boxPosY += 20;
		// Select
		if (i == -1)
		{
			mouse::selectDialogInfoBox = gl_dialogInfoCounter;
			mouse::multiSelDialog[mouse::multiSelCounter] = gl_dialogInfoCounter;
			newSelOffset[mouse::multiSelCounter] = gl_dialogInfoCounter - oldSel[mouse::multiSelCounter];
		}
		else { mouse::multiSelDialog[i] = gl_dialogInfoCounter; newSelOffset[i] = gl_dialogInfoCounter - oldSel[i]; }
		// Update data
		gl_dialogInfoCounter += 1;
	}
	// Updating the links
	for (int i = 0; i <= mouse::multiSelCounter; i++)
	{
		for (int y = 0; y < gl_dialogInfo[mouse::multiSelDialog[i]].hook_amount; y++)
		{
			bool linkFixed = false;
			// Checking if linked to another copied object
			for (int u = 0; u <= mouse::multiSelCounter; u++)
			{
				if (gl_dialogInfo[mouse::multiSelDialog[i]].hook_actionId[y] == oldSel[u])
				{
					linkFixed = true;
					gl_dialogInfo[mouse::multiSelDialog[i]].hook_actionId[y] += newSelOffset[u];
				}
			}
			// If not, remove the link
			if (!linkFixed)
			{
				for (int u = y; u < gl_dialogInfo[mouse::multiSelDialog[i]].hook_amount - 1; u++)
				{
					gl_dialogInfo[mouse::multiSelDialog[i]].hook_actionId[u] = gl_dialogInfo[mouse::multiSelDialog[i]].hook_actionId[u + 1];
					gl_dialogInfo[mouse::multiSelDialog[i]].e_hook_pointAposX[u] = gl_dialogInfo[mouse::multiSelDialog[i]].e_hook_pointAposX[u + 1];
					gl_dialogInfo[mouse::multiSelDialog[i]].e_hook_pointAposY[u] = gl_dialogInfo[mouse::multiSelDialog[i]].e_hook_pointAposY[u + 1];
					gl_dialogInfo[mouse::multiSelDialog[i]].e_hook_pointBposX[u] = gl_dialogInfo[mouse::multiSelDialog[i]].e_hook_pointBposX[u + 1];
					gl_dialogInfo[mouse::multiSelDialog[i]].e_hook_pointBposY[u] = gl_dialogInfo[mouse::multiSelDialog[i]].e_hook_pointBposY[u + 1];
				}
				gl_dialogInfo[mouse::multiSelDialog[i]].hook_amount -= 1;
				y -= 1;
			}
		}
	}
	mouse::multiSelDialog[mouse::multiSelCounter] = -1;
}

void UI::deleteObjects()
{
	myUndo::createBackupPoint();
	// Removing the link
	if (mouse::selectDialogInfoBox != -1 && mouse::selectDialogLink != -1)
	{
		// Moving other links
		for (int i = mouse::selectDialogLink; i < gl_dialogInfo[mouse::selectDialogInfoBox].hook_amount - 1; i++)
		{
			gl_dialogInfo[mouse::selectDialogInfoBox].hook_actionId[i] = gl_dialogInfo[mouse::selectDialogInfoBox].hook_actionId[i + 1];
			gl_dialogInfo[mouse::selectDialogInfoBox].e_hook_pointAposX[i] = gl_dialogInfo[mouse::selectDialogInfoBox].e_hook_pointAposX[i + 1];
			gl_dialogInfo[mouse::selectDialogInfoBox].e_hook_pointAposY[i] = gl_dialogInfo[mouse::selectDialogInfoBox].e_hook_pointAposY[i + 1];
			gl_dialogInfo[mouse::selectDialogInfoBox].e_hook_pointBposX[i] = gl_dialogInfo[mouse::selectDialogInfoBox].e_hook_pointBposX[i + 1];
			gl_dialogInfo[mouse::selectDialogInfoBox].e_hook_pointBposY[i] = gl_dialogInfo[mouse::selectDialogInfoBox].e_hook_pointBposY[i + 1];
		}
		gl_dialogInfo[mouse::selectDialogInfoBox].hook_amount -= 1;
		mouse::selectDialogLink = -1;
		mouse::selectDialogInfoBox = -1;
	}
	// Removing the dialogInfo box
	else if (mouse::selectDialogInfoBox != -1 && mouse::selectDialogLink == -1)
	{
		int deletedId = mouse::selectDialogInfoBox;
		for (int y = -1; y < mouse::multiSelCounter; y++)
		{
			if (y > -1) { deletedId = mouse::multiSelDialog[y]; }
			// Clearing marker values
			if (dialogInfo::entryPoint == deletedId) { dialogInfo::entryPoint = -1; }
			if (dialogInfo::bsodPoint == deletedId) { dialogInfo::bsodPoint = -1; }
			// Fixing marker values
			if (dialogInfo::entryPoint > deletedId) { dialogInfo::entryPoint -= 1; }
			else if (dialogInfo::bsodPoint == deletedId) { dialogInfo::bsodPoint = -1; }
			// Fixing the links
			for (int b = 0; b < gl_dialogInfoCounter; b++)
			{
				for (int a = 0; a < gl_dialogInfo[b].hook_amount; a++)
				{
					if (gl_dialogInfo[b].hook_actionId[a] > deletedId) { gl_dialogInfo[b].hook_actionId[a] -= 1; }
					else if (gl_dialogInfo[b].hook_actionId[a] == deletedId)
					{
						for (int i = a; i < gl_dialogInfo[b].hook_amount - 1; i++)
						{
							gl_dialogInfo[b].hook_actionId[i] = gl_dialogInfo[b].hook_actionId[i + 1];
							gl_dialogInfo[b].e_hook_pointAposX[i] = gl_dialogInfo[b].e_hook_pointAposX[i + 1];
							gl_dialogInfo[b].e_hook_pointAposY[i] = gl_dialogInfo[b].e_hook_pointAposY[i + 1];
							gl_dialogInfo[b].e_hook_pointBposX[i] = gl_dialogInfo[b].e_hook_pointBposX[i + 1];
							gl_dialogInfo[b].e_hook_pointBposY[i] = gl_dialogInfo[b].e_hook_pointBposY[i + 1];
						}
						gl_dialogInfo[b].hook_amount -= 1;
						a -= 1;
					}
				}
			}
			// Fixing the multi-selection
			for (int i = 0; i < mouse::multiSelCounter; i++)
			{
				if (mouse::multiSelDialog[i] > deletedId) { mouse::multiSelDialog[i] -= 1; }
			}
			// Moving the dialogInfo data values
			for (int i = deletedId; i < gl_dialogInfoCounter; i++)
			{
				gl_dialogInfo[i] = gl_dialogInfo[i + 1];
			}
			gl_dialogInfoCounter -= 1;
		}
		mouse::multiSelCounter = 0;
		mouse::selectDialogInfoBox = -1;
		dialogInfo::updateVisibility();
	}
}

void UI::quickTest(sf::RenderWindow &winHandle)
{
	ShowWindow(winHandle.getSystemHandle(), SW_MINIMIZE);
	saveModule(L"Modules\\" + save::path);
	ShellExecute(0, 0, L"client.exe", save::path.c_str(), 0, SW_SHOW);
}

void UI::pasteText(sf::RenderWindow &winHandle)
{
	if (OpenClipboard(winHandle.getSystemHandle()))
	{
		myUndo::createBackupPoint();

		std::wstring buffer;
		HANDLE hData = GetClipboardData(CF_UNICODETEXT);
		wchar_t* chBuffer = (wchar_t*)GlobalLock(hData);
		buffer = chBuffer;
		GlobalUnlock(hData);
		CloseClipboard();

		// Paste to global edit field
		if (textTool::editField == EDITFIELD_GLOBAL && (textTool::editTarget == EDITTARGET_SAVEPATH || textTool::editTarget == EDITTARGET_LOADPATH))
		{
			logic::replaceDecimal(buffer, L"\n", L"");
			textTool::buffer.insert(textTool::editCaretChar, buffer);
			textTool::editCaretChar += buffer.length();
			if (textTool::buffer.length() > 32) { textTool::buffer = textTool::buffer.substr(0, 32); }
			if (textTool::editCaretChar > textTool::buffer.length()) { textTool::editCaretChar = textTool::buffer.length(); }
			save::path = textTool::buffer;
		}
		// Paste to dialog box title
		else if (textTool::editField == EDITFIELD_TOP && textTool::editCaretLine == -1)
		{
			logic::replaceDecimal(buffer, L"\n", L"");
			textTool::buffer.insert(textTool::editCaretChar, buffer);
			textTool::editCaretChar += buffer.length();
			if (textTool::buffer.length() > 128) { textTool::buffer = textTool::buffer.substr(0, 128); }
			if (textTool::editCaretChar > textTool::buffer.length()) { textTool::editCaretChar = textTool::buffer.length(); }
			gl_dialogInfo[mouse::selectDialogInfoBox].e_boxTitle = textTool::buffer;
		}
		// Paste to dialog box description
		else if (textTool::editField == EDITFIELD_TOP && textTool::editCaretLine > -1)
		{
			int search = 0;
			//logic::replaceDecimal(buffer, L"\n", L"");
			while (search != -1)
			{
				search = buffer.find(L"\n");
				if (search != -1)
				{
					gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionText[textTool::editCaretLine].insert(textTool::editCaretChar, buffer.substr(0, search));
					gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionText[textTool::editCaretLine].erase(gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionText[textTool::editCaretLine].length() - 1);
					textTool::editCaretChar += search;
					buffer = buffer.substr(search + 1);
					textTool::buffer = gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionText[textTool::editCaretLine];
					if (buffer.length() > 1) { input::addNewDialogInfoLine(); }
				}
			}
			if (buffer.length() > 1)
			{
				gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionText[textTool::editCaretLine].insert(textTool::editCaretChar, buffer.substr(0, buffer.length()));
				textTool::editCaretChar += buffer.length();
			}
			textTool::buffer = gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionText[textTool::editCaretLine];
			//gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionText[textTool::editCaretLine] = textTool::buffer;
			//gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionText[textTool::editCaretLine] = textTool::buffer;
		}

		// Updating
		if (textTool::editField == EDITFIELD_TOP)
		{
			gl_dialogInfo[mouse::selectDialogInfoBox].e_adjustBoxToText();
			gl_dialogInfo[mouse::selectDialogInfoBox].e_updateDrawInfo();
		}
		// Forcing paint
		mainPaint(winHandle);
	}
}