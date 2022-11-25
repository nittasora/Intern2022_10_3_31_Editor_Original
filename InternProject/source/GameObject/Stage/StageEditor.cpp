#include "StageEditor.h"

namespace MySystem
{
	const String StageEditor::_LABEL_RETURN_BUTTON = U"Return";
	const String StageEditor::_LABEL_SAVE_BUTTON = U"Save";
	const String StageEditor::_LABEL_CHOICE_PIECE_VIEW = U"ChoicePieceView";
	const std::pair<String, Vec2> StageEditor::_LABEL_CHOICE_PIECE = { U"PieceNum", Vec2{ 0.0, static_cast<double>(_MAX_PIECE_NUM - 1)}};
	const std::pair<String, Array<String>> StageEditor::_LABEL_EDIT_MODE = { U"EditMode", { U"カケラ編集", U"ステージ編集" }};

	const String StageEditor::_LABEL_MOVE_ABLE = U"MoveAble";
	const String StageEditor::_LABEL_SCALE_ABLE = U"ScaleAble";
	const String StageEditor::_LABEL_ROLL_ABLE = U"RollAble";
	const String StageEditor::_LABEL_WIDTH_VIEW = U"WidthView";
	const String StageEditor::_LABEL_HEIGHT_VIEW = U"HeightView";
	const std::pair<String, Vec2> StageEditor::_LABEL_WIDTH = { U"Width", Vec2{ 1.0, static_cast<double>(StagePiece::MAX_WIDTH) } };
	const std::pair<String, Vec2> StageEditor::_LABEL_HEIGHT = { U"Hieght", Vec2{ 1.0, static_cast<double>(StagePiece::MAX_HEIGHT) } };
	const std::pair<String, Array<String>> StageEditor::_LABEL_SET_TYPE = { U"SetType", { U"地面", U"ギミック" } };
	const std::pair<String, Array<String>> StageEditor::_LABEL_SET_MODE = { U"SetMode", { U"消去", U"追加" } };
	const std::pair<String, Array<String>> StageEditor::_LABEL_BACK_TYPE = { U"BackType", { U"通常", U"透過", U"重力" } };
	const std::pair<String, Array<String>> StageEditor::_LABEL_TILE_TYPE = { U"TileType", { U"四角", U"三角"} };
	const std::pair<String, Array<String>> StageEditor::_LABEL_TILE_ANGLE = { U"TileAngle", { U"0", U"90", U"180", U"270" } };
	const std::pair<String, Array<String>> StageEditor::_LABEL_GIMMICK_TYPE = { U"GimmickType", { U"Player", U"Goal" } };
	const std::pair<String, Array<String>> StageEditor::_LABEL_GIMMICK_DIRECTION = { U"GimmickDirection", { U"左向き", U"右向き" } };
	const std::pair<String, std::pair<double, Point>> StageEditor::_LABEL_TILE_BUTTON = { U"TileButton", { 20.0, TileObject::MAX_UV_POSITION } };

	constexpr double POS_MAX_X = TileObject::TILE_SIZE * StagePiece::MAX_WIDTH / 2.0;
	constexpr double POS_MAX_Y = TileObject::TILE_SIZE * StagePiece::MAX_HEIGHT / 2.0;

	const std::pair<String, Vec2> StageEditor::_LABEL_PIECE_POS_X = { U"PosX", Vec2{ -POS_MAX_X, POS_MAX_X } };
	const std::pair<String, Vec2> StageEditor::_LABEL_PIECE_POS_Y = { U"PosY", Vec2{ -POS_MAX_Y, POS_MAX_Y } };
	const std::pair<String, Vec2> StageEditor::_LABEL_PIECE_SCALE = { U"ScaleX", Vec2{ 5.0, 15.0 } };
	const std::pair<String, Vec2> StageEditor::_LABEL_PIECE_ANGLE = { U"Angle", Vec2{ 0.0_deg, 360.0_deg } };

	StageEditor::StageEditor(const int16 worldIndex, const int16 stageIndex) noexcept :
		StageEditor{ worldIndex, stageIndex, Transform{ Scene::CenterF(), Vec2{ 1.0, 1.0 }, 0.0 } }
	{
	}

