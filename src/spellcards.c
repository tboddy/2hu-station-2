// spell cards

#include <genesis.h>

#include "main.h"
#include "controls.h"
#include "bullets.h"
#include "player.h"
#include "spellcards.h"


// default shot
void defaultShot(){
	shotInterval = 10;
	if(shotClock == 0){
		struct bulletSpawner bSpawn = {
			.pX = pPos.x,
			.pY = bSpawnY,
			.angle = shotAngle - 16 + random() % 32,
			.speed = FIX16(16),
			.type = spellInts[0] + 1,
			.player = TRUE
		};
		spawnBullet(bSpawn, eUpdate, eSuicide);
		spellInts[0] = spellInts[0] == 0 ? 6 : (spellInts[0] == 6 ? 10 : 0);
	}
}

// an offering to the ownerless
void ownerless(){
	shotInterval = 60;
	if(shotClock == 0){
		struct bulletSpawner bSpawn = {
			.pX = pPos.x,
			.pY = bSpawnY,
			.angle = shotAngle,
			.speed = FIX16(3),
			.type = spellInts[0] + 2,
			.player = TRUE
		};
		bSpawn.ints[0] = bSpawn.type;
		void bSuicide(s16 i){
			struct bulletSpawner bSpawn = {
				.pX = fix16Sub(bullets[i].pos.x, bullets[i].vel.x),
				.pY = fix16Sub(bullets[i].pos.y, bullets[i].vel.y),
				.angle = random() % 1024,
				.speed = FIX16(3),
				.type = bullets[i].ints[0],
				.player = TRUE
			};
			for(s16 j = 0; j < 16; j++){
				spawnBullet(bSpawn, eUpdate, eSuicide);
				bSpawn.angle += 64;
			}
		}
		spawnBullet(bSpawn, eUpdate, bSuicide);
		spellInts[0] += 2;
		if(spellInts[0] > 8) spellInts[0] = 0;
	}
}

// danmaku hoarder's obsession
void obsession(){
	shotInterval = 60;
	if(shotClock == 0){
		spellInts[0] += 2;
		if(spellInts[0] > 8) spellInts[0] = 0;
		shooting = TRUE;
	}
	if(shotClock % 2 == 0 && shotClock % shotInterval < 30 && shooting){
		struct bulletSpawner bSpawn = {
			.pX = pPos.x,
			.pY = bSpawnY,
			.angle = shotAngle - 56 + random() % 112,
			.speed = FIX16(random() % 2 < 1 ? 2 : 3),
			.type = spellInts[0] + 1,
			.player = TRUE
		};
		void bUpdate(s16 i){
			if(bullets[i].clock == 5 || bullets[i].clock == 10){
				bullets[i].speed = fix16Add(bullets[i].speed, FIX16(2));
				updateVelocity(i, 1);
			}
		}
		spawnBullet(bSpawn, bUpdate, eSuicide);
	} else if(shooting && shotClock % shotInterval >= 30) shooting = FALSE;
}

// danmaku free market
void freeMarket(){
	shotInterval = 60;
	if(shotClock == 0){
		struct bulletSpawner bSpawn = {
			.pX = pPos.x,
			.pY = bSpawnY,
			.angle = shotAngle - 320,
			.speed = FIX16(7),
			.type = spellBools[0] ? 4 : 8,
			.player = TRUE
		};
		spellBools[0] = !spellBools[0];
		bSpawn.ints[0] = random() % 1024;
		bSpawn.fixes[0] = FIX16(80);
		bSpawn.fixes[1] = FIX16(1.25);
		bSpawn.vectors[0].x = fix16Add(pPos.x, fix16Mul(cosFix16(shotAngle), bSpawn.fixes[0]));
		bSpawn.vectors[0].y = fix16Add(pPos.y, fix16Mul(sinFix16(shotAngle), bSpawn.fixes[0]));
		void bUpdate(s16 i){
			if(!bullets[i].bools[0] && bullets[i].clock % 2 == 1){
				bullets[i].speed = fix16Sub(bullets[i].speed, bullets[i].fixes[1]);
				if(bullets[i].speed < 0){
					bullets[i].vel = hone(bullets[i].pos, bullets[i].vectors[0], FIX16(3), 0);
					bullets[i].bools[0] = TRUE;
				} else updateVelocity(i, 1);
			}
		}
		for(s16 i = 0; i < 11; i++){
			spawnBullet(bSpawn, bUpdate, eSuicide);
			bSpawn.angle += 64;
		}
	}
}

// rainbow ring of people
void rainbowRing(){
	shotInterval = 60;
	if(shotClock == 0){
		spellInts[0] = shotAngle;
		spellInts[1] = spellInts[0] + 512;
		spellVectors[0].x = pPos.x;
		spellVectors[0].y = bSpawnY;
		shooting = TRUE;
	}
	if(shotClock % 8 == 0 && shotClock % shotInterval < 30 && shooting){
		struct bulletSpawner bSpawn = {
			.pX = spellVectors[0].x,
			.pY = spellVectors[0].y,
			.speed = FIX16(7),
			.ints[0] = spellInts[0],
			.ints[1] = spellInts[1],
			.type = 1,
			.player = TRUE
		};
		for(s16 i = 0; i < 5; i++){
			bSpawn.angle = bSpawn.ints[0];
			spawnBullet(bSpawn, eUpdate, eSuicide);
			bSpawn.angle = bSpawn.ints[1];
			bSpawn.type++;
			spawnBullet(bSpawn, eUpdate, eSuicide);
			bSpawn.type++;
			bSpawn.ints[0] += 205;
			bSpawn.ints[1] += 205;
		}
		spellInts[0] += 32;
		spellInts[1] -= 64;
	} else if(shooting && shotClock % shotInterval >= 30) shooting = FALSE;
}


// main loop

void loadSpellcards(){
	shotAngle = 0;
	shotClock = 600;
}

void updateSpellcards(){
	if(shotClock >= shotInterval && controls.a) shotClock = 0;
	bSpawnY = fix16Sub(pPos.y, B_SPAWN_MOD);

	rainbowRing();
	
	shotClock++;
	if(shotClock >= 600) shotClock = shotInterval;
}