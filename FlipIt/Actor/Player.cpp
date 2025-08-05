#include "Player.h"
#include "Game/Game.h"
#include "Game/ResourceMgr.h"
#include "Asset/ImageData.h"
#include "Level/GameLevel.h"
#include "Engine.h"
#include <cassert>


const Vector2 Player::directions[(int)EDirection::MAX] = { Vector2(0,-1), Vector2(0,1), Vector2(-1,0), Vector2(1,0) };

Player::Player(const char* image, Vector2 startPosIndex, EDirection startDir, ETileState targetTile)
	:targetTile(targetTile), positionIndex(startPosIndex), curDir(startDir)
{
	// �̹��� ������ ��������
	imageData = dynamic_cast<ImageData*>(Game::Get().ResourceManager()->GetResource(EResourceType::Image, image));
	
	// TODO imageData�� ���� �� ó��
	assert(imageData != nullptr);

	// ũ�� ����
	SetSize(imageData->Size());

	// �̹��� ����
	//// ���ڿ� ����.
	//length = (int)strlen(tileImageData->Buffer());
	//// �޸� �Ҵ�.
	//this->image = new char[length + 1];
	//// ���ڿ� ����.
	//strcpy_s(this->image, length + 1, tileImageData->Buffer());


	//tmp
	sortingOrder = 3;
	color = EColor::Red;
}

Player::~Player()
{
}

void Player::BeginPlay()
{
	Super::BeginPlay();

	// ��ġ ����
	SetPositionOnTile(positionIndex);

}

void Player::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	// tmp �Է�ó�� 
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		QuitGame();
		return;
	}

	if (Input::Get().GetKeyDown(VK_RIGHT))
	{
		Move(EDirection::Right);
	}
	if (Input::Get().GetKeyDown(VK_LEFT))
	{
		Move(EDirection::Left);
	}
	if (Input::Get().GetKeyDown(VK_UP))
	{
		Move(EDirection::Up);
	}
	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		Move(EDirection::Down);
	}
}

void Player::Render()
{
	Engine::Get().WriteToBuffer(*this);
}

inline const char* Player::Image() const
{
	if(imageData != nullptr)
		return imageData->Buffer();
	return image;
}

void Player::Move(EDirection moveDir)
{
	// ������ ��ȿ���� �ʴ� ��� �̵����� �ʴ´�
	if (moveDir == EDirection::None || moveDir == EDirection::MAX)
		return;

	// Ư�� �������� �̵��Ѵ�.
	SetPositionOnTile(positionIndex + directions[(int)moveDir]);
}

void Player::SetPositionOnTile(Vector2 newPosition)
{
	// TODO  ������ ���������� Ȯ���ؾ���
	// 
	// 1. ���ο� ��ġ�� Ÿ�� ���� ������	
	// 2. Ÿ�� Ȯ���ϱ� (Block Ȥ�� ��� Ÿ���̸� �̵��� �� ����)


	GameLevel* gameLevel = dynamic_cast<GameLevel*>(owner);
	// Player�� ���� ������ gamelevel�� �ƴ� ��� assert 
	assert(gameLevel);
	

	// 1. ���ο� ��ġ�� Ÿ�� ���� ������ Ȯ��
	Vector2 size = gameLevel->GetTilMapSize();
	if ( newPosition.x < 0 || newPosition.x >= size.x
		|| newPosition.y < 0|| newPosition.y >= size.y)
		return;

	// 2. �̵��� ��ġ�� Ÿ�� Ȯ���ϱ�
	ETileState tileState = gameLevel->GetTileState(newPosition);
	if (tileState == targetTile)
	{
		// �̵�!
		positionIndex = newPosition;
	}

	// ȭ����� position ����ϱ�(Ÿ�� �߾ӿ� ������)
	// Ÿ�� ������ + (Ÿ�� ũ�� - ���� ũ��) / 2
	Vector2 offset = gameLevel->GetTileSize(positionIndex) - imageData->Size();
	offset.x = offset.x < 0 ? 0 : offset.x;
	offset.y = offset.y < 0 ? 0 : offset.y;

	position = gameLevel->GetTilePos(positionIndex) + (offset / 2);


}
