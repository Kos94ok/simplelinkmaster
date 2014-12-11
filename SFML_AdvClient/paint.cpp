
#include "main.h"

sf::RectangleShape brushRect;
sf::Text brushText;
sf::Transform matrix;

void paint::p_gameImages(sf::RenderWindow &winHandle)
{
	brushRect.setOrigin(0.00f, 0.00f);
	brushText.setFont(gl_mainFont);
	brushText.setStyle(sf::Text::Regular);
	matrix = sf::Transform::Identity;
	brushRect.setOutlineThickness(0.00f);
	brushRect.setOutlineColor(sf::Color(0, 0, 0));
	for (int pr = 0; pr < game::maxPriority; pr++)
	{
		for (int i = 0; i < game::displayImageCounter; i++)
		{
			if (game::displayImages[i].priority == pr && !game::displayImages[i].isEffect)
			{
				brushRect.setOrigin(0, 0);
				brushRect.setFillColor(sf::Color(255, 255, 255));
				// Fade
				if (game::displayImages[i].fadeMax > 0.00f)
				{
					if (game::displayImages[i].fadeCur > game::displayImages[i].fadeMax) { game::displayImages[i].fadeCur = game::displayImages[i].fadeMax; }

					brushRect.setFillColor(sf::Color(255, 255, 255, (game::displayImages[i].fadeCur / game::displayImages[i].fadeMax) * 255));
				}
				// Position
				if (game::displayImages[i].usingAbsPos) { brushRect.setPosition(game::displayImages[i].posAbsX, game::displayImages[i].posAbsY); }
				else { brushRect.setPosition(game::displayImages[i].posRelX * camera::resolutionX, game::displayImages[i].posRelY * camera::resolutionY); }
				// Size
				if (game::displayImages[i].usingAbsSize) { brushRect.setSize(sf::Vector2f(game::displayImages[i].sizeAbsX, game::displayImages[i].sizeAbsY)); }
				else { brushRect.setSize(sf::Vector2f(game::displayImages[i].sizeRelX * camera::resolutionX, game::displayImages[i].sizeRelY * camera::resolutionY)); }
				// Texture
				brushRect.setTexture(&gl_gameTexture[game::displayImages[i].tex]);
				brushRect.setTextureRect(sf::IntRect(0, 0, gl_gameTexture[game::displayImages[i].tex].getSize().x, gl_gameTexture[game::displayImages[i].tex].getSize().y));
				// Inverting the matrix
				if (game::displayImages[i].inverseX) { matrix.translate(sf::Vector2f(game::displayImages[i].sizeAbsX, 0)); matrix.scale(-1.00f, 1.00f); }
				if (game::displayImages[i].inverseY) { matrix.translate(sf::Vector2f(0, game::displayImages[i].sizeAbsX)); matrix.scale(1.00f, -1.00f); }
				// Display
				winHandle.draw(brushRect, matrix);
				matrix = sf::Transform::Identity;
			}
		}
	}
}

