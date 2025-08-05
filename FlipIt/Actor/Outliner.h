#pragma once
#include "Actor/Actor.h"

class Outliner : public Actor
{
	RTTI_DECLARATIONS(Outliner, Actor)

public:
	Outliner(const char* name);
	virtual ~Outliner();

	virtual void Render() override;

	virtual inline const char* Image() const override;

	void ActivateOutliner(Vector2 position, EColor color, EColor backgroundColor = EColor::None);
	void DeactivateOutliner();

private:
	class ImageData* imageData = nullptr;
};