	StageEditor::StageEditor(const int16 worldIndex, const int16 stageIndex, const Transform& transform) noexcept :
		Stage{ worldIndex, stageIndex, transform },
		_commonWindow{ _COMMON_GUI_POSITION, _GUI_SIZE, _GUI_REAL_SIZE },
		_tileAndGimmickWindow{ _TILE_GIMMICK_GUI_POSITION, _GUI_SIZE, _GUI_REAL_SIZE },
		_transformWindow{ _TRANSFORM_GUI_POSITION, _TRANSFORM_GUI_SIZE, _TRANSFORM_GUI_SIZE },
		_flag{ _GUI_OPEN },
		_currentPiece{ 0 },
		_editMode{ EditorMode::Piece },
		_setMode{ SetMode::Delete },
		_setType{ SetType::Ground },
		_tileBrush{ },
		_gimmickBrush{ }
	{
		InitilizeGUI();
	}

	StageEditor& StageEditor::InitilizeGUI()
	{
		_commonWindow.AddButton(_LABEL_RETURN_BUTTON, U"ステージ選択へ戻る", Vec2{ 0.0, 0.0 });
		_commonWindow.AddButton(_LABEL_SAVE_BUTTON, U"保存する", Vec2{ 0.0, 45.0 });
		_commonWindow.AddLabel(U"1", U"選択中のカケラ", Vec2{ 0.0, 90.0 });
		_commonWindow.AddLabel(_LABEL_CHOICE_PIECE_VIEW, U"待機中", Vec2{ 0.0, 130.0 }, 100.0);
		_commonWindow.AddSlider(_LABEL_CHOICE_PIECE.first, Vec2{ 100.0, 130.0 }, 180.0, _LABEL_CHOICE_PIECE.second.x, _LABEL_CHOICE_PIECE.second.y);
		_commonWindow.AddRadioButton(_LABEL_EDIT_MODE.first, _LABEL_EDIT_MODE.second, Vec2{ 0.0, 175.0 });
		_commonWindow.AddLabel(U"2", U"※ Mキーでメニューを隠す。", Vec2{ 0.0, 265.0 }, _GUI_SIZE.x);
		_commonWindow.AddLabel(U"3", U"メニューが開いている間は、", Vec2{ 0.0, 305.0 }, _GUI_SIZE.x);
		_commonWindow.AddLabel(U"4", U"メニュー操作のみ可能。", Vec2{ 0.0, 345.0 }, _GUI_SIZE.x);

		_tileAndGimmickWindow.AddLabel(U"1", U"横タイル数", Vec2{ 0.0, 0.0 });
		_tileAndGimmickWindow.AddLabel(_LABEL_WIDTH_VIEW, U"待機中", Vec2{ 0.0, 40.0 }, 100.0);
		_tileAndGimmickWindow.AddSlider(_LABEL_WIDTH.first, Vec2{ 100.0, 40.0 }, 260.0, _LABEL_WIDTH.second.x, _LABEL_WIDTH.second.y);
		_tileAndGimmickWindow.AddLabel(U"2", U"縦タイル数", Vec2{ 0.0, 80.0 });
		_tileAndGimmickWindow.AddLabel(_LABEL_HEIGHT_VIEW, U"待機中", Vec2{ 0.0, 120.0 }, 100.0);
		_tileAndGimmickWindow.AddSlider(_LABEL_HEIGHT.first, Vec2{ 100.0, 120.0 }, 260.0, _LABEL_HEIGHT.second.x, _LABEL_HEIGHT.second.y);
		_tileAndGimmickWindow.AddButton(_LABEL_MOVE_ABLE, U"移動可能", Vec2{ 0.0, 165.0 }, 0.0, false);
		_tileAndGimmickWindow.AddButton(_LABEL_SCALE_ABLE, U"拡大縮小可能", Vec2{ 0.0, 205.0 }, 0.0, false);
		_tileAndGimmickWindow.AddButton(_LABEL_ROLL_ABLE, U"回転可能", Vec2{ 0.0, 245.0 }, 0.0, false);
		_tileAndGimmickWindow.AddLabel(U"3", U"タイルの種類", Vec2{ 0.0, 290.0 }, 180.0);
		_tileAndGimmickWindow.AddLabel(U"4", U"追加するか", Vec2{ 180.0, 290.0 }, 180.0);
		_tileAndGimmickWindow.AddRadioButton(_LABEL_SET_TYPE.first, _LABEL_SET_TYPE.second, Vec2{ 0.0, 330.0 }, 180.0);
		_tileAndGimmickWindow.AddRadioButton(_LABEL_SET_MODE.first, _LABEL_SET_MODE.second, Vec2{ 180.0, 330.0 }, 180.0);
		_tileAndGimmickWindow.AddLabel(U"5", U"背景の種類", Vec2{ 0.0, 415.0 }, 360.0);
		_tileAndGimmickWindow.AddRadioButton(_LABEL_BACK_TYPE.first, _LABEL_BACK_TYPE.second, Vec2{ 0.0, 455.0 }, 360.0);
		_tileAndGimmickWindow.AddLabel(U"6", U"地面の形", Vec2{ 0.0, 580.0 }, 180.0);
		_tileAndGimmickWindow.AddLabel(U"7", U"地面の角度", Vec2{ 180.0, 580.0 }, 180.0);
		_tileAndGimmickWindow.AddRadioButton(_LABEL_TILE_TYPE.first, _LABEL_TILE_TYPE.second, Vec2{ 0.0, 620.0 }, 180.0);
		_tileAndGimmickWindow.AddRadioButton(_LABEL_TILE_ANGLE.first, _LABEL_TILE_ANGLE.second, Vec2{ 180.0, 620.0 }, 180.0);
		_tileAndGimmickWindow.AddLabel(U"8", U"地面のUV", Vec2{ 0.0, 785.0 }, _LABEL_TILE_BUTTON.second.first * _LABEL_TILE_BUTTON.second.second.x);
		_tileAndGimmickWindow.AddTileButton(_LABEL_TILE_BUTTON.first, TextureAsset(U"Tile"), Vec2{ 0.0, 825.0 }, _LABEL_TILE_BUTTON.second.first, _LABEL_TILE_BUTTON.second.second.x, _LABEL_TILE_BUTTON.second.second.y);

		double newY = 825.5 + static_cast<double>(TileObject::MAX_UV_POSITION.y * 20);
		_tileAndGimmickWindow.AddLabel(U"9", U"ギミックの向き", Vec2{ 0.0, newY }, 180.0);
		_tileAndGimmickWindow.AddLabel(U"10", U"ギミックの種類", Vec2{ 180.0, newY }, 180.0);
		_tileAndGimmickWindow.AddRadioButton(_LABEL_GIMMICK_DIRECTION.first, _LABEL_GIMMICK_DIRECTION.second, Vec2{ 0.0, newY + 40.0 }, 180.0);
		_tileAndGimmickWindow.AddRadioButton(_LABEL_GIMMICK_TYPE.first, _LABEL_GIMMICK_TYPE.second, Vec2{ 180.0, newY + 40.0 }, 180.0);

		{
			double labelSize = 100.0;
			_transformWindow.AddLabel(U"1", U"座標X", Vec2{ 0.0, 0.0 }, labelSize);
			_transformWindow.AddLabel(U"2", U"座標Y", Vec2{ 0.0, 40.0 }, labelSize);
			_transformWindow.AddLabel(U"3", U"大きさ", Vec2{ 0.0, 80.0 }, labelSize);
			_transformWindow.AddLabel(U"5", U"角度", Vec2{ 0.0, 120.0 }, labelSize);

			double sliderSize = 260.0;
			_transformWindow.AddSlider(_LABEL_PIECE_POS_X.first, Vec2{ labelSize, 0.0 }, sliderSize, _LABEL_PIECE_POS_X.second.x, _LABEL_PIECE_POS_X.second.y);
			_transformWindow.AddSlider(_LABEL_PIECE_POS_Y.first, Vec2{ labelSize, 40.0 }, sliderSize, _LABEL_PIECE_POS_Y.second.x, _LABEL_PIECE_POS_Y.second.y);
			_transformWindow.AddSlider(_LABEL_PIECE_SCALE.first, Vec2{ labelSize, 80.0 }, sliderSize, _LABEL_PIECE_SCALE.second.x, _LABEL_PIECE_SCALE.second.y);
			_transformWindow.AddSlider(_LABEL_PIECE_ANGLE.first, Vec2{ labelSize, 120.0 }, sliderSize, _LABEL_PIECE_ANGLE.second.x, _LABEL_PIECE_ANGLE.second.y);
		}

		for (auto i = _data.pieceData.size(); i > 0; --i)
		{
			_currentPiece = i - 1;

			ReInitilizeGUI();
			ReInitilizePieceScale();
		}

		return *this;
	}

