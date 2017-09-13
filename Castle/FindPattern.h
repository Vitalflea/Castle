#pragma once
#include <windows.h>
#include <Psapi.h>
#include <stdint.h>
uintptr_t FindPattern(const char* module, const char* pattern_string, const char* mask);