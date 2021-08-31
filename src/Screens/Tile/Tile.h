#pragma once

#include "raylib.h"


static constexpr int TILE_SIZE = 16;

enum class TileType { START, FINISH, PASSABLE, BLOCKED, SLIPPERY, RESET};
struct Tile {
	TileType type;
	Vector2 position;
};

