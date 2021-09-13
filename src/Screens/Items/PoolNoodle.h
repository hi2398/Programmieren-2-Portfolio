#pragma once

#include "ItemBase.h"

class PoolNoodle : public ItemBase {
public:
	explicit PoolNoodle(Vector2 spawnVector = { 0 });
	void Draw() override;
	~PoolNoodle() = default;

private:

};