void paint::p_dialogInfoDescription(sf::RenderWindow &winHandle)
{
	brushRect.setOrigin(0.00f, 0.00f);
	brushText.setFont(gl_mainFont);
	brushText.setStyle(sf::Text::Regular);
	matrix = sf::Transform::Identity;
	if (game::currentDialogInfo != -1)
	{
		UI::printDelayOver = true;
		int charsPrinted = 0;
		//if (!UI::custom_fancyPrintAllowed) { charsPrinted = 100000; UI::printDelayAmount = 100001; }
		std::wstring buf;		std::wstring miniBuf;
		int strStart = 0, strEnd = 0, prevOffset = 0;
		int bold_marks = 0, underline_marks = 0, italic_marks = 0, color_marks = 0, color_end_marks = 0;
		bool style_bold = false, style_underlined = false, style_italic = false;
		int color_r = 255, color_g = 255, color_b = 255;

		int charSize = UI::custom_textCharSize;

		charsPrinted = 0;
		for (int i = 0; i < gl_dialogInfo[game::currentDialogInfo].g_descriptionStringsUsed; i++)
		{
			strStart = 0;	strEnd = 0;		prevOffset = 0;
			bold_marks = 0;		underline_marks = 0;	italic_marks = 0;	color_marks = 0;	color_end_marks = 0;

			buf = gl_dialogInfo[game::currentDialogInfo].g_descriptionText[i];
			input::removeMarkerCharacters(&buf);
			brushText.setStyle(sf::Text::Regular);

			for (int a = 0; a < buf.length(); a++)
			{
				if (buf[a] != '/' && buf[a] != '|' && a < buf.length() - 1 && (charsPrinted < UI::printDelayAmount || !UI::custom_fancyPrintAllowed))
				{
					strEnd += 1;
					charsPrinted += 1;
				}
				else
				{
					if (UI::custom_fancyPrintAllowed && charsPrinted >= UI::printDelayAmount) { a = buf.length(); UI::printDelayOver = false; }
					if (a == buf.length() -1) { strEnd += 1; }
					//else { strStart += 1; }
					if (bold_marks + underline_marks + italic_marks + color_marks + color_end_marks % 2 != 0) { strEnd += 1; }
					// Drawing the string
					miniBuf = buf.substr(strStart, strEnd);
					brushText.setString(miniBuf);
					brushText.setCharacterSize(charSize);
					if (!UI::custom_textOffsetRelative)
					{
						brushText.setPosition(UI::custom_textOffsetX + prevOffset, UI::custom_textOffsetY + i * (charSize + UI::custom_textLineSpacing));
					}
					else
					{
						brushText.setPosition(UI::custom_textOffsetX * camera::resolutionX + prevOffset, UI::custom_textOffsetY * camera::resolutionY + i * (charSize + UI::custom_textLineSpacing));
					}
					brushText.setColor(sf::Color(color_r, color_g, color_b));
					// Styles
					if (!style_bold && !style_underlined && !style_italic) { brushText.setStyle(sf::Text::Regular); }
					else if (style_bold && !style_underlined && !style_italic) { brushText.setStyle(sf::Text::Bold); }
					else if (!style_bold && style_underlined && !style_italic) { brushText.setStyle(sf::Text::Underlined); }
					else if (!style_bold && !style_underlined && style_italic) { brushText.setStyle(sf::Text::Italic); }
					else if (style_bold && style_underlined && !style_italic) { brushText.setStyle(sf::Text::Bold | sf::Text::Underlined); }
					else if (style_bold && !style_underlined && style_italic) { brushText.setStyle(sf::Text::Bold | sf::Text::Italic); }
					else if (!style_bold && style_underlined && style_italic) { brushText.setStyle(sf::Text::Underlined | sf::Text::Italic); }
					else { brushText.setStyle(sf::Text::Bold | sf::Text::Underlined | sf::Text::Italic); }
					// Flushing
					winHandle.draw(brushText);
					// Updating the visual offset
					prevOffset += getVisualOffsetX(strStart + strEnd, miniBuf, charSize, style_bold, style_underlined, style_italic);
					// Parsing the marker
					if (a < buf.length() - 1)
					{
						if (buf[a + 1] == 'n') { a += 2; }
						else if (buf[a + 1] == 'b') { style_bold = !style_bold; a += 3; bold_marks += 1; }
						else if (buf[a + 1] == 'u') { style_underlined = !style_underlined; a += 3; underline_marks += 1; }
						else if (buf[a + 1] == 'i') { style_italic = !style_italic; a += 3; italic_marks += 1; }
						else if (buf[a + 1] == 'c')
						{
							color_r = input::parseColorCode(buf[a + 3], buf[a + 4]);
							color_g = input::parseColorCode(buf[a + 5], buf[a + 6]);
							color_b = input::parseColorCode(buf[a + 7], buf[a + 8]);
							a += 10;
							color_marks += 1;
						}
						else if (buf[a + 1] == 'r') { color_r = 255; color_g = 255; color_b = 255; a += 3; color_end_marks += 1; }
					}
					// Updating the data
					strStart = a;
					strEnd = 0;
				}
			}
		}
	}
}

