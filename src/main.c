#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "controls.h"
#include "background.h"
#include "explosion.h"
#include "room.h"
#include "bullets.h"
#include "player.h"
#include "enemies.h"
#include "chrome.h"


// helpers

fix16 getDistance(Vect2D_f16 a, Vect2D_f16 b){
	return fix32ToFix16(getApproximatedDistance(fix32Sub(fix16ToFix32(a.x), fix16ToFix32(b.x)), fix32Sub(fix16ToFix32(a.y), fix16ToFix32(b.y))));
}

u16 sAttr(){ return TILE_ATTR(PAL1, 0, FALSE, FALSE); }
void eUpdate(s16 i){ if(i){} }
void eSuicide(s16 i){ if(i){} }

void updateVelocity(s16 i, s16 type){
	switch(type){
		case 1:
			bullets[i].vel.x = fix16Mul(cosFix16(bullets[i].angle), bullets[i].speed);
			bullets[i].vel.y = fix16Mul(sinFix16(bullets[i].angle), bullets[i].speed);
			break;
		case 2:
			enemies[i].vel.x = fix16Mul(cosFix16(enemies[i].angle), enemies[i].speed);
			enemies[i].vel.y = fix16Mul(sinFix16(enemies[i].angle), enemies[i].speed);
			break;
	}
}

Vect2D_f16 hone(Vect2D_f16 pos, Vect2D_f16 target, fix16 speed, s16 lerp){
	hPos.x = target.x;
	hPos.y = target.y;
	if(lerp > 0){
		hPos.x = fix16Add(fix16Sub(hPos.x, FIX16(lerp)), FIX16(random() % (lerp * 2)));
		hPos.y = fix16Add(fix16Sub(hPos.y, FIX16(lerp)), FIX16(random() % (lerp * 2)));
	}
	honeSpeed = fix32ToFix16(getApproximatedDistance(
		fix32Sub(fix16ToFix32(pos.x), fix16ToFix32(hPos.x)),
		fix32Sub(fix16ToFix32(pos.y), fix16ToFix32(hPos.y))));
	hPos.x = fix16Mul(fix16Div(fix16Sub(hPos.x, pos.x), honeSpeed), speed);
	hPos.y = fix16Mul(fix16Div(fix16Sub(hPos.y, pos.y), honeSpeed), speed);
	return hPos;
}


// game

void loadGame(){
	loadBackground();
	loadRoom();
	loadPlayer();
	loadChrome();
}

void updateGame(){
	updateBackground();
	updatePlayer();
	updateRoom();
	updateBullets();
	updateEnemies();
	updateExplosions();
	updateChrome();
	drawPlayer();
	gameClock++;
	if(gameClock >= 1800) gameClock = 120;
}


// main

void loadResources(){
	VDP_loadFont(font.tileset, DMA);
	VDP_setPalette(PAL1, font.palette -> data);
	VDP_setPalette(PAL2, chimata.palette -> data);
	VDP_setTextPalette(1);
	VDP_loadTileSet(least.tileset, LEAST_TILE, DMA);
	VDP_loadTileSet(half.tileset, HALF_TILE, DMA);
	VDP_loadTileSet(most.tileset, MOST_TILE, DMA);
}

int main() {
	VDP_setScreenWidth256();
	JOY_init();
	JOY_setEventHandler(&updateControls);
	loadResources();
	SPR_init(0, 0, 0);
	loadGame();
	while(1){
		updateGame();
		SPR_update();
		SYS_doVBlankProcess();
	}
	return (0);
}