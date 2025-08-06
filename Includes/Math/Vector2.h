#pragma once

#include "Core.h"
#include <Windows.h>

class Engine_API Vector2
{
public:
	Vector2(int x = 0, int y = 0);
	~Vector2();

	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;
	Vector2 operator/(int other) const;
	bool operator==(const Vector2& other) const;
	bool operator != (const Vector2& other) const;

	// ����ȯ ������ �����ε�.
	operator COORD();
	operator COORD() const;

	// ���ڿ��� ���.
	const char* ToString();

	// �ٸ� Vector�� ���� Vector ���� ���� �ִ��� Ȯ��
	bool InRange(const Vector2& other) const;

	static Vector2 Zero;
	static Vector2 One;
	static Vector2 Up;
	static Vector2 Right;

public:
	// X/Y ��ǥ.
	int x = 0;
	int y = 0;

private:
	// ���ڿ� ����.
	char* value = nullptr;
};