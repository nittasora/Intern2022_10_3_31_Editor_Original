/** ****************************************************************************************************
 * @file
 * @brief トランスフォームクラス提供
 **************************************************************************************************** */
#pragma once

namespace MySystem
{
	/** ****************************************************************************************************
	 * @brief	トランスフォーム情報管理クラス
	 * @warning	親子付けはしない
	 **************************************************************************************************** */
	class Transform
	{
	public:
		using Position	= Vec2;		//!< 座標用
		using Scale		= Vec2;		//!< 大きさ用
		using Angle		= double;	//!< 角度用

	private:
		static constexpr Position	_DEFAULT_POSITION	= Position{ 0.0, 0.0 };	//!< 座標初期値
		static constexpr Scale		_DEFAULT_SCALE		= Scale{ 1.0, 1.0 };	//!< 大きさ初期値
		static constexpr Angle		_DEFAULT_ANGLE		= Angle{ 0.0 };			//!< 角度初期値

	public:
		Position	position;	//!< 座標
		Scale		scale;		//!< 大きさ
		Angle		angle;		//!< 角度

		//Position	prevPosition;	//!< 前回の座標
		//Scale		prevScale;		//!< 前回の大きさ
		//Angle		prevAngle;		//!< 前回の角度

	public:
		Transform() noexcept;
		Transform(const Position& position, const Scale& scale, const Angle& angle) noexcept;

	public:
		Transform& SetDefaultPosition() noexcept;
		Transform& SetDefaultScale() noexcept;
		Transform& SetDefaultAngle() noexcept;

		Transform& SetDefaultPositionAndScale() noexcept;
		Transform& SetDefaultScaleAndAngle() noexcept;
		Transform& SetDefaultAngleAndPosition() noexcept;

		Transform& SetDefaultAll() noexcept;

	//public:
	//	Transform& SetPrevTransform() noexcept;
	};
}

