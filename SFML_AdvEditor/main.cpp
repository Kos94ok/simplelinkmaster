
#include "main.h"

//mouse gl_mouse;
bool mouse::buttonClick = false;
int mouse::attachId = ATTACH_NOTHING;
int mouse::selectTool = TOOL_NOTHING;
int mouse::prevTool;
int mouse::attachDialogInfoBox;
int mouse::selectDialogInfoBox = -1;
int mouse::attachOffsetX;
int mouse::attachOffsetY;
int mouse::lastKnownPosX;
int mouse::lastKnownPosY;
int mouse::attachDialogLink;
int mouse::attachDialogLinkPoint;
int mouse::selectDialogLink = -1;
int mouse::multiSelCounter = 0;
int mouse::multiSelDialog[SELECTION_LIMIT];
int mouse::multiSelAttachOffsetX[SELECTION_LIMIT];
int mouse::multiSelAttachOffsetY[SELECTION_LIMIT];
bool linker::pointAfound = false;
int linker::pointAposX;
int linker::pointAposY;
int linker::linkType;
int linker::linkInfoId;
int textTool::editField;
int textTool::editCaretChar;
int textTool::editCaretLine;
std::wstring textTool::buffer;
int textTool::editTarget;
float textTool::editCaretTimer = 0.00f;
bool textTool::editCaretDisplay = true;
bool camera::fullscreen;
bool camera::borderless;
int camera::resolutionX;
int camera::resolutionY;
int camera::viewportOffsetX = 0;
int camera::viewportOffsetY = 0;
float camera::viewportZoom = 1.00f;
bool input::autoChangeLine;
int input::maxVisualOffset;
sf::View camera::view;
std::wstring save::path = L"unnamed.amf";
int undo::maxAmount;
int undo::currentSnapshot;
int dialogInfo::entryPoint = -1;
int dialogInfo::bsodPoint = -1;
int settings::maxUndoPoints;
bool settings::autoCreateDirectories;
sf::Vector3i settings::dialogInfoColor;
sf::Vector3i settings::dialogActionColor;
sf::Vector3i settings::dialogTeleportColor;
sf::Vector3i settings::dialogVariableColor;
sf::Vector3i settings::dialogConditionColor;
sf::Vector3i settings::dialogImageColor;
sf::Vector3i settings::dialogSoundColor;
sf::Vector3i settings::dialogInfoColorSel;
sf::Vector3i settings::dialogActionColorSel;
sf::Vector3i settings::dialogTeleportColorSel;
sf::Vector3i settings::dialogVariableColorSel;
sf::Vector3i settings::dialogConditionColorSel;
sf::Vector3i settings::dialogImageColorSel;
sf::Vector3i settings::dialogSoundColorSel;
button UI::btn[64];
int UI::buttonCounter = 0;
slider UI::sld[64];
int UI::sliderCounter = 0;
int UI::dialogActionCounter = 0;
int UI::menuLevel = MENU_NOTHING;
int UI::lastMenuLevel = MENU_MAIN;
int UI::displayingMenu = 0;
int myUndo::currentBackup = 0;
bool myUndo::undoChain;
bool myUndo::objectMoved;

sf::Font gl_mainFont;
int debugInt[8];
int gl_dialogInfoCounter = 0;
dialogInfo gl_dialogInfo[OBJECT_LIMIT];


//=================================================================================
//=================================================================================
// Entry point
//=================================================================================
//=================================================================================
int main()
{
	std::string title = "Simple Link Master v1.0 RC3";
	int globalTime = 0, elapsedTime = 0;
	std::locale::global(std::locale("Russian"));
	// Loading settings
	settings::load();
	// Overriding resolution settings
	if (camera::borderless) { camera::resolutionX = sf::VideoMode::getDesktopMode().width;	camera::resolutionY = sf::VideoMode::getDesktopMode().height; }
	// Opening window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow windowMain;
	if (camera::borderless) { windowMain.create(sf::VideoMode(camera::resolutionX, camera::resolutionY), title, 0, settings);}
	else if (camera::fullscreen) { windowMain.create(sf::VideoMode(camera::resolutionX, camera::resolutionY), title, sf::Style::Fullscreen, settings); }
	else { windowMain.create(sf::VideoMode(camera::resolutionX, camera::resolutionY), title, sf::Style::Titlebar | sf::Style::Close, settings); }
	// Icon
	sf::Image Icon;
	if (Icon.loadFromFile("Data//Textures//UI_icon_editor.png")) { windowMain.setIcon(64, 64, Icon.getPixelsPtr()); }
	// Loading fonts
	if (!gl_mainFont.loadFromFile("Data//Fonts//consola.ttf"))
	{
		gl_mainFont.loadFromFile("C:/Windows/Fonts/consola.ttf");
	}
	// Opening menu
	UI::displayMenu(UI::menuLevel);
	
	// Main loop
	while (windowMain.isOpen())
	{
		// Timers
		elapsedTime = GetTickCount() - globalTime;
		mainTimerChecking(elapsedTime);
		globalTime = GetTickCount();
		// Event handling
		mainEventCheck(windowMain);
		// Painting everythingg
		mainPaint(windowMain);
	}
	return 0;
}

//=================================================================================
//=================================================================================
// Timers
//=================================================================================
//=================================================================================
void mainTimerChecking(int elapsedTime)
{
	float timevar = (float)elapsedTime / 1000;
	if (timevar > 0.05) { return; }

	// Edit caret blink
	if (mouse::selectTool == TOOL_TEXT && textTool::editField != EDITFIELD_NOTHING)
	{
		textTool::editCaretTimer += timevar;
		if (textTool::editCaretTimer > 0.53f) { textTool::editCaretTimer = 0.00f;	textTool::editCaretDisplay = !textTool::editCaretDisplay; }
	}
}

