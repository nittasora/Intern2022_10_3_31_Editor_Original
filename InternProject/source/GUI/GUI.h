#pragma once

#include <Siv3D.hpp>
#include "GUILabel.h"
#include "GUIButton.h"
#include "GUIRadioButton.h"
#include "GUISlider.h"
#include "GUITIleButton.h"

namespace MySystem
{
	namespace GUI
	{
		void Init();

		Font GetFont() noexcept;

		int32 GetCellSize() noexcept;

		int32 GetFontYOffset() noexcept;

		ColorF GetTextColor(const bool enable) noexcept;

		ColorF GetBackGroundColor(const bool enable, const bool mouseOver) noexcept;
	}

	class GUIWindow
	{
	private:
		Vec2 _position;
		Vec2 _currentPosition;
		Vec2 _size;
		Vec2 _realSize;
		Vec2 _velocity;
		Vec2 _toPosition;

		GUISlider _horizontalSlider;
		GUISlider _virticalSlider;

		HashTable<String, GUILabel>			_aLabels;
		HashTable<String, GUIButton>		_aButtons;
		HashTable<String, GUIButtonImage>	_aImageButtons;
		HashTable<String, GUIRadioButton>	_aRadioButtons;
		HashTable<String, GUISlider>		_aSliders;
		HashTable<String, GUITIleButton>	_aTileButtons;

	public:
		GUIWindow() = delete;
		GUIWindow(const Vec2& position, const Vec2& drawSize, const Vec2& realSize);

	public:
		GUIWindow& Update(const Vec2& parent = Vec2{ 0.0, 0.0 }) noexcept;

		const GUIWindow& Draw(const Vec2& parent = Vec2{ 0.0, 0.0 }) const noexcept;

	public:
		GUIWindow& SetPosition(const Vec2& position) noexcept;

		GUIWindow& SetDrawSize(const Vec2& size) noexcept;

		GUIWindow& SetRealSize(const Vec2& size) noexcept;

		GUIWindow& SetToPosition(const Vec2& position) noexcept;

	public:
		[[nodiscard]]
		const Vec2 GetPosition() const noexcept;

		[[nodiscard]]
		const Vec2 GetDrawSize() const noexcept;

		[[nodiscard]]
		const Vec2 GetRealSize() const noexcept;

	public:
		GUIWindow& AddLabel(String id, String text, const Vec2& position, const double width = 0.0, const ColorF& backGroundColor = Palette::White) noexcept;
		GUIWindow& AddButton(String id, String text, const Vec2& position, const double width = 0.0, const bool isTrigger = true) noexcept;
		GUIWindow& AddImageButton(String id, String filePath, const Vec2& position, const double width = 0.0, const bool isTrigger = true) noexcept;
		GUIWindow& AddRadioButton(String id, const Array<String>& aLabels, const Vec2& position, const double width = 0.0) noexcept;
		GUIWindow& AddSlider(String id, const Vec2& position, const double width = 40.0, const double min = 0.0, const double max = 1.0, const bool isVertical = false) noexcept;
		GUIWindow& AddTileButton(String id, const Texture texture, const Vec2& position, const double cellSize = 40.0, const uint32 cellNUmX = 1, const uint32 cellNumY = 1) noexcept;

		GUIWindow& DeleteLabel(String id);
		GUIWindow& DeleteButton(String id);
		GUIWindow& DeleteImageButton(String id);
		GUIWindow& DeleteRadioButton(String id);
		GUIWindow& DeleteSlider(String id);
		GUIWindow& DeleteTileButton(String id);

		GUILabel* GetLabel(String id);
		GUIButton* GetButton(String id);
		GUIButtonImage* GetImageButton(String id);
		GUIRadioButton* GetRadioButton(String id);
		GUISlider* GetSlider(String id);
		GUITIleButton* GetTileButton(String id);
	};
}

