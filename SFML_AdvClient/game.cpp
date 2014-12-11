
#include "main.h"

void game::loadGameTextures()
{
	std::wstring name, buf1 = L"\\Images\\", wbuf;
	for (int i = 0; i < gl_dialogInfoCounter; i++)
	{
		if (gl_dialogInfo[i].type == DIALOGTYPE_IMAGE)
		{
			name = gl_dialogInfo[i].g_descriptionText[0];
			// If not clearing
			if (name != L"clear" && name != L"stop")
			{
				gl_gameTexName[gl_gameTexCount] = name;
				name = L"Modules\\" + game::folder + buf1 + name;
				std::string a_name(name.begin(), name.end());
				gl_gameTexture[gl_gameTexCount].loadFromFile(a_name);
				gl_gameTexCount += 1;
			}
		}
	}
}

void game::execDialogImage(int id)
{
	std::wstring imageId = L"0";
	bool usingAbsPos = true, usingAbsSize = true;
	int imageAbsPosX = 0, imageAbsPosY = 0, imageAbsSizeX = 100, imageAbsSizeY = -1, imagePriority = 0;
	float imageRelPosX = 1.00f, imageRelPosY = 1.00f, imageRelSizeX = 0.10f, imageRelSizeY = -1;
	float fadeDelay = 0.00f, fadeVal = 0.00f;
	bool clear = false, inverseX = false, inverseY = false;
	std::wstring name, buf1 = L"\\Images\\", wbuf;
	// Effect parameters
	bool isEffect = false;
	int e_frontLength = 0;
	float e_angleMin = 0.00f, e_angleMax = 360.00f;
	float e_density = 1.00f;
	int e_speed = 1;
	float e_lifespan = 1.00f;
	float e_period = 1.00f;
	float e_delay = 0.00f;
	// Parsing name
	name = gl_dialogInfo[id].g_descriptionText[0];
	if (name == L"clear" || name == L"stop") { clear = true; }
	//name = L"Modules\\" + game::folder + buf1 + name;
	// Checking parameters
	for (int i = 1; i < gl_dialogInfo[id].g_descriptionStringsUsed; i++)
	{
		// ID
		if (gl_dialogInfo[id].g_descriptionText[i].find(L"ID ") != -1 || gl_dialogInfo[id].g_descriptionText[i].find(L"Id ") != -1 || gl_dialogInfo[id].g_descriptionText[i].find(L"id ") != -1)
		{
			imageId = gl_dialogInfo[id].g_descriptionText[i].substr(3);
		}
		// Position (Absolute)
		if (gl_dialogInfo[id].g_descriptionText[i].find(L"Pos ") != -1)
		{
			usingAbsPos = true;
			wbuf = gl_dialogInfo[id].g_descriptionText[i].substr(3, gl_dialogInfo[id].g_descriptionText[i].find(L";"));
			std::wstringstream(wbuf) >> imageAbsPosX;
			wbuf = gl_dialogInfo[id].g_descriptionText[i].substr(gl_dialogInfo[id].g_descriptionText[i].find(L";") + 1);
			std::wstringstream(wbuf) >> imageAbsPosY;
		}
		if (gl_dialogInfo[id].g_descriptionText[i].find(L"PosAbs") != -1)
		{
			usingAbsPos = true;
			wbuf = gl_dialogInfo[id].g_descriptionText[i].substr(6, gl_dialogInfo[id].g_descriptionText[i].find(L";"));
			std::wstringstream(wbuf) >> imageAbsPosX;
			wbuf = gl_dialogInfo[id].g_descriptionText[i].substr(gl_dialogInfo[id].g_descriptionText[i].find(L";") + 1);
			std::wstringstream(wbuf) >> imageAbsPosY;
		}
		// Position (Relative)
		if (gl_dialogInfo[id].g_descriptionText[i].find(L"PosRel") != -1)
		{
			usingAbsPos = false;
			wbuf = gl_dialogInfo[id].g_descriptionText[i].substr(6, gl_dialogInfo[id].g_descriptionText[i].find(L";"));
			imageRelPosX = logic::wtof(wbuf);
			wbuf = gl_dialogInfo[id].g_descriptionText[i].substr(gl_dialogInfo[id].g_descriptionText[i].find(L";") + 1);
			imageRelPosY = logic::wtof(wbuf);
		}
		// Size (Absolute)
		if (gl_dialogInfo[id].g_descriptionText[i].find(L"Size ") != -1)
		{
			usingAbsSize = true;
			wbuf = gl_dialogInfo[id].g_descriptionText[i].substr(4, gl_dialogInfo[id].g_descriptionText[i].find(L";"));
			std::wstringstream(wbuf) >> imageAbsSizeX;

			wbuf = gl_dialogInfo[id].g_descriptionText[i].substr(gl_dialogInfo[id].g_descriptionText[i].find(L";") + 1);
			std::wstringstream(wbuf) >> imageAbsSizeY;
		}
		if (gl_dialogInfo[id].g_descriptionText[i].find(L"SizeAbs") != -1)
		{
			usingAbsSize = true;
			wbuf = gl_dialogInfo[id].g_descriptionText[i].substr(7, gl_dialogInfo[id].g_descriptionText[i].find(L";"));
			std::wstringstream(wbuf) >> imageAbsSizeX;

			wbuf = gl_dialogInfo[id].g_descriptionText[i].substr(gl_dialogInfo[id].g_descriptionText[i].find(L";") + 1);
			std::wstringstream(wbuf) >> imageAbsSizeY;
		}
		// Size (Relative)
		if (gl_dialogInfo[id].g_descriptionText[i].find(L"SizeRel") != -1)
		{
			usingAbsSize = false;
			wbuf = gl_dialogInfo[id].g_descriptionText[i].substr(7, gl_dialogInfo[id].g_descriptionText[i].find(L";"));
			imageRelSizeX = logic::wtof(wbuf);
			
			wbuf = gl_dialogInfo[id].g_descriptionText[i].substr(gl_dialogInfo[id].g_descriptionText[i].find(L";") + 1);
			imageRelSizeY = logic::wtof(wbuf);
		}
		// Fade
		if (gl_dialogInfo[id].g_descriptionText[i].find(L"Fade") != -1)
		{
			wbuf = gl_dialogInfo[id].g_descriptionText[i].substr(4);
			fadeVal = logic::wtof(wbuf);
		}
		// FadeDelay
		if (gl_dialogInfo[id].g_descriptionText[i].find(L"Delay") != -1)
		{
			wbuf = gl_dialogInfo[id].g_descriptionText[i].substr(5);
			fadeDelay = logic::wtof(wbuf);
		}
		// Priority
		if (gl_dialogInfo[id].g_descriptionText[i].find(L"Priority") != -1)
		{
			wbuf = gl_dialogInfo[id].g_descriptionText[i].substr(8);
			std::wstringstream(wbuf) >> imagePriority;
			if (imagePriority > game::maxPriority) { game::maxPriority = imagePriority; }
		}
		// Inverse X
		if (gl_dialogInfo[id].g_descriptionText[i].find(L"Inverse X") != -1)
		{
			inverseX = true;
		}
		// Inverse Y
		if (gl_dialogInfo[id].g_descriptionText[i].find(L"Inverse Y") != -1)
		{
			inverseY = true;
		}
		// Effect parameters
		// Front (Absolute)
		if (gl_dialogInfo[id].g_descriptionText[i].find(L"e_Front ") != -1)
		{
			isEffect = true;
			wbuf = gl_dialogInfo[id].g_descriptionText[i].substr(7);
			std::wstringstream(wbuf) >> e_frontLength;
		}
		if (gl_dialogInfo[id].g_descriptionText[i].find(L"e_FrontAbs") != -1)
		{
			isEffect = true;
			wbuf = gl_dialogInfo[id].g_descriptionText[i].substr(10);
			std::wstringstream(wbuf) >> e_frontLength;
		}
		// Front (Relative to X)
		if (gl_dialogInfo[id].g_descriptionText[i].find(L"e_FrontRelX") != -1)
		{
			isEffect = true;
			wbuf = gl_dialogInfo[id].g_descriptionText[i].substr(11);
			e_frontLength = logic::wtof(wbuf) * camera::resolutionX;
		}
		// Front (Relative to Y)
		if (gl_dialogInfo[id].g_descriptionText[i].find(L"e_FrontRelY") != -1)
		{
			isEffect = true;
			wbuf = gl_dialogInfo[id].g_descriptionText[i].substr(11);
			e_frontLength = logic::wtof(wbuf) * camera::resolutionY;
		}
		// Angle
		if (gl_dialogInfo[id].g_descriptionText[i].find(L"e_Angle") != -1)
		{
			isEffect = true;
			wbuf = gl_dialogInfo[id].g_descriptionText[i].substr(7, gl_dialogInfo[id].g_descriptionText[i].find(L";"));
			e_angleMin = logic::wtof(wbuf);
			if (gl_dialogInfo[id].g_descriptionText[i].find(L";") != -1)
			{
				wbuf = gl_dialogInfo[id].g_descriptionText[i].substr(gl_dialogInfo[id].g_descriptionText[i].find(L";") + 1);
				e_angleMax = logic::wtof(wbuf);
			}
			else { e_angleMax = e_angleMin; }
		}
		// Density
		if (gl_dialogInfo[id].g_descriptionText[i].find(L"e_Density") != -1)
		{
			isEffect = true;
			wbuf = gl_dialogInfo[id].g_descriptionText[i].substr(9);
			e_density = logic::wtof(wbuf);
		}
		// Lifespan
		if (gl_dialogInfo[id].g_descriptionText[i].find(L"e_Lifespan") != -1)
		{
			isEffect = true;
			wbuf = gl_dialogInfo[id].g_descriptionText[i].substr(10);
			e_lifespan = logic::wtof(wbuf);
		}
		// Speed (Absolute)
		if (gl_dialogInfo[id].g_descriptionText[i].find(L"e_Speed") != -1)
		{
			isEffect = true;
			wbuf = gl_dialogInfo[id].g_descriptionText[i].substr(7);
			std::wstringstream(wbuf) >> e_speed;
		}
		// Period
		if (gl_dialogInfo[id].g_descriptionText[i].find(L"e_Period") != -1)
		{
			isEffect = true;
			wbuf = gl_dialogInfo[id].g_descriptionText[i].substr(8);
			e_period = logic::wtof(wbuf);
		}
		// Delay
		if (gl_dialogInfo[id].g_descriptionText[i].find(L"e_Delay") != -1)
		{
			isEffect = true;
			wbuf = gl_dialogInfo[id].g_descriptionText[i].substr(7);
			e_delay = logic::wtof(wbuf);
		}
	}
	if (!clear)
	{
		game::displayImages[game::displayImageCounter].ID = imageId;
		game::displayImages[game::displayImageCounter].tex = -1;
		game::displayImages[game::displayImageCounter].lifespan = -1;
		game::displayImages[game::displayImageCounter].effectSpawnTimer = 0;
		// Looking for the texture
		for (int i = 0; i < gl_gameTexCount; i++)
		{
			if (gl_gameTexName[i] == name) { game::displayImages[game::displayImageCounter].tex = i; i = gl_gameTexCount; }
		}
		// Texture not found - loading
		if (game::displayImages[game::displayImageCounter].tex == -1)
		{
			game::displayImages[game::displayImageCounter].tex = gl_gameTexCount;
			gl_gameTexName[gl_gameTexCount] = name;
			name = L"Modules\\" + game::folder + buf1 + name;
			std::string buf(name.begin(), name.end());
			gl_gameTexture[gl_gameTexCount].loadFromFile(buf);
			gl_gameTexCount += 1;
		}
		// Effect parameters
		game::displayImages[game::displayImageCounter].effectSpawnTimer = e_delay * 1000;
		game::displayImages[game::displayImageCounter].isEffect = isEffect;
		game::displayImages[game::displayImageCounter].effectSpeed = e_speed;
		game::displayImages[game::displayImageCounter].effectDensity = e_density;
		game::displayImages[game::displayImageCounter].effectLifespan = e_lifespan;
		game::displayImages[game::displayImageCounter].effectAngleMin = e_angleMin;
		game::displayImages[game::displayImageCounter].effectAngleMax = e_angleMax;
		game::displayImages[game::displayImageCounter].effectSpawnPeriod = e_period;
		game::displayImages[game::displayImageCounter].effectFrontLength = e_frontLength;
		// Relative size
		//float aspectRatio = gl_gameTexture[game::displayImages[game::displayImageCounter].tex].getSize().x * pow((float)gl_gameTexture[game::displayImages[game::displayImageCounter].tex].getSize().y, -1);
		float aspectRatio = (float)gl_gameTexture[game::displayImages[game::displayImageCounter].tex].getSize().x / (float)gl_gameTexture[game::displayImages[game::displayImageCounter].tex].getSize().y;
		if (aspectRatio != 0)
		{
			if (imageAbsSizeX < 0 && imageAbsSizeY > 0 && usingAbsSize) { imageAbsSizeX = imageAbsSizeY * aspectRatio; }
			else if (imageAbsSizeX < 0 && imageAbsSizeY > 0 && usingAbsSize) { imageAbsSizeY = imageAbsSizeX / aspectRatio; }
				
			if (imageRelSizeX < 0 && imageRelSizeY > 0 && !usingAbsSize) { imageRelSizeX = imageRelSizeY * aspectRatio; }
			else if (imageRelSizeY < 0 && imageRelSizeY > 0 && !usingAbsSize) { imageRelSizeY = imageRelSizeX / aspectRatio; }

			if ((imageAbsSizeX < 0 && imageAbsSizeY < 0) || (imageRelSizeX < 0 && imageRelSizeY < 0))
			{
				usingAbsSize = true;
				imageAbsSizeX = gl_gameTexture[game::displayImages[game::displayImageCounter].tex].getSize().x;
				imageAbsSizeY = gl_gameTexture[game::displayImages[game::displayImageCounter].tex].getSize().y;
			}
		}
		// Other parameters
		game::displayImages[game::displayImageCounter].posAbsX = imageAbsPosX;
		game::displayImages[game::displayImageCounter].posAbsY = imageAbsPosY;
		game::displayImages[game::displayImageCounter].sizeAbsX = imageAbsSizeX;
		game::displayImages[game::displayImageCounter].sizeAbsY = imageAbsSizeY;
		game::displayImages[game::displayImageCounter].posRelX = imageRelPosX;
		game::displayImages[game::displayImageCounter].posRelY = imageRelPosY;
		game::displayImages[game::displayImageCounter].sizeRelX = imageRelSizeX;
		game::displayImages[game::displayImageCounter].sizeRelY = imageRelSizeY;
		game::displayImages[game::displayImageCounter].usingAbsPos = usingAbsPos;
		game::displayImages[game::displayImageCounter].usingAbsSize = usingAbsSize;
		game::displayImages[game::displayImageCounter].priority = imagePriority;
		game::displayImages[game::displayImageCounter].fadeCur = 0.00f;
		game::displayImages[game::displayImageCounter].fadeBack = false;
		game::displayImages[game::displayImageCounter].fadeMax = fadeVal;
		game::displayImages[game::displayImageCounter].delayTimer = fadeDelay;
		game::displayImages[game::displayImageCounter].inverseX = inverseX;
		game::displayImages[game::displayImageCounter].inverseY = inverseY;
		game::displayImageCounter += 1;
	}
	else
	{
		if (fadeVal == 0.00f)
		{
			game::removeImage(imageId);
		}
		else
		{
			for (int i = 0; i < game::displayImageCounter; i++)
			{
				if (game::displayImages[i].ID == imageId)
				{
					// No delay
					if (fadeDelay == 0.00f || game::displayImages[i].fadeCur >= game::displayImages[i].fadeMax)
					{
						game::displayImages[i].fadeBack = true;
						game::displayImages[i].fadeCur = fadeVal;
						game::displayImages[i].fadeMax = fadeVal;
					}
					// Delay
					else
					{
						game::displayImages[i].toDelayTimer = fadeDelay;
						game::displayImages[i].toFadeBack = true;
						game::displayImages[i].toFadeMax = fadeVal;
					} 
				}
			}
		}
	}
}

