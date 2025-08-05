#pragma once
#include "Actor/Actor.h"
#include "Game/Types.h"

// TODO
//  [V] ȭ�鿡 ���
//	 [V] Ÿ�� ������ �̵�
//		���Է¿� ���� ĳ���� �̵� (Input  - Deligate �ڵ� Ȯ��)
//		��Ÿ�Ͽ� ���� Player ��ġ ���
//		�� Player�� ũ��� Tile�� ũ�Ⱑ �ٸ��� ����ؾ� �Ѵ�
//  [V] ���� ���� (ȸ���� ���� ǥ�õ�) -> �ϴ� ���̴� �� �ܹ��� �켱 
//  [V] Ư�� ������ sortorder�� -1�� �����ؼ� ����� ���̵��� ����ؾ߰ڴ�
// 
//	[~] �̵��Ϸ��� Ÿ���� �ٸ� Ÿ���� Ÿ���� ��� �ƿ������� ǥ���ϰ�, �̋� Ư��Ű(����)�� ������ Flip
//			[~]TryMove�� Move�� �ѹ� ���Ѵ�. ���� �̵��Ϸ��� Ÿ���� �ٸ� Ÿ���� Ÿ���̸� �ƿ����̳ʸ� ǥ���Ѵ�.    
//         [~]TileOutliener->Actor �߰�. Ÿ�Ϻ���? �ƴ� Player����? ���� ����� ���� �� ������ ��·�� Player�� on/off �ؾ��ϴϱ� �÷��̾ ������ ����
//         [~]Outliner�� ������ 

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
	void SelectTile(Vector2 selectTile);

private:
	// ĳ���� �̹���
	class ImageData* imageData;

	// ĳ���� ��ġ - Ÿ�ϸ� ����(�ε���)
	Vector2 positionIndex;

	// ĳ���� ���� - Ÿ�ϸ� ���� 
	// ��(0,-1) / ��(0,1) / ��(-1, 0) / ��(1,0
	static const Vector2 directions[(int)EDirection::MAX];
	EDirection curDir;

	// ���� �÷��̾��� Ÿ��(Front / Back)
	ETileState playerTileState;

	// ������ Ÿ�� �ε���
	Vector2 selectedTileIndex;

	// �ƿ����̳�
	class Outliner* SelectableTileOutliner = nullptr;
};