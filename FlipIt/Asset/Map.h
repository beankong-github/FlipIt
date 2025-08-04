#pragma once
#include "IAsset.h"
#include "Math/Vector2.h"
#include <vector>

class Map : public IAsset
{
	RTTI_DECLARATIONS(Map, IAsset)

public:
	Map(const char* name);
	virtual ~Map();

private:
	virtual void Save();
	virtual void Load();

	inline virtual EResourceType GetType() { return EResourceType::Map; }

public:
	// 타일맵의 크기
	Vector2 MapSize() const;

	const std::vector<ETileState>& operator[](size_t row) const
	{
		if(row < initialTileStates.size())
			return initialTileStates[row];

		return std::vector<ETileState>();
	}

private:
	std::vector<std::vector<ETileState>> initialTileStates;
};
