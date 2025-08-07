#pragma once
#include "Math/Vector2.h"
#include "Math/Color.h"
#include"Types.h"
#include <unordered_map>

// stirng -> DisplayText
// �� ���ڸ� �̹����� ġȯ�ϴ� ����
// �����ϴ� ���� : 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, : , 

enum class EFont
{
	None = -1,
	Timer,
	Score,
	Text,
	Max
};

class TextImageRenderer
{
public:
	TextImageRenderer( );
	~TextImageRenderer();

	// ���� ��ġ �� ��ġ�� ��ȯ�Ѵ�. (�»�)
	Vector2 RenderText(const char* text, Vector2 pos, EColor color, EColor backgroundColor, int sortingOrder, EFont font = EFont::Text);
	Vector2 RenderTextEX(
		const char* text
		, Vector2 pos, std::vector<Vector2> offsets
		, std::vector <EColor> colors
		, std::vector <EColor> backgroundColors
		, int sortingOrder
		, EFont font = EFont::Text);
	
	static const char* fonts[(int)EFont::Max];

private:
	std::unordered_map <char, class ImageData* > TextImageMap[(int)EFont::Max];

};


