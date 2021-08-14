#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "player.h"
#include "enemies.h"
#include "bullets.h"


// weak 

void weak1(s16 x, s16 y){ // hones

	struct enemySpawner spawner = {
		.x = FIX16(x),
		.y = FIX16(y),
		.type = 1,
		.health = 10
	};
	spawner.fixes[1] = FIX16(GAME_H / 2 + 8);
	spawner.ints[0] = 60;
	spawner.ints[1] = random() % spawner.ints[0];
	spawner.vectors[0].x = FIX16(GAME_W / 2);
	spawner.vectors[0].y = FIX16(GAME_H / 2);

	void movement(s16 i){
		if(enemies[i].clock % 60 == 0){
			if(enemies[i].clock % 120 == 0){
				enemies[i].vel = hone(enemies[i].pos, pPos, FIX16(0.5), 32);
			} else {
				enemies[i].speed = FIX16(0.5);
				enemies[i].angle = enemies[i].pos.x > enemies[i].vectors[0].x ?
					(enemies[i].pos.y > enemies[i].vectors[0].y ? 640 : 384) : (enemies[i].pos.y > enemies[i].vectors[0].y ? 896 : 128);
				enemies[i].angle = enemies[i].angle - 128 + random() % 256;
				updateVelocity(i, 2);
			}
			SPR_setHFlip(enemies[i].image, pPos.x > enemies[i].pos.x ? 1 : 0);
		}
	}

	void patternOne(s16 i){
		if(enemies[i].clock % enemies[i].ints[0] == enemies[i].ints[1]){
			struct bulletSpawner bSpawn = {
				.pX = enemies[i].pos.x,
				.pY = enemies[i].pos.y,
				.type = 3
			};
			bSpawn.vectors[0].x = bSpawn.pX;
			bSpawn.vectors[0].y = bSpawn.pY;
			bSpawn.vel = hone(bSpawn.vectors[0], pPos, FIX16(1.5), 0);
			spawnBullet(bSpawn, eUpdate, eSuicide);
		}
	}

	void updater(s16 i){
		movement(i);
		patternOne(i);
	}
	spawnEnemy(spawner, updater);
}

void weak2(s16 x, s16 y){ // turret

	struct enemySpawner spawner = {
		.x = FIX16(x),
		.y = FIX16(y),
		.type = 2,
		.health = 10
	};
	spawner.ints[0] = 60;
	spawner.ints[1] = random() % spawner.ints[0];

	void updater(s16 i){
		if(enemies[i].clock % enemies[i].ints[0] == enemies[i].ints[1]){
			struct bulletSpawner bSpawn = {
				.pX = enemies[i].pos.x,
				.pY = enemies[i].pos.y,
				.type = 1,
				.speed = FIX16(2.5),
				.angle = random() % 1024
			};
			for(s16 j = 0; j < 5; j++){
				spawnBullet(bSpawn, eUpdate, eSuicide);
				bSpawn.angle += 205;
			}
		}
	}

	spawnEnemy(spawner, updater);

}