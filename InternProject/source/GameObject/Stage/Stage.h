#pragma once

#include "StagePiece.h"

namespace MySystem
{
	class Stage : public GameObject
	{
	protected:
		static constexpr uint8 _MAX_PIECE_NUM = 10;

		static const String _DIRECTORY_PATH;

	public:
		struct Data
		{
			std::array<StagePiece::Data, _MAX_PIECE_NUM> pieceData;
		};

	protected:
		int16 _worldIndex;
		int16 _stageIndex;

		Data _data;

	public:
		Stage() = delete;
		Stage(const int16 worldIndex, const int16 stageIndex) noexcept;
		Stage(const int16 worldIndex, const int16 stageIndex, const Transform& transform) noexcept;

	public:
		virtual Stage& Update() override;
		virtual const Stage& Draw() const override;

	protected:
		bool Load();
		bool Save();

	private:
		void SaveNewData();
	};
}

