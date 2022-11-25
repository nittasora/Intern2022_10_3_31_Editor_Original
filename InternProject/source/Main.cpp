#include <Siv3D.hpp>
#include "Scene/SelectScene.h"
#include "Scene/GameScene.h"
#include "Scene/EditorScene.h"

void Main()
{
	Window::Resize(1200, 720);

	MySystem::App manager;
	manager.add<MySystem::SelectScene>(U"Select");
	manager.add<MySystem::GameScene>(U"Game");
	manager.add<MySystem::EditorScene>(U"Editor");

	MySystem::GUI::Init();

	while (System::Update())
	{
		if (manager.update())
		{

		}
	}
}
