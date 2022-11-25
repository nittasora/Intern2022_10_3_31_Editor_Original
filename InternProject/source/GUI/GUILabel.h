#pragma once

#include <Siv3D.hpp>
#include "../BitFlag.h"

namespace MySystem
{
	class GUILabel
	{
	private:
		using Flag = uint8;

	private:
		static constexpr Flag _ENABLE = BitFlag::Get<Flag>(0);

	private:
		String _text;
		Vec2 _position;
		double _width;
		ColorF _backGroundColor;
		Flag _flag;

	public:
		GUILabel();
		GUILabel(const String& text, const Vec2& position, const double width = 0.0, const ColorF& backGroundColor = Palette::White, const bool enable = true);

	public:
		const GUILabel& Draw() const noexcept;
		const GUILabel& Draw(const Vec2& parent) const noexcept;

	public:
		GUILabel& SetText(const String& text) noexcept;
		GUILabel& SetPosition(const Vec2& position) noexcept;
		GUILabel& SetWidth(const double& width) noexcept;
		GUILabel& SetColor(const ColorF& color) noexcept;
		GUILabel& SetEnable(const bool enable) noexcept;

	public:
		[[nodiscard]]
		String GetText() const noexcept;

		[[nodiscard]]
		Vec2 GetPosition() const noexcept;

		[[nodiscard]]
		Vec2 GetScale() const noexcept;

		[[nodiscard]]
		ColorF GetColor() const noexcept;

		[[nodiscard]]
		bool GetEnable() const noexcept;
	};
}

