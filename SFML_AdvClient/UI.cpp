
#include "main.h"

void button::init()
{
	texID = TEX_EMPTY;
	posX = 0;
	posY = 0;
	sizeX = 350;
	sizeY = 60;

	timerValue = -1;
	action = MENU_NOTHING;
	nextMenu = MENU_NOTHING;
	opened = false;
	hidden = false;
	hovered = false;
	textCenter = false;
	gameButton = false;
	textOffsetX = 0;
	textOffsetY = 0;
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
		if (this == &UI::btn[i]) { UI::btn[i].action = MENU_NOTHING; myId = i; i = 64; }
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
	type = SLIDER_NOTHING;

	posX = 0;
	posY = 0;
	sizeX = 350;
	sizeY = 60;

	sliderValue = 50.00f;
	sliderMinValue = 0.00f;
	sliderMaxValue = 100.00f;
	sliderDivision = 1.00f;
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

int UI::addSlider()
{
	UI::sld[UI::sliderCounter].init();
	UI::sliderCounter += 1;

	return UI::sliderCounter - 1;
}

int UI::findSliderInPoint(int i_posX, int i_posY)
{
	for (int i = 0; i < UI::sliderCounter; i++)
	{
		if (i_posX > UI::sld[i].posX && i_posX < UI::sld[i].posX + UI::sld[i].sizeX
			&& i_posY > UI::sld[i].posY && i_posY < UI::sld[i].posY + UI::sld[i].sizeY)
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
	// Main menu (not loaded)
	if (level == MENU_MAIN && !game::isModuleLoaded)
	{
		UI::menuLevel = MENU_MAIN;
		// Main module
		search = UI::addButton();
		UI::btn[search].action = MENU_LOADTEMP;
		UI::btn[search].nextMenu = MENU_GAME;
		UI::btn[search].move(100, 150);
		UI::btn[search].text = L"Campaign";
		if (settings::lang == LANG_RUSSIAN) { UI::btn[search].text = L"Кампания"; }
		UI::btn[search].sizeX = 300;
		UI::btn[search].sizeY = 40;
		UI::btn[search].textCenter = true;
		// Other modules
		if (UI::displayingMenu != MENU_LOADMODULE)
		{
			search = UI::addButton();
			UI::btn[search].nextMenu = MENU_LOADMODULE;
			UI::btn[search].move(100, 200);
			UI::btn[search].text = L"Adventures";
			if (settings::lang == LANG_RUSSIAN) { UI::btn[search].text = L"Приключения"; }
			UI::btn[search].sizeX = 300;
			UI::btn[search].sizeY = 40;
			UI::btn[search].textCenter = true;
		}
		// Load save point
		if (UI::displayingMenu != MENU_LOADSAVEPOINT)
		{
			search = UI::addButton();
			UI::btn[search].nextMenu = MENU_LOADSAVEPOINT;
			UI::btn[search].move(100, 250);
			UI::btn[search].text = L"Saved games";
			if (settings::lang == LANG_RUSSIAN) { UI::btn[search].text = L"Сохраненные игры"; }
			UI::btn[search].sizeX = 300;
			UI::btn[search].sizeY = 40;
			UI::btn[search].textCenter = true;
		}
		// Settings
		if (UI::displayingMenu != MENU_SETTINGS)
		{
			search = UI::addButton();
			UI::btn[search].nextMenu = MENU_SETTINGS;
			UI::btn[search].move(100, 325);
			UI::btn[search].text = L"Settings";
			if (settings::lang == LANG_RUSSIAN) { UI::btn[search].text = L"Настройки"; }
			UI::btn[search].sizeX = 300;
			UI::btn[search].sizeY = 40;
			UI::btn[search].textCenter = true;
		}
		// Credits
		search = UI::addButton();
		UI::btn[search].action = MENU_CREDITS;
		UI::btn[search].nextMenu = MENU_GAME;
		UI::btn[search].move(100, 375);
		UI::btn[search].text = L"Credits";
		if (settings::lang == LANG_RUSSIAN) { UI::btn[search].text = L"Авторы"; }
		UI::btn[search].sizeX = 300;
		UI::btn[search].sizeY = 40;
		UI::btn[search].textCenter = true;
		// Exit game
		search = UI::addButton();
		UI::btn[search].action = MENU_EXIT;
		UI::btn[search].nextMenu = MENU_NOTHING;
		UI::btn[search].move(100, camera::resolutionY - 50);
		UI::btn[search].text = L"Quit";
		if (settings::lang == LANG_RUSSIAN) { UI::btn[search].text = L"Выход"; }
		UI::btn[search].sizeX = 300;
		UI::btn[search].sizeY = 40;
		UI::btn[search].textCenter = true;
	}
	// Module load menu
	else if (level == MENU_LOADMODULE) { UI::displayLoadModuleMenu(); }
	// Load save point menu
	else if (level == MENU_LOADSAVEPOINT) { UI::displayLoadSavePointMenu(false); }
	// Create save point menu
	else if (level == MENU_CREATESAVEPOINT) { UI::displayLoadSavePointMenu(true); }
	// Settings menu
	else if (level == MENU_SETTINGS) { UI::displaySettingsMenu(); }
	// Main menu (loaded)
	else if (level == MENU_MAIN && game::isModuleLoaded)
	{
		UI::menuLevel = MENU_MAIN;
		// Continue
		search = UI::addButton();
		UI::btn[search].action = MENU_CONTINUE;
		UI::btn[search].nextMenu = MENU_GAME;
		UI::btn[search].move(100, 150);
		UI::btn[search].text = L"Continue";
		if (settings::lang == LANG_RUSSIAN) { UI::btn[search].text = L"Продолжить"; }
		UI::btn[search].sizeX = 300;
		UI::btn[search].sizeY = 40;
		UI::btn[search].textCenter = true;
		// Save module
		if (UI::displayingMenu != MENU_CREATESAVEPOINT)
		{
			search = UI::addButton();
			UI::btn[search].nextMenu = MENU_CREATESAVEPOINT;
			UI::btn[search].move(100, 225);
			UI::btn[search].text = L"Save game";
			if (settings::lang == LANG_RUSSIAN) { UI::btn[search].text = L"Сохранить игру"; }
			UI::btn[search].sizeX = 300;
			UI::btn[search].sizeY = 40;
			UI::btn[search].textCenter = true;
		}
		// Save load
		if (UI::displayingMenu != MENU_LOADSAVEPOINT)
		{
			search = UI::addButton();
			UI::btn[search].nextMenu = MENU_LOADSAVEPOINT;
			UI::btn[search].move(100, 275);
			UI::btn[search].text = L"Load game";
			if (settings::lang == LANG_RUSSIAN) { UI::btn[search].text = L"Загрузить игру"; }
			UI::btn[search].sizeX = 300;
			UI::btn[search].sizeY = 40;
			UI::btn[search].textCenter = true;
		}
		// Settings
		if (UI::displayingMenu != MENU_SETTINGS)
		{
			search = UI::addButton();
			UI::btn[search].action = MENU_SETTINGS;
			UI::btn[search].nextMenu = MENU_SETTINGS;
			UI::btn[search].move(100, 350);
			UI::btn[search].text = L"Settings";
			if (settings::lang == LANG_RUSSIAN) { UI::btn[search].text = L"Настройки"; }
			UI::btn[search].sizeX = 300;
			UI::btn[search].sizeY = 40;
			UI::btn[search].textCenter = true;
		}
		// Stop module
		search = UI::addButton();
		UI::btn[search].action = MENU_CLEARMODULE;
		UI::btn[search].nextMenu = MENU_MAIN;
		UI::btn[search].move(100, camera::resolutionY - 100);
		UI::btn[search].text = L"Back to main menu";
		if (settings::lang == LANG_RUSSIAN) { UI::btn[search].text = L"В главное меню"; }
		UI::btn[search].sizeX = 300;
		UI::btn[search].sizeY = 40;
		UI::btn[search].textCenter = true;
		// Exit game
		search = UI::addButton();
		UI::btn[search].action = MENU_EXIT;
		UI::btn[search].nextMenu = MENU_NOTHING;
		UI::btn[search].move(100, camera::resolutionY - 50);
		UI::btn[search].text = L"Quit";
		if (settings::lang == LANG_RUSSIAN) { UI::btn[search].text = L"Выход"; }
		UI::btn[search].sizeX = 300;
		UI::btn[search].sizeY = 40;
		UI::btn[search].textCenter = true;
	}
	// In-game menu
	else if (level == MENU_GAME) { UI::displayGameMenu(); }

	UI::displayingMenu = 0;
}

void UI::buttonCallback(int id, sf::RenderWindow &winHandle)
{
	std::wstring buf;
	int tpChosen = 0;
	int tpsFound = 0;
	int action = UI::btn[id].action;
	int tpId[32];
	if (id == -1) { return; }
	int oldMenu = -1;
	UI::sliderCounter = 0;
	bool triggerTimers = false;

	if (game::isModuleLoaded && UI::btn[id].action != MENU_CLEARMODULE && UI::btn[id].action != MENU_NEXTDIALOGINFO) { UI::clearButtons(false); }
	else { UI::clearButtons(true); }

	// Start campaign
	if (UI::btn[id].action == MENU_LOADTEMP) { game::loadModuleFull(L"main.amf"); triggerTimers = true; }
	// Credits
	if (UI::btn[id].action == MENU_CREDITS) { game::loadModuleFull(L"credits.amf", true); triggerTimers = true; game::creditsMode = true; }
	// Start adventure
	else if (UI::btn[id].action == MENU_LOADMODULESTART) { game::loadModuleFull(UI::btn[id].extraData); triggerTimers = true; }
	// Save game
	else if (UI::btn[id].action >= MENU_CREATESAVEPOINT0 && UI::btn[id].action <= MENU_CREATESAVEPOINT0 + 10) { game::createSavePoint(UI::btn[id].action - MENU_CREATESAVEPOINT0); }
	// Load game
	else if (UI::btn[id].action >= MENU_LOADSAVEPOINT0 && UI::btn[id].action <= MENU_LOADSAVEPOINT0 + 10) { game::loadSavePoint(UI::btn[id].action - MENU_LOADSAVEPOINT0); }
	// Exit
	else if (UI::btn[id].action == MENU_EXIT) { winHandle.close(); }
	// Clear module
	else if (UI::btn[id].action == MENU_CLEARMODULE)
	{
		clearModule();
		game::fullClearUp();
		printf("[UI::buttonCallback] Module cleared!\n");

		game::loadModuleFull(L"menu.amf");
		game::isModuleLoaded = false;
		logic::activateMenuData();
	}
	// Next dialogInfo
	else if (UI::btn[id].action == MENU_NEXTDIALOGINFO)
	{
		triggerTimers = true;
		//if (UI::menuLevel != MENU_GAME) { oldMenu = UI::menuLevel; }
		// Stopping the VO
		game::voiceOverFadeTime = 500;
		game::voiceOverMaxVolume = 0.00f;
		// Going to BSOD
		if (dialogInfo::bsodPoint != -1 && gl_dialogInfo[UI::btn[id].g_corDialogAction].hook_amount == 0) { game::currentDialogInfo = dialogInfo::bsodPoint; }
		// Parsing actions
		if (gl_dialogInfo[UI::btn[id].g_corDialogAction].g_descriptionStringsUsed > 1)
		{
			logic::parseActions(UI::btn[id].g_corDialogAction);
		}
		// Pre-checking links
		for (int i = 0; i < UI::btn[id].g_nextDialogInfoCounter; i++)
		{
			// dialogImage
			if (gl_dialogInfo[UI::btn[id].g_nextDialogInfo[i]].type == DIALOGTYPE_IMAGE) { game::execDialogImage(UI::btn[id].g_nextDialogInfo[i]); }
			// dialogSound
			if (gl_dialogInfo[UI::btn[id].g_nextDialogInfo[i]].type == DIALOGTYPE_SOUND) { game::execDialogSound(UI::btn[id].g_nextDialogInfo[i]); }
		}
		// Checking links
		for (int i = 0; i < UI::btn[id].g_nextDialogInfoCounter; i++)
		{
			bool infoFound = false;
			// Normal link
			if (!infoFound && gl_dialogInfo[UI::btn[id].g_nextDialogInfo[i]].type == DIALOGTYPE_INFO)
			{
				game::currentDialogInfo = UI::btn[id].g_nextDialogInfo[i];
				infoFound = true;
				if (UI::custom_fancyPrintAllowed) { UI::printDelayActive = UI::custom_fancyPrintDelay;	UI::printDelayAmount = 0; }
			}
			// Condition link
			else if (gl_dialogInfo[UI::btn[id].g_nextDialogInfo[i]].type == DIALOGTYPE_CONDITION)
			{
				int nextDlg = UI::btn[id].g_nextDialogInfo[i];
				// No condition
				if (gl_dialogInfo[nextDlg].g_descriptionStringsUsed == 0)
				{
					printf("[UI::buttonCallback]: Empty condition. Skipping.\n");
					game::currentDialogInfo = gl_dialogInfo[nextDlg].hook_actionId[0];
				}
				// Single-line condition
				else if (gl_dialogInfo[nextDlg].g_descriptionStringsUsed == 1)
				{
					bool result = logic::checkCondition(gl_dialogInfo[nextDlg].g_descriptionText[0]);
	
					if (result) { game::currentDialogInfo = gl_dialogInfo[nextDlg].hook_actionId[0]; i = UI::btn[id].g_nextDialogInfoCounter; }
					else if (gl_dialogInfo[nextDlg].hook_actionId[1] != -1) { game::currentDialogInfo = gl_dialogInfo[nextDlg].hook_actionId[1]; i = UI::btn[id].g_nextDialogInfoCounter; }
					if (UI::custom_fancyPrintAllowed) { UI::printDelayActive = UI::custom_fancyPrintDelay;	UI::printDelayAmount = 0; }
				}
				// Multi-line condition
				else if (gl_dialogInfo[nextDlg].g_descriptionStringsUsed > 1)
				{
					bool finalResult = logic::checkMultiCondition(nextDlg);
				
					// Selecting the right way
					if (finalResult) { game::currentDialogInfo = gl_dialogInfo[nextDlg].hook_actionId[0]; i = UI::btn[id].g_nextDialogInfoCounter; }
					else if (gl_dialogInfo[nextDlg].hook_actionId[1] != -1) { game::currentDialogInfo = gl_dialogInfo[nextDlg].hook_actionId[1]; i = UI::btn[id].g_nextDialogInfoCounter; }
					if (UI::custom_fancyPrintAllowed) { UI::printDelayActive = UI::custom_fancyPrintDelay;	UI::printDelayAmount = 0; }
				}
			}
			// Teleport link
			else if (gl_dialogInfo[UI::btn[id].g_nextDialogInfo[i]].type == DIALOGTYPE_TELEPORT)
			{
				for (int y = 0; y < gl_dialogInfo[UI::btn[id].g_nextDialogInfo[i]].g_descriptionStringsUsed; y++)
				{
					for (int x = 0; x < gl_dialogInfoCounter; x++)
					{
						if (gl_dialogInfo[x].e_boxTitle == gl_dialogInfo[UI::btn[id].g_nextDialogInfo[i]].g_descriptionText[y])
						{
							tpId[tpsFound++] = x;
						}
					}
				}
				if (gl_dialogInfo[UI::btn[id].g_nextDialogInfo[i]].g_descriptionStringsUsed == 0 || tpsFound == 0) { printf("[UI::buttonCallback]: Target portal not connected!\n"); }
				// Checking each tp
				int outTPcount = 0;
				int outTP[16];
				for (int y = 0; y < tpsFound; y++)
				{
					for (int u = 0; u < gl_dialogInfo[tpId[y]].hook_amount; u++)
					{
						if (gl_dialogInfo[gl_dialogInfo[tpId[y]].hook_actionId[u]].type == DIALOGTYPE_IMAGE) { game::execDialogImage(gl_dialogInfo[tpId[y]].hook_actionId[u]); }
						else if (gl_dialogInfo[gl_dialogInfo[tpId[y]].hook_actionId[u]].type == DIALOGTYPE_SOUND) { game::execDialogSound(gl_dialogInfo[tpId[y]].hook_actionId[u]); }
						else if (gl_dialogInfo[gl_dialogInfo[tpId[y]].hook_actionId[u]].type == DIALOGTYPE_INFO) { outTP[outTPcount++] = gl_dialogInfo[tpId[y]].hook_actionId[u]; }
					}
				}
				// Going out
				if (!infoFound && outTPcount > 0)
				{
					game::currentDialogInfo = outTP[a_math::rand(0, outTPcount - 1)];
					i = UI::btn[id].g_nextDialogInfoCounter;
					if (UI::custom_fancyPrintAllowed) { UI::printDelayActive = UI::custom_fancyPrintDelay;	UI::printDelayAmount = 0; }
				}
			}
		}
	}

	UI::displayingMenu = 0;
	// Displaying menus
	if (UI::btn[id].nextMenu != MENU_NOTHING) { UI::displayMenu(UI::btn[id].nextMenu); }
	// Returning the main menu on top
	if (oldMenu != -1) { UI::displayMenu(oldMenu); }
	// Looking for timer actions
	if (triggerTimers) { logic::activateTimers(); }
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

sf::Text visualOffsetText;
int getVisualOffsetX(int number, std::wstring target, int charsize, bool bold, bool underlined, bool italic)
{
	visualOffsetText.setFont(gl_mainFont);
	visualOffsetText.setString(target);
	visualOffsetText.setCharacterSize(charsize);
	if (!bold && !underlined && !italic) { visualOffsetText.setStyle(sf::Text::Regular); }
	else if (bold && !underlined && !italic) { visualOffsetText.setStyle(sf::Text::Bold); }
	else if (!bold && underlined && !italic) { visualOffsetText.setStyle(sf::Text::Underlined); }
	else if (!bold && !underlined && italic) { visualOffsetText.setStyle(sf::Text::Italic); }
	else if (bold && underlined && !italic) { visualOffsetText.setStyle(sf::Text::Bold | sf::Text::Underlined); }
	else if (bold && !underlined && italic) { visualOffsetText.setStyle(sf::Text::Bold | sf::Text::Italic); }
	else if (!bold && underlined && italic) { visualOffsetText.setStyle(sf::Text::Underlined | sf::Text::Italic); }
	else { visualOffsetText.setStyle(sf::Text::Bold | sf::Text::Underlined | sf::Text::Italic); }
	
	//if (number >= target.length()) { return -1; }
	return visualOffsetText.findCharacterPos(number).x;
}

void UI::displayGameMenu()
{
	int info, search;
	UI::dialogActionCounter = 0;
	UI::menuLevel = MENU_GAME;
	// Creating game buttons
	if (game::currentDialogInfo != -1)
	{
		int buttonsFound = 0, buttonsTotal = 0;
		// Looking for total button count
		for (int i = 0; i < gl_dialogInfo[game::currentDialogInfo].hook_amount; i++)
		{
			info = gl_dialogInfo[game::currentDialogInfo].hook_actionId[i];
			if (!logic::isActionHidden(info)
				&& (gl_dialogInfo[info].type == DIALOGTYPE_ACTION || gl_dialogInfo[info].type == DIALOGTYPE_SUCCESS || gl_dialogInfo[info].type == DIALOGTYPE_FAILURE))
			{
				buttonsTotal += 1;
			}
			else if (!logic::isActionHidden(info) && gl_dialogInfo[info].type == DIALOGTYPE_CONDITION && ((gl_dialogInfo[info].g_descriptionStringsUsed == 1
				&& logic::checkCondition(gl_dialogInfo[info].g_descriptionText[0]))
				|| (gl_dialogInfo[info].g_descriptionStringsUsed > 1 && logic::checkMultiCondition(info))))
			{
				buttonsTotal += 1;
			}
		}
		// Creating the buttons
		for (int i = 0; i < gl_dialogInfo[game::currentDialogInfo].hook_amount; i++)
		{
			info = gl_dialogInfo[game::currentDialogInfo].hook_actionId[i];
			if (gl_dialogInfo[info].type == DIALOGTYPE_CONDITION && ((gl_dialogInfo[info].g_descriptionStringsUsed == 1 && logic::checkCondition(gl_dialogInfo[info].g_descriptionText[0]))
				|| (gl_dialogInfo[info].g_descriptionStringsUsed > 1 && logic::checkMultiCondition(info))))
			{
				info = gl_dialogInfo[info].hook_actionId[0];
			}
			if (gl_dialogInfo[info].type == DIALOGTYPE_ACTION || gl_dialogInfo[info].type == DIALOGTYPE_SUCCESS || gl_dialogInfo[info].type == DIALOGTYPE_FAILURE)
			{
				search = UI::addButton();
				UI::btn[search].g_corDialogAction = info;
				UI::btn[search].action = MENU_NEXTDIALOGINFO;
				UI::btn[search].nextMenu = MENU_GAME;
				UI::btn[search].gameButton = true;
				if (!UI::custom_actionOffsetRelative)
				{
					if (!UI::custom_actionOffsetAnchorTop) {
						UI::btn[search].move(UI::custom_actionOffsetX, camera::resolutionY - (buttonsTotal - buttonsFound) * (UI::custom_actionSizeY + UI::custom_actionLineSpacing) - UI::custom_actionOffsetY);
					}
					else {
						UI::btn[search].move(UI::custom_actionOffsetX, buttonsFound * (UI::custom_actionSizeY + UI::custom_actionLineSpacing) + UI::custom_actionOffsetY);
					}
				}
				else
				{
					if (!UI::custom_actionOffsetAnchorTop) {
						UI::btn[search].move(UI::custom_actionOffsetX * camera::resolutionX, camera::resolutionY - (buttonsTotal - buttonsFound) * (UI::custom_actionSizeY + UI::custom_actionLineSpacing) - UI::custom_actionOffsetY * camera::resolutionY);
					}
					else {
						UI::btn[search].move(UI::custom_actionOffsetX * camera::resolutionX, buttonsFound * (UI::custom_actionSizeY + UI::custom_actionLineSpacing) + UI::custom_actionOffsetY * camera::resolutionY);
					}
				}
				
				UI::btn[search].text = gl_dialogInfo[info].g_descriptionText[0];
				UI::btn[search].g_nextDialogInfoCounter = gl_dialogInfo[info].hook_amount;
				for (int a = 0; a < gl_dialogInfo[info].hook_amount; a++)
				{
					UI::btn[search].g_nextDialogInfo[a] = gl_dialogInfo[info].hook_actionId[a];
				}
				UI::btn[search].texID = TEX_EMPTY;
				UI::btn[search].sizeX = camera::resolutionX - 25;
				if (UI::custom_actionSelLength > 0)
				{
					UI::btn[search].sizeX = UI::custom_actionSelLength;
					if (UI::custom_actionSelLengthRel) { UI::btn[search].sizeX *= camera::resolutionX; }
				}
				UI::btn[search].sizeY = UI::custom_actionSizeY;
				if (gl_dialogInfo[info].type == DIALOGTYPE_SUCCESS || gl_dialogInfo[info].type == DIALOGTYPE_FAILURE)
				{
					UI::btn[search].action = MENU_CLEARMODULE;
					UI::btn[search].nextMenu = MENU_MAIN;
				}
				// Hiding the button
				if ((gl_dialogInfo[game::currentDialogInfo].hook_amount == 1 && UI::custom_hideContinueButton) || logic::isActionHidden(info))
				{
					UI::btn[search].hidden = true;
					UI::btn[search].sizeX = 0;
					UI::btn[search].sizeY = 0;
				}
				else
				{
					// Variables
					buttonsFound += 1;
					UI::dialogActionCounter += 1;
				}
			}
		}
	}
}

void UI::displayLoadModuleMenu()
{
	int search;
	UI::menuButtonCountL2 = 0;
	// Drawing main menu
	UI::displayingMenu = MENU_LOADMODULE;
	UI::displayMenu(MENU_MAIN);
	UI::menuLevel = MENU_LOADMODULE;
	// Looking for available files
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	std::wstring filename, filepath, modulename, buttontext, buttontextbuf1, buttontextbuf2;

	hFind = FindFirstFile(L"Modules\\*", &FindFileData);
	bool result = true;
	while (result)
	{
		// Checking the file
		filename = FindFileData.cFileName;
		if (filename.length() > 4 && filename.substr(filename.length() - 4) == L".amf" && filename != L"main.amf" && filename != L"menu.amf")
		{
			modulename = filename;
			filepath = L"Modules\\" + filename;
			getModuleName(filepath, modulename);
			buttontextbuf1 = std::to_wstring((_Longlong)UI::menuButtonCountL2 + 1);
			if (UI::menuButtonCountL2 < 9) { buttontext = L"0" + buttontextbuf1 + L". " + modulename; }
			else { buttontext = buttontextbuf1 + L". " + modulename; }
			// Creating the button
			search = UI::addButton();
			UI::btn[search].action = MENU_LOADMODULESTART;
			UI::btn[search].nextMenu = MENU_GAME;
			UI::btn[search].text = buttontext;
			UI::btn[search].textCenter = false;
			UI::btn[search].extraData = filename;
			UI::btn[search].move(455, 100 + UI::menuButtonCountL2 * 40);
			UI::btn[search].sizeX = camera::resolutionX - 470;
			UI::btn[search].sizeY = 35;
			UI::btn[search].textOffsetY = -3;

			UI::menuButtonCountL2 += 1;
		}
		// Looking for the next file
		result = FindNextFile(hFind, &FindFileData);
	}
	// Creating the back button
	search = UI::addButton();
	UI::btn[search].nextMenu = MENU_MAIN;
	UI::btn[search].move(100, 200);
	UI::btn[search].text = L"Adventures";
	if (settings::lang == LANG_RUSSIAN) { UI::btn[search].text = L"Приключения"; }
	UI::btn[search].sizeX = 300;
	UI::btn[search].sizeY = 40;
	UI::btn[search].textCenter = true;
	UI::btn[search].opened = true;
}

void UI::displayLoadSavePointMenu(bool save)
{
	int search, hours, minutes, seconds;
	UI::menuButtonCountL2 = 0;
	// Drawing main menu
	if (!save)
	{
		UI::displayingMenu = MENU_LOADSAVEPOINT;
		UI::displayMenu(MENU_MAIN);
		UI::menuLevel = MENU_LOADSAVEPOINT;
	}
	else
	{
		UI::displayingMenu = MENU_CREATESAVEPOINT;
		UI::displayMenu(MENU_MAIN);
		UI::menuLevel = MENU_CREATESAVEPOINT;
	}
	// Looking for available files
	std::wifstream file;
	std::wstring filename, filepath, modulename, buttontext, buttontextbuf1, buttontextbuf2, buf;
	std::wstring slot, noData;
	slot = L"Slot ";	noData = L"[No data]";
	if (settings::lang == LANG_RUSSIAN) { slot = L"Слот "; noData = L"[Нет данных]"; }

	for (int i = 0; i < 10; i++)
	{
		filepath = L"Data\\Savefiles\\slot" + std::to_wstring((_Longlong)i) + L".bin";
		// Opening the file
		file.open(filepath);
		if (file.good())
		{
			std::getline(file, filename);
			modulename = filename + L".amf";
			filepath = L"Modules\\" + filename + L".amf";
			getModuleName(filepath, modulename);
			buttontextbuf1 = std::to_wstring((_Longlong)UI::menuButtonCountL2 + 1);
			if (UI::menuButtonCountL2 < 9) { buttontext = slot + L"0" + buttontextbuf1 + L". " + modulename; }
			else { buttontext = slot + buttontextbuf1 + L". " + modulename; }
			// Creating the main button
			search = UI::addButton();
			if (!save) { UI::btn[search].action = MENU_LOADSAVEPOINT0 + UI::menuButtonCountL2; }
			else { UI::btn[search].action = MENU_CREATESAVEPOINT0 + UI::menuButtonCountL2; }
			UI::btn[search].nextMenu = MENU_GAME;
			UI::btn[search].text = buttontext;
			UI::btn[search].textCenter = false;
			UI::btn[search].extraData = filename;
			UI::btn[search].move(455, 100 + UI::menuButtonCountL2 * 40);
			UI::btn[search].sizeX = camera::resolutionX - 470;
			UI::btn[search].sizeY = 35;
			UI::btn[search].textOffsetY = -3;

			// Loading the gametime data
			std::getline(file, buf);	std::wstringstream(buf) >> hours;
			std::getline(file, buf);	std::wstringstream(buf) >> minutes;
			std::getline(file, buf);	std::wstringstream(buf) >> seconds;

			// Creating the gametime button
			if (camera::resolutionX >= 1100)
			{
				search = UI::addButton();
				UI::btn[search].move(1000, 100 + UI::menuButtonCountL2 * 40);
				UI::btn[search].sizeX = 0;
				UI::btn[search].textOffsetY = -3;
				if (hours < 10) { buttontext = L"0"; } 
				buttontext += std::to_wstring((_Longlong)hours) + L":";
				if (minutes < 10) { buttontext += L"0"; }
				buttontext += std::to_wstring((_Longlong)minutes) + L":";
				if (seconds < 10) { buttontext += L"0"; }
				buttontext += std::to_wstring((_Longlong)seconds);
				UI::btn[search].text = buttontext;
			}

			UI::menuButtonCountL2 += 1;
		}
		else
		{
			// Creating empty button
			search = UI::addButton();
			buttontextbuf1 = std::to_wstring((_Longlong)UI::menuButtonCountL2 + 1);
			if (UI::menuButtonCountL2 < 9) { buttontext = slot + L"0" + buttontextbuf1 + L". " + noData; }
			else { buttontext = slot + buttontextbuf1 + L". " + noData; }
			UI::btn[search].nextMenu = MENU_LOADSAVEPOINT;
			if (save)
			{
				UI::btn[search].nextMenu = MENU_GAME;
				UI::btn[search].action = MENU_CREATESAVEPOINT0 + UI::menuButtonCountL2;
			}
			UI::btn[search].text = buttontext;
			UI::btn[search].textCenter = false;
			UI::btn[search].extraData = filename;
			UI::btn[search].move(455, 100 + UI::menuButtonCountL2 * 40);
			UI::btn[search].sizeX = camera::resolutionX - 470;
			UI::btn[search].sizeY = 35;
			UI::btn[search].textOffsetY = -3;

			UI::menuButtonCountL2 += 1;
		}
		file.close();
	}
	// Creating the back button
	if (!save)
	{
		search = UI::addButton();
		UI::btn[search].nextMenu = MENU_MAIN;
		if (!game::isModuleLoaded)
		{
			UI::btn[search].move(100, 250);
			UI::btn[search].text = L"Saved games";
			if (settings::lang == LANG_RUSSIAN) { UI::btn[search].text = L"Сохраненные игры"; }
		}
		else
		{
			UI::btn[search].move(100, 275);
			UI::btn[search].text = L"Load game";
			if (settings::lang == LANG_RUSSIAN) { UI::btn[search].text = L"Загрузить игру"; }
		}
		UI::btn[search].sizeX = 300;
		UI::btn[search].sizeY = 40;
		UI::btn[search].textCenter = true;
		UI::btn[search].opened = true;
	}
	else
	{
		search = UI::addButton();
		UI::btn[search].nextMenu = MENU_MAIN;
		if (!game::isModuleLoaded) { UI::btn[search].move(100, 200); }
		else { UI::btn[search].move(100, 225); }
		UI::btn[search].text = L"Save game";
		if (settings::lang == LANG_RUSSIAN) { UI::btn[search].text = L"Сохранить игру"; }
		UI::btn[search].sizeX = 300;
		UI::btn[search].sizeY = 40;
		UI::btn[search].textCenter = true;
		UI::btn[search].opened = true;
	}
}

void UI::displaySettingsMenu()
{
	int search;
	UI::menuButtonCountL2 = 0;
	// Drawing main menu
	UI::displayingMenu = MENU_SETTINGS;
	UI::displayMenu(MENU_MAIN);
	UI::menuLevel = MENU_SETTINGS;
	
	// Body
	search = UI::addSlider();
	UI::sld[search].type = SLIDER_VOLUME_MASTER;
	UI::sld[search].move(700, 145);
	UI::sld[search].sizeX = 200;
	UI::sld[search].sizeY = 40;
	UI::sld[search].sliderDivision = 5.00f;
	UI::sld[search].sliderValue = settings::volMaster * 100.00f;
	search = UI::addSlider();
	UI::sld[search].type = SLIDER_VOLUME_SOUND;
	UI::sld[search].move(700, 190);
	UI::sld[search].sizeX = 200;
	UI::sld[search].sizeY = 40;
	UI::sld[search].sliderDivision = 5.00f;
	UI::sld[search].sliderValue = settings::volSound * 100.00f;
	search = UI::addSlider();
	UI::sld[search].type = SLIDER_VOLUME_MUSIC;
	UI::sld[search].move(700, 235);
	UI::sld[search].sizeX = 200;
	UI::sld[search].sizeY = 40;
	UI::sld[search].sliderDivision = 5.00f;
	UI::sld[search].sliderValue = settings::volMusic * 100.00f;
	search = UI::addSlider();
	UI::sld[search].type = SLIDER_VOLUME_VOICE;
	UI::sld[search].move(700, 280);
	UI::sld[search].sizeX = 200;
	UI::sld[search].sizeY = 40;
	UI::sld[search].sliderDivision = 5.00f;
	UI::sld[search].sliderValue = settings::volVoice * 100.00f;

	// Creating the back button
	search = UI::addButton();
	UI::btn[search].nextMenu = MENU_MAIN;
	if (!game::isModuleLoaded) { UI::btn[search].move(100, 325); }
	else { UI::btn[search].move(100, 350); }
	UI::btn[search].text = L"Settings";
	if (settings::lang == LANG_RUSSIAN) { UI::btn[search].text = L"Настройки"; }
	UI::btn[search].sizeX = 300;
	UI::btn[search].sizeY = 40;
	UI::btn[search].textCenter = true;
	UI::btn[search].opened = true;
}

// DISPLAY MENU TEMPLATE
/*void UI::display%OUR LEVEL%Menu()
{
	int search;
	UI::menuButtonCountL2 = 0;
	// Drawing main menu
	UI::displayingMenu = MENU_%OUR LEVEL%;
	UI::displayMenu(MENU_MAIN);
	UI::menuLevel = MENU_%OUR LEVEL%;

	// Creating the back button
	search = UI::addButton();
	UI::btn[search].nextMenu = MENU_MAIN;
	UI::btn[search].move(100, %POSITION Y%);
	UI::btn[search].text = L"%ENGLISH BUTTON TEXT%";
	if (settings::lang == LANG_RUSSIAN) { UI::btn[search].text = L"%RUSSIAN BUTTON TEXT%"; }
	UI::btn[search].sizeX = 300;
	UI::btn[search].sizeY = 40;
	UI::btn[search].textCenter = true;
	UI::btn[search].opened = true;
}*/

void UI::clearButtons(bool removeTimers)
{
	if (removeTimers) { UI::buttonCounter = 0; }
	else
	{
		button vault[64];
		int vaultCounter = 0;
		for (int i = 0; i < UI::buttonCounter; i++)
		{
			if (UI::btn[i].timerValue > 0 && UI::btn[i].timerValue < 50000)
			{
				vault[vaultCounter++] = UI::btn[i];
			}
		}

		for (int i = 0; i < vaultCounter; i++)
		{
			UI::btn[i] = vault[i];
		}
		UI::buttonCounter = vaultCounter;
	}
}