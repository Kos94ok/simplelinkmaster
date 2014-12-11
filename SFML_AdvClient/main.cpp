
#include "main.h"

button UI::btn[64];
int UI::buttonCounter = 0;
int UI::dialogActionCounter = 0;
slider UI::sld[64];
int UI::sliderCounter = 0;
int UI::menuLevel = MENU_MAIN;
int UI::displayingMenu;
int game::currentDialogInfo = -1;
bool game::isModuleLoaded = false;
bool game::creditsMode = false;
bool camera::fullscreen;
bool camera::borderless;
int camera::resolutionX = 1024;
int camera::resolutionY = 768;
int game::maxPriority = 1;
std::wstring game::folder = L"";
sf::Music game::mainSound;
sf::Music game::bgMusic[16];
std::wstring game::bgMusicName[16];
int game::bgMusicFadeTime[16];
float game::bgMusicMaxVolume[16];
sf::Music game::voiceOver;
std::wstring game::voiceOverName;
int game::voiceOverFadeTime;
float game::voiceOverMaxVolume;
int game::displayImageCounter = 0;
image game::displayImages[IMAGE_LIMIT];
bool UI::custom_hideOverlay;
float UI::custom_textOffsetX;
float UI::custom_textOffsetY;
bool UI::custom_textOffsetRelative;
float UI::custom_textMaxLength;
bool UI::custom_textMaxLengthRel;
int UI::custom_textLineSpacing;
int UI::custom_textCharSize;
float UI::custom_actionOffsetX;
float UI::custom_actionOffsetY;
bool UI::custom_actionOffsetRelative;
bool UI::custom_actionOffsetAnchorTop;
float UI::custom_actionSelLength;
bool UI::custom_actionSelLengthRel;
int UI::custom_actionLineSpacing;
int UI::custom_actionCharSize;
int UI::custom_actionSizeY;
int UI::custom_actionTextOffsetY;
bool UI::custom_allowScreenContinue;
bool UI::custom_hideContinueButton;
bool UI::custom_fancyPrintAllowed;
float UI::custom_fancyPrintDelay;

bool UI::printDelayOver = false;
int UI::printDelayAmount = 0;
float UI::printDelayActive = 0;
int UI::menuButtonCountL2 = 0;
int UI::menuButtonCountL3 = 0;
int gametime::millisec = 0;
int gametime::seconds = 0;
int gametime::minutes = 0;
int gametime::hours = 0;

bool settings::autoCreateDirectories = false;
bool settings::forceTexturePreload;
bool settings::forceTextureClearUp;
float settings::volMaster = 0.50f;
float settings::volSound = 0.50f;
float settings::volMusic = 0.50f;
float settings::volVoice = 0.50f;
int settings::lang = LANG_ENGLISH;
int globalTime;
int dialogInfo::entryPoint = -1;
int dialogInfo::bsodPoint = -1;
dialogInfo gl_dialogInfo[OBJECT_LIMIT];
int gl_dialogInfoCounter = 0;
sf::Font gl_mainFont;
int gl_gameTexCount = 0;
sf::Texture gl_gameTexture[128];
std::wstring gl_gameTexName[128];


