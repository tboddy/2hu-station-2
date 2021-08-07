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

void loadBlocks(){
	// abstract this
	VDP_loadTileSet(block2yx.tileset, BLOCK2_YX, DMA);
	VDP_loadTileSet(block2yw.tileset, BLOCK2_YX + 1, DMA);
	VDP_loadTileSet(block2yy.tileset, BLOCK2_YX + 2, DMA);
	VDP_loadTileSet(block2yz.tileset, BLOCK2_YX + 3, DMA);

	VDP_loadTileSet(blockBlack.tileset, BLOCK2_XX, DMA);
	VDP_loadTileSet(block2xw.tileset, BLOCK2_XX + 1, DMA);
	VDP_loadTileSet(blockBlack.tileset, BLOCK2_XX + 2, DMA);
	VDP_loadTileSet(block2xz.tileset, BLOCK2_XX + 3, DMA);

	VDP_loadTileSet(blockBlack.tileset, BLOCK2_C, DMA);
	VDP_loadTileSet(block2c.tileset, BLOCK2_C + 1, DMA);
	VDP_loadTileSet(blockBlack.tileset, BLOCK2_C + 2, DMA);
	VDP_loadTileSet(blockBlack.tileset, BLOCK2_C + 3, DMA);

	VDP_loadTileSet(block3x.tileset, BLOCK3_X, DMA);
	VDP_loadTileSet(block3w.tileset, BLOCK3_X + 1, DMA);
	VDP_loadTileSet(block3y.tileset, BLOCK3_X + 2, DMA);
	VDP_loadTileSet(block3z.tileset, BLOCK3_X + 3, DMA);

	VDP_loadTileSet(block4x.tileset, BLOCK4_X, DMA);
	VDP_loadTileSet(block4w.tileset, BLOCK4_X + 1, DMA);
	VDP_loadTileSet(block4y.tileset, BLOCK4_X + 2, DMA);
	VDP_loadTileSet(block4z.tileset, BLOCK4_X + 3, DMA);

	VDP_loadTileSet(block5x.tileset, BLOCK5_X, DMA);
	VDP_loadTileSet(block5w.tileset, BLOCK5_X + 1, DMA);
	VDP_loadTileSet(block5y.tileset, BLOCK5_X + 2, DMA);
	VDP_loadTileSet(block5z.tileset, BLOCK5_X + 3, DMA);

	VDP_loadTileSet(block6x.tileset, BLOCK6_X, DMA);
	VDP_loadTileSet(block6w.tileset, BLOCK6_X + 1, DMA);
	VDP_loadTileSet(block6y.tileset, BLOCK6_X + 2, DMA);
	VDP_loadTileSet(block6z.tileset, BLOCK6_X + 3, DMA);

}

