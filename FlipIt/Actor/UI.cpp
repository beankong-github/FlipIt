#include "UI.h"
#include "Game/Game.h"
#include "Game/ResourceMgr.h"
#include "Asset/ImageData.h"

UI::UI(const char* name, Vector2 pos, Vector2 offset)
{
	imageData = dynamic_cast<ImageData*>(Game::Get().GetResourceMgr()->GetResource(EResourceType::Image, name));
	//assert(imageData);

	SetPosition(pos);
	SetPositionOffset(offset);

	// UI Soring order : 10 ~ 30
	sortingOrder = 10;

}

UI::~UI()
{
}

void UI::Render()
{
	Engine::Get().WriteToBuffer(*this);
}

const char* UI::Image() const
{
	if (imageData != nullptr)
		return imageData->Buffer();
	
	return image;
}
