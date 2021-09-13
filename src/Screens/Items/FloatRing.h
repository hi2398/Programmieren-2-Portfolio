#pragma once

#include "ItemBase.h"

class FloatRing : public ItemBase {
public:
	explicit FloatRing(Vector2 spawnVector = { 0 });
	void Draw() override;
	~FloatRing() = default;

private:

};