#pragma once

#include <Siv3D.hpp>

namespace MySystem
{
	struct CommonSceneData
	{
		int16 worldIndex;
		int16 stageIndex;
	};

	using App = SceneManager<String, CommonSceneData>;
}
