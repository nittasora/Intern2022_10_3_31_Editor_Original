#include "Stage.h"

namespace MySystem
{
	struct TileData
	{
		Vec2 position;	//!< 表示座標
		double angle;	//!< 表示角度
		Point uv;		//!< UV開始位置

		TileObject::TileIndex tileType;	//!< タイルの種類
	};

	struct GimmickData
	{
		Vec2 position;	//!< 表示座標
		double angle;	//!< 表示角度

		GimmickObject::GimmickIndex gimmickType;	//!< ギミックの種類
	};

	struct PieceData
	{
		Vec2	position;	//!< 座標
		double	scale;		//!< 大きさ
		double	angle;		//!< 角度
		Vec2	backScale;	//!< 背景の大きさ

		bool canMoving;		//!< 移動できるか
		bool canScaling;	//!< 拡大縮小できるか
		bool canRolling;	//!< 回転できるか

		StagePiece::BackIndex backType;	//!< 背景の種類

		Array<TileData>		aTileDescs;		//!< タイルのデータ群
		Array<GimmickData>	aGimmiclDesc;	//!< ギミックのデータ群
	};

	struct StageData
	{
		Array<PieceData> aPieceDescs;
	};

	const String Stage::_DIRECTORY_PATH = U"Assets/Stage/data_";

	Stage::Stage(const int16 worldIndex, const int16 stageIndex) noexcept :
		Stage{ worldIndex, stageIndex, Transform{ Scene::CenterF(), Vec2{ 0.0, 0.0 }, 0.0 } }
	{
	}

	Stage::Stage(const int16 worldIndex, const int16 stageIndex, const Transform& transform) noexcept :
		GameObject{ transform },
		_worldIndex{ worldIndex },
		_stageIndex{ stageIndex }
	{
		TextureAsset::Register(U"Tile", TileObject::TEXTURE_PATH);
		if (not Load())
		{
			// 
		};
	}

	Stage& Stage::Update()
	{
		return *this;
	}

	const Stage& Stage::Draw() const
	{
		return *this;
	}

	bool Stage::Load()
	{
		String path = _DIRECTORY_PATH;

		path += U"{:2d}"_fmt(_worldIndex);
		path += U"_";
		path += U"{:2d}"_fmt(_stageIndex);
		path += U"_Editor.csv";

		CSV reader{ path };
		if (not reader) {
			return false;
		}

		uint16 index = 0;
		for (auto& data : _data.pieceData)
		{
			data.transform.position = Parse<Transform::Position>(reader[index][0]);
			data.transform.scale = Parse<Transform::Scale>(reader[index][1]);
			data.transform.angle = Parse<Transform::Angle>(reader[index][2]);

			data.width = Parse<uint16>(reader[index + 1][0]);
			data.height = Parse<uint16>(reader[index + 1][1]);

			data.flag = Parse<StagePiece::Flag>(reader[index + 2][0]);
			data.index = Parse<StagePiece::BackIndex>(reader[index + 2][1]);

			data.tileDatas.resize(data.width, data.height);
			data.gimmickDatas.resize(data.width, data.height);

			index += 3;

			for (auto x : step(data.width))
			{
				for (auto y : step(data.height))
				{
					data.tileDatas[y][x].first = Parse<bool>(reader[index][0]);
					data.tileDatas[y][x].second.index = Parse<TileObject::TileIndex>(reader[index][1]);
					data.tileDatas[y][x].second.angle = Parse<double>(reader[index][2]);
					data.tileDatas[y][x].second.uv = Parse<Point>(reader[index][3]);

					data.gimmickDatas[y][x].first = Parse<bool>(reader[index + 1][0]);
					data.gimmickDatas[y][x].second.index = Parse<GimmickObject::GimmickIndex>(reader[index + 1][1]);
					data.gimmickDatas[y][x].second.direction = Parse<GimmickObject::DirectionIndex>(reader[index + 1][2]);

					index += 2;
				}
			}
		}

		return true;
	}

