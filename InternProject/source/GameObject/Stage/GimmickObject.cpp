#include "GimmickObject.h"

namespace MySystem
{
	void GimmickObject::DrawStatic(const Data& data, const Transform& parent, const Transform& tileTransform)
	{
		Texture texture = TextureAsset(U"Player");

		switch (static_cast<GimmickType>(data.index))
		{
		case GimmickType::Goal:
			TextureAsset::Register(U"Goal", U"🚩"_emoji);
			texture = TextureAsset(U"Goal");
			break;
		default:
			TextureAsset::Register(U"Player", U"🦕"_emoji);
			texture = TextureAsset(U"Player");
			break;
		}

		RectF{ tileTransform.position, tileTransform.scale }.
			rotatedAt(parent.position, parent.angle)(texture).
			draw();
	}
}
