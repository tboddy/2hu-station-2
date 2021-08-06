#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "player.h"
#include "chrome.h"


// frame

void loadFrame(){
	VDP_loadTileSet(frame1.tileset, FRAME_TILE_1, DMA);
	VDP_loadTileSet(frame2.tileset, FRAME_TILE_2, DMA);
	VDP_loadTileSet(frame3.tileset, FRAME_TILE_3, DMA);
	VDP_loadTileSet(frame4.tileset, FRAME_TILE_4, DMA);

	for(s16 y = 0; y < FRAME_HEIGHT; y++) for(s16 x = 0; x < FRAME_WIDTH; x++){
		if(y < FRAME_OFF_Y || y > FRAME_OFF_Z){
			frameTile = y == FRAME_OFF_Y - 1 || y == FRAME_OFF_Z + 1 ? FRAME_TILE_3 : FRAME_TILE_1;
			frameV = y == FRAME_OFF_Y - 1 ? 1 : 0;
			VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 1, frameV, 0, frameTile), x, y);
		}
	}
	// 	if(y < FRAME_OFF_Y || y > FRAME_OFF_Z || x == FRAME_OFF_X || x == FRAME_OFF_W){
	// 		frameTile = FRAME_TILE_1;
	// 		frameV = 0;
	// 		frameH = 0;
	// 		if(y >= FRAME_OFF_Y && y <= FRAME_OFF_Z){
	// 			frameTile = FRAME_TILE_2;
	// 			if(x == FRAME_OFF_X) frameH = 1;
	// 		} else if(y == FRAME_OFF_Y - 1 || y == FRAME_OFF_Z + 1){
	// 			frameTile = FRAME_TILE_3;
	// 			if(x == FRAME_OFF_X || x == FRAME_OFF_W) frameTile = FRAME_TILE_4;
	// 			if(y == FRAME_OFF_Y - 1) frameV = 1;
	// 			if(x == FRAME_OFF_W) frameH = 1;
	// 		}
	// 		VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 1, frameV, frameH, frameTile), x, y);
	// 	}
	// }
}


// hud

void loadScore(){
	VDP_drawText("SCORE 00070350", SCORE_X, SCORE_Y);
}

void updateLives(){
	if(chromeLives != currentLives){
		for(s16 x = 0; x < currentLives; x++) VDP_drawText("#", LIVES_X - x, LIVES_Y);
		chromeLives = currentLives;
	}
}


// export

void loadChrome(){
	loadFrame();
	loadScore();
}

void updateChrome(){
	updateLives();
}