int main(int argc, char* argv[])
{
	std::string title = "Simple Link Player v1.0 RC3";
	int elapsedTime = 0;
	srand(time(0));
	std::locale::global(std::locale("Russian"));
	// Load settings
	settings::load();
	settings::load_customUI();
	// Loading fonts
	if (!gl_mainFont.loadFromFile("Data//Fonts//segoepr.ttf"))
	{
		gl_mainFont.loadFromFile("C://Windows//Fonts//segoepr.ttf");
	}
	// segoepr.ttf
	
	// Overriding resolution settings
	if (camera::borderless) { camera::resolutionX = sf::VideoMode::getDesktopMode().width;	camera::resolutionY = sf::VideoMode::getDesktopMode().height; }
	// Opening window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;
	sf::RenderWindow windowMain;
	// Window mode
	if (camera::borderless) { windowMain.create(sf::VideoMode(camera::resolutionX, camera::resolutionY), title, 0, settings); }
	else if (camera::fullscreen) { windowMain.create(sf::VideoMode(camera::resolutionX, camera::resolutionY), title, sf::Style::Fullscreen, settings); }
	else { windowMain.create(sf::VideoMode(camera::resolutionX, camera::resolutionY), title, sf::Style::Titlebar | sf::Style::Close, settings); }
	// Icon
	sf::Image Icon;
	if (Icon.loadFromFile("Data//Textures//UI_icon_adventure.png")) { windowMain.setIcon(64, 64, Icon.getPixelsPtr()); }
	// Loading menu
	game::loadModuleFull(L"menu.amf");
	game::isModuleLoaded = false;
	logic::activateMenuData();
	UI::displayMenu(MENU_MAIN);
	// Parsing arguments
	mainArgumentParse(argc, argv, windowMain);
	// Main loop
	globalTime = timeGetTime();
	while (windowMain.isOpen())
	{
		// Timers
		elapsedTime = timeGetTime() - globalTime;
		mainTimerChecking(elapsedTime, windowMain);
		globalTime = timeGetTime();
		// Event handling
		mainEventCheck(windowMain);
		// Painting
		mainPaint(windowMain);
	}
	return 0;
}

void mainArgumentParse(int argc, char* argv[], sf::RenderWindow &winHandle)
{
	std::string arg;
	std::wstring warg;
	for (int i = 1; i < argc; i++)
	{
		arg = argv[i];
		warg = std::wstring(arg.begin(), arg.end());
		// Forced loading
		if (warg.substr(warg.length() - 4) == L".amf")
		{
			UI::clearButtons(true);
			game::loadModuleFull(warg.substr(0));
			UI::displayMenu(MENU_GAME);
			logic::activateTimers();
		}
	}
}

