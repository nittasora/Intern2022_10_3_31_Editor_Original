#include "GUI.h"

namespace MySystem
{
	namespace
	{
		constexpr int32 gCELL_SIZE = 40;
		constexpr int32 gFONT_Y_OFFSET = -1;
		constexpr ColorF gACTIVE_TEXT_COLOR{ 0.11 };
		constexpr ColorF gDISABLED_TEXT_COLOR{ 0.67 };
		constexpr ColorF gMOUSE_OVER_COLOR{ 0.9, 0.95, 1.0 };
		constexpr ColorF gACTIVE_BACK_COLOR{ 1.0 };
		constexpr ColorF gDISABLED_BACKGROUND_COLOR{ 0.92 };

		std::unique_ptr<Font> gpDefaultFont;
		Array<Font> gaIconFonts;
	}

	void GUI::Init()
	{
		gpDefaultFont = std::make_unique<Font>(FontMethod::MSDF, 20, Typeface::CJK_Regular_JP);

		if (Font::IsAvailable(Typeface::Icon_Awesome_Solid))
		{
			gaIconFonts.emplace_back(FontMethod::MSDF, 20, Typeface::Icon_Awesome_Solid);
		}

		if (Font::IsAvailable(Typeface::Icon_MaterialDesign))
		{
			gaIconFonts.emplace_back(FontMethod::MSDF, 20, Typeface::Icon_MaterialDesign);
		}

		for (const auto& iconFont : gaIconFonts)
		{
			gpDefaultFont->addFallback(iconFont);
		}
	}

	Font GUI::GetFont() noexcept
	{
		return *gpDefaultFont;
	}

	int32 GUI::GetCellSize() noexcept
	{
		return gCELL_SIZE;
	}

	int32 GUI::GetFontYOffset() noexcept
	{
		return gFONT_Y_OFFSET;
	}

	ColorF GUI::GetTextColor(const bool enable) noexcept
	{
		return enable ? gACTIVE_TEXT_COLOR : gDISABLED_TEXT_COLOR;
	}

	ColorF GUI::GetBackGroundColor(const bool enable, const bool mouseOver) noexcept
	{
		return enable ? (mouseOver ? gMOUSE_OVER_COLOR : gACTIVE_BACK_COLOR) : gDISABLED_BACKGROUND_COLOR;
	}

	GUIWindow::GUIWindow(const Vec2& position, const Vec2& drawSize, const Vec2& realSize) :
		_position{ position },
		_currentPosition{ Vec2{ 0.0, 0.0 } },
		_size{ drawSize },
		_realSize{ realSize },
		_velocity{ Vec2{ 0.0, 0.0 } },
		_toPosition{ _position },
		_horizontalSlider{ Vec2{ 0.0, drawSize.y - 40.0 }, drawSize.x - 40.0, 0.0, 1.0, false },
		_virticalSlider{ Vec2{ drawSize.x - 40.0, 0.0 }, drawSize.y - 40.0, 0.0, 1.0, true }
	{
	}

	GUIWindow& GUIWindow::Update(const Vec2& parent) noexcept
	{
		_position = Math::SmoothDamp(_position, _toPosition, _velocity, 0.1);

		auto position = _position + parent;

		if (not RectF{ position, _size }.mouseOver()) {
			return *this;
		}

		_horizontalSlider.Update(_position);
		_virticalSlider.Update(_position);

		_currentPosition.x = _horizontalSlider.GetCurrent() * (_realSize.x - _size.x) * -1.0;
		_currentPosition.y = _virticalSlider.GetCurrent() * (_realSize.y - _size.y) * -1.0;

		position += _currentPosition;

		for (auto& item : _aButtons)
		{
			item.second.Update(position);
		}

		for (auto& item : _aImageButtons)
		{
			item.second.Update(position);
		}

		for (auto& item : _aRadioButtons)
		{
			item.second.Update(position);
		}

		for (auto& item : _aSliders)
		{
			item.second.Update(position);
		}

		for (auto& item : _aTileButtons)
		{
			item.second.Update(position);
		}

		return *this;
	}

	const GUIWindow& GUIWindow::Draw(const Vec2& parent) const noexcept
	{
		double thickness = 5.0f;
		auto color = Palette::Orange;
		auto position = _position + parent;
		auto drawPosition = position + _currentPosition;


		RectF back{ position, _size };

		Graphics2D::SetScissorRect(back.asRect());

		RasterizerState rs = RasterizerState::Default2D;
		rs.scissorEnable = true;
		const ScopedRenderStates2D rasterizer{ rs };

		back.draw(Palette::Wheat);

		for (auto& item : _aLabels)
		{
			item.second.Draw(drawPosition);
		}

		for (auto& item : _aButtons)
		{
			item.second.Draw(drawPosition);
		}

		for (auto& item : _aImageButtons)
		{
			item.second.Draw(drawPosition);
		}

		for (auto& item : _aRadioButtons)
		{
			item.second.Draw(drawPosition);
		}

		for (auto& item : _aSliders)
		{
			item.second.Draw(drawPosition);
		}

		for (auto& item : _aTileButtons)
		{
			item.second.Draw(drawPosition);
		}

		_horizontalSlider.Draw(_position);
		_virticalSlider.Draw(_position);

		RectF{ position, _size }.drawFrame(thickness, color);

		return *this;
	}

