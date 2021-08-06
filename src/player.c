#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "controls.h"
#include "background.h"
#include "bullets.h"
#include "enemies.h"
#include "explosion.h"
#include "player.h"
#include "room.h"


// shooting

void spawnPlayerBullet(){
	struct bulletSpawner bSpawn = {
		.pX = pPos.x,
		.pY = pPos.y,
		.angle = shotAngle - 64,
		.player = TRUE,
		.type = 5,
		.speed = FIX16(16)
	};
	for(s16 i = 0; i < 3; i++){
		spawnBullet(bSpawn, eUpdate);
		bSpawn.angle += 64;
	}
}

void loadShot(){
	shotAngle = 0;
	playerShotClock = PLAYER_SHOT_INTERVAL;
}

void updateShot(){
	if(playerShotClock >= PLAYER_SHOT_INTERVAL && controls.a){
		playerShotClock = 0;
		spawnPlayerBullet();
	}
	playerShotClock++;
	if(playerShotClock >= 600) playerShotClock = PLAYER_SHOT_INTERVAL;
}


// collision

void resetBounds(){
	pCol.x = pPos.x - P_COL_OFF_X;
	pCol.y = pPos.y - P_COL_OFF_Y;
	pCol.w = pPos.x + P_COL_OFF_X;
	pCol.z = pPos.y + P_COL_OFF_Y;
}

void updateBounds(){
	if(opens.w && pPos.x > PLAYER_LIMIT_RIGHT_MOVE) nextRoom(1);
	else if(!opens.w && pPos.x > PLAYER_LIMIT_RIGHT) pPos.x = PLAYER_LIMIT_RIGHT;
	else if(opens.x && pPos.x < PLAYER_LIMIT_LEFT_MOVE) nextRoom(3);
	else if(!opens.x && pPos.x < PLAYER_LIMIT_LEFT) pPos.x = PLAYER_LIMIT_LEFT;
	else if(opens.y && pPos.y < PLAYER_LIMIT_TOP_MOVE) nextRoom(0);
	else if(!opens.y && pPos.y < PLAYER_LIMIT_TOP) pPos.y = PLAYER_LIMIT_TOP;
	else if(opens.z && pPos.y > PLAYER_LIMIT_BOTTOM_MOVE) nextRoom(2);
	else if(!opens.z && pPos.y > PLAYER_LIMIT_BOTTOM){
		pPos.y = PLAYER_LIMIT_BOTTOM;
		grounded = TRUE;
	}
}

void blockPlayerCol(s16 i){
	blockDist.x = fix16Sub(blocks[i].pos.x, pCol.w);
	blockDist.w = fix16Sub(pCol.x, blocks[i].pos.w);
	blockDist.y = fix16Sub(blocks[i].pos.y, pCol.z);
	blockDist.z = fix16Sub(pCol.y, blocks[i].pos.z);
	// left side of block
	if(blockDist.x <= 0 && blockDist.x > blockDist.y && blockDist.x > fix16Add(blockDist.z, C_FIX))
		if(fix16Sub(blocks[i].pos.x, pCol.x) > 0) pPos.x = fix16Sub(blocks[i].pos.x, P_COL_OFF_X);
	// right side of block
	if(blockDist.w <= 0 && blockDist.w > blockDist.y && blockDist.w > blockDist.z)
		if(fix16Sub(pCol.w, blocks[i].pos.w) > 0) pPos.x = fix16Add(blocks[i].pos.w, P_COL_OFF_X);
	// top side of block
	if(blockDist.y <= 0 && blockDist.y > fix16Add(blockDist.w, C_FIX) && blockDist.y > blockDist.x){
		grounded = TRUE;
		if(fix16Sub(blocks[i].pos.y, pCol.y) > 0) pPos.y = fix16Sub(blocks[i].pos.y, P_COL_OFF_Y);
	}
	// else grounded = FALSE;
	// bottom side of block
	if(blockDist.z <= 0 && blockDist.z > blockDist.w && blockDist.z > blockDist.x)
		if(fix16Sub(pCol.z, blocks[i].pos.z) > 0) pPos.y = fix16Add(blocks[i].pos.z, P_COL_OFF_Y);
	updateBounds();
}


// movement

void loadMove(){
	jumpSpeed = 0;
	pPos.x = PLAYER_INIT_X;
	pPos.y = PLAYER_INIT_Y;
	playerSprite = SPR_addSprite(&chimata, pPos.x, pPos.y, sAttr());
	resetBounds();
	SPR_setDepth(playerSprite, 4);
}

void updateJump(){
	if(grounded){
		if(controls.b){
			jumpSpeed = JUMP_SET;
			grounded = FALSE;
		}
	} else {
		pPos.y = fix16Sub(pPos.y, jumpSpeed);
		jumpSpeed = fix16Sub(jumpSpeed, JUMP_MOD);
	}
}

void updateMove(){
	moveSpeed = 0;
	if(controls.left || controls.right || controls.up || controls.down){
		if(controls.left || controls.right){
			playerAngle = controls.left ? 512 : 0;
			moveSpeed = P_SPEED;
			SPR_setHFlip(playerSprite, controls.left ? 1 : 0);
		}
		shotAngle = controls.left ? (controls.up ? 640 : (controls.down ? 384 : 512)) :
			(controls.right ? (controls.up ? 896 : (controls.down ? 128 : 0)) : (controls.up ? 768 : 256));
	}
	if(moveSpeed > 0){
		pPos.x = fix16Add(pPos.x, fix16Mul(cosFix16(playerAngle), moveSpeed));
		pPos.y = fix16Add(pPos.y, fix16Mul(sinFix16(playerAngle), moveSpeed));
	}
	resetBounds();
	playerMoveClock++;
	if(playerMoveClock >= 6000) playerMoveClock = 60;
}

void updateDead(){
	killClock--;
	if(killClock <= 0) SPR_setVisibility(playerSprite, VISIBLE);
}


// main loop

void loadPlayer(){
	currentLives = 3;
	currentBombs = 2;
	loadMove();
	loadShot();
}

void updatePlayer(){
	if(killClock > 0) updateDead();
	else {
		updateShot();
		updateJump();
		updateMove();
	}
}

void drawPlayer(){
	SPR_setPosition(playerSprite, fix16ToInt(pPos.x) - 16 + SPRITE_OFF_X, fix16ToInt(pPos.y) - 24 + SPRITE_OFF_Y);
}