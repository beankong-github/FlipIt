#include "Player.h"
#include "Game/Game.h"
#include "Game/ResourceMgr.h"
#include "Asset/ImageData.h"
#include "Level/GameLevel.h"
#include "Engine.h"
#include <cassert>


const Vector2 Player::directions[(int)EDirection::MAX] = { Vector2(0,1), Vector2(0,-1), Vector2(-1,0), Vector2(0,1) };

Player::Player(const char* image, Vector2 startPos, EDirection startDir)
{
	// �̹��� ������ ��������
	imageData = dynamic_cast<ImageData*>(Game::Get().ResourceManager()->GetResource(EResourceType::Image, image));
	
	// TODO imageData�� ���� �� ó��
	assert(imageData != nullptr);

	// �̹��� ����
	//// ���ڿ� ����.
	//length = (int)strlen(tileImageData->Buffer());
	//// �޸� �Ҵ�.
	//this->image = new char[length + 1];
	//// ���ڿ� ����.
	//strcpy_s(this->image, length + 1, tileImageData->Buffer());

	// ���� ����
	curDir = startDir;
	// ��ġ ����
	SetPosition(startPos);
	// ũ�� ����
	SetSize(imageData->Size());

	sortingOrder = 3;
	color = EColor::Red;
}

Player::~Player()
{
}

void Player::BeginPlay()
{
	Super::BeginPlay();
}

void Player::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
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

void Player::SetPositionOnTile(Vector2 position)
{
	// TODO  ������ ���������� Ȯ���ؾ���
	// 1. ���ο� ��ġ�� Ÿ�� ���� ������	
	// 2. Ÿ�� Ȯ���ϱ� (Block Ȥ�� ��� Ÿ���̸� �̵��� �� ����)


	// 1. ���ο� ��ġ�� Ÿ�� ���� ������	Ȯ��
	GameLevel* gameLevel = dynamic_cast<GameLevel*>(owner);
	Vector2 size = gameLevel->GetTilMapSize();
	if (size.x >= position.x || size.y >= position.y)
		return;

	// 2. �̵��� ��ġ�� Ÿ�� Ȯ���ϱ�
	
	

	// Player�� ���� ������ gamelevel�� �ƴ� ��� assert 
	assert(gameLevel);


	

	// ȭ����� position ����ϱ�
}