void paint::p_menuOverlay(sf::RenderWindow &winHandle)
{
	brushText.setColor(sf::Color(255, 255, 255));
	brushRect.setOrigin(0.00f, 0.00f);
	brushText.setFont(gl_mainFont);
	brushText.setStyle(sf::Text::Regular);
	matrix = sf::Transform::Identity;
	brushRect.setOutlineThickness(0.00f);
	brushRect.setOutlineColor(sf::Color(0, 0, 0));
	if (UI::menuLevel != MENU_GAME)
	{
		// In-game menu background fade
		brushRect.setTexture(0);
		if (game::isModuleLoaded)
		{
			brushRect.setPosition(0, 0);
			brushRect.setSize(sf::Vector2f(camera::resolutionX, camera::resolutionY));
			brushRect.setFillColor(sf::Color(127, 127, 127, 220));
			winHandle.draw(brushRect);
		}
		std::wstring buf = L"Main menu";
		if (settings::lang == LANG_RUSSIAN) { buf = L"Главное меню"; }
		brushRect.setSize(sf::Vector2f(300, 2000));
		brushRect.setPosition(100, 0);
		brushRect.setFillColor(sf::Color(0, 0, 0, 100));
		brushRect.setTexture(NULL);
		winHandle.draw(brushRect);
		brushText.setString(buf);
		brushText.setPosition(100 + (300 - getVisualOffsetX(buf.length(), buf, 40)) / 2, 25);
		brushText.setCharacterSize(40);
		winHandle.draw(brushText);
		if (UI::menuLevel == MENU_LOADMODULE || UI::menuLevel == MENU_LOADSAVEPOINT || UI::menuLevel == MENU_CREATESAVEPOINT || UI::menuLevel == MENU_SETTINGS)
		{
			brushRect.setPosition(450, 50);
			brushRect.setSize(sf::Vector2f(camera::resolutionX - 460, camera::resolutionY - 60));
			winHandle.draw(brushRect);
			if (settings::lang == LANG_ENGLISH)
			{
				if (UI::menuLevel == MENU_LOADMODULE) { brushText.setString(L"Available adventures:"); }
				else if (UI::menuLevel == MENU_LOADSAVEPOINT && !game::isModuleLoaded) { brushText.setString(L"Saved games:"); }
				else if (UI::menuLevel == MENU_LOADSAVEPOINT && game::isModuleLoaded) { brushText.setString(L"Load game:"); }
				else if (UI::menuLevel == MENU_CREATESAVEPOINT) { brushText.setString(L"Save game:"); }
				else if (UI::menuLevel == MENU_SETTINGS) { brushText.setString(L"Settings:"); }
			}
			else if (settings::lang == LANG_RUSSIAN)
			{
				if (UI::menuLevel == MENU_LOADMODULE) { brushText.setString(L"Доступные приключения:"); }
				else if (UI::menuLevel == MENU_LOADSAVEPOINT && !game::isModuleLoaded) { brushText.setString(L"Сохраненные игры:"); }
				else if (UI::menuLevel == MENU_LOADSAVEPOINT && game::isModuleLoaded) { brushText.setString(L"Загрузить игру:"); }
				else if (UI::menuLevel == MENU_CREATESAVEPOINT) { brushText.setString(L"Сохранить игру:"); }
				else if (UI::menuLevel == MENU_SETTINGS) { brushText.setString(L"Настройки:"); }
			}
			brushText.setPosition(475, 60);
			brushText.setCharacterSize(24);
			brushText.setStyle(sf::Text::Underlined);
			winHandle.draw(brushText);

			if (UI::menuLevel == MENU_SETTINGS)
			{
				brushText.setCharacterSize(20);
				brushText.setStyle(sf::Text::Regular);

				brushText.setString(L"Master volume:");
				if (settings::lang == LANG_RUSSIAN) { brushText.setString(L"Общая громкость:"); }
				brushText.setPosition(460, 150);
				winHandle.draw(brushText);
				brushText.setString(L"Sound volume:");
				if (settings::lang == LANG_RUSSIAN) { brushText.setString(L"Громкость звука:"); }
				brushText.setPosition(460, 195);
				winHandle.draw(brushText);
				brushText.setString(L"Music volume:");
				if (settings::lang == LANG_RUSSIAN) { brushText.setString(L"Громкость музыки:"); }
				brushText.setPosition(460, 240);
				winHandle.draw(brushText);
				brushText.setString(L"Voice volume:");
				if (settings::lang == LANG_RUSSIAN) { brushText.setString(L"Громкость голоса:"); }
				brushText.setPosition(460, 285);
				winHandle.draw(brushText);
			}
		}
	}
}

