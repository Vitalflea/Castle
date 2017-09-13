#pragma once
#include "draw.h"

namespace Resolver
{
	extern std::vector<int64_t> Players;

	void FrameStageNotify(ClientFrameStage_t stage);
	void PostFrameStageNotify(ClientFrameStage_t stage);
	void FireGameEvent(IGameEvent* event);
}