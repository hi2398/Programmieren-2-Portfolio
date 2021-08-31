#pragma once

#include "ItemBase.h"

class PoolNoodle : public ItemBase {
public:
	explicit PoolNoodle(Vector2 spawnVector);
	void Draw() override;
	~PoolNoodle() = default;

private:

};