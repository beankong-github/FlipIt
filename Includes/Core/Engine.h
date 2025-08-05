#pragma once

#include "Core.h"
#include "Input.h"
#include "Math/Color.h"
#include "Math/Vector2.h"
#include "Actor/Actor.h"

#include <Windows.h>

// ���� ���� ����ü.
struct EngineSettings
{
	// �ܼ� ȭ�� ���� ũ��.
	int width = 0;

	// �ܼ� ȭ�� ���� ũ��.
	int height = 0;

	int fontsize = 0;

	// Ÿ�� ������ �ӵ�.
	float framerate = 0.0f;
};

// �X�� �������� ������ �� �ִ� �̹��� ���� ����ü.
struct ImageBuffer
{
	ImageBuffer(int bufferCount)
	{
		charInfoArray = new CHAR_INFO[bufferCount];
		memset(charInfoArray, 0, sizeof(CHAR_INFO) * bufferCount);
		
		sortingOrderArray = new int[bufferCount];
		memset(charInfoArray, 0, sizeof(int) * bufferCount);
	}

	~ImageBuffer()
	{
		SafeDeleteArray(charInfoArray);
		SafeDeleteArray(sortingOrderArray);
	}

	// �ֿܼ� �׸� �� ����� ����ü (����,���� �� ����).
	CHAR_INFO* charInfoArray = nullptr;

	// �ش� ��ġ�� �׸����� �Ǵ��� �� ����� �X�� ��(sortingOrder).
	int* sortingOrderArray = nullptr;
};

class Level;
class ScreenBuffer;
class Engine_API Engine : public RTTI
{
public:

	// ������.
	Engine();

	// �Ҹ���.
	virtual ~Engine();

	// ���� ���� �Լ�.
	void Run();

	// ���ڿ� �׸��� ��û �Լ�.
	void WriteToBuffer(
		const Vector2& position, const char* image, EColor color = EColor::White, EColor backgroundColor = EColor::None, int sortingOrder = 0
	);

	void WriteToBuffer(const Actor& actor);

	// ���۸� ��ٷ� ��ȯ ��û�� �� ����ϴ� �Լ�.
	void PresentImmediately();

	// ���� �߰� �Լ�.
	void AddLevel(Level* newLevel);

	// �޸� ���� �Լ�.
	virtual void CleanUp();

	// ���� �Լ�.
	void Quit();

	// �̱��� ���� �Լ�.
	static Engine& Get();

	// ȭ�� ����/���� ũ�� ��ȯ �Լ�.
	int Width() const;
	int Height() const;

protected:

	// ����/���� �ʱ�ȭ �� ��� (���� �߰� ��).
	virtual void OnInitialized();

	// �ܼ� â ũ�� ���� �ȵǵ��� �� �� ����ϴ� �Լ�.
	void DisableToResizeWindow();

	void BeginPlay();
	void Tick(float deltaTime = 0.0f);

	// ȭ�� ����� �Լ� (��ü�� �� ���ڿ��� ����).
	void Clear();

	// ���� �׸��� �Լ� (����ۿ� ���).
	void Render();

	// ���� ��ȯ �Լ� (����Ʈ ���� <-> �����)
	void Present();

	// ���� ���� �ε� �Լ�.
	void LoadEngineSettings();

	// ����� ���� Ÿ�� ��ȯ �Լ�.
	ScreenBuffer* GetRenderer() const;

	// ���� ���� ����� �Լ�.
	void ClearImageBuffer();


protected:
	// ���� ���� �÷���.
	bool isQuit = false;

	// ���� ����.
	Level* mainLevel = nullptr;

	// �Է� ������.
	Input input;

	// ���� ����.
	EngineSettings settings;

	// �����(������).
	//CHAR_INFO* imageBuffer = nullptr;
	// ����, ����, �X��(sortingOrder)���� �����ϴ� ����.
	ImageBuffer* imageBuffer = nullptr;
	
	// ���� ����.
	ScreenBuffer* renderTargets[2] = { };

	// ����۷� ����ϴ� ���� Ÿ���� �ε���.
	int currentRenderTargetIndex = 0;

	// �̱��� ����.
	static Engine* instance;
};