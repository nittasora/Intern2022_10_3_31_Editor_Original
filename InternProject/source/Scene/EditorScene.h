#pragma once

#include "SceneCommon.h"
#include "../GUI/GUI.h"
#include "../GameObject/Stage/StageEditor.h"

namespace MySystem
{
	class EditorScene : public App::Scene
	{
	private:
		StageEditor editor;

	public:
		EditorScene(const InitData& init);
		~EditorScene();

	public:
		void update() override;
		void draw() const override;
	};
}

