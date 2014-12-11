
#include "main.h"

void settings::load()
{
	LPCWSTR filename = L".\\editor.ini";

	// Display settings
	camera::fullscreen = GetPrivateProfileInt(L"Display", L"fullscreen", 0, filename);
	camera::borderless = GetPrivateProfileInt(L"Display", L"borderless", 0, filename);
	camera::resolutionX = GetPrivateProfileInt(L"Display", L"resolutionX", 1024, filename);
	camera::resolutionY = GetPrivateProfileInt(L"Display", L"resolutionY", 768, filename);
	// Functional settings
	settings::maxUndoPoints = GetPrivateProfileInt(L"User Interface", L"maxUndoPoints", 50, filename);
	settings::autoCreateDirectories = GetPrivateProfileInt(L"User Interface", L"autoCreateDirectories", 1, filename);

	// Color codes
	settings::dialogInfoColor.x = GetPrivateProfileInt(L"Color codes", L"dialogInfo_R", 0, filename);
	settings::dialogInfoColor.y = GetPrivateProfileInt(L"Color codes", L"dialogInfo_G", 220, filename);
	settings::dialogInfoColor.z = GetPrivateProfileInt(L"Color codes", L"dialogInfo_B", 220, filename);
	settings::dialogActionColor.x = GetPrivateProfileInt(L"Color codes", L"dialogAction_R", 200, filename);
	settings::dialogActionColor.y = GetPrivateProfileInt(L"Color codes", L"dialogAction_G", 70, filename);
	settings::dialogActionColor.z = GetPrivateProfileInt(L"Color codes", L"dialogAction_B", 200, filename);
	settings::dialogTeleportColor.x = GetPrivateProfileInt(L"Color codes", L"dialogTeleport_R", 80, filename);
	settings::dialogTeleportColor.y = GetPrivateProfileInt(L"Color codes", L"dialogTeleport_G", 80, filename);
	settings::dialogTeleportColor.z = GetPrivateProfileInt(L"Color codes", L"dialogTeleport_B", 255, filename);
	settings::dialogVariableColor.x = GetPrivateProfileInt(L"Color codes", L"dialogVariable_R", 200, filename);
	settings::dialogVariableColor.y = GetPrivateProfileInt(L"Color codes", L"dialogVariable_G", 200, filename);
	settings::dialogVariableColor.z = GetPrivateProfileInt(L"Color codes", L"dialogVariable_B", 200, filename);
	settings::dialogConditionColor.x = GetPrivateProfileInt(L"Color codes", L"dialogCondition_R", 255, filename);
	settings::dialogConditionColor.y = GetPrivateProfileInt(L"Color codes", L"dialogCondition_G", 255, filename);
	settings::dialogConditionColor.z = GetPrivateProfileInt(L"Color codes", L"dialogCondition_B", 50, filename);
	settings::dialogImageColor.x = GetPrivateProfileInt(L"Color codes", L"dialogImage_R", 75, filename);
	settings::dialogImageColor.y = GetPrivateProfileInt(L"Color codes", L"dialogImage_G", 200, filename);
	settings::dialogImageColor.z = GetPrivateProfileInt(L"Color codes", L"dialogImage_B", 100, filename);
	settings::dialogSoundColor.x = GetPrivateProfileInt(L"Color codes", L"dialogSound_R", 255, filename);
	settings::dialogSoundColor.y = GetPrivateProfileInt(L"Color codes", L"dialogSound_G", 128, filename);
	settings::dialogSoundColor.z = GetPrivateProfileInt(L"Color codes", L"dialogSound_B", 0, filename);

	settings::dialogInfoColorSel.x = GetPrivateProfileInt(L"Color codes", L"dialogInfoSel_R", 0, filename);
	settings::dialogInfoColorSel.y = GetPrivateProfileInt(L"Color codes", L"dialogInfoSel_G", 180, filename);
	settings::dialogInfoColorSel.z = GetPrivateProfileInt(L"Color codes", L"dialogInfoSel_B", 180, filename);
	settings::dialogActionColorSel.x = GetPrivateProfileInt(L"Color codes", L"dialogActionSel_R", 150, filename);
	settings::dialogActionColorSel.y = GetPrivateProfileInt(L"Color codes", L"dialogActionSel_G", 50, filename);
	settings::dialogActionColorSel.z = GetPrivateProfileInt(L"Color codes", L"dialogActionSel_B", 150, filename);
	settings::dialogTeleportColorSel.x = GetPrivateProfileInt(L"Color codes", L"dialogTeleportSel_R", 80, filename);
	settings::dialogTeleportColorSel.y = GetPrivateProfileInt(L"Color codes", L"dialogTeleportSel_G", 80, filename);
	settings::dialogTeleportColorSel.z = GetPrivateProfileInt(L"Color codes", L"dialogTeleportSel_B", 200, filename);
	settings::dialogVariableColorSel.x = GetPrivateProfileInt(L"Color codes", L"dialogVariableSel_R", 170, filename);
	settings::dialogVariableColorSel.y = GetPrivateProfileInt(L"Color codes", L"dialogVariableSel_G", 170, filename);
	settings::dialogVariableColorSel.z = GetPrivateProfileInt(L"Color codes", L"dialogVariableSel_B", 170, filename);
	settings::dialogConditionColorSel.x = GetPrivateProfileInt(L"Color codes", L"dialogConditionSel_R", 200, filename);
	settings::dialogConditionColorSel.y = GetPrivateProfileInt(L"Color codes", L"dialogConditionSel_G", 200, filename);
	settings::dialogConditionColorSel.z = GetPrivateProfileInt(L"Color codes", L"dialogConditionSel_B", 50, filename);
	settings::dialogImageColorSel.x = GetPrivateProfileInt(L"Color codes", L"dialogImageSel_R", 50, filename);
	settings::dialogImageColorSel.y = GetPrivateProfileInt(L"Color codes", L"dialogImageSel_G", 150, filename);
	settings::dialogImageColorSel.z = GetPrivateProfileInt(L"Color codes", L"dialogImageSel_B", 75, filename);
	settings::dialogSoundColorSel.x = GetPrivateProfileInt(L"Color codes", L"dialogSoundSel_R", 200, filename);
	settings::dialogSoundColorSel.y = GetPrivateProfileInt(L"Color codes", L"dialogSoundSel_G", 80, filename);
	settings::dialogSoundColorSel.z = GetPrivateProfileInt(L"Color codes", L"dialogSoundSel_B", 0, filename);
}