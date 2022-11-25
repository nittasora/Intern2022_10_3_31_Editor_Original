#include "GameScene.h"

namespace MySystem
{
	GameScene::GameScene(const InitData& init) :
		IScene{ init },
		_stage{ getData().worldIndex, getData().stageIndex }
	{
	}

	GameScene::~GameScene()
	{
	}

	void GameScene::update()
	{
	}

	void GameScene::draw() const
	{
	}
}
