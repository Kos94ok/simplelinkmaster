
#include "main.h"

sf::Text visualOffsetText;
int getVisualOffsetX(int number, std::wstring target, int charsize)
{
	visualOffsetText.setFont(gl_mainFont);
	visualOffsetText.setString(target);
	visualOffsetText.setCharacterSize(charsize);

	return visualOffsetText.findCharacterPos(number).x;// - visualOffsetText.findCharacterPos(0).x;
}

int getVisualOffsetY(int number, std::wstring target, int charsize)
{
	return 0;
}

void input::addNewDialogInfoLine()
{
	bool StringTranslate = false;
	std::wstring tempbuf;
	// Translating a substring
	if (textTool::editCaretLine > -1 && textTool::editCaretChar < textTool::buffer.length())
	{
		StringTranslate = true;
		tempbuf = gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionText[textTool::editCaretLine].substr(textTool::editCaretChar, -1);
		gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionText[textTool::editCaretLine].erase(textTool::editCaretChar, -1);
	}
	gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionStringsUsed += 1;
	textTool::editCaretLine += 1;
	// Moving bottom strings
	for (int i = gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionStringsUsed - 1; i > textTool::editCaretLine; i--)
	{
		gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionText[i] = gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionText[i - 1];
	}
	// Clearing "added" string
	gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionText[textTool::editCaretLine].clear();
	// Finishing translating a substring
	textTool::editCaretChar = 0;
	if (StringTranslate) { gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionText[textTool::editCaretLine] = tempbuf; }
	// Updating buffer
	if (textTool::editField == EDITFIELD_TOP)
	{
		if (textTool::editCaretLine > -1) { textTool::buffer = gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionText[textTool::editCaretLine]; }
		else { textTool::buffer = gl_dialogInfo[mouse::selectDialogInfoBox].e_boxTitle; }
	}
	// Updating size
	gl_dialogInfo[mouse::selectDialogInfoBox].e_adjustBoxToText();
}