void mainTimerChecking(int elapsedTime, sf::RenderWindow &winHandle)
{
	float timevar = (float)elapsedTime / 1000.00f;
	if (timevar > 0.10f) { return; }
	
	// Gametime
	if (UI::menuLevel == MENU_GAME)
	{
		gametime::millisec += elapsedTime;
		if (gametime::millisec >= 1000) { gametime::seconds += 1;	gametime::millisec -= 1000; }
		if (gametime::seconds >= 60)	{ gametime::minutes += 1;	gametime::seconds -= 60; }
		if (gametime::minutes >= 60)	{ gametime::hours += 1;		gametime::minutes -= 60; }
	}
	// Checking button timers
	for (int i = 0; i < UI::buttonCounter; i++)
	{
		int savedActiveInfo = game::currentDialogInfo;
		if (UI::btn[i].timerValue == 0 || (UI::btn[i].timerValue > 0 && UI::menuLevel == MENU_GAME))
		{
			UI::btn[i].timerValue -= elapsedTime;
			if (UI::btn[i].timerValue < 0)
			{
				UI::buttonCallback(i, winHandle);
				if (savedActiveInfo == game::currentDialogInfo)
				{
					for (int y = 0; y < UI::buttonCounter; y++)
					{
						if (UI::btn[y].timerValue == 0) { UI::btn[y].timerValue = 100500; }
					}
				}
			}
		}
	}
	// Checking fancy text print
	if (UI::custom_fancyPrintAllowed && !UI::printDelayOver && UI::menuLevel == MENU_GAME)
	{
		UI::printDelayActive -= timevar;
		if (UI::printDelayActive <= 0.00f)
		{
			UI::printDelayActive = UI::custom_fancyPrintDelay;
			UI::printDelayAmount += 1;
		}
	}
	// Checking images
	for (int i = 0; i < game::displayImageCounter; i++)
	{
		// Moving
		if (game::displayImages[i].movingSpeed > 0)
		{
			game::displayImages[i].posAbsX = a_math::polarX(game::displayImages[i].posAbsX, game::displayImages[i].movingSpeed * timevar, game::displayImages[i].movingAngle);
			game::displayImages[i].posAbsY = a_math::polarY(game::displayImages[i].posAbsY, -game::displayImages[i].movingSpeed * timevar, game::displayImages[i].movingAngle);
		}
		// Effect spawning
		int search;
		int offsetDist;
		float averageAngle;
		if (game::displayImages[i].isEffect)
		{
			game::displayImages[i].effectSpawnTimer -= elapsedTime;
			if (game::displayImages[i].effectSpawnTimer <= 0)
			{
				game::displayImages[i].effectSpawnTimer = game::displayImages[i].effectSpawnPeriod * 1000;
				for (int y = 0; y < game::displayImages[i].effectDensity; y++)
				{
					if (IMAGE_LIMIT - game::displayImageCounter > IMAGE_RESERVE)
					{
						offsetDist = a_math::rand(0, game::displayImages[i].effectFrontLength / 2);
						averageAngle = (game::displayImages[i].effectAngleMin + game::displayImages[i].effectAngleMax) / 2.00f;
						if (a_math::randf(0.00f, 1.00f) < 0.50f) { averageAngle += 90.00f; } else { averageAngle -= 90.00f; }

						search = game::displayImageCounter;
						game::displayImages[search] = game::displayImages[i];
						game::displayImages[search].isEffect = false;
						if (game::displayImages[search].usingAbsPos)
						{
							game::displayImages[search].posAbsX = a_math::polarX(game::displayImages[i].posAbsX, offsetDist, averageAngle);
							game::displayImages[search].posAbsY = a_math::polarY(game::displayImages[i].posAbsY, offsetDist, averageAngle);
						}
						else
						{
							game::displayImages[search].usingAbsPos = true;
							game::displayImages[search].posAbsX = a_math::polarX(game::displayImages[i].posRelX * camera::resolutionX, offsetDist, averageAngle);
							game::displayImages[search].posAbsY = a_math::polarY(game::displayImages[i].posRelY * camera::resolutionY, offsetDist, averageAngle);
						}
						game::displayImages[search].movingAngle = a_math::randf(game::displayImages[i].effectAngleMin, game::displayImages[i].effectAngleMax);
						game::displayImages[search].movingSpeed = game::displayImages[i].effectSpeed;
						game::displayImages[search].lifespan = game::displayImages[i].effectLifespan;
						game::displayImageCounter += 1;
					}
				}
			}
		}
		// FadeDelay
		if (game::displayImages[i].delayTimer > 0.00f)
		{
			game::displayImages[i].delayTimer -= timevar;
			if (game::displayImages[i].delayTimer < 0.00f) { game::displayImages[i].delayTimer = 0.00; }
		}
		else
		{
			// FadeIn
			if (game::displayImages[i].fadeMax > 0.00f && game::displayImages[i].fadeCur < game::displayImages[i].fadeMax && !game::displayImages[i].fadeBack)
			{
				game::displayImages[i].fadeCur += timevar;
				if (game::displayImages[i].fadeCur >= game::displayImages[i].fadeMax)
				{
					if (game::displayImages[i].toFadeBack)
					{
						game::displayImages[i].fadeBack = true;
						game::displayImages[i].delayTimer = game::displayImages[i].toDelayTimer;
						game::displayImages[i].fadeMax = game::displayImages[i].toFadeMax;
						game::displayImages[i].toFadeBack = false;
						game::displayImages[i].toDelayTimer = 0.00f;
					}
				}
			}
			// FadeOut
			if (game::displayImages[i].fadeBack && game::displayImages[i].fadeCur > 0.00f)
			{
				game::displayImages[i].fadeCur -= timevar;
				if (game::displayImages[i].fadeCur <= 0.00f)
				{
					for (int y = i; y < game::displayImageCounter - 1; y++)
					{
						game::displayImages[y] = game::displayImages[y + 1];
					}
					game::displayImageCounter -= 1;
					i = game::displayImageCounter;
				}
			}
		}
		// Lifespan
		if (game::displayImages[i].lifespan > 0)
		{
			game::displayImages[i].lifespan -= timevar;
			if (game::displayImages[i].lifespan < 0)
			{
				// Removing the image from the list
				for (int y = i; y < game::displayImageCounter - 1; y++)
				{
					game::displayImages[y] = game::displayImages[y + 1];
				}
				game::displayImageCounter -= 1;
				i -= 1;
			}
		}
	}
	// Checking sound channels
		// Voiceover
	if (game::voiceOver.getStatus() == sf::Music::Playing && abs(game::voiceOverMaxVolume - game::voiceOver.getVolume()) > 1.00f && game::voiceOverFadeTime > 0)
	{
		// Increasing
		if (game::voiceOverMaxVolume > game::voiceOver.getVolume())
		{
			game::voiceOver.setVolume( game::voiceOver.getVolume() + ((float)elapsedTime / game::voiceOverFadeTime) * 100.00f );
		}
		// Decreasing
		else
		{
			game::voiceOver.setVolume( game::voiceOver.getVolume() - ((float)elapsedTime / game::voiceOverFadeTime) * 100.00f );
			if (game::voiceOver.getVolume() < 1.00) { game::voiceOver.stop(); }
		}
	}
		// Music channels
	for (int i = 0; i < 16; i++)
	{
		if (game::bgMusic[i].getStatus() == sf::Music::Playing && abs(game::bgMusicMaxVolume[i] - game::bgMusic[i].getVolume()) >= 1.00f && game::bgMusicFadeTime[i] > 0)
		{
			// Increasing
			if (game::bgMusicMaxVolume[i] > game::bgMusic[i].getVolume())
			{
				game::bgMusic[i].setVolume( game::bgMusic[i].getVolume() + ((float)elapsedTime / game::bgMusicFadeTime[i]) * 100.00f );
			}
			// Decreasing
			else
			{
				game::bgMusic[i].setVolume( game::bgMusic[i].getVolume() - ((float)elapsedTime / game::bgMusicFadeTime[i]) * 100.00f );
				if (game::bgMusic[i].getVolume() < 1.00f) { game::bgMusic[i].stop(); }
			}
		}
	}
}