	StageEditor& StageEditor::ReInitilizeGUI()
	{
		_tileAndGimmickWindow.GetSlider(_LABEL_WIDTH.first)->SetCurrent(_data.pieceData[_currentPiece].width);
		_tileAndGimmickWindow.GetSlider(_LABEL_HEIGHT.first)->SetCurrent(_data.pieceData[_currentPiece].height);
		_tileAndGimmickWindow.GetButton(_LABEL_MOVE_ABLE)->SetIsOn(BitFlag::CheckAnyPop(_data.pieceData[_currentPiece].flag, StagePiece::CAN_MOVING));
		_tileAndGimmickWindow.GetButton(_LABEL_SCALE_ABLE)->SetIsOn(BitFlag::CheckAnyPop(_data.pieceData[_currentPiece].flag, StagePiece::CAN_SCALING));
		_tileAndGimmickWindow.GetButton(_LABEL_ROLL_ABLE)->SetIsOn(BitFlag::CheckAnyPop(_data.pieceData[_currentPiece].flag, StagePiece::CAN_ROLLING));
		_tileAndGimmickWindow.GetRadioButton(_LABEL_BACK_TYPE.first)->SetIndex(_data.pieceData[_currentPiece].index);

		// auto& transform = _data.pieceData[_currentPiece].transform;

		_transformWindow.GetSlider(_LABEL_PIECE_POS_X.first)->SetCurrent(_data.pieceData[_currentPiece].transform.position.x);
		_transformWindow.GetSlider(_LABEL_PIECE_POS_Y.first)->SetCurrent(_data.pieceData[_currentPiece].transform.position.y);
		_transformWindow.GetSlider(_LABEL_PIECE_SCALE.first)->SetCurrent(_data.pieceData[_currentPiece].transform.scale.x * 10.0);
		_transformWindow.GetSlider(_LABEL_PIECE_ANGLE.first)->SetCurrent(_data.pieceData[_currentPiece].transform.angle);

		ReInitilizePieceScale();

		return *this;
	}

