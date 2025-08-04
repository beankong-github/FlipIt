#pragma once
#include <unordered_map>
#include "Types.h"

class IAsset;
class ResourceMgr
{

public:
	ResourceMgr();
	~ResourceMgr();


private:
	// 리소스 데이터들
	std::unordered_map<const char*, IAsset*> Resources[(int)EResourceType::MAX];
};

