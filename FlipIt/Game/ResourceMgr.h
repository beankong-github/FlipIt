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
	// ���ҽ� �����͵�
	std::unordered_map<const char*, IAsset*> Resources[(int)EResourceType::MAX];
};

