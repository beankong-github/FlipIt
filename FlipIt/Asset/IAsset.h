#pragma once
#include "Core.h"
#include "Game/Types.h"
#include <iostream>

class IAsset
{
public:
	IAsset(const char* type, const char* name)
		:type(type), name(name)
	{
	}

	virtual ~IAsset() {}

public:
	virtual void Save() = 0;
	virtual void Load() = 0;

	inline virtual EResourceType GetType() = 0;

public:
	// 에셋의 전체 경로를 반환한다.
	const char* GetFullAssetPath() const
	{
		static /*thread_local*/ char assetFullPath[255]; // 멀티 스레스 사용 시, thread_local 사용
		snprintf(assetFullPath, sizeof(assetFullPath), "%s%s/%s.txt", assetFilePath, type, name);
		return assetFullPath;
	}

private:
	static constexpr const char* assetFilePath = "../Assets/";

protected:
	// 에셋 경로 설정 용도
	// (assetFilePath)/(type)/(name).text
	const char* type;	 // ! 생성자에서 초기화
	const char* name;	 // ! 생성자에서 초기화
};
