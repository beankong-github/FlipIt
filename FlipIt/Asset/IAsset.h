#pragma once
#include "Core.h"
#include "RTTI.h"
#include "Game/Types.h"
#include <iostream>

class IAsset : public RTTI
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
	// WARN ������ Ȯ���ڴ� ���� .txt�� �����Ǿ� �ִ�.
	// TODO  ���� ���� ���� Ȯ���ڰ�  �޶��� ��� GetFullAssetPath�� �������̵��Ͽ� ������ �ؾ� �Ѵ�.
	const char* GetFullAssetPath() const
	{
		static /*thread_local*/ char assetFullPath[255]; // ��Ƽ ������ ��� ��, thread_local ���
		snprintf(assetFullPath, sizeof(assetFullPath), "%s%s/%s", assetFilePath, type, name);
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
