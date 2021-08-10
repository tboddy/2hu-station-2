// background

#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "controls.h"
#include "chrome.h"
// #include "room.h"
#include "background.h"


// bottom

void loadRays(){
	for(s16 y = 0; y < BG_H; y++) for(s16 x = 0; x < BG_W; x++) {
		if(y > 3){
			if(!clearingMessage || (clearingMessage && x >= messageX && x < messageX + messageW && y >= messageY && y < messageY + messageZ)){
				// thick ray
				if(x == 35 - y || x == 41 - y)
					VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, x == 41 - y ? 1 : 0, x == 41 - y ? 1 : 0, BG_RAY_3), x, y);
				else if(x >= 36 - y && x <= 40 - y) 
					VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, BG_RAY_4), x, y);
				// skinny ray
				else if(x == 33 - y || x == 32 - y)
					VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, x == 33 - y ? 1 : 0, x == 33 - y ? 1 : 0, BG_RAY_3), x, y);
			}
		}
	}
	if(clearingMessage) clearingMessage = FALSE;	
}

void loadTrees(){
	for(s16 y = 0; y <= BG_H; y++) for(s16 x = -8; x <= BG_W; x++){
		if(x % 8 == 0 && y == MOUNTAIN_LINE) VDP_drawImageEx(BG_B, &mountains, TILE_ATTR_FULL(PAL1, 0, 0, 0, BG_MOUNTAINS), x, MOUNTAIN_LINE, 0, DMA);
		if(x % 8 == 0 && y == TREE_LINE) VDP_drawImageEx(BG_B, &trees, TILE_ATTR_FULL(PAL1, 0, 0, 0, BG_TREES), x, TREE_LINE, 0, DMA);
		else if(y > TREE_LINE + 2) VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, 0, 0, BG_TREES_BOTTOM), x, y);
		else if(y < MOUNTAIN_LINE || (y >= MOUNTAIN_LINE + 2 && y < TREE_LINE)) VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, 0, 0, FULL_TILE), x, y);
	}
}

void loadBottom(){
	VDP_loadTileSet(ray3.tileset, BG_RAY_3, DMA);
	VDP_loadTileSet(ray4.tileset, BG_RAY_4, DMA);
	VDP_loadTileSet(treesBottom.tileset, BG_TREES_BOTTOM, DMA);
	loadTrees();
	VDP_setScrollingMode(HSCROLL_TILE, VSCROLL_PLANE);
}

void updateBottom(){
	if(pScroll1 != 0){
		VDP_setHorizontalScrollTile(BG_B, MOUNTAIN_LINE, bgScrollsRound, BG_SCROLL_HEIGHT, DMA);
		for(s16 i = 0; i < BG_SCROLL_HEIGHT; i++){
			if(i < 2) bgScrolls[i] = fix16Add(bgScrolls[i], pScroll1);
			else if(i > 5) bgScrolls[i] = fix16Add(bgScrolls[i], pScroll2);
			if(bgScrolls[i] >= BG_SCROLL_LIMIT || bgScrolls[i] <= BG_SCROLL_LIMIT_NEG) bgScrolls[i] = 0;
			bgScrollsRound[i] = fix16ToInt(bgScrolls[i]);
		}
	}
}


// main loop

void loadBackground(){
	loadBottom();
}

void updateBackground(){
	updateBottom();
}



	// bgPos.y = fix16Add(fix16Add(bgPos.y, fix16Mul(bgVel.y, BG_SPEED)), BG_SPEED_Y);
	// VDP_setHorizontalScroll(BG_B, fix16ToInt(bgPos.x));
	// VDP_setVerticalScroll(BG_B, fix16ToInt(bgPos.y));
	// if(bgPos.y >= BG_SIZE || bgPos.y <= BG_SIZE_NEG) bgPos.y = 0;