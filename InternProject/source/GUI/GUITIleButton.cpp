#include "GUITIleButton.h"
#include "GUI.h"

namespace MySystem
{
	GUITIleButton::GUITIleButton() :
		_position{ Vec2{ 0.0, 0.0 } },
		_cellSize{ 40.0 },
		_widthSize{ 1 },
		_heightSize{ 1 },
		_index{ 0 },
		_texture{ U"📁"_emoji },
		_flag{ static_cast<Flag>(0) }
	{
	}

	GUITIleButton::GUITIleButton(const Texture texture, const Vec2& position, const double cellSize, const uint32 cellNUmX, const uint32 cellNumY, const bool enable) :
		_position{ position },
		_cellSize{ cellSize },
		_widthSize{ cellNUmX },
		_heightSize{ cellNumY },
		_index{ 0 },
		_texture{ texture },
		_flag{ enable ? _ENABLE : static_cast<Flag>(0) }
	{
	}

	GUITIleButton& GUITIleButton::Update(const Vec2& parent) noexcept
	{
		RectF hitBox{ _position + parent, GetScale() };

		if (not hitBox.mouseOver() || not GetEnable())
		{
			return *this;
		}

		if (not MouseL.down())
		{
			return *this;
		}

		auto cursorPositin = Cursor::PosF() - _position - parent;
		auto x = static_cast<uint32>(cursorPositin.x / _cellSize);
		auto y = static_cast<uint32>(cursorPositin.y / _cellSize);

		_index = x + (y * _widthSize);

		return *this;
	}

	const GUITIleButton& GUITIleButton::Draw(const Vec2& parent) const noexcept
	{
		auto index = GetIndex();
		auto position = _position + parent;
		auto boxColor = GUI::GetTextColor(GetEnable());

		RectF backBox{ position, GetScale() };
		backBox(_texture).draw(GUI::GetBackGroundColor(GetEnable(), backBox.mouseOver()));

		for (auto x : step(_widthSize))
		{
			Vec2 boxPosition = position;
			boxPosition.x += x * _cellSize;

			for (auto y : step(_heightSize))
			{
				// ここの計算は無駄である(_cellSizeを足すだけでよい)
				// 警告を回避出来なかったためそのままにしている
				boxPosition.y = y * _cellSize + position.y;

				RectF box{ boxPosition, _cellSize };
				box.drawFrame(2.0, boxColor);
			}
		}

		Vec2 boxPosition = position;
		boxPosition.x += index.x * _cellSize;
		boxPosition.y += index.y * _cellSize;
		RectF box{ boxPosition, _cellSize };
		box.drawFrame(4.0, _FRAME_COLOR);

		return *this;
	}

	GUITIleButton& GUITIleButton::SetPosition(const Vec2& position) noexcept
	{
		_position = position;

		return *this;
	}

	GUITIleButton& GUITIleButton::SetCellSize(const double cellSize) noexcept
	{
		_cellSize = cellSize;

		return *this;
	}

	GUITIleButton& GUITIleButton::SetCellNum(const uint32 x, const uint32 y) noexcept
	{
		_widthSize = x;
		_heightSize = y;

		return *this;
	}

	GUITIleButton& GUITIleButton::SetEnable(const bool enable) noexcept
	{
		BitFlag::PopOrUnPop(_flag, _ENABLE, enable);

		return *this;
	}

	Vec2 GUITIleButton::GetPosition() const noexcept
	{
		return _position;
	}

	Vec2 GUITIleButton::GetScale() const noexcept
	{
		Vec2 scale;

		scale.x = static_cast<double>(_widthSize) * _cellSize;
		scale.y = static_cast<double>(_heightSize) * _cellSize;

		return scale;
	}

	Point GUITIleButton::GetCellNum() const noexcept
	{
		return Point{ _widthSize, _heightSize };
	}

	Point GUITIleButton::GetIndex() const noexcept
	{
		auto x = _index % _widthSize;
		auto y = _index / _widthSize;

		return Point(x, y);
	}

	bool GUITIleButton::GetEnable() const noexcept
	{
		return BitFlag::CheckAnyPop(_flag, _ENABLE);
	}
}
