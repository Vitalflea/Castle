#pragma once

#include <sstream>
#include <fstream>


namespace Chams
{
	void DrawModelExecute(IMatRenderContext* matctx, const DrawModelState_t& state, const ModelRenderInfo_t& pInfo, matrix3x4* pCustomBoneToWorld);
}