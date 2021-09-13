#pragma once

#include "ItemBase.h"

class Snorkel : public ItemBase {
public:
	explicit Snorkel(Vector2 spawnVector = { 0 });
	void Draw() override;
	~Snorkel() = default;

private:

};