void mainEventCheck(sf::RenderWindow &winHandle)
{
	bool mouseUsed = false;
	sf::Event eventPoll;
	while (winHandle.pollEvent(eventPoll))
	{
		if (eventPoll.type == sf::Event::Closed) { winHandle.close(); }
		// Slider move
		if ((eventPoll.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			|| (eventPoll.type == sf::Event::MouseButtonPressed && eventPoll.mouseButton.button == sf::Mouse::Left))
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(winHandle);
			int search = UI::findSliderInPoint(mousePos.x, mousePos.y);
			if (search != -1)
			{
				UI::sld[search].sliderValue = (float)(mousePos.x - UI::sld[search].posX) / UI::sld[search].sizeX * UI::sld[search].sliderMaxValue;
				UI::sld[search].sliderValue = a_math::round(UI::sld[search].sliderValue / UI::sld[search].sliderDivision) * UI::sld[search].sliderDivision;
				if (UI::sld[search].type == SLIDER_VOLUME_MASTER) { settings::volMaster = UI::sld[search].sliderValue / 100.00f; }
				else if (UI::sld[search].type == SLIDER_VOLUME_SOUND) { settings::volSound = UI::sld[search].sliderValue / 100.00f; }
				else if (UI::sld[search].type == SLIDER_VOLUME_MUSIC) { settings::volMusic = UI::sld[search].sliderValue / 100.00f; }
				else if (UI::sld[search].type == SLIDER_VOLUME_VOICE) { settings::volVoice = UI::sld[search].sliderValue / 100.00f; }
				settings::updateMusicVolume();
				settings::save();
			}
		}
		// Button click
		if (eventPoll.type == sf::Event::MouseButtonPressed && eventPoll.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(winHandle);
			int search = UI::findButtonInPoint(mousePos.x, mousePos.y);
			if (search != -1)
			{
				mouseUsed = true;
				UI::buttonCallback(search, winHandle);
			}
		}
		// Mouse move
		if (eventPoll.type == sf::Event::MouseMoved)
		{
			UI::buttonHoverover(winHandle);
		}
		// Escape button
		if (eventPoll.type == sf::Event::KeyPressed && eventPoll.key.code == sf::Keyboard::Escape && game::isModuleLoaded)
		{
			UI::clearButtons(false);
			if (!game::creditsMode)
			{
				if (UI::menuLevel == MENU_MAIN) { UI::displayMenu(MENU_GAME); }
				else { UI::displayMenu(MENU_MAIN); }
			}
			else
			{
				game::creditsMode = false;
				clearModule();
				game::fullClearUp();
				game::loadModuleFull(L"menu.amf");
				game::isModuleLoaded = false;
				logic::activateMenuData();
				UI::displayMenu(MENU_MAIN);
			}
		}
		// Screen continue
		if (eventPoll.type == sf::Event::MouseButtonPressed && eventPoll.mouseButton.button == sf::Mouse::Left && !mouseUsed && UI::custom_allowScreenContinue
			&& !(UI::custom_fancyPrintAllowed && !UI::printDelayOver))
		{
			if (gl_dialogInfo[game::currentDialogInfo].hook_amount == 1)
			{
				bool continueFound = false;
				// Button
				for (int i = 0; i < UI::buttonCounter; i++)
				{
					for (int y = 0; y < LINK_LIMIT; y++)
					{
						if (UI::btn[i].g_corDialogAction == gl_dialogInfo[game::currentDialogInfo].hook_actionId[y] && !UI::btn[i].hidden)
						{
							continueFound = true;
							UI::buttonCallback(i, winHandle);
							i = UI::buttonCounter;
						}
					}
				}
				// Direct connection
				if (!continueFound && gl_dialogInfo[gl_dialogInfo[game::currentDialogInfo].hook_actionId[0]].type == DIALOGTYPE_INFO)
				{
					// Simulating the button
					continueFound = true;

					int search = UI::addButton();
					UI::btn[search].action = MENU_NEXTDIALOGINFO;
					UI::btn[search].nextMenu = MENU_GAME;
					UI::btn[search].g_nextDialogInfoCounter = 1;
					UI::btn[search].g_nextDialogInfo[0] = gl_dialogInfo[game::currentDialogInfo].hook_actionId[0];
					UI::btn[search].g_corDialogAction = gl_dialogInfo[game::currentDialogInfo].hook_actionId[0];

					UI::buttonCallback(search, winHandle);
				}
				// Reset the fancy text data
				if (UI::custom_fancyPrintAllowed && continueFound) { UI::printDelayActive = UI::custom_fancyPrintDelay;	UI::printDelayAmount = 0; }
			}
		}
		// Skip fancy print
		if (eventPoll.type == sf::Event::MouseButtonPressed && eventPoll.mouseButton.button == sf::Mouse::Left && !mouseUsed
			&& UI::custom_fancyPrintAllowed && !UI::printDelayOver)
		{
			UI::printDelayOver = true;
			UI::printDelayAmount = 1000000;
		}
	}
}

