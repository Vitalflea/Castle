#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

namespace Spammer
{
	void BeginFrame(float frameTime);
	void FireGameEvent(IGameEvent* event);
}