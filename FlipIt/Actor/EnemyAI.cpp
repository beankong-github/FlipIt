#include "EnemyAI.h"
#include "Level/GameLevel.h"
#include "Actor/Tile.h"
#include "Actor/Outliner.h"

#include <vector>
#include <queue>
#include <algorithm>


EnemyAI::EnemyAI(const char* image, Vector2 startPosIndex, EDirection startDir, ETileState targetTile)
	:Player(image, startPosIndex, startDir, targetTile)
{
	//tmp
	color = EColor::LightRed;
	backgroundColor = EColor::None;;
}

void EnemyAI::Tick(float deltaTime)
{
	elapsedTime += deltaTime;
	if (elapsedTime >= moveSpeed)
	{
		elapsedTime = 0.f;

		// 뒤집기 동작
		if (SelectableTileOutliner != nullptr)
		{
			if (SelectableTileOutliner->IsActive())
			{
				GameLevel* gameLevel = dynamic_cast<GameLevel*>(owner);
				// Player가 속한 레벨이 gamelevel이 아닐 경우 assert 
				assert(gameLevel);

				gameLevel->FlipTile(selectedTileIndex, playerTileState);
				SelectableTileOutliner->DeactivateOutliner();
			}
		}

		// 목표 위치 수집하기
		auto goals = CollectFlipTargetTiles();
		// 길찾기
		auto path = AStar(goals);
		if (!path.empty())
		{
			Vector2 next = path[0];

			// 다음 위치로 이동
			Move(next);
		}
	}
}

void EnemyAI::SetMoveSpeed(float speed)
{
	moveSpeed = speed;
}

std::vector<Vector2> EnemyAI::CollectFlipTargetTiles()
{
	GameLevel* gamelevel = dynamic_cast<GameLevel*>(owner);
	assert(gamelevel);

	// 타일 주변 이동할 수 있는 타일들을 조사한다.
	std::vector<Vector2> flipableTiles;
	Vector2 tileMapSize = gamelevel->GetTilMapSize();
	for (int iy = 0; iy < tileMapSize.y ; ++iy)
		for (int ix = 0; ix < tileMapSize.x; ++ix)
		{
			// 적의 타일은 모두 수집한다.
			if(REVERSE(playerTileState) == gamelevel->GetTileState(Vector2(ix, iy)))
			{

				flipableTiles.emplace_back(Vector2(ix, iy));

				//적 타일 주변 4방향을 조사한다.
				//for (auto dir : directions)
				//{
				//	Vector2 next = Vector2(ix, iy) + dir;

				//	// 보드 범위 밖이면 유효한 타일이 아니다.
				//	if (!gamelevel->GetTilMapSize().InRange(next))
				//	{
				//		continue;
				//	}
				//	// 타일 타입이 내 타일 타입과 같아야 한다.
				//	if (playerTileState == gamelevel->GetTileState(next))
				//	{
				//		flipableTiles.emplace_back(next);
				//	}
				//}
			}
		}

	return flipableTiles;
}

std::vector<Vector2> EnemyAI::AStar(std::vector<Vector2>& goals)
{
	GameLevel* gamelevel = dynamic_cast<GameLevel*>(owner);
	assert(gamelevel);

	int tableColCount = gamelevel->GetTilMapSize().x;
	int tableRowCount = gamelevel->GetTilMapSize().y;

	// G-Score 테이블 : 시작점부터 해당 칸까지 알려진 최단 비용. 최대값으로 초기화 해둔다.
	std::vector<std::vector<int>> gScoreBoard(tableRowCount, std::vector<int>(tableColCount, INT_MAX));

	// 경로 복원을 위한 부모 위치 테이블(현재 노드 방문전 방문했던 노드 위치)
	std::vector<std::vector<Vector2>> cameFrom(tableRowCount, std::vector<Vector2>(tableColCount, {-1,-1}));

	// 우선 순위 큐 -> 열린 목록 : 열린 목록에서 가장 작은 f값을 가진 것을 경로로 선택한다.
	std::priority_queue<Node> openQ;
	
	// 시작 위치 표시
	gScoreBoard[positionIndex.y][positionIndex.x] = 0;
	// 현재 위치에서 목표까지 가장 적은 휴리스틱 값을 구한다.
	int initialHeuristics = MinGoalHeuristic(positionIndex, goals); // 휴리스틱 추정값 조사용
	// 시작 위치 OpenQ에 삽입
	openQ.push(Node{ positionIndex , 0 , initialHeuristics });
	
	// A* 메인 루프
	while (!openQ.empty())
	{
		Node curNode = openQ.top();
		openQ.pop();

		// 현재 노드가 목표 위치 중 하나?
		for (const auto& goal : goals)
		{
			if (goal == curNode.pos)
			{
				// 경로 복원
				// 실제 이동 경로(스텝별 위치)를 얻기 위해 부모 테이블에서 역추적(backtrack)을 수행
				std::vector<Vector2> path;
				Vector2 step = curNode.pos;
				if (step == positionIndex)
				{
					path.push_back(step);
					return path;
				}

				while (step != positionIndex)
				{
					// 경로에 스탭추가
					path.push_back(step);
					step = cameFrom[step.y][step.x];
				}
				std::reverse(path.begin(), path.end());
				return path;
			}
		}

		//이미 더 짧은 경로로 처리된 경우 스킵
		if (curNode.gScore > gScoreBoard[curNode.pos.y][curNode.pos.x])
		{
			continue;
		}
	
		// 인접 칸 탐색
		for (const auto& dir : directions)
		{
			Vector2 neighbor = curNode.pos + dir;

			if (!gamelevel->GetTilMapSize().InRange(neighbor))
				continue;

			// 이동 불가한 타일은 건너뛴다.
			/*if (gamelevel->GetTileState(neighbor) != playerTileState)
				continue;*/

			// G 값, F값 계산
			int newG = curNode.gScore + 1;
			//새로운 G값이 기존 G값보다 작다면 갱신한다.
			if (newG < gScoreBoard[neighbor.y][neighbor.x])
			{
				// G 스코어 보드 갱신
				gScoreBoard[neighbor.y][neighbor.x] = newG;
				// 인접 노드(방문할 노드)는 현재 노드에서 이동했다.
				cameFrom[neighbor.y][neighbor.x] = curNode.pos;

				// 휴리스틱값
				int heuristic = MinGoalHeuristic(neighbor, goals);

				// 큐에 인접 노드를 삽입
				openQ.push({ neighbor, newG, heuristic });
			}
		}
	}

	// 경로를 찾지 못했다면 빈 벡터 반환
	return {};
}

int EnemyAI::MinGoalHeuristic(const Vector2& start, const std::vector<Vector2>& goals)
{
	int minDist = INT_MAX;
	for (const auto& goal : goals)
	{
		int distance = Heuristic(start, goal);
		minDist = distance < minDist ? distance : minDist;
	}

	return minDist;
}
