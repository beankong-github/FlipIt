#pragma once
#include "IAsset.h"
#include "Math/Vector2.h"
#include <vector>

class MapData : public IAsset
{
	RTTI_DECLARATIONS(MapData, IAsset)

public:
	MapData(const char* name);
	virtual ~MapData();

private:
	virtual void Save();
	virtual void Load();

	inline virtual EResourceType GetType() { return EResourceType::Map; }

public:
	// 타일맵의 크기
	Vector2 MapSize() const;

	Vector2 PlayerSpawnPos() const;
	Vector2 EnemySpawnPos() const;

	const std::vector<ETileState>& operator[](size_t row) const
	{
		if(row < initialTileStates.size())
			return initialTileStates[row];

		return std::vector<ETileState>();
	}

private:
	std::vector<std::vector<ETileState>> initialTileStates;
	int playerSpawnIndex = 0; // Front
	int enemySpawnIndex = 0; // Back
};