	StageEditor& StageEditor::ReInitilizePieceScale()
	{
		auto& data = _data.pieceData[_currentPiece];

		auto width = data.width;
		auto height = data.height;

		data.tileDatas.resize(width, height);
		data.gimmickDatas.resize(width, height);
		_hitBoxes.resize(width, height);

		auto backSize = Vec2{ width, height };
		auto tileSize = Vec2{ TileObject::TILE_SIZE, TileObject::TILE_SIZE };
		backSize *= tileSize;

		auto start = _transform.position - Vec2{ backSize / 2.0 };

		for (auto x : step(_hitBoxes.width()))
		{
			for (auto y : step(_hitBoxes.height()))
			{
				auto drawPosition = start + (Vec2{ x, y } *tileSize);

				_hitBoxes[y][x] = RectF{ drawPosition, tileSize };
			}
		}

		return *this;
	}

	StageEditor& StageEditor::Update()
	{
		UpdateGUI();
		UpdatePiece();
		UpdateStage();

		return *this;
	}

	const StageEditor& StageEditor::Draw() const
	{
		DrawPiece();
		DrawStage();

		_commonWindow.Draw();
		_tileAndGimmickWindow.Draw();
		_transformWindow.Draw();

		return *this;
	}

	StageEditor& StageEditor::UpdateGUI()
	{
		if (KeyM.down()) {
			if (BitFlag::CheckAnyPop(_flag, _GUI_OPEN))
			{
				BitFlag::UnPop(_flag, _GUI_OPEN);

				auto commonPosition = _COMMON_GUI_POSITION;
				auto tileGimmickPosition = _TILE_GIMMICK_GUI_POSITION;

				commonPosition.x -= (_GUI_SIZE.x + 1);
				tileGimmickPosition.x += (_GUI_SIZE.x + 1);

				_commonWindow.SetToPosition(commonPosition);
				_tileAndGimmickWindow.SetToPosition(tileGimmickPosition);

				if (_editMode == EditorMode::Stage)
				{
					_transformWindow.SetToPosition(_transform.position);
				}
			}
			else
			{
				BitFlag::Pop(_flag, _GUI_OPEN);

				_commonWindow.SetToPosition(_COMMON_GUI_POSITION);
				_tileAndGimmickWindow.SetToPosition(_TILE_GIMMICK_GUI_POSITION);
				_transformWindow.SetToPosition(_TRANSFORM_GUI_POSITION);
			}
		}

		if (MouseR.down()) {
			if (_editMode == EditorMode::Stage && BitFlag::CheckAllUnPop(_flag, _GUI_OPEN))
			{
				_transformWindow.SetToPosition(Cursor::PosF());
			}
		}

		_commonWindow.Update();
		_tileAndGimmickWindow.Update();
		_transformWindow.Update();

		if (BitFlag::CheckAllUnPop(_flag, _GUI_OPEN))
		{
			return *this;
		}

		if (_commonWindow.GetButton(_LABEL_RETURN_BUTTON)->GetIsOn())
		{
			BitFlag::Pop(_flag, _RETURN_SCENE);
			return *this;
		}

		if (_commonWindow.GetButton(_LABEL_SAVE_BUTTON)->GetIsOn())
		{
			Save();
		}

		{
			auto slider = _commonWindow.GetSlider(_LABEL_CHOICE_PIECE.first);
			slider->SetRoundCurrentUnClicked();

			auto current = slider->GetCurrent();
			if (current != _currentPiece) {
				_currentPiece = static_cast<uint8>(current);
				ReInitilizeGUI();
			}

			_commonWindow.GetLabel(_LABEL_CHOICE_PIECE_VIEW)->SetText(U"{:2.0f}"_fmt(slider->GetCurrent()));
		}

		{
			_editMode = static_cast<EditorMode>(_commonWindow.GetRadioButton(_LABEL_EDIT_MODE.first)->GetIndex());
			_setMode = static_cast<SetMode>(_tileAndGimmickWindow.GetRadioButton(_LABEL_SET_MODE.first)->GetIndex());
			_setType = static_cast<SetType>(_tileAndGimmickWindow.GetRadioButton(_LABEL_SET_TYPE.first)->GetIndex());
		}

		{
			_tileBrush.index = static_cast<TileObject::TileIndex>(_tileAndGimmickWindow.GetRadioButton(_LABEL_TILE_TYPE.first)->GetIndex());
			_tileBrush.angle = static_cast<double>(_tileAndGimmickWindow.GetRadioButton(_LABEL_TILE_ANGLE.first)->GetIndex()) * 90.0_deg;
			_tileBrush.uv = _tileAndGimmickWindow.GetTileButton(_LABEL_TILE_BUTTON.first)->GetIndex();
		}

		{
			_gimmickBrush.index = static_cast<GimmickObject::GimmickIndex>(_tileAndGimmickWindow.GetRadioButton(_LABEL_GIMMICK_TYPE.first)->GetIndex());
			_gimmickBrush.direction = static_cast<GimmickObject::DirectionIndex>(_tileAndGimmickWindow.GetRadioButton(_LABEL_GIMMICK_DIRECTION.first)->GetIndex());
		}

		{
			auto widthSlider = _tileAndGimmickWindow.GetSlider(_LABEL_WIDTH.first);
			auto heightSlider = _tileAndGimmickWindow.GetSlider(_LABEL_HEIGHT.first);

			widthSlider->SetRoundCurrentUnClicked();
			heightSlider->SetRoundCurrentUnClicked();

			auto width = widthSlider->GetCurrent();
			auto height = heightSlider->GetCurrent();

			_tileAndGimmickWindow.GetLabel(_LABEL_WIDTH_VIEW)->SetText(U"{:2.0f}"_fmt(width));
			_tileAndGimmickWindow.GetLabel(_LABEL_HEIGHT_VIEW)->SetText(U"{:2.0f}"_fmt(height));

			bool isChange = false;

			if (width != _data.pieceData[_currentPiece].width)
			{
				isChange = true;
				_data.pieceData[_currentPiece].width = static_cast<uint16>(width);
			}

			if (height != _data.pieceData[_currentPiece].height)
			{
				isChange = true;
				_data.pieceData[_currentPiece].height = static_cast<uint16>(height);
			}

			if (isChange)
			{
				ReInitilizePieceScale();
			}

			BitFlag::PopOrUnPop(_data.pieceData[_currentPiece].flag, StagePiece::CAN_MOVING, _tileAndGimmickWindow.GetButton(_LABEL_MOVE_ABLE)->GetIsOn());
			BitFlag::PopOrUnPop(_data.pieceData[_currentPiece].flag, StagePiece::CAN_SCALING, _tileAndGimmickWindow.GetButton(_LABEL_SCALE_ABLE)->GetIsOn());
			BitFlag::PopOrUnPop(_data.pieceData[_currentPiece].flag, StagePiece::CAN_ROLLING, _tileAndGimmickWindow.GetButton(_LABEL_ROLL_ABLE)->GetIsOn());

			_data.pieceData[_currentPiece].index = static_cast<StagePiece::BackIndex>(_tileAndGimmickWindow.GetRadioButton(_LABEL_BACK_TYPE.first)->GetIndex());
		}
	}

