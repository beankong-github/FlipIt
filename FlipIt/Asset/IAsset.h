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
	// ������ ��ü ��θ� ��ȯ�Ѵ�.
	const char* GetFullAssetPath() const
	{
		static /*thread_local*/ char assetFullPath[255]; // ��Ƽ ������ ��� ��, thread_local ���
		snprintf(assetFullPath, sizeof(assetFullPath), "%s%s/%s.txt", assetFilePath, type, name);
		return assetFullPath;
	}

private:
	static constexpr const char* assetFilePath = "../Assets/";

protected:
	// ���� ��� ���� �뵵
	// (assetFilePath)/(type)/(name).text
	const char* type;	 // ! �����ڿ��� �ʱ�ȭ
	const char* name;	 // ! �����ڿ��� �ʱ�ȭ
};
