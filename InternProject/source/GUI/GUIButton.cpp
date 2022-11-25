#include "GUIButton.h"
#include "GUI.h"

namespace MySystem
{
	GUIButtonInterFace::GUIButtonInterFace(const Vec2& position, const double width, const bool enable, const bool isTrigger) :
		_position{ position },
		_width{ width },
		_flag{ }
	{
		SetEnable(enable);
		SetType(isTrigger);
	}

	GUIButtonInterFace& GUIButtonInterFace::Update(const Vec2& parent) noexcept
	{
		const RectF hitBox{ _position + parent, GetScale() };
		auto enable = GetEnable();
		auto isTrigger = GetType();
		auto mouseOver = hitBox.mouseOver() && enable;

		if (isTrigger)
		{
			BitFlag::UnPop(_flag, _IS_ON);
		}

		// マウスが当たっていないか無効状態 == ボタンが操作されない -> 処理を省略
		if (not mouseOver || not enable)
		{
			return *this;
		}

		Cursor::RequestStyle(CursorStyle::Hand);

		if (MouseL.down())
		{
			// フラグの立て折りを逆転
			BitFlag::PopOrUnPop(_flag, _IS_ON, not BitFlag::CheckAnyPop(_flag, _IS_ON));
		}

		return *this;
	}

	GUIButtonInterFace& GUIButtonInterFace::SetPosition(const Vec2& position) noexcept
	{
		_position = position;

		return *this;
	}

	GUIButtonInterFace& GUIButtonInterFace::SetWidth(const double& width) noexcept
	{
		_width = width;

		return *this;
	}

	GUIButtonInterFace& GUIButtonInterFace::SetEnable(const bool enable) noexcept
	{
		BitFlag::PopOrUnPop(_flag, _ENABLE, enable);

		return *this;
	}

	GUIButtonInterFace& GUIButtonInterFace::SetType(const bool isTrigger) noexcept
	{
		BitFlag::PopOrUnPop(_flag, _IS_TRIGGER, isTrigger);

		return *this;
	}

	GUIButtonInterFace& GUIButtonInterFace::SetIsOn(const bool isOn) noexcept
	{
		BitFlag::PopOrUnPop(_flag, _IS_ON, isOn);

		return *this;
	}

	Vec2 GUIButtonInterFace::GetPosition() const noexcept
	{
		return _position;
	}

	Vec2 GUIButtonInterFace::GetScale() const noexcept
	{
		return Vec2{ _width, GUI::GetCellSize()};
	}

	bool GUIButtonInterFace::GetEnable() const noexcept
	{
		return BitFlag::CheckAnyPop(_flag, _ENABLE);
	}

	bool GUIButtonInterFace::GetType() const noexcept
	{
		return BitFlag::CheckAnyPop(_flag, _IS_TRIGGER);
	}

	bool GUIButtonInterFace::GetIsOn() const noexcept
	{
		return BitFlag::CheckAnyPop(_flag, _IS_ON);
	}

	GUIButton::GUIButton() :
		GUIButtonInterFace{ Vec2{ 0.0, 0.0 }, 0.0, false, true },
		_text{ U"DefaultButton"}
	{
	}

	GUIButton::GUIButton(const String& text, const Vec2& position, const double width, const bool enable, const bool isTrigger) :
		GUIButtonInterFace{ position, width, enable, isTrigger },
		_text{ text }
	{
	}

	const GUIButtonInterFace& GUIButton::Draw(const Vec2& parent) const noexcept
	{
		const RectF backBox{ _position + parent, GetScale() };
		auto isOn = BitFlag::CheckAnyPop(_flag, _IS_ON);

		backBox.draw(GUI::GetBackGroundColor(GetEnable(), backBox.mouseOver()));

		if (isOn)
		{
			backBox.drawFrame(2, 0, _FRAME_COLOR);
		}
		else
		{
			backBox.drawFrame(1, 0, Palette::Gray);
		}

		const Font& font = GUI::GetFont();
		const auto dtext = font(_text);
		const double labelWidth = Math::Ceil(dtext.region().w);
		const Vec2 labelPos{ (backBox.x + (backBox.w - labelWidth) / 2.0), (backBox.center().y - font.height() / 2.0 + GUI::GetFontYOffset()) };
		dtext.draw(labelPos, GUI::GetTextColor(BitFlag::CheckAnyPop(_flag, _ENABLE)));

		return *this;
	}

	GUIButtonInterFace& GUIButton::SetText(const String& text) noexcept
	{
		_text = text;

		return *this;
	}

	String GUIButton::GetText() const noexcept
	{
		return _text;
	}

	Vec2 GUIButton::GetScale() const noexcept
	{
		const Font& font = GUI::GetFont();
		const double width = Max(_width, Math::Ceil(font(_text).region().w + 20));
		return Vec2{ width, GUI::GetCellSize() };
	}

	GUIButtonImage::GUIButtonImage() :
		GUIButtonInterFace{ Vec2{ 0.0, 0.0 }, 0.0, false, true },
		_texture{ U"📁"_emoji}
	{
	}

	GUIButtonImage::GUIButtonImage(const String& texturePath, const Vec2& position, const double width, const bool enable, const bool isTrigger) :
		GUIButtonInterFace{ position, width, enable, isTrigger },
		_texture{ texturePath }
	{
	}

	const GUIButtonInterFace& GUIButtonImage::Draw(const Vec2& parent) const noexcept
	{
		auto width = GetScale();
		const RectF backBox{ _position + parent, GetScale() };
		auto isOn = BitFlag::CheckAnyPop(_flag, _IS_ON);

		backBox(_texture).draw(GUI::GetBackGroundColor(GetEnable(), backBox.mouseOver()));

		if (isOn)
		{
			backBox.drawFrame(2, 0, _FRAME_COLOR);
		}
		else
		{
			backBox.drawFrame(1, 0, Palette::Gray);
		}

		return *this;
	}

	GUIButtonInterFace& GUIButtonImage::SetTexture(const String& texturePath) noexcept
	{
		_texture = Texture{ texturePath };

		return *this;
	}

	Texture GUIButtonImage::GetTexture() const noexcept
	{
		return _texture;
	}
}
