#pragma once

#include "ItemBase.h"

class FloatRing : public ItemBase {
public:
	explicit FloatRing(Vector2 spawnVector);
	void Draw() override;
	~FloatRing() = default;

private:

};