void paint::p_menuButtons(sf::RenderWindow &winHandle)
{
	brushRect.setOutlineThickness(0.00f);
	brushRect.setOutlineColor(sf::Color(0, 0, 0));
	brushRect.setOrigin(0.00f, 0.00f);
	brushText.setFont(gl_mainFont);
	brushText.setStyle(sf::Text::Regular);
	brushText.setColor(sf::Color(255, 255, 255));
	matrix = sf::Transform::Identity;
	for (int i = 0; i < UI::buttonCounter; i++)
	{
		if (!UI::btn[i].hidden)
		{
			// Base rect
			brushRect.setPosition(UI::btn[i].posX, UI::btn[i].posY);
			brushRect.setFillColor(sf::Color(255, 255, 255));
			brushRect.setOutlineThickness(0.00f);
			brushRect.setSize(sf::Vector2f(UI::btn[i].sizeX, UI::btn[i].sizeY));
			if (UI::btn[i].texID != TEX_EMPTY) { brushRect.setTexture(0); }
			else
			{
				brushRect.setTexture(NULL);
				if (!UI::btn[i].hovered) { brushRect.setFillColor(sf::Color(255, 255, 255, 0)); }
				else { brushRect.setFillColor(sf::Color(0, 0, 0, 100)); }
			}
			winHandle.draw(brushRect);
			// Button text
			int charSize = UI::custom_actionCharSize;

			std::wstring buf;		std::wstring miniBuf;
			int strStart = 0, strEnd = 0, prevOffset = 0;
			int bold_marks = 0, underline_marks = 0, italic_marks = 0, color_marks = 0, color_end_marks = 0;
			bool style_bold = false, style_underlined = false, style_italic = false;
			int color_r = 255, color_g = 255, color_b = 255;
			if (UI::btn[i].hovered) { color_r = 175; color_g = 175; color_b = 175; }
			if (UI::btn[i].opened) { color_r = 155; color_g = 255; color_b = 255; }
			if (UI::btn[i].hovered && UI::btn[i].opened) { color_r = 55; color_g = 225; color_b = 225; }

			buf = UI::btn[i].text;
			for (int a = 0; a < buf.length(); a++)
			{
				if (buf[a] != '/' && buf[a] != '|' && a < buf.length() - 1) { strEnd += 1; }
				else
				{
					if (a == buf.length() -1) { strEnd += 1; }
					//else { strStart += 1; }
					if (bold_marks + underline_marks + italic_marks + color_marks + color_end_marks % 2 != 0) { strEnd += 1; }
					// Drawing the string
					miniBuf = buf.substr(strStart, strEnd);
					brushText.setString(miniBuf);
					brushText.setCharacterSize(charSize);
					//brushText.setCharacterSize(80);
					if (UI::menuLevel != MENU_GAME)
					{
						if (!UI::btn[i].textCenter) { brushText.setPosition(UI::btn[i].posX + 10 + prevOffset + UI::btn[i].textOffsetX, UI::btn[i].posY + UI::btn[i].textOffsetY + 4); }
						else
						{
							brushText.setPosition(UI::btn[i].posX + (UI::btn[i].sizeX - getVisualOffsetX(UI::btn[i].text.length(), UI::btn[i].text, charSize)) / 2 + UI::btn[i].textOffsetX, UI::btn[i].posY + UI::btn[i].textOffsetY + 4);
						}
					}
					if (UI::menuLevel == MENU_GAME || UI::btn[i].gameButton)
					{
						brushText.setPosition(UI::btn[i].posX + 10 + prevOffset + UI::btn[i].textOffsetX, UI::btn[i].posY + UI::custom_actionTextOffsetY + UI::btn[i].textOffsetY);
					}
					brushText.setColor(sf::Color(color_r, color_g, color_b));
					// Styles
					if (!style_bold && !style_underlined && !style_italic) { brushText.setStyle(sf::Text::Regular); }
					else if (style_bold && !style_underlined && !style_italic) { brushText.setStyle(sf::Text::Bold); }
					else if (!style_bold && style_underlined && !style_italic) { brushText.setStyle(sf::Text::Underlined); }
					else if (!style_bold && !style_underlined && style_italic) { brushText.setStyle(sf::Text::Italic); }
					else if (style_bold && style_underlined && !style_italic) { brushText.setStyle(sf::Text::Bold | sf::Text::Underlined); }
					else if (style_bold && !style_underlined && style_italic) { brushText.setStyle(sf::Text::Bold | sf::Text::Italic); }
					else if (!style_bold && style_underlined && style_italic) { brushText.setStyle(sf::Text::Underlined | sf::Text::Italic); }
					else { brushText.setStyle(sf::Text::Bold | sf::Text::Underlined | sf::Text::Italic); }
					// Flushing
					winHandle.draw(brushText);
					// Updating the visual offset
					prevOffset += getVisualOffsetX(strStart + strEnd, miniBuf, charSize, style_bold, style_underlined, style_italic);
					// Parsing the marker
					if (a < buf.length() - 1)
					{
						if (buf[a + 1] == 'b') { style_bold = !style_bold; a += 3; bold_marks += 1; }
						else if (buf[a + 1] == 'u') { style_underlined = !style_underlined; a += 3; underline_marks += 1; }
						else if (buf[a + 1] == 'i') { style_italic = !style_italic; a += 3; italic_marks += 1; }
						else if (buf[a + 1] == 'c')
						{
							color_r = input::parseColorCode(buf[a + 3], buf[a + 4]);
							color_g = input::parseColorCode(buf[a + 5], buf[a + 6]);
							color_b = input::parseColorCode(buf[a + 7], buf[a + 8]);
							a += 10;
							color_marks += 1;
						}
						else if (buf[a + 1] == 'r')
						{
							color_r = 215; color_g = 215; color_b = 215;
							if (UI::btn[i].hovered) { color_r = 255; color_g = 255; color_b = 255; }
							a += 3;
							color_end_marks += 1;
						}
					}
					// Updating the data
					strStart = a;
					strEnd = 0;
				}
			}
		}
	}
}

