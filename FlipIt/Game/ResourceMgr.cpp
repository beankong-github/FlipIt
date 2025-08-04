#include "ResourceMgr.h"
#include <iostream>
#include <windows.h>
#include "Core.h"

#include "Asset/IAsset.h"
#include "Asset/Image.h"
#include "Asset/Map.h"

ResourceMgr::ResourceMgr()
{
	// Asset 파일 로드
    for (int type = 0; type < (int)EResourceType::MAX; ++type)
    {
        // TODO 에셋 로드
        // 타입 특정 경로의 파일들을 모두 읽는다.
        // 해당 파일을 기반으로 에셋 클래스를 생성한다.
        // 에셋 클래스 -> Load
        // resourceTableArray에 저장한다.

        // 타입에 따라 타입 경로 찾기
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
            // 리소스 해시 테이블에 파일 이름과 파일 저장
            if (findFileData.cFileName)
            {
                IAsset* newResource = nullptr;
                switch (static_cast<EResourceType>(type))
                {
                case EResourceType::Image:
                    newResource = CreateResource<Image>(findFileData.cFileName);
                    break;
                case EResourceType::Map:
                    // TODO Map 리소스 추가
                    //newResource = CreateResource<Map>(findFileData.cFileName);
                    break;
                }
                if(newResource != nullptr)
                    resourceTableArray[type].emplace(std::make_pair(findFileData.cFileName, newResource));
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
        SafeDeleteHashTable<const char*, IAsset*>(resourceTableArray[i]);
    }
}
