#pragma once

#include "ItemBase.h"

class SoakerGun : public ItemBase {
public:
	explicit SoakerGun(Vector2 spawnVector);
	void Draw() override;
	~SoakerGun() = default;

private:

};