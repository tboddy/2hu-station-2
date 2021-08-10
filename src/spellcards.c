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
			.speed = FIX16(12),
			.type = spellInts[0] + 1,
			.player = TRUE
		};
		spawnBullet(bSpawn, eUpdate, eSuicide);
		spellInts[0] = spellInts[0] == 0 ? 6 : (spellInts[0] == 6 ? 10 : 0);
	}
}


////////////////////////////
// BEGIN CHIMATA'S SPELLS //
////////////////////////////

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

// free market
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
			.speed = FIX16(6),
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

// bullet dominion
void bulletDominion(){
	shotInterval = 60;
	if(shotClock == 0){
		spellInts[0] = shotAngle;
		spellInts[1] = 1;
		spellVectors[0].x = pPos.x;
		spellVectors[0].y = bSpawnY;
		shooting = TRUE;
	}
	if(shotClock % 15 == 0 && shotClock % shotInterval <= 30 && shooting){
		struct bulletSpawner bSpawn = {
			.pX = spellVectors[0].x,
			.pY = spellVectors[0].y,
			.angle = spellInts[0],
			.type = (shotClock == 15 ? 1 : 0) + spellInts[1],
			.player = TRUE
		};
		bSpawn.fixes[0] = FIX16(1);
		bSpawn.bools[0] = bSpawn.type == 1 ? TRUE : FALSE;
		spellInts[1] += 2;
		void bUpdate(s16 i){
			if(bullets[i].clock % 2 == 0 && bullets[i].clock > 0 && bullets[i].clock < 30){
				bullets[i].speed = fix16Sub(bullets[i].speed, bullets[i].fixes[0]);
				bullets[i].angle += bullets[i].bools[0] ? 64 : -64;
				updateVelocity(i, 1);
			}
		}
		for(s16 i = 0; i < 10; i++){
			bSpawn.speed = FIX16(i % 2 == 0 ? 6 : 4);
			spawnBullet(bSpawn, bUpdate, eSuicide);
			bSpawn.angle += 102;
		}
	} else if(shooting && shotClock % shotInterval >= 30) shooting = FALSE;
}

// asylum of danmaku
void asylum(){
	shotInterval = 90;
	if(shotClock == 0){
		spellInts[0] = shotAngle;
		spellInts[1] = 4;
		spellVectors[0].x = pPos.x;
		spellVectors[0].y = bSpawnY;
		shooting = TRUE;
		spellFixes[0] = FIX16(3);
		spellFixes[1] = FIX16(1.5);
		spellFixes[2] = FIX16(0.5);
	}
	if(shotClock % 3 == 0 && shotClock % shotInterval < 9 && shooting){
		struct bulletSpawner bSpawn = {
			.pX = spellVectors[0].x,
			.pY = spellVectors[0].y,
			.angle = spellInts[0],
			.type = spellInts[1],
			.speed = spellFixes[0],
			.player = TRUE
		};
		bSpawn.bools[0] = shotClock % 6 == 3;
		void bUpdate(s16 i){
			if(bullets[i].clock % 10 == 0 && bullets[i].clock > 0 && bullets[i].clock < 60){
				bullets[i].angle += bullets[i].bools[0] ? -40 : 40;
				updateVelocity(i, 1);
			}
		}
		for(s16 i = 0; i < 9; i++){
			spawnBullet(bSpawn, bUpdate, eSuicide);
			bSpawn.angle += 114;
		}
		spellFixes[0] = fix16Add(spellFixes[0], spellFixes[1]);
		if(spellInts[1] == 10) spellFixes[0] = fix16Add(spellFixes[0], spellFixes[2]);
		spellInts[1] = spellInts[1] == 4 ? 10 : 6;
	} else if(shotClock % 3 == 1 && shooting && shotClock % shotInterval < 30){
		struct bulletSpawner bSpawn = {
			.pX = spellVectors[0].x,
			.pY = spellVectors[0].y,
			.angle = spellInts[0] - 48 + random() % 96,
			.type = 1,
			.speed = FIX16(random() % 2 < 1 ? 5 : 4),
			.player = TRUE
		};
		spawnBullet(bSpawn, eUpdate, eSuicide);
	}
	else if(shooting && shotClock % shotInterval >= 30) shooting = FALSE;
}

