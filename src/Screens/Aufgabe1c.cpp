#include "Aufgabe1c.h"
#include "raylib.h"
#include "../global.h"
#include "StartScreen.h"
#include "Items/Cap.h"

Aufgabe1c::Aufgabe1c() : Screen(SceneName::Aufgabe1c) {
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
		//20 elements per row
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

	//save all empty/"passable" tiles
	Vector2 tmp;
	int x = 0;
	int y = 0;
	for (const auto& column : map) {
		for (const auto& element : column) {
			tmp.x = TILE_SIZE * x;
			tmp.y = TILE_SIZE * y;
			if (element.type == TileType::PASSABLE) {
				emptySpace.emplace_back(tmp); //add element for each empty tile
			}
			x++;
		}
		x = 0;
		y++;
	}
	
	//emplace five items on a random empty tile
	Vector2 itemvec;
	int thisTile;
	for (int n = 0; n < 5; n++) {
		thisTile = GetRandomValue(0, emptySpace.size() - 1);
		itemvec = { emptySpace[thisTile] };
		item.emplace_back(std::make_unique<Cap>(itemvec)); //emplaces item on this position
		emptySpace.erase(emptySpace.begin() + thisTile-1); //erases element when an item is placed on it
	}
	
}

void Aufgabe1c::Input()
{
	if (IsKeyReleased(KEY_BACKSPACE)) nextScreen = std::make_shared<StartScreen>();
}

void Aufgabe1c::Update()
{
	frameCounter++;
	if (frameCounter >= 15) {
		thisFrame++;
		frameCounter = 0;
	}
	activeFrame = { 0, (float)thisFrame * 16, 16, 16 };


}

void Aufgabe1c::Draw()
{
	ClearBackground(GREEN);
	//draw tiles
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

	//draw items
	for (const auto& items : item) {
		items->Draw();
	}
}