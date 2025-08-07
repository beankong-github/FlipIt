#include "TextImageRenderer.h"
#include "Game/Game.h"
#include "Game/ResourceMgr.h"
#include "Engine.h"
#include "Asset/ImageData.h"


const char* TextImageRenderer::fonts[3] = {"Timer", "Score", "Text"};


TextImageRenderer::TextImageRenderer()
{
    ResourceMgr* resourceMgr = Game::Get().GetResourceMgr();
    assert(resourceMgr);

    // �ؽ�Ʈ ���ҽ����� �ε��Ѵ�. 
    //  ����
    for (int num = 0; num < 10; ++num)
    {
        for (int i = 0; i < (int)EFont::Text; ++i)
        {
            char text = (num + '0');
            char name[100];
            sprintf_s(name, 100, "%s_%c.txt", fonts[i], text);
            TextImageMap[i].emplace(std::pair<char, ImageData*>(text, dynamic_cast<ImageData*>(resourceMgr->GetResource(EResourceType::Image, name))));
        }
    }
    //�빮��
    int index = 0;
    while ('A' + index <= 'Z')
    {
        char text = (index + 'A');
        char name[100];
        sprintf_s(name, 100, "%s_%c.txt", fonts[(int)EFont::Text], (char)('A'+index));
        TextImageMap[(int)EFont::Text].emplace(std::pair<char, ImageData*>(text, dynamic_cast<ImageData*>(resourceMgr->GetResource(EResourceType::Image, name))));
        ++index;
    }
    // �ҹ���
    index = 0;
    while ('a' + index <= 'z')
    {
        char text = (index + 'a');
        char name[100];
        sprintf_s(name, 100, "%s_l%c.txt", fonts[(int)EFont::Text], (char)('a' + index));
        TextImageMap[(int)EFont::Text].emplace(std::pair<char, ImageData*>(text, dynamic_cast<ImageData*>(resourceMgr->GetResource(EResourceType::Image, name))));
        ++index;
    }

    // �� �� (�̰� �����ؾ��Ѵ� �̤� )
    // Timer ��Ʈ�� :
    char key = ':';
    TextImageMap[(int)EFont::Timer].emplace(std::pair<char, ImageData*>(key, dynamic_cast<ImageData*>(resourceMgr->GetResource(EResourceType::Image, "Colon.txt"))));
    
    // Text ��Ʈ��:
    key = '!';
    TextImageMap[(int)EFont::Text].emplace(std::pair<char, ImageData*>(key, dynamic_cast<ImageData*>(resourceMgr->GetResource(EResourceType::Image, "Text_!.txt"))));

}

TextImageRenderer::~TextImageRenderer()
{
}

Vector2 TextImageRenderer::RenderText(const char* text, Vector2 pos, EColor color, EColor backgroundColor, int sortingOrder, EFont font)
{
   // char* cur = const_cast<char*>(text);
    Vector2 position = pos;

    if (font == EFont::None || font == EFont::Max)
        return position;

    int index = 0;
    while (text[index])
    {       
       
           // �̹��� �����Ͱ� ������ ��� �����Ѵ�
        if (TextImageMap[(int)font].find(text[index]) == TextImageMap[(int)font].end())
        {
            ++index;
            continue;
        }
        ImageData* curImageData = TextImageMap[(int)font].find(text[index])->second;

        // �̹��� �����Ͱ� ������ ��� �����Ѵ�
        if (curImageData == nullptr)
        {
            ++index;
            continue;
        }

        Engine::Get().WriteToBuffer(position, curImageData->Size(), curImageData->Buffer(), color, backgroundColor, sortingOrder);
        position.x += curImageData->Size().x;
        ++index;
    }

    return position;
}
