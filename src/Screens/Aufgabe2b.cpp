#include "Aufgabe2b.h"
#include "raylib.h"
#include "../global.h"
#include "StartScreen.h"
#include "Items/ItemList.h"
#include "InventoryScreen.h"


Aufgabe2b::Aufgabe2b() : Screen(SceneName::Aufgabe2b) {
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
			map[j][i].position = { (float)i * TILE_SIZE, (float)j * TILE_SIZE };
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
	for (int n = 0; n < 7; n++) {
		thisTile = GetRandomValue(0, emptySpace.size() - 1); //get a random passable tile
		itemvec = { emptySpace[thisTile] };
		switch (n)
		{
		case 0:
			item.emplace_back(std::make_unique<Cap>(itemvec)); //emplaces item on this position
			break;
		case 1:
			item.emplace_back(std::make_unique<SoakerGun>(itemvec));
			break;
		case 2:
			item.emplace_back(std::make_unique<PoolNoodle>(itemvec));
			break;
		case 3:
			item.emplace_back(std::make_unique<ArmFloats>(itemvec));
			break;
		case 4:
			item.emplace_back(std::make_unique<Snorkel>(itemvec));
			break;
		case 5:
			item.emplace_back(std::make_unique<FloatRing>(itemvec));
			break;
		case 6:
			item.emplace_back(std::make_unique<Shuriken>(itemvec));
			break;
		}

		emptySpace.erase(emptySpace.begin() + thisTile); //erases element when an item is placed on it
	}



	Vector2 playerSpawn = { 10 * 16, 0 };
	player = std::make_shared<PlayerChar>(playerSpawn);


	invInterface = std::make_unique<InventoryScreen>(sceneName, *player);

}

void Aufgabe2b::Input()
{
	if (!inventoryIsOpen) {
		if (IsKeyReleased(KEY_BACKSPACE)) nextScreen = std::make_shared<StartScreen>(); //go back to start menu
		if (IsKeyReleased(KEY_E)) inventoryIsOpen = true; // open inventory

		for (const auto& row : map) {//move player when standing on slippery tile
			for (const auto& element : row) {
				if (element.position.x == player->GetPosition().x && element.position.y == player->GetPosition().y) {
					if (element.type == TileType::FINISH) {
						player->MoveTo(player->GetLastDirection(), map);
					}
				}
			}
		}

		for (const auto& row : map) {//move player when standing on slippery tile
			for (const auto& element : row) {
				if (element.position.x == player->GetPosition().x && element.position.y == player->GetPosition().y) {
					if (element.type == TileType::SLIPPERY) {
						player->MoveTo(player->GetLastDirection(), map);
					}
				}
			}
		}

		//player controls
		if (IsKeyReleased(KEY_W)) player->MoveTo({ 0, -16 }, map);
		if (IsKeyReleased(KEY_A)) player->MoveTo({ -16, 0 }, map);
		if (IsKeyReleased(KEY_S)) player->MoveTo({ 0, 16 }, map);
		if (IsKeyReleased(KEY_D)) player->MoveTo({ 16, 0 }, map);



	}
	else {
		if (IsKeyReleased(KEY_E)) inventoryIsOpen = false;
		invInterface->Input(*player);
	}
}


void Aufgabe2b::Update()
{
	if (!inventoryIsOpen) {
		frameCounter++;
		if (frameCounter >= 15) {
			thisFrame++;
			frameCounter = 0;
		}
		activeFrame = { 0, (float)thisFrame * 16, 16, 16 };

		for (int i = 0; i < item.size(); i++) {
			if (item[i]->GetPosition().x == player->GetPosition().x && item[i]->GetPosition().y == player->GetPosition().y && item[i]->IsVisible()) {
				player->GetInventory()->SetItem(*item[i], GetFreeInventorySlot());
				item[i]->SetIsVisible(false);
			}
		}
	}
	else {
		invInterface->Update(*player);
	}
	player->Update();

}

int Aufgabe2b::GetFreeInventorySlot()
{
	int counter = 0;
	for (int i = 0; i < player->GetInventory()->GetSlots(); i++) {
		if (player->GetInventory()->GetItem(i).GetType() == ItemType::Empty) {
			return i;
		};
	}
	return 0;
}

void Aufgabe2b::Draw()
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
		if (items->IsVisible()) {
			items->Draw();
		}
	}

	//draw player
	player->Draw();


	//draw inventory when open
	if (inventoryIsOpen) {
		invInterface->Draw();
	}
}