// explosions

#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "explosion.h"


// spawn

void spawnExplosion(Vect2D_f16 pos, bool type){
	s16 i = -1;
	for(s16 h = 0; h < EXP_COUNT; h++) if(!explosions[h].active && i == -1) i = h;
	if(i > -1){
		explosions[i].active = TRUE;
		explosions[i].clock = 0;
		expImg = type == 1 ? &explosion2 : &explosion;
		explosions[i].image = SPR_addSprite(expImg, fix16ToInt(pos.x) - EXP_OFF, fix16ToInt(pos.y) + 4, sAttr());
		SPR_setDepth(explosions[i].image, 3);
	}
}


// update

void updateExplosion(s16 i){
	if(explosions[i].clock >= EXPLOSION_LIMIT || paused){
		SPR_releaseSprite(explosions[i].image);
		explosions[i].active = FALSE;
	}
	explosions[i].clock++;
}


// main loop

void updateExplosions(){
	for(s16 i = 0; i < EXP_COUNT; i++) if(explosions[i].active) updateExplosion(i);
}