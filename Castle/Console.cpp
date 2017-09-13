#include "Vitalflea.h"
bool Open;
void OpenConsole()
{
	if (!FreeConsole()) {
		FILE* fp;
		if(AllocConsole())
			Open = true;
		SetConsoleTitleA("Resurrection");
		freopen_s(&fp, "CONOUT$", "w", stdout);
	}
}