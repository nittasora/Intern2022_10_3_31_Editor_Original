#pragma once

#include "SceneCommon.h"
#include "../GUI/GUI.h"

namespace MySystem
{
	class SelectScene : public App::Scene
	{
	public:
		GUIWindow _window;

	public:
		SelectScene(const InitData& init);
		~SelectScene();

	public:
		void update() override;
		void draw() const override;
	};
}