void game::removeImage(std::wstring imageId)
{
	// Removing the image
	for (int i = 0; i < game::displayImageCounter; i++)
	{
		if (game::displayImages[i].ID == imageId)
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

void game::execDialogSound(int id)
{
	bool stop = false, isMusic = false, isVoice = false, isLoop = false;
	int musicChannel = 0;
	float volume = 100, fadeTime = -1.00f;
	std::wstring name, buf1 = L"\\Sounds\\", wbuf, clearName;
	// Parsing name
	name = gl_dialogInfo[id].g_descriptionText[0];
	clearName = name;
	if (name == L"stop" || name == L"clear") { stop = true; }
	name = L"Modules\\" + game::folder + buf1 + name;
	// Checking parameters
	for (int i = 1; i < gl_dialogInfo[id].g_descriptionStringsUsed; i++)
	{
		// Loop
		if (gl_dialogInfo[id].g_descriptionText[i].find(L"Loop") != -1) { isLoop = true; }
		// Music channel
		if (gl_dialogInfo[id].g_descriptionText[i].find(L"Music") != -1)
		{
			isMusic = true;
			isVoice = false;
			if (gl_dialogInfo[id].g_descriptionText[i].length() > 5)
			{
				wbuf = gl_dialogInfo[id].g_descriptionText[i].substr(5);
				std::wstringstream(wbuf) >> musicChannel;
			}
		}
		// Voiceover
		if (gl_dialogInfo[id].g_descriptionText[i].find(L"Voice") != -1)
		{
			isVoice = true;
			isMusic = false;
		}
		// Volume
		if (gl_dialogInfo[id].g_descriptionText[i].find(L"Volume") != -1)
		{
			wbuf = gl_dialogInfo[id].g_descriptionText[i].substr(6);
			std::wstringstream(wbuf) >> volume;
		}
		// Fade
		if (gl_dialogInfo[id].g_descriptionText[i].find(L"Fade") != -1)
		{
			wbuf = gl_dialogInfo[id].g_descriptionText[i].substr(4);
			fadeTime = logic::wtof(wbuf);
		}
	}
	if (!stop)
	{
		// Sound
		if (!isMusic && !isVoice)
		{
			std::string buf(name.begin(), name.end());
			game::mainSound.openFromFile(buf);
			game::mainSound.setVolume(volume * settings::volSound * settings::volMaster);
			game::mainSound.play();
		}
		// Music
		else if (isMusic)
		{
			std::string buf(name.begin(), name.end());
			game::bgMusic[musicChannel].openFromFile(buf);
			game::bgMusicMaxVolume[musicChannel] = volume;
			game::bgMusicFadeTime[musicChannel] = fadeTime * 1000;
			game::bgMusic[musicChannel].setVolume(volume * settings::volMusic * settings::volMaster);
			if (fadeTime > 0) { game::bgMusic[musicChannel].setVolume(0.00f); }
			game::bgMusic[musicChannel].setLoop(isLoop);
			game::bgMusic[musicChannel].play();
			game::bgMusicName[musicChannel] = clearName;
		}
		// Voice
		else if (isVoice)
		{
			std::string buf(name.begin(), name.end());
			game::voiceOver.openFromFile(buf);
			game::voiceOverMaxVolume = volume;
			game::voiceOverFadeTime = fadeTime * 1000;
			game::voiceOver.setVolume(volume * settings::volVoice * settings::volMaster);
			if (fadeTime > 0) { game::voiceOver.setVolume(0.00f); }
			game::voiceOver.play();
			game::voiceOverName = clearName;
		}
	}
	else
	{
		if (!isMusic && !isVoice) { game::mainSound.stop(); }
		else if (isMusic)
		{
			if (fadeTime > 0) { game::bgMusicMaxVolume[musicChannel] = 0.00f; game::bgMusicFadeTime[musicChannel] = fadeTime * 1000; }
			else { game::bgMusic[musicChannel].stop(); }
		}
		else if (isVoice)
		{
			if (fadeTime > 0) { game::voiceOverMaxVolume = 0.00f; game::voiceOverFadeTime = fadeTime * 1000; }
			else { game::voiceOver.stop(); }
		}
	}
}

bool logic::checkCondition(std::wstring exp)
{
	bool result = false;
	int varValueInt, expType = -1;
	std::wstring varName, varValue;
	// Parsing the string
	int pos = exp.find(L"==");
	if (pos != -1) { expType = 0; varName = exp.substr(0, pos - 1);	varValue = exp.substr(pos + 3); }
	else
	{
		pos = exp.find(L">=");
		if (pos != -1) { expType = 1; varName = exp.substr(0, pos - 1);	varValue = exp.substr(pos + 3); }
		else
		{
			pos = exp.find(L"<=");
			if (pos != -1) { expType = 2; varName = exp.substr(0, pos - 1);	varValue = exp.substr(pos + 3); }
			else
			{
				pos = exp.find(L">");
				if (pos != -1) { expType = 3; varName = exp.substr(0, pos - 1);	varValue = exp.substr(pos + 2); }
				else
				{
					pos = exp.find(L"<");
					if (pos != -1) { expType = 4; varName = exp.substr(0, pos - 1);	varValue = exp.substr(pos + 2); }
					else
					{
						pos = exp.find(L"!=");
						if (pos != -1) { expType = 5; varName = exp.substr(0, pos - 1);	varValue = exp.substr(pos + 3); }
					}
				}
			}
		}
	}
	// Checking if varValue is a variable
	bool variableFound = false;
	for (int i = 0; i < gl_dialogInfoCounter; i++)
	{
		if (gl_dialogInfo[i].type == DIALOGTYPE_VARIABLE && gl_dialogInfo[i].e_boxTitle == varValue)
		{
			variableFound = true;
			varValueInt = gl_dialogInfo[i].var_value;
		}
	}
	if (!variableFound) { std::wstringstream(varValue) >> varValueInt; }

	// Checking the condition
	for (int i = 0; i < gl_dialogInfoCounter; i++)
	{
		if (gl_dialogInfo[i].e_boxTitle == varName)
		{
			if ((expType == 0 && gl_dialogInfo[i].var_value == varValueInt) || (expType == 1 && gl_dialogInfo[i].var_value >= varValueInt)
				|| (expType == 2 && gl_dialogInfo[i].var_value <= varValueInt) || (expType == 3 && gl_dialogInfo[i].var_value > varValueInt)
				|| (expType == 4 && gl_dialogInfo[i].var_value < varValueInt) || (expType == 5 && gl_dialogInfo[i].var_value != varValueInt))
			{ 
				result = true;
			}
		}
	}

	return result;
}

bool logic::checkMultiCondition(int nextDlg)
{
	bool finalResult = true;
	bool invert = false;	bool expOr = false;
	bool result = false;	std::wstring exp;
	exp = gl_dialogInfo[nextDlg].g_descriptionText[0];
	
	if (exp.find(L"!") != -1) { invert = true; }
	if (exp.find(L"||") != -1) { expOr = true; }

	// Checking all the strings
	for (int a = 1; a < gl_dialogInfo[nextDlg].g_descriptionStringsUsed; a++)
	{
		result = logic::checkCondition(gl_dialogInfo[nextDlg].g_descriptionText[a]);
		if (!invert && !expOr && result == false) { finalResult = false; a = gl_dialogInfo[nextDlg].g_descriptionStringsUsed; }
		else if (!invert && expOr && result == true) { finalResult = true; a = gl_dialogInfo[nextDlg].g_descriptionStringsUsed; }
		else if (invert && !expOr && result == true) { finalResult = false; a = gl_dialogInfo[nextDlg].g_descriptionStringsUsed; }
		else if (invert && expOr && result == true) { finalResult = false; a = gl_dialogInfo[nextDlg].g_descriptionStringsUsed; }
	}

	return result;
}

void logic::replaceDecimal(std::wstring &str, std::wstring from, std::wstring to)
{
	int search;
	do
	{
		search = str.find(from);
		if (search != -1)
		{
			str.replace(search, 1, to);
		}
	}
	while (search != -1);
}

float logic::wtof(std::wstring &str)
{
	float pointResult = 0.00f, commaResult = 0.00f;
	std::wstring buf = str;
	logic::replaceDecimal(buf, L".", L",");
	std::wstringstream(buf) >> commaResult;
	logic::replaceDecimal(buf, L",", L".");
	std::wstringstream(buf) >> pointResult;

	if (abs(pointResult) > abs(commaResult)) { return pointResult; }
	else { return commaResult; }
}

void logic::parseActions(int id)
{
	if (gl_dialogInfo[id].g_descriptionStringsUsed < 1) { return; }
	bool result = false;
	int varValueInt, expType = -1;
	float varValueFloat;
	std::wstring varName, varValue, exp;

	for (int i = 1; i < gl_dialogInfo[id].g_descriptionStringsUsed; i++)
	{
		exp = gl_dialogInfo[id].g_descriptionText[i];
		// Parsing the string
		int pos = exp.find(L"set");
		if (pos != -1) { expType = 0; varName = exp.substr(0, pos - 1);	varValue = exp.substr(pos + 4); }
		else {
			pos = exp.find(L"add");
			if (pos != -1) { expType = 1; varName = exp.substr(0, pos - 1);	varValue = exp.substr(pos + 4); }
			else {
				pos = exp.find(L"sub");
				if (pos != -1) { expType = 2; varName = exp.substr(0, pos - 1);	varValue = exp.substr(pos + 4); }
				else {
					pos = exp.find(L"mul");
					if (pos != -1) { expType = 3; varName = exp.substr(0, pos - 1);	varValue = exp.substr(pos + 4); }
					else {
						pos = exp.find(L"div");
						if (pos != -1) { expType = 4; varName = exp.substr(0, pos - 1);	varValue = exp.substr(pos + 4); }
						else {
							pos = exp.find(L"=");
							if (pos != -1) { expType = 0; varName = exp.substr(0, pos - 1);	varValue = exp.substr(pos + 2); }
							else {
								pos = exp.find(L"+=");
								if (pos != -1) { expType = 1; varName = exp.substr(0, pos - 1);	varValue = exp.substr(pos + 3); }
								else {
									pos = exp.find(L"-=");
									if (pos != -1) { expType = 2; varName = exp.substr(0, pos - 1);	varValue = exp.substr(pos + 3); }
									else {
										pos = exp.find(L"*=");
										if (pos != -1) { expType = 3; varName = exp.substr(0, pos - 1);	varValue = exp.substr(pos + 3); }
										else {
											pos = exp.find(L"/=");
											if (pos != -1) { expType = 4; varName = exp.substr(0, pos - 1);	varValue = exp.substr(pos + 3); }
										}
									}
								}
							}
						}
					}
				}
			}
		}
		// Checking if varValue is a variable
		bool variableFound = false;
		for (int i = 0; i < gl_dialogInfoCounter; i++)
		{
			if (gl_dialogInfo[i].type == DIALOGTYPE_VARIABLE && gl_dialogInfo[i].e_boxTitle == varValue)
			{
				variableFound = true;
				varValueInt = gl_dialogInfo[i].var_value;
				varValueFloat = varValueInt;
			}
		}
		if (!variableFound) { varValueFloat = logic::wtof(varValue); varValueInt = varValueFloat; }

		// Searching for the variable
		if (varName == L"hideOverlay") { UI::custom_hideOverlay = logic::advanceValue(UI::custom_hideOverlay, varValueFloat, expType); }
		else if (varName == L"textOffsetX") { UI::custom_textOffsetX = logic::advanceValue(UI::custom_textOffsetX, varValueFloat, expType); }
		else if (varName == L"textOffsetY") { UI::custom_textOffsetY = logic::advanceValue(UI::custom_textOffsetY, varValueFloat, expType); }
		else if (varName == L"textOffsetRelative") { UI::custom_textOffsetRelative = logic::advanceValue(UI::custom_textOffsetRelative, varValueFloat, expType); }
		else if (varName == L"textMaxLength") { UI::custom_textMaxLength = logic::advanceValue(UI::custom_textMaxLength, varValueFloat, expType); }
		else if (varName == L"textMaxLengthRel") { UI::custom_textMaxLengthRel = logic::advanceValue(UI::custom_textMaxLengthRel, varValueFloat, expType); }
		else if (varName == L"textLineSpacing") { UI::custom_textLineSpacing = logic::advanceValue(UI::custom_textLineSpacing, varValueFloat, expType); }
		else if (varName == L"textCharSize") { UI::custom_textCharSize = logic::advanceValue(UI::custom_textCharSize, varValueFloat, expType); }
		else if (varName == L"actionOffsetX") { UI::custom_actionOffsetX = logic::advanceValue(UI::custom_actionOffsetX, varValueFloat, expType); }
		else if (varName == L"actionOffsetY") { UI::custom_actionOffsetY = logic::advanceValue(UI::custom_actionOffsetY, varValueFloat, expType); }
		else if (varName == L"actionOffsetRelative") { UI::custom_actionOffsetRelative = logic::advanceValue(UI::custom_actionOffsetRelative, varValueFloat, expType); }
		else if (varName == L"actionOffsetAnchorTop") { UI::custom_actionOffsetAnchorTop = logic::advanceValue(UI::custom_actionOffsetAnchorTop, varValueFloat, expType); }
		else if (varName == L"actionSelLength") { UI::custom_actionSelLength = logic::advanceValue(UI::custom_actionSelLength, varValueFloat, expType); }
		else if (varName == L"actionSelLengthRel") { UI::custom_actionSelLengthRel = logic::advanceValue(UI::custom_actionSelLengthRel, varValueFloat, expType); }
		else if (varName == L"actionLineSpacing") { UI::custom_actionLineSpacing = logic::advanceValue(UI::custom_actionLineSpacing, varValueFloat, expType); }
		else if (varName == L"actionCharSize") { UI::custom_actionCharSize = logic::advanceValue(UI::custom_actionCharSize, varValueFloat, expType); }
		else if (varName == L"actionSizeY") { UI::custom_actionSizeY = logic::advanceValue(UI::custom_actionSizeY, varValueFloat, expType); }
		else if (varName == L"actionTextOffsetY") { UI::custom_actionTextOffsetY = logic::advanceValue(UI::custom_actionTextOffsetY, varValueFloat, expType); }
		else if (varName == L"allowScreenContinue") { UI::custom_allowScreenContinue = logic::advanceValue(UI::custom_allowScreenContinue, varValueFloat, expType); }
		else if (varName == L"hideContinueButton") { UI::custom_hideContinueButton = logic::advanceValue(UI::custom_hideContinueButton, varValueFloat, expType); }
		else if (varName == L"fancyPrintAllowed") { UI::custom_fancyPrintAllowed = logic::advanceValue(UI::custom_fancyPrintAllowed, varValueFloat, expType); }
		else if (varName == L"fancyPrintDelay") { UI::custom_fancyPrintDelay = logic::advanceValue(UI::custom_fancyPrintDelay, varValueFloat, expType); }
		else
		{
			for (int a = 0; a < gl_dialogInfoCounter; a++)
			{
				if (gl_dialogInfo[a].e_boxTitle == varName)
				{
					gl_dialogInfo[a].var_value = logic::advanceValue(gl_dialogInfo[a].var_value, varValueFloat, expType);
					a = gl_dialogInfoCounter;
				}
			}
		}
	}
}

float logic::advanceValue(float input, float advance, int expType)
{
	if (expType == 0) { input = advance; }
	else if (expType == 1) { input += advance; }
	else if (expType == 2) { input -= advance; }
	else if (expType == 3) { input *= advance; }
	else if (expType == 4) { input /= advance; }

	return input;
}

void game::fullClearUp()
{
	game::displayImageCounter = 0;
	for (int i = 0; i < 16; i++) { game::bgMusicFadeTime[i] = 1000; game::bgMusicMaxVolume[i] = 0.00f; }
	//game::voiceOver.stop();
	game::voiceOverMaxVolume = 0.00f;	game::voiceOverFadeTime = 1000;
	game::mainSound.stop();
	UI::printDelayAmount = 0;
	UI::printDelayOver = false;
	UI::printDelayActive = 0.00f;
	gametime::hours = 0;	gametime::minutes = 0;	gametime::seconds = 0;	gametime::millisec = 0;
	if (settings::forceTextureClearUp) { gl_gameTexCount = 0; }
}

void game::loadModuleFull(std::wstring file, bool decode)
{
	std::wstring filepath = L"Modules\\" + file;
	clearModule();
	game::fullClearUp();
	game::folder = file.substr(0, file.length() - 4);
	settings::load_customUI();
	loadModule(filepath, decode);
	if (settings::forceTexturePreload) { game::loadGameTextures(); }
	if (dialogInfo::entryPoint == -1)
	{
		printf("[UI::buttonCallback]: Entry point not defined!\n");
		for (int i = 0; i < gl_dialogInfoCounter; i++) { if (gl_dialogInfo[i].type == DIALOGTYPE_INFO) { game::currentDialogInfo = i; }}
	}
	else { game::currentDialogInfo = dialogInfo::entryPoint; }
	game::isModuleLoaded = true;
}

void game::createSavePoint(int slot)
{
	int varCount = 0, imageCount = 0;
	int varValue[512];
	std::wstring varName[512];
	std::wstring path = L"Data\\Savefiles\\slot" + std::to_wstring((_Longlong)slot) + L".bin";
	// Creating the folder (just in case)
	CreateDirectory(L"Data", 0);
	CreateDirectory(L"Data\\Savefiles", 0);
	// Opening the file
	std::wofstream file;
	file.open(path, std::ios::trunc);
	// Searching for variables
	for (int i = 0; i < gl_dialogInfoCounter; i++)
	{
		if (gl_dialogInfo[i].type == DIALOGTYPE_VARIABLE)
		{
			varName[varCount] = gl_dialogInfo[i].e_boxTitle;
			varValue[varCount] = gl_dialogInfo[i].var_value;
			varCount += 1;
		}
	}
	
	// Checking images
	for (int i = 0; i < game::displayImageCounter; i++)
	{
		if (game::displayImages[i].lifespan < 0)
		{
			imageCount += 1;
		}
	}

	// Writing the data
		// Active file
	file << game::folder << std::endl;
		// Gametime
	file << gametime::hours << std::endl;
	file << gametime::minutes << std::endl;
	file << gametime::seconds << std::endl;
		// Current dialogInfo
	file << game::currentDialogInfo << std::endl;
		// Amount of variables
	file << varCount << std::endl;
		// Variable data
	for (int i = 0; i < varCount; i++)
	{
		file << varName[i] << std::endl;
		file << varValue[i] << std::endl;
	}
		// Amount of images
	file << imageCount << std::endl;
		// Image data
	for (int i = 0; i < game::displayImageCounter; i++)
	{
		if (game::displayImages[i].lifespan < 0)
		{
			file << game::displayImages[i].ID << std::endl;
			// Texture
			file << gl_gameTexName[game::displayImages[i].tex] << std::endl;
			// Other stuff
			file << game::displayImages[i].delayTimer << std::endl;
			file << game::displayImages[i].effectAngleMax << std::endl;
			file << game::displayImages[i].effectAngleMin << std::endl;
			file << game::displayImages[i].effectDensity << std::endl;
			file << game::displayImages[i].effectFrontLength << std::endl;
			file << game::displayImages[i].effectLifespan << std::endl;
			file << game::displayImages[i].effectSpawnPeriod << std::endl;
			file << game::displayImages[i].effectSpawnTimer << std::endl;
			file << game::displayImages[i].effectSpeed << std::endl;
			file << game::displayImages[i].fadeBack << std::endl;
			file << game::displayImages[i].fadeCur << std::endl;
			file << game::displayImages[i].fadeMax << std::endl;
			file << game::displayImages[i].fadeOut << std::endl;
			file << game::displayImages[i].isEffect << std::endl;
			file << game::displayImages[i].lifespan << std::endl;
			file << game::displayImages[i].movingAngle << std::endl;
			file << game::displayImages[i].movingSpeed << std::endl;
			file << game::displayImages[i].posAbsX << std::endl;
			file << game::displayImages[i].posAbsY << std::endl;
			file << game::displayImages[i].posRelX << std::endl;
			file << game::displayImages[i].posRelY << std::endl;
			file << game::displayImages[i].sizeAbsX << std::endl;
			file << game::displayImages[i].sizeAbsY << std::endl;
			file << game::displayImages[i].sizeRelX << std::endl;
			file << game::displayImages[i].sizeRelY << std::endl;
			file << game::displayImages[i].toDelayTimer << std::endl;
			file << game::displayImages[i].toFadeBack << std::endl;
			file << game::displayImages[i].toFadeMax << std::endl;
			file << game::displayImages[i].usingAbsPos << std::endl;
			file << game::displayImages[i].usingAbsSize << std::endl;
			file << game::displayImages[i].priority << std::endl;
			if (game::displayImages[i].priority > game::maxPriority) { game::maxPriority = game::displayImages[i].priority; }
		}
	}
		// Amount of music channels
	file << 16 << std::endl;
		// Music data
	for (int i = 0; i < 16; i++)
	{
		if (game::bgMusic[i].getStatus() == sf::Music::Playing && game::bgMusicMaxVolume[i] > 1.00f)
		{
			file << game::bgMusicName[i] << std::endl;
			file << game::bgMusic[i].getLoop() << std::endl;
			file << game::bgMusicMaxVolume[i] << std::endl;
		}
		else
		{
			file << "0" << std::endl;
		}
	}
		// Amount of other sound channels
	file << 1 << std::endl;
		// Voiceover channel
	if (game::voiceOver.getStatus() == sf::Music::Playing && game::voiceOverMaxVolume > 1.00f)
	{
		file << game::voiceOverName << std::endl;
		file << game::voiceOverMaxVolume << std::endl;
	}
	else { file << "0" << std::endl; }
		// Amount of interface status entries
	file << 22 << std::endl;
		// Interface status
	file << UI::custom_hideOverlay << std::endl;
	file << UI::custom_textOffsetX << std::endl;
	file << UI::custom_textOffsetY << std::endl;
	file << UI::custom_textOffsetRelative << std::endl;
	file << UI::custom_textMaxLength << std::endl;
	file << UI::custom_textMaxLengthRel << std::endl;
	file << UI::custom_textLineSpacing << std::endl;
	file << UI::custom_textCharSize << std::endl;
	file << UI::custom_actionOffsetX << std::endl;
	file << UI::custom_actionOffsetY << std::endl;
	file << UI::custom_actionOffsetRelative << std::endl;
	file << UI::custom_actionOffsetAnchorTop << std::endl;
	file << UI::custom_actionSelLength << std::endl;
	file << UI::custom_actionSelLengthRel << std::endl;
	file << UI::custom_actionLineSpacing << std::endl;
	file << UI::custom_actionCharSize << std::endl;
	file << UI::custom_actionSizeY << std::endl;
	file << UI::custom_actionTextOffsetY << std::endl;
	file << UI::custom_allowScreenContinue << std::endl;
	file << UI::custom_hideContinueButton << std::endl;
	file << UI::custom_fancyPrintAllowed << std::endl;
	file << UI::custom_fancyPrintDelay << std::endl;
	// Closing the file
	file.close();
}

void game::loadSavePoint(int slot)
{
	int varValue[512];
	std::wstring varName[512];
	int tempi;
	int entryPoint, varCount, musicChannels, interfaceAmount;
	std::wstring buf, fileName, name, buf1 = L"\\Images\\";
	std::wstring path = L"Data\\Savefiles\\slot" + std::to_wstring((_Longlong)slot) + L".bin";
	// Opening the file
	std::wifstream file;
	file.open(path);
	// Reading the data
		// Active file
	std::getline(file, fileName);
		// Gametime
	std::getline(file, buf);	std::wstringstream(buf) >> gametime::hours;
	std::getline(file, buf);	std::wstringstream(buf) >> gametime::minutes;
	std::getline(file, buf);	std::wstringstream(buf) >> gametime::seconds;
		// Current dialogInfo
	std::getline(file, buf);	std::wstringstream(buf) >> entryPoint;

		// Loading the module
	fileName = fileName + L".amf";
	game::loadModuleFull(fileName);
	game::currentDialogInfo = entryPoint;

		// Amount of variables
	std::getline(file, buf);	std::wstringstream(buf) >> varCount;
		// Variable data
	for (int i = 0; i < varCount; i++)
	{
		std::getline(file, varName[i]);
		std::getline(file, buf);	std::wstringstream(buf) >> varValue[i];
	}
		// Amount of images
	std::getline(file, buf);	std::wstringstream(buf) >> game::displayImageCounter;
		// Image data
	for (int i = 0; i < game::displayImageCounter; i++)
	{
		std::getline(file, buf);	std::wstringstream(buf) >> game::displayImages[i].ID;
		// Texture
		std::getline(file, buf);	name = buf;
			// Looking for the texture
		for (int y = 0; y < gl_gameTexCount; y++)
		{
			if (gl_gameTexName[y] == name) { game::displayImages[i].tex = y; y = gl_gameTexCount; }
		}
			// Texture not found - loading
		if (game::displayImages[game::displayImageCounter].tex == -1)
		{
			game::displayImages[game::displayImageCounter].tex = gl_gameTexCount;
			gl_gameTexName[gl_gameTexCount] = name;
			name = L"Modules\\" + game::folder + buf1 + name;
			std::string buf2(name.begin(), name.end());
			gl_gameTexture[gl_gameTexCount].loadFromFile(buf2);
			gl_gameTexCount += 1;
		}
		// Other stuff
		std::getline(file, buf);	game::displayImages[i].delayTimer = logic::wtof(buf);
		std::getline(file, buf);	game::displayImages[i].effectAngleMax = logic::wtof(buf);
		std::getline(file, buf);	game::displayImages[i].effectAngleMin = logic::wtof(buf);
		std::getline(file, buf);	game::displayImages[i].effectDensity = logic::wtof(buf);
		std::getline(file, buf);	std::wstringstream(buf) >> game::displayImages[i].effectFrontLength;
		std::getline(file, buf);	game::displayImages[i].effectLifespan = logic::wtof(buf);
		std::getline(file, buf);	game::displayImages[i].effectSpawnPeriod = logic::wtof(buf);
		std::getline(file, buf);	std::wstringstream(buf) >> game::displayImages[i].effectSpawnTimer;
		std::getline(file, buf);	std::wstringstream(buf) >> game::displayImages[i].effectSpeed;
		std::getline(file, buf);	std::wstringstream(buf) >> game::displayImages[i].fadeBack;
		std::getline(file, buf);	game::displayImages[i].fadeCur = logic::wtof(buf);
		std::getline(file, buf);	game::displayImages[i].fadeMax = logic::wtof(buf);
		std::getline(file, buf);	game::displayImages[i].fadeOut = logic::wtof(buf);
		std::getline(file, buf);	std::wstringstream(buf) >> game::displayImages[i].isEffect;
		std::getline(file, buf);	game::displayImages[i].lifespan = logic::wtof(buf);
		std::getline(file, buf);	game::displayImages[i].movingAngle = logic::wtof(buf);
		std::getline(file, buf);	std::wstringstream(buf) >> game::displayImages[i].movingSpeed;
		std::getline(file, buf);	std::wstringstream(buf) >> game::displayImages[i].posAbsX;
		std::getline(file, buf);	std::wstringstream(buf) >> game::displayImages[i].posAbsY;
		std::getline(file, buf);	game::displayImages[i].posRelX = logic::wtof(buf);
		std::getline(file, buf);	game::displayImages[i].posRelY = logic::wtof(buf);
		std::getline(file, buf);	std::wstringstream(buf) >> game::displayImages[i].sizeAbsX;
		std::getline(file, buf);	std::wstringstream(buf) >> game::displayImages[i].sizeAbsY;
		std::getline(file, buf);	game::displayImages[i].sizeRelX = logic::wtof(buf);
		std::getline(file, buf);	game::displayImages[i].sizeRelY = logic::wtof(buf);
		std::getline(file, buf);	game::displayImages[i].toDelayTimer = logic::wtof(buf);
		std::getline(file, buf);	std::wstringstream(buf) >> game::displayImages[i].toFadeBack;
		std::getline(file, buf);	game::displayImages[i].toFadeMax = logic::wtof(buf);
		std::getline(file, buf);	std::wstringstream(buf) >> game::displayImages[i].usingAbsPos;
		std::getline(file, buf);	std::wstringstream(buf) >> game::displayImages[i].usingAbsSize;
		std::getline(file, buf);	std::wstringstream(buf) >> game::displayImages[i].priority;
	}
		// Amount of music channels
	std::getline(file, buf);		std::wstringstream(buf) >> musicChannels;
	for (int i = 0; i < musicChannels; i++)
	{
		std::getline(file, buf);
		if (buf != L"0")
		{
			game::bgMusicName[i] = buf;
			std::getline(file, buf);	std::wstringstream(buf) >> tempi;	game::bgMusic[i].setLoop(tempi);
			std::getline(file, buf);
			game::bgMusic[i].setVolume(1.50f);
			game::bgMusicMaxVolume[i] = logic::wtof(buf);
			game::bgMusicFadeTime[i] = 2000;
			buf = L"Modules\\" + game::folder + L"\\Sounds\\" + game::bgMusicName[i];
			game::bgMusic[i].openFromFile(std::string(buf.begin(), buf.end()));
			game::bgMusic[i].play();
		}
	}
		// Amount of other channels
	std::getline(file, buf);		std::wstringstream(buf) >> musicChannels;
		// Voiceover channel
	if (musicChannels >= 1)
	{
		std::getline(file, buf);
		if (buf != L"0")
		{
			game::voiceOverName = buf;
			std::getline(file, buf);
			game::voiceOver.setVolume(1.50f);
			game::voiceOverMaxVolume = logic::wtof(buf);
			game::voiceOverFadeTime = 500;
			buf = L"Modules\\" + game::folder + L"\\Sounds\\" + game::voiceOverName;
			game::voiceOver.openFromFile(std::string(buf.begin(), buf.end()));
			game::voiceOver.play();
		}
	}
		// Amount of interface status entries
	std::getline(file, buf);	std::wstringstream(buf) >> interfaceAmount;
		// Interface status
	if (interfaceAmount >= 22)
	{
		std::getline(file, buf);	UI::custom_hideOverlay = logic::wtof(buf);
		std::getline(file, buf);	UI::custom_textOffsetX = logic::wtof(buf);
		std::getline(file, buf);	UI::custom_textOffsetY = logic::wtof(buf);
		std::getline(file, buf);	UI::custom_textOffsetRelative = logic::wtof(buf);
		std::getline(file, buf);	UI::custom_textMaxLength = logic::wtof(buf);
		std::getline(file, buf);	UI::custom_textMaxLengthRel = logic::wtof(buf);
		std::getline(file, buf);	UI::custom_textLineSpacing = logic::wtof(buf);
		std::getline(file, buf);	UI::custom_textCharSize = logic::wtof(buf);
		std::getline(file, buf);	UI::custom_actionOffsetX = logic::wtof(buf);
		std::getline(file, buf);	UI::custom_actionOffsetY = logic::wtof(buf);
		std::getline(file, buf);	UI::custom_actionOffsetRelative = logic::wtof(buf);
		std::getline(file, buf);	UI::custom_actionOffsetAnchorTop = logic::wtof(buf);
		std::getline(file, buf);	UI::custom_actionSelLength = logic::wtof(buf);
		std::getline(file, buf);	UI::custom_actionSelLengthRel = logic::wtof(buf);
		std::getline(file, buf);	UI::custom_actionLineSpacing = logic::wtof(buf);
		std::getline(file, buf);	UI::custom_actionCharSize = logic::wtof(buf);
		std::getline(file, buf);	UI::custom_actionSizeY = logic::wtof(buf);
		std::getline(file, buf);	UI::custom_actionTextOffsetY = logic::wtof(buf);
		std::getline(file, buf);	UI::custom_allowScreenContinue = logic::wtof(buf);
		std::getline(file, buf);	UI::custom_hideContinueButton = logic::wtof(buf);
		std::getline(file, buf);	UI::custom_fancyPrintAllowed = logic::wtof(buf);
		std::getline(file, buf);	UI::custom_fancyPrintDelay = logic::wtof(buf);
	}
	// Closing the file
	file.close();

	// Variables
	for (int i = 0; i < gl_dialogInfoCounter; i++)
	{
		if (gl_dialogInfo[i].type == DIALOGTYPE_VARIABLE)
		{
			for (int y = 0; y < varCount; y++)
			{
				if (gl_dialogInfo[i].e_boxTitle == varName[y])
				{
					gl_dialogInfo[i].var_value = varValue[y];
					y = varCount;
				}
			}
		}
	}
}

bool logic::isActionHidden(int id)
{
	std::wstring exp;
	if (gl_dialogInfo[id].g_descriptionText[0].find(L"*Hidden*") != -1) { return true; }
	for (int i = 1; i < gl_dialogInfo[id].g_descriptionStringsUsed; i++)
	{
		exp = gl_dialogInfo[id].g_descriptionText[i];
		if (exp.find(L"Hidden") != -1)
		{
			return true;
		}
	}
	return false;
}

void logic::activateTimers()
{
	float timerValue;
	for (int i = 0; i < UI::buttonCounter; i++)
	{
		for (int y = 0; y < gl_dialogInfo[UI::btn[i].g_corDialogAction].g_descriptionStringsUsed; y++)
		{
			std::wstring exp = gl_dialogInfo[UI::btn[i].g_corDialogAction].g_descriptionText[y];
			if (exp.find(L"Timer ") != -1)
			{
				std::wstring varValue = exp.substr(5);
				timerValue = logic::wtof(varValue);
				UI::btn[i].timerValue = timerValue * 1000;
				// Destroy the timer. Forever.
				//if (timerValue == 0) { gl_dialogInfo[UI::btn[i].g_corDialogAction].g_descriptionText[y] = L""; }
			}
		}
	}
}

void logic::activateMenuData()
{
	for (int i = 0; i < gl_dialogInfoCounter; i++)
	{
		if (gl_dialogInfo[i].type == DIALOGTYPE_IMAGE) { game::execDialogImage(i); }
		else if (gl_dialogInfo[i].type == DIALOGTYPE_SOUND) { game::execDialogSound(i); }
	}
}