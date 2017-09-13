#include "Menu.h"
#include "ImGui/imgui_internal.h"
#include "settings.h"
#include "config.h"
#include <Shlobj.h>
#include "AimBotTab.h"
#include "TriggerBotTab.h"
#include "HvHTab.h"
#include "SkinsTab.h"
#include "ModelsTabs.h"
#include "Features.h"
const char *tracerEffectNames[] = {
	"Assault Rifle", // 0
	"Pistol",
	"SMG",
	"Rifle",
	"Kisak Snot",
	"Machine Gun",
	"Shotgun",
	"Kisak Snot Fallback",
	"Kisak Snot Fallback2",
	"Wire1A",
	"Wire2",
	"Wire1B",
	"Original",
	"Backup",
	".50 Cal",
	".50 Cal Glow",
	".50 Cal Low",
	".50 Cal Low Glow", // 17
};
/*
int GetConnected(int Index)
{
static DWORD dwTemp = *(DWORD*)((GetModuleHandleA("client.dll") + 0x2EC61BC));
return *(int*)(dwTemp + offsets.DT_PlayerResource.m_bConnected + (int)Index);
}
TeamID GetTeam(int index)
{
static DWORD dwTemp = *(DWORD*)((GetModuleHandleA("client.dll") + 0x2EC61BC));
return *(TeamID*)(dwTemp + offsets.DT_PlayerResource.m_iTeam + (int)index * 4);
}
int* GetCompetitiveRanking(int index)
{
static DWORD dwTemp = *(DWORD*)((GetModuleHandleA("client.dll") + 0x2EC61BC));
return (int*)(dwTemp + offsets.DT_CSPlayerResource.m_iCompetitiveRanking + (int)index * 4);
}
int* GetCompetitiveWins(int index)
{
static DWORD dwTemp = *(DWORD*)((GetModuleHandleA("client.dll") + 0x2EC61BC));
return (int*)(dwTemp + offsets.DT_CSPlayerResource.m_iCompetitiveWins + (int)index * 4);
}
const char* GetClan(int index)
{
static DWORD dwTemp = *(DWORD*)((GetModuleHandleA("client.dll") + 0x2EC61BC));
return (const char*)(dwTemp + offsets.DT_CSPlayerResource.m_szClan + (int)index * 16);
}
*/
bool Walk::showWindow;
float Settings::UI::Windows::Walkbot::posY;
float Settings::UI::Windows::Walkbot::posX;
float Settings::UI::Windows::Walkbot::sizeX;
float Settings::UI::Windows::Walkbot::sizeY;
bool Settings::UI::Windows::Walkbot::open;
bool Settings::UI::Windows::Walkbot::reload;
static int currentPlayer = -1;
bool Settings::ScreenshotCleaner::enabled = false;
CHAR path[MAX_PATH];
std::string folder, file;
 int configItemCurrent = -1;

 char buf[128] = "";
 const char* ButtonNames[] =
 {

	 "KEY_NONE",
	 "KEY_0",
	 "KEY_1",
	 "KEY_2",
	 "KEY_3",
	 "KEY_4",
	 "KEY_5",
	 "KEY_6",
	 "KEY_7",
	 "KEY_8",
	 "KEY_9",
	 "KEY_A",
	 "KEY_B",
	 "KEY_C",
	 "KEY_D",
	 "KEY_E",
	 "KEY_F",
	 "KEY_G",
	 "KEY_H",
	 "KEY_I",
	 "KEY_J",
	 "KEY_K",
	 "KEY_L",
	 "KEY_M",
	 "KEY_N",
	 "KEY_O",
	 "KEY_P",
	 "KEY_Q",
	 "KEY_R",
	 "KEY_S",
	 "KEY_T",
	 "KEY_U",
	 "KEY_V",
	 "KEY_W",
	 "KEY_X",
	 "KEY_Y",
	 "KEY_Z",
	 "KEY_PAD_0",
	 "KEY_PAD_1",
	 "KEY_PAD_2",
	 "KEY_PAD_3",
	 "KEY_PAD_4",
	 "KEY_PAD_5",
	 "KEY_PAD_6",
	 "KEY_PAD_7",
	 "KEY_PAD_8",
	 "KEY_PAD_9",
	 "KEY_PAD_DIVIDE",
	 "KEY_PAD_MULTIPLY",
	 "KEY_PAD_MINUS",
	 "KEY_PAD_PLUS",
	 "KEY_PAD_ENTER",
	 "KEY_PAD_DECIMAL",
	 "KEY_LBRACKET",
	 "KEY_RBRACKET",
	 "KEY_SEMICOLON",
	 "KEY_APOSTROPHE",
	 "KEY_BACKQUOTE",
	 "KEY_COMMA",
	 "KEY_PERIOD",
	 "KEY_SLASH",
	 "KEY_BACKSLASH",
	 "KEY_MINUS",
	 "KEY_EQUAL",
	 "KEY_ENTER",
	 "KEY_SPACE",
	 "KEY_BACKSPACE",
	 "KEY_TAB",
	 "KEY_CAPSLOCK",
	 "KEY_NUMLOCK",
	 "KEY_ESCAPE",
	 "KEY_SCROLLLOCK",
	 "KEY_INSERT",
	 "KEY_DELETE",
	 "KEY_HOME",
	 "KEY_END",
	 "KEY_PAGEUP",
	 "KEY_PAGEDOWN",
	 "KEY_BREAK",
	 "KEY_LSHIFT",
	 "KEY_RSHIFT",
	 "KEY_LALT",
	 "KEY_RALT",
	 "KEY_LCONTROL",
	 "KEY_RCONTROL",
	 "KEY_LWIN",
	 "KEY_RWIN",
	 "KEY_APP",
	 "KEY_UP",
	 "KEY_LEFT",
	 "KEY_DOWN",
	 "KEY_RIGHT",
	 "KEY_F1",
	 "KEY_F2",
	 "KEY_F3",
	 "KEY_F4",
	 "KEY_F5",
	 "KEY_F6",
	 "KEY_F7",
	 "KEY_F8",
	 "KEY_F9",
	 "KEY_F10",
	 "KEY_F11",
	 "KEY_F12",
	 "KEY_CAPSLOCKTOGGLE",
	 "KEY_NUMLOCKTOGGLE",
	 "KEY_SCROLLLOCKTOGGLE",



	 "MOUSE_LEFT",
	 "MOUSE_RIGHT",
	 "MOUSE_MIDDLE",
	 "MOUSE_4",
	 "MOUSE_5",
	 "MOUSE_WHEEL_UP",		// A fake button which is 'pressed' and 'released' when the wheel is moved up
	 "MOUSE_WHEEL_DOWN",	// A fake button which is 'pressed' and 'released' when the wheel is moved down

							// VAXIS NEGATIVE
 };
ColorVar Settings::UI::mainColor = ImColor(54, 54, 54, 255);
ColorVar Settings::UI::bodyColor = ImColor(24, 24, 24, 240);
ColorVar Settings::UI::fontColor = ImColor(255, 255, 255, 255);
const char* BoxTypes[] = { "Flat 2D", "Frame 2D", "Box 3D" };
const char* TracerTypes[] = { "Bottom", "Cursor" };
const char* BarTypes[] = { "Vertical Left", "Vertical Right", "Horizontal Below", "Horizontal Above", "Interwebz" };
const char* BarColorTypes[] = { "Static", "Health Based" };
const char* TeamColorTypes[] = { "Absolute", "Relative" };
const char* ChamsTypes[] = { "Normal", "Normal - XQZ", "Flat", "Flat - XQZ" };
const char* ArmsTypes[] = { "Default", "Wireframe", "None" };

const char* tabs[] = {
	"Aimbot",
	"Triggerbot",
	"Visuals",
	"HvH",
	"Player List",
	//"Models",
	"Misc",
	"Colors"
};
const char* strafeTypes[] = { "Forwards", "Backwards", "Left", "Right", "Rage" };
const char* animationTypes[] = { "Static", "Marquee", "Words", "Letters" };
const char* spammerTypes[] = { "None", "Normal", "Positions" };
const char* teams[] = { "Allies", "Enemies", "Both" };
const char* grenadeTypes[] = { "FLASH", "SMOKE", "MOLOTOV", "HEGRENADE" };
const char* throwTypes[] = { "NORMAL", "RUN", "JUMP", "WALK" };
static char nickname[127] = "";
struct ColorListVar
{
	const char* name;
	union
	{
		ColorVar* colorVarPtr;
		HealthColorVar* healthColorVarPtr;
	};
	enum
	{
		COLORVAR_TYPE,
		HEALTHCOLORVAR_TYPE
	} type;

	ColorListVar(const char* name, ColorVar* ptr)
	{
		this->name = name;
		this->colorVarPtr = ptr;
		this->type = COLORVAR_TYPE;
	}