	bool Stage::Save()
	{
		String path = _DIRECTORY_PATH;

		path += U"{:2d}"_fmt(_worldIndex);
		path += U"_";
		path += U"{:2d}"_fmt(_stageIndex);
		path += U"_Editor.csv";

		CSV writer;

		for (auto& data : _data.pieceData)
		{
			writer.writeRow(data.transform.position, data.transform.scale, data.transform.angle);
			writer.writeRow(data.width, data.height);
			writer.writeRow(data.flag, data.index);
			for (auto x : step(data.width))
			{
				for (auto y : step(data.height))
				{
					auto& tileData = data.tileDatas[y][x];
					auto& gimmickData = data.gimmickDatas[y][x];

					writer.writeRow(tileData.first, tileData.second.index, tileData.second.angle, tileData.second.uv);
					writer.writeRow(gimmickData.first, gimmickData.second.index, gimmickData.second.direction);
				}
			}
		}

		writer.save(path);

		SaveNewData();

		return true;
	}

	void Stage::SaveNewData()
	{
		String path = _DIRECTORY_PATH;

		path += U"{:2d}"_fmt(_worldIndex);
		path += U"_";
		path += U"{:2d}"_fmt(_stageIndex);
		path += U".csv";

		CSV writer;

		StageData newData;

		for (auto& data : _data.pieceData)
		{
			auto& pieceData = newData.aPieceDescs.emplace_back();

			auto backSize = Vec2{ data.width, data.height } * TileObject::TILE_SIZE;

			pieceData.position = data.transform.position;
			pieceData.scale = data.transform.scale.x;
			pieceData.angle = data.transform.angle;
			pieceData.backScale = backSize;

			pieceData.canMoving = BitFlag::CheckAnyPop(data.flag, StagePiece::CAN_MOVING);
			pieceData.canScaling = BitFlag::CheckAnyPop(data.flag, StagePiece::CAN_SCALING);
			pieceData.canRolling = BitFlag::CheckAnyPop(data.flag, StagePiece::CAN_ROLLING);

			pieceData.backType = data.index;

			auto start = -Vec2{ backSize / 2.0 };

			for (auto x : step(data.width))
			{
				for (auto y : step(data.height))
				{
					auto& tileData = data.tileDatas[y][x];
					auto& gimmickData = data.gimmickDatas[y][x];

					if (tileData.first)
					{
						auto& tile = pieceData.aTileDescs.emplace_back();

						tile.position = start + Vec2{ x * TileObject::TILE_SIZE, y * TileObject::TILE_SIZE };
						tile.angle = tileData.second.angle;
						tile.uv = tileData.second.uv;
						tile.tileType = tileData.second.index;
					}

					if (gimmickData.first)
					{
						auto& gimmick = pieceData.aGimmiclDesc.emplace_back();

						gimmick.position = start + Vec2{ x * TileObject::TILE_SIZE, y * TileObject::TILE_SIZE };
						gimmick.angle = 0.0;
						gimmick.gimmickType = gimmickData.second.index;
					}
				}
			}
		}

		writer.writeRow(U"ステージ名");
		writer.writeRow(newData.aPieceDescs.size());

		for (auto pieceData : newData.aPieceDescs)
		{
			writer.writeRow(pieceData.position.x, pieceData.position.y, pieceData.scale, pieceData.angle, pieceData.backScale);
			writer.writeRow(pieceData.canMoving, pieceData.canScaling, pieceData.canRolling, pieceData.backType);

			writer.writeRow(pieceData.aTileDescs.size());
			for (auto tileData : pieceData.aTileDescs)
			{
				writer.writeRow(tileData.position.x, tileData.position.y, tileData.angle, tileData.tileType, tileData.uv.x, tileData.uv.y);
			}

			writer.writeRow(pieceData.aGimmiclDesc.size());
			for (auto gimmickData : pieceData.aGimmiclDesc)
			{
				writer.writeRow(gimmickData.position.x, gimmickData.position.y, gimmickData.angle, gimmickData.gimmickType);
			}
		}

		writer.save(path);
	}
}
