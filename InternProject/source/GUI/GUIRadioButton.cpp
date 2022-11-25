#include "GUIRadioButton.h"
#include "GUI.h"

namespace MySystem
{
	GUIRadioButton::GUIRadioButton() :
		_position{ Vec2{ 0.0, 0.0 } },
		_width{ 0.0 },
		_flag{ static_cast<Flag>(0) },
		_index{ 0 },
		_aLabels{ U"①", U"②", U"③" }
	{
	}

	GUIRadioButton::GUIRadioButton(const Vec2& position, const Array<String>& aLabels, const double width, const bool enable) :
		_position{ position },
		_width{ width },
		_flag{ enable ? _ENABLE : static_cast<Flag>(0) },
		_index{ 0 },
		_aLabels{ aLabels }
	{
		SetWidth(width);
	}

	GUIRadioButton& GUIRadioButton::Update(const Vec2& parent) noexcept
	{
		RectF hitBox{ _position + parent, GUI::GetCellSize() };
		auto enable = GetEnable();

		// 無効状態 == ボタンが操作されない -> 処理を省略
		if (not enable)
		{
			return *this;
		}

		for (size_t i = 0, max = _aLabels.size(); i < max; ++i)
		{
			if(hitBox.mouseOver())
			{
				if (MouseL.down())
				{
					_index = i;
				}

				Cursor::RequestStyle(CursorStyle::Hand);

				// 同時に判定できないように
				break;
			}

			hitBox.moveBy(0.0, GUI::GetCellSize());
		}

		return *this;
	}

	const GUIRadioButton& GUIRadioButton::Draw(const Vec2& parent) const noexcept
	{
		auto cellSize = static_cast<double>(GUI::GetCellSize());
		auto cellHalfSize = cellSize / 2.0;
		auto buttonSize = cellHalfSize / 2.0;
		auto backScale = GetScale();
		auto backColor = GUI::GetBackGroundColor(true, false);
		auto position = _position + parent;
		auto enable = GetEnable();
		const Font& font = GUI::GetFont();

		ColorF baseColor = enable ? _BASE_COLOR : GUI::GetTextColor(false);
		ColorF choiceColor = enable ? _CHOICE_COLOR : GUI::GetTextColor(false);

		for (size_t i = 0, max = _aLabels.size(); i < max; ++i)
		{
			RectF{ position, backScale }.draw(backColor);
			Circle button{ position.x + cellHalfSize, position.y + cellHalfSize, buttonSize };

			if (i != _index)
			{
				button.drawFrame(2.0, -0.5, baseColor);
			}
			else
			{
				button.
					drawFrame(2.0, -0.5, choiceColor).
					stretched(-5).
					draw(choiceColor);
			}

			const auto dtext = font(_aLabels[i]);
			const Vec2 labelPos{ position.x + cellSize, (position.y + cellHalfSize - font.height() / 2.0 + GUI::GetFontYOffset()) };
			dtext.draw(labelPos, GUI::GetTextColor(BitFlag::CheckAnyPop(_flag, _ENABLE)));

			position.y += cellSize;
		}

		return *this;
	}

	GUIRadioButton& GUIRadioButton::SetPosition(const Vec2& position) noexcept
	{
		_position = position;

		return *this;
	}

	GUIRadioButton& GUIRadioButton::SetWidth(const double& width) noexcept
	{
		const Font& font = GUI::GetFont();
		double maxWidth = width;
		auto cellSize = GUI::GetCellSize();

		for (auto label : _aLabels)
		{
			maxWidth = Max(maxWidth, Math::Ceil(font(label).region().w + 20) + cellSize);
		}

		_width = maxWidth;

		return *this;
	}

	GUIRadioButton& GUIRadioButton::SetEnable(const bool enable) noexcept
	{
		BitFlag::PopOrUnPop(_flag, _ENABLE, enable);

		return *this;
	}

	GUIRadioButton& GUIRadioButton::SetLabels(Array<String>& aLabels) noexcept
	{
		_aLabels = aLabels;

		_index = Min(_index, _aLabels.size());

		return *this;
	}

	GUIRadioButton& GUIRadioButton::SetIndex(const size_t index) noexcept
	{
		_index = index;

		_index = Min(_index, _aLabels.size());

		return *this;
	}

	Vec2 GUIRadioButton::GetPosition() const noexcept
	{
		return _position;
	}

	Vec2 GUIRadioButton::GetScale() const noexcept
	{
		return Vec2{ _width, GUI::GetCellSize() };
	}

	bool GUIRadioButton::GetEnable() const noexcept
	{
		return BitFlag::CheckAnyPop(_flag, _ENABLE);
	}

	size_t GUIRadioButton::GetIndex() const noexcept
	{
		return _index;
	}
}
