#include "GUISlider.h"
#include "GUI.h"

namespace MySystem
{
	GUISlider::GUISlider() :
		_position{ Vec2{ 0.0, 0.0 } },
		_width{ static_cast<double>(GUI::GetCellSize() * 2) },
		_min{ 0.0 },
		_max{ 1.0 },
		_current{ 0.0 },
		_flag{ static_cast<Flag>(0) }
	{
	}

	GUISlider::GUISlider(const Vec2& position, const double width, const double min, const double max, const bool isVertical) :
		_position{ position },
		_width{ Max(width, static_cast<double>(GUI::GetCellSize() * 2)) },
		_min{ Min(min, max) },
		_max{ Max(min, max) },
		_current{ _min },
		_flag{ isVertical ? BitFlag::GetMask(_ENABLE, _VERTICAL) : _ENABLE }
	{
	}

	GUISlider& GUISlider::Update(const Vec2& parent) noexcept
	{
		// 有効化されていない -> 更新されない
		if (not GetEnable()) {
			return *this;
		}

		auto cellSize = static_cast<double>(GUI::GetCellSize());
		auto position = _position + parent;
		auto barWidth = _width - cellSize;
		auto isVertical = GetIsVirtical();
		double cursorPosition;
		RectF hitBox;

		if (isVertical)
		{
			hitBox = RectF{ position, cellSize, _width };
			position.y += cellSize / 2.0;
			cursorPosition = Cursor::PosF().y - position.y;
		}
		else
		{
			hitBox = RectF{ position, _width, cellSize };
			position.x += cellSize / 2.0;
			cursorPosition = Cursor::PosF().x - position.x;
		}

		// マウスがスライダー上にない -> 更新されない
		if (not hitBox.mouseOver())
		{
			return *this;
		}

		Cursor::RequestStyle(CursorStyle::Hand);

		// クリックされていない -> 更新されない
		if (not MouseL.pressed()) {
			return *this;
		}

		if (cursorPosition < 0.0)
		{
			_current = _min;
		}
		else if (cursorPosition > barWidth)
		{
			_current = _max;
		}
		else
		{
			auto rate = cursorPosition / barWidth;
			_current = (_max - _min) * rate + _min;
		}

		return *this;
	}

	const GUISlider& GUISlider::Draw(const Vec2& parent) const noexcept
	{
		auto enable = GetEnable();
		auto scale = GetScale();
		auto baseColor = enable ? _ACITIV_BASE_COLOR : _DISABLED_BASE_COLOR;
		auto fillColor = enable ? _ACITIV_FILL_COLOR : _DISABLED_FILL_COLOR;

		RectF backBox{ _position + parent, scale };
		backBox.draw(GUI::GetBackGroundColor(true, false));

		auto cellSize = static_cast<double>(GUI::GetCellSize());
		auto cellHalfSize = cellSize / 2.0;
		auto cellQuarterSize = cellSize / 4.0;
		auto varSize = _width - cellSize;
		Vec2 basePostition, fillPosition;
		Vec2 baseSize, fillSize;

		auto rate = (_current - _min) / (_max - _min);

		if (GetIsVirtical())
		{
			baseSize = Vec2{ cellHalfSize, varSize };
			fillSize = Vec2{ cellHalfSize, varSize * rate };

			basePostition = Vec2{ backBox.leftX() + cellQuarterSize, backBox.topY() + cellHalfSize };
			fillPosition = Vec2{ backBox.centerX(), basePostition.y + fillSize.y };
		}
		else
		{
			baseSize = Vec2{ varSize, cellHalfSize };
			fillSize = Vec2{ varSize * rate, cellHalfSize };

			basePostition = Vec2{ backBox.leftX() + cellHalfSize, backBox.topY() + cellQuarterSize };
			fillPosition = Vec2{ basePostition.x + fillSize.x, backBox.centerY() };
		}

		RectF{ basePostition, baseSize }.draw(baseColor);
		RectF{ basePostition, fillSize }.draw(fillColor);

		if (enable)
		{
			Circle{ fillPosition, cellQuarterSize }.draw(GUI::GetBackGroundColor(true, false)).drawFrame(1, ColorF{ 0.33 });
		}
		else
		{
			Circle{ fillPosition, cellQuarterSize }.draw(GUI::GetBackGroundColor(true, false)).drawFrame(1, ColorF{ 0.67 });
		}

		return *this;
	}

	GUISlider& GUISlider::SetPosition(const Vec2& position) noexcept
	{
		_position = position;

		return *this;
	}

	GUISlider& GUISlider::SetWidth(const double& width) noexcept
	{
		_width = Max(width, static_cast<double>(GUI::GetCellSize() * 2));

		return *this;
	}

	GUISlider& GUISlider::SetMin(const double& min) noexcept
	{
		if (_max > min)
		{
			_min = min;
		}
		else if (_max == min)
		{
			_min = min;
			_max = _min + 1;
		}
		else {
			_min = _max;
			_max = min;
		}

		return *this;
	}

	GUISlider& GUISlider::SetMax(const double& max) noexcept
	{
		if (_min < max)
		{
			_max = max;
		}
		else if (_min == max)
		{
			_max = _max;
			_min = _max - 1;
		}
		else {
			_max = _min;
			_min = max;
		}

		return *this;
	}

	GUISlider& GUISlider::SetCurrent(const double& current) noexcept
	{
		_current = Clamp(current, _min, _max);

		return *this;
	}

	GUISlider& GUISlider::SetRoundCurrent() noexcept
	{
		_current = Math::Round(_current);

		return *this;
	}

	GUISlider& GUISlider::SetRoundCurrentUnClicked() noexcept
	{
		if (not MouseL.pressed())
		{
			_current = Math::Round(_current);
		}

		return *this;
	}

	GUISlider& GUISlider::SetEnable(const bool enable) noexcept
	{
		BitFlag::PopOrUnPop(_flag, _ENABLE, enable);

		return *this;
	}

	GUISlider& GUISlider::SetDirection(const bool isVertical) noexcept
	{
		BitFlag::PopOrUnPop(_flag, _VERTICAL, isVertical);

		return *this;
	}

	Vec2 GUISlider::GetPosition() const noexcept
	{
		return _position;
	}

	Vec2 GUISlider::GetScale() const noexcept
	{
		auto cellSize = GUI::GetCellSize();

		if (GetIsVirtical()) {
			return Vec2{ cellSize, _width };
		}
		else {
			return Vec2{ _width, cellSize };
		}
	}

	double GUISlider::GetMin() const noexcept
	{
		return _min;
	}

	double GUISlider::GetMax() const noexcept
	{
		return _max;
	}

	double GUISlider::GetCurrent() const noexcept
	{
		return _current;
	}

	bool GUISlider::GetEnable() const noexcept
	{
		return BitFlag::CheckAnyPop(_flag, _ENABLE);
	}

	bool GUISlider::GetIsVirtical() const noexcept
	{
		return BitFlag::CheckAnyPop(_flag, _VERTICAL);
	}
}
