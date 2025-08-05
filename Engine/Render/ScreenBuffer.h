#pragma once

#include <Windows.h>
#include "Math/Vector2.h"

/*
* �ۼ���: �弼��.
* Screen buffer
* ���� ���۸� ������ ����� ȭ�� ���� Ŭ����.
*/

class ScreenBuffer
{
	friend class Engine;

public:
	// ���ο� ���۸� ������ �� ����� ������.
	ScreenBuffer(const Vector2& screenSize, int fontSize);

	// conslle�� ���޵� �ڵ��� ����� �ܼ� ���� ����.
	ScreenBuffer(HANDLE console, const Vector2& screenSize, int fontSize);

	// �Ҹ���.
	~ScreenBuffer();

	// ���� �����.
	void Clear();

	// �ܼ� ���ۿ� ���ڿ� ���۸� �� �� ����ϴ� �Լ�.
	void Render(CHAR_INFO* charInfo);

private:

	// �ܼ� �ڵ�.
	HANDLE consoleBuffer = nullptr;

	// �ܼ� ȭ�� ũ��.
	Vector2 screenSize;
};