#include "ScreenBuffer.h"
#include <iostream>

ScreenBuffer::ScreenBuffer(const Vector2& screenSize, int fontSize)
	: screenSize(screenSize)
{
	// ���� ��� ���� (�б�/����).
	unsigned long accessMode = GENERIC_READ | GENERIC_WRITE;

	// ���� ��� ���� (���� �����).
	unsigned long shareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;

	// �ܼ� ���� ����.
	consoleBuffer = CreateConsoleScreenBuffer(accessMode, shareMode, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	// ����ó��: ���� ���� ����.
	if (consoleBuffer == INVALID_HANDLE_VALUE)
	{
		//__debugbreak();
		std::cout << "���� ���� ����\n";
		return;
	}


	// �ܼ� â ũ�� ����.
	SMALL_RECT rect{ 0, 0, (short)screenSize.x, (short)screenSize.y };
	BOOL setWindowsInfoResult = SetConsoleWindowInfo(consoleBuffer, true, &rect);
	if (!setWindowsInfoResult)
	{
		CONSOLE_SCREEN_BUFFER_INFO  returnValue;
		GetConsoleScreenBufferInfo(consoleBuffer, &returnValue);

		std::cerr << "Failed to set console window size\n";
		__debugbreak();
	}

	// �ܼ� ���� ũ�� ����
	BOOL setScreenBufferSizeResult
		= SetConsoleScreenBufferSize(consoleBuffer, Vector2(screenSize.x + 1, screenSize.y + 1));
	if (!setScreenBufferSizeResult)
	{
		std::cerr << "Failed to set screen buffer size\n";
		__debugbreak();
	}

	// Ŀ�� �Ⱥ��̰� ����.
	CONSOLE_CURSOR_INFO info{ 1, FALSE };
	SetConsoleCursorInfo(consoleBuffer, &info);

	// �ܼ� ��Ʈ ũ�� ����
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = (SHORT)fontSize;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, LF_FACESIZE, L"Consolas"); // Choose your font
	if (!SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi))
	{
		__debugbreak();
	}
}

ScreenBuffer::ScreenBuffer(HANDLE console, const Vector2& screenSize, int fontSize)
	: screenSize(screenSize), consoleBuffer(console)
{
	//hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// �ܼ� â ũ�� ����.
	SMALL_RECT rect{ 0, 0, (short)screenSize.x, (short)screenSize.y };
	BOOL setWindowsInfoResult = SetConsoleWindowInfo(consoleBuffer, true, &rect);
	if (!setWindowsInfoResult)
	{
		CONSOLE_SCREEN_BUFFER_INFO  returnValue;
		GetConsoleScreenBufferInfo(consoleBuffer, &returnValue);

		std::cerr << "Failed to set console window size\n";
		__debugbreak();
	}

	// �ܼ� ���� ũ�� ����
	BOOL setScreenBufferSizeResult
		= SetConsoleScreenBufferSize(consoleBuffer, Vector2(screenSize.x + 1, screenSize.y + 1));
	if (!setScreenBufferSizeResult)
	{
		std::cerr << "Failed to set screen buffer size\n";
		__debugbreak();
	}
	
	// Ŀ�� �Ⱥ��̰� ����.
	CONSOLE_CURSOR_INFO cursorInfo{ 1, FALSE };
	SetConsoleCursorInfo(consoleBuffer, &cursorInfo);

	// �ܼ� ��Ʈ ũ�� ����
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = (SHORT)fontSize;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, LF_FACESIZE, L"Consolas"); // Choose your font
	if (!SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi))
	{
		__debugbreak();
	}
}

ScreenBuffer::~ScreenBuffer()
{
	// ������ �ڵ� ����.
	if (consoleBuffer)
	{
		CloseHandle(consoleBuffer);
	}
}

void ScreenBuffer::Clear()
{
	// Ŀ�� ��ġ.
	Vector2 position;

	// �ֿܼ� ����� ���� ���� ��ȯ�ޱ� ���� ����.
	DWORD writtenCount = 0;

	// ȭ�� ���� ��ü�� �� ���ڿ� ���.
	// �ܼ� ��ü�� �� ���ڸ� �Է��� �� ��� (memset�� ���).
	FillConsoleOutputCharacter(consoleBuffer, ' ', (screenSize.x + 1) * screenSize.y + 1, position, &writtenCount);
}

void ScreenBuffer::Render(CHAR_INFO* charInfo)
{
	// ���� ��ġ �ʱ�ȭ.
	Vector2 bufferPosition;

	// ����� ������ ũ��.
	SMALL_RECT writeRegion{ 0, 0, (short)screenSize.x - 1, (short)screenSize.y - 1 };

	// ���޵� ���� ������ ���ۿ� ���.
	WriteConsoleOutputA(consoleBuffer, charInfo, screenSize, bufferPosition, &writeRegion);
}