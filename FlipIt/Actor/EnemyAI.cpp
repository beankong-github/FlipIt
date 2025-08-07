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

		// ������ ����
		if (SelectableTileOutliner != nullptr)
		{
			if (SelectableTileOutliner->IsActive())
			{
				GameLevel* gameLevel = dynamic_cast<GameLevel*>(owner);
				// Player�� ���� ������ gamelevel�� �ƴ� ��� assert 
				assert(gameLevel);

				gameLevel->FlipTile(selectedTileIndex, playerTileState);
				SelectableTileOutliner->DeactivateOutliner();
			}
		}

		// ��ǥ ��ġ �����ϱ�
		auto goals = CollectFlipTargetTiles();
		// ��ã��
		auto path = AStar(goals);
		if (!path.empty())
		{
			Vector2 next = path[0];

			// ���� ��ġ�� �̵�
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

	// Ÿ�� �ֺ� �̵��� �� �ִ� Ÿ�ϵ��� �����Ѵ�.
	std::vector<Vector2> flipableTiles;
	Vector2 tileMapSize = gamelevel->GetTilMapSize();
	for (int iy = 0; iy < tileMapSize.y ; ++iy)
		for (int ix = 0; ix < tileMapSize.x; ++ix)
		{
			// ���� Ÿ���� ��� �����Ѵ�.
			if(REVERSE(playerTileState) == gamelevel->GetTileState(Vector2(ix, iy)))
			{

				flipableTiles.emplace_back(Vector2(ix, iy));

				//�� Ÿ�� �ֺ� 4������ �����Ѵ�.
				//for (auto dir : directions)
				//{
				//	Vector2 next = Vector2(ix, iy) + dir;

				//	// ���� ���� ���̸� ��ȿ�� Ÿ���� �ƴϴ�.
				//	if (!gamelevel->GetTilMapSize().InRange(next))
				//	{
				//		continue;
				//	}
				//	// Ÿ�� Ÿ���� �� Ÿ�� Ÿ�԰� ���ƾ� �Ѵ�.
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

	// G-Score ���̺� : ���������� �ش� ĭ���� �˷��� �ִ� ���. �ִ밪���� �ʱ�ȭ �صд�.
	std::vector<std::vector<int>> gScoreBoard(tableRowCount, std::vector<int>(tableColCount, INT_MAX));

	// ��� ������ ���� �θ� ��ġ ���̺�(���� ��� �湮�� �湮�ߴ� ��� ��ġ)
	std::vector<std::vector<Vector2>> cameFrom(tableRowCount, std::vector<Vector2>(tableColCount, {-1,-1}));

	// �켱 ���� ť -> ���� ��� : ���� ��Ͽ��� ���� ���� f���� ���� ���� ��η� �����Ѵ�.
	std::priority_queue<Node> openQ;
	
	// ���� ��ġ ǥ��
	gScoreBoard[positionIndex.y][positionIndex.x] = 0;
	// ���� ��ġ���� ��ǥ���� ���� ���� �޸���ƽ ���� ���Ѵ�.
	int initialHeuristics = MinGoalHeuristic(positionIndex, goals); // �޸���ƽ ������ �����
	// ���� ��ġ OpenQ�� ����
	openQ.push(Node{ positionIndex , 0 , initialHeuristics });
	
	// A* ���� ����
	while (!openQ.empty())
	{
		Node curNode = openQ.top();
		openQ.pop();

		// ���� ��尡 ��ǥ ��ġ �� �ϳ�?
		for (const auto& goal : goals)
		{
			if (goal == curNode.pos)
			{
				// ��� ����
				// ���� �̵� ���(���ܺ� ��ġ)�� ��� ���� �θ� ���̺��� ������(backtrack)�� ����
				std::vector<Vector2> path;
				Vector2 step = curNode.pos;
				if (step == positionIndex)
				{
					path.push_back(step);
					return path;
				}

				while (step != positionIndex)
				{
					// ��ο� �����߰�
					path.push_back(step);
					step = cameFrom[step.y][step.x];
				}
				std::reverse(path.begin(), path.end());
				return path;
			}
		}

		//�̹� �� ª�� ��η� ó���� ��� ��ŵ
		if (curNode.gScore > gScoreBoard[curNode.pos.y][curNode.pos.x])
		{
			continue;
		}
	
		// ���� ĭ Ž��
		for (const auto& dir : directions)
		{
			Vector2 neighbor = curNode.pos + dir;

			if (!gamelevel->GetTilMapSize().InRange(neighbor))
				continue;

			// �̵� �Ұ��� Ÿ���� �ǳʶڴ�.
			/*if (gamelevel->GetTileState(neighbor) != playerTileState)
				continue;*/

			// G ��, F�� ���
			int newG = curNode.gScore + 1;
			//���ο� G���� ���� G������ �۴ٸ� �����Ѵ�.
			if (newG < gScoreBoard[neighbor.y][neighbor.x])
			{
				// G ���ھ� ���� ����
				gScoreBoard[neighbor.y][neighbor.x] = newG;
				// ���� ���(�湮�� ���)�� ���� ��忡�� �̵��ߴ�.
				cameFrom[neighbor.y][neighbor.x] = curNode.pos;

				// �޸���ƽ��
				int heuristic = MinGoalHeuristic(neighbor, goals);

				// ť�� ���� ��带 ����
				openQ.push({ neighbor, newG, heuristic });
			}
		}
	}

	// ��θ� ã�� ���ߴٸ� �� ���� ��ȯ
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
