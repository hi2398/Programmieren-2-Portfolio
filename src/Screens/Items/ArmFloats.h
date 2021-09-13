#pragma once

#include "ItemBase.h"

class ArmFloats : public ItemBase {
public:
	explicit ArmFloats(Vector2 spawnVector = {0});
	void Draw() override;
	~ArmFloats() = default;

private:

};