	StageEditor& StageEditor::UpdatePiece()
	{
		if (_editMode != EditorMode::Piece)
		{
			return *this;
		}

		if (BitFlag::CheckAnyPop(_flag, _GUI_OPEN))
		{
			return *this;
		}

		if (not MouseL.pressed())
		{
			return *this;
		}

		auto& data = _data.pieceData[_currentPiece];

		for (auto x : step(data.width))
		{
			for (auto y : step(data.height))
			{
				if (not _hitBoxes[y][x].mouseOver())
				{
					continue;
				}

				if (_setType == SetType::Ground)
				{
					if (_setMode == SetMode::Delete)
					{
						data.tileDatas[y][x].first = false;
					}
					else
					{
						data.tileDatas[y][x].first = true;
						data.tileDatas[y][x].second = TileObject::Data{
							_tileBrush.angle, _tileBrush.index, _tileBrush.uv
						};
					}
				}
				else
				{
					if (_setMode == SetMode::Delete)
					{
						data.gimmickDatas[y][x].first = false;
					}
					else
					{
						data.gimmickDatas[y][x].first = true;
						data.gimmickDatas[y][x].second = GimmickObject::Data{
							_gimmickBrush.index, _gimmickBrush.direction
						};
					}
				}
			}
		}

		return *this;
	}

