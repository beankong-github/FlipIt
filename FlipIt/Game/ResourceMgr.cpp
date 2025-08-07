#include "ResourceMgr.h"
#include <iostream>
#include <windows.h>
#include "Core.h"

#include "Asset/ImageData.h"
#include "Asset/MapData.h"

ResourceMgr::ResourceMgr()
{
	// Asset 파일 로드
    for (int type = 0; type < (int)EResourceType::MAX; ++type)
    {
        // 타입에 따라 타입 경로 찾기
        // WARN ! 리소스는 txt 타입만 읽어 온다. (상황에 따라 수정 필요)
        static char path[100];
        sprintf_s(path, sizeof(path), "..\\Assets\\%s\\*.txt", ResourceTypeToString(static_cast<EResourceType>(type)));

        // 경로에 첫번째 파일 정보 가져오기
        WIN32_FIND_DATA findFileData;
        HANDLE hFind = FindFirstFile(path, &findFileData);

        // 파일 가져오기 실패
        if (hFind == INVALID_HANDLE_VALUE) {
            std::cerr << "Error: Unable to open directory." << std::endl;
            return;
        }

        do {
            if (findFileData.cFileName)
            {
                IAsset* newResource = nullptr;

                // 타입 별로 리소스 객체 생성
                switch (static_cast<EResourceType>(type))
                {
                case EResourceType::Image: 
                    newResource = CreateResource<ImageData>(findFileData.cFileName);
                    break;
                case EResourceType::Map:
                    newResource = CreateResource<MapData>(findFileData.cFileName);
                    break;
                }

                // 리소스 해시 테이블에 파일 이름과 파일 저장
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
    // 리소스 메모리 해제
    for (int i = 0; i < (int)EResourceType::MAX; ++i)
    {
        SafeDeleteHashTable<std::string, IAsset*>(resourceTableArray[i]);
    }
}

IAsset* ResourceMgr::GetResource(EResourceType type, const char* name)
{
    // None 혹은 MAX 타입 리소스는 없다. Out of range
    if (type == EResourceType::None || type == EResourceType::MAX)
        return nullptr;

    return  resourceTableArray[(int)type][name];
}

const std::unordered_map<std::string, IAsset*>* ResourceMgr::GetReosurceHashMap(EResourceType type)
{    
    // None 혹은 MAX 타입 리소스는 없다. Out of range
    if (type == EResourceType::None || type == EResourceType::MAX)
        return nullptr;

    return  &resourceTableArray[(int)type];
}
