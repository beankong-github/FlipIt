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

private:
	std::vector<std::vector<ETileState>> initialTileStates;
};