void mainPaint(sf::RenderWindow &winHandle)
{
	std::wofstream file;
	std::wstring buf;
	// Creating brushes
	sf::RectangleShape brushRect;
	sf::Text brushText;
	brushText.setFont(gl_mainFont);
	sf::Transform matrix;
	// Clearing the window
	winHandle.clear(sf::Color(150, 150, 150));
	// Displaying the in-game images
	paint::p_gameImages(winHandle);
	// Displaying the in-game overlay
	if (UI::menuLevel == MENU_GAME && !UI::custom_hideOverlay)
	{
		brushRect.setTexture(0);
		brushRect.setPosition(0, 0);
		brushRect.setSize(sf::Vector2f(camera::resolutionX, gl_dialogInfo[game::currentDialogInfo].g_descriptionStringsUsed * (UI::custom_textCharSize + UI::custom_textLineSpacing) + 30));
		brushRect.setFillColor(sf::Color(0, 0, 0, 100));
		brushRect.setOutlineThickness(0);
		winHandle.draw(brushRect);

		brushRect.setPosition(0, camera::resolutionY - UI::dialogActionCounter * (UI::custom_actionSizeY + UI::custom_actionLineSpacing) - 75);
		brushRect.setSize(sf::Vector2f(camera::resolutionX, camera::resolutionY));
		brushRect.setFillColor(sf::Color(0, 0, 0, 100));
		winHandle.draw(brushRect);
	}

	brushText.setStyle(sf::Text::Regular);
	// Displaying the active dialogInfo description
	paint::p_dialogInfoDescription(winHandle);
	// Displaying the main menu overlay
	paint::p_menuOverlay(winHandle);
	// Painting buttons
	paint::p_menuButtons(winHandle);
	paint::p_menuSliders(winHandle);
	// Flushing the buffer
	winHandle.display();
}