	GUIWindow& GUIWindow::SetPosition(const Vec2& position) noexcept
	{
		_position = position;

		return *this;
	}

	GUIWindow& GUIWindow::SetDrawSize(const Vec2& size) noexcept
	{
		_size = size;

		return *this;
	}

	GUIWindow& GUIWindow::SetRealSize(const Vec2& size) noexcept
	{
		_realSize = size;

		return *this;
	}

	GUIWindow& GUIWindow::SetToPosition(const Vec2& position) noexcept
	{
		_toPosition = position;

		return *this;
	}

	const Vec2 GUIWindow::GetPosition() const noexcept
	{
		return _position;
	}

	const Vec2 GUIWindow::GetDrawSize() const noexcept
	{
		return _size;
	}

	const Vec2 GUIWindow::GetRealSize() const noexcept
	{
		return _realSize;
	}

	GUIWindow& GUIWindow::AddLabel(String id, String text, const Vec2& position, const double width, const ColorF& backGroundColor) noexcept
	{
		auto item = GUILabel{ text, position, width, backGroundColor };

		if (_aLabels.contains(id))
		{
			_aLabels[id] = item;
			return *this;
		}

		_aLabels.emplace(id, item);

		return *this;
	}

	GUIWindow& GUIWindow::AddButton(String id, String text, const Vec2& position, const double width, const bool isTrigger) noexcept
	{
		auto item = GUIButton{ text, position, width, true, isTrigger };

		if (_aButtons.contains(id))
		{
			_aButtons[id] = item;
			return *this;
		}

		_aButtons.emplace(id, item);

		return *this;
	}

	GUIWindow& GUIWindow::AddImageButton(String id, String filePath, const Vec2& position, const double width, const bool isTrigger) noexcept
	{
		auto item = GUIButtonImage{ filePath, position, width, true, isTrigger };

		if (_aImageButtons.contains(id))
		{
			_aImageButtons[id] = item;
			return *this;
		}

		_aImageButtons.emplace(id, item);

		return *this;
	}

	GUIWindow& GUIWindow::AddRadioButton(String id, const Array<String>& aLabels, const Vec2& position, const double width) noexcept
	{
		auto item = GUIRadioButton{ position, aLabels, width };

		if (_aRadioButtons.contains(id))
		{
			_aRadioButtons[id] = item;
			return *this;
		}

		_aRadioButtons.emplace(id, item);

		return *this;
	}

	GUIWindow& GUIWindow::AddSlider(String id, const Vec2& position, const double width, const double min, const double max, const bool isVertical) noexcept
	{
		auto item = GUISlider{ position, width, min, max, isVertical };

		if (_aSliders.contains(id))
		{
			_aSliders[id] = item;
			return *this;
		}

		_aSliders.emplace(id, item);

		return *this;
	}

	GUIWindow& GUIWindow::AddTileButton(String id, const Texture texture, const Vec2& position, const double cellSize, const uint32 cellNUmX, const uint32 cellNumY) noexcept
	{
		auto item = GUITIleButton{ texture, position, cellSize, cellNUmX, cellNumY };

		if (_aTileButtons.contains(id))
		{
			_aTileButtons[id] = item;
			return *this;
		}

		_aTileButtons.emplace(id, item);

		return *this;
	}

	GUIWindow& GUIWindow::DeleteLabel(String id)
	{
		_aLabels.erase(id);

		return *this;
	}

	GUIWindow& GUIWindow::DeleteButton(String id)
	{
		_aButtons.erase(id);

		return *this;
	}

	GUIWindow& GUIWindow::DeleteImageButton(String id)
	{
		_aImageButtons.erase(id);

		return *this;
	}

	GUIWindow& GUIWindow::DeleteRadioButton(String id)
	{
		_aRadioButtons.erase(id);

		return *this;
	}

	GUIWindow& GUIWindow::DeleteSlider(String id)
	{
		_aSliders.erase(id);

		return *this;
	}

	GUIWindow& GUIWindow::DeleteTileButton(String id)
	{
		_aTileButtons.erase(id);

		return *this;
	}

	GUILabel* GUIWindow::GetLabel(String id)
	{
		if (_aLabels.contains(id))
		{
			return &_aLabels[id];
		}

		return nullptr;
	}

	GUIButton* GUIWindow::GetButton(String id)
	{
		if (_aButtons.contains(id))
		{
			return &_aButtons[id];
		}

		return nullptr;
	}

	GUIButtonImage* GUIWindow::GetImageButton(String id)
	{
		if (_aImageButtons.contains(id))
		{
			return &_aImageButtons[id];
		}

		return nullptr;
	}

	GUIRadioButton* GUIWindow::GetRadioButton(String id)
	{
		if (_aRadioButtons.contains(id))
		{
			return &_aRadioButtons[id];
		}

		return nullptr;
	}

	GUISlider* GUIWindow::GetSlider(String id)
	{
		if (_aSliders.contains(id))
		{
			return &_aSliders[id];
		}

		return nullptr;
	}

	GUITIleButton* GUIWindow::GetTileButton(String id)
	{
		if (_aTileButtons.contains(id))
		{
			return &_aTileButtons[id];
		}

		return nullptr;
	}
}

