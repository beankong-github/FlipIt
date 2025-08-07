#pragma once
#include "Engine.h"

class ResourceMgr; 
class  TextImageRenderer;
class Game : public Engine
{
	RTTI_DECLARATIONS(Game, Engine)

public:
	Game();
	virtual ~Game();

	virtual void CleanUp();

	static Game& Get(){ return *dynamic_cast<Game*>(instance); };

	ResourceMgr* GetResourceMgr() const { return this->resourceMgr; }
	TextImageRenderer* GetTextImageRenderer() const { return this->textImageRenderer; }

	void StartGame();
	void FinishGame(int playerScore, int enemyScore);

private:
	ResourceMgr* resourceMgr;
	TextImageRenderer* textImageRenderer;
};