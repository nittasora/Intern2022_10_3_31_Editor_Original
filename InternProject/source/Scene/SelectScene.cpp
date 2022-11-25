#include "SelectScene.h"

namespace MySystem
{
	SelectScene::SelectScene(const InitData& init) :
		IScene{ init },
		_window{ Vec2{ 0.0, 0.0 }, Scene::Size(), Vec2{ 1200.0, Scene::Height() } }
	{
		_window.AddButton(U"S1", U"ステージへ(かみんぐすーん)", Vec2{ 10.0, 10.0 });
		_window.AddButton(U"E1", U"エディタ―へ", Vec2{ 10.0, 60.0 });
	}

	SelectScene::~SelectScene()
	{
	}

	void SelectScene::update()
	{
		_window.Update();

		auto& data = getData();
		auto stageButton = _window.GetButton(U"S1");
		auto editorButton = _window.GetButton(U"E1");

		if (stageButton->GetIsOn()) {
			data.worldIndex = 0;
			data.stageIndex = 0;

			//changeScene(U"Game");
		}
		else if (editorButton->GetIsOn()) {
			data.worldIndex = 0;
			data.stageIndex = 0;

			changeScene(U"Editor");
		}
	}

	void SelectScene::draw() const
	{
		_window.Draw();
	}
}