void paint::p_menuSliders(sf::RenderWindow &winHandle)
{
	brushRect.setOutlineThickness(0.00f);
	brushRect.setOutlineColor(sf::Color(0, 0, 0));
	for (int i = 0; i < UI::sliderCounter; i++)
	{
		brushRect.setPosition(0, 0);
		brushRect.setOrigin(0, 0);
		// Base rect
		brushRect.setPosition(UI::sld[i].posX, UI::sld[i].posY + UI::sld[i].sizeY / 2 - 10);
		brushRect.setFillColor(sf::Color(100, 100, 100));
		brushRect.setOutlineThickness(1.00f);
		brushRect.setOutlineColor(sf::Color(0, 0, 0));
		brushRect.setSize(sf::Vector2f(UI::sld[i].sizeX, 20));
		brushRect.setTexture(NULL);
		winHandle.draw(brushRect);
		// Slider
		brushRect.setPosition(UI::sld[i].posX + (UI::sld[i].sliderValue / UI::sld[i].sliderMaxValue) * UI::sld[i].sizeX - 5.00f, UI::sld[i].posY);
		brushRect.setFillColor(sf::Color(200, 200, 200));
		brushRect.setOutlineColor(sf::Color(20, 20, 20));
		brushRect.setSize(sf::Vector2f(10.00f, UI::sld[i].sizeY));
		winHandle.draw(brushRect);
		
		// Slider value text
		int charSize = 24;

		brushText.setPosition(UI::sld[i].posX + UI::sld[i].sizeX + 10, UI::sld[i].posY + UI::sld[i].sizeY / 2 - 15);
		brushText.setColor(sf::Color(255, 255, 255));
		brushText.setString(std::to_wstring((long double)UI::sld[i].sliderValue) + L"%");
		brushText.setCharacterSize(charSize);
		brushText.setFont(gl_mainFont);
		winHandle.draw(brushText);
	}
}