#pragma once

#include "ItemBase.h"

class ArmFloats : public ItemBase {
public:
	explicit ArmFloats(Vector2 spawnVector);
	void Draw() override;
	~ArmFloats() = default;

private:

};