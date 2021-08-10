// bullets

#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "bullets.h"
#include "room.h"
#include "player.h"
#include "explosion.h"


// spawn

void spawnBullet(struct bulletSpawner spawner, void(*updater), void(*suicide)){
	s16 i = -1;
	for(s16 h = 0; h < BULLET_COUNT; h++) if(!bullets[h].active && i == -1) i = h;
	if(i > -1 && !gameOver){
		bullets[i].active = TRUE;
		bullets[i].grazed = FALSE;
		bullets[i].pos.x = spawner.pX;
		bullets[i].pos.y = spawner.pY;
		bullets[i].speed = spawner.speed;
		bullets[i].angle = spawner.angle;
		bullets[i].updater = updater;
		bullets[i].suicide = suicide;
		bullets[i].clock = 0;
		bullets[i].player = spawner.player;
		for(s16 j = 0; j < COUNT_INT; j++){
			bullets[i].ints[j] = spawner.ints[j];
			bullets[i].fixes[j] = spawner.fixes[j];
			bullets[i].bools[j] = spawner.bools[j];
			bullets[i].vectors[j] = spawner.vectors[j];
		}
		if(spawner.vel.x != 0 || spawner.vel.y != 0){
			bullets[i].vel.x = spawner.vel.x;
			bullets[i].vel.y = spawner.vel.y;
		} else {
			bullets[i].vel.x = fix16Mul(cosFix16(spawner.angle), spawner.speed);
			bullets[i].vel.y = fix16Mul(sinFix16(spawner.angle), spawner.speed);
		}
		switch(spawner.type){
			case 1: bulletImg = &smallBlueBullet; break;
			case 2: bulletImg = &bigBlueBullet; break;
			case 3: bulletImg = &smallRedBullet; break;
			case 4: bulletImg = &bigRedBullet; break;
			case 5: bulletImg = &smallGreenBullet; break;
			case 6: bulletImg = &bigGreenBullet; break;
			case 7: bulletImg = &smallPinkBullet; break;
			case 8: bulletImg = &bigPinkBullet; break;
			case 9: bulletImg = &smallYellowBullet; break;
			case 10: bulletImg = &bigYellowBullet; break;
			case 11: bulletImg = &smallWhiteBullet; break;
			case 12: bulletImg = &bigWhiteBullet; break;
		}
		bullets[i].image = SPR_addSprite(bulletImg, -32, GAME_H + 32, sAttr());
		if(spawner.type % 2 == 0){
			bullets[i].off.x = FIX16(8);
			bullets[i].off.y = FIX16(8);
			SPR_setDepth(bullets[i].image, 2);
		} else if(spawner.type % 2 == 1){
			bullets[i].off.x = FIX16(4);
			bullets[i].off.y = FIX16(4);
			SPR_setDepth(bullets[i].image, 1);
		}
	}
}


// collision

void checkBulletCol(s16 i){
	bulletColDist = getApproximatedDistance(
		fix16ToFix32(pPos.x) - fix16ToFix32(bullets[i].pos.x),
		fix16ToFix32(pPos.y) - fix16ToFix32(bullets[i].pos.y));
	if(bulletColDist < fix16ToFix32(bullets[i].off.x)){
		destroyBullet(i);
		spawnExplosion(bullets[i].pos, 1);
	} else if(!bullets[i].grazed) bullets[i].grazed = TRUE;
}

void destroyBullet(s16 i){
	SPR_releaseSprite(bullets[i].image);
	bullets[i].active = FALSE;
	bullets[i].clock = 0;
}

void updateKillBullets(){
	if(killBullets){
		if(killBulletsClock % 4 == 0 && killBulletsClock < 20){
			// spawnExplosion(32 + random() % 192, 32 + random() % 128, FALSE);
		}
		killBulletsClock++;
		if(killBulletsClock >= 30){
			killBullets = FALSE;
			killBulletsClock = 0;
		}
	}
}

void clearBullets(){
	for(s16 i = 0; i < BULLET_COUNT; i++) if(bullets[i].active) destroyBullet(i);
}

void blockBulletCol(s16 i){
	for(s16 j = 0; j < BULLET_COUNT; j++) if(bullets[j].active){
		if(bullets[j].pos.x <= blocks[i].pos.w &&
			bullets[j].pos.x >= blocks[i].pos.x &&
			bullets[j].pos.y <= blocks[i].pos.z &&
			bullets[j].pos.y >= blocks[i].pos.y){
			spawnExplosion(bullets[j].pos, 1);
			destroyBullet(j);
		}
	}
}


// main loop

void updateBullet(s16 i){
	bulletCount++;
	bullets[i].pos.x = fix16Add(bullets[i].pos.x, bullets[i].vel.x);
	bullets[i].pos.y = fix16Add(bullets[i].pos.y, bullets[i].vel.y);
	bullets[i].updater(i);
	SPR_setPosition(bullets[i].image,
		fix16ToInt(fix16Sub(bullets[i].pos.x, bullets[i].off.x)) + SPRITE_OFF_X,
		fix16ToInt(fix16Sub(bullets[i].pos.y, bullets[i].off.y)) + SPRITE_OFF_Y);
	bullets[i].clock++;
	if(bullets[i].pos.x < BULLET_LIMIT_X ||
		bullets[i].pos.x > BULLET_LIMIT_W ||
		bullets[i].pos.y < BULLET_LIMIT_Y ||
		bullets[i].pos.y > BULLET_LIMIT_Z ||
		killBullets && bullets[i].clock % 2 == 0){
		spawnExplosion(bullets[i].pos, 1);
		bullets[i].suicide(i);
		destroyBullet(i);
	} else if(!bullets[i].player) checkBulletCol(i);
}

void updateBullets(){
	if(gameClock % 2 == 0){
		bulletCount = 0;
		for(s16 i = 0; i < BULLET_COUNT; i++) if(bullets[i].active) updateBullet(i);
		updateKillBullets();
	}
}