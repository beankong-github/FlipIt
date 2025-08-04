#include "ImageData.h"
#include "Map.h"

ImageData::ImageData(const char* name)
	: IAsset("Image", name)
	,buffer(nullptr)
	, size(Vector2(0,0))
{
}

ImageData::~ImageData()
{
	SafeDeleteArray(buffer);
}

void ImageData::Save()
{
}

void ImageData::Load()
{
	const char* filepath = GetFullAssetPath();
	FILE* file = nullptr;
	fopen_s(&file, filepath, "rt");

	if (file == nullptr)
	{
		//__debugbreak;
		std::cout << "맵 파일 읽기 실패. : " << filepath << '\n';
		return;
	}

	// 파싱
	// 파일에 저장된 문자열 크기 읽기
	fseek(file, 0, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	// 파일 데이터를 버퍼에 저장
	char* tmp = new char[fileSize + 1];
	memset(tmp, 0, fileSize + 1);
	buffer = new char[fileSize + 1];
	memset(buffer, 0, fileSize + 1);
	size_t readSize = fread(tmp, sizeof(char), fileSize, file);
	fclose(file);
	
	int bufferIndex = 0;
	for (int i = 0; i < (int)readSize; ++i)
	{
		if (tmp[i] == '\n')
		{
			++size.y;
			continue;
		}
		
		buffer[bufferIndex] = tmp[i];
		++bufferIndex;
	}

	size.y += 1;
	size.x = readSize / size.y;

}
