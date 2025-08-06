#pragma once
#include "Actor/Actor.h"
#include "Game/Types.h"

// TODO
//  [V] 화면에 출력
//	 [V] 타일 단위로 이동
//		ㄴ입력에 따라 캐릭터 이동 (Input  - Deligate 코드 확인)
//		ㄴ타일에 따라 Player 위치 계산
//		ㄴ Player의 크기와 Tile의 크기가 다름을 고려해야 한다
//  [V] 방향 정보 (회전에 대한 표시도) -> 일단 보이는 건 단방향 우선 
//  [V] 특정 공간의 sortorder는 -1로 설정해서 배경이 보이도록 출력해야겠다
// 
//	[V] 이동하려는 타일이 다른 타입의 타일일 경우 아웃라인을 표시하고, 이떄 특정키(뭐든)를 누르면 Flip
//			[V]TryMove로 Move를 한번 감싼다. 만약 이동하려는 타일이 다른 타입의 타일이면 아웃라이너를 표시한다.    
//         [V]TileOutliener->Actor 추가. 타일별로? 아님 Player별로? 별로 상관은 없을 것 같은데 어쨌든 Player가 on/off 해야하니까 플레이어가 가지고 있자
//         [V]Outliner가 켜지면 

// 예외처리 -> 다른 플레이어가 서있는 타일으로는 이동할 수 없고 타일을 뒤집을 수 없다.

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


public:
	void Move(EDirection moveDir);
	void Move(Vector2 newPosition);
	void SetPositionOnTile(Vector2 newPosition);
	void SelectTile(Vector2 selectTile);

protected:
	// 캐릭터 이미지
	class ImageData* imageData;

	// 캐릭터 위치 - 타일맵 기준(인덱스)
	Vector2 positionIndex;
	// 선택한 타일 인덱스
	Vector2 selectedTileIndex;

	EDirection curDir;
	// 캐릭터 방향 - 타일맵 기준 
	// 상(0,-1) / 하(0,1) / 좌(-1, 0) / 우(1,0
	static const Vector2 directions[(int)EDirection::MAX];

	// 현재 플레이어의 타일(Front / Back)
	ETileState playerTileState;

	// 아웃라이너
	class Outliner* SelectableTileOutliner = nullptr;
};