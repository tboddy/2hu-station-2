// background

#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "controls.h"
#include "background.h"


// bottom

void loadBottom(){
	VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
	for(s16 y = 0; y <= 32; y++) for(s16 x = 0; x <= 32; x++){
		if(x % 4 == 0 && y % 4 == 0) VDP_drawImageEx(BG_B, &ground1, TILE_ATTR_FULL(PAL1, 0, 0, 0, 30), x, y, 0, DMA);
	}
}

void updateBottom(){
	bgPos.x = fix16Sub(fix16Sub(bgPos.x, fix16Mul(bgVel.x, BG_SPEED)), BG_SPEED_X);
	bgPos.y = fix16Add(fix16Add(bgPos.y, fix16Mul(bgVel.y, BG_SPEED)), BG_SPEED_Y);
	VDP_setHorizontalScroll(BG_B, fix16ToInt(bgPos.x));
	VDP_setVerticalScroll(BG_B, fix16ToInt(bgPos.y));
	if(bgPos.x >= BG_SIZE || bgPos.x <= BG_SIZE_NEG) bgPos.x = 0;
	if(bgPos.y >= BG_SIZE || bgPos.y <= BG_SIZE_NEG) bgPos.y = 0;
}


// ----------------------
// export
// ----------------------

void loadBackground(){
	loadBottom();
}

void updateBackground(){
	updateBottom();
}