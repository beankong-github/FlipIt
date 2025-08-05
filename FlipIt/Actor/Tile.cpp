#include "Tile.h"
#include "Engine.h"
#include "Game/Game.h"
#include "Game/ResourceMgr.h"
#include "Asset/ImageData.h"


Tile::Tile(const char* image, EColor color, EColor backgroundColor, const Vector2& position, const Vector2& size) 
	:Actor(image, color, backgroundColor, position, size)
	, tileState(ETileState::None)
	, tileImageData(nullptr)
{
}

Tile::Tile(ETileState state, const Vector2& index)
	: tileState(state)
	, tileImageData(nullptr)
{
	switch (state)
	{
	case ETileState::Front:
	{
		tileImageData = dynamic_cast<ImageData*>(Game::Get().ResourceManager()->GetResource(EResourceType::Image, frontImageName));
		color = EColor::White;
	}
		break;
	case ETileState::Back:
	{
		tileImageData = dynamic_cast<ImageData*>(Game::Get().ResourceManager()->GetResource(EResourceType::Image, backImageName));
		backgroundColor = EColor::LightGray;
	}
		break;
	}

	// 타일 이미지가 없으면 안대..!
	assert(tileImageData != nullptr);

	// 문자열 길이.
	length = (int)strlen(tileImageData->Buffer());
	// 메모리 할당.
	this->image = new char[length + 1];
	// 문자열 복사.
	strcpy_s(this->image, length + 1, tileImageData->Buffer());


	Vector2 pos(0, 0);
	pos.x = tileImageData->Size().x * index.x;
	pos.y = tileImageData->Size().y * index.y;
	SetPosition(pos);
	SetSize(tileImageData->Size());

}

void Tile::Render()
{
	// 타일 그리기
	Engine::Get().WriteToBuffer(*this);
}