//=================================================================================
//=================================================================================
// Event handling
//=================================================================================
//=================================================================================
void mainEventCheck(sf::RenderWindow &winHandle)
{
	sf::Event eventPoll;
	while (winHandle.pollEvent(eventPoll))
	{
		//=============================================================================
		//=============================================================================
		// Keyboard button events
		//=============================================================================
		//=============================================================================
		// Reset textTool
		if (eventPoll.type == sf::Event::KeyPressed && eventPoll.key.code >= sf::Keyboard::F1 && eventPoll.key.code <= sf::Keyboard::F4 && mouse::selectTool == TOOL_TEXT)
		{
			textTool::editField = EDITFIELD_NOTHING;
			textTool::editTarget = EDITTARGET_NOTHING;
		}
		// Select basic tool
		if (eventPoll.type == sf::Event::KeyPressed && !sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) && (eventPoll.key.code == sf::Keyboard::F1 ||
			(eventPoll.key.code == sf::Keyboard::Num1 && !(mouse::selectTool == TOOL_TEXT && textTool::editField != EDITFIELD_NOTHING))))
		{
			mouse::selectTool = TOOL_NOTHING;
		}
		// Select linker tool
		if (eventPoll.type == sf::Event::KeyPressed && !sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) && (eventPoll.key.code == sf::Keyboard::F2 ||
			(eventPoll.key.code == sf::Keyboard::Num2 && !(mouse::selectTool == TOOL_TEXT && textTool::editField != EDITFIELD_NOTHING))))
		{
			mouse::selectTool = TOOL_LINKER;
		}
		// Select text tool
		if (eventPoll.type == sf::Event::KeyPressed && !sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) && (eventPoll.key.code == sf::Keyboard::F3 ||
			(eventPoll.key.code == sf::Keyboard::Num3 && !(mouse::selectTool == TOOL_TEXT && textTool::editField != EDITFIELD_NOTHING))))
		{
			mouse::selectTool = TOOL_TEXT;
		}
		// Select marker tool
		if (eventPoll.type == sf::Event::KeyPressed && !sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) && (eventPoll.key.code == sf::Keyboard::F4 ||
			(eventPoll.key.code == sf::Keyboard::Num4 && !(mouse::selectTool == TOOL_TEXT && textTool::editField != EDITFIELD_NOTHING))))
		{
			if (mouse::selectTool == TOOL_MARKER_ENTRY) { mouse::selectTool = TOOL_MARKER_SUCCESS; }
			else if (mouse::selectTool == TOOL_MARKER_SUCCESS) { mouse::selectTool = TOOL_MARKER_FAILURE; }
			else if (mouse::selectTool == TOOL_MARKER_FAILURE) { mouse::selectTool = TOOL_MARKER_BSOD; }
			else if (mouse::selectTool == TOOL_MARKER_BSOD) { mouse::selectTool = TOOL_MARKER_ENTRY; }
			else { mouse::selectTool = TOOL_MARKER_ENTRY; }
		}

		// Window closed
		if (eventPoll.type == sf::Event::Closed)
		{
			myUndo::clearBackupPoints(0);
			exit(0);
		}

		// Creating new dialogInfo box
		if (eventPoll.type == sf::Event::KeyPressed && eventPoll.key.code == sf::Keyboard::Num1 && sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
		{
			UI::menuCreateDialog(DIALOGTYPE_INFO, winHandle);
		}
		// Creating new dialogAction box
		if (eventPoll.type == sf::Event::KeyPressed && eventPoll.key.code == sf::Keyboard::Num2 && sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
		{
			UI::menuCreateDialog(DIALOGTYPE_ACTION, winHandle);
		}
		// Creating new dialogTeleport box
		if (eventPoll.type == sf::Event::KeyPressed && eventPoll.key.code == sf::Keyboard::Num3 && sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
		{
			UI::menuCreateDialog(DIALOGTYPE_TELEPORT, winHandle);
		}
		// Creating new dialogVar box
		if (eventPoll.type == sf::Event::KeyPressed && eventPoll.key.code == sf::Keyboard::Num4 && sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
		{
			UI::menuCreateDialog(DIALOGTYPE_VARIABLE, winHandle);
		}
		// Creating new dialogCondition box
		if (eventPoll.type == sf::Event::KeyPressed && eventPoll.key.code == sf::Keyboard::Num5 && sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
		{
			UI::menuCreateDialog(DIALOGTYPE_CONDITION, winHandle);
		}
		// Creating new dialogImage box
		if (eventPoll.type == sf::Event::KeyPressed && eventPoll.key.code == sf::Keyboard::Num6 && sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
		{
			UI::menuCreateDialog(DIALOGTYPE_IMAGE, winHandle);
		}
		// Creating new dialogSound box
		if (eventPoll.type == sf::Event::KeyPressed && eventPoll.key.code == sf::Keyboard::Num7 && sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
		{
			UI::menuCreateDialog(DIALOGTYPE_SOUND, winHandle);
		}
		// CTRL + V (Paste selected text)
		if (eventPoll.type == sf::Event::KeyPressed && eventPoll.key.code == sf::Keyboard::V && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
			&& mouse::selectTool == TOOL_TEXT && (mouse::selectDialogInfoBox != -1 || textTool::editField == EDITFIELD_GLOBAL))
		{
			UI::pasteText(winHandle);
		}
		// CTRL + C (Copy the selected box)
		if (eventPoll.type == sf::Event::KeyPressed && eventPoll.key.code == sf::Keyboard::C && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
			&& mouse::selectTool == TOOL_NOTHING && mouse::selectDialogInfoBox != -1)
		{
			UI::copyObjects(winHandle);
		}
		// CTRL + S (Saving module)
		if (eventPoll.type == sf::Event::KeyPressed && eventPoll.key.code == sf::Keyboard::S && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
		{
			UI::menuSaveModule();
			textTool::editCaretTimer = 0.00f;	textTool::editCaretDisplay = true;
		}
		// CTRL + L (Loading module)
		if (eventPoll.type == sf::Event::KeyPressed && eventPoll.key.code == sf::Keyboard::L && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
		{
			UI::menuLoadModule();
			textTool::editCaretTimer = 0.00f;	textTool::editCaretDisplay = true;
		}
		// CTRL + Y (Redo action)
		if (eventPoll.type == sf::Event::KeyPressed && eventPoll.key.code == sf::Keyboard::Y && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
			&& !(mouse::selectTool == TOOL_TEXT && mouse::selectDialogInfoBox != -1) && !(mouse::selectTool == TOOL_LINKER && linker::pointAfound))
		{
			myUndo::moveToNextBackup();
		}
		// CTRL + Z (Undo action)
		if (eventPoll.type == sf::Event::KeyPressed && eventPoll.key.code == sf::Keyboard::Z && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
			&& !(mouse::selectTool == TOOL_TEXT && mouse::selectDialogInfoBox != -1) && !(mouse::selectTool == TOOL_LINKER && linker::pointAfound))
		{
			if (!myUndo::undoChain) { myUndo::createBackupPoint(); myUndo::undoChain = true; myUndo::currentBackup -= 1; }
			myUndo::moveToPrevBackup();
		}
		// Enter (Save the module)
		if (eventPoll.type == sf::Event::KeyPressed && eventPoll.key.code == sf::Keyboard::Return && mouse::selectTool == TOOL_TEXT && textTool::editField == EDITFIELD_GLOBAL
			&& textTool::editTarget == EDITTARGET_SAVEPATH)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) { UI::menuSaveModule(true); }
			else { UI::menuSaveModule(); }
		}
		// Enter (Load the module)
		if (eventPoll.type == sf::Event::KeyPressed && eventPoll.key.code == sf::Keyboard::Return && mouse::selectTool == TOOL_TEXT && textTool::editField == EDITFIELD_GLOBAL
			&& textTool::editTarget == EDITTARGET_LOADPATH)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) { UI::menuLoadModule(true); }
			else { UI::menuLoadModule(); }
		}
		// Module quick test
		if (eventPoll.type == sf::Event::KeyPressed && eventPoll.key.code == sf::Keyboard::F5)
		{
			UI::quickTest(winHandle);
		}
		//=============================================================================
		//=============================================================================
		// Menu events
		//=============================================================================
		//=============================================================================
		// Button click
		if (eventPoll.type == sf::Event::MouseButtonPressed && eventPoll.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(winHandle);
			int button = UI::findButtonInPoint(mousePos.x, mousePos.y);
			if (button != -1)
			{
				mouse::buttonClick = true;
				UI::buttonCallback(button, winHandle);
			}
		}
		// Mouse move
		if (eventPoll.type == sf::Event::MouseMoved)
		{
			UI::buttonHoverover(winHandle);
		}
		// Open menu
		if (eventPoll.type == sf::Event::KeyPressed && eventPoll.key.code == sf::Keyboard::Tab && !(mouse::selectTool == TOOL_TEXT && mouse::selectDialogInfoBox != -1))
		{
			UI::buttonCounter = 0;
			if (UI::menuLevel == UI::lastMenuLevel) { UI::displayMenu(MENU_NOTHING); }
			else { UI::displayMenu(UI::lastMenuLevel); }
		}

		//=============================================================================
		//=============================================================================
		// Marker events
		//=============================================================================
		//=============================================================================
		// Mouse click (Marking as an entry point)
		if (eventPoll.type == sf::Event::MouseButtonPressed && eventPoll.mouseButton.button == sf::Mouse::Left && mouse::selectTool == TOOL_MARKER_ENTRY)
		{
			myUndo::createBackupPoint();
			sf::Vector2i mousePos = sf::Mouse::getPosition(winHandle);
			camera::applyTransformI(mousePos);

			int search = dialogInfo::findDialogInfoBoxInPoint(mousePos.x, mousePos.y, DIALOGTYPE_INFO);
			if (search != -1)
			{
				if (dialogInfo::entryPoint == search)
				{
					dialogInfo::entryPoint = -1;
					if (gl_dialogInfo[search].e_boxTitle == L"Unnamed Module") { gl_dialogInfo[search].e_boxTitle = L"dialogInfo"; }
				}
				else
				{
					dialogInfo::entryPoint = search;
					if (gl_dialogInfo[search].e_boxTitle == L"dialogInfo") { gl_dialogInfo[search].e_boxTitle = L"Unnamed Module"; }
				}
				gl_dialogInfo[search].e_updateDrawInfo();
			}
		}
		// Mouse click (Marking as a success point)
		if (eventPoll.type == sf::Event::MouseButtonPressed && eventPoll.mouseButton.button == sf::Mouse::Left && mouse::selectTool == TOOL_MARKER_SUCCESS)
		{
			myUndo::createBackupPoint();
			sf::Vector2i mousePos = sf::Mouse::getPosition(winHandle);
			camera::applyTransformI(mousePos);

			int search = dialogInfo::findDialogInfoBoxInPoint(mousePos.x, mousePos.y, DIALOGTYPE_ACTION);
			if (search != -1) { gl_dialogInfo[search].type = DIALOGTYPE_SUCCESS; }
			else
			{
				search = dialogInfo::findDialogInfoBoxInPoint(mousePos.x, mousePos.y, DIALOGTYPE_SUCCESS);
				if (search != -1) { gl_dialogInfo[search].type = DIALOGTYPE_ACTION; }
			}
		}
		// Mouse click (Marking as a failure point)
		if (eventPoll.type == sf::Event::MouseButtonPressed && eventPoll.mouseButton.button == sf::Mouse::Left && mouse::selectTool == TOOL_MARKER_FAILURE)
		{
			myUndo::createBackupPoint();
			sf::Vector2i mousePos = sf::Mouse::getPosition(winHandle);
			camera::applyTransformI(mousePos);

			int search = dialogInfo::findDialogInfoBoxInPoint(mousePos.x, mousePos.y, DIALOGTYPE_ACTION);
			if (search != -1) { gl_dialogInfo[search].type = DIALOGTYPE_FAILURE; }
			else
			{
				search = dialogInfo::findDialogInfoBoxInPoint(mousePos.x, mousePos.y, DIALOGTYPE_FAILURE);
				if (search != -1) { gl_dialogInfo[search].type = DIALOGTYPE_ACTION; }
			}
		}
		// Mouse click (Marking as a bsod point)
		if (eventPoll.type == sf::Event::MouseButtonPressed && eventPoll.mouseButton.button == sf::Mouse::Left && mouse::selectTool == TOOL_MARKER_BSOD)
		{
			myUndo::createBackupPoint();
			sf::Vector2i mousePos = sf::Mouse::getPosition(winHandle);
			camera::applyTransformI(mousePos);

			int search = dialogInfo::findDialogInfoBoxInPoint(mousePos.x, mousePos.y, DIALOGTYPE_INFO);
			if (search != -1)
			{
				if (dialogInfo::bsodPoint == search) { dialogInfo::bsodPoint = -1; }
				else { dialogInfo::bsodPoint = search; }
			}
		}

		//=============================================================================
		//=============================================================================
		// Text tool events
		//=============================================================================
		//=============================================================================
		// Mouse click (Dropping selected object)
		if (eventPoll.type == sf::Event::MouseButtonPressed && eventPoll.mouseButton.button == sf::Mouse::Left
			&& mouse::attachId == ATTACH_NOTHING && mouse::selectTool == TOOL_TEXT && !mouse::buttonClick)
		{
			if (textTool::editField == EDITFIELD_GLOBAL) { mouse::selectTool = mouse::prevTool; }
			textTool::editField = EDITFIELD_NOTHING;
			mouse::selectDialogLink = -1;
			mouse::selectDialogInfoBox = -1;
			textTool::editTarget = EDITTARGET_NOTHING;
		}
		// Selecting box for editing
		if (eventPoll.type == sf::Event::MouseButtonPressed && eventPoll.mouseButton.button == sf::Mouse::Left && mouse::selectTool == TOOL_TEXT && textTool::editField != EDITFIELD_GLOBAL)
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(winHandle);
			camera::applyTransformI(mousePos);

			textTool::editField = 0;
			int search = dialogInfo::findDialogInfoBoxInPoint(mousePos.x, mousePos.y);
			if (search != -1)
			{
				textTool::editCaretTimer = 0.00f;
				textTool::editCaretDisplay = true;

				mouse::selectDialogInfoBox = search;
				textTool::editField = EDITFIELD_TOP;
				textTool::buffer = gl_dialogInfo[search].e_boxTitle;
				// Calculating the clicked line
				textTool::editCaretLine = a_math::round((float)(mousePos.y - gl_dialogInfo[search].e_boxPosY - 60) / 20);
				// Fixing
				if (mousePos.y - gl_dialogInfo[search].e_boxPosY > 30 && textTool::editCaretLine == -1) { textTool::editCaretLine = 0; }
				if (textTool::editCaretLine < -1) { textTool::editCaretLine = -1; textTool::buffer = gl_dialogInfo[search].e_boxTitle; }
				if (textTool::editCaretLine >= gl_dialogInfo[search].g_descriptionStringsUsed) { textTool::editCaretLine = gl_dialogInfo[search].g_descriptionStringsUsed - 1; }
				// Adding to buffer
				if (textTool::editCaretLine == -1) { textTool::buffer = gl_dialogInfo[search].e_boxTitle; }
				else { textTool::buffer = gl_dialogInfo[search].g_descriptionText[textTool::editCaretLine]; }
				// Calculating the clicked char
				int closestCharNum, closestCharDist, tempCharDist;
				std::wofstream file;
				// Title
				if (textTool::editCaretLine == -1)
				{
					closestCharNum = 0;
					for (int i = 0; i < gl_dialogInfo[search].e_boxTitle.length() + 1; i++)
					{
						tempCharDist = abs(mousePos.x - 10 - gl_dialogInfo[search].e_boxPosX - getVisualOffsetX(i, gl_dialogInfo[search].e_boxTitle, 24));
						if (i == 0 || tempCharDist < closestCharDist) { closestCharDist = tempCharDist;	closestCharNum = i; }
					}
					textTool::editCaretChar = closestCharNum;
				}
				// Description
				else
				{
					closestCharNum = 0;
					for (int i = 0; i < gl_dialogInfo[search].g_descriptionText[textTool::editCaretLine].length() + 1; i++)
					{
						tempCharDist = abs(mousePos.x - 10 - gl_dialogInfo[search].e_boxPosX - getVisualOffsetX(i, gl_dialogInfo[search].g_descriptionText[textTool::editCaretLine], 24));
						if (i == 0 || tempCharDist < closestCharDist) { closestCharDist = tempCharDist;	closestCharNum = i; }
					}
					textTool::editCaretChar = closestCharNum;
				}
			}
		}
		// Typing something to dialogInfo
		if (eventPoll.type == sf::Event::TextEntered && mouse::selectTool == TOOL_TEXT && textTool::editField != EDITFIELD_NOTHING
			&& !sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
		{
			myUndo::createBackupPoint();

			textTool::editCaretTimer = 0.00f;
			textTool::editCaretDisplay = true;

			if (textTool::editField == EDITFIELD_GLOBAL && (textTool::editTarget == EDITTARGET_SAVEPATH || textTool::editTarget == EDITTARGET_LOADPATH))
				{ textTool::buffer = save::path; }
			else if (textTool::editCaretLine == -1) { textTool::buffer = gl_dialogInfo[mouse::selectDialogInfoBox].e_boxTitle; }
			else { textTool::buffer = gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionText[textTool::editCaretLine]; }

			// Backspace - 8, Enter - 13, Escape - 27, Space - 32

			bool LineAutoChange = false;
			bool LineRemoveAvailable = true;
			// Adding characters
			if (eventPoll.text.unicode != 8 && eventPoll.text.unicode != 13 && eventPoll.text.unicode != 27)
			{
				if (input::autoChangeLine && mouse::selectDialogInfoBox != -1 && gl_dialogInfo[mouse::selectDialogInfoBox].type == DIALOGTYPE_INFO 
					&& eventPoll.text.unicode == 32 && getVisualOffsetX(textTool::buffer.length(), textTool::buffer, 24) >= input::maxVisualOffset)
				{
					LineAutoChange = true;
				}
				else
				{
					std::wstring shortbuf;		shortbuf += eventPoll.text.unicode;
					textTool::buffer.insert(textTool::editCaretChar, shortbuf);
					textTool::editCaretChar += 1;
				}
			}
			// Removing characters
			else if (eventPoll.text.unicode == 8 && textTool::editCaretChar > 0 && !sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				LineRemoveAvailable = false;
				textTool::buffer.erase(textTool::editCaretChar - 1, 1);
				textTool::editCaretChar -= 1;
			}
			// Removing the full line
			else if (eventPoll.text.unicode == 8 && textTool::editCaretChar > 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				LineRemoveAvailable = false;
				textTool::buffer.erase(0, textTool::editCaretChar);
				textTool::editCaretChar = 0;
			}
			// Removing the last line

			// Applying changes
			if (textTool::editField == EDITFIELD_GLOBAL && (textTool::editTarget == EDITTARGET_SAVEPATH || textTool::editTarget == EDITTARGET_LOADPATH))
			{
				save::path = textTool::buffer;
			}
			else if (textTool::editField == EDITFIELD_TOP && textTool::editCaretLine == -1)
			{
				gl_dialogInfo[mouse::selectDialogInfoBox].e_boxTitle = textTool::buffer;
			}
			else if (textTool::editField == EDITFIELD_TOP && textTool::editCaretLine > -1)
			{
				gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionText[textTool::editCaretLine] = textTool::buffer;
			}

			// Removing lines
			if (eventPoll.text.unicode == 8 && (textTool::editCaretLine > 0 || textTool::buffer.length() == 0) && LineRemoveAvailable)
			{
				std::wstring tempbuf = gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionText[textTool::editCaretLine];
				for (int i = textTool::editCaretLine; i < gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionStringsUsed - 1; i++)
				{
					gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionText[i] = gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionText[i + 1];
				}
				gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionStringsUsed -= 1;
				textTool::editCaretLine -= 1;
				// Adjust to strlen
				if (textTool::editCaretLine == -1) { textTool::editCaretChar = gl_dialogInfo[mouse::selectDialogInfoBox].e_boxTitle.length(); }
				else { textTool::editCaretChar = gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionText[textTool::editCaretLine].length(); }
				// Append removed string
				if (textTool::editCaretLine > -1) { gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionText[textTool::editCaretLine].append(tempbuf); }
				// Updating buffer
				if (textTool::editField == EDITFIELD_TOP)
				{
					if (textTool::editCaretLine > -1) { textTool::buffer = gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionText[textTool::editCaretLine]; }
					else { textTool::buffer = gl_dialogInfo[mouse::selectDialogInfoBox].e_boxTitle; }
				}
			}
			// Checking strlen overflow
			if (LineAutoChange)
			{
				//textTool::buffer.erase(textTool::editCaretChar, textTool::buffer.length());
				//input::addNewDialogInfoLine();
			}
			// Adjusting the box and updating draw info
			if (textTool::editField == EDITFIELD_TOP)
			{
				gl_dialogInfo[mouse::selectDialogInfoBox].e_adjustBoxToText();
				gl_dialogInfo[mouse::selectDialogInfoBox].e_updateDrawInfo();
			}
			// Forcing paint
			mainPaint(winHandle);
		}
		// Delete
		if (eventPoll.type == sf::Event::KeyPressed && eventPoll.key.code == sf::Keyboard::Delete && mouse::selectTool == TOOL_TEXT && textTool::editField != EDITFIELD_NOTHING)
		{
			textTool::editCaretTimer = 0.00f;
			textTool::editCaretDisplay = true;

			myUndo::createBackupPoint();
			// Copying the buffer
			if (textTool::editField == EDITFIELD_GLOBAL && (textTool::editTarget == EDITTARGET_SAVEPATH || textTool::editTarget == EDITTARGET_LOADPATH))
				{ textTool::buffer = save::path; }
			else if (textTool::editCaretLine == -1) { textTool::buffer = gl_dialogInfo[mouse::selectDialogInfoBox].e_boxTitle; }
			else { textTool::buffer = gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionText[textTool::editCaretLine]; }

			// Removing the char
			if (textTool::editCaretChar < textTool::buffer.length() && !sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				textTool::buffer.erase(textTool::editCaretChar, 1);
			}
			// Removing the line
			else if (textTool::editCaretChar < textTool::buffer.length() && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				textTool::buffer.erase(textTool::editCaretChar, textTool::buffer.length() - textTool::editCaretChar);
			}

			// Applying changes
			if (textTool::editField == EDITFIELD_GLOBAL && (textTool::editTarget == EDITTARGET_SAVEPATH || textTool::editTarget == EDITTARGET_LOADPATH))
			{
				save::path = textTool::buffer;
			}
			else if (textTool::editField == EDITFIELD_TOP && textTool::editCaretLine == -1)
			{
				gl_dialogInfo[mouse::selectDialogInfoBox].e_boxTitle = textTool::buffer;
				gl_dialogInfo[mouse::selectDialogInfoBox].e_adjustBoxToText();
				gl_dialogInfo[mouse::selectDialogInfoBox].e_updateDrawInfo();
			}
			else if (textTool::editField == EDITFIELD_TOP && textTool::editCaretLine > -1)
			{
				gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionText[textTool::editCaretLine] = textTool::buffer;
				gl_dialogInfo[mouse::selectDialogInfoBox].e_adjustBoxToText();
				gl_dialogInfo[mouse::selectDialogInfoBox].e_updateDrawInfo();
			}
			// Forcing paint
			mainPaint(winHandle);
		}
		// Arrow keys to move caret
		if (eventPoll.type == sf::Event::KeyPressed && eventPoll.key.code == sf::Keyboard::Left && mouse::selectTool == TOOL_TEXT && textTool::editField != EDITFIELD_NOTHING)
		{
			textTool::editCaretTimer = 0.00f;	textTool::editCaretDisplay = true;
			textTool::editCaretChar -= 1;
			if (textTool::editCaretChar < 0) { textTool::editCaretChar = 0; }
		}
		if (eventPoll.type == sf::Event::KeyPressed && eventPoll.key.code == sf::Keyboard::Right && mouse::selectTool == TOOL_TEXT && textTool::editField != EDITFIELD_NOTHING)
		{
			textTool::editCaretTimer = 0.00f;	textTool::editCaretDisplay = true;
			textTool::editCaretChar += 1;
			// Checking the length
			if (textTool::editCaretChar > textTool::buffer.length()) { textTool::editCaretChar = textTool::buffer.length(); }
		}
		if (eventPoll.type == sf::Event::KeyPressed && eventPoll.key.code == sf::Keyboard::Up && mouse::selectTool == TOOL_TEXT && textTool::editField == EDITFIELD_TOP)
		{
			textTool::editCaretTimer = 0.00f;	textTool::editCaretDisplay = true;
			textTool::editCaretLine -= 1;
			if (textTool::editCaretLine < -1) { textTool::editCaretLine = -1; }
			if (textTool::editField == EDITFIELD_TOP)
			{
				if (textTool::editCaretLine > -1) { textTool::buffer = gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionText[textTool::editCaretLine]; }
				else { textTool::buffer = gl_dialogInfo[mouse::selectDialogInfoBox].e_boxTitle; }
			}
			// Adjust to strlen
			if (textTool::editCaretChar > textTool::buffer.length()) { textTool::editCaretChar = textTool::buffer.length(); }
		}
		if (eventPoll.type == sf::Event::KeyPressed && eventPoll.key.code == sf::Keyboard::Down && mouse::selectTool == TOOL_TEXT && textTool::editField == EDITFIELD_TOP)
		{
			textTool::editCaretTimer = 0.00f;	textTool::editCaretDisplay = true;
			textTool::editCaretLine += 1;
			if (textTool::editField == EDITFIELD_TOP)
			{
				if (textTool::editCaretLine >= gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionStringsUsed)
				{
					textTool::editCaretLine = gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionStringsUsed - 1;
				}
				textTool::buffer = gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionText[textTool::editCaretLine];
			}
			// Adjust to strlen
			if (textTool::editCaretChar > textTool::buffer.length()) { textTool::editCaretChar = textTool::buffer.length(); }
		}
		// Enter
		if (eventPoll.type == sf::Event::KeyPressed && eventPoll.key.code == sf::Keyboard::Return && mouse::selectTool == TOOL_TEXT && textTool::editField == EDITFIELD_TOP)
		{
			input::addNewDialogInfoLine();
			textTool::editCaretTimer = 0.00f;	textTool::editCaretDisplay = true;
		}
		// Home
		if (eventPoll.type == sf::Event::KeyPressed && eventPoll.key.code == sf::Keyboard::Home && mouse::selectTool == TOOL_TEXT && textTool::editField != EDITFIELD_NOTHING)
		{
			textTool::editCaretChar = 0;
			textTool::editCaretTimer = 0.00f;	textTool::editCaretDisplay = true;
		}
		// End
		if (eventPoll.type == sf::Event::KeyPressed && eventPoll.key.code == sf::Keyboard::End && mouse::selectTool == TOOL_TEXT && textTool::editField != EDITFIELD_NOTHING)
		{
			textTool::editCaretChar = textTool::buffer.length();
			textTool::editCaretTimer = 0.00f;	textTool::editCaretDisplay = true;
		}
		// Page up
		if (eventPoll.type == sf::Event::KeyPressed && eventPoll.key.code == sf::Keyboard::PageUp && mouse::selectTool == TOOL_TEXT && textTool::editField == EDITFIELD_TOP)
		{
			textTool::editCaretTimer = 0.00f;	textTool::editCaretDisplay = true;
			textTool::editCaretLine = -1;
			if (textTool::editField == EDITFIELD_TOP)
			{
				textTool::buffer = gl_dialogInfo[mouse::selectDialogInfoBox].e_boxTitle;
			}
			// Adjust to strlen
			if (textTool::editCaretChar > textTool::buffer.length()) { textTool::editCaretChar = textTool::buffer.length(); }
		}
		// Page down
		if (eventPoll.type == sf::Event::KeyPressed && eventPoll.key.code == sf::Keyboard::PageDown && mouse::selectTool == TOOL_TEXT && textTool::editField == EDITFIELD_TOP)
		{
			textTool::editCaretTimer = 0.00f;	textTool::editCaretDisplay = true;
			textTool::editCaretLine = gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionStringsUsed - 1;
			if (textTool::editField == EDITFIELD_TOP)
			{
				textTool::buffer = gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionText[textTool::editCaretLine];
			}
			// Adjust to strlen
			if (textTool::editCaretChar > textTool::buffer.length()) { textTool::editCaretChar = textTool::buffer.length(); }
		}
		//=============================================================================
		//=============================================================================
		// Mouse click (Link point A)
		//=============================================================================
		//=============================================================================
		if (eventPoll.type == sf::Event::MouseButtonPressed && eventPoll.mouseButton.button == sf::Mouse::Left && mouse::selectTool == TOOL_LINKER && !linker::pointAfound)
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(winHandle);
			camera::applyTransformI(mousePos);
			// Link dialogInfo to something
			int search = dialogInfo::findDialogInfoBoxInPoint(mousePos.x, mousePos.y, DIALOGTYPE_INFO);
			if (search != -1)
			{
				linker::linkInfoId = search;
				linker::linkType = LINK_INFOTOANY;
				linker::pointAfound = true;
				linker::pointAposX = mousePos.x - gl_dialogInfo[search].e_boxPosX + 5;
				linker::pointAposY = mousePos.y - gl_dialogInfo[search].e_boxPosY + 5;
				linker::pointAposX = a_math::round((float)linker::pointAposX / 10) * 10 - 5;
				linker::pointAposY = a_math::round((float)linker::pointAposY / 10) * 10 - 5;
			}
			// Link dialogAction to something
			search = dialogInfo::findDialogInfoBoxInPoint(mousePos.x, mousePos.y, DIALOGTYPE_ACTION);
			if (search != -1)
			{
				linker::linkInfoId = search;
				linker::linkType = LINK_ACTIONTOANY;
				linker::pointAfound = true;
				linker::pointAposX = mousePos.x - gl_dialogInfo[search].e_boxPosX + 5;
				linker::pointAposY = mousePos.y - gl_dialogInfo[search].e_boxPosY + 5;
				linker::pointAposX = a_math::round((float)linker::pointAposX / 10) * 10 - 5;
				linker::pointAposY = a_math::round((float)linker::pointAposY / 10) * 10 - 5;
			}
			// Link dialogTeleport to something
			search = dialogInfo::findDialogInfoBoxInPoint(mousePos.x, mousePos.y, DIALOGTYPE_TELEPORT);
			if (search != -1)
			{
				linker::linkInfoId = search;
				linker::linkType = LINK_TELEPORTTOANY;
				linker::pointAfound = true;
				linker::pointAposX = mousePos.x - gl_dialogInfo[search].e_boxPosX + 5;
				linker::pointAposY = mousePos.y - gl_dialogInfo[search].e_boxPosY + 5;
				linker::pointAposX = a_math::round((float)linker::pointAposX / 10) * 10 - 5;
				linker::pointAposY = a_math::round((float)linker::pointAposY / 10) * 10 - 5;
			}
			// Link dialogCondition to something
			search = dialogInfo::findDialogInfoBoxInPoint(mousePos.x, mousePos.y, DIALOGTYPE_CONDITION);
			if (search != -1)
			{
				linker::linkInfoId = search;
				linker::linkType = LINK_CONDITIONTOANY;
				linker::pointAfound = true;
				linker::pointAposX = mousePos.x - gl_dialogInfo[search].e_boxPosX + 5;
				linker::pointAposY = mousePos.y - gl_dialogInfo[search].e_boxPosY + 5;
				linker::pointAposX = a_math::round((float)linker::pointAposX / 10) * 10 - 5;
				linker::pointAposY = a_math::round((float)linker::pointAposY / 10) * 10 - 5;
			}
		}
		// Mouse click (Confirm link)
		else if (eventPoll.type == sf::Event::MouseButtonPressed && eventPoll.mouseButton.button == sf::Mouse::Left && mouse::selectTool == TOOL_LINKER && linker::pointAfound)
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(winHandle);
			camera::applyTransformI(mousePos);
			int search;
			if (linker::linkType == LINK_INFOTOANY)
			{
				search = dialogInfo::findDialogInfoBoxInPoint(mousePos.x, mousePos.y, DIALOGTYPE_ANY);
				if (search != -1 && (gl_dialogInfo[search].type == DIALOGTYPE_INFO || gl_dialogInfo[search].type == DIALOGTYPE_ACTION
					|| gl_dialogInfo[search].type == DIALOGTYPE_SUCCESS || gl_dialogInfo[search].type == DIALOGTYPE_FAILURE
					|| gl_dialogInfo[search].type == DIALOGTYPE_CONDITION))
				{
					myUndo::createBackupPoint();
					mousePos.x += 5;	mousePos.y += 5;
					mousePos.x = a_math::round((float)mousePos.x / 10) * 10 - 5;
					mousePos.y = a_math::round((float)mousePos.y / 10) * 10 - 5;
					// Adding information about the link to dialogInfo object
					gl_dialogInfo[linker::linkInfoId].hook_actionId[gl_dialogInfo[linker::linkInfoId].hook_amount] = search;
					gl_dialogInfo[linker::linkInfoId].e_hook_pointAposX[gl_dialogInfo[linker::linkInfoId].hook_amount] = linker::pointAposX;
					gl_dialogInfo[linker::linkInfoId].e_hook_pointAposY[gl_dialogInfo[linker::linkInfoId].hook_amount] = linker::pointAposY;
					gl_dialogInfo[linker::linkInfoId].e_hook_pointBposX[gl_dialogInfo[linker::linkInfoId].hook_amount] = mousePos.x - gl_dialogInfo[search].e_boxPosX;
					gl_dialogInfo[linker::linkInfoId].e_hook_pointBposY[gl_dialogInfo[linker::linkInfoId].hook_amount] = mousePos.y - gl_dialogInfo[search].e_boxPosY;
					gl_dialogInfo[linker::linkInfoId].hook_amount += 1;
				}
			}
			else if (linker::linkType == LINK_ACTIONTOANY)
			{
				search = dialogInfo::findDialogInfoBoxInPoint(mousePos.x, mousePos.y, DIALOGTYPE_ANY);
				if (search != -1 && (gl_dialogInfo[search].type == DIALOGTYPE_INFO || gl_dialogInfo[search].type == DIALOGTYPE_TELEPORT || gl_dialogInfo[search].type == DIALOGTYPE_CONDITION
					|| gl_dialogInfo[search].type == DIALOGTYPE_IMAGE || gl_dialogInfo[search].type == DIALOGTYPE_SOUND))
				{
					myUndo::createBackupPoint();
					mousePos.x += 5;	mousePos.y += 5;
					mousePos.x = a_math::round((float)mousePos.x / 10) * 10 - 5;
					mousePos.y = a_math::round((float)mousePos.y / 10) * 10 - 5;
					// Adding information about the link to dialogInfo object
					gl_dialogInfo[linker::linkInfoId].hook_actionId[gl_dialogInfo[linker::linkInfoId].hook_amount] = search;
					gl_dialogInfo[linker::linkInfoId].e_hook_pointAposX[gl_dialogInfo[linker::linkInfoId].hook_amount] = linker::pointAposX;
					gl_dialogInfo[linker::linkInfoId].e_hook_pointAposY[gl_dialogInfo[linker::linkInfoId].hook_amount] = linker::pointAposY;
					gl_dialogInfo[linker::linkInfoId].e_hook_pointBposX[gl_dialogInfo[linker::linkInfoId].hook_amount] = mousePos.x - gl_dialogInfo[search].e_boxPosX;
					gl_dialogInfo[linker::linkInfoId].e_hook_pointBposY[gl_dialogInfo[linker::linkInfoId].hook_amount] = mousePos.y - gl_dialogInfo[search].e_boxPosY;
					gl_dialogInfo[linker::linkInfoId].hook_amount += 1;
				}
			}
			else if (linker::linkType == LINK_TELEPORTTOANY)
			{
				search = dialogInfo::findDialogInfoBoxInPoint(mousePos.x, mousePos.y, DIALOGTYPE_ANY);
				if (search != -1 && (gl_dialogInfo[search].type == DIALOGTYPE_INFO || gl_dialogInfo[search].type == DIALOGTYPE_IMAGE || gl_dialogInfo[search].type == DIALOGTYPE_SOUND))
				{
					myUndo::createBackupPoint();
					mousePos.x += 5;	mousePos.y += 5;
					mousePos.x = a_math::round((float)mousePos.x / 10) * 10 - 5;
					mousePos.y = a_math::round((float)mousePos.y / 10) * 10 - 5;
					// Adding information about the link to dialogInfo object
					gl_dialogInfo[linker::linkInfoId].hook_actionId[gl_dialogInfo[linker::linkInfoId].hook_amount] = search;
					gl_dialogInfo[linker::linkInfoId].e_hook_pointAposX[gl_dialogInfo[linker::linkInfoId].hook_amount] = linker::pointAposX;
					gl_dialogInfo[linker::linkInfoId].e_hook_pointAposY[gl_dialogInfo[linker::linkInfoId].hook_amount] = linker::pointAposY;
					gl_dialogInfo[linker::linkInfoId].e_hook_pointBposX[gl_dialogInfo[linker::linkInfoId].hook_amount] = mousePos.x - gl_dialogInfo[search].e_boxPosX;
					gl_dialogInfo[linker::linkInfoId].e_hook_pointBposY[gl_dialogInfo[linker::linkInfoId].hook_amount] = mousePos.y - gl_dialogInfo[search].e_boxPosY;
					gl_dialogInfo[linker::linkInfoId].hook_amount += 1;
				}
			}
			else if (linker::linkType == LINK_CONDITIONTOANY)
			{
				search = dialogInfo::findDialogInfoBoxInPoint(mousePos.x, mousePos.y, DIALOGTYPE_ANY);
				if (search != -1 && (gl_dialogInfo[search].type == DIALOGTYPE_INFO || gl_dialogInfo[search].type == DIALOGTYPE_ACTION))
				{
					myUndo::createBackupPoint();
					mousePos.x += 5;	mousePos.y += 5;
					mousePos.x = a_math::round((float)mousePos.x / 10) * 10 - 5;
					mousePos.y = a_math::round((float)mousePos.y / 10) * 10 - 5;
					// Adding information about the link to dialogInfo object
					gl_dialogInfo[linker::linkInfoId].hook_actionId[gl_dialogInfo[linker::linkInfoId].hook_amount] = search;
					gl_dialogInfo[linker::linkInfoId].e_hook_pointAposX[gl_dialogInfo[linker::linkInfoId].hook_amount] = linker::pointAposX;
					gl_dialogInfo[linker::linkInfoId].e_hook_pointAposY[gl_dialogInfo[linker::linkInfoId].hook_amount] = linker::pointAposY;
					gl_dialogInfo[linker::linkInfoId].e_hook_pointBposX[gl_dialogInfo[linker::linkInfoId].hook_amount] = mousePos.x - gl_dialogInfo[search].e_boxPosX;
					gl_dialogInfo[linker::linkInfoId].e_hook_pointBposY[gl_dialogInfo[linker::linkInfoId].hook_amount] = mousePos.y - gl_dialogInfo[search].e_boxPosY;
					gl_dialogInfo[linker::linkInfoId].hook_amount += 1;
				}
			}
			linker::pointAfound = false;
		}
		// Mouse click (Cancel link after point A)
		if (eventPoll.type == sf::Event::MouseButtonPressed && eventPoll.mouseButton.button == sf::Mouse::Right && mouse::selectTool == TOOL_LINKER && linker::pointAfound)
		{
			linker::pointAfound = false;
		}

		//=============================================================================
		//=============================================================================
		// Deleting stuff
		//=============================================================================
		//=============================================================================
		if (eventPoll.type == sf::Event::KeyPressed && eventPoll.key.code == sf::Keyboard::Delete && mouse::selectTool == TOOL_NOTHING)
		{
			UI::deleteObjects();
		}

		//=============================================================================
		//=============================================================================
		// Mouse click (Taking the dialogInfo boxes)
		//=============================================================================
		//=============================================================================
		if (eventPoll.type == sf::Event::MouseButtonPressed && eventPoll.mouseButton.button == sf::Mouse::Left && mouse::selectTool == TOOL_NOTHING && !mouse::buttonClick)
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(winHandle);
			camera::applyTransformI(mousePos);
			int clickedDialogBox = dialogInfo::findDialogInfoBoxInPoint(mousePos.x, mousePos.y);
			// Taking the dialogInfo box
			if (clickedDialogBox != -1)
			{
				bool ignoreSingleSel = false, resetMulti = true;
				// Multi-selection
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && mouse::selectDialogInfoBox != -1)
				{
					bool addToSel = true;
					// Checking if removing the last dialogbox
					if (mouse::selectDialogInfoBox == clickedDialogBox)
					{
						addToSel = false;
						if (mouse::multiSelCounter > 0)
						{
							mouse::selectDialogInfoBox = mouse::multiSelDialog[mouse::multiSelCounter - 1];
							mouse::multiSelCounter -= 1;
						}
						else { mouse::selectDialogInfoBox = -1; }
						ignoreSingleSel = true;
					}
					// Checking if already selected
					for (int i = 0; i < mouse::multiSelCounter; i++)
					{
						if (mouse::multiSelDialog[i] == clickedDialogBox)
						{
							addToSel = false;
							for (int y = i; y < mouse::multiSelCounter - 1; y++)
							{
								mouse::multiSelDialog[y] = mouse::multiSelDialog[y + 1];
							}
							mouse::multiSelCounter -= 1;
							ignoreSingleSel = true;
						}
					}
					// Adding
					if (addToSel) { mouse::multiSelDialog[mouse::multiSelCounter++] = mouse::selectDialogInfoBox; }
				}
				// Checking if multi-selected box is now target
				if (clickedDialogBox == mouse::selectDialogInfoBox) { resetMulti = false; }
				for (int i = 0; i < mouse::multiSelCounter; i++)
				{
					if (mouse::multiSelDialog[i] == clickedDialogBox) { resetMulti = false;	mouse::multiSelDialog[i] = mouse::selectDialogInfoBox; }
				}
				// Single selection
				mouse::attachId = ATTACH_DIALOGINFOBOX;
				if (!ignoreSingleSel)
				{
					myUndo::createBackupPoint();	myUndo::objectMoved = false;
					mouse::attachDialogInfoBox = clickedDialogBox;
					mouse::selectDialogInfoBox = clickedDialogBox;
					mouse::attachOffsetX = mousePos.x - gl_dialogInfo[clickedDialogBox].e_boxPosX;
					mouse::attachOffsetY = mousePos.y - gl_dialogInfo[clickedDialogBox].e_boxPosY;
					mouse::selectDialogLink = -1;
					if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && resetMulti) { mouse::multiSelCounter = 0; }
				}
			}
			// Taking the link
			for (int b = 0; b < gl_dialogInfoCounter; b++)
			{
				for (int a = 0; a < gl_dialogInfo[b].hook_amount; a++)
				{
					if (a_math::getDistance(mousePos.x, mousePos.y,
						gl_dialogInfo[b].e_boxPosX - 1 + gl_dialogInfo[b].e_hook_pointAposX[a],
						gl_dialogInfo[b].e_boxPosY - 1 + gl_dialogInfo[b].e_hook_pointAposY[a]) < 7)
					{
						mouse::attachId = ATTACH_DIALOGLINK;
						mouse::attachDialogInfoBox = b;
						mouse::attachDialogLink = a;
						mouse::attachDialogLinkPoint = ATTACH_POINT_A;
						mouse::selectDialogInfoBox = b;
						mouse::selectDialogLink = a;
					}
					if (a_math::getDistance(mousePos.x, mousePos.y,
						gl_dialogInfo[gl_dialogInfo[b].hook_actionId[a]].e_boxPosX - 1+ gl_dialogInfo[b].e_hook_pointBposX[a],
						gl_dialogInfo[gl_dialogInfo[b].hook_actionId[a]].e_boxPosY - 1+ gl_dialogInfo[b].e_hook_pointBposY[a]) < 7)
					{
						mouse::attachId = ATTACH_DIALOGLINK;
						mouse::attachDialogInfoBox = b;
						mouse::attachDialogLink = a;
						mouse::attachDialogLinkPoint = ATTACH_POINT_B;
						mouse::selectDialogInfoBox = b;
						mouse::selectDialogLink = a;
					}
				}
			}
		}

		// Mouse move (Moving the dialogInfo boxes)
		if (eventPoll.type == sf::Event::MouseMoved && mouse::attachId == ATTACH_DIALOGINFOBOX && !sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && !mouse::buttonClick)
		{
			myUndo::objectMoved = true;
			sf::Vector2i dialogOffset;
			sf::Vector2i mousePos = sf::Mouse::getPosition(winHandle);
			camera::applyTransformI(mousePos);
			// Saving start values
			dialogOffset.x = gl_dialogInfo[mouse::attachDialogInfoBox].e_boxPosX;
			dialogOffset.y = gl_dialogInfo[mouse::attachDialogInfoBox].e_boxPosY;
			// Moving the dialogInfo
			gl_dialogInfo[mouse::attachDialogInfoBox].e_boxPosX = mousePos.x - mouse::attachOffsetX;
			gl_dialogInfo[mouse::attachDialogInfoBox].e_boxPosY = mousePos.y - mouse::attachOffsetY;
			// Rounding up
			gl_dialogInfo[mouse::attachDialogInfoBox].e_roundBoxToGrid();
			// Calculating the offset
			dialogOffset.x -= gl_dialogInfo[mouse::attachDialogInfoBox].e_boxPosX;
			dialogOffset.y -= gl_dialogInfo[mouse::attachDialogInfoBox].e_boxPosY;
			// Moving the multi-selected
			for (int i = 0; i < mouse::multiSelCounter; i++)
			{
				gl_dialogInfo[mouse::multiSelDialog[i]].e_boxPosX -= dialogOffset.x;
				gl_dialogInfo[mouse::multiSelDialog[i]].e_boxPosY -= dialogOffset.y;
			}
		}
		// Mouse move (Moving the dialogInfo link)
		if (eventPoll.type == sf::Event::MouseMoved && mouse::attachId == ATTACH_DIALOGLINK && !mouse::buttonClick)
		{
			myUndo::objectMoved = true;
			sf::Vector2i mousePos = sf::Mouse::getPosition(winHandle);
			camera::applyTransformI(mousePos);
			if (mouse::attachDialogLinkPoint == ATTACH_POINT_A)
			{
				gl_dialogInfo[mouse::attachDialogInfoBox].e_hook_pointAposX[mouse::attachDialogLink] = mousePos.x - gl_dialogInfo[mouse::attachDialogInfoBox].e_boxPosX + 5;
				gl_dialogInfo[mouse::attachDialogInfoBox].e_hook_pointAposY[mouse::attachDialogLink] = mousePos.y - gl_dialogInfo[mouse::attachDialogInfoBox].e_boxPosY + 5;
				gl_dialogInfo[mouse::attachDialogInfoBox].e_hook_pointAposX[mouse::attachDialogLink] = a_math::round((float)gl_dialogInfo[mouse::attachDialogInfoBox].e_hook_pointAposX[mouse::attachDialogLink] / 10) * 10 - 5;
				gl_dialogInfo[mouse::attachDialogInfoBox].e_hook_pointAposY[mouse::attachDialogLink] = a_math::round((float)gl_dialogInfo[mouse::attachDialogInfoBox].e_hook_pointAposY[mouse::attachDialogLink] / 10) * 10 - 5;
			}
			else if (mouse::attachDialogLinkPoint == ATTACH_POINT_B)
			{
				gl_dialogInfo[mouse::attachDialogInfoBox].e_hook_pointBposX[mouse::attachDialogLink] = mousePos.x - gl_dialogInfo[gl_dialogInfo[mouse::attachDialogInfoBox].hook_actionId[mouse::attachDialogLink]].e_boxPosX + 5;
				gl_dialogInfo[mouse::attachDialogInfoBox].e_hook_pointBposY[mouse::attachDialogLink] = mousePos.y - gl_dialogInfo[gl_dialogInfo[mouse::attachDialogInfoBox].hook_actionId[mouse::attachDialogLink]].e_boxPosY + 5;
				gl_dialogInfo[mouse::attachDialogInfoBox].e_hook_pointBposX[mouse::attachDialogLink] = a_math::round((float)gl_dialogInfo[mouse::attachDialogInfoBox].e_hook_pointBposX[mouse::attachDialogLink] / 10) * 10 - 5;
				gl_dialogInfo[mouse::attachDialogInfoBox].e_hook_pointBposY[mouse::attachDialogLink] = a_math::round((float)gl_dialogInfo[mouse::attachDialogInfoBox].e_hook_pointBposY[mouse::attachDialogLink] / 10) * 10 - 5;
			}
		}

		// Mouse release (Dropping the dialogInfo boxes)
		if (eventPoll.type == sf::Event::MouseButtonReleased && eventPoll.mouseButton.button == sf::Mouse::Left && mouse::attachId == ATTACH_DIALOGINFOBOX)
		{
			gl_dialogInfo[mouse::attachDialogInfoBox].e_roundBoxToGrid();
			mouse::attachId = ATTACH_NOTHING;
			if (!myUndo::objectMoved || mouse::selectTool == TOOL_LINKER) { myUndo::currentBackup -= 1;		myUndo::clearBackupPoints(myUndo::currentBackup); }
		}
		// Mouse release (Dropping the dialogInfo link)
		if (eventPoll.type == sf::Event::MouseButtonReleased && eventPoll.mouseButton.button == sf::Mouse::Left && mouse::attachId == ATTACH_DIALOGLINK)
		{
			mouse::attachId = ATTACH_NOTHING;
		}
		// Any mouse release
		if (eventPoll.type == sf::Event::MouseButtonReleased && eventPoll.mouseButton.button == sf::Mouse::Left)
		{
			mouse::buttonClick = false;
		}
		// Mouse move (Moving the viewpoint)
		if (eventPoll.type == sf::Event::MouseMoved && mouse::attachId == ATTACH_NOTHING && sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouse::selectTool == TOOL_NOTHING
			&& !mouse::buttonClick)
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(winHandle);
			camera::viewportOffsetX += (mousePos.x - mouse::lastKnownPosX) / camera::viewportZoom;
			camera::viewportOffsetY += (mousePos.y - mouse::lastKnownPosY) / camera::viewportZoom;
			dialogInfo::updateVisibility();
		}
		// Mouse click (Dropping selected object)
		if (eventPoll.type == sf::Event::MouseButtonPressed && eventPoll.mouseButton.button == sf::Mouse::Left && mouse::selectDialogInfoBox != -1
			&& mouse::attachId == ATTACH_NOTHING && mouse::selectTool != TOOL_TEXT && !mouse::buttonClick)
		{
			mouse::selectDialogInfoBox = -1;
			mouse::multiSelCounter = 0;
		}
		// Mouse wheel (Viewport zoom)
		if (eventPoll.type == sf::Event::MouseWheelMoved && mouse::attachId == ATTACH_NOTHING)
		{
			camera::viewportZoom += eventPoll.mouseWheel.delta * 0.10f;
			if (camera::viewportZoom > 5.00f) { camera::viewportZoom = 5.00f; }
			else if (camera::viewportZoom < 0.10) { camera::viewportZoom = 0.10f; }
			dialogInfo::updateVisibility();
		}
		// Reset zoom
		if (eventPoll.type == sf::Event::MouseButtonPressed && eventPoll.mouseButton.button == sf::Mouse::Middle)
		{
			camera::viewportZoom = 1.00f;
			dialogInfo::updateVisibility();
		}
		// Dialog hoverover & Updating mouse position
		if (eventPoll.type == sf::Event::MouseMoved)
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(winHandle);
			mouse::lastKnownPosX = mousePos.x;
			mouse::lastKnownPosY = mousePos.y;

			UI::dialogHoverover(winHandle);
		}

		//=============================================================================
		//=============================================================================
		// Mouse click (Multi-selection box)
		//=============================================================================
		//=============================================================================
		// Starting the selection
		if (eventPoll.type == sf::Event::MouseButtonPressed && eventPoll.mouseButton.button == sf::Mouse::Right)
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(winHandle);

			mouse::selectDialogLink = -1;
			mouse::attachId = ATTACH_SELECTIONBOX;
			mouse::attachOffsetX = mousePos.x;
			mouse::attachOffsetY = mousePos.y;
		}
		// Checking the selection
		if (eventPoll.type == sf::Event::MouseMoved && mouse::attachId == ATTACH_SELECTIONBOX)
		{
			//mouse::attachId = ATTACH_NOTHING;
			if (mouse::selectTool == TOOL_NOTHING)
			{
				bool alreadySelected;

				sf::Vector2i mousePos = sf::Mouse::getPosition(winHandle);
				sf::Vector2i attachPos(mouse::attachOffsetX, mouse::attachOffsetY);
				camera::applyTransformI(mousePos);
				camera::applyTransformI(attachPos);

				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) { mouse::selectDialogInfoBox = -1;	mouse::multiSelCounter = 0; }
				for (int i = 0; i < gl_dialogInfoCounter; i++)
				{
					alreadySelected = false;
					if (gl_dialogInfo[i].isInRegion(attachPos.x, attachPos.y, mousePos.x, mousePos.y))
					{
						if (mouse::selectDialogInfoBox == -1) { mouse::selectDialogInfoBox = i; }
						else if (i != mouse::selectDialogInfoBox)
						{
							// Checking for selection
							for (int y = 0; y < mouse::multiSelCounter; y++)
							{
								if (mouse::multiSelDialog[y] == i)
								{
									alreadySelected = true;
									y = mouse::multiSelCounter;
								}
							}
							if (!alreadySelected) { mouse::multiSelDialog[mouse::multiSelCounter++] = i; }
						}
					}
				}
			}
		}
		// Stopping the selection
		if (eventPoll.type == sf::Event::MouseButtonReleased && eventPoll.mouseButton.button == sf::Mouse::Right && mouse::attachId == ATTACH_SELECTIONBOX)
		{
			mouse::attachId = ATTACH_NOTHING;
		}
	}
}

