#include "Aufgabe1b.h"
#include "raylib.h"
#include "../global.h"
#include "StartScreen.h"

Aufgabe1b::Aufgabe1b() : Screen(SceneName::Aufgabe1b) {
	sand = LoadTexture("assets/Sand.png");
	water = LoadTexture("assets/Waves.png");
	castle = LoadTexture("assets/Castle.png");
	towel = LoadTexture("assets/Towel.png");
	icecream = LoadTexture("assets/Icecream.png");
	crab = LoadTexture("assets/Crab.png");
	//generate 20x20 tile map
	for (int j = 0; j < 20; j++) {
		//20 rows
		map.emplace_back(std::vector<Tile>());

		for (int i = 0; i < 20; i++) {
			map[j].emplace_back();
			map[j][i].type = TileType::PASSABLE;
		}

	}

	//unterste Reihe besteht aus FINISH TILES
	for (int i = 0; i < 20; i++) {
		map[19][i].type = TileType::FINISH;
	}

	//Ein START TILE
	map[0][10].type = TileType::START;

	//Zufällige Verteilung von BLOCKED TILES
	for (int i = 1; i < 19; i++) {
		int j = GetRandomValue(0, 19);
		map[i][j].type = TileType::BLOCKED;
	}

	//Zufällige Verteilung von RESET TILES
	for (int i = 1; i < 19; i++) {
		int j = GetRandomValue(0, 19);
		if (map[i][j].type != TileType::BLOCKED)map[i][j].type = TileType::RESET;
	}

	//Zufällige Verteilung von SLIPPERY TILES
	for (int i = 1; i < 19; i++) {
		for (int j = 0; j < 20; j++) {
			if (GetRandomValue(0, 200) < 5)map[i][j].type = TileType::SLIPPERY;
		}
	}

	//Sicher stellen, dass der mittlere Weg immer passierbar ist
	for (int i = 1; i < 19; i++) {
		for (int j = 10; j < 12; j++) {
			map[i][j].type = TileType::PASSABLE;
		}
	}

}

void Aufgabe1b::Input()
{
	if (IsKeyReleased(KEY_BACKSPACE)) nextScreen = std::make_shared<StartScreen>();
}

void Aufgabe1b::Update()
{
	frameCounter++;
	if (frameCounter >= 15) {
		thisFrame++;
		frameCounter = 0;
	}
	activeFrame = { 0, (float)thisFrame * 16, 16, 16 };


}

void Aufgabe1b::Draw()
{
	ClearBackground(GREEN);
	tileVec.x = 0;
	tileVec.y = 0;
	for (auto& row : map) {

		for (auto& column : row) { // for each element in each row


			switch (column.type)
			{
			case TileType::PASSABLE:
				DrawTexture(sand, tileVec.x * TILE_SIZE, tileVec.y * TILE_SIZE, WHITE);
				break;
			case TileType::START:
				DrawTexture(towel, tileVec.x * TILE_SIZE, tileVec.y * TILE_SIZE, WHITE);
				break;
			case TileType::FINISH:
				DrawTextureRec(water, activeFrame, { tileVec.x * TILE_SIZE, tileVec.y * TILE_SIZE }, WHITE);
				break;
			case TileType::BLOCKED:
				DrawTextureRec(castle, activeFrame, { tileVec.x * TILE_SIZE, tileVec.y * TILE_SIZE }, WHITE);
				break;
			case TileType::SLIPPERY:
				DrawTexture(icecream, tileVec.x * TILE_SIZE, tileVec.y * TILE_SIZE, WHITE);
				break;
			case TileType::RESET:
				DrawTextureRec(crab, activeFrame, { tileVec.x * TILE_SIZE, tileVec.y * TILE_SIZE }, WHITE);
				break;
			default:
				break;
			}

			tileVec.x += 1;
		}
		tileVec.x = 0;
		tileVec.y += 1;
	}
}
