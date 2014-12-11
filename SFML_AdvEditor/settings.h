
#include "define.h"

class settings
{
public:
	static int maxUndoPoints;
	static bool autoCreateDirectories;
	// Colors
	static sf::Vector3i dialogInfoColor;
	static sf::Vector3i dialogActionColor;
	static sf::Vector3i dialogTeleportColor;
	static sf::Vector3i dialogVariableColor;
	static sf::Vector3i dialogConditionColor;
	static sf::Vector3i dialogImageColor;
	static sf::Vector3i dialogSoundColor;
	static sf::Vector3i dialogInfoColorSel;
	static sf::Vector3i dialogActionColorSel;
	static sf::Vector3i dialogTeleportColorSel;
	static sf::Vector3i dialogVariableColorSel;
	static sf::Vector3i dialogConditionColorSel;
	static sf::Vector3i dialogImageColorSel;
	static sf::Vector3i dialogSoundColorSel;

	static void load();
	static void save();
};