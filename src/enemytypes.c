#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "player.h"
#include "enemies.h"
#include "bullets.h"


// ----------------------
// boss 1
// ----------------------

void spawnBoss1(s16 x, s16 y){

	struct enemySpawner spawner = {
		.x = FIX16(x),
		.y = FIX16(y),
		.type = 1
	};
	spawner.fixes[1] = FIX16(GAME_H / 2 + 8);
	spawner.fixes[2] = FIX16(GAME_H / 2 - 8);
	spawner.fixes[3] = FIX16(GAME_W - 104);
	spawner.fixes[4] = FIX16(104);

	void movement(s16 i){
		if(enemies[i].clock % 30 == 0){
			SPR_setHFlip(enemies[i].image, pPos.x > enemies[i].pos.x ? 1 : 0);
			enemies[i].vel = hone(enemies[i].pos, FIX16(0.5), 8);
			// enemies[i].vel.x = honeOnPlayer(enemies[i].pos.x, enemies[i].pos.y, FIX16(0.5), 8, TRUE);
			// enemies[i].vel.y = honeOnPlayer(enemies[i].pos.x, enemies[i].pos.y, FIX16(0.5), 8, FALSE);
		}
	}

	void patternOne(s16 i){
		if(enemies[i].clock % 30 == 14){
			struct bulletSpawner bSpawn = {
				.pX = enemies[i].pos.x,
				.pY = enemies[i].pos.y,
				.angle = random() % 1024,
				.type = 4,
				.speed = FIX16(2)
			};
			for(s16 j = 0; j < 8; j++){
				spawnBullet(bSpawn, eUpdate);
				bSpawn.angle += 128;
			}
		}
	}

	void updater(s16 i){
		movement(i);
		patternOne(i);
	}
	spawnEnemy(spawner, updater);
}