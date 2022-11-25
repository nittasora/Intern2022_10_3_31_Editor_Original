#include "EditorScene.h"

namespace MySystem
{
	EditorScene::EditorScene(const InitData& init) :
		IScene{ init },
		editor{ getData().worldIndex, getData().stageIndex }
	{
	}

	EditorScene::~EditorScene()
	{
	}

	void EditorScene::update()
	{
		editor.Update();

		if (editor.GetReturnScene())
		{
			changeScene(U"Select");
		}
	}

	void EditorScene::draw() const
	{
		editor.Draw();
	}
}
