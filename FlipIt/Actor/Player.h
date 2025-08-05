#pragma once
#include "Actor/Actor.h"
#include "Game/Types.h"

// TODO
//  [V] ȭ�鿡 ���
//  2. Ÿ�� ������ �̵�
//		���Է¿� ���� ĳ���� �̵� (Input  - Deligate �ڵ� Ȯ��)
//		��Ÿ�Ͽ� ���� Player ��ġ ���
//		�� Player�� ũ��� Tile�� ũ�Ⱑ �ٸ��� ����ؾ� �Ѵ�
//  3. ���� ���� (ȸ���� ���� ǥ�õ�) -> �ϴ� ���̴� �� �ܹ��� �켱 
//  4. Ư�� ������ sortorder�� -1�� �����ؼ� ����� ���̵��� ����ؾ߰ڴ�

class Player : public Actor
{
	RTTI_DECLARATIONS(Player , Actor)

public:
	Player(const char* image ,Vector2 startPosIndex, EDirection startDir, ETileState targetTile /*Front Ȥ�� Back*/);
	virtual ~Player();

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Render() override;

	virtual inline const char* Image() const override;


private:
	void Move(EDirection moveDir);
	void SetPositionOnTile(Vector2 newPosition);

private:
	// ĳ���� �̹���
	class ImageData* imageData;

	// ĳ���� ��ġ - Ÿ�ϸ� ����(�ε���)
	Vector2 positionIndex;

	// ĳ���� ���� - Ÿ�ϸ� ���� 
	// ��(0,1) / ��(0,-1) / ��(-1, 0) / ��(1,0
	static const Vector2 directions[(int)EDirection::MAX];
	EDirection curDir;

	// Ÿ�� Ÿ�� ����
	ETileState targetTile;
};