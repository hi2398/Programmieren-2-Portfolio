#pragma once

#include "ItemBase.h"

class Cap : public ItemBase {
public:
	explicit Cap(Vector2 spawnVector);
	void Draw() override;
	~Cap() = default;

private:

};