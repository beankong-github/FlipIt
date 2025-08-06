#pragma once
#include "Actor/Actor.h"


class UI : public Actor
{
public:
	UI(const char* name, Vector2 pos = Vector2::Zero, Vector2 offset = Vector2::Zero);
	virtual ~UI();

	virtual void Render() override;

	virtual const char* Image() const override;

private:
	class ImageData* imageData;
};