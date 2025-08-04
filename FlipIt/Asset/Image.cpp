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

	fclose(file);
}
