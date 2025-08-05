#include "ScreenBuffer.h"
#include <iostream>

ScreenBuffer::ScreenBuffer(const Vector2& screenSize, int fontSize)
	: screenSize(screenSize)
{
	// 접근 모드 설정 (읽기/쓰기).
	unsigned long accessMode = GENERIC_READ | GENERIC_WRITE;

	// 공유 모드 설정 (파일 입출력).
	unsigned long shareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;

	// 콘솔 버퍼 생성.
	consoleBuffer = CreateConsoleScreenBuffer(accessMode, shareMode, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	// 예외처리: 버퍼 생성 실패.
	if (consoleBuffer == INVALID_HANDLE_VALUE)
	{
		//__debugbreak();
		std::cout << "버퍼 생성 실패\n";
		return;
	}


	// 콘솔 창 크기 설정.
	SMALL_RECT rect{ 0, 0, (short)screenSize.x, (short)screenSize.y };
	BOOL setWindowsInfoResult = SetConsoleWindowInfo(consoleBuffer, true, &rect);
	if (!setWindowsInfoResult)
	{
		CONSOLE_SCREEN_BUFFER_INFO  returnValue;
		GetConsoleScreenBufferInfo(consoleBuffer, &returnValue);

		std::cerr << "Failed to set console window size\n";
		__debugbreak();
	}

	// 콘솔 버퍼 크기 설정
	BOOL setScreenBufferSizeResult
		= SetConsoleScreenBufferSize(consoleBuffer, Vector2(screenSize.x + 1, screenSize.y + 1));
	if (!setScreenBufferSizeResult)
	{
		std::cerr << "Failed to set screen buffer size\n";
		__debugbreak();
	}

	// 커서 안보이게 설정.
	CONSOLE_CURSOR_INFO info{ 1, FALSE };
	SetConsoleCursorInfo(consoleBuffer, &info);

	// 콘솔 폰트 크기 변경
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

	// 콘솔 창 크기 설정.
	SMALL_RECT rect{ 0, 0, (short)screenSize.x, (short)screenSize.y };
	BOOL setWindowsInfoResult = SetConsoleWindowInfo(consoleBuffer, true, &rect);
	if (!setWindowsInfoResult)
	{
		CONSOLE_SCREEN_BUFFER_INFO  returnValue;
		GetConsoleScreenBufferInfo(consoleBuffer, &returnValue);

		std::cerr << "Failed to set console window size\n";
		__debugbreak();
	}

	// 콘솔 버퍼 크기 설정
	BOOL setScreenBufferSizeResult
		= SetConsoleScreenBufferSize(consoleBuffer, Vector2(screenSize.x + 1, screenSize.y + 1));
	if (!setScreenBufferSizeResult)
	{
		std::cerr << "Failed to set screen buffer size\n";
		__debugbreak();
	}
	
	// 커서 안보이게 설정.
	CONSOLE_CURSOR_INFO cursorInfo{ 1, FALSE };
	SetConsoleCursorInfo(consoleBuffer, &cursorInfo);

	// 콘솔 폰트 크기 변경
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
	// 생성한 핸들 해제.
	if (consoleBuffer)
	{
		CloseHandle(consoleBuffer);
	}
}

void ScreenBuffer::Clear()
{
	// 커서 위치.
	Vector2 position;

	// 콘솔에 기록한 글자 수를 반환받기 위한 변수.
	DWORD writtenCount = 0;

	// 화면 버퍼 전체에 빈 문자열 기록.
	// 콘솔 전체에 한 글자를 입력할 때 사용 (memset과 비슷).
	FillConsoleOutputCharacter(consoleBuffer, ' ', (screenSize.x + 1) * screenSize.y + 1, position, &writtenCount);
}

void ScreenBuffer::Render(CHAR_INFO* charInfo)
{
	// 버퍼 위치 초기화.
	Vector2 bufferPosition;

	// 기록할 영역의 크기.
	SMALL_RECT writeRegion{ 0, 0, (short)screenSize.x - 1, (short)screenSize.y - 1 };

	// 전달된 문자 정보를 버퍼에 기록.
	WriteConsoleOutputA(consoleBuffer, charInfo, screenSize, bufferPosition, &writeRegion);
}