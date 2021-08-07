// enemies

#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "bullets.h"
#include "enemies.h"
#include "player.h"
#include "explosion.h"
#include "room.h"


// spawn

void spawnEnemy(struct enemySpawner spawner, void(*updater)){
	s16 i = -1;
	for(s16 j = 0; j < ENEMY_COUNT; j++) if(!enemies[j].active && i == -1) i = j;
	if(i > -1){
		enemies[i].active = TRUE;
		enemies[i].pos.x = spawner.x;
		enemies[i].pos.y = spawner.y;
		enemies[i].type = spawner.type;
		for(s16 j = 0; j < COUNT_INT; j++){
			enemies[i].ints[j] = spawner.ints[j] ? spawner.ints[j] : 0;
			enemies[i].fixes[j] = spawner.fixes[j] ? spawner.fixes[j] : 0;
			enemies[i].bools[j] = spawner.bools[j] ? TRUE : FALSE;
		}
		enemies[i].speed = 0;
		enemies[i].vel.x = spawner.velocityX ? spawner.velocityX : 0;
		enemies[i].vel.y = spawner.velocityY ? spawner.velocityY : 0;
		switch(spawner.type){
			case 1:
				enemies[i].off = 12;
				enemyImg = &crescent;
				break;
		}
		enemies[i].image = SPR_addSprite(enemyImg, GAME_W, GAME_H + 64, sAttr());
		SPR_setFrame(enemies[i].image, random() % 4);
		if(spawner.hFlip) SPR_setHFlip(enemies[i].image, 1);
		if(spawner.vFlip) SPR_setVFlip(enemies[i].image, 1);
		enemies[i].clock = 0;
		enemies[i].updater = updater;
	}
}


// loop

void updateEnemy(s16 i){
	enemies[i].pos.x = fix16Add(enemies[i].pos.x, enemies[i].vel.x);
	enemies[i].pos.y = fix16Add(enemies[i].pos.y, enemies[i].vel.y);
	enemies[i].updater(i);
	enemies[i].clock++;
	if(enemies[i].clock >= 1200) enemies[i].clock = 120;
}

void drawEnemy(s16 i){
	SPR_setPosition(enemies[i].image,
		fix16ToInt(enemies[i].pos.x) - enemies[i].off + SPRITE_OFF_X,
		fix16ToInt(enemies[i].pos.y) - enemies[i].off + SPRITE_OFF_Y);
}

void clearEnemies(){
	for(s16 i = 0; i < ENEMY_COUNT; i++) if(enemies[i].active){
		enemies[i].active = FALSE;
		SPR_releaseSprite(enemies[i].image);
	}
}


// main loop

void updateEnemies(){
	for(s16 i = 0; i < ENEMY_COUNT; i++) if(enemies[i].active)
		gameClock % 2 == 0 ? updateEnemy(i) : drawEnemy(i);
}