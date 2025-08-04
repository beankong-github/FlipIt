#pragma once
#include <unordered_map>
#include "Types.h"

class IAsset;
class ResourceMgr
{

public:
	ResourceMgr();
	~ResourceMgr();

	template<typename T>
	IAsset* CreateResource(const char* name)
	{
		IAsset* newRes = static_cast<IAsset*>(new T(name));
		if (!newRes)
				return nullptr;

		newRes->Load();
		return newRes;
	}

	static const char* ResourceTypeToString(EResourceType type)
	{
		switch (type)
		{
		case EResourceType::Image:
			return "Image";
			break;
		case EResourceType::Map:
			return "Map";
			break;
		default:
			return "";
			break;
		}
	}

private:
	// 리소스 데이터들
	std::unordered_map<const char*, IAsset*> resourceTableArray[(int)EResourceType::MAX];
};

