#pragma once

#include "TileObject.h"
#include "GimmickObject.h"

namespace MySystem
{
	class StagePiece : public GameObject
	{
	public:
		using Flag = uint8;
		using BackIndex = uint8;

		enum class BackType : BackIndex
		{
			Normal,
			Void,
			Max
		};

		static constexpr Flag CAN_MOVING = BitFlag::Get<Flag>(0);
		static constexpr Flag CAN_SCALING = BitFlag::Get<Flag>(1);
		static constexpr Flag CAN_ROLLING = BitFlag::Get<Flag>(2);

		static constexpr uint16 MAX_WIDTH = 40;
		static constexpr uint16 MAX_HEIGHT = 24;

		static constexpr std::array<ColorF, static_cast<BackIndex>(BackType::Max) + 1> BACK_GROUND_COLORS = {
			Palette::White,
			ColorF{},
			Palette::White
		};

	public:
		struct Data
		{
			Transform transform;

			uint16 width;
			uint16 height;

			Flag flag;
			BackIndex index;

			Grid<std::pair<bool, TileObject::Data>> tileDatas;
			Grid<std::pair<bool, GimmickObject::Data>> gimmickDatas;

			inline Data() :
				transform{ },
				width{ 1 },
				height{ 1 },
				flag{ static_cast<Flag>(0) },
				index{ static_cast<BackIndex>(0) }
			{

			}
		};

	public:
		static void DrawStatic(const Data& data, const Transform& parent);
		static void DrawNormalStatic(const Data& data, const Transform& parent);
	};
}
