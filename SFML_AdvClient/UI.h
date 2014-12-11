
int getVisualOffsetX(int number, std::wstring target, int charsize, bool bold = false, bool underlined = false, bool italic = false);

class button
{
public:
	bool hidden;
	bool gameButton;

	bool hovered;
	bool opened;
	bool textCenter;
	int texID;
	int action;
	int nextMenu;
	int posX;
	int posY;
	float sizeX;
	int sizeY;
	int textOffsetX;
	int textOffsetY;
	int timerValue;
	std::wstring text;

	int g_corDialogAction;
	int g_nextDialogInfoCounter;
	int g_nextDialogInfo[32];
	std::wstring extraData;

	void init();
	void move(int newX, int newY);
	void remove();
};

class slider
{
public:
	int type;

	int posX;
	int posY;
	int sizeX;
	int sizeY;

	float sliderValue;
	float sliderMinValue;
	float sliderMaxValue;
	float sliderDivision;

	void init();
	void move(int newX, int newY);
	void remove();
};

class UI
{
public:
	static bool custom_hideOverlay;
	static float custom_textOffsetX;
	static float custom_textOffsetY;
	static bool custom_textOffsetRelative;
	static float custom_textMaxLength;
	static bool custom_textMaxLengthRel;
	static int custom_textLineSpacing;
	static int custom_textCharSize;
	static float custom_actionOffsetX;
	static float custom_actionOffsetY;
	static bool custom_actionOffsetRelative;
	static bool custom_actionOffsetAnchorTop;
	static float custom_actionSelLength;
	static bool custom_actionSelLengthRel;
	static int custom_actionLineSpacing;
	static int custom_actionCharSize;
	static int custom_actionSizeY;
	static int custom_actionTextOffsetY;
	static bool custom_allowScreenContinue;
	static bool custom_hideContinueButton;
	static bool custom_fancyPrintAllowed;
	static float custom_fancyPrintDelay;

	static bool printDelayOver;
	static int printDelayAmount;
	static float printDelayActive;

	static button btn[64];
	static int buttonCounter;
	static int dialogActionCounter;
	static slider sld[64];
	static int sliderCounter;

	static int displayingMenu;
	static int menuLevel;
	static int addButton();
	static int findButtonInPoint(int i_posX, int i_posY);
	static int addSlider();
	static int findSliderInPoint(int i_posX, int i_posY);
	static int menuButtonCountL2;
	static int menuButtonCountL3;

	static void displayMenu(int level);
	static void buttonCallback(int id, sf::RenderWindow &winHandle);
	static void buttonHoverover(sf::RenderWindow &winHandle);

	static void displayGameMenu();
	static void displayLoadModuleMenu();
	static void displayLoadSavePointMenu(bool save = false);
	static void displaySettingsMenu();

	static void clearButtons(bool removeTimers);
};