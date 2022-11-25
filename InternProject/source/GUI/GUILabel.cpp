#include "GUILabel.h"
#include "GUI.h"

namespace MySystem
{
	GUILabel::GUILabel() :
		_text{ U"DefaultLabel"},
		_position{ Vec2{ 0.0, 0.0 } },
		_width{ 0.0 },
		_backGroundColor{ Palette::White },
		_flag{ static_cast<Flag>(0) }
	{
	}

	GUILabel::GUILabel(const String& text, const Vec2& position, const double width, const ColorF& backGroundColor, const bool enable) :
		_text{ text },
		_position{ position },
		_width{ width },
		_backGroundColor{ backGroundColor },
		_flag{ enable ? _ENABLE : static_cast<Flag>(0) }
	{
	}

	const GUILabel& GUILabel::Draw() const noexcept
	{
		return Draw(Vec2::Zero());
	}

	const GUILabel& GUILabel::Draw(const Vec2& parent) const noexcept
	{
		const Font& font = GUI::GetFont();
		const RectF region{ parent + _position, GetScale() };
		region.draw(GetColor());

		const auto dtext = font(_text);
		const double labelWidth = Math::Ceil(dtext.region().w);
		const Vec2 labelPos{ (region.x + (region.w - labelWidth) / 2.0), (region.center().y - font.height() / 2.0 + GUI::GetFontYOffset()) };
		dtext.draw(labelPos, GUI::GetTextColor(BitFlag::CheckAnyPop(_flag, _ENABLE)));

		return *this;
	}

	GUILabel& GUILabel::SetText(const String& text) noexcept
	{
		_text = text;

		return *this;
	}

	GUILabel& GUILabel::SetPosition(const Vec2& position) noexcept
	{
		_position = position;

		return *this;
	}

	GUILabel& GUILabel::SetWidth(const double& width) noexcept
	{
		_width = width;

		return *this;
	}

	GUILabel& GUILabel::SetColor(const ColorF& color) noexcept
	{
		_backGroundColor = color;

		return *this;
	}

	GUILabel& GUILabel::SetEnable(const bool enable) noexcept
	{
		BitFlag::PopOrUnPop(_flag, _ENABLE, enable);

		return *this;
	}

	String GUILabel::GetText() const noexcept
	{
		return _text;
	}

	Vec2 GUILabel::GetPosition() const noexcept
	{
		return _position;
	}

	Vec2 GUILabel::GetScale() const noexcept
	{
		const Font& font = GUI::GetFont();
		const double width = Max(_width, Math::Ceil(font(_text).region().w + 20));
		return Vec2{ width, GUI::GetCellSize() };
	}

	ColorF GUILabel::GetColor() const noexcept
	{
		return _backGroundColor;
	}

	bool GUILabel::GetEnable() const noexcept
	{
		return BitFlag::CheckAnyPop(_flag, _ENABLE);
	}
}
