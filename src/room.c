// room code

#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "controls.h"
#include "background.h"
#include "bullets.h"
#include "enemies.h"
#include "enemytypes.h"
#include "room.h"
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
	blocks[i].col.x = fix16Sub(blocks[i].pos.x, COL_BLOCK_OFF);
	blocks[i].col.y = fix16Sub(blocks[i].pos.y, COL_BLOCK_OFF);
	blocks[i].col.w = fix16Add(fix16Add(blocks[i].pos.x, BLOCK_SZ), COL_BLOCK_OFF);
	blocks[i].col.z = fix16Add(fix16Add(blocks[i].pos.y, BLOCK_SZ), COL_BLOCK_OFF);
	blockTile = BLOCK_TILE_1 + type * 4;
	switch(type){
		case 1: blockImg = &block1; break;
		case 2: blockImg = &block2; break;
		case 3: blockImg = &block3; break;
	}
	VDP_drawImageEx(BG_A, blockImg, TILE_ATTR_FULL(PAL1, 0, 0, 0, blockTile), x + TILE_OFF_X, y + TILE_OFF_Y, 0, DMA);
}

void updateBlocks(){
	for(s16 i = 0; i < COL_BLOCK_CT; i++) colPBlocks[i] = -1;
	for(s16 i = 0; i < BLOCK_CT; i++) if(blocks[i].active && !blocks[i].dead){
		if(gameClock % 2 == 0) blockBulletCol(i);
		blockPlayerCol(i);
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
	for(s16 i = 0; i < 4; i++) spawnBlock(i < 2 ? 0 : ROOM_W - 2, i % 2 == 0 ? ROOM_H - 2 : 0, 1, TRUE);
	for(s16 y = 0; y < ROOM_H; y++) for(s16 x = 0; x < ROOM_W + 1; x++){
		if(x % 2 == 0 && y % 2 == 0 && x < ROOM_W){
			if(x == 0 && (!opens.x || (opens.x && (y == DOOR_Y_START || y == DOOR_Y_END)))) spawnBlock(x, y, 1, !opens.x);

			if(x == ROOM_W - 2 && (!opens.w || (opens.w && (y <= DOOR_Y_START || y >= DOOR_Y_END)))) spawnBlock(x, y, 1, !opens.w);

			if(y == 0 && (!opens.y || (opens.y && (x == DOOR_X_START || x == DOOR_X_END)))) spawnBlock(x, y, 1, !opens.y);
			if(y == ROOM_H - 2 && (!opens.z || (opens.z && (x == DOOR_X_START || x == DOOR_X_END)))) spawnBlock(x, y, 1, !opens.z);
		}
	}
}

void loadRoomTiles(){
	for(s16 y = 0; y < BLOCK_HEIGHT; y++) for(s16 x = 0; x < BLOCK_WIDTH; x++){
		if(roomLayout[y][x] > 0){
			needBlockCancel = FALSE;
			if(roomLayout[y][x] < 10){
				if(y > 0 && roomLayout[y - 1][x] > 0 && y < BLOCK_WIDTH - 1 && roomLayout[y + 1][x] > 0 &&
					x > 0 && roomLayout[y][x - 1] > 0 && x < BLOCK_HEIGHT - 1 && roomLayout[y][x + 1] > 0) needBlockCancel = TRUE;
				spawnBlock((x + 1) * 2, (y + 1) * 2, roomLayout[y][x], needBlockCancel);
			} else {
				roomEnemyX = (x + 1) * 2 * 8 + 8;
				roomEnemyY = (y + 1) * 2 * 8 + 8;
				switch(roomLayout[y][x]){
					case 10:
						spawnBoss1(roomEnemyX, roomEnemyY);
						break;
				}
			}
		}
	}
}


// ----------------------
// room routines
// ----------------------

void a1(){ // start
	loadRoomBorder(FALSE, TRUE, FALSE, FALSE);
	// 10
	s16 tempLayout[BLOCK_HEIGHT][BLOCK_WIDTH] = {
		{01, 00, 01, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
		{00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 01, 00, 00},
		{00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
		{00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
		{00, 00, 00, 00, 00, 00, 00, 00, 02, 02, 00, 00, 00, 00},
		{00, 00, 00, 00, 00, 00, 00, 02, 00, 00, 00, 01, 00, 00},
		{00, 00, 00, 00, 00, 00, 00, 02, 00, 00, 00, 01, 00, 00},
		{00, 00, 00, 00, 00, 01, 02, 00, 00, 00, 00, 00, 00, 00},
		{00, 00, 02, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
		{00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 01},
	};
	memcpy(roomLayout, tempLayout, sizeof(roomLayout));
	loadRoomTiles();
	MEM_free(tempLayout);
	rightRoom = a2;
}

void a2(){ // fish and worm
	loadRoomBorder(TRUE, TRUE, FALSE, FALSE);
	s16 tempLayout[BLOCK_HEIGHT][BLOCK_WIDTH] = {
		{0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
	memcpy(roomLayout, tempLayout, sizeof(roomLayout));
	loadRoomTiles();
	MEM_free(tempLayout);
	leftRoom = a1;
	rightRoom = a3;
}

void a3(){ // junction, ways down or continue right, worms
	loadRoomBorder(TRUE, TRUE, FALSE, TRUE);
	s16 tempLayout[BLOCK_HEIGHT][BLOCK_WIDTH] = {
		{0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0}
	};
	leftRoom = a2;
	rightRoom = a4;
	bottomRoom = a1;
	memcpy(roomLayout, tempLayout, sizeof(roomLayout));
	loadRoomTiles();
	MEM_free(tempLayout);
	// spawnBakebake(5 * 16, 32, FALSE);
	// spawnBakebake(9 * 16, 32, TRUE);
}

void a4(){ // fish and worms
	loadRoomBorder(TRUE, TRUE, FALSE, FALSE);
	s16 tempLayout[BLOCK_HEIGHT][BLOCK_WIDTH] = {
		{0, 0, 0, 1, 0, 0, 2, 1, 0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}
	};
	leftRoom = a3;
	rightRoom = a5;
	memcpy(roomLayout, tempLayout, sizeof(roomLayout));
	loadRoomTiles();
	MEM_free(tempLayout);
}

void a5(){ // bug and worms
	loadRoomBorder(TRUE, TRUE, FALSE, FALSE);
	s16 tempLayout[BLOCK_HEIGHT][BLOCK_WIDTH] = {
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0}
	};
	leftRoom = a4;
	rightRoom = a5;
	memcpy(roomLayout, tempLayout, sizeof(roomLayout));
	loadRoomTiles();
	MEM_free(tempLayout);
}


// ----------------------
// room movement
// ----------------------

void nextRoom(s16 direction){
	removeBlocks();
	clearEnemies();
	clearBullets();
	switch(direction){
		case 0: // up
			pPos.y = PLAYER_INIT_BOTTOM;
			changeRoom = topRoom;
			break;
		case 1: // right
			pPos.x = PLAYER_INIT_LEFT;
			changeRoom = rightRoom;
			break;
		case 2: // down
			pPos.y = PLAYER_INIT_TOP;
			changeRoom = bottomRoom;
			break;
		case 3: // left
			pPos.x = PLAYER_INIT_RIGHT;
			changeRoom = leftRoom;
			break;
	}
	changeRoom();
}


// tiles

void loadOverlay(){
	for(s16 x = 0; x < ROOM_W; x++) for(s16 y = 0; y < ROOM_H; y++){
		VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, HALF_TILE), x + TILE_OFF_X, y + TILE_OFF_Y);
	}
}

void loadTiles(){
	loadOverlay();
	switch(currentRoomType){
		case 1: a1(); break;
	}
}


// ----------------------
// export
// ----------------------

void loadRoom(){
	currentRoomType = 1;
	loadTiles();
}

void updateRoom(){
	updateBlocks();
}