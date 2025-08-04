#include "Image.h"

Image::Image(const char* name)
	: IAsset("Image", name)
{
}

Image::~Image()
{
	SafeDeleteArray(buffer);
}

void Image::Save()
{
}

void Image::Load()
{
	const char* filepath = GetFullAssetPath();
	FILE* file = nullptr;
	fopen_s(&file, filepath, "rt");

	if (file == nullptr)
	{
		__debugbreak;
		std::cout << "맵 파일 읽기 실패. : " << filepath << '\n';
		return;
	}

	// 파싱
	// 파일에 저장된 문자열 크기 읽기
	fseek(file, 0, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	// 파일 데이터를 버퍼에 저장
	buffer = new char[fileSize + 1];
	memset(buffer, 0, fileSize + 1);
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);

	fclose(file);
}
