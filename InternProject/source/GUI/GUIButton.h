#pragma once

#include <Siv3D.hpp>
#include "../BitFlag.h"

namespace MySystem
{
	class GUIButtonInterFace
	{
	private:
		using Flag = uint8;

	protected:
		static constexpr Flag _ENABLE = BitFlag::Get<Flag>(0);
		static constexpr Flag _IS_ON = BitFlag::Get<Flag>(1);
		static constexpr Flag _IS_TRIGGER = BitFlag::Get<Flag>(2);
		static constexpr ColorF _FRAME_COLOR = Palette::Orange;

	protected:
		Vec2 _position;
		double _width;
		Flag _flag;

	public:
		GUIButtonInterFace() = delete;
		GUIButtonInterFace(const Vec2& position, const double width, const bool enable, const bool isTrigger);

	public:
		GUIButtonInterFace& Update(const Vec2& parent = Vec2{ 0.0, 0.0 }) noexcept;

		virtual const GUIButtonInterFace& Draw(const Vec2& parent = Vec2{ 0.0, 0.0 }) const noexcept = 0;

	public:
		GUIButtonInterFace& SetPosition(const Vec2& position) noexcept;
		GUIButtonInterFace& SetWidth(const double& width) noexcept;
		GUIButtonInterFace& SetEnable(const bool enable) noexcept;
		GUIButtonInterFace& SetType(const bool isTrigger) noexcept;
		GUIButtonInterFace& SetIsOn(const bool isOn) noexcept;

	public:
		[[nodiscard]]
		Vec2 GetPosition() const noexcept;

		[[nodiscard]]
		virtual Vec2 GetScale() const noexcept;

		[[nodiscard]]
		bool GetEnable() const noexcept;

		[[nodiscard]]
		bool GetType() const noexcept;

		[[nodiscard]]
		bool GetIsOn() const noexcept;
	};

	class GUIButton : public GUIButtonInterFace
	{
	private:
		static constexpr double ROUND_SIZE = 4.8;

	private:
		String _text;

	public:
		GUIButton();
		GUIButton(const String& text, const Vec2& position, const double width = 0.0, const bool enable = true, const bool isTrigger = true);

	public:
		const GUIButtonInterFace& Draw(const Vec2& parent = Vec2{ 0.0, 0.0 }) const noexcept override final;

	public:
		GUIButtonInterFace& SetText(const String& text) noexcept;

	public:
		[[nodiscard]]
		String GetText() const noexcept;

		[[nodiscard]]
		Vec2 GetScale() const noexcept override final;
	};

	class GUIButtonImage : public GUIButtonInterFace
	{
	private:
		Texture _texture;

	public:
		GUIButtonImage();
		GUIButtonImage(const String& texturePath, const Vec2& position, const double width = 40.0, const bool enable = true, const bool isTrigger = true);

	public:
		const GUIButtonInterFace& Draw(const Vec2& parent = Vec2{ 0.0, 0.0 }) const noexcept override final;

	public:
		GUIButtonInterFace& SetTexture(const String& texturePath) noexcept;

	public:
		[[nodiscard]]
		Texture GetTexture() const noexcept;
	};
}