//////////////////////////
// END CHIMATA'S SPELLS //
//////////////////////////


///////////////////////////
// BEGIN MOMOYO'S SPELLS //
///////////////////////////

// cannibalistic insect
void cannibalistic(){
	shotInterval = 60;
	if(shotClock == 0){
		spellInts[0] = shotAngle;
		spellVectors[0].x = pPos.x;
		spellVectors[0].y = bSpawnY;
		shooting = TRUE;
	}
	if(shotClock % 10 == 0 && shotClock % shotInterval < 30 && shooting){
		struct bulletSpawner bSpawn = {
			.pX = spellVectors[0].x,
			.pY = spellVectors[0].y,
			.angle = spellInts[0],
			.type = 2,
			.speed = FIX16(6),
			.player = TRUE
		};
		void bUpdate(s16 i){
			if(bullets[i].clock % 2 == 0){
				if(bullets[i].clock > 0 && bullets[i].clock < 16){
					bullets[i].angle += 112;
					updateVelocity(i, 1);
				} else if(bullets[i].clock >= 24 && bullets[i].clock < 32){
					bullets[i].angle -= 64;
					updateVelocity(i, 1);
				} else if(bullets[i].clock % 4 == 0){
					bullets[i].angle -= 24;
					updateVelocity(i, 1);
				}
			}
		}
		for(s16 i = 0; i < 8; i++){
			spawnBullet(bSpawn, bUpdate, eSuicide);
			bSpawn.angle += 128;
		}
	} else if(shooting && shotClock % shotInterval >= 30) shooting = FALSE;
}

// cave swarmer
void caveSwarmer(){
	shotInterval = 60;
	if(shotClock == 0){
		shooting = TRUE;
		spellInts[0] = shotAngle;
		spellBools[0] = !spellBools[0];
	}
	if(shotClock % 2 == 0 && shotClock % shotInterval < 40 && shooting){
		struct bulletSpawner bSpawn = {
			.pX = pPos.x,
			.pY = bSpawnY,
			.angle = spellInts[0] - 96 + random() % 192,
			.type = spellBools[0] ? 5 : 9,
			.speed = FIX16(random() % 2 < 1 ? 2 : 3),
			.player = TRUE
		};
		spawnBullet(bSpawn, eUpdate, eSuicide);
	} else if(shooting && shotClock % shotInterval >= 40) shooting = FALSE;
}

// sky pendra
void skyPendra(){
	shotInterval = 120;
	if(shotClock == 0){
		shooting = TRUE;
		spellFixes[0] = FIX16(52 - 16 + random() % 32);
		spellFixes[1] = FIX16(102 - 16 + random() % 32);
		spellFixes[2] = FIX16(154 - 16 + random() % 32);
		spellFixes[3] = FIX16(206 - 16 + random() % 32);
		spellInts[0] = shotAngle;
	}
	if(shotClock % 10 == 0 && shotClock % shotInterval < 60 && shooting){
		struct bulletSpawner bSpawn = {
			.pY = FIX16(16),
			.angle = 256 + 64,
			.type = 1,
			.speed = FIX16(2.5),
			.player = TRUE
		};
		bSpawn.ints[0] = 128;
		bSpawn.ints[1] = -128;
		void bUpdate(s16 i){
			if(bullets[i].clock % 10 == 0 && bullets[i].clock > 0){
				bullets[i].angle += bullets[i].bools[0] ? bullets[i].ints[0] : bullets[i].ints[1];
				bullets[i].bools[0] = !bullets[i].bools[0];
				updateVelocity(i, 1);
			}
		}
		for(s16 i = 0; i < 4; i++){
			bSpawn.pX = spellFixes[i];
			spawnBullet(bSpawn, bUpdate, eSuicide);
		}
	} else if(shotClock % 5 == 1 && shotClock % shotInterval < 25 && shooting){
		struct bulletSpawner bSpawn = {
			.pX = pPos.x,
			.pY = bSpawnY,
			.angle = spellInts[0] - 80 + random() % 40,
			.type = 10,
			.speed = FIX16(random() % 2 < 1 ? 2.5 : 3),
			.player = TRUE
		};
		spawnBullet(bSpawn, eUpdate, eSuicide);
	} else if(shooting && shotClock % shotInterval >= 60) shooting = FALSE;
}

