#include "ResourceMgr.h"
#include "Asset/IAsset.h"

ResourceMgr::ResourceMgr()
{
	// Asset 파일 로드
	for (int type = 0; type < (int)EResourceType::MAX; ++type)
	{
		// TODO 에셋 로드
		// 타입 특정 경로의 파일들을 모두 읽는다.
		// 해당 파일을 기반으로 에셋 클래스를 생성한다.
		// 에셋 클래스 -> Load
		// Resources 해시 테이블에 저장한다.


	}

}

ResourceMgr::~ResourceMgr()
{
}
