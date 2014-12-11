
#include "main.h"

void settings::load()
{
	LPWSTR buf = new wchar_t[64];
	LPCWSTR filename = L".\\client.ini";

	// Display settings
	camera::fullscreen = GetPrivateProfileInt(L"Display", L"fullscreen", 0, filename);
	camera::borderless = GetPrivateProfileInt(L"Display", L"borderless", 0, filename);
	camera::resolutionX = GetPrivateProfileInt(L"Display", L"resolutionX", 1024, filename);
	camera::resolutionY = GetPrivateProfileInt(L"Display", L"resolutionY", 768, filename);
	// Gameplay settings
	settings::forceTexturePreload = GetPrivateProfileInt(L"Gameplay", L"forceTexturePreload", 1, filename);
	settings::forceTextureClearUp = GetPrivateProfileInt(L"Gameplay", L"forceTextureClearUp", 1, filename);
	// Audio settings
	settings::volMaster = (float)GetPrivateProfileInt(L"Audio", L"masterVolume", 50, filename) / 100.00f;
	settings::volSound = (float)GetPrivateProfileInt(L"Audio", L"soundVolume", 50, filename) / 100.00f;
	settings::volMusic = (float)GetPrivateProfileInt(L"Audio", L"musicVolume", 50, filename) / 100.00f;
	settings::volVoice = (float)GetPrivateProfileInt(L"Audio", L"voiceVolume", 50, filename) / 100.00f;

	// General settings
	filename = L".\\general.ini";
	GetPrivateProfileString(L"General", L"Language", L"english", buf, 64, filename);
	if (wcscmp(buf, L"english") == 0) { settings::lang = LANG_ENGLISH; }
	else if (wcscmp(buf, L"russian") == 0) { settings::lang = LANG_RUSSIAN; }
}

void settings::save()
{
	LPWSTR buf = new wchar_t[64];
	LPCWSTR filename = L".\\client.ini";

	// Audio settings
	wsprintf(buf, L" %i", a_math::round(settings::volMaster * 100.00f));		WritePrivateProfileString(L"Audio", L"masterVolume", buf, filename);
	wsprintf(buf, L" %i", a_math::round(settings::volSound * 100.00f));		WritePrivateProfileString(L"Audio", L"soundVolume", buf, filename);
	wsprintf(buf, L" %i", a_math::round(settings::volMusic * 100.00f));		WritePrivateProfileString(L"Audio", L"musicVolume", buf, filename);
	wsprintf(buf, L" %i", a_math::round(settings::volVoice * 100.00f));		WritePrivateProfileString(L"Audio", L"voiceVolume", buf, filename);
}

void settings::load_customUI()
{
	wchar_t *buf = new wchar_t[64];
	std::wstring wbuf;
	std::wstring path = L".\\Modules\\", buf1 = L"\\customUI.ini";
	path = path + game::folder + buf1;
	LPCWSTR filename = path.c_str();

	UI::custom_hideOverlay = GetPrivateProfileInt(L"Custom UI", L"hideOverlay", 0, filename);
	GetPrivateProfileString(L"Custom UI", L"textOffsetX", L"10", buf, 64, filename);			UI::custom_textOffsetX = logic::wtof(std::wstring(buf));
	GetPrivateProfileString(L"Custom UI", L"textOffsetY", L"5", buf, 64, filename);				UI::custom_textOffsetY = logic::wtof(std::wstring(buf));
	UI::custom_textOffsetRelative = GetPrivateProfileInt(L"Custom UI", L"textOffsetRelative", 0, filename);
	GetPrivateProfileString(L"Custom UI", L"textMaxLength", L"-1", buf, 64, filename);			UI::custom_textMaxLength = logic::wtof(std::wstring(buf));
	UI::custom_textMaxLengthRel = GetPrivateProfileInt(L"Custom UI", L"textMaxLengthRel", 0, filename);
	UI::custom_textLineSpacing = GetPrivateProfileInt(L"Custom UI", L"textLineSpacing", 8, filename);
	UI::custom_textCharSize = GetPrivateProfileInt(L"Custom UI", L"textCharSize", 24, filename);

	GetPrivateProfileString(L"Custom UI", L"actionOffsetX", L"15", buf, 64, filename);			UI::custom_actionOffsetX = logic::wtof(std::wstring(buf));
	GetPrivateProfileString(L"Custom UI", L"actionOffsetY", L"50", buf, 64, filename);			UI::custom_actionOffsetY = logic::wtof(std::wstring(buf));
	UI::custom_actionOffsetRelative = GetPrivateProfileInt(L"Custom UI", L"actionOffsetRelative", 0, filename);
	UI::custom_actionOffsetAnchorTop = GetPrivateProfileInt(L"Custom UI", L"actionOffsetAnchorTop", 0, filename);
	GetPrivateProfileString(L"Custom UI", L"actionSelLength", L"-1", buf, 64, filename);			UI::custom_actionSelLength = logic::wtof(std::wstring(buf));
	UI::custom_actionSelLengthRel = GetPrivateProfileInt(L"Custom UI", L"actionSelLengthRel", 0, filename);
	UI::custom_actionLineSpacing = GetPrivateProfileInt(L"Custom UI", L"actionLineSpacing", 5, filename);
	UI::custom_actionCharSize = GetPrivateProfileInt(L"Custom UI", L"actionCharSize", 24, filename);
	UI::custom_actionSizeY = GetPrivateProfileInt(L"Custom UI", L"actionSizeY", 40, filename);
	UI::custom_actionTextOffsetY = GetPrivateProfileInt(L"Custom UI", L"actionTextOffsetY", 4, filename);

	UI::custom_allowScreenContinue = GetPrivateProfileInt(L"Custom UI", L"allowScreenContinue", 0, filename);
	UI::custom_hideContinueButton = GetPrivateProfileInt(L"Custom UI", L"hideContinueButton", 0, filename);
	UI::custom_fancyPrintAllowed = GetPrivateProfileInt(L"Custom UI", L"fancyPrintAllowed", 0, filename);
	GetPrivateProfileString(L"Custom UI", L"fancyPrintDelay", L"0", buf, 64, filename);		UI::custom_fancyPrintDelay = logic::wtof(std::wstring(buf));
}

void settings::updateMusicVolume()
{
	for (int i = 0; i < 16; i++)
	{
		if (game::bgMusicFadeTime[i] <= 0)
		{
			game::bgMusic[i].setVolume(settings::volMusic * settings::volMaster);
		}
	}
}