	StageEditor& StageEditor::UpdateStage()
	{
		if (_editMode != EditorMode::Stage)
		{
			return *this;
		}

		{
			auto posXSlider = _transformWindow.GetSlider(_LABEL_PIECE_POS_X.first);
			auto posYSlider = _transformWindow.GetSlider(_LABEL_PIECE_POS_Y.first);
			auto scaleSlider = _transformWindow.GetSlider(_LABEL_PIECE_SCALE.first);
			auto angleSlider = _transformWindow.GetSlider(_LABEL_PIECE_ANGLE.first);

			posXSlider->SetRoundCurrentUnClicked();
			posYSlider->SetRoundCurrentUnClicked();
			scaleSlider->SetRoundCurrentUnClicked();

			ToDegrees(angleSlider->GetCurrent());

			_data.pieceData[_currentPiece].transform.position.x = static_cast<double>(static_cast<int64>(posXSlider->GetCurrent() / 10.0) * 10.0);
			_data.pieceData[_currentPiece].transform.position.y = static_cast<double>(static_cast<int64>(posYSlider->GetCurrent() / 10.0) * 10.0);
			_data.pieceData[_currentPiece].transform.scale.x = scaleSlider->GetCurrent() / 10.0;
			_data.pieceData[_currentPiece].transform.scale.y = scaleSlider->GetCurrent() / 10.0;
			_data.pieceData[_currentPiece].transform.angle = Math::ToRadians(static_cast<double>(static_cast<int64>(Math::ToDegrees(angleSlider->GetCurrent()) / 5.0) * 5.0));
		}

		if (BitFlag::CheckAnyPop(_flag, _GUI_OPEN))
		{
			return *this;
		}

		return *this;
	}

	const StageEditor& StageEditor::DrawPiece() const
	{
		if (_editMode != EditorMode::Piece)
		{
			return *this;
		}

		StagePiece::DrawNormalStatic(_data.pieceData[_currentPiece], _transform);

		for (auto hitBox : _hitBoxes)
		{
			double width = 2.0;

			if (hitBox.mouseOver())
			{
				width = 4.0;
			}

			hitBox.drawFrame(width, Palette::Black);
		}

		return *this;
	}

	const StageEditor& StageEditor::DrawStage() const
	{
		if (_editMode != EditorMode::Stage)
		{
			return *this;
		}

		for (auto data : _data.pieceData)
		{
			StagePiece::DrawStatic(data, _transform);

		}

		return *this;
	}

	bool StageEditor::GetReturnScene() noexcept
	{
		return BitFlag::CheckAnyPop(_flag, _RETURN_SCENE);
	}
}
