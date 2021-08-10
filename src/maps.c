#include <genesis.h>

#include "main.h"
#include "maps.h"
#include "room.h"


// zone a

void a1(){
	loadRoomBorder(FALSE, TRUE, FALSE, FALSE);
	s16 tempLayout[BLOCK_HEIGHT][BLOCK_WIDTH] = {
		{19,19,  5,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  6, 19},
		{19, 5, 12,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 11,  6},
		{5, 12,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 11},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{7, 10,  0,  0,  0, 16, 13, 13, 13, 13, 17,  0,  0,  0,  0,  0},
		{19, 7, 14, 13, 15,  8, 19, 19, 19, 19,  7, 14, 13, 13, 15,  2},
	};
	memcpy(roomLayout, tempLayout, sizeof(roomLayout));
	loadRoomTiles();
	MEM_free(tempLayout);
	rightRoom = a2;
}

void a2(){
	loadRoomBorder(TRUE, TRUE, FALSE, FALSE);
	s16 tempLayout[BLOCK_HEIGHT][BLOCK_WIDTH] = {
		{5,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{12, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
	};
	memcpy(roomLayout, tempLayout, sizeof(roomLayout));
	loadRoomTiles();
	MEM_free(tempLayout);
	leftRoom = a1;
	rightRoom = a3;
}

void a3(){
	loadRoomBorder(TRUE, TRUE, FALSE, FALSE);
	s16 tempLayout[BLOCK_HEIGHT][BLOCK_WIDTH] = {
		{1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  6},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 11},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  9,  2,  2,  2},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4, 19, 19, 19},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  9,  2,  2,  8, 19, 19, 19},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  4, 19, 19, 19, 19, 19, 19},
		{2,  2,  2,  2,  2,  2,  2,  2,  2,  8, 19, 19, 19, 19, 19, 19},
	};
	leftRoom = a2;
	rightRoom = a4;
	memcpy(roomLayout, tempLayout, sizeof(roomLayout));
	loadRoomTiles();
	MEM_free(tempLayout);
}

void a4(){
	loadRoomBorder(TRUE, TRUE, FALSE, TRUE);
	s16 tempLayout[BLOCK_HEIGHT][BLOCK_WIDTH] = {
		{5,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  6},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4},
		{12, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 11},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{2,  2,  2,  2, 10,  0,  0,  0,  0,  0,  0,  9,  2,  2,  2,  2},
		{19, 19, 19, 19, 3, 25, 25, 25, 25, 25, 25,  4, 19, 19, 19, 19},
		{19, 19, 19, 19, 3,  0,  0,  0,  0,  0,  0,  4, 19, 19, 19, 19},
		{19, 19, 19, 19, 3,  0,  0,  0,  0,  0,  0,  4, 19, 19, 19, 19},
		{19, 19, 19, 19, 3,  0,  0,  0,  0,  0,  0,  4, 19, 19, 19, 19},
	};
	leftRoom = a3;
	rightRoom = a5;
	bottomRoom = a1;
	memcpy(roomLayout, tempLayout, sizeof(roomLayout));
	loadRoomTiles();
	MEM_free(tempLayout);
}

void a5(){
	loadRoomBorder(TRUE, TRUE, FALSE, FALSE);
	s16 tempLayout[BLOCK_HEIGHT][BLOCK_WIDTH] = {
		{5,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{12, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{2,  2,  2,  2, 10,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{19,19, 19, 19,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{19,19, 19, 19,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{19,19, 19, 19,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{19,19, 19, 19,  7,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
	};
	memcpy(roomLayout, tempLayout, sizeof(roomLayout));
	loadRoomTiles();
	MEM_free(tempLayout);
	leftRoom = a4;
	rightRoom = a6;
}

void a6(){
	loadRoomBorder(TRUE, FALSE, TRUE, FALSE);
	s16 tempLayout[BLOCK_HEIGHT][BLOCK_WIDTH] = {
		{1,  1,  1,  1,  1, 12,  0,  0,  0, 30,  0,  0, 4, 19, 19, 19},
		{0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0, 11,  1,  6, 19},
		{0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  4, 19},
		{0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  4, 19},
		{0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  4, 19},
		{0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  4, 19},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4, 19},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  9,  2,  8, 19},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4, 19, 19, 19},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4, 19, 19, 19},
		{0,  0,  0,  0,  0,  0,  0,  9,  2,  2,  2,  2,  8, 19, 19, 19},
		{0,  0,  0,  0,  0,  0,  0,  4, 19, 19, 19, 19, 19, 19, 19, 19},
		{2,  2,  2,  2,  2,  2,  2,  8, 19, 19, 19, 19, 19, 19, 19, 19},
	};
	memcpy(roomLayout, tempLayout, sizeof(roomLayout));
	loadRoomTiles();
	MEM_free(tempLayout);
	leftRoom = a5;
	topRoom = a7;
}

void a7(){
	loadRoomBorder(FALSE, FALSE, TRUE, TRUE);
	s16 tempLayout[BLOCK_HEIGHT][BLOCK_WIDTH] = {
		{5,  1,  1,  1, 12,  0,  0,  0,  0, 30,  0,  0, 11,  1,  1,  6},
		{3,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  0,  4},
		{3,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  0,  4},
		{3,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  0,  4},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4},
		{7,  2,  2,  2,  2,  2,  2,  2, 10, 30,  0,  0,  0,  0,  0,  4},
		{19,19, 19, 19, 19,  5,  1,  1, 12, 30,  0,  0,  0,  0,  0,  4},
		{19,19, 19, 19, 19,  3,  0,  0,  0, 30,  0,  0,  0,  0,  0,  4},
		{19,19, 19, 19, 19,  3,  0,  0,  0, 30,  0,  0,  9,  2,  2,  8},
		{19,19, 19, 19, 19,  3,  0,  0,  0, 30,  0,  0,  4, 19, 19, 19},
	};
	memcpy(roomLayout, tempLayout, sizeof(roomLayout));
	loadRoomTiles();
	MEM_free(tempLayout);
	bottomRoom = a6;
	topRoom = a8;
}

void a8(){
	loadRoomBorder(FALSE, FALSE, TRUE, TRUE);
	s16 tempLayout[BLOCK_HEIGHT][BLOCK_WIDTH] = {
		{5,  1,  1,  1, 12,  0,  0,  0,  0,  0, 30,  0, 11,  1,  1,  6},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  4},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  4},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  4},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  4},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  4},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  4},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  4},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  4},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  4},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  4},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  4},
		{7,  2,  2,  2, 10,  0,  0,  0,  0,  0, 30,  0,  9,  2,  2,  8},
	};
	memcpy(roomLayout, tempLayout, sizeof(roomLayout));
	loadRoomTiles();
	MEM_free(tempLayout);
	bottomRoom = a7;
	topRoom = a9;
}

