#include "Aufgabe3b.h"
#include "raylib.h"
#include "../global.h"
#include "StartScreen.h"
#include "Items/ItemList.h"
#include "InventoryScreen.h"


Aufgabe3b::Aufgabe3b() : Screen(SceneName::Aufgabe3a) {
	sand = LoadTexture("assets/Sand.png");
	water = LoadTexture("assets/Waves.png");
	towel = LoadTexture("assets/Towel.png");
	chest = LoadTexture("assets/chest.png");

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


	Vector2 playerSpawn = { 10 * 16, 0 };
	player = std::make_shared<PlayerChar>(playerSpawn, 20);


	invInterface = std::make_unique<InventoryScreen>(sceneName, *player);

	//creat three random inventories
	generatedInventory = std::make_shared<Inventory<ItemBase>>(14);


	//fill the three inventories with random Items
	for (int i = 0; i < 14; i++) {		
		if (i == 0 || i == 1) itemCont.emplace_back(std::make_unique<ArmFloats>());
		if (i == 2 || i == 3)itemCont.emplace_back(std::make_unique<Cap>());
		if (i == 4 || i == 5)itemCont.emplace_back(std::make_unique<FloatRing>());
		if (i == 6 || i == 7)itemCont.emplace_back(std::make_unique<PoolNoodle>());
		if (i == 8 || i == 9)itemCont.emplace_back(std::make_unique<Shuriken>());
		if (i == 10 || i == 11)itemCont.emplace_back(std::make_unique<Snorkel>());
		if (i == 12 || i == 13)itemCont.emplace_back(std::make_unique<SoakerGun>());
	}
	for (int i = 0; i < 14; i++) {
		generatedInventory->SetItem(*itemCont[i], i);
	}
}

void Aufgabe3b::Input()
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


void Aufgabe3b::Update()
{
	if (!inventoryIsOpen) {
		frameCounter++;
		if (frameCounter >= 15) {
			thisFrame++;
			frameCounter = 0;
		}
		activeFrame = { 0, (float)thisFrame * 16, 16, 16 };

		if (player->GetPosition().x == invVec1.x && player->GetPosition().y == invVec1.y) { //overwrite player inventory with generated inventory
			for (int i = 0; i < 14; i++) {
				player->GetInventory()->SetItem(generatedInventory->GetItem(i),i);
			}
		}
	}
	else {
		invInterface->Update(*player);
	}
	player->Update();

}

int Aufgabe3b::GetFreeInventorySlot()
{
	int counter = 0;
	for (int i = 0; i < player->GetInventory()->GetSlots(); i++) {
		if (player->GetInventory()->GetItem(i).GetType() == ItemType::Empty) {
			return i;
		};
	}
	return 0;
}

void Aufgabe3b::Draw()
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
			default:
				break;
			}

			tileVec.x += 1;
		}
		tileVec.x = 0;
		tileVec.y += 1;
	}

	//draw chest
	DrawTexture(chest, 9 * 16, 3 * 16, WHITE);



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