#pragma once

#include <Siv3D.hpp>
#include "../GameObject.h"
#include "../../BitFlag.h"

namespace MySystem
{
	class TileObject : public GameObject
	{
	public:
		using TileIndex = uint8;

		enum class TileType : TileIndex
		{
			Rect = 0U,	//! 四角形当たり判定
			Triangle,	//! 三角形当たり判定
			Max			//! 種類数
		};

		static constexpr double TILE_SIZE = 30.0;
		static constexpr Point MAX_UV_POSITION{ 16, 32 };
		static const String TEXTURE_PATH;

		static const std::array<std::pair<Polygon, Vec2>, static_cast<size_t>(TileType::Max) + 1U> STATIC_COLLISIONS;

	public:
		struct Data
		{
			Transform::Angle angle;
			TileIndex index;
			Point uv;
		};

	public:
		static void DrawStatic(const Data& data, const Transform& parent, const Transform& tileTransform);
	};
}
