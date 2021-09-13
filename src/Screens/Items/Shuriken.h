#pragma once

#include "ItemBase.h"

class Shuriken : public ItemBase {
public:
	explicit Shuriken(Vector2 spawnVector = { 0 });
	void Draw() override;
	~Shuriken() = default;

private:

};