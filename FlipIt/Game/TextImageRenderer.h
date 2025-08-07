#pragma once
#include "Math/Vector2.h"
#include "Math/Color.h"
#include"Types.h"
#include <unordered_map>

// stirng -> DisplayText
// 각 글자를 이미지로 치환하는 역할
// 지원하는 글자 : 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, : , 

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

	// 액터 위치 끝 위치를 반환한다. (좌상)
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


