#pragma once
#include "Actor/Actor.h"

// TODO
//  1. 화면에 출력
//  2. 타일 단위로 이동
//		ㄴ타일에 따라 Player 위치 계산
//		ㄴ Player의 크기와 Tile의 크기가 다름을 고려해야 한다
//  3. 방향 정보 (회전에 대한 표시도) -> 일단 보이는 건 단방향 우선 
//  4. 특정 공간의 sortorder는 -1로 설정해서 배경이 보이도록 출력해야겠다

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