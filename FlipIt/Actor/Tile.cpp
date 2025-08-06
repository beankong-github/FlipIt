#include "Tile.h"
#include "Engine.h"
#include "Game/Game.h"
#include "Game/ResourceMgr.h"
#include "Asset/ImageData.h"


Tile::Tile(const char* image, EColor color, EColor backgroundColor, const Vector2& position, const Vector2& size) 
	:Actor(image, color, backgroundColor, position, size)
	, tileState(ETileState::None)
	, curTileImageData(nullptr)
{
}

Tile::Tile(ETileState state, const Vector2& index)
	: tileState(state)
	, curTileImageData(nullptr)
	, index(index)
{
	frontTileImageData = dynamic_cast<ImageData*>(Game::Get().ResourceManager()->GetResource(EResourceType::Image, frontImageName));
	backTileImageData = dynamic_cast<ImageData*>(Game::Get().ResourceManager()->GetResource(EResourceType::Image, backImageName));
	
	Flip(state);

	// 타일 이미지가 없으면 안대..!
	assert(curTileImageData != nullptr);

	// 이미지 복사
	//// 문자열 길이.
	//length = (int)strlen(tileImageData->Buffer());
	//// 메모리 할당.
	//this->image = new char[length + 1];
	//// 문자열 복사.
	//strcpy_s(this->image, length + 1, tileImageData->Buffer());


	Vector2 pos(0, 0);
	pos.x = curTileImageData->Size().x * index.x;
	pos.y = curTileImageData->Size().y * index.y;
	SetPosition(pos);
	SetSize(curTileImageData->Size());

}

void Tile::Render()
{
	// 타일 그리기
	Engine::Get().WriteToBuffer(*this);
}

void Tile::Flip(ETileState state)
{
	if (!(state == ETileState::Front || state == ETileState::Back))
		return;

	tileState = state;

	if(tileState == ETileState::Front)
	{
		curTileImageData = frontTileImageData;
		color = frontColor;
		backgroundColor = frontBackgroundColor;
	}
	else
	{
		curTileImageData = backTileImageData;
		color = backColor;
		backgroundColor = backBackgroundColor;
	}
}

void Tile::OnPlayerCome()
{
	tileState = ETileState::Block;
}

void Tile::OnPlayerLeave(ETileState playerTargetState)
{
	// 플레이어가 떠나면 플레이어의 상태로 다시 돌려 놓는다.
	tileState = playerTargetState;
}

inline const char* Tile::Image() const
{
	if (curTileImageData != nullptr)
		return curTileImageData->Buffer();

	return image;
}
