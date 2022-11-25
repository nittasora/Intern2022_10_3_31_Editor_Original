#pragma once

#include <Siv3D.hpp>
#include "../BitFlag.h"

namespace MySystem
{
	class GUITIleButton
	{
	private:
		using Flag = uint8;

	private:
		static constexpr Flag _ENABLE = BitFlag::Get<Flag>(0);
		static constexpr ColorF _FRAME_COLOR = Palette::Orange;

	private:
		Vec2 _position;
		double _cellSize;
		uint32 _widthSize;
		uint32 _heightSize;
		uint32 _index;
		Texture _texture;
		Flag _flag;

	public:
		GUITIleButton();
		GUITIleButton(const Texture texture, const Vec2& position, const double cellSize = 40.0, const uint32 cellNUmX = 1, const uint32 cellNumY = 1, const bool enable = true);

	public:
		GUITIleButton& Update(const Vec2& parent = Vec2{ 0.0, 0.0 }) noexcept;

		const GUITIleButton& Draw(const Vec2& parent = Vec2{ 0.0, 0.0 }) const noexcept;

	public:
		GUITIleButton& SetPosition(const Vec2& position) noexcept;
		GUITIleButton& SetCellSize(const double cellSize) noexcept;
		GUITIleButton& SetCellNum(const uint32 x, const uint32 y) noexcept;
		GUITIleButton& SetEnable(const bool enable) noexcept;

	public:
		[[nodiscard]]
		Vec2 GetPosition() const noexcept;

		[[nodiscard]]
		Vec2 GetScale() const noexcept;

		[[nodiscard]]
		Point GetCellNum() const noexcept;

		[[nodiscard]]
		Point GetIndex() const noexcept;

		[[nodiscard]]
		bool GetEnable() const noexcept;

	};
}