// ever-accumulating mine dump
void mineDump(){
	shotInterval = 120;
	if(shotClock == 0){
		shooting = TRUE;
	}
	if(shotClock % 5 == 0 && shotClock % shotInterval < 115 && shooting){
		struct bulletSpawner bSpawn = {
			.pY = FIX16(16),
			.pX = FIX16(24 + random() % 208),
			.angle = 256,
			.type = 3,
			.speed = FIX16(2),
			.player = TRUE
		};
		void bUpdate(s16 i){
			if(bullets[i].clock % 5 == 0 && bullets[i].clock > 0){
				switch(bullets[i].clock){
					case 5: bullets[i].speed = FIX16(3); break;
					case 10: bullets[i].speed = FIX16(3.5); break;
					case 20: bullets[i].speed = FIX16(3); break;
					case 25: bullets[i].speed = FIX16(2); break;
					case 30:
						bullets[i].angle = 128 + random() % 256;
						break;
				}
				updateVelocity(i, 1);
			}
		}
		spawnBullet(bSpawn, bUpdate, eSuicide);
	} else if(shooting && shotClock % shotInterval >= 115) shooting = FALSE;
}

// snake eater
void snakeEater(){
	shotInterval = 120;
	if(shotClock == 0){
		shooting = TRUE;
		spellFixes[0] = FIX16(24 + random() % 208);
		spellBools[0] = !spellBools[0];
	}
	if(shotClock % 30 == 0 && shotClock % shotInterval < 90 && shooting){
		struct bulletSpawner bSpawn = {
			.pY = FIX16(16),
			.pX = FIX16(24 + random() % 208),
			.angle = 0,
			.type = 9,
			.speed = FIX16(5),
			.player = TRUE
		};
		for(s16 i = 0; i < 16; i++){
			if(bSpawn.angle < 512 && bSpawn.angle > 0) spawnBullet(bSpawn, eUpdate, eSuicide);
			bSpawn.angle += 64;
		}
	} else if(shotClock % 10 == 5 && shotClock % shotInterval < 90 && shooting){
		if(shotClock % 40 == 5) spellVectors[1] = pPos;
		struct bulletSpawner bSpawn = {
			.pY = FIX16(16),
			.pX = spellFixes[0],
			.type = spellBools[0] ? 2 : 8,
			.player = TRUE
		};
		spellVectors[0].x = bSpawn.pX;
		spellVectors[0].y = bSpawn.pY;
		bSpawn.vel = hone(spellVectors[0], spellVectors[1], FIX16(3.5), 48);
		spawnBullet(bSpawn, eUpdate, eSuicide);
	} else if(shooting && shotClock % shotInterval > 90) shooting = FALSE;
}

/////////////////////////
// END MOMOYO'S SPELLS //
/////////////////////////






// main loop

void loadSpellcards(){
	shotAngle = 0;
	shotClock = 600;
}

void updateSpellcards(){
	if(shotClock >= shotInterval && controls.a) shotClock = 0;
	// bSpawnY = fix16Sub(pPos.y, B_SPAWN_MOD);
	bSpawnY = pPos.y;

	defaultShot();
	
	shotClock++;
	if(shotClock >= 600) shotClock = shotInterval;
}