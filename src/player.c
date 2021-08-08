#include <genesis.h>
#include <resources.h>

#include "main.h"
#include "controls.h"
#include "background.h"
#include "bullets.h"
#include "spellcards.h"
#include "enemies.h"
#include "explosion.h"
#include "player.h"
#include "room.h"



// collision

void resetBounds(){
	pCol.x = pPos.x - P_COL_OFF_X;
	pCol.y = pPos.y - P_COL_OFF_Y;
	pCol.w = pPos.x + P_COL_OFF_X;
	pCol.z = pPos.y + P_COL_OFF_Y;
}

void updateBounds(){
	if(opens.w && pPos.x > PLAYER_LIMIT_RIGHT_MOVE) nextRoom(1);
	else if(opens.x && pPos.x < PLAYER_LIMIT_LEFT_MOVE) nextRoom(3);
	else if(opens.y && pPos.y < PLAYER_LIMIT_TOP_MOVE) nextRoom(0);
	else if(!opens.y && pPos.y < PLAYER_LIMIT_TOP) pPos.y = PLAYER_LIMIT_TOP;
	else if(opens.z && pPos.y > PLAYER_LIMIT_BOTTOM_MOVE) nextRoom(2);
	else if(!opens.z && pPos.y > PLAYER_LIMIT_BOTTOM){
		fallSpeed = 0;
		pPos.y = PLAYER_LIMIT_BOTTOM;
	}
}

void blockPlayerCol(s16 i){
	blockDist.x = fix16Sub(blocks[i].pos.x, pCol.w);
	blockDist.w = fix16Sub(pCol.x, blocks[i].pos.w);
	blockDist.y = fix16Sub(blocks[i].pos.y, pCol.z);
	blockDist.z = fix16Sub(pCol.y, blocks[i].pos.z);

	// left side of block
	if(blockDist.x <= 0 && blockDist.x > blockDist.y && blockDist.x > blockDist.z && fix16Sub(blocks[i].pos.x, pCol.x) > 0)
		pPos.x = fix16Sub(blocks[i].pos.x, P_COL_OFF_X);

	// right side of block
	if(blockDist.w <= 0 && blockDist.w > blockDist.y && blockDist.w > blockDist.z && fix16Sub(pCol.w, blocks[i].pos.w) > 0)
		pPos.x = fix16Add(blocks[i].pos.w, P_COL_OFF_X);

	// top side of block
	if(blockDist.y <= 0 && blockDist.y > blockDist.w && blockDist.y > blockDist.x && fix16Sub(blocks[i].pos.y, pCol.y) > 0){
		fallSpeed = 0;
		pPos.y = fix16Sub(blocks[i].pos.y, P_COL_OFF_Y);
	}

	// bottom side of block
	if(blockDist.z <= 0 && blockDist.z > blockDist.w && blockDist.z > blockDist.x && fix16Sub(pCol.z, blocks[i].pos.z) > 0)
		pPos.y = fix16Add(blocks[i].pos.z, P_COL_OFF_Y);
}


// movement

void loadMove(){
	pPos.x = PLAYER_INIT_X;
	pPos.y = PLAYER_INIT_Y;
	playerSprite = SPR_addSprite(&chimata, pPos.x, pPos.y, TILE_ATTR(PAL2, 0, FALSE, FALSE));
	resetBounds();
	SPR_setDepth(playerSprite, 4);
}

void updateJump(){
	if(controls.b && !jumping && fallSpeed == 0){
		fallSpeed = JUMP_SPEED;
		jumping = TRUE;
	} else if(!controls.b && jumping && fallSpeed == 0) jumping = FALSE;
	pPos.y = fix16Add(pPos.y, fallSpeed);
	if(fallSpeed < GRAVITY_MAX){
		fallSpeed = fix16Add(fallSpeed, GRAVITY);
		if(fallSpeed > GRAVITY_MAX) fallSpeed = GRAVITY_MAX;
	}
}

void updateMove(){
	moveSpeed = 0;
	if(controls.left || controls.right || controls.up || controls.down){
		if(controls.left || controls.right){
		// playerAngle = controls.left ? (controls.up ? 640 : (controls.down ? 384 : 512)) :
		// 	(controls.right ? (controls.up ? 896 : (controls.down ? 128 : 0)) : (controls.up ? 768 : 256));
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
	loadSpellcards();
}

void updatePlayer(){
	if(killClock > 0) updateDead();
	else {
		updateSpellcards();
		updateJump();
		updateMove();
		updateBounds();
	}
}

void drawPlayer(){
	SPR_setPosition(playerSprite, fix16ToInt(pPos.x) - 16 + SPRITE_OFF_X, fix16ToInt(pPos.y) - 24 + SPRITE_OFF_Y);
}