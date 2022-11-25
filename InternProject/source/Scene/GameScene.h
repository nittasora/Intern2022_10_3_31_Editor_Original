#pragma once

#include "SceneCommon.h"
#include "../GUI/GUI.h"
#include "../GameObject/Stage/Stage.h"

namespace MySystem
{
	class GameScene : public App::Scene
	{
	private:
		Stage _stage;

	public:
		GameScene(const InitData& init);
		~GameScene();

	public:
		void update() override;
		void draw() const override;
	};
}

