
#include "define.h"

void saveModule(std::wstring path, bool createDir = true, bool encode = false);
void loadModule(std::wstring path, bool decode = false);
void getModuleName(std::wstring path, std::wstring &target);
void clearModule();
void encodeDialogInfo(dialogInfo &target);
void decodeDialogInfo(dialogInfo &target);

class save
{
public:
	static std::wstring path;
};

class undo
{
public:
	static int maxAmount;
	static int currentSnapshot;
};