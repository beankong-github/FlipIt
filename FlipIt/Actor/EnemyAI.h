#pragma once
#include "Player.h"
#include "Game/Types.h"

// TODO �� AI�� �̵��� ��ġ�� �����Ѵ�.
// 1. ���� ��ü�� ��ȸ�ϸ� �� Ÿ���� �����Ѵ�.
//  2. �� Ÿ�� ���� 4Ÿ�� �߿� AI�� �� �� �ִ� Ÿ�� ����� �����Ѵ�


class EnemyAI : public Player
{
    // A* ��� ����
    struct Node {
        Vector2 pos;
        int gScore;         // g-score: ���� �������� �� ������ ���� ���
        int fScore;          // f-score : g-score + �޸���ƽ �� 
        
        bool operator<(const Node& o) const
        {
            return fScore > o.fScore;  // f�� ���� ���� �켱
        }
    };

public:
    EnemyAI(const char* image, Vector2 startPosIndex, EDirection startDir, ETileState targetTile /*Front Ȥ�� Back*/);
    virtual  ~EnemyAI() {};

    virtual void Tick(float deltaTime) override;

    void SetMoveSpeed(float speed);

private:
    // ��� Ÿ�� ���� ĭ(������ ��ġ) ����
    std::vector<Vector2> CollectFlipTargetTiles();
    // ��ã��
    std::vector<Vector2> AStar(std::vector<Vector2>& goals);
  
    // ����ư �޸���ƽ 
    int Heuristic(const Vector2& a, const Vector2& b) {
        return abs(a.x - b.x) + abs(a.y - b.y);
    }

    int MinGoalHeuristic(const Vector2& start, const std::vector<Vector2>& goals);

private:
    float moveSpeed = 0.5f;
    float elapsedTime = 0.f;

};