void a9(){

	loadRoomBorder(FALSE, TRUE, TRUE, TRUE);
	s16 tempLayout[BLOCK_HEIGHT][BLOCK_WIDTH] = {
		{5,  1,  1,  1, 12,  0,  0,  0,  0,  0, 30,  0, 11,  1,  1,  6},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  4},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  4},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0, 11},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  0},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  0},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  0},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  0},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  0},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  9},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  4},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  4},
		{7,  2,  2,  2, 10,  0,  0,  0,  0,  0, 30,  0,  9,  2,  2,  8},
	};
	memcpy(roomLayout, tempLayout, sizeof(roomLayout));
	loadRoomTiles();
	MEM_free(tempLayout);
	bottomRoom = a8;
	topRoom = a10;
	rightRoom = a1;
}

void a10(){

	loadRoomBorder(FALSE, FALSE, TRUE, TRUE);
	s16 tempLayout[BLOCK_HEIGHT][BLOCK_WIDTH] = {
		{5,  1,  1,  1, 12,  0,  0,  0,  0,  0, 30,  0, 11,  1,  1,  6},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  4},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  4},
		{12, 0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  4},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  4},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  4},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  4},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  4},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  4},
		{10, 0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  4},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  4},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  4},
		{7,  2,  2,  2, 10,  0,  0,  0,  0,  0, 30,  0,  9,  2,  2,  8},
	};
	memcpy(roomLayout, tempLayout, sizeof(roomLayout));
	loadRoomTiles();
	MEM_free(tempLayout);
	bottomRoom = a9;
	topRoom = a11;
	// leftRoom = a12;
}

void a11(){
	loadRoomBorder(FALSE, FALSE, FALSE, TRUE);
	s16 tempLayout[BLOCK_HEIGHT][BLOCK_WIDTH] = {
		{5,  1,  1,  1,  1,  1,  1,  1, 49, 49,  1,  1,  1,  1,  1,  6},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4},
		{12, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  4},
		{10, 0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  4},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  4},
		{3,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  4},
		{7,  2,  2,  2, 10,  0,  0,  0,  0,  0, 30,  0,  9,  2,  2,  8},
	};
	memcpy(roomLayout, tempLayout, sizeof(roomLayout));
	loadRoomTiles();
	MEM_free(tempLayout);
	bottomRoom = a10;
	// leftRoom = a1;
}

void a12(){}
void a13(){}
void a14(){}
void a15(){}
void a16(){}
void a17(){}
void a18(){}
void a19(){}
void a20(){}


// zone b

void b1(){}
void b2(){}
void b3(){}
void b4(){}
void b5(){}
void b6(){}
void b7(){}
void b8(){}
void b9(){}
void b10(){}
void b11(){}
void b12(){}
void b13(){}
void b14(){}
void b15(){}
void b16(){}
void b17(){}
void b18(){}
void b19(){}
void b20(){}
void b21(){}
void b22(){}


// zone c

void c1(){}
void c2(){}
void c3(){}
void c4(){}
void c5(){}
void c6(){}
void c7(){}
void c8(){}
void c9(){}
void c10(){}
void c11(){}
void c12(){}
void c13(){}
void c14(){}
void c15(){}
void c16(){}
void c17(){}
void c18(){}
void c19(){}
void c20(){}
void c21(){}
void c22(){}
void c23(){}
void c24(){}
void c25(){}


// zone d

void d1(){}
void d2(){}
void d3(){}
void d4(){}
void d5(){}
void d6(){}
void d7(){}
void d8(){}
void d9(){}
void d10(){}





/*

{5,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  6},
{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4},
{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4},
{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4},
{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4},
{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4},
{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4},
{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4},
{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4},
{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4},
{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4},
{3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4},
{7,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  8},

*/