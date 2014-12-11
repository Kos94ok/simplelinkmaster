
#include "main.h"

void saveModule(std::wstring path, bool createDir, bool encode)
{
	std::wstring buf;
	dialogInfo info;
	// Opening file
	std::wofstream file;
	file.open(path, std::ios::trunc);
	if (!file.good()) { printf("[saveModule]: Can not open the file. Returning.\n");		return; }
	// Creating a header
	file << gl_dialogInfoCounter << std::endl;
	// Amount of markers to read
	file << 2 << std::endl;
	file << dialogInfo::entryPoint << std::endl;
	file << dialogInfo::bsodPoint << std::endl;
	// For each object...
	for (int i = 0; i < gl_dialogInfoCounter; i++)
	{
		info = gl_dialogInfo[i];
		if (encode) { encodeDialogInfo(info); }
		// Title
		file << info.e_boxTitle << std::endl;
		// Type
		file << info.type << std::endl;
		// Editor-only data
		file << info.e_boxSizeX << std::endl;
		file << info.e_boxSizeY << std::endl;
		file << info.e_boxPosX << std::endl;
		file << info.e_boxPosY << std::endl;
		// Descriptions
		file << info.g_descriptionStringsUsed << std::endl;
		for (int d = 0; d < gl_dialogInfo[i].g_descriptionStringsUsed; d++)
		{
			file << info.g_descriptionText[d] << std::endl;
		}
		// Hooks
		file << info.hook_amount << std::endl;
		for (int d = 0; d < info.hook_amount; d++)
		{
			file << info.hook_actionId[d] << std::endl;
			file << info.e_hook_pointAposX[d] << std::endl;
			file << info.e_hook_pointAposY[d] << std::endl;
			file << info.e_hook_pointBposX[d] << std::endl;
			file << info.e_hook_pointBposY[d] << std::endl;
		}
	}
	// Closing the file
	file.close();
	// Creating a directory for the data
	if (createDir && settings::autoCreateDirectories)
	{
		// Main dir
		buf = path.substr(0, path.length() - 4);					CreateDirectory(buf.c_str(), 0);
		// Copying customUI.ini
		buf += L"\\customUI.ini";
		CopyFile(L"Modules\\z_default_customUI.ini", buf.c_str(), true);
		// Images
		buf = path.substr(0, path.length() - 4) + L"\\Images";		CreateDirectory(buf.c_str(), 0);
		// Sounds
		buf = path.substr(0, path.length() - 4) + L"\\Sounds";		CreateDirectory(buf.c_str(), 0);
	}
	// Message to the console
	printf("[saveModule]: Module saved successfully!\n");
}

void loadModule(std::wstring path, bool decode)
{
	int markersSaved = 0;
	std::wstring buf;
	// Clearing everything
	clearModule();
	// Opening file
	std::wifstream file;
	file.open(path);
	if (!file.good()) { printf("[loadModule]: File not found. Returning.\n");	return; }
	// Reading a header
	std::getline(file, buf);		std::wstringstream(buf) >> gl_dialogInfoCounter;
	std::getline(file, buf);		std::wstringstream(buf) >> markersSaved;
	if (markersSaved >= 1) { std::getline(file, buf);	std::wstringstream(buf) >> dialogInfo::entryPoint; }
	if (markersSaved >= 2) { std::getline(file, buf);	std::wstringstream(buf) >> dialogInfo::bsodPoint; }
	// For each object
	for (int i = 0; i < gl_dialogInfoCounter; i++)
	{
		gl_dialogInfo[i].isValid = true;
		// Title
		std::getline(file, buf);		gl_dialogInfo[i].e_boxTitle = buf;
		// Type
		std::getline(file, buf);		std::wstringstream(buf) >> gl_dialogInfo[i].type;
		// Editor-only data
		std::getline(file, buf);		std::wstringstream(buf) >> gl_dialogInfo[i].e_boxSizeX;
		std::getline(file, buf);		std::wstringstream(buf) >> gl_dialogInfo[i].e_boxSizeY;
		std::getline(file, buf);		std::wstringstream(buf) >> gl_dialogInfo[i].e_boxPosX;
		std::getline(file, buf);		std::wstringstream(buf) >> gl_dialogInfo[i].e_boxPosY;
		// Descriptions
		std::getline(file, buf);		std::wstringstream(buf) >> gl_dialogInfo[i].g_descriptionStringsUsed;
		for (int d = 0; d < gl_dialogInfo[i].g_descriptionStringsUsed; d++)
		{
			std::getline(file, buf);	gl_dialogInfo[i].g_descriptionText[d] = buf;
		}
		// Variable starting value
		if (gl_dialogInfo[i].type == DIALOGTYPE_VARIABLE) { buf = gl_dialogInfo[i].g_descriptionText[0];	std::wstringstream(buf) >> gl_dialogInfo[i].var_value; }
		// Hooks
		std::getline(file, buf);	std::wstringstream(buf) >> gl_dialogInfo[i].hook_amount;
		for (int d = 0; d < gl_dialogInfo[i].hook_amount; d++)
		{
			std::getline(file, buf);		std::wstringstream(buf) >> gl_dialogInfo[i].hook_actionId[d];
			std::getline(file, buf);		std::wstringstream(buf) >> gl_dialogInfo[i].e_hook_pointAposX[d];
			std::getline(file, buf);		std::wstringstream(buf) >> gl_dialogInfo[i].e_hook_pointAposY[d];
			std::getline(file, buf);		std::wstringstream(buf) >> gl_dialogInfo[i].e_hook_pointBposX[d];
			std::getline(file, buf);		std::wstringstream(buf) >> gl_dialogInfo[i].e_hook_pointBposY[d];
		}
		if (decode) { decodeDialogInfo(gl_dialogInfo[i]); }
		// Rebuild description
		gl_dialogInfo[i].g_descrLenAdjust();
		gl_dialogInfo[i].e_updateDrawInfo();
	}
	// Updating the visibility
	dialogInfo::updateVisibility();
	// Closing the file
	file.close();
	// Message to the console
	printf("[loadModule]: Module loaded successfully!\n");
}

