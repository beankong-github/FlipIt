#pragma once
#include "Actor/Actor.h"
#include "Game/Types.h"

// TODO
//  [V] 화면에 출력
//  2. 타일 단위로 이동
//		ㄴ입력에 따라 캐릭터 이동 (Input  - Deligate 코드 확인)
//		ㄴ타일에 따라 Player 위치 계산
//		ㄴ Player의 크기와 Tile의 크기가 다름을 고려해야 한다
//  3. 방향 정보 (회전에 대한 표시도) -> 일단 보이는 건 단방향 우선 
//  4. 특정 공간의 sortorder는 -1로 설정해서 배경이 보이도록 출력해야겠다

class Player : public Actor
{
	RTTI_DECLARATIONS(Player , Actor)

public:
	Player(const char* image ,Vector2 startPosIndex, EDirection startDir, ETileState targetTile /*Front 혹은 Back*/);
	virtual ~Player();

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Render() override;

	virtual inline const char* Image() const override;


private:
	void Move(EDirection moveDir);
	void SetPositionOnTile(Vector2 newPosition);

private:
	// 캐릭터 이미지
	class ImageData* imageData;

	// 캐릭터 위치 - 타일맵 기준(인덱스)
	Vector2 positionIndex;

	// 캐릭터 방향 - 타일맵 기준 
	// 상(0,1) / 하(0,-1) / 좌(-1, 0) / 우(1,0
	static const Vector2 directions[(int)EDirection::MAX];
	EDirection curDir;

	// 타겟 타일 상태
	ETileState targetTile;
};