#pragma once
#include "Player.h"
#include "Game/Types.h"

// TODO 적 AI가 이동할 위치를 수집한다.
// 1. 보드 전체를 순회하며 적 타일을 수집한다.
//  2. 적 타일 인접 4타일 중에 AI가 설 수 있는 타일 목록을 저장한다


class EnemyAI : public Player
{
    // A* 노드 정의
    struct Node {
        Vector2 pos;
        int gScore;         // g-score: 시작 지점부터 이 노드까지 실제 비용
        int fScore;          // f-score : g-score + 휴리스틱 값 
        
        bool operator<(const Node& o) const
        {
            return fScore > o.fScore;  // f가 작은 것이 우선
        }
    };

public:
    EnemyAI(const char* image, Vector2 startPosIndex, EDirection startDir, ETileState targetTile /*Front 혹은 Back*/);
    virtual  ~EnemyAI() {};

    virtual void Tick(float deltaTime) override;

    void SetMoveSpeed(float speed);

private:
    // 상대 타일 인접 칸(뒤집기 위치) 수집
    std::vector<Vector2> CollectFlipTargetTiles();
    // 길찾기
    std::vector<Vector2> AStar(std::vector<Vector2>& goals);
  
    // 멘하튼 휴리스틱 
    int Heuristic(const Vector2& a, const Vector2& b) {
        return abs(a.x - b.x) + abs(a.y - b.y);
    }

    int MinGoalHeuristic(const Vector2& start, const std::vector<Vector2>& goals);

private:
    float moveSpeed = 0.5f;
    float elapsedTime = 0.f;

};