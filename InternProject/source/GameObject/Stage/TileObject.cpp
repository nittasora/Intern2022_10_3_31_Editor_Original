#include "TileObject.h"

namespace MySystem
{
	const String TileObject::TEXTURE_PATH = U"Assets/Sprite/Tile.png";

	const std::array<std::pair<Polygon, Vec2>, static_cast<size_t>(TileObject::TileType::Max) + 1U> TileObject::STATIC_COLLISIONS = {
	std::make_pair<Polygon, Vec2>(Polygon{ Vec2{ 0.0, 0.0 }, Vec2{ 1.0, 0.0 }, Vec2{ 1.0, 1.0 }, Vec2{ 0.0, 1.0 } }, Vec2{ 0.5, 0.5 }),
	std::make_pair<Polygon, Vec2>(Polygon{ Vec2{ 1.0, 0.0 }, Vec2{ 1.0, 1.0 }, Vec2{ 0.0, 1.0 } }, Vec2{ 0.5, 0.5 }),
	std::make_pair<Polygon, Vec2>(Polygon{ Vec2{ 0.0, 0.0 }, Vec2{ 1.0, 0.0 }, Vec2{ 1.0, 1.0 }, Vec2{ 0.0, 1.0 } }, Vec2{ 0.5, 0.5 })	// Max
	};

	void TileObject::DrawStatic(const Data& data, const Transform& parent, const Transform& tileTransform)
	{
		auto texture = TextureAsset(U"Tile");
		auto uvSize = texture.size() / MAX_UV_POSITION;

		auto region = texture(uvSize * data.uv, uvSize);

		RectF{ tileTransform.position, tileTransform.scale }.
			rotated(data.angle).
			rotatedAt(parent.position, parent.angle)(region).
			draw();

		STATIC_COLLISIONS[data.index].
			first.
			rotatedAt(STATIC_COLLISIONS[data.index].second, data.angle).
			scale(tileTransform.scale).
			moveBy(tileTransform.position).
			rotatedAt(parent.position, parent.angle).
			drawFrame(5.0, Palette::Green);
	}
}