void getModuleName(std::wstring path, std::wstring &target)
{
	int infoCounter = 0, markersSaved = 0, entryPoint = 0, descrAmount = 0, hookAmount = 0;
	std::wstring buf;
	// Opening file
	std::wifstream file;
	file.open(path);
	if (!file.good()) { return; }
	// Reading a header
	std::getline(file, buf);		std::wstringstream(buf) >> infoCounter;
	std::getline(file, buf);		std::wstringstream(buf) >> markersSaved;
	if (markersSaved >= 1) { std::getline(file, buf);	std::wstringstream(buf) >> entryPoint; }
	if (markersSaved >= 2) { std::getline(file, buf); }
	// For each object
	for (int i = 0; i < infoCounter; i++)
	{
		// Title
		std::getline(file, buf);
		if (i == entryPoint)
		{
			target = buf;
			file.close();
			return;
		}
		// Skipping next 5 lines
		for (int d = 0; d < 5; d++) { std::getline(file, buf); }
		// Descriptions
		std::getline(file, buf);		std::wstringstream(buf) >> descrAmount;
		for (int d = 0; d < descrAmount; d++) { std::getline(file, buf); }
		// Hooks
		std::getline(file, buf);		std::wstringstream(buf) >> hookAmount;
		for (int d = 0; d < hookAmount * 5; d++) { std::getline(file, buf); }
	}
	// Closing the file
	file.close();
}

void clearModule()
{
	dialogInfo::entryPoint = -1;
	for (int i = 0; i < gl_dialogInfoCounter; i++)
	{
		gl_dialogInfo[i].isValid = false;
		gl_dialogInfo[i].hook_amount = 0;
		gl_dialogInfo[i].g_descriptionStringsUsed = 0;
	}
}

void encodeDialogInfo(dialogInfo &target)
{
	wchar_t rChar;
	std::wstring wStr, newString = L"";

	// Title
	for (int i = 0; i < target.e_boxTitle.length(); i++)
	{
		rChar = target.e_boxTitle[i];
		rChar = rChar + i * 2 + 150;
		wStr = std::to_wstring((_Longlong)rChar);
		while (wStr.length() < 4)
		{
			wStr = L"0" + wStr;
		}
		newString += wStr;
	}
	target.e_boxTitle = newString;

	// Description
	for (int y = 0; y < target.g_descriptionStringsUsed; y++)
	{
		newString = L"";
		for (int i = 0; i < target.g_descriptionText[y].length(); i++)
		{
			rChar = target.g_descriptionText[y][i];
			rChar = rChar + i * 2 + 150;
			wStr = std::to_wstring((_Longlong)rChar);
			while (wStr.length() < 4)
			{
				wStr = L"0" + wStr;
			}
			newString += wStr;
		}
		target.g_descriptionText[y] = newString;
	}
}

void decodeDialogInfo(dialogInfo &target)
{
	int value;
	wchar_t wChar;
	std::wstring wStr, newString = L"";

	// Title
	for (int i = 0; i < target.e_boxTitle.length(); i += 4)
	{
		wStr = target.e_boxTitle.substr(i, 4);
		std::wstringstream(wStr) >> value;
		value -= i / 2 + 150;
		wChar = (wchar_t)value;
		newString += wChar;
	}
	target.e_boxTitle = newString;

	// Description
	for (int y = 0; y < target.g_descriptionStringsUsed; y++)
	{
		newString = L"";
		for (int i = 0; i < target.g_descriptionText[y].length(); i += 4)
		{
			wStr = target.g_descriptionText[y].substr(i, 4);
			std::wstringstream(wStr) >> value;
			value -= i / 2 + 150;
			wChar = (wchar_t)value;
			newString += wChar;
		}
		target.g_descriptionText[y] = newString;
	}
}