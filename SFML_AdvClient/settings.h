
#include "define.h"

class settings
{
public:
	static void load_customUI();
	static void load();
	static void save();

	static int lang;
	static bool forceTexturePreload;
	static bool forceTextureClearUp;

	static float volMaster;
	static float volSound;
	static float volMusic;
	static float volVoice;
	static void updateMusicVolume();

	// Compatibility
	static bool autoCreateDirectories;
};