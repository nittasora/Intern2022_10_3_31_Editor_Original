#pragma once

#include <Siv3D.hpp>
#include "../GameObject.h"
#include "../../BitFlag.h"

namespace MySystem
{
	class GimmickObject : public GameObject
	{
	public:
		using GimmickIndex = uint8;
		using DirectionIndex = uint8;

		enum class GimmickType : GimmickIndex
		{
			Player = 0U,	//! プレイヤー
			Goal,			//! ゴール
			Max				//! 種類数
		};

		enum class GimmickDirection : DirectionIndex
		{
			Left = 0,
			Right
		};

	public:
		static const std::array<std::pair<String, String>, static_cast<GimmickIndex>(GimmickType::Max) + 1> LABEL_TEXTURE_PATH;

	public:
		struct Data
		{
			GimmickIndex index;
			DirectionIndex direction;
		};

	public:
		static void DrawStatic(const Data& data, const Transform& parent, const Transform& tileTransform);
	};
}

