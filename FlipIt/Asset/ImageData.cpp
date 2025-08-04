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
		std::cout << "�� ���� �б� ����. : " << filepath << '\n';
		return;
	}

	// �Ľ�
	// ���Ͽ� ����� ���ڿ� ũ�� �б�
	fseek(file, 0, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	// ���� �����͸� ���ۿ� ����
	buffer = new char[fileSize + 1];
	memset(buffer, 0, fileSize + 1);
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);
	
	for (int i = 0; i < (int)readSize;++i)
	{
		if (buffer[i] == '\n')
			++size.y;
	}
	size.y += 1;
	size.x = readSize / size.y;

	fclose(file);
}
