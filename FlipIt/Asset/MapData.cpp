#include "MapData.h"

MapData::MapData(const char* name)
	:IAsset("Map", name)
{

}

MapData::~MapData()
{
}

void MapData::Save()
{

}

void MapData::Load()
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
	char* buffer = new char[fileSize + 1];
	memset(buffer, 0, fileSize + 1);
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);

	for (int i = 0; i < (int)readSize;)
	{
		std::vector<ETileState> state;

		while (buffer[i] != '\n')
		{
			switch (buffer[i])
			{
			case('F'):
				state.emplace_back(ETileState::Front);
				break;

			case('B'):
				state.emplace_back(ETileState::Back);
				break;
			}

			++i;
		}

		if (!state.empty())
			initialTileStates.emplace_back(std::move(state));

		++i;
	}

	delete[] buffer;
	fclose(file);
}

Vector2 MapData::MapSize() const
{
	Vector2 size(0, 0);
	size.y = initialTileStates.size();// �� ũ��
	if (size.y > 0)
		size.x = initialTileStates[0].size();

	return size;
}
