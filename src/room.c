// room code

#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "controls.h"
#include "background.h"
#include "bullets.h"
#include "background.h"
#include "enemies.h"
#include "enemytypes.h"
#include "room.h"
#include "maps.h"
#include "player.h"


// blocks

void spawnBlock(s16 x, s16 y, s16 type, bool dead){
	static s16 i = 0; for(s16 j = 0; j < BLOCK_CT; j++) if(!blocks[j].active) i = j;
	blocks[i].active = TRUE;
	blocks[i].dead = dead;
	blocks[i].pos.x = FIX16(x * 8);
	blocks[i].pos.y = FIX16(y * 8);
	blocks[i].pos.w = fix16Add(blocks[i].pos.x, BLOCK_SZ);
	blocks[i].pos.z = fix16Add(blocks[i].pos.y, BLOCK_SZ);
	blocks[i].center.x = fix16Add(blocks[i].pos.x, BLOCK_OFF);
	blocks[i].center.y = fix16Add(blocks[i].pos.y, BLOCK_OFF);
	switch(type){
		case 1:
			blockImg = &rockBlueBottom;
			blockTile = ROCK_BLUE_BOTTOM;
			break;
		case 49:
			blockImg = &rockBlueBottom;
			blockTile = ROCK_BLUE_BOTTOM;
			break;
		case 2:
			blockImg = &rockBlueTop;
			blockTile = ROCK_BLUE_TOP;
			break;
		case 3:
			blockImg = &rockBlueRight;
			blockTile = ROCK_BLUE_RIGHT;
			break;
		case 4:
			blockImg = &rockBlueLeft;
			blockTile = ROCK_BLUE_LEFT;
			break;
		case 5:
			blockImg = &rockBlueCornerX;
			blockTile = ROCK_BLUE_CORNERX;
			break;
		case 6:
			blockImg = &rockBlueCornerW;
			blockTile = ROCK_BLUE_CORNERW;
			break;
		case 7:
			blockImg = &rockBlueCornerY;
			blockTile = ROCK_BLUE_CORNERY;
			break;
		case 8:
			blockImg = &rockBlueCornerZ;
			blockTile = ROCK_BLUE_CORNERZ;
			break;
		case 9:
			blockImg = &rockBlueTopLeft;
			blockTile = ROCK_BLUE_TOP_LEFT;
			break;
		case 10:
			blockImg = &rockBlueTopRight;
			blockTile = ROCK_BLUE_TOP_RIGHT;
			break;
		case 11:
			blockImg = &rockBlueBottomLeft;
			blockTile = ROCK_BLUE_BOTTOM_LEFT;
			break;
		case 12:
			blockImg = &rockBlueBottomRight;
			blockTile = ROCK_BLUE_BOTTOM_RIGHT;
			break;
		case 13:
			blockImg = &rockBlueGrassMiddle;
			blockTile = ROCK_BLUE_GRASS_MIDDLE;
			break;
		case 14:
			blockImg = &rockBlueGrassLeft;
			blockTile = ROCK_BLUE_GRASS_LEFT;
			break;
		case 15:
			blockImg = &rockBlueGrassRight;
			blockTile = ROCK_BLUE_GRASS_RIGHT;
			break;
		case 16:
			blockImg = &rockBlueGrassX;
			blockTile = ROCK_BLUE_GRASS_X;
			break;
		case 17:
			blockImg = &rockBlueGrassW;
			blockTile = ROCK_BLUE_GRASS_W;
			break;
		case 25:
			blockImg = &doorGreen;
			blockTile = DOOR_GREEN;
			break;
		case 30:
			blockImg = &ladder;
			blockTile = LADDER;
			break;
		case 31:
			blockImg = &ladderTop;
			blockTile = LADDER_TOP;
			break;
		case 32:
			blockImg = &ladderBottom;
			blockTile = LADDER_BOTTOM;
			break;
	}
	blocks[i].ladder = type == 30 || type == 31 || type == 32;
	// blocks[i].trigger = random() % 4;
	if(type == 19){
		VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, FULL_TILE), x + TILE_OFF_X, y + TILE_OFF_Y);
		VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, FULL_TILE), x + TILE_OFF_X + 1, y + TILE_OFF_Y);
		VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, FULL_TILE), x + TILE_OFF_X, y + TILE_OFF_Y + 1);
		VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, FULL_TILE), x + TILE_OFF_X + 1, y + TILE_OFF_Y + 1);
	} else VDP_drawImageEx(BG_A, blockImg, TILE_ATTR_FULL(PAL1, 0, 0, 0, blockTile), x + TILE_OFF_X, y + TILE_OFF_Y, 0, DMA);
}

