#include "util_sdk.h"
#include "FindPattern.h"
char Util::GetButtonString(ButtonCode_t key)
{
	switch (key)
	{
	case KEY_PAD_0:
		return '0';
	case KEY_PAD_1:
		return '1';
	case KEY_PAD_2:
		return '2';
	case KEY_PAD_3:
		return '3';
	case KEY_PAD_4:
		return '4';
	case KEY_PAD_5:
		return '5';
	case KEY_PAD_6:
		return '6';
	case KEY_PAD_7:
		return '7';
	case KEY_PAD_8:
		return '8';
	case KEY_PAD_9:
		return '9';
	case KEY_PAD_DIVIDE:
		return '/';
	case KEY_PAD_MULTIPLY:
		return '*';
	case KEY_PAD_MINUS:
		return '-';
	case KEY_PAD_PLUS:
		return '+';
	case KEY_SEMICOLON:
		return ';';
	default:
		return pInputSystem->ButtonCodeToString(key)[0];
	}
}

std::string Util::GetButtonName(ButtonCode_t buttonCode)
{
	return pInputSystem->ButtonCodeToString(buttonCode);
}

ButtonCode_t Util::GetButtonCode(std::string buttonName)
{
	for (int i = 0; i < ButtonCode_t::KEY_XSTICK2_UP; i++)
	{
		const char* currentButton = pInputSystem->ButtonCodeToString((ButtonCode_t)i);
		if (strcmp(currentButton, buttonName.c_str()) == 0)
			return (ButtonCode_t)i;
	}

	return ButtonCode_t::BUTTON_CODE_INVALID;
}


void InitKeyValues(KeyValues* keyValues, char const * name)
{
	DWORD dwFunction = (DWORD)FindPattern("client.dll", "\x68\x00\x00\x00\x00\x8B\xC8\xE8\x00\x00\x00\x00\x89\x45\xFC\xEB\x07\xC7\x45\x00\x00\x00\x00\x00\x8B\x03\x56", "x????xxx????xxxxxxx?????xxx");
	dwFunction += 7;
	dwFunction = dwFunction + *reinterpret_cast< PDWORD_PTR >(dwFunction + 1) + 5;
	__asm
	{
		push name
		mov ecx, keyValues
		call dwFunction
	}
}

void LoadFromBuffer(KeyValues* keyValues, char const *resourceName, const char *pBuffer)
{
	DWORD dwFunction = (DWORD)FindPattern("client.dll", "\x55\x8B\xEC\x83\xE4\xF8\x83\xEC\x34\x53\x8B\x5D\x0C\x89\x4C\x24\x04", "xxxxxxxxxxxxxxxxx");

	__asm
	{
		push 0
		push 0
		push 0
		push pBuffer
		push resourceName
		mov ecx, keyValues
		call dwFunction
	}
}
int RandomInt2(int min, int max)
{
	return rand() % (max - min + 1) + min;
}
IMaterial* Util::CreateMaterial(std::string type, std::string texture, bool ignorez, bool nofog, bool model, bool nocull, bool halflambert)
{
	std::stringstream materialData;
	materialData << "\"" + type + "\"\n"
		"{\n"
		"\t\"$basetexture\" \"" + texture + "\"\n"
		"\t\"$ignorez\" \"" + std::to_string(ignorez) + "\"\n"
		"\t\"$nofog\" \"" + std::to_string(nofog) + "\"\n"
		"\t\"$model\" \"" + std::to_string(model) + "\"\n"
		"\t\"$nocull\" \"" + std::to_string(nocull) + "\"\n"
		"\t\"$halflambert\" \"" + std::to_string(halflambert) + "\"\n"
		"}\n" << std::flush;

	std::string materialName = "Castle" + std::to_string(RandomInt2(10, 100000));
	KeyValues* keyValues = new KeyValues(materialName.c_str());

	InitKeyValues(keyValues, type.c_str());
	LoadFromBuffer(keyValues, materialName.c_str(), materialData.str().c_str());

	return pMaterial->CreateMaterial(materialName.c_str(), keyValues);
}