//=================================================================================
//=================================================================================
// Main paint
//=================================================================================
//=================================================================================
void mainPaint(sf::RenderWindow &winHandle)
{
	std::wstring buf;
	winHandle.clear(sf::Color(128, 128, 128));
	sf::Transform matrix = sf::Transform::Identity;
	matrix.translate(sf::Vector2f(camera::resolutionX / 2, camera::resolutionY / 2));
	matrix.scale(sf::Vector2f(camera::viewportZoom, camera::viewportZoom));
	matrix.translate(sf::Vector2f(-camera::resolutionX / 2, -camera::resolutionY / 2));
	matrix.translate(sf::Vector2f(camera::viewportOffsetX, camera::viewportOffsetY));

	bool dialogSkip[OBJECT_LIMIT];
	for (int i = 0; i < OBJECT_LIMIT; i++) { dialogSkip[i] = false; }

	// Creating brushes
	sf::Text brushText;
	sf::RectangleShape brushRect;
	sf::VertexArray brushQuad(sf::Quads, 4);
	sf::Vertex brushQuadVertex[4];
	sf::CircleShape brushCircle;
	// Brush setup
	brushText.setFont(gl_mainFont);

	// Displaying editor background
	paint::p_editorBackground(matrix, winHandle);

	// Marking multi-selection boxes
	for (int i = 0; i < mouse::multiSelCounter; i++) { dialogSkip[mouse::multiSelDialog[i]] = true; }

	// Drawing dialogInfo boxes
	for (int i = 0; i < gl_dialogInfoCounter; i++)
	{
		if (gl_dialogInfo[i].isValid && mouse::selectDialogInfoBox != i && !dialogSkip[i])
		{
			paint::p_dialogInfo(i, false, matrix, winHandle);
		}
	}

	// Selected dialogInfo box goes on top
	if (mouse::selectDialogInfoBox != -1 && gl_dialogInfo[mouse::selectDialogInfoBox].isValid)
	{
		paint::p_dialogInfo(mouse::selectDialogInfoBox, (mouse::selectDialogLink == -1), matrix, winHandle);
		for (int i = 0; i < mouse::multiSelCounter; i++)
		{
			paint::p_dialogInfo(mouse::multiSelDialog[i], (mouse::selectDialogLink == -1), matrix, winHandle);
		}
	}

	// Display all available dialogInfo links
	for (int i = 0; i < gl_dialogInfoCounter; i++)
	{
		if (gl_dialogInfo[i].isValid && gl_dialogInfo[i].hook_amount > 0)
		{
			paint::p_dialogInfoLinks(i, matrix, winHandle);
		}
	}

	// Draw linker temp line
	if (mouse::selectTool == TOOL_LINKER && linker::pointAfound)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(winHandle);
		camera::applyTransformI(mousePos);
		int lineWidth = 2;
		float angle = a_math::getAngle(
			linker::pointAposX + gl_dialogInfo[linker::linkInfoId].e_boxPosX,
			linker::pointAposY + gl_dialogInfo[linker::linkInfoId].e_boxPosY,
			mousePos.x, mousePos.y);
		float dist = a_math::getDistance(
			linker::pointAposX + gl_dialogInfo[linker::linkInfoId].e_boxPosX,
			linker::pointAposY + gl_dialogInfo[linker::linkInfoId].e_boxPosY,
			mousePos.x, mousePos.y);
		brushQuad.clear();
		brushQuadVertex[0].color = sf::Color(0, 0, 0);
		brushQuadVertex[0].position.x = a_math::polarX(linker::pointAposX, lineWidth, angle + 90) + gl_dialogInfo[linker::linkInfoId].e_boxPosX;
		brushQuadVertex[0].position.y = a_math::polarY(linker::pointAposY, lineWidth, angle + 90) + gl_dialogInfo[linker::linkInfoId].e_boxPosY;
		brushQuadVertex[1].color = sf::Color(0, 0, 0);
		brushQuadVertex[1].position.x = a_math::polarX(linker::pointAposX, lineWidth, angle - 90) + gl_dialogInfo[linker::linkInfoId].e_boxPosX;
		brushQuadVertex[1].position.y = a_math::polarY(linker::pointAposY, lineWidth, angle - 90) + gl_dialogInfo[linker::linkInfoId].e_boxPosY;
		brushQuadVertex[2].color = sf::Color(0, 0, 0);
		brushQuadVertex[2].position.x = a_math::polarX(brushQuadVertex[1].position.x, dist, angle);
		brushQuadVertex[2].position.y = a_math::polarY(brushQuadVertex[1].position.y, dist, angle);
		brushQuadVertex[3].color = sf::Color(0, 0, 0);
		brushQuadVertex[3].position.x = a_math::polarX(brushQuadVertex[0].position.x, dist, angle);
		brushQuadVertex[3].position.y = a_math::polarY(brushQuadVertex[0].position.y, dist, angle);
		brushQuad.append(brushQuadVertex[0]);
		brushQuad.append(brushQuadVertex[1]);
		brushQuad.append(brushQuadVertex[2]);
		brushQuad.append(brushQuadVertex[3]);

		winHandle.draw(brushQuad, matrix);

		int circleRad = 4;
		brushCircle.setOrigin(
			-linker::pointAposX + circleRad - gl_dialogInfo[linker::linkInfoId].e_boxPosX,
			-linker::pointAposY + circleRad - gl_dialogInfo[linker::linkInfoId].e_boxPosY);
		brushCircle.setRadius(circleRad);
		brushCircle.setOutlineThickness(2);
		brushCircle.setOutlineColor(sf::Color(0, 0, 0));
		brushCircle.setFillColor(sf::Color(0, 255, 0));
		winHandle.draw(brushCircle, matrix);

		brushCircle.setOrigin(-mousePos.x + circleRad, -mousePos.y + circleRad);
		int search = dialogInfo::findDialogInfoBoxInPoint(mousePos.x, mousePos.y, DIALOGTYPE_ANY);
		if (search != -1
			&& (linker::linkType == LINK_INFOTOANY && (gl_dialogInfo[search].type == DIALOGTYPE_INFO || gl_dialogInfo[search].type == DIALOGTYPE_ACTION || gl_dialogInfo[search].type == DIALOGTYPE_SUCCESS || gl_dialogInfo[search].type == DIALOGTYPE_FAILURE || gl_dialogInfo[search].type == DIALOGTYPE_CONDITION)
			|| (linker::linkType == LINK_ACTIONTOANY && (gl_dialogInfo[search].type == DIALOGTYPE_INFO || gl_dialogInfo[search].type == DIALOGTYPE_TELEPORT || gl_dialogInfo[search].type == DIALOGTYPE_CONDITION || gl_dialogInfo[search].type == DIALOGTYPE_IMAGE || gl_dialogInfo[search].type == DIALOGTYPE_SOUND))
			|| (linker::linkType == LINK_TELEPORTTOANY && (gl_dialogInfo[search].type == DIALOGTYPE_INFO || gl_dialogInfo[search].type == DIALOGTYPE_IMAGE || gl_dialogInfo[search].type == DIALOGTYPE_SOUND))
			|| (linker::linkType == LINK_CONDITIONTOANY && (gl_dialogInfo[search].type == DIALOGTYPE_INFO || gl_dialogInfo[search].type == DIALOGTYPE_ACTION)))
			)
		{
			brushCircle.setFillColor(sf::Color(255, 255, 0));
		}
		else { brushCircle.setFillColor(sf::Color(255, 0, 0)); }
		winHandle.draw(brushCircle, matrix);
	}

	// Draw GUI text
	brushText.setOrigin(0, 0);
	brushText.setPosition(5, 0);
	if (mouse::selectTool == TOOL_NOTHING) { brushText.setString("Tool: Selection"); }
	else if (mouse::selectTool == TOOL_LINKER) { brushText.setString("Tool: Linker"); }
	else if (mouse::selectTool == TOOL_TEXT && textTool::editField != EDITFIELD_GLOBAL) { brushText.setString("Tool: Text"); }
	else if (mouse::selectTool == TOOL_TEXT && textTool::editField == EDITFIELD_GLOBAL) { brushText.setString("Tool: Text [Global]"); }
	else if (mouse::selectTool == TOOL_MARKER_ENTRY) { brushText.setString("Tool: Marker [Entry Point]"); }
	else if (mouse::selectTool == TOOL_MARKER_SUCCESS) { brushText.setString("Tool: Marker [Success Point]"); }
	else if (mouse::selectTool == TOOL_MARKER_FAILURE) { brushText.setString("Tool: Marker [Failure Point]"); }
	else if (mouse::selectTool == TOOL_MARKER_BSOD) { brushText.setString("Tool: Marker [Grey Screen of Death]"); }
	brushText.setCharacterSize(24);
	brushText.setColor(sf::Color(0, 0, 0));
	winHandle.draw(brushText);

	// Global text field
	brushText.setPosition(5, 30);
	if (mouse::selectTool == TOOL_TEXT && textTool::editField == EDITFIELD_GLOBAL)
	{
		if (textTool::editTarget == EDITTARGET_SAVEPATH) { buf = L"Module save path: " + textTool::buffer; }
		else if (textTool::editTarget == EDITTARGET_LOADPATH) { buf = L"Module load path: " + textTool::buffer; }
		else { buf = L"Unknown: " + textTool::buffer; }
		brushText.setString(buf);
		winHandle.draw(brushText);
	}
	// Draw text edit caret
	if (mouse::selectTool == TOOL_TEXT && textTool::editField != EDITFIELD_NOTHING && textTool::editCaretDisplay)
	{
		if (textTool::editField == EDITFIELD_TOP)
		{
			if (textTool::editCaretLine == -1)
			{
				brushRect.setPosition(
					gl_dialogInfo[mouse::selectDialogInfoBox].e_boxPosX + 9 +
						getVisualOffsetX(textTool::editCaretChar, textTool::buffer, 24),
					gl_dialogInfo[mouse::selectDialogInfoBox].e_boxPosY + 10);
			}
			else
			{
				brushRect.setPosition(
					gl_dialogInfo[mouse::selectDialogInfoBox].e_boxPosX + 9 +
						getVisualOffsetX(textTool::editCaretChar, textTool::buffer, 24),
							gl_dialogInfo[mouse::selectDialogInfoBox].e_boxPosY + 7 + 20 * textTool::editCaretLine + 45);
			}
		}
		else if (textTool::editField == EDITFIELD_GLOBAL)
		{
			brushRect.setPosition(238 + getVisualOffsetX(textTool::editCaretChar, textTool::buffer, 24), 37);
		}
		brushRect.setSize(sf::Vector2f(2, 20));
		brushRect.setOutlineThickness(0);
		brushRect.setFillColor(sf::Color(0, 0, 0));
		if (textTool::editField != EDITFIELD_GLOBAL) { winHandle.draw(brushRect, matrix); }
		else { winHandle.draw(brushRect); }
	}
	// Selection box
	if (mouse::attachId == ATTACH_SELECTIONBOX)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(winHandle);

		brushRect.setFillColor(sf::Color(0, 255, 0));
		// Start -> Right
		brushRect.setPosition(mouse::attachOffsetX, mouse::attachOffsetY);
		brushRect.setSize(sf::Vector2f(mousePos.x - mouse::attachOffsetX, 1));
		winHandle.draw(brushRect);
		brushRect.setSize(sf::Vector2f(1, 1));
		winHandle.draw(brushRect);
		// Right -> Down
		brushRect.setPosition(mousePos.x, mouse::attachOffsetY);
		brushRect.setSize(sf::Vector2f(1, mousePos.y - mouse::attachOffsetY));
		winHandle.draw(brushRect);
		brushRect.setSize(sf::Vector2f(1, 1));
		winHandle.draw(brushRect);
		// Down -> Left
		brushRect.setPosition(mousePos.x, mousePos.y);
		brushRect.setSize(sf::Vector2f(mouse::attachOffsetX - mousePos.x, 1));
		winHandle.draw(brushRect);
		brushRect.setSize(sf::Vector2f(1, 1));
		winHandle.draw(brushRect);
		// Left -> Top
		brushRect.setPosition(mouse::attachOffsetX, mousePos.y);
		brushRect.setSize(sf::Vector2f(1, mouse::attachOffsetY - mousePos.y));
		winHandle.draw(brushRect);
		brushRect.setSize(sf::Vector2f(1, 1));
		winHandle.draw(brushRect);
	}
	// Menu overlay
	if (UI::menuLevel != MENU_NOTHING)
	{
		paint::p_menuOverlay(winHandle);
	}
	// Menu buttons
	for (int i = 0; i < UI::buttonCounter; i++)
	{
		paint::p_menuButton(i, winHandle);
	}
	// Menu sliders
	for (int i = 0; i < UI::sliderCounter; i++)
	{
		paint::p_menuSlider(i, winHandle);
	}
	// Main display
	winHandle.display();
}

