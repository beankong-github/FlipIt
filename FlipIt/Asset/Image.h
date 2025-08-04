#pragma once
#include "IAsset.h"

class Image : public IAsset
{
	RTTI_DECLARATIONS(Image, IAsset)

public:
	Image(const char* name);
	virtual ~Image();
	virtual void Save() override;
	virtual void Load() override;

	// �̹��� ���ҽ� Ÿ�� ��ȯ
	inline virtual EResourceType GetType() override { return EResourceType::Image; }


private:
	char* buffer;
};