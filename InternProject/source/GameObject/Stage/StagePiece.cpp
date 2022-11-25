#include "StagePiece.h"

namespace MySystem
{
	void StagePiece::DrawStatic(const Data& data, const Transform& parent)
	{
		auto backSize = Vec2{ data.width, data.height };
		auto tileSize = TileObject::TILE_SIZE * data.transform.scale;
		backSize *= tileSize;

		auto center = parent.position + data.transform.position;

		auto start = center - Vec2{ backSize / 2.0 };

		RectF{ Arg::center = center, backSize }.
			rotatedAt(center, data.transform.angle).
			draw(BACK_GROUND_COLORS[data.index]).
			drawFrame(5.0, Palette::Orange);

		for (auto x : step(data.width))
		{
			for (auto y : step(data.height))
			{
				auto drawPosition = start + (Vec2{ x, y } *tileSize);

				if (data.tileDatas[y][x].first) {
					TileObject::DrawStatic(data.tileDatas[y][x].second, Transform{ center, backSize * data.transform.scale, data.transform.angle }, Transform{ drawPosition, tileSize, 0.0 });
				}

				if (data.gimmickDatas[y][x].first) {
					GimmickObject::DrawStatic(data.gimmickDatas[y][x].second, Transform{ center, backSize * data.transform.scale, data.transform.angle }, Transform{ drawPosition, tileSize, 0.0 });
				}
			}
		}
	}

	void StagePiece::DrawNormalStatic(const Data& data, const Transform& parent)
	{
		auto backSize = Vec2{ data.width, data.height };
		auto tileSize = Vec2{ TileObject::TILE_SIZE, TileObject::TILE_SIZE };
		backSize *= tileSize;

		auto center = parent.position;

		RectF{ Arg::center = center, backSize }.
			draw(BACK_GROUND_COLORS[data.index]).
			drawFrame(5.0, Palette::Orange);

		auto start = center - Vec2{ backSize / 2.0 };

		for (auto x : step(data.width))
		{
			for (auto y : step(data.height))
			{
				auto drawPosition = start + (Vec2{ x, y } *tileSize);

				if (data.tileDatas[y][x].first) {
					TileObject::DrawStatic(data.tileDatas[y][x].second, Transform{ center, backSize, 0.0 }, Transform{ drawPosition, tileSize, 0.0 });
				}

				if (data.gimmickDatas[y][x].first) {
					GimmickObject::DrawStatic(data.gimmickDatas[y][x].second, Transform{ center, backSize, 0.0 }, Transform{ drawPosition, tileSize, 0.0 });
				}
			}
		}
	}
}
