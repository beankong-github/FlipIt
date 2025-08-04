#include "ResourceMgr.h"
#include <iostream>
#include <windows.h>
#include "Core.h"

#include "Asset/IAsset.h"
#include "Asset/Image.h"
#include "Asset/Map.h"

ResourceMgr::ResourceMgr()
{
	// Asset ���� �ε�
    for (int type = 0; type < (int)EResourceType::MAX; ++type)
    {
        // Ÿ�Կ� ���� Ÿ�� ��� ã��
        static char path[100];
        // WARN ! ���ҽ��� txt Ÿ�Ը� �о� �´�. (��Ȳ�� ���� ���� �ʿ�)
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
                    newResource = CreateResource<Image>(findFileData.cFileName);
                    break;
                case EResourceType::Map:
                    // TODO Map ���ҽ� �߰�
                    newResource = CreateResource<Map>(findFileData.cFileName);
                    break;
                }

                // ���ҽ� �ؽ� ���̺� ���� �̸��� ���� ����
                if(newResource != nullptr)
                    resourceTableArray[type].emplace(std::make_pair(findFileData.cFileName, newResource));
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
        SafeDeleteHashTable<const char*, IAsset*>(resourceTableArray[i]);
    }
}
