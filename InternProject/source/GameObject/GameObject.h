/** ****************************************************************************************************
 * @file
 * @brief ゲームオブジェクトクラス提供
 **************************************************************************************************** */
#pragma once

#include "Transform.h"

namespace MySystem
{
	/** ****************************************************************************************************
	 * @brief ゲームオブジェクト基底クラス
	 **************************************************************************************************** */
	class GameObject
	{
	protected:
		Transform _transform;

	public:
		GameObject() noexcept;
		GameObject(const Transform& transform) noexcept;

	public:
		virtual GameObject& Initilize();
		virtual GameObject& Finalize();

		virtual GameObject& Update() = 0;
		virtual const GameObject& Draw() const = 0;
		virtual const GameObject& Draw(const Transform& parent) const;
	};
}

