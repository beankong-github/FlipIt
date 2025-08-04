#pragma once
#include <unordered_map>
#include "Types.h"
#include "Asset/IAsset.h"

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

	// TODO : EResourceType -> RTTI의 TypeID로 대체
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

	IAsset* GetResource(EResourceType type, const char* name);


private:
	// 리소스 데이터들
	std::unordered_map<const char*, IAsset*> resourceTableArray[(int)EResourceType::MAX];
};

