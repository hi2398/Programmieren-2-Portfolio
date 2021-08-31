#pragma once

#include "ItemBase.h"

class Shuriken : public ItemBase {
public:
	explicit Shuriken(Vector2 spawnVector);
	void Draw() override;
	~Shuriken() = default;

private:

};