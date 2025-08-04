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

private:
	ResourceMgr* ResourceManager;
};