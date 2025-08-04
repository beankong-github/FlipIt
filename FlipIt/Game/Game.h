#pragma once
#include "Engine.h"

class ResourceMgr;
class Game : public Engine
{
	RTTI_DECLARATIONS(Game, Engine)

public:
	Game();
	virtual ~Game();

	virtual void CleanUp();

	static Game& Get(){ return *dynamic_cast<Game*>(instance); };

	ResourceMgr* ResourceManager() const { return this->resourceManager; }

private:
	ResourceMgr* resourceManager;
};