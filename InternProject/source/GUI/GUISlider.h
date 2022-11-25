#pragma once

#include <Siv3D.hpp>
#include "../BitFlag.h"

namespace MySystem
{
	class GUISlider
	{
	private:
		using Flag = uint8;

	private:
		static constexpr Flag _ENABLE = BitFlag::Get<Flag>(0);
		static constexpr Flag _VERTICAL = BitFlag::Get<Flag>(1);
		static constexpr ColorF _ACITIV_BASE_COLOR{ 0.33 };
		static constexpr ColorF _ACITIV_FILL_COLOR{ 0.35, 0.7, 1.0 };
		static constexpr ColorF _DISABLED_BASE_COLOR{ 0.75 };
		static constexpr ColorF _DISABLED_FILL_COLOR{ 0.75, 0.85, 1.0 };

	private:
		Vec2 _position;
		double _width;
		double _min;
		double _max;
		double _current;
		Flag _flag;

	public:
		GUISlider();
		GUISlider(const Vec2& position, const double width = 40.0, const double min = 0.0, const double max = 1.0, const bool isVertical = false);

	public:
		GUISlider& Update(const Vec2& parent = Vec2{ 0.0, 0.0 }) noexcept;

		const GUISlider& Draw(const Vec2& parent = Vec2{ 0.0, 0.0 }) const noexcept;

	public:
		GUISlider& SetPosition(const Vec2& position) noexcept;
		GUISlider& SetWidth(const double& width) noexcept;
		GUISlider& SetMin(const double& min) noexcept;
		GUISlider& SetMax(const double& max) noexcept;
		GUISlider& SetCurrent(const double& current) noexcept;
		GUISlider& SetRoundCurrent() noexcept;
		GUISlider& SetRoundCurrentUnClicked() noexcept;
		GUISlider& SetEnable(const bool enable) noexcept;
		GUISlider& SetDirection(const bool isVertical) noexcept;

	public:
		[[nodiscard]]
		Vec2 GetPosition() const noexcept;

		[[nodiscard]]
		virtual Vec2 GetScale() const noexcept;

		[[nodiscard]]
		virtual double GetMin() const noexcept;

		[[nodiscard]]
		virtual double GetMax() const noexcept;

		[[nodiscard]]
		virtual double GetCurrent() const noexcept;

		[[nodiscard]]
		bool GetEnable() const noexcept;

		[[nodiscard]]
		bool GetIsVirtical() const noexcept;
	};
}

