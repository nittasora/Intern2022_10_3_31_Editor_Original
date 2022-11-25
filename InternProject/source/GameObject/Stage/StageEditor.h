#pragma once

#include "Stage.h"
#include "../../GUI/GUI.h"
#include "../../BitFlag.h"

namespace MySystem
{
	class StageEditor : public Stage
	{
	private:
		using Flag = uint8;

	private:
		enum class EditorMode : uint8
		{
			Piece = 0,
			Stage
		};

		enum class SetType : uint8
		{
			Ground = 0,
			Gimmick
		};

		enum class SetMode : uint8
		{
			Delete,
			Add
		};

		static constexpr Flag _GUI_OPEN = BitFlag::Get<Flag>(0);
		static constexpr Flag _RETURN_SCENE = BitFlag::Get<Flag>(1);

		static constexpr Vec2 _GUI_SIZE{ 400.0, 720.0 };
		static constexpr Vec2 _GUI_REAL_SIZE{ 400.0, 2000.0 };
		static constexpr Vec2 _TRANSFORM_GUI_SIZE{ 420.0, 240.0 };

		static constexpr Vec2 _COMMON_GUI_POSITION{ 0.0, 0.0 };
		static constexpr Vec2 _TILE_GIMMICK_GUI_POSITION{ 1200.0 - _GUI_SIZE.x, 0.0 };
		static constexpr Vec2 _TRANSFORM_GUI_POSITION{ 0.0, -_TRANSFORM_GUI_SIZE.y * 2.0 };

		static const String _LABEL_RETURN_BUTTON;
		static const String _LABEL_SAVE_BUTTON;
		static const String _LABEL_CHOICE_PIECE_VIEW;
		static const std::pair<String, Vec2> _LABEL_CHOICE_PIECE;
		static const std::pair<String, Array<String>> _LABEL_EDIT_MODE;

		static const String _LABEL_MOVE_ABLE;
		static const String _LABEL_SCALE_ABLE;
		static const String _LABEL_ROLL_ABLE;
		static const String _LABEL_WIDTH_VIEW;
		static const String _LABEL_HEIGHT_VIEW;
		static const std::pair<String, Vec2> _LABEL_WIDTH;
		static const std::pair<String, Vec2> _LABEL_HEIGHT;
		static const std::pair<String, Array<String>> _LABEL_SET_TYPE;
		static const std::pair<String, Array<String>> _LABEL_SET_MODE;
		static const std::pair<String, Array<String>> _LABEL_BACK_TYPE;
		static const std::pair<String, Array<String>> _LABEL_TILE_TYPE;
		static const std::pair<String, Array<String>> _LABEL_TILE_ANGLE;
		static const std::pair<String, Array<String>> _LABEL_GIMMICK_TYPE;
		static const std::pair<String, Array<String>> _LABEL_GIMMICK_DIRECTION;
		static const std::pair<String, std::pair<double, Point>> _LABEL_TILE_BUTTON;

		static const std::pair<String, Vec2> _LABEL_PIECE_POS_X;
		static const std::pair<String, Vec2> _LABEL_PIECE_POS_Y;
		static const std::pair<String, Vec2> _LABEL_PIECE_SCALE;
		static const std::pair<String, Vec2> _LABEL_PIECE_ANGLE;

	private:
		struct TileBrush
		{
			Transform::Angle angle;
			TileObject::TileIndex index;
			Point uv;

			inline TileBrush() :
				angle{ 0.0 },
				index{ static_cast<TileObject::TileIndex>(0) },
				uv{ 0, 0 }
			{

			}
		};

		struct GimmmickBrush
		{
			GimmickObject::GimmickIndex index;
			GimmickObject::DirectionIndex direction;

			inline GimmmickBrush() :
				index{ static_cast<GimmickObject::GimmickIndex>(0) },
				direction{ static_cast<GimmickObject::DirectionIndex>(0) }
			{

			}
		};

	private:
		GUIWindow _commonWindow;
		GUIWindow _tileAndGimmickWindow;
		GUIWindow _transformWindow;

		Flag _flag;
		uint8 _currentPiece;

		EditorMode _editMode;
		SetMode _setMode;
		SetType _setType;

		TileBrush _tileBrush;
		GimmmickBrush _gimmickBrush;

		Grid<RectF> _hitBoxes;

	public:
		StageEditor() = delete;
		StageEditor(const int16 worldIndex, const int16 stageIndex) noexcept;
		StageEditor(const int16 worldIndex, const int16 stageIndex, const Transform& transform) noexcept;

	private:
		StageEditor& InitilizeGUI();
		StageEditor& ReInitilizeGUI();
		StageEditor& ReInitilizePieceScale();

	public:
		virtual StageEditor& Update() override;
		virtual const StageEditor& Draw() const override;

	private:
		StageEditor& UpdateGUI();

		StageEditor& UpdatePiece();
		StageEditor& UpdateStage();

		const StageEditor& DrawPiece() const;
		const StageEditor& DrawStage() const;

	public:
		bool GetReturnScene() noexcept;
	};
}
