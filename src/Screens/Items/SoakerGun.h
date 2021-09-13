#pragma once

#include "ItemBase.h"

class SoakerGun : public ItemBase {
public:
	explicit SoakerGun(Vector2 spawnVector = { 0 });
	void Draw() override;
	~SoakerGun() = default;

private:

};