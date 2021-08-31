#pragma once

#include "ItemBase.h"

class Snorkel : public ItemBase {
public:
	explicit Snorkel(Vector2 spawnVector);
	void Draw() override;
	~Snorkel() = default;

private:

};