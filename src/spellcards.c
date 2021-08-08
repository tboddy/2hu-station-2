// spell cards

#include <genesis.h>

#include "main.h"
#include "controls.h"
#include "bullets.h"
#include "player.h"
#include "spellcards.h"


// default

void spawnDefaultShot(){
	struct bulletSpawner bSpawn = {
		.pX = pPos.x,
		.pY = pPos.y,
		.angle = shotAngle,
		.speed = FIX16(16),
		.type = spellInts[0] + 1,
		.player = TRUE
	};
	spawnBullet(bSpawn, eUpdate);
	spellInts[0] = spellInts[0] == 0 ? 6 : (spellInts[0] == 6 ? 10 : 0);
}

void defaultShot(){
	shotInterval = 10;
	if(shotClock == 0) spawnDefaultShot();
}


// main loop

void loadSpellcards(){
	shotAngle = 0;
	shotClock = 600;
}

void updateSpellcards(){
	if(shotClock >= shotInterval && controls.a) shotClock = 0;
	defaultShot();
	shotClock++;
	if(shotClock >= 600) shotClock = shotInterval;
}