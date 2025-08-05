#pragma once

#include "Core.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "RTTI.h"

// ���� ����.
class Level;
class Engine_API Actor : public RTTI
{
	friend class Level;
	RTTI_DECLARATIONS(Actor, RTTI)

public:
	Actor(
		const char* image = "",
		EColor color = EColor::White,
		EColor background = EColor::None,
		const Vector2& position = Vector2::Zero,
		const Vector2& size = Vector2::Zero
	);
	virtual ~Actor();

	// �̺�Ʈ �Լ�.

	// ��ü �����ֱ�(Lifetime)�� 1���� ȣ��� (�ʱ�ȭ ����).
	virtual void BeginPlay();

	// ������ ���� ȣ�� (�ݺ��� �۾�/���Ӽ��� �ʿ��� �۾�).
	virtual void Tick(float deltaTime);

	// �׸��� �Լ�.
	virtual void Render();

	// BeginPlay ȣ�� ���� Ȯ��.
	inline bool HasBeganPlay() const { return hasBeganPlay; }

	// ��ġ ����/�� �д� �Լ�.
	void SetPosition(const Vector2& newPosition);
	inline Vector2 Position() const;
	void SetSize(const Vector2& newSize);
	inline Vector2 Size() const;

	// ���ڿ� ���� ��ȯ.
	inline int Length() const;

	inline bool IsActive() const { return !isExpired && isActive; }

	// Sorting Order ����.
	void SetSortingOrder(int sortingOrder);
	inline int SortingOrder() const;

	// ���ʽ� ����.
	void SetOwner(Level* newOwner);
	Level* GetOwner();

	// �浹 Ȯ�� ��û �Լ� (������ AABB ����).
	bool TestIntersect(const Actor* const other);

	// ������ �̹��� �� ���� �Լ�.
	void ChangeImage(const char* newImage);
	virtual inline const char* Image() const;

	// ���� �� 
	inline EColor Color() const;
	inline EColor BackgroundColor() const;

	// ��ü ���� �Լ�.
	void Destroy();

	// ��ü�� �����Ǳ� ������ ȣ��Ǵ� �Լ�.
	virtual void OnDestroy();

	// ���� �ֱ� ���� �Լ�.
	void SetLifetime(float newLifetime);

	// ���� ���� ��û �Լ�.
	void QuitGame();

protected:
	// Transform
	//��ġ ���� (�»��)
	Vector2 position;
	// ũ�� ����
	Vector2 size;

	// �׸� ��.
	//char image = ' ';
	char* image = nullptr;

	// ���ڿ� ����.
	int length = 0;

	// �ؽ�Ʈ ���� ��.
	EColor color;
	EColor backgroundColor;

	// BeginPlay ȣ���� �Ǿ����� Ȯ��.
	bool hasBeganPlay = false;

	// ���� ����.
	int sortingOrder = 0;

	// ���Ͱ� Ȱ�� �������� �˷��ִ� ����.
	bool isActive = true;

	// ���� ��û�ƴ��� �˷��ִ� ����.
	bool isExpired = false;

	// ���� �ֱ� (����: ��).
	float lifetime = 0.0f;

	// �� �÷��׸� true�� �����ϸ� ���� �ֱ⸦ ����� �ڵ� ����.
	bool autoDestroy = false;

	// ���� ����(���ʽ�).
	Level* owner = nullptr;
};