void updateBlocks(){
	onLadder = FALSE;
	for(s16 i = 0; i < BLOCK_CT; i++) if(blocks[i].active && !blocks[i].dead){
		// if(gameClock % 4 == blocks[i].trigger) blockBulletCol(i);
		blocks[i].ladder ? ladderCol(i) : blockPlayerCol(i);
	}
}

void removeBlocks(){
	VDP_clearTileMapRect(BG_A, TILE_OFF_X, TILE_OFF_Y, ROOM_W, ROOM_H);
	for(s16 i = 0; i < BLOCK_CT; i++) if(blocks[i].active) blocks[i].active = FALSE;
	bgPos.x = 0;
	bgPos.y = 0;
}


// room loading

void loadRoomBorder(bool openX, bool openW, bool openY, bool openZ){
	opens.x = openX;
	opens.w = openW;
	opens.y = openY;
	opens.z = openZ;
}

void loadRoomTiles(){
	for(s16 y = 0; y < BLOCK_HEIGHT; y++) for(s16 x = 0; x < BLOCK_WIDTH; x++){
		if(roomLayout[y][x] > 0){
			needBlockCancel = FALSE;
			if(roomLayout[y][x] < 50 ){
				if((y > 0 && roomLayout[y - 1][x] > 0 && y < BLOCK_WIDTH - 1 && roomLayout[y + 1][x] > 0 &&
					x > 0 && roomLayout[y][x - 1] > 0 && x < BLOCK_HEIGHT - 1 && roomLayout[y][x + 1] > 0) ||
					roomLayout[y][x] == 19 || roomLayout[y][x] == 49) needBlockCancel = TRUE;
				spawnBlock(x * 2, y * 2, roomLayout[y][x], needBlockCancel);
			} else {
				roomEnemyX = x * 2 * 8 + 8;
				roomEnemyY = y * 2 * 8 + 8;
				switch(roomLayout[y][x]){
					case 50: weak1(roomEnemyX, roomEnemyY); break;
					case 51: weak2(roomEnemyX, roomEnemyY); break;
				}
			}
		}
	}
}


// room movement

void nextRoom(s16 direction){
	removeBlocks();
	clearEnemies();
	clearBullets();
	loadOverlay();
	switch(direction){
		case 0: // up
			changeRoom = topRoom;
			break;
		case 1: // right
			changeRoom = rightRoom;
			break;
		case 2: // down
			changeRoom = bottomRoom;
			break;
		case 3: // left
			changeRoom = leftRoom;
			break;
	}
	changeRoom();
	changingRoom = direction;
}

void nextRoomPos(){
	switch(changingRoom){
		case 0: // up
			pPos.y = PLAYER_INIT_BOTTOM;
			break;
		case 1: // right
			pPos.x = PLAYER_INIT_LEFT;
			break;
		case 2: // down
			pPos.y = PLAYER_INIT_TOP;
			break;
		case 3: // left
			pPos.x = PLAYER_INIT_RIGHT;
			break;
	}
	changingRoom = -1;
}



// tiles

void loadOverlay(){
	loadRays();
	// for(s16 x = 0; x < ROOM_W; x++) for(s16 y = 0; y < ROOM_H; y++){
		// VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, LEAST_TILE), x + TILE_OFF_X, y + TILE_OFF_Y);
	// }
}

void loadTiles(){
	loadOverlay();
	switch(currentRoomType){
		case 1: a2(); break;
	}
}


// ----------------------
// export
// ----------------------

void loadRoom(){
	changingRoom = -1;
	currentRoomType = 1;
	loadTiles();
}

void updateRoom(){
	updateBlocks();
	if(changingRoom > -1) nextRoomPos();
}