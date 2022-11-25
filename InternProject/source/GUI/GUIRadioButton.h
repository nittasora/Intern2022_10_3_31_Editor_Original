#pragma once

#include <Siv3D.hpp>
#include "../BitFlag.h"

namespace MySystem
{
	class GUIRadioButton
	{
	private:
		using Flag = uint8;

	protected:
		static constexpr Flag _ENABLE = BitFlag::Get<Flag>(0);
		static constexpr Flag _IS_UPDATE = BitFlag::Get<Flag>(1);
		static constexpr ColorF _BASE_COLOR = ColorF{ 0.5 };
		static constexpr ColorF _CHOICE_COLOR = ColorF{ 0.35, 0.7, 1.0 };

	protected:
		Vec2 _position;
		double _width;
		Flag _flag;
		size_t _index;
		Array<String> _aLabels;

	public:
		GUIRadioButton();
		GUIRadioButton(const Vec2& position, const Array<String>& aLabels, const double width = 0.0, const bool enable = true);

	public:
		GUIRadioButton& Update(const Vec2& parent = Vec2{ 0.0, 0.0 }) noexcept;

		const GUIRadioButton& Draw(const Vec2& parent = Vec2{ 0.0, 0.0 }) const noexcept;

	public:
		GUIRadioButton& SetPosition(const Vec2& position) noexcept;
		GUIRadioButton& SetWidth(const double& width) noexcept;
		GUIRadioButton& SetEnable(const bool enable) noexcept;
		GUIRadioButton& SetLabels(Array<String>& aLabels) noexcept;
		GUIRadioButton& SetIndex(const size_t index) noexcept;

	public:
		[[nodiscard]]
		Vec2 GetPosition() const noexcept;

		[[nodiscard]]
		virtual Vec2 GetScale() const noexcept;

		[[nodiscard]]
		bool GetEnable() const noexcept;

		[[nodiscard]]
		size_t GetIndex() const noexcept;
	};
}

