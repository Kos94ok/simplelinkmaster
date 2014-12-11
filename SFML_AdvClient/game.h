
#include "define.h"

class image
{
public:
	std::wstring ID;
	//sf::Texture tex;
	int tex;
	bool usingAbsPos;
	bool usingAbsSize;
	float posAbsX, posAbsY, sizeAbsX, sizeAbsY;
	float posRelX, posRelY, sizeRelX, sizeRelY;
	bool fadeBack, toFadeBack;
	float fadeCur, fadeOut, fadeMax, toFadeMax, delayTimer, toDelayTimer;

	bool inverseX;
	bool inverseY;
	int priority;
	float lifespan;
	float movingAngle;
	int movingSpeed;

	bool isEffect;
	int effectSpawnTimer;
	int effectFrontLength;
	float effectAngleMin;
	float effectAngleMax;
	float effectDensity;
	int effectSpeed;
	float effectSpawnPeriod;
	float effectLifespan;

	void paint(sf::RenderWindow &winHandle);
};

class game
{
public:
	static bool creditsMode;
	static bool isModuleLoaded;

	static int maxPriority;
	static int currentDialogInfo;
	
	static std::wstring folder;
	static sf::Music mainSound;
	static sf::Music bgMusic[16];
	static std::wstring bgMusicName[16];
	static int bgMusicFadeTime[16];
	static float bgMusicMaxVolume[16];
	static sf::Music voiceOver;
	static std::wstring voiceOverName;
	static int voiceOverFadeTime;
	static float voiceOverMaxVolume;
	static int displayImageCounter;
	static image displayImages[IMAGE_LIMIT];

	static void removeImage(std::wstring imageId);
	static void execDialogImage(int id);
	static void execDialogSound(int id);
	static void loadGameTextures();

	static void fullClearUp();
	static void loadModuleFull(std::wstring file, bool decode = false);

	static void createSavePoint(int slot);
	static void loadSavePoint(int slot);
};

class logic
{
public:
	static void replaceDecimal(std::wstring &str, std::wstring from = L".", std::wstring to = L",");
	static bool checkCondition(std::wstring exp);
	static bool checkMultiCondition(int nextDlg);
	static void parseActions(int id);
	static float advanceValue(float input, float advance, int expType);
	static float wtof(std::wstring &str);
	static bool isActionHidden(int id);
	static void activateTimers();
	static void activateMenuData();
};

class gametime
{
public:
	static int hours;
	static int minutes;
	static int seconds;
	static int millisec;
};