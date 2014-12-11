
class button
{
public:
	bool hovered;
	bool textCenter;
	int texID;
	int action;
	int nextMenu;
	int posX;
	int posY;
	int sizeX;
	int sizeY;
	std::wstring text;

	int g_corDialogAction;
	int g_nextDialogInfoCounter;
	int g_nextDialogInfo[LINK_LIMIT];

	void init();
	void move(int newX, int newY);
	void remove();
};

class slider
{
public:
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
	static int lastMenuLevel;
	static button btn[64];
	static int buttonCounter;
	static int dialogActionCounter;
	static slider sld[64];
	static int sliderCounter;

	static int menuLevel;
	static int addButton();
	static int findButtonInPoint(int i_posX, int i_posY);

	static int displayingMenu;
	static void displayMenu(int level);
	static void buttonCallback(int id, sf::RenderWindow &winHandle);
	static void buttonHoverover(sf::RenderWindow &winHandle);
	static void dialogHoverover(sf::RenderWindow &winHandle);

	static void menuClearModule();
	static void menuLoadModule(bool decode = false);
	static void menuSaveModule(bool encode = false);
	static void menuCreateDialog(int type, sf::RenderWindow &winHandle);

	static void copyObjects(sf::RenderWindow &winHandle);
	static void deleteObjects();
	static void quickTest(sf::RenderWindow &winHandle);
	static void pasteText(sf::RenderWindow &winHandle);
};

class myUndo
{
public:
	static int currentBackup;
	static bool objectMoved;
	static bool undoChain;

	static void createBackupPoint();
	static void moveToNextBackup();
	static void moveToPrevBackup();
	static void clearBackupPoints(int start);
};

class logic
{
public:
	static void replaceDecimal(std::wstring &str, std::wstring from, std::wstring to);
	static float wtof(std::wstring &str);
};