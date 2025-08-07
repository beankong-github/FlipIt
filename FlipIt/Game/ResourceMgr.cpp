#include "ResourceMgr.h"
#include <iostream>
#include <windows.h>
#include "Core.h"

#include "Asset/ImageData.h"
#include "Asset/MapData.h"

ResourceMgr::ResourceMgr()
{
	// Asset ���� �ε�
    for (int type = 0; type < (int)EResourceType::MAX; ++type)
    {
        // Ÿ�Կ� ���� Ÿ�� ��� ã��
        // WARN ! ���ҽ��� txt Ÿ�Ը� �о� �´�. (��Ȳ�� ���� ���� �ʿ�)
        static char path[100];
        sprintf_s(path, sizeof(path), "..\\Assets\\%s\\*.txt", ResourceTypeToString(static_cast<EResourceType>(type)));

        // ��ο� ù��° ���� ���� ��������
        WIN32_FIND_DATA findFileData;
        HANDLE hFind = FindFirstFile(path, &findFileData);

        // ���� �������� ����
        if (hFind == INVALID_HANDLE_VALUE) {
            std::cerr << "Error: Unable to open directory." << std::endl;
            return;
        }

        do {
            if (findFileData.cFileName)
            {
                IAsset* newResource = nullptr;

                // Ÿ�� ���� ���ҽ� ��ü ����
                switch (static_cast<EResourceType>(type))
                {
                case EResourceType::Image: 
                    newResource = CreateResource<ImageData>(findFileData.cFileName);
                    break;
                case EResourceType::Map:
                    newResource = CreateResource<MapData>(findFileData.cFileName);
                    break;
                }

                // ���ҽ� �ؽ� ���̺� ���� �̸��� ���� ����
                if (newResource != nullptr)
                {
                    resourceTableArray[type].emplace(std::make_pair(std::string(findFileData.cFileName), std::move(newResource)));
                }
            }
        } while (FindNextFile(hFind, &findFileData) != 0);

        FindClose(hFind);
    }
}

ResourceMgr::~ResourceMgr()
{
    // ���ҽ� �޸� ����
    for (int i = 0; i < (int)EResourceType::MAX; ++i)
    {
        SafeDeleteHashTable<std::string, IAsset*>(resourceTableArray[i]);
    }
}

IAsset* ResourceMgr::GetResource(EResourceType type, const char* name)
{
    // None Ȥ�� MAX Ÿ�� ���ҽ��� ����. Out of range
    if (type == EResourceType::None || type == EResourceType::MAX)
        return nullptr;

    return  resourceTableArray[(int)type][name];
}

const std::unordered_map<std::string, IAsset*>* ResourceMgr::GetReosurceHashMap(EResourceType type)
{    
    // None Ȥ�� MAX Ÿ�� ���ҽ��� ����. Out of range
    if (type == EResourceType::None || type == EResourceType::MAX)
        return nullptr;

    return  &resourceTableArray[(int)type];
}
