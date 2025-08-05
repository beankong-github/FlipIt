#include "Outliner.h"
#include "Game/Game.h"
#include  "Game/ResourceMgr.h"
#include "Asset/ImageData.h"

Outliner::Outliner(const char* name)
{
	imageData = dynamic_cast<ImageData*>(Game::Get().ResourceManager()->GetResource(EResourceType::Image, name));
	assert(imageData);


	isActive = false;
	sortingOrder = 5;
	SetSize(imageData->Size());

}

Outliner::~Outliner()
{
}

void Outliner::Render()
{
	Engine::Get().WriteToBuffer(*this);
}

inline const char* Outliner::Image() const
{
	if (imageData != nullptr)
		return imageData->Buffer();
	
	return image;
}

void Outliner::ActivateOutliner(Vector2 position, EColor color, EColor backgroundColor) 
{
	SetPosition(position);
	this->color = color;
	this->backgroundColor = backgroundColor;

	isActive = true;
}

void Outliner::DeactivateOutliner()
{
	isActive = false;
}
