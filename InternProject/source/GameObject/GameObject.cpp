#include "GameObject.h"

namespace MySystem
{
	GameObject::GameObject() noexcept :
		_transform{}
	{
	}

	GameObject::GameObject(const Transform& transform) noexcept :
		_transform{ transform }
	{
	}

	GameObject& GameObject::Initilize()
	{
		return *this;
	}

	GameObject& GameObject::Finalize()
	{
		return *this;
	}

	const GameObject& GameObject::Draw(const Transform& parent) const
	{
		return Draw();
	}
}

