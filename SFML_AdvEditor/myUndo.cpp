
#include "main.h"

void myUndo::createBackupPoint()
{
	myUndo::undoChain = false;
	int maxBackup = settings::maxUndoPoints + 1;
	// Creating temp directory if needed
	CreateDirectory(L"Temp", 0);
	// Creating the temp file path
	std::wstring buf, bufNum, bufEnd = L".amf", bufNew;
	bufNum = std::to_wstring((_Longlong)myUndo::currentBackup);
	buf = L"Temp//undo" + bufNum + bufEnd;
	saveModule(buf, false);
	myUndo::currentBackup += 1;
	// Moving the files if needed
	if (myUndo::currentBackup > maxBackup)
	{
		buf = L"Temp//undo0.amf";
		DeleteFile(buf.c_str());
		for (int i = 1; i <= maxBackup; i++)
		{
			// Connecting names
			bufNum = std::to_wstring((_Longlong)i);			buf = L"Temp//undo" + bufNum + bufEnd;
			bufNum = std::to_wstring((_Longlong)i - 1);		bufNew = L"Temp//undo" + bufNum + bufEnd;
			// Renaming
			rename(std::string(buf.begin(), buf.end()).c_str(), std::string(bufNew.begin(), bufNew.end()).c_str());
		}
		myUndo::currentBackup -= 1;
	}
	// Removing forward steps
	else
	{
		myUndo::clearBackupPoints(myUndo::currentBackup);
	}
}

void myUndo::moveToNextBackup()
{
	std::wstring buf, bufNum, bufEnd = L".amf";
	// Searching for the name
	bufNum = std::to_wstring((_Longlong)myUndo::currentBackup + 1);
	buf = L"Temp//undo" + bufNum + bufEnd;

	// Checking if the file does exist
	FILE* file = fopen(std::string(buf.begin(), buf.end()).c_str(), "r");
	if (file == 0) { return; }
	else { fclose(file); }

	// Loading
	loadModule(buf);
	myUndo::currentBackup += 1;

	// Checking if undo chain is stopped
	bufNum = std::to_wstring((_Longlong)myUndo::currentBackup + 1);
	buf = L"Temp//undo" + bufNum + bufEnd;
	file = fopen(std::string(buf.begin(), buf.end()).c_str(), "r");
	if (file == 0) { myUndo::undoChain = false; }
	else { fclose(file); }
}

void myUndo::moveToPrevBackup()
{
	if (myUndo::currentBackup == 0) { return; }

	std::wstring buf, bufNum, bufEnd = L".amf";
	myUndo::currentBackup -= 1;
	// Searching for the name
	bufNum = std::to_wstring((_Longlong)myUndo::currentBackup);
	buf = L"Temp//undo" + bufNum + bufEnd;
	// Loading
	loadModule(buf);
	// Fixing the textTool
	/*if (mouse::selectTool == TOOL_TEXT && mouse::selectDialogInfoBox != -1)
	{
		if (textTool::editCaretLine == -1) { textTool::buffer = gl_dialogInfo[mouse::selectDialogInfoBox].e_boxTitle; }
		else { textTool::buffer = gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionText[textTool::editCaretLine]; }

		if (textTool::editCaretLine >= gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionStringsUsed && gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionStringsUsed > 0)
		{
			textTool::buffer = gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionText[gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionStringsUsed - 1];
			textTool::editCaretLine = gl_dialogInfo[mouse::selectDialogInfoBox].g_descriptionStringsUsed - 1;
			textTool::editCaretChar = textTool::buffer.length();
		}
		if (textTool::editCaretChar > textTool::buffer.length())
		{
			textTool::editCaretChar = textTool::buffer.length();
		}
	}*/
}

void myUndo::clearBackupPoints(int start)
{
	int maxBackup = settings::maxUndoPoints + 1;
	std::wstring buf, bufNum, bufEnd = L".amf", bufNew;
	// Removing the files
	for (int i = start; i < maxBackup; i++)
	{
		bufNum = std::to_wstring((_Longlong)i);		buf = L"Temp//undo" + bufNum + bufEnd;
		DeleteFile(buf.c_str());
	}
	// Removing the directory
	if (start == 0)
	{
		buf = L"Temp";
		RemoveDirectory(buf.c_str());
		myUndo::currentBackup = 0;
	}
}