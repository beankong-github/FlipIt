#pragma once
#include "IAsset.h"
#include "Math/Vector2.h"

class ImageData : public IAsset
{
	RTTI_DECLARATIONS(ImageData, IAsset)

public:
	ImageData(const char* name);
	virtual ~ImageData();
	virtual void Save() override;
	virtual void Load() override;

	// 이미지 리소스 타입 반환
	inline virtual EResourceType GetType() override { return EResourceType::Image; }

	inline const char* Buffer() const { return buffer; }
	inline const Vector2& Size() const { return size; }

private:
	char* buffer;
	Vector2 size;
};