	ColorListVar(const char* name, HealthColorVar* ptr)
	{
		this->name = name;
		this->healthColorVarPtr = ptr;
		this->type = HEALTHCOLORVAR_TYPE;
	}
};
ColorListVar colors[] = {
	{ "UI Main", &Settings::UI::mainColor },
	{ "UI Body", &Settings::UI::bodyColor },
	{ "UI Font", &Settings::UI::fontColor },
	{ "FOV Circle", &Settings::ESP::FOVCrosshair::color },
	{ "Hitmarker", &Settings::ESP::Hitmarker::color },
	{ "ESP - Enemy", &Settings::ESP::enemyColor },
	{ "ESP - Team", &Settings::ESP::allyColor },
	{ "ESP - Enemy Visible", &Settings::ESP::enemyVisibleColor },
	{ "ESP - Team Visible", &Settings::ESP::allyVisibleColor },
	{ "ESP - CT", &Settings::ESP::ctColor },
	{ "ESP - T", &Settings::ESP::tColor },
	{ "ESP - CT Visible", &Settings::ESP::ctVisibleColor },
	{ "ESP - T Visible", &Settings::ESP::tVisibleColor },
	{ "ESP - LocalPlayer", &Settings::ESP::localplayerColor },
	{ "ESP - Bomb", &Settings::ESP::bombColor },
	{ "ESP - Bomb Defusing", &Settings::ESP::bombDefusingColor },
	{ "ESP - Hostage", &Settings::ESP::hostageColor },
	{ "ESP - Defuser", &Settings::ESP::defuserColor },
	{ "ESP - Weapon", &Settings::ESP::weaponColor },
	{ "ESP - Chicken", &Settings::ESP::chickenColor },
	{ "ESP - Fish", &Settings::ESP::fishColor },
	{ "ESP - Smoke", &Settings::ESP::smokeColor },
	{ "ESP - Decoy", &Settings::ESP::decoyColor },
	{ "ESP - Flashbang", &Settings::ESP::flashbangColor },
	{ "ESP - Grenade", &Settings::ESP::grenadeColor },
	{ "ESP - Molotov", &Settings::ESP::molotovColor },
	{ "ESP - Skeleton", &Settings::ESP::Skeleton::color },
	{ "Chams - Team", &Settings::ESP::Chams::allyColor },
	{ "Chams - Team Visible", &Settings::ESP::Chams::allyVisibleColor },
	{ "Chams - Enemy", &Settings::ESP::Chams::enemyColor },
	{ "Chams - Enemy Visible", &Settings::ESP::Chams::enemyVisibleColor },
	{ "Chams - LocalPlayer", &Settings::ESP::Chams::localplayerColor },
	{ "Chams - Arms", &Settings::ESP::Chams::Arms::color },
	{ "Chams - Weapon", &Settings::ESP::Chams::Weapon::color },
	{ "Grenade Helper - Aim Line", &Settings::GrenadeHelper::aimLine },
	{ "Grenade Helper - Aim Dot", &Settings::GrenadeHelper::aimDot },
	{ "Grenade Helper - HE Info", &Settings::GrenadeHelper::infoHE },
	{ "Grenade Helper - Smoke Info", &Settings::GrenadeHelper::infoSmoke },
	{ "Grenade Helper - Molotov Info", &Settings::GrenadeHelper::infoMolotov },
	{ "Grenade Helper - Flash Info", &Settings::GrenadeHelper::infoFlash },
	{ "Radar - Enemy", &Settings::Radar::enemyColor },
	{ "Radar - Team", &Settings::Radar::allyColor },
	{ "Radar - Enemy Visible", &Settings::Radar::enemyVisibleColor },
	{ "Radar - Team Visible", &Settings::Radar::allyVisibleColor },
	{ "Radar - CT", &Settings::Radar::ctColor },
	{ "Radar - T", &Settings::Radar::tColor },
	{ "Radar - CT Visible", &Settings::Radar::ctVisibleColor },
	{ "Radar - T Visible", &Settings::Radar::tVisibleColor },
	{ "Radar - Bomb", &Settings::Radar::bombColor },
	{ "Radar - Bomb Defusing", &Settings::Radar::bombDefusingColor },
	{ "Glow - Team", &Settings::ESP::Glow::allyColor },
	{ "Glow - Enemy", &Settings::ESP::Glow::enemyColor },
	{ "Glow - Enemy Visible", &Settings::ESP::Glow::enemyVisibleColor },
	{ "Glow - LocalPlayer", &Settings::ESP::Glow::localplayerColor },
	{ "Glow - Weapon", &Settings::ESP::Glow::weaponColor },
	{ "Glow - Grenade", &Settings::ESP::Glow::grenadeColor },
	{ "Glow - Defuser", &Settings::ESP::Glow::defuserColor },
	{ "Glow - Chicken", &Settings::ESP::Glow::chickenColor },
	{ "Sky", &Settings::NoSky::color },
	{ "Walls", &Settings::ASUSWalls::color },
};
const char* colorNames[IM_ARRAYSIZE(colors)];
char ConfigNames[128] = "";
bool ColorPicker(float* col, bool alphabar)
{
	const int EDGE_SIZE = 200; // = int(ImGui::GetWindowWidth() * 0.75f);
	const ImVec2 SV_PICKER_SIZE = ImVec2(EDGE_SIZE, EDGE_SIZE);
	const float SPACING = ImGui::GetStyle().ItemInnerSpacing.x;
	const float HUE_PICKER_WIDTH = 20.f;
	const float CROSSHAIR_SIZE = 7.0f;

	ImColor color(col[0], col[1], col[2]);
	bool value_changed = false;

	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	ImVec2 picker_pos = ImGui::GetCursorScreenPos();

	float hue, saturation, value;
	ImGui::ColorConvertRGBtoHSV(color.Value.x, color.Value.y, color.Value.z, hue, saturation, value);

	ImColor colors[] = {
		ImColor(255, 0, 0),
		ImColor(255, 255, 0),
		ImColor(0, 255, 0),
		ImColor(0, 255, 255),
		ImColor(0, 0, 255),
		ImColor(255, 0, 255),
		ImColor(255, 0, 0)
	};

	for (int i = 0; i < 6; i++)
	{
		draw_list->AddRectFilledMultiColor(
			ImVec2(picker_pos.x + SV_PICKER_SIZE.x + SPACING, picker_pos.y + i * (SV_PICKER_SIZE.y / 6)),
			ImVec2(picker_pos.x + SV_PICKER_SIZE.x + SPACING + HUE_PICKER_WIDTH,
				picker_pos.y + (i + 1) * (SV_PICKER_SIZE.y / 6)),
			colors[i],
			colors[i],
			colors[i + 1],
			colors[i + 1]
		);
	}

	draw_list->AddLine(
		ImVec2(picker_pos.x + SV_PICKER_SIZE.x + SPACING - 2, picker_pos.y + hue * SV_PICKER_SIZE.y),
		ImVec2(picker_pos.x + SV_PICKER_SIZE.x + SPACING + 2 + HUE_PICKER_WIDTH, picker_pos.y + hue * SV_PICKER_SIZE.y),
		ImColor(255, 255, 255)
	);

	if (alphabar)
	{
		float alpha = col[3];

		draw_list->AddRectFilledMultiColor(
			ImVec2(picker_pos.x + SV_PICKER_SIZE.x + 2 * SPACING + HUE_PICKER_WIDTH, picker_pos.y),
			ImVec2(picker_pos.x + SV_PICKER_SIZE.x + 2 * SPACING + 2 * HUE_PICKER_WIDTH, picker_pos.y + SV_PICKER_SIZE.y),
			ImColor(0, 0, 0), ImColor(0, 0, 0), ImColor(255, 255, 255), ImColor(255, 255, 255)
		);

		draw_list->AddLine(
			ImVec2(picker_pos.x + SV_PICKER_SIZE.x + 2 * (SPACING - 2) + HUE_PICKER_WIDTH, picker_pos.y + alpha * SV_PICKER_SIZE.y),
			ImVec2(picker_pos.x + SV_PICKER_SIZE.x + 2 * (SPACING + 2) + 2 * HUE_PICKER_WIDTH, picker_pos.y + alpha * SV_PICKER_SIZE.y),
			ImColor(255.f - alpha, 255.f, 255.f)
		);
	}

	const ImU32 c_oColorBlack = ImGui::ColorConvertFloat4ToU32(ImVec4(0.f, 0.f, 0.f, 1.f));
	const ImU32 c_oColorBlackTransparent = ImGui::ColorConvertFloat4ToU32(ImVec4(0.f, 0.f, 0.f, 0.f));
	const ImU32 c_oColorWhite = ImGui::ColorConvertFloat4ToU32(ImVec4(1.f, 1.f, 1.f, 1.f));

	ImVec4 cHueValue(1, 1, 1, 1);
	ImGui::ColorConvertHSVtoRGB(hue, 1, 1, cHueValue.x, cHueValue.y, cHueValue.z);
	ImU32 oHueColor = ImGui::ColorConvertFloat4ToU32(cHueValue);

	draw_list->AddRectFilledMultiColor(
		ImVec2(picker_pos.x, picker_pos.y),
		ImVec2(picker_pos.x + SV_PICKER_SIZE.x, picker_pos.y + SV_PICKER_SIZE.y),
		c_oColorWhite,
		oHueColor,
		oHueColor,
		c_oColorWhite
	);

	draw_list->AddRectFilledMultiColor(
		ImVec2(picker_pos.x, picker_pos.y),
		ImVec2(picker_pos.x + SV_PICKER_SIZE.x, picker_pos.y + SV_PICKER_SIZE.y),
		c_oColorBlackTransparent,
		c_oColorBlackTransparent,
		c_oColorBlack,
		c_oColorBlack
	);

	float x = saturation * SV_PICKER_SIZE.x;
	float y = (1 - value) * SV_PICKER_SIZE.y;
	ImVec2 p(picker_pos.x + x, picker_pos.y + y);
	draw_list->AddLine(ImVec2(p.x - CROSSHAIR_SIZE, p.y), ImVec2(p.x - 2, p.y), ImColor(255, 255, 255));
	draw_list->AddLine(ImVec2(p.x + CROSSHAIR_SIZE, p.y), ImVec2(p.x + 2, p.y), ImColor(255, 255, 255));
	draw_list->AddLine(ImVec2(p.x, p.y + CROSSHAIR_SIZE), ImVec2(p.x, p.y + 2), ImColor(255, 255, 255));
	draw_list->AddLine(ImVec2(p.x, p.y - CROSSHAIR_SIZE), ImVec2(p.x, p.y - 2), ImColor(255, 255, 255));

	ImGui::InvisibleButton("saturation_value_selector", SV_PICKER_SIZE);

	if (ImGui::IsItemActive() && ImGui::GetIO().MouseDown[0])
	{
		ImVec2 mouse_pos_in_canvas = ImVec2(ImGui::GetIO().MousePos.x - picker_pos.x, ImGui::GetIO().MousePos.y - picker_pos.y);

		if (mouse_pos_in_canvas.x <	0)
			mouse_pos_in_canvas.x = 0;
		else if (mouse_pos_in_canvas.x >= SV_PICKER_SIZE.x - 1)
			mouse_pos_in_canvas.x = SV_PICKER_SIZE.x - 1;

		if (mouse_pos_in_canvas.y < 0)
			mouse_pos_in_canvas.y = 0;
		else if (mouse_pos_in_canvas.y >= SV_PICKER_SIZE.y - 1)
			mouse_pos_in_canvas.y = SV_PICKER_SIZE.y - 1;

		value = 1 - (mouse_pos_in_canvas.y / (SV_PICKER_SIZE.y - 1));
		saturation = mouse_pos_in_canvas.x / (SV_PICKER_SIZE.x - 1);
		value_changed = true;
	}

	// hue bar logic
	ImGui::SetCursorScreenPos(ImVec2(picker_pos.x + SPACING + SV_PICKER_SIZE.x, picker_pos.y));
	ImGui::InvisibleButton("hue_selector", ImVec2(HUE_PICKER_WIDTH, SV_PICKER_SIZE.y));

	if (ImGui::GetIO().MouseDown[0] && (ImGui::IsItemHovered() || ImGui::IsItemActive()))
	{
		ImVec2 mouse_pos_in_canvas = ImVec2(ImGui::GetIO().MousePos.x - picker_pos.x, ImGui::GetIO().MousePos.y - picker_pos.y);

		if (mouse_pos_in_canvas.y <	0)
			mouse_pos_in_canvas.y = 0;
		else if (mouse_pos_in_canvas.y >= SV_PICKER_SIZE.y - 1)
			mouse_pos_in_canvas.y = SV_PICKER_SIZE.y - 1;

		hue = mouse_pos_in_canvas.y / (SV_PICKER_SIZE.y - 1);
		value_changed = true;
	}

	if (alphabar)
	{
		ImGui::SetCursorScreenPos(ImVec2(picker_pos.x + SPACING * 2 + HUE_PICKER_WIDTH + SV_PICKER_SIZE.x, picker_pos.y));
		ImGui::InvisibleButton("alpha_selector", ImVec2(HUE_PICKER_WIDTH, SV_PICKER_SIZE.y));

		if (ImGui::GetIO().MouseDown[0] && (ImGui::IsItemHovered() || ImGui::IsItemActive()))
		{
			ImVec2 mouse_pos_in_canvas = ImVec2(ImGui::GetIO().MousePos.x - picker_pos.x, ImGui::GetIO().MousePos.y - picker_pos.y);

			if (mouse_pos_in_canvas.y <	0)
				mouse_pos_in_canvas.y = 0;
			else if (mouse_pos_in_canvas.y >= SV_PICKER_SIZE.y - 1)
				mouse_pos_in_canvas.y = SV_PICKER_SIZE.y - 1;

			float alpha = mouse_pos_in_canvas.y / (SV_PICKER_SIZE.y - 1);
			col[3] = alpha;
			value_changed = true;
		}
	}

	color = ImColor::HSV(hue >= 1 ? hue - 10 * 1e-6 : hue, saturation > 0 ? saturation : 10 * 1e-6, value > 0 ? value : 1e-6);
	col[0] = color.Value.x;
	col[1] = color.Value.y;
	col[2] = color.Value.z;

	bool widget_used;
	ImGui::PushItemWidth((alphabar ? SPACING + HUE_PICKER_WIDTH : 0) + SV_PICKER_SIZE.x + SPACING + HUE_PICKER_WIDTH - 2 * ImGui::GetStyle().FramePadding.x);
	widget_used = alphabar ? ImGui::ColorEdit4("", col) : ImGui::ColorEdit3("", col);
	ImGui::PopItemWidth();

	float new_hue, new_sat, new_val;
	ImGui::ColorConvertRGBtoHSV(col[0], col[1], col[2], new_hue, new_sat, new_val);

	if (new_hue <= 0 && hue > 0)
	{
		if (new_val <= 0 && value != new_val)
		{
			color = ImColor::HSV(hue, saturation, new_val <= 0 ? value * 0.5f : new_val);
			col[0] = color.Value.x;
			col[1] = color.Value.y;
			col[2] = color.Value.z;
		}
		else if (new_sat <= 0)
		{
			color = ImColor::HSV(hue, new_sat <= 0 ? saturation * 0.5f : new_sat, new_val);
			col[0] = color.Value.x;
			col[1] = color.Value.y;
			col[2] = color.Value.z;
		}
	}

	return value_changed | widget_used;
}
bool ColorPicker4(float col[4])
{
	return ColorPicker(col, true);
}
void Menu()
{
	static int colorSelected = 0;
	static bool mouse_enabled, Visuals, VisualsTab, Misc, MiscTab, Aim, AimTab, HvH, HvHTab, Skins, SkinsTab, Models, ModelsTab;
	bool is_renderer_active = renderer.IsActive();

	if (is_renderer_active) {
		if (mouse_enabled) {
			pEngine->ClientCmd_Unrestricted("cl_mouseenable 0");
			mouse_enabled = false;
		}
	}
	else {
		if (!mouse_enabled) {
			pEngine->ClientCmd_Unrestricted("cl_mouseenable 1");
			mouse_enabled = true;
		}
	}
	ImGui::GetIO().MouseDrawCursor = is_renderer_active;
	//ImGui::GetIO().IniFilename = "imgui.ini";
	//ImGui::LogToFile();
	ImGui_ImplDX9_NewFrame();
	static ImGuiStyle* style = &ImGui::GetStyle();
	static bool once;
	if (!once)
	{
		ImGuiStyle& style = ImGui::GetStyle();

		ImVec4 mainColorHovered = ImVec4(Settings::UI::mainColor.Color().Value.x + 0.1f, Settings::UI::mainColor.Color().Value.y + 0.1f, Settings::UI::mainColor.Color().Value.z + 0.1f, Settings::UI::mainColor.Color().Value.w);
		ImVec4 mainColorActive = ImVec4(Settings::UI::mainColor.Color().Value.x + 0.2f, Settings::UI::mainColor.Color().Value.y + 0.2f, Settings::UI::mainColor.Color().Value.z + 0.2f, Settings::UI::mainColor.Color().Value.w);
		ImVec4 menubarColor = ImVec4(Settings::UI::bodyColor.Color().Value.x, Settings::UI::bodyColor.Color().Value.y, Settings::UI::bodyColor.Color().Value.z, Settings::UI::bodyColor.Color().Value.w - 0.8f);
		ImVec4 frameBgColor = ImVec4(Settings::UI::bodyColor.Color().Value.x, Settings::UI::bodyColor.Color().Value.y, Settings::UI::bodyColor.Color().Value.z, Settings::UI::bodyColor.Color().Value.w + .1f);
		ImVec4 tooltipBgColor = ImVec4(Settings::UI::bodyColor.Color().Value.x, Settings::UI::bodyColor.Color().Value.y, Settings::UI::bodyColor.Color().Value.z, Settings::UI::bodyColor.Color().Value.w + .05f);

		style.Alpha = 1.0f;
		style.WindowPadding = ImVec2(8, 8);
		style.WindowMinSize = ImVec2(32, 32);
		style.WindowRounding = 0.0f;
		style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
		style.ChildWindowRounding = 0.0f;
		style.FramePadding = ImVec2(4, 3);
		style.FrameRounding = 0.0f;
		style.ItemSpacing = ImVec2(8, 4);
		style.ItemInnerSpacing = ImVec2(4, 4);
		style.TouchExtraPadding = ImVec2(0, 0);
		style.IndentSpacing = 21.0f;
		style.ColumnsMinSpacing = 3.0f;
		style.ScrollbarSize = 12.0f;
		style.ScrollbarRounding = 0.0f;
		style.GrabMinSize = 5.0f;
		style.GrabRounding = 0.0f;
		style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
		style.DisplayWindowPadding = ImVec2(22, 22);
		style.DisplaySafeAreaPadding = ImVec2(4, 4);
		style.AntiAliasedLines = true;
		style.AntiAliasedShapes = true;
		style.CurveTessellationTol = 1.25f;

		style.Colors[ImGuiCol_Text] = Settings::UI::fontColor.Color();
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style.Colors[ImGuiCol_WindowBg] = Settings::UI::bodyColor.Color();
		style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(.0f, .0f, .0f, .0f);
		style.Colors[ImGuiCol_PopupBg] = tooltipBgColor;
		style.Colors[ImGuiCol_Border] = Settings::UI::mainColor.Color();
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
		style.Colors[ImGuiCol_FrameBg] = frameBgColor;
		style.Colors[ImGuiCol_FrameBgHovered] = mainColorHovered;
		style.Colors[ImGuiCol_FrameBgActive] = mainColorActive;
		style.Colors[ImGuiCol_TitleBg] = Settings::UI::mainColor.Color();
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
		style.Colors[ImGuiCol_TitleBgActive] = Settings::UI::mainColor.Color();
		style.Colors[ImGuiCol_MenuBarBg] = menubarColor;
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(frameBgColor.x + .05f, frameBgColor.y + .05f, frameBgColor.z + .05f, frameBgColor.w);
		style.Colors[ImGuiCol_ScrollbarGrab] = Settings::UI::mainColor.Color();
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = mainColorHovered;
		style.Colors[ImGuiCol_ScrollbarGrabActive] = mainColorActive;
		style.Colors[ImGuiCol_ComboBg] = frameBgColor;
		style.Colors[ImGuiCol_CheckMark] = Settings::UI::mainColor.Color();
		style.Colors[ImGuiCol_SliderGrab] = mainColorHovered;
		style.Colors[ImGuiCol_SliderGrabActive] = mainColorActive;
		style.Colors[ImGuiCol_Button] = Settings::UI::mainColor.Color();
		style.Colors[ImGuiCol_ButtonHovered] = mainColorHovered;
		style.Colors[ImGuiCol_ButtonActive] = mainColorActive;
		style.Colors[ImGuiCol_Header] = Settings::UI::mainColor.Color();
		style.Colors[ImGuiCol_HeaderHovered] = mainColorHovered;
		style.Colors[ImGuiCol_HeaderActive] = mainColorActive;
		style.Colors[ImGuiCol_Column] = Settings::UI::mainColor.Color();
		style.Colors[ImGuiCol_ColumnHovered] = mainColorHovered;
		style.Colors[ImGuiCol_ColumnActive] = mainColorActive;
		style.Colors[ImGuiCol_ResizeGrip] = Settings::UI::mainColor.Color();
		style.Colors[ImGuiCol_ResizeGripHovered] = mainColorHovered;
		style.Colors[ImGuiCol_ResizeGripActive] = mainColorActive;
		style.Colors[ImGuiCol_CloseButton] = Settings::UI::mainColor.Color();
		style.Colors[ImGuiCol_CloseButtonHovered] = mainColorHovered;
		style.Colors[ImGuiCol_CloseButtonActive] = mainColorActive;
		style.Colors[ImGuiCol_PlotLines] = Settings::UI::mainColor.Color();
		style.Colors[ImGuiCol_PlotLinesHovered] = mainColorHovered;
		style.Colors[ImGuiCol_PlotHistogram] = Settings::UI::mainColor.Color();
		style.Colors[ImGuiCol_PlotHistogramHovered] = mainColorHovered;
		style.Colors[ImGuiCol_TextSelectedBg] = mainColorHovered;
		style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.0f, 0.0f, 0.0f, 0.75f);
	}
		/*{
		
			style->WindowPadding = ImVec2(10.0f, 10.0f);
			style->WindowRounding = 5.0f;
			style->ChildWindowRounding = 5.0f;
			style->FramePadding = ImVec2(5.0f, 4.0f);
			style->FrameRounding = 5.0f;
			style->ItemSpacing = ImVec2(5.0f, 5.0f);
			style->ItemInnerSpacing = ImVec2(10.0f, 10.0f);
			style->IndentSpacing = 15.0f;
			style->ScrollbarSize = 16.0f;
			style->ScrollbarRounding = 5.0f;
			style->GrabMinSize = 7.0f;
			style->GrabRounding = 2.0f;

			style->Colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
			style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
			style->Colors[ImGuiCol_WindowBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
			style->Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.92f, 0.92f, 0.92f, 1.00f);
			style->Colors[ImGuiCol_PopupBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
			style->Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.80f);
			style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			style->Colors[ImGuiCol_FrameBg] = ImVec4(0.71f, 0.71f, 0.71f, 0.39f);
			style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.00f, 0.59f, 0.80f, 0.43f);
			style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.00f, 0.47f, 0.71f, 0.67f);
			style->Colors[ImGuiCol_TitleBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.80f);
			style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.78f, 0.78f, 0.78f, 0.39f);
			style->Colors[ImGuiCol_TitleBgActive] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
			style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
			style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.25f, 0.30f, 0.60f);
			style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.00f, 0.00f, 0.00f, 0.39f);
			style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.59f);
			style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.00f, 0.00f, 0.00f, 0.78f);
			style->Colors[ImGuiCol_ComboBg] = ImVec4(0.78f, 0.78f, 0.78f, 0.98f);
			style->Colors[ImGuiCol_CheckMark] = ImVec4(0.27f, 0.59f, 0.75f, 1.00f);
			style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 0.00f, 0.00f, 0.35f);
			style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.00f, 0.00f, 0.00f, 0.59f);
			style->Colors[ImGuiCol_Button] = ImVec4(0.00f, 0.00f, 0.00f, 0.27f);
			style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.00f, 0.59f, 0.80f, 0.43f);
			style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.00f, 0.47f, 0.71f, 0.67f);
			style->Colors[ImGuiCol_Header] = ImVec4(0.71f, 0.71f, 0.71f, 0.39f);
			style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.20f, 0.51f, 0.67f, 1.00f);
			style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.08f, 0.39f, 0.55f, 1.00f);
			//style->Colors[ImGuiCol_Separator] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
			//style->Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.27f, 0.59f, 0.75f, 1.00f);
			//style->Colors[ImGuiCol_SeparatorActive] = ImVec4(0.08f, 0.39f, 0.55f, 1.00f);
			style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.78f);
			style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.27f, 0.59f, 0.75f, 0.78f);
			style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.08f, 0.39f, 0.55f, 0.78f);
			style->Colors[ImGuiCol_CloseButton] = ImVec4(0.00f, 0.00f, 0.00f, 0.50f);
			style->Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.71f, 0.71f, 0.71f, 0.60f);
			style->Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
			style->Colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
			style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
			style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
			style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
			style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.27f, 0.59f, 0.75f, 1.00f);
			style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.00f, 0.00f, 0.00f, 0.35f);
			once = true;
			
		}*/
	Radar::RenderWindow();
	if (is_renderer_active) 
	{
		static int page = 0;
		ImGui::SetNextWindowSize(ImVec2(960, 645), ImGuiSetCond_FirstUseEver);
		static bool shit;
		ImGui::Begin("Castle", &shit, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders);
		{
			for (int i = 0; i < IM_ARRAYSIZE(tabs); i++)
			{
				int distance = i == page ? 0 : i > page ? i - page : page - i;

				if (ImGui::Button(tabs[i], ImVec2(ImGui::GetWindowSize().x / IM_ARRAYSIZE(tabs) - 9, 0)))
					page = i;

				if (i < IM_ARRAYSIZE(tabs) - 1)
					ImGui::SameLine();
			}

			ImGui::Separator();

			switch (page)
			{
			case 0:
				Aimbot::RenderTab();
				break;
			case 1:
				Triggerbot::RenderTab();
				break;
			case 2:
				/*
				ImGui::Checkbox("ESP", &Settings::ESP::enabled);
				ImGui::Checkbox("Chams", &Settings::ESP::Chams::enabled);
				ImGui::Checkbox("Allies", &Settings::ESP::Filters::allies);
				ImGui::Checkbox("Enemies", &Settings::ESP::Filters::enemies); 
				ImGui::Checkbox("Local Player", &Settings::ESP::Filters::localplayer);
				ImGui::Checkbox("Arms", &Settings::ESP::Chams::Arms::enabled);
				ImGui::Checkbox("Weapon", &Settings::ESP::Chams::Weapon::enabled);
				ImGui::Checkbox("Legit", &Settings::ESP::Filters::legit);
				ImGui::Combo("##CHAMSTYPE", &Settings::ESP::Chams::type, ChamsTypes, IM_ARRAYSIZE(ChamsTypes));
				ImGui::Combo("##ARMTYPE", &Settings::ESP::Chams::Arms::type, ArmsTypes, IM_ARRAYSIZE(ArmsTypes));
				*/
			
			
				ImGui::Checkbox("Enabled", &Settings::ESP::enabled);
				ImGui::Separator();

				ImGui::Columns(2, NULL, true);
				{
					ImGui::BeginChild("COL1", ImVec2(0, 0), true);
					{
						ImGui::Text("ESP");
						ImGui::BeginChild("ESP", ImVec2(0, 0), true);
						ImGui::Text("Type");
						ImGui::Separator();
						ImGui::Columns(2, NULL, true);
						{
							ImGui::Checkbox("Outline Box", &Settings::ESP::Boxes::enabled);
							//SetTooltip("Outline players with a box");
							ImGui::Checkbox("Chams", &Settings::ESP::Chams::enabled);
							//SetTooltip("Change players' model texture");
							ImGui::Checkbox("Health", &Settings::ESP::Bars::enabled);
							//SetTooltip("Show a players health with a bar");
							ImGui::Checkbox("Tracers", &Settings::ESP::Tracers::enabled);
							//SetTooltip("Draws a line to each player");
							ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
							ImGui::Text("Bar Color");
							ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
							ImGui::Text("Team Color");
							ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
							ImGui::Checkbox("Bullet Tracers", &Settings::ESP::BulletTracers::enabled);
							//SetTooltip("Adds a line showing where a player is aiming");
							ImGui::Checkbox("Head Dot", &Settings::ESP::HeadDot::enabled);
							//SetTooltip("Adds a Dot on the Head of a player");
						}
						ImGui::NextColumn();
						{
							ImGui::PushItemWidth(-1);
							ImGui::Combo("##BOXTYPE", (int*)& Settings::ESP::Boxes::type, BoxTypes, IM_ARRAYSIZE(BoxTypes));
							ImGui::Combo("##CHAMSTYPE", (int*)& Settings::ESP::Chams::type, ChamsTypes, IM_ARRAYSIZE(ChamsTypes));
							ImGui::Combo("##BARTYPE", (int*)& Settings::ESP::Bars::type, BarTypes, IM_ARRAYSIZE(BarTypes));
							ImGui::Combo("##TRACERTYPE", (int*)& Settings::ESP::Tracers::type, TracerTypes, IM_ARRAYSIZE(TracerTypes));
							ImGui::Combo("##BARCOLTYPE", (int*)& Settings::ESP::Bars::colorType, BarColorTypes, IM_ARRAYSIZE(BarColorTypes));
							ImGui::Combo("##TEAMCOLTYPE", (int*)& Settings::ESP::teamColorType, TeamColorTypes, IM_ARRAYSIZE(TeamColorTypes));
							ImGui::PopItemWidth();
							ImGui::Checkbox("Skeleton", &Settings::ESP::Skeleton::enabled);
							//SetTooltip("Show a players skeleton");
							ImGui::PushItemWidth(-1);
							ImGui::SliderFloat("##HDOTSIZE", &Settings::ESP::HeadDot::size, 1.f, 10.f, "Size: %0.3f");
							ImGui::PopItemWidth();
						}
						ImGui::Columns(1);
						ImGui::Separator();
						ImGui::Text("Filter");
						ImGui::Separator();
						ImGui::Columns(2, NULL, true);
						{
							ImGui::Checkbox("Enemies", &Settings::ESP::Filters::enemies);
							//SetTooltip("Show enemies");
							ImGui::Checkbox("Chickens", &Settings::ESP::Filters::chickens);
							//SetTooltip("Show chickens");
							ImGui::Checkbox("LocalPlayer", &Settings::ESP::Filters::localplayer);
							//SetTooltip("Show localplayer");
							ImGui::Checkbox("Legit Mode", &Settings::ESP::Filters::legit);
							//SetTooltip("Hide enemies behind walls");
						}
						ImGui::NextColumn();
						{
							ImGui::Checkbox("Allies", &Settings::ESP::Filters::allies);
							//SetTooltip("Show team mates");
							ImGui::Checkbox("Fish", &Settings::ESP::Filters::fishes);
							//SetTooltip("Show fish");
							ImGui::Checkbox("Smoke Check", &Settings::ESP::Filters::smokeCheck);
							//SetTooltip("Mark players behind smokes as invisible");
							ImGui::Checkbox("Visiblity Check", &Settings::ESP::Filters::visibilityCheck);
							//SetTooltip("Change color of outlined box based on whether you see them");
						}
						ImGui::Columns(1);
						ImGui::Separator();
						ImGui::Text("Player Information");
						ImGui::Separator();
						ImGui::Columns(2, NULL, true);
						{
							ImGui::Checkbox("Clan", &Settings::ESP::Info::clan);
							//SetTooltip("Show clan");
							ImGui::Checkbox("Rank", &Settings::ESP::Info::rank);
							//SetTooltip("Show rank");
							ImGui::PushID(1);
							ImGui::Checkbox("Health", &Settings::ESP::Info::health);
							//SetTooltip("Show health");
							ImGui::PopID();
							ImGui::Checkbox("Scoped", &Settings::ESP::Info::scoped);
							//SetTooltip("Show whether they are scoped");
							ImGui::Checkbox("Flashed", &Settings::ESP::Info::flashed);
							//SetTooltip("Show whether they are flashed");
							ImGui::Checkbox("Defuse Kit", &Settings::ESP::Info::hasDefuser);
							//SetTooltip("Show whether they have a defuse kit");
							ImGui::Checkbox("Grabbing Hostage", &Settings::ESP::Info::grabbingHostage);
							//SetTooltip("Show whether they are grabbing a hostage");
							ImGui::Checkbox("Location", &Settings::ESP::Info::location);
							//SetTooltip("Show location");
						}
						ImGui::NextColumn();
						{
							ImGui::Checkbox("Name", &Settings::ESP::Info::name);
							//SetTooltip("Show name");
							ImGui::Checkbox("Steam ID", &Settings::ESP::Info::steamId);
							//SetTooltip("Show Steam ID");
							ImGui::Checkbox("Weapon", &Settings::ESP::Info::weapon);
							//SetTooltip("Show held weapon");
							ImGui::Checkbox("Reloading", &Settings::ESP::Info::reloading);
							//SetTooltip("Show whether they are reloading");
							ImGui::Checkbox("Planting", &Settings::ESP::Info::planting);
							//SetTooltip("Show whether they are planting");
							ImGui::Checkbox("Defusing", &Settings::ESP::Info::defusing);
							//SetTooltip("Show whether they are defusing");
							ImGui::Checkbox("Rescuing Hostage", &Settings::ESP::Info::rescuing);
							//SetTooltip("Show whether they are rescuing a hostage");
						}

						ImGui::Columns(1);
						ImGui::Separator();
						ImGui::Text("World");
						ImGui::Separator();
						ImGui::Columns(2, NULL, true);
						{
							ImGui::Checkbox("Weapons", &Settings::ESP::Filters::weapons);
							//SetTooltip("Show weapons on floor");
							ImGui::Checkbox("Throwables", &Settings::ESP::Filters::throwables);
							//SetTooltip("Show throwables");
							ImGui::Checkbox("Entity Glow", &Settings::ESP::Glow::enabled);
							//SetTooltip("Show a glow around entities");
						}
						ImGui::NextColumn();
						{
							ImGui::Checkbox("Bomb", &Settings::ESP::Filters::bomb);
							//SetTooltip("Show bomb when planted");
							ImGui::Checkbox("Defuse Kits", &Settings::ESP::Filters::defusers);
							//SetTooltip("Show defuse kits on floor");
							ImGui::Checkbox("Hostages", &Settings::ESP::Filters::hostages);
							//SetTooltip("Show hostages");
						}
						ImGui::Columns(1);
						ImGui::EndChild();
						ImGui::EndChild();
					}
				}

				ImGui::NextColumn();
				{
					ImGui::BeginChild("Chams", ImVec2(0, 0), true);
					{
						ImGui::Text("Crosshair");
						ImGui::Separator();
						ImGui::Columns(2, NULL, true);
						{
							ImGui::Checkbox("Recoil Crosshair", &Settings::Recoilcrosshair::enabled);
							//SetTooltip("Show a crosshair based on recoil");
							ImGui::Checkbox("FOV Circle", &Settings::ESP::FOVCrosshair::enabled);
							//SetTooltip("Show circle around aimbot FOV");
						}
						ImGui::NextColumn();
						{
							ImGui::Checkbox("Only When Shooting", &Settings::Recoilcrosshair::showOnlyWhenShooting);
							//SetTooltip("Only show recoil crosshair when shooting");
							ImGui::Checkbox("Filled", &Settings::ESP::FOVCrosshair::filled);
							//SetTooltip("Fill the fov circle");
						}
						ImGui::Columns(1);
						ImGui::Separator();
						ImGui::Text("Other Visual Settings");
						ImGui::Separator();
						ImGui::Columns(2, NULL, true);
						{
							ImGui::Checkbox("Arms", &Settings::ESP::Chams::Arms::enabled);
							//SetTooltip("Apply chams to arms");
							ImGui::Checkbox("Dlights", &Settings::Dlights::enabled);
							//SetTooltip("Adds a light source to players");
							ImGui::Checkbox("No Flash", &Settings::Noflash::enabled);
							//SetTooltip("Hide flashbang effect");
							ImGui::Checkbox("Show Footsteps", &Settings::ESP::Sounds::enabled);
							//SetTooltip("Shows you footsteps in 3D space");
							ImGui::Checkbox("No View Punch", &Settings::View::NoViewPunch::enabled);
							//SetTooltip("Disables view punch when shooting");
							ImGui::Checkbox("Weapons", &Settings::ESP::Chams::Weapon::enabled);
							//SetTooltip("Apply chams to weapons");
							ImGui::Checkbox("No Sky", &Settings::NoSky::enabled);
							//SetTooltip("Allows for the skybox to be colored or disabled");
							ImGui::Checkbox("No Smoke", &Settings::NoSmoke::enabled);
							//SetTooltip("Disables smoke rendering");
						}
						ImGui::NextColumn();
						{
							ImGui::PushItemWidth(-1);
							ImGui::Combo("##ARMSTYPE", (int*)& Settings::ESP::Chams::Arms::type, ArmsTypes, IM_ARRAYSIZE(ArmsTypes));
							ImGui::SliderFloat("##DLIGHTRADIUS", &Settings::Dlights::radius, 0, 1000, "Radius: %0.f");
							ImGui::SliderFloat("##NOFLASHAMOUNT", &Settings::Noflash::value, 0, 255, "Amount: %0.f");
							ImGui::SliderInt("##SOUNDSTIME", &Settings::ESP::Sounds::time, 250, 5000, "Timeout: %0.f");
							ImGui::PopItemWidth();
							ImGui::Checkbox("No Aim Punch", &Settings::View::NoAimPunch::enabled);
							//SetTooltip("Disables aim punch when shooting");
							ImGui::Checkbox("ASUS Walls", &Settings::ASUSWalls::enabled);
							//SetTooltip("Makes wall textures transparent");
							ImGui::Checkbox("No Scope Border", &Settings::NoScopeBorder::enabled);
							//SetTooltip("Disables black scope silhouette");
						}
						ImGui::Columns(1);
						ImGui::Separator();
						ImGui::Text("Radar");
						ImGui::Separator();
						ImGui::Columns(2, NULL, true);
						{
							ImGui::Checkbox("Radar", &Settings::Radar::enabled);
							//SetTooltip("Shows players on the custom radar");
							ImGui::PushItemWidth(-1);
							ImGui::Combo("##RADARTEAMCOLTYPE", (int*)& Settings::Radar::teamColorType, TeamColorTypes, IM_ARRAYSIZE(TeamColorTypes));
							ImGui::PopItemWidth();
							ImGui::Checkbox("Enemies", &Settings::Radar::enemies);
							ImGui::Checkbox("Bomb", &Settings::Radar::bomb);
							ImGui::Checkbox("Legit", &Settings::Radar::legit);
							ImGui::Checkbox("In-game Radar", &Settings::Radar::InGame::enabled);
							//SetTooltip("Shows players on the in-game radar");
						}
						ImGui::NextColumn();
						{
							ImGui::PushItemWidth(-1);
							ImGui::SliderFloat("##RADARZOOM", &Settings::Radar::zoom, 0.f, 100.f, "Zoom: %0.f");
							ImGui::SliderFloat("##RADARICONSSCALE", &Settings::Radar::iconsScale, 2, 16, "Icons Scale: %0.1f");
							ImGui::PopItemWidth();
							ImGui::Checkbox("Allies", &Settings::Radar::allies);
							ImGui::Checkbox("Defuser", &Settings::Radar::defuser);
							ImGui::Checkbox("Visibility Check", &Settings::Radar::visibilityCheck);
							ImGui::Checkbox("Smoke Check", &Settings::Radar::smokeCheck);
						}
						ImGui::Columns(1);
						ImGui::Separator();

						ImGui::Text("Hitmarkers");
						ImGui::Separator();
						ImGui::Columns(2, NULL, true);
						{
							ImGui::Checkbox("Hitmarkers", &Settings::ESP::Hitmarker::enabled);
							//SetTooltip("Notify when you hit another player");

							ImGui::Checkbox("Enemies##HITMARKERS", &Settings::ESP::Hitmarker::enemies);
							ImGui::Checkbox("Allies##HITMARKERS", &Settings::ESP::Hitmarker::allies);
							ImGui::Checkbox("Damage##HITMARKERS", &Settings::ESP::Hitmarker::Damage::enabled);
							//SetTooltip("Show dealt damage next to the hitmarker");
						}
						ImGui::NextColumn();
						{
							ImGui::PushItemWidth(-1);
							ImGui::SliderInt("##HITMARKERDUR", &Settings::ESP::Hitmarker::duration, 250, 3000, "Timeout: %0.f");
							ImGui::SliderInt("##HITMARKERSIZE", &Settings::ESP::Hitmarker::size, 1, 32, "Size: %0.f");
							ImGui::SliderInt("##HITMARKERGAP", &Settings::ESP::Hitmarker::innerGap, 1, 16, "Gap: %0.f");
							ImGui::PopItemWidth();
						}
						ImGui::Columns(1);
						ImGui::Separator();

						ImGui::EndChild();
					}
				}
				ImGui::Columns(1);
				break;
			case 3:
				HvH::RenderTab();
				break;
			case 4:

				if (!pEngine->IsInGame() || (*csPlayerResource && !(*csPlayerResource)->GetConnected(currentPlayer)))
					currentPlayer = -1;

				ImGui::ListBoxHeader("##PLAYERS", ImVec2(-1, (ImGui::GetWindowSize().y - 95)));
				if (pEngine->IsInGame() && *csPlayerResource)
				{
					ImGui::Columns(6);

					ImGui::Text("ID");
					ImGui::NextColumn();

					ImGui::Text("Nickname");
					ImGui::NextColumn();

					ImGui::Text("Team");
					ImGui::NextColumn();

					ImGui::Text("Clan tag");
					ImGui::NextColumn();

					ImGui::Text("Rank");
					ImGui::NextColumn();

					ImGui::Text("Wins");
					ImGui::NextColumn();

					std::unordered_map<TeamID, std::vector<int>, Util::IntHash<TeamID>> players = {
						{ TeamID::TEAM_UNASSIGNED,{} },
						{ TeamID::TEAM_SPECTATOR,{} },
						{ TeamID::TEAM_TERRORIST,{} },
						{ TeamID::TEAM_COUNTER_TERRORIST,{} },
					};

					for (int i = 1; i < pEngine->GetMaxClients(); i++)
					{
						if (i == pEngine->GetLocalPlayer())
							continue;

						if (!(*csPlayerResource)->GetConnected(i))
							continue;

						players[(*csPlayerResource)->GetTeam(i)].push_back(i);
					}

					for (int team = (int)TeamID::TEAM_UNASSIGNED; team <= (int)TeamID::TEAM_COUNTER_TERRORIST; team++)
					{
						char* teamName = strdup("");
						switch ((TeamID)team)
						{
						case TeamID::TEAM_UNASSIGNED:
							teamName = strdup("Unassigned");
							break;
						case TeamID::TEAM_SPECTATOR:
							teamName = strdup("Spectator");
							break;
						case TeamID::TEAM_TERRORIST:
							teamName = strdup("Terrorist");
							break;
						case TeamID::TEAM_COUNTER_TERRORIST:
							teamName = strdup("Counter Terrorist");
							break;
						}

						for (auto it : players[(TeamID)team])
						{
							std::string id = std::to_string(it);

							IEngineClient::player_info_t entityInformation;
							pEngine->GetPlayerInfo(it, &entityInformation);

							//if (entityInformation.ishltv)
							//	continue;

							ImGui::Separator();

							if (ImGui::Selectable(id.c_str(), it == currentPlayer, ImGuiSelectableFlags_SpanAllColumns))
								currentPlayer = it;
							ImGui::NextColumn();

							ImGui::Text("%s", entityInformation.name);
							ImGui::NextColumn();

							ImGui::Text("%s", teamName);
							ImGui::NextColumn();

							ImGui::Text("%s", (*csPlayerResource)->GetClan(it));
							ImGui::NextColumn();

							ImGui::Text("%s", ESP::ranks[*(*csPlayerResource)->GetCompetitiveRanking(it)]);
							ImGui::NextColumn();

							ImGui::Text("%d", *(*csPlayerResource)->GetCompetitiveWins(it));
							ImGui::NextColumn();
						}
					}
				}
				ImGui::ListBoxFooter();

				if (currentPlayer != -1)
				{
					IEngineClient::player_info_t entityInformation;
					pEngine->GetPlayerInfo(currentPlayer, &entityInformation);

					ImGui::Columns(2);
					{
						bool isFriendly = std::find(Aimbot::friends.begin(), Aimbot::friends.end(), entityInformation.xuid) != Aimbot::friends.end();
						if (ImGui::Checkbox("Friend", &isFriendly))
						{
							if (isFriendly)
								Aimbot::friends.push_back(entityInformation.xuid);
							else
								Aimbot::friends.erase(std::find(Aimbot::friends.begin(), Aimbot::friends.end(), entityInformation.xuid));
						}

						bool shouldResolve = std::find(Resolver::Players.begin(), Resolver::Players.end(), entityInformation.xuid) != Resolver::Players.end();
						if (ImGui::Checkbox("Resolver", &shouldResolve))
						{
							if (shouldResolve)
								Resolver::Players.push_back(entityInformation.xuid);
							else
								Resolver::Players.erase(std::find(Resolver::Players.begin(), Resolver::Players.end(), entityInformation.xuid));
						}
					}
					ImGui::NextColumn();
					{
						if (ImGui::Button("Steal name"))
						{
							std::string name;
							const char* ass = entityInformation.name;
							name = ass;

							strcpy(nickname, name.c_str());
							NameChanger::SetName(name.c_str());
						}

						const char* clanTag = (*csPlayerResource)->GetClan(currentPlayer);
						if (strlen(clanTag) > 0 && ImGui::Button("Steal clan tag"))
						{
							Settings::ClanTagChanger::enabled = true;
							strcpy(Settings::ClanTagChanger::value, clanTag);
							Settings::ClanTagChanger::type = ClanTagType::STATIC;

							ClanTagChanger::UpdateClanTagCallback();
						}
					}
				}
				break;
		//	case 5:
				//Models::RenderTab();
			//	break;
			case 5:
				ImGui::PushItemWidth(138);
				ImGui::InputText("", buf, IM_ARRAYSIZE(buf));
				ImGui::PopItemWidth();
				ImGui::SameLine();
				if (ImGui::Button("Save"))
				{
					if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, path)))
					{
						folder = std::string(path) + "\\Castle\\";
						file = std::string(folder) + std::string(buf) + ".ini";
						Settings::LoadDefaultsOrSave(file);
					}
				}
				ImGui::SameLine();
				if (ImGui::Button("Load"))
				{
					if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, path)))
					{
						folder = std::string(path) + "\\Castle\\";
						file = std::string(folder) + std::string(buf) + ".ini";
						Settings::LoadConfig(file);
					}
				}
				ImGui::SameLine();
				if (ImGui::Button("Remove"))
				{
					if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, path)))
					{
						folder = std::string(path) + "\\Castle\\";
						file = std::string(folder) + std::string(buf) + ".ini";
						remove(file.c_str());
					}
				}
				ImGui::PushItemWidth(178);

				ImGui::Columns(2, NULL, true);
				{
					ImGui::BeginChild("Child1", ImVec2(0, 0), true);
					{
						ImGui::Text("Movement");
						ImGui::Separator();

						ImGui::Checkbox("Bunny Hop", &Settings::BHop::enabled);
						//SetTooltip("Auto bunny hop");
						ImGui::Columns(2, NULL, true);
						{
							ImGui::Checkbox("Edge Jump", &Settings::EdgeJump::enabled);
							//SetTooltip("Jumps off the edges");
						}
						ImGui::NextColumn();
						{
							ImGui::Combo("##edgejumpkey", (int*)&Settings::EdgeJump::key, ButtonNames, IM_ARRAYSIZE(ButtonNames));
						}
						ImGui::Columns(1);

						ImGui::Separator();
						ImGui::Columns(2, NULL, true);
						{
							ImGui::Checkbox("Auto Strafe", &Settings::AutoStrafe::enabled);
							//SetTooltip("Auto strafe when bunny hopping");
						}
						ImGui::NextColumn();
						{
							ImGui::PushItemWidth(-1);
							ImGui::Combo("##STRAFETYPE", (int*)& Settings::AutoStrafe::type, strafeTypes, IM_ARRAYSIZE(strafeTypes));
							ImGui::PopItemWidth();
						}

						if (Settings::AutoStrafe::type == AutostrafeType::AS_RAGE)
						{
							ImGui::Checkbox("Silent", &Settings::AutoStrafe::silent);
							//SetTooltip("Strafes won't be visible for spectators");
						}

						ImGui::Columns(1);
						ImGui::Separator();
						ImGui::Text("Spammer");
						ImGui::Separator();

						ImGui::Columns(3, NULL, true);
						{
							ImGui::Checkbox("Kill Messages", &Settings::Spammer::KillSpammer::enabled);
							//SetTooltip("Spams a kill message when killing an enemy");
						}
						ImGui::NextColumn();
						{
							ImGui::Checkbox("Team Chat###SAY_TEAM1", &Settings::Spammer::KillSpammer::sayTeam);
							//SetTooltip("Only show kill message in team chat");
						}
						ImGui::NextColumn();
						{
							if (ImGui::Button("Options###KILL"))
								ImGui::OpenPopup("options_kill");

							ImGui::SetNextWindowSize(ImVec2(565, 268), ImGuiSetCond_Always);
							if (ImGui::BeginPopup("options_kill"))
							{
								static int killSpammerMessageCurrent = -1;
								static char killSpammerMessageBuf[126];

								ImGui::PushItemWidth(445);
								ImGui::InputText("###SPAMMERMESSAGE", killSpammerMessageBuf, IM_ARRAYSIZE(killSpammerMessageBuf));
								ImGui::PopItemWidth();
								ImGui::SameLine();

								if (ImGui::Button("Add"))
								{
									if (strlen(killSpammerMessageBuf) > 0)
										Settings::Spammer::KillSpammer::messages.push_back(std::string(killSpammerMessageBuf));

									strcpy(killSpammerMessageBuf, "");
								}
								ImGui::SameLine();

								if (ImGui::Button("Remove"))
									if (killSpammerMessageCurrent > -1 && (int)Settings::Spammer::KillSpammer::messages.size() > killSpammerMessageCurrent)
										Settings::Spammer::KillSpammer::messages.erase(Settings::Spammer::KillSpammer::messages.begin() + killSpammerMessageCurrent);

								ImGui::PushItemWidth(550);
								//ImGui::ListBox("", &killSpammerMessageCurrent, Settings::Spammer::KillSpammer::messages, 10);
								ImGui::PopItemWidth();

								ImGui::EndPopup();
							}
						}

						ImGui::Columns(1);
						ImGui::Checkbox("Radio Commands", &Settings::Spammer::RadioSpammer::enabled);

						ImGui::Columns(3, NULL, true);
						{
							ImGui::Combo("###SPAMMERYPE", (int*)&Settings::Spammer::type, spammerTypes, IM_ARRAYSIZE(spammerTypes));
						}
						ImGui::NextColumn();
						{
							ImGui::Checkbox("Team Chat###SAY_TEAM2", &Settings::Spammer::say_team);
							//SetTooltip("Only spam messages in team chat");
						}
						ImGui::NextColumn();
						{
							if (Settings::Spammer::type != SpammerType::SPAMMER_NONE && ImGui::Button("Options###SPAMMER"))
								ImGui::OpenPopup("options_spammer");

							if (Settings::Spammer::type == SpammerType::SPAMMER_NORMAL)
								ImGui::SetNextWindowSize(ImVec2(565, 268), ImGuiSetCond_Always);
							else if (Settings::Spammer::type == SpammerType::SPAMMER_POSITIONS)
								ImGui::SetNextWindowSize(ImVec2(200, 240), ImGuiSetCond_Always);

							if (Settings::Spammer::type != SpammerType::SPAMMER_NONE && ImGui::BeginPopup("options_spammer"))
							{
								if (Settings::Spammer::type == SpammerType::SPAMMER_NORMAL)
								{
									static int spammerMessageCurrent = -1;
									static char spammerMessageBuf[126];

									ImGui::PushItemWidth(445);
									ImGui::InputText("###SPAMMERMESSAGE", spammerMessageBuf, IM_ARRAYSIZE(spammerMessageBuf));
									ImGui::PopItemWidth();
									ImGui::SameLine();

									if (ImGui::Button("Add"))
									{
										if (strlen(spammerMessageBuf) > 0)
											Settings::Spammer::NormalSpammer::messages.push_back(std::string(spammerMessageBuf));

										strcpy(spammerMessageBuf, "");
									}
									ImGui::SameLine();

									if (ImGui::Button("Remove"))
										if (spammerMessageCurrent > -1 && (int)Settings::Spammer::NormalSpammer::messages.size() > spammerMessageCurrent)
											Settings::Spammer::NormalSpammer::messages.erase(Settings::Spammer::NormalSpammer::messages.begin() + spammerMessageCurrent);

									ImGui::PushItemWidth(550);
									//ImGui::ListBox("", &spammerMessageCurrent, Settings::Spammer::NormalSpammer::messages, 10);
									ImGui::PopItemWidth();
								}
								else if (Settings::Spammer::type == SpammerType::SPAMMER_POSITIONS)
								{
									ImGui::PushItemWidth(185);
									ImGui::Combo("###POSITIONSTEAM", &Settings::Spammer::PositionSpammer::team, teams, IM_ARRAYSIZE(teams));
									ImGui::PopItemWidth();
									ImGui::Separator();
									ImGui::Checkbox("Show Name", &Settings::Spammer::PositionSpammer::showName);
									ImGui::Checkbox("Show Weapon", &Settings::Spammer::PositionSpammer::showWeapon);
									ImGui::Checkbox("Show Rank", &Settings::Spammer::PositionSpammer::showRank);
									ImGui::Checkbox("Show Wins", &Settings::Spammer::PositionSpammer::showWins);
									ImGui::Checkbox("Show Health", &Settings::Spammer::PositionSpammer::showHealth);
									ImGui::Checkbox("Show Money", &Settings::Spammer::PositionSpammer::showMoney);
									ImGui::Checkbox("Show Last Place", &Settings::Spammer::PositionSpammer::showLastplace);
								}

								ImGui::EndPopup();
							}
						}
						ImGui::Columns(1);
						ImGui::Separator();
						ImGui::Text("FOV");
						ImGui::Separator();
						ImGui::Columns(2, NULL, true);
						{
							ImGui::Checkbox("FOV", &Settings::FOVChanger::enabled);
							//SetTooltip("Change camera FOV");
							ImGui::Checkbox("Viewmodel FOV", &Settings::FOVChanger::viewmodelEnabled);
							//SetTooltip("Change viewmodel FOV");
							ImGui::Checkbox("Ignore Scope", &Settings::FOVChanger::ignoreScope);
							//SetTooltip("Disable FOV Changer while scoping");
						}
						ImGui::NextColumn();
						{
							ImGui::PushItemWidth(-1);
							ImGui::SliderFloat("##FOVAMOUNT", &Settings::FOVChanger::value, 0, 180);
							ImGui::SliderFloat("##MODELFOVAMOUNT", &Settings::FOVChanger::viewmodelValue, 0, 360);
							ImGui::PopItemWidth();
						}
						ImGui::Columns(1);
						ImGui::Separator();
						ImGui::Text("Third Person");
						ImGui::Separator();
						ImGui::Columns(2, NULL, true);
						{
							ImGui::Checkbox("Enabled", &Settings::ThirdPerson::enabled);
							ImGui::Checkbox("Real Angles", &Settings::ThirdPerson::Real);
							//SetTooltip("Switches from first-person perspective to third-person perspective.");
						}
						ImGui::NextColumn();
						{
							ImGui::PushItemWidth(-1);
							ImGui::SliderFloat("##TPCAMOFFSET", &Settings::ThirdPerson::distance, 0.f, 500.f, "Camera Offset: %0.f");
							ImGui::PopItemWidth();
							ImGui::Checkbox("Fake Angles", &Settings::ThirdPerson::Fake);
						}
						ImGui::Columns(1);
						ImGui::Separator();
						ImGui::Text("Grenade Helper");
						ImGui::Separator();
						ImGui::Columns(2, NULL, true);
						{
							ImGui::Checkbox("Enabled ###ghenabled", &Settings::GrenadeHelper::enabled);
							//SetTooltip("Show Saved Grenade Throws, Visuals required.");
						}
						ImGui::NextColumn();
						{
							ImGui::Checkbox("Only matching ###match", &Settings::GrenadeHelper::onlyMatchingInfos);
							//SetTooltip("Shows only the info's for your equipped Grenade.");
						}

						ImGui::Columns(2);
						{
							if (ImGui::Button("Aimassist", ImVec2(-1, 0)))
								ImGui::OpenPopup("optionAimAssist");
							ImGui::SetNextWindowSize(ImVec2(200, 120), ImGuiSetCond_Always);
							if (ImGui::BeginPopup("optionAimAssist"))
							{
								ImGui::PushItemWidth(-1);
								ImGui::Checkbox("Enabled", &Settings::GrenadeHelper::aimAssist);
								//SetTooltip("Whether the Aimassist will help you throw Grenades.");
								ImGui::SliderFloat("###aimstep", &Settings::GrenadeHelper::aimStep, 0, 10, "Speed: %0.3f");
								//SetTooltip("The speed at which the Aimassist helps.");
								ImGui::SliderFloat("###aimfov", &Settings::GrenadeHelper::aimFov, 0, 180, "Fov: %0.2f");
								//SetTooltip("The Fov at which the Aimassist starts.");
								ImGui::SliderFloat("###aimdistance", &Settings::GrenadeHelper::aimDistance, 0, 100, "Distance: %0.2f");
								//SetTooltip("The distance at which the Aimassist starts.");
								ImGui::PopItemWidth();

								ImGui::EndPopup();
							}
						}
						ImGui::NextColumn();
						{
							if (ImGui::Button("Add Info", ImVec2(-1, 0)))
								ImGui::OpenPopup("addinfo_throw");

							ImGui::SetNextWindowSize(ImVec2(565, 268), ImGuiSetCond_Always);
							if (ImGui::BeginPopup("addinfo_throw"))
							{
								static int throwMessageCurrent = -1;
								static char inputName[40];
								static int tType = (int)ThrowType::NORMAL;
								static int gType = (int)GrenadeType::SMOKE;

								if (pEngine->IsInGame())
								{
									C_BasePlayer* localPlayer = (C_BasePlayer*)pEntityList->GetClientEntity(pEngine->GetLocalPlayer());
									if (localPlayer)
									{
										C_BaseCombatWeapon *activeWeapon = (C_BaseCombatWeapon *)pEntityList->GetClientEntityFromHandle(
											localPlayer->GetActiveWeapon());
										if (activeWeapon &&
											activeWeapon->GetCSWpnData()->GetWeaponType() == CSWeaponType::WEAPONTYPE_GRENADE)
											gType = (int)getGrenadeType(activeWeapon);
									}
								}
								ImGui::Columns(1);
								ImGui::PushItemWidth(500);
								ImGui::InputText("", inputName, sizeof(inputName));
								ImGui::PopItemWidth();
								ImGui::SameLine();
								if (ImGui::Button("Add") && pEngine->IsInGame() && Settings::GrenadeHelper::actMapName.length() > 0)
								{
									C_BasePlayer* localPlayer = (C_BasePlayer*)pEntityList->GetClientEntity(pEngine->GetLocalPlayer());
									if (strlen(inputName) > 0)
									{
										GrenadeInfo n = GrenadeInfo((GrenadeType)gType, localPlayer->GetEyePosition(), *localPlayer->GetVAngles(), (ThrowType)tType, inputName);
										Settings::GrenadeHelper::grenadeInfos.push_back(n);
									//	std::string path = GetGhConfigDirectory() << Settings::GrenadeHelper::actMapName;
									//	if (!DoesFileExist(path.c_str()))
										//	mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
									//	Settings::SaveGrenadeInfo(path << "/config.json");
									}
									strcpy(inputName, "");
								}
								ImGui::Columns(2);
								ImGui::Combo("###Throwtype", &tType, throwTypes, IM_ARRAYSIZE(throwTypes));
								ImGui::NextColumn();
								ImGui::Combo("###Grenadetype", &gType, grenadeTypes, IM_ARRAYSIZE(grenadeTypes));
								ImGui::Columns(1);
								ImGui::Separator();
								ImGui::PushItemWidth(550);
								auto lambda = [](void* data, int idx, const char** out_text)
								{
									*out_text = Settings::GrenadeHelper::grenadeInfos.at(idx).name.c_str();
									return *out_text != NULL;
								};
								ImGui::ListBox("", &throwMessageCurrent, lambda, NULL, Settings::GrenadeHelper::grenadeInfos.size(), 7);
								ImGui::PopItemWidth();
								ImGui::Columns(1);
								if (ImGui::Button("Remove", ImVec2(ImGui::GetWindowWidth(), 30)))
									if (throwMessageCurrent > -1 && (int)Settings::GrenadeHelper::grenadeInfos.size() > throwMessageCurrent)
									{
										Settings::GrenadeHelper::grenadeInfos.erase(Settings::GrenadeHelper::grenadeInfos.begin() + throwMessageCurrent);
										//pstring path = GetGhConfigDirectory() << Settings::GrenadeHelper::actMapName;
										//if (!DoesFileExist(path.c_str()))
									//		mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
									//	Settings::SaveGrenadeInfo(path << "/config.json");
									}
								ImGui::EndPopup();
							}
						}
						ImGui::Columns(1);
						ImGui::Separator();
						ImGui::Text("WalkBot");
						ImGui::Separator();
						ImGui::Columns(1, NULL, true);
						{
							ImGui::Text("Dust 2 Walkbot");

							ImGui::Checkbox("Enable", &Settings::WalkBot::enabled);

							ImGui::SameLine();
							if (ImGui::Button("Reset")) {
								Settings::WalkBot::forceReset = true;
							}

							ImGui::Separator();

							ImGui::Checkbox("Autobuy", &Settings::WalkBot::autobuy);

							ImGui::SameLine();
							ImGui::SliderInt("", &Settings::WalkBot::autobuyAt, 0, 16000, "Autobuy At $%0.f");
						}
						ImGui::Columns(1);
						ImGui::Separator();

						ImGui::Text("Other");
						ImGui::Separator();
						ImGui::Columns(1, NULL, true);
						{
							ImGui::Checkbox("WackWalk", &Settings::FakeWalk::enabled);
							ImGui::Checkbox("WackTrack", &Settings::Aimbot::BackTrack);
							ImGui::SliderInt("##stupidandfake", &Settings::Aimbot::BackTrackAmount, 0, 50, "Ticks to WackTrack %0.f");
							ImGui::Combo("##WackTrackKey", (int*)&Settings::Aimbot::BackTrackKey, ButtonNames, IM_ARRAYSIZE(ButtonNames));
						}
						ImGui::Columns(1);
						ImGui::Separator();

						if (ImGui::Button("Tracer Effect", ImVec2(-1, 0)))
							ImGui::OpenPopup("##TracerEffectWindow");
						ImGui::SetNextWindowSize(ImVec2(320, 120), ImGuiSetCond_Always);
						if (ImGui::BeginPopup("##TracerEffectWindow"))
						{
							ImGui::PushItemWidth(-1);
							if (Settings::TracerEffects::serverSide)
							{
								Settings::TracerEffects::frequency = 1;
								Settings::TracerEffects::effect = TracerEffects_t::TASER;
							}
							ImGui::Combo("##TracerEffects", (int*)& Settings::TracerEffects::effect, tracerEffectNames, IM_ARRAYSIZE(tracerEffectNames));
							ImGui::Checkbox("Enable Tracers", &Settings::TracerEffects::enabled);
							ImGui::Checkbox("Server Sided?", &Settings::TracerEffects::serverSide);
							//SetTooltip("Requires a Taser in your Inventory.\nCan only shoot one shot at a time\nOnly Works with Kisak Snot");
							ImGui::Columns(2, NULL, false);
							{
								ImGui::SliderInt("##TracerFreq", &Settings::TracerEffects::frequency, 0, 10, "Freq: %0.f");
							}
							ImGui::NextColumn();
							{
								if (ImGui::Button("Restore Tracers")) {
									TracerEffect::RestoreTracers();
								}
							}
							ImGui::PopItemWidth();
							ImGui::EndPopup();
						}
						ImGui::EndChild();
					}
				}
				ImGui::NextColumn();
				{
					ImGui::BeginChild("Child2", ImVec2(0, 0), true);
					{
						ImGui::Text("Clantag");
						ImGui::Separator();
						ImGui::Checkbox("Enabled", &Settings::ClanTagChanger::enabled);
						//SetTooltip("Display a custom clantag");
						ImGui::Separator();
						ImGui::Columns(2, NULL, true);
						{
							ImGui::PushItemWidth(-1);
							if (ImGui::InputText("##CLANTAG", Settings::ClanTagChanger::value, 30))
								ClanTagChanger::UpdateClanTagCallback();
							ImGui::PopItemWidth();

							ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
							ImGui::Text("Animation Speed");
						}
						ImGui::NextColumn();
						{
							ImGui::PushItemWidth(-1);
							if (ImGui::Combo("##ANIMATIONTYPE", (int*)& Settings::ClanTagChanger::type, animationTypes, IM_ARRAYSIZE(animationTypes)))
								ClanTagChanger::UpdateClanTagCallback();
							if (ImGui::SliderInt("##ANIMATIONSPEED", &Settings::ClanTagChanger::animationSpeed, 0, 2000))
								ClanTagChanger::UpdateClanTagCallback();
							ImGui::PopItemWidth();
						}
						ImGui::Columns(1);
						ImGui::Separator();
						ImGui::Text("Nickname");
						ImGui::Separator();

						ImGui::InputText("##NICKNAME", nickname, 127);

						ImGui::SameLine();
						if (ImGui::Button("Set Nickname", ImVec2(-1, 0)))
							NameChanger::SetName(std::string(nickname).c_str());

						if (ImGui::Button("Glitch Name"))
							NameChanger::SetName("\n\xAD\xAD\xAD");
					//	SetTooltip("Allows you to change your name an infinite amount of times and doesn't show in server message");
						ImGui::SameLine();
						if (ImGui::Button("Set unbindall / Quit"))
						{
							NameChanger::changes = 0;
							NameChanger::type = NC_Type::NC_NORMAL;
						}
						ImGui::SameLine();
						if (ImGui::Button("Set Sensitivity"))
						{
							NameChanger::changes = 0;
							NameChanger::type = NC_Type::NC_TROLL;
						}

						ImGui::SameLine();
						if (ImGui::Button("Rainbow Name"))
							NameChanger::InitColorChange(NC_Type::NC_RAINBOW);

						ImGui::SameLine();
						if (ImGui::Button("Colorize Name", ImVec2(-1, 0)))
							ImGui::OpenPopup("optionColorizeName");
						ImGui::SetNextWindowSize(ImVec2(150, 300), ImGuiSetCond_Always);
						if (ImGui::BeginPopup("optionColorizeName"))
						{
							ImGui::PushItemWidth(-1);
							for (auto& it : NameChanger::colors)
							{
								if (ImGui::Button(it.second, ImVec2(-1, 0)))
									NameChanger::InitColorChange(NC_Type::NC_SOLID, it.first);
							}
							ImGui::PopItemWidth();

							ImGui::EndPopup();
						}
						ImGui::Columns(2, NULL, true);
						{
							if (ImGui::Checkbox("Name Stealer", &Settings::NameStealer::enabled))
								NameStealer::entityId = -1;
						}
						ImGui::NextColumn();
						{
							ImGui::Combo("", &Settings::NameStealer::team, teams, IM_ARRAYSIZE(teams));
						}

						ImGui::Columns(1);
						ImGui::Separator();
						ImGui::Text("Other");
						ImGui::Separator();
						ImGui::Columns(2, NULL, true);
						{
							ImGui::Checkbox("Fake Lag", &Settings::FakeLag::enabled);
						//	SetTooltip("Chokes packets so it appears you're lagging");
							ImGui::Checkbox("Adaptive Fake Lag", &Settings::FakeLag::adaptive);
							//SetTooltip("Chokes packets based on velocity (minimum choked is fakelag value)");
							ImGui::Checkbox("Auto Accept", &Settings::AutoAccept::enabled);
						//	SetTooltip("Auto accept games when in MM queue");
							ImGui::Checkbox("AirStuck", &Settings::Airstuck::enabled);
							//SetTooltip("Stops tickrate so you freeze in place");
							ImGui::Checkbox("Autoblock", &Settings::Autoblock::enabled);
							//SetTooltip("Allows you to block players from moving forwards by standing in front of them and mirroring their moves - great for griefing");
							if (ImGui::Checkbox("Teleport", &Settings::Teleport::enabled))
							{
								if (((*pGameRules) && (*pGameRules)->IsValveDS()) && Settings::Teleport::enabled)
								{
									Settings::Teleport::enabled = false;
									ImGui::OpenPopup("Error###UNTRUSTED_FEATURE");
								}
							}
							//SetTooltip("Teleport to (0, 0) on any map");
							ImGui::Checkbox("Jump Throw", &Settings::JumpThrow::enabled);
						//	SetTooltip("Hold to prime grenade, release to perform perfect jump throw. Good for executing map smokes.");
							ImGui::Checkbox("Auto Defuse", &Settings::AutoDefuse::enabled);
						//	SetTooltip("Will automatically defuse the bomb with 0.5 seconds remaining - starts at 5.5 seconds until explosion with kit and 10.5 without");
							ImGui::Checkbox("Sniper Crosshair", &Settings::SniperCrosshair::enabled);
						//	SetTooltip("Enables the crosshair with sniper rifles");
							ImGui::Checkbox("Disable post-processing", &Settings::DisablePostProcessing::enabled);
						//	SetTooltip("Disables post-processing");
						}
						ImGui::NextColumn();
						{
							ImGui::PushItemWidth(-1);
							ImGui::SliderInt("##FAKELAGAMOUNT", &Settings::FakeLag::value, 0, 16, "Amount: %0.f");
							ImGui::PopItemWidth();
							ImGui::Checkbox("Show Ranks", &Settings::ShowRanks::enabled);
							//SetTooltip("Displays competitive rank of all players in the scoreboard next to their name during a competitive match");
							ImGui::Checkbox("Screenshot Cleaner", &Settings::ScreenshotCleaner::enabled);
							//SetTooltip("Prevents AimTux visuals from appearing in screenshots taken");
							ImGui::Combo("##AirstuckKey", (int*)&Settings::Airstuck::key, ButtonNames, IM_ARRAYSIZE(ButtonNames));
							ImGui::Combo("##AutoblockKey", (int*)&Settings::Autoblock::key, ButtonNames, IM_ARRAYSIZE(ButtonNames));
							ImGui::Combo("##TeleportKey", (int*)&Settings::Teleport::key, ButtonNames, IM_ARRAYSIZE(ButtonNames));
							ImGui::Combo("##JumpThrowKey", (int*)&Settings::JumpThrow::key, ButtonNames, IM_ARRAYSIZE(ButtonNames));

							//UI::KeyBindButton(&Settings::Airstuck::key);
							//UI::KeyBindButton(&Settings::Autoblock::key);
							//UI::KeyBindButton(&Settings::Teleport::key);
							//UI::KeyBindButton(&Settings::JumpThrow::key);
						}
						ImGui::Columns(1);
						ImGui::Separator();

						ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(210, 85));
						if (ImGui::BeginPopupModal("Error###UNTRUSTED_FEATURE"))
						{
							ImGui::Text("You cannot use this feature on a VALVE server.");

							//ImGui::Checkbox("This is not a VALVE server", &ValveDSCheck::forceUT);

							if (ImGui::Button("OK"))
								ImGui::CloseCurrentPopup();

							ImGui::EndPopup();
						}
						ImGui::PopStyleVar();

						ImGui::EndChild();
					}
				}


				break;
			case 6:
				for (int i = 0; i < IM_ARRAYSIZE(colors); i++)
					colorNames[i] = colors[i].name;


				ImGui::SetNextWindowSize(ImVec2(540, 325), ImGuiSetCond_Always);
				ImGui::Columns(2, NULL, true);
				{
					ImGui::PushItemWidth(-1);
					ImGui::ListBox("##COLORSELECTION", &colorSelected, colorNames, IM_ARRAYSIZE(colorNames), 12);
					ImGui::PopItemWidth();
				}
				ImGui::NextColumn();
				{
					if (colors[colorSelected].type == ColorListVar::HEALTHCOLORVAR_TYPE)
					{
						ColorPicker4((float*)colors[colorSelected].healthColorVarPtr);
						ImGui::Checkbox("Rainbow", &colors[colorSelected].healthColorVarPtr->rainbow);
						//SetTooltip("Makes the color an animated rainbow.");
						ImGui::SameLine();
						ImGui::Checkbox("Health-Based", &colors[colorSelected].healthColorVarPtr->hp);
						//SetTooltip("Takes color from entity health, i.e. 100 - green, 50 - yellow.");
						ImGui::PushItemWidth(-1);
						ImGui::SliderFloat("##RAINBOWSPEED", &colors[colorSelected].healthColorVarPtr->rainbowSpeed, 0.f, 1.f, "Rainbow Speed: %0.3f");
						ImGui::PopItemWidth();
					}
					else
					{
						ColorPicker4((float*)colors[colorSelected].colorVarPtr);
						ImGui::Checkbox("Rainbow", &colors[colorSelected].colorVarPtr->rainbow);
						//SetTooltip("Makes the color an animated rainbow.");
						ImGui::PushItemWidth(-1);
						ImGui::SliderFloat("##RAINBOWSPEED", &colors[colorSelected].colorVarPtr->rainbowSpeed, 0.f, 1.f, "Rainbow Speed: %0.3f");
						ImGui::PopItemWidth();
					}
				}
				break;
			}
			ImGui::End();
		}
	}

	ImGui::Render();
}