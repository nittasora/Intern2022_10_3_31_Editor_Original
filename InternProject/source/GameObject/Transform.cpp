/** ****************************************************************************************************
 * @file
 * @brief トランスフォームクラス提供
 **************************************************************************************************** */
#include "Transform.h"

namespace MySystem
{
	Transform::Transform() noexcept :
		position{ _DEFAULT_POSITION },
		scale{ _DEFAULT_SCALE },
		angle{ _DEFAULT_ANGLE }
	{

	}

	Transform::Transform(const Position& position, const Scale& scale, const Angle& angle) noexcept :
		position{ position },
		scale{ scale },
		angle{ angle }
	{
	}

	Transform& Transform::SetDefaultPosition() noexcept
	{
		position = _DEFAULT_POSITION;

		return *this;
	}

	Transform& Transform::SetDefaultScale() noexcept
	{
		scale = _DEFAULT_SCALE;

		return *this;
	}

	Transform& Transform::SetDefaultAngle() noexcept
	{
		angle = _DEFAULT_ANGLE;

		return *this;
	}

	Transform& Transform::SetDefaultPositionAndScale() noexcept
	{
		position = _DEFAULT_POSITION;
		scale = _DEFAULT_SCALE;

		return *this;
	}

	Transform& Transform::SetDefaultScaleAndAngle() noexcept
	{
		scale = _DEFAULT_SCALE;
		angle = _DEFAULT_ANGLE;

		return *this;
	}

	Transform& Transform::SetDefaultAngleAndPosition() noexcept
	{
		angle = _DEFAULT_ANGLE;
		position = _DEFAULT_POSITION;

		return *this;
	}

	Transform& Transform::SetDefaultAll() noexcept
	{
		position = _DEFAULT_POSITION;
		scale = _DEFAULT_SCALE;
		angle = _DEFAULT_ANGLE;

		return *this;
	}

	//Transform& Transform::SetPrevTransform() noexcept
	//{
	//	prevPosition = position;
	//	prevScale = scale;
	//	prevAngle = angle;
	//}
}

