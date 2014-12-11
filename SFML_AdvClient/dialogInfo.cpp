
#include "main.h"

dialogInfo::dialogInfo()
{
	isValid = false;
	hook_amount = 0;
	for (int i = 0; i < 32; i++)
	{
		hook_actionId[i] = -1;
	}
	g_descriptionStringsUsed = 0;
	for (int i = 0; i < 128; i++)
	{
		g_descriptionText[i] = L"";
	}
}

void dialogInfo::g_descrLenAdjust()
{
	if (type != DIALOGTYPE_INFO) { return; }

	int formattedCounter = 0;
	std::wstring formatted[128], lastWord, lenBuf;

	wchar_t iter;
	bool style_bold = false, style_underline = false, style_italic = false, colorf = false;
	bool stickFound = false, ignoreNextSpace = false, removeLast = true;
	int visibleLength = 0;
	float maxLength = camera::resolutionX - 50;
	if (UI::custom_textMaxLength > 0)
	{
		maxLength = UI::custom_textMaxLength;
		if (UI::custom_textMaxLengthRel) { maxLength *= camera::resolutionX; }
	}
	//maxLength -= 

	std::wofstream outbuf;
	std::wifstream inbuf;

	outbuf.open(L"buf.txt", std::ios::trunc);
	// Sending all the text to the buffer
	for (int i = 0; i < this->g_descriptionStringsUsed; i++)
	{
		outbuf << g_descriptionText[i] << L" ";
	}
	outbuf.close();

	// Starting reading the buffer char by char
	inbuf.open(L"buf.txt");
	lastWord = L"";		formatted[0] = L"";
	while (inbuf.good())
	{
		iter = inbuf.get();
		if (iter == ' ')
		{
			formatted[formattedCounter] += lastWord;
			lastWord = L"";
		}
		else if (iter == '|' && !colorf) { stickFound = !stickFound; }
		else if (iter == '|' && colorf) { colorf = false; }
		// Color symbols
		else if (iter == 'c' && stickFound) { colorf = true; }
		// Style symbols
		else if (iter == 'b' && stickFound) { style_bold = !style_bold; }
		else if (iter == 'u' && stickFound) { style_underline = !style_underline; }
		else if (iter == 'i' && stickFound) { style_italic = !style_italic; }
		// Line change symbol
		else if (iter == 'n' && stickFound)
		{
			stickFound = false;
			// Checking for "empty" words
			if (lastWord.substr(lastWord.length() - 1) == L"|") { lastWord = lastWord.substr(0, lastWord.length() - 1); }
			// Removing extra symbol
			if (removeLast) { formatted[formattedCounter] += lastWord.substr(0, lastWord.length() - 1); }
			else { formatted[formattedCounter] += lastWord; }
			removeLast = false;

			visibleLength = 0;
			lastWord = L"/";
			formattedCounter += 1;

			ignoreNextSpace = true;
		}
		// Adding the checked letter to the string
		if (!(iter == ' ' && ignoreNextSpace))
		{
			lastWord += iter;
			if (!stickFound)
			{
				lenBuf = iter;
				visibleLength += getVisualOffsetX(lenBuf.length(), lenBuf, UI::custom_textCharSize, style_bold, style_underline, style_italic);
				// String is too long
				if (visibleLength >= maxLength)
				{
					formattedCounter += 1;
					lastWord = lastWord.substr(1);
					removeLast = true;

					visibleLength = 75;
				}
			}
		}
		else { ignoreNextSpace = false; }
	}
	inbuf.close();
	DeleteFile(L"buf.txt");
	// Copying the formatted strings
	g_descriptionStringsUsed = formattedCounter + 1;
	for (int i = 0; i < formattedCounter + 1; i++)
	{
		g_descriptionText[i] = formatted[i];
	}
}

void dialogInfo::updateVisibility() {}
void dialogInfo::e_updateDrawInfo() {}