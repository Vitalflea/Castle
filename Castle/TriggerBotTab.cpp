#include "Settings.h"
#include "ImGui\imgui.h"
#include "ImGui\imgui_internal.h"
#include "Util_Items.h"
#include "triggerbottab.h"
#include "Menu.h"
const char* ButtonNamesT[] =
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
void Triggerbot::RenderTab()
{
	ImGui::Checkbox("Enabled", &Settings::Triggerbot::enabled);
	ImGui::Separator();
	ImGui::Columns(2, NULL, true);
	{
		ImGui::BeginChild("TRIG1", ImVec2(0, 0), true);
		{
			ImGui::Text("Keybind");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
				ImGui::Text("Trigger Key");
			}
			ImGui::NextColumn();
			{	
				ImGui::Combo("##TriggerKey", (int*)&Settings::Triggerbot::key, ButtonNamesT, IM_ARRAYSIZE(ButtonNamesT));
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Delay");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Enabled", &Settings::Triggerbot::Delay::enabled);
				//SetTooltip("Adds a delay to the Triggerbot");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				ImGui::SliderInt("##TRIGGERDELAY", &Settings::Triggerbot::Delay::value, 0, 1000);
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::EndChild();
		}
	}
	ImGui::NextColumn();
	{
		ImGui::BeginChild("TRIG2", ImVec2(0, 0), true);
		{
			ImGui::Text("Filter");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Enemies", &Settings::Triggerbot::Filters::enemies);
				//SetTooltip("Trigger on enemies");
				ImGui::Checkbox("Walls", &Settings::Triggerbot::Filters::walls);
				//SetTooltip("Trigger through walls");
				ImGui::Checkbox("Head", &Settings::Triggerbot::Filters::head);
				//SetTooltip("Trigger on head");
				ImGui::Checkbox("Chest", &Settings::Triggerbot::Filters::chest);
				//SetTooltip("Trigger on chest");
				ImGui::Checkbox("Legs", &Settings::Triggerbot::Filters::legs);
				//SetTooltip("Trigger on legs");
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox("Allies", &Settings::Triggerbot::Filters::allies);
				//SetTooltip("Trigger on allies");
				ImGui::Checkbox("Smoke check", &Settings::Triggerbot::Filters::smokeCheck);
				//SetTooltip("Don't shoot through smokes");
				ImGui::Checkbox("Flash check", &Settings::Triggerbot::Filters::flashCheck);
				//SetTooltip("Don't shoot while flashed");
				ImGui::Checkbox("Stomach", &Settings::Triggerbot::Filters::stomach);
				//SetTooltip("Trigger on stomach");
				ImGui::Checkbox("Arms", &Settings::Triggerbot::Filters::arms);
				//SetTooltip("Trigger on arms");
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::EndChild();
		}
	}
}