void spawnBlock(s16 x, s16 y, s16 type, bool dead, bool flipH, bool flipV){
	blockFlipH = flipH;
	blockFlipV = flipV;
	static s16 i = 0; for(s16 j = 0; j < BLOCK_CT; j++) if(!blocks[j].active) i = j;
	blocks[i].active = TRUE;
	blocks[i].dead = dead;
	blocks[i].pos.x = FIX16(x * 8);
	blocks[i].pos.y = FIX16(y * 8);
	blocks[i].pos.w = fix16Add(blocks[i].pos.x, BLOCK_SZ);
	blocks[i].pos.z = fix16Add(blocks[i].pos.y, BLOCK_SZ);
	switch(type){
		case 1: blockTile = BLOCK2_YX; break;
		case 2: blockTile = BLOCK2_XX; break;
		case 3: blockTile = BLOCK2_C; break;
		case 10: blockTile = BLOCK3_X; break;
		case 11:
			blockTile = BLOCK3_X;
			blockFlipV = TRUE;
			break;
		case 12: blockTile = BLOCK4_X; break;
		case 13: blockTile = BLOCK5_X; break;
		case 14: blockTile = BLOCK6_X; break;
		case 15:
			blockTile = BLOCK6_X;
			blockFlipH = TRUE;
			break;
	}

	// clean up this fucking mess!
	if(blockFlipH && blockFlipV){
		VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 1, 1, blockTile + 3), x + TILE_OFF_X, y + TILE_OFF_Y);
		VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 1, 1, blockTile + 2), x + TILE_OFF_X + 1, y + TILE_OFF_Y);
		VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 1, 1, blockTile + 1), x + TILE_OFF_X, y + TILE_OFF_Y + 1);
		VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 1, 1, blockTile), x + TILE_OFF_X + 1, y + TILE_OFF_Y + 1);
	} else if(blockFlipH){
		VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 1, blockTile + 1), x + TILE_OFF_X, y + TILE_OFF_Y);
		VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 1, blockTile), x + TILE_OFF_X + 1, y + TILE_OFF_Y);
		VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 1, blockTile + 3), x + TILE_OFF_X, y + TILE_OFF_Y + 1);
		VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 1, blockTile + 2), x + TILE_OFF_X + 1, y + TILE_OFF_Y + 1);
	} else if(blockFlipV){
		VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 1, 0, blockTile + 2), x + TILE_OFF_X, y + TILE_OFF_Y);
		VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 1, 0, blockTile + 3), x + TILE_OFF_X + 1, y + TILE_OFF_Y);
		VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 1, 0, blockTile), x + TILE_OFF_X, y + TILE_OFF_Y + 1);
		VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 1, 0, blockTile + 1), x + TILE_OFF_X + 1, y + TILE_OFF_Y + 1);
	} else {
		VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, blockTile), x + TILE_OFF_X, y + TILE_OFF_Y);
		VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, blockTile + 1), x + TILE_OFF_X + 1, y + TILE_OFF_Y);
		VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, blockTile + 2), x + TILE_OFF_X, y + TILE_OFF_Y + 1);
		VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, blockTile + 3), x + TILE_OFF_X + 1, y + TILE_OFF_Y + 1);
	}
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
	// for(s16 i = 0; i < 4; i++) spawnBlock(i < 2 ? 0 : ROOM_W - 2, i % 2 == 0 ? ROOM_H - 2 : 0, 3, TRUE, FALSE, FALSE);
	for(s16 y = 0; y < ROOM_H; y++) for(s16 x = 0; x < ROOM_W; x++){
		if(x % 2 == 0 && y % 2 == 0 && x < ROOM_W){
			if(x == 0 && (!opens.x || (opens.x && (y == DOOR_Y_START || y == DOOR_Y_END))) && y > 0 && y < ROOM_H - 2)
				spawnBlock(x, y, 2, FALSE, FALSE, FALSE);
			else if(x == ROOM_W - 2 && (!opens.w || (opens.w && (y <= DOOR_Y_START || y >= DOOR_Y_END))) && y > 0 && y < ROOM_H - 2)
				spawnBlock(x, y, 2, FALSE, TRUE, FALSE);
			else if(y == 0 && (!opens.y || (opens.y && (x == DOOR_X_START || x == DOOR_X_END))) && x > 0 && x < ROOM_W - 2)
				spawnBlock(x, y, 1, TRUE, FALSE, TRUE);
			else if(y == ROOM_H - 2 && (!opens.z || (opens.z && (x == DOOR_X_START || x == DOOR_X_END))) && x > 0 && x < ROOM_W - 2)
				spawnBlock(x, y, 1, TRUE, FALSE, FALSE);
		}
	}
	if(!opens.x && !opens.y) spawnBlock(0, 0, 3, TRUE, FALSE, TRUE);
	if(!opens.w && !opens.y) spawnBlock(ROOM_W - 2, 0, 3, TRUE, TRUE, TRUE);
	if(!opens.x && !opens.z) spawnBlock(0, ROOM_H - 2, 3, FALSE, FALSE, FALSE);
	if(!opens.w && !opens.z) spawnBlock(ROOM_W - 2, ROOM_H - 2, 3, FALSE, TRUE, FALSE);
}

void loadRoomTiles(){
	for(s16 y = 0; y < BLOCK_HEIGHT; y++) for(s16 x = 0; x < BLOCK_WIDTH; x++){
		if(roomLayout[y][x] > 0){
			needBlockCancel = FALSE;
			if(roomLayout[y][x] < 20){
				if(y > 0 && roomLayout[y - 1][x] > 0 && y < BLOCK_WIDTH - 1 && roomLayout[y + 1][x] > 0 &&
					x > 0 && roomLayout[y][x - 1] > 0 && x < BLOCK_HEIGHT - 1 && roomLayout[y][x + 1] > 0) needBlockCancel = TRUE;
				spawnBlock((x + 1) * 2, (y + 1) * 2, roomLayout[y][x], needBlockCancel, FALSE, FALSE);
			} else {
				roomEnemyX = (x + 1) * 2 * 8 + 8;
				roomEnemyY = (y + 1) * 2 * 8 + 8;
				switch(roomLayout[y][x]){
					case 20:
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
	loadRoomBorder(FALSE, FALSE, FALSE, FALSE);
	// 10
	s16 tempLayout[BLOCK_HEIGHT][BLOCK_WIDTH] = {
		{00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
		{00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
		{00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
		{00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 10, 00, 00, 00},
		{00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 12, 00, 00, 00},
		{00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 12, 00, 00, 00},
		{00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 12, 00, 00, 00},
		{00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 12, 00, 00, 00},
		{00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 12, 00, 00, 00},
		{00, 00, 00, 15, 13, 13, 14, 00, 00, 00, 11, 00, 00, 00},
		{00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
		{00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
	};
	memcpy(roomLayout, tempLayout, sizeof(roomLayout));
	loadRoomTiles();
	MEM_free(tempLayout);
	leftRoom = a2;
	rightRoom = a2;
}

void a2(){ // fish and worm
	loadRoomBorder(TRUE, TRUE, FALSE, FALSE);
	s16 tempLayout[BLOCK_HEIGHT][BLOCK_WIDTH] = {
		{00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
		{00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
		{00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
		{00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
		{00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
		{00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
		{00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
		{00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
		{00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
		{00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
		{00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
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
	loadOverlay();
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
		VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, LEAST_TILE), x + TILE_OFF_X, y + TILE_OFF_Y);
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
	loadBlocks();
	currentRoomType = 1;
	loadTiles();
}

void updateRoom(){
	updateBlocks();
}