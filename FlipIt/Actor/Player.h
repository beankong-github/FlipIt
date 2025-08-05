#pragma once
#include "Actor/Actor.h"

// TODO
//  1. ȭ�鿡 ���
//  2. Ÿ�� ������ �̵�
//		��Ÿ�Ͽ� ���� Player ��ġ ���
//		�� Player�� ũ��� Tile�� ũ�Ⱑ �ٸ��� ����ؾ� �Ѵ�
//  3. ���� ���� (ȸ���� ���� ǥ�õ�) -> �ϴ� ���̴� �� �ܹ��� �켱 
//  4. Ư�� ������ sortorder�� -1�� �����ؼ� ����� ���̵��� ����ؾ߰ڴ�

class Player : public Actor
{
	RTTI_DECLARATIONS(Player , Actor)

public:
	Player();
	~Player();

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Render() override;

private:
	class ImageData* tileImageData;
};