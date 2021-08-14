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
	else if(!opens.z && pPos.y > PLAYER_LIMIT_BOTTOM) pPos.y = PLAYER_LIMIT_BOTTOM;
}

void blockPlayerCol(s16 i){
	blockDist.x = fix16Sub(blocks[i].pos.x, pCol.w);
	blockDist.w = fix16Sub(pCol.x, blocks[i].pos.w);
	blockDist.y = fix16Sub(blocks[i].pos.y, pCol.z);
	blockDist.z = fix16Sub(pCol.y, blocks[i].pos.z);

	// left side of block
	if(blockDist.x <= 0 && blockDist.x > blockDist.y && blockDist.x > blockDist.z){
		pPos.x = fix16Sub(blocks[i].pos.x, P_COL_OFF_X_WALL);
	}

	// right side of block
	if(blockDist.w <= 0 && blockDist.w > blockDist.y && blockDist.w > blockDist.z){
		pPos.x = fix16Add(blocks[i].pos.w, P_COL_OFF_X_WALL);
	}

	// top side of block
	if(blockDist.y < 0 && blockDist.y > blockDist.w && blockDist.y > blockDist.x){
		fallSpeed = 0;
		falling = FALSE;
		pPos.y = fix16Sub(blocks[i].pos.y, P_COL_OFF_Y_WALL);
	}

	// bottom side of block
	if(blockDist.z <= (onLadder ? 0 : BLOCK_Z_FIX) && blockDist.z > blockDist.w && blockDist.z > blockDist.x){
		fallSpeed = GRAVITY_MIN;
		pPos.y = fix16Add(blocks[i].pos.z, P_COL_OFF_Y_WALL);
	}
}

void ladderCol(s16 i){
	if((pCol.x <= fix16Sub(blocks[i].pos.w, LADDER_OFF_X) && pCol.w >= fix16Add(blocks[i].pos.x, LADDER_OFF_X) &&
		pCol.y <= fix16Sub(blocks[i].pos.z, LADDER_OFF_Z) && pCol.z >= fix16Add(blocks[i].pos.y, LADDER_OFF_Y))){
		onLadder = TRUE;
	}
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
	if(falling) SPR_setFrame(playerSprite, fallSpeed > FIX16(1.25) ? 0 : 1);
	if(controls.b && !jumping && fallSpeed == 0){
		fallSpeed = JUMP_SPEED;
		jumping = TRUE;
		falling = TRUE;
		SPR_setAnim(playerSprite, 1);
	} else if(!controls.b && jumping && fallSpeed == 0) jumping = FALSE;
	pPos.y = fix16Add(pPos.y, fallSpeed);
	if(fallSpeed < GRAVITY_MAX){
		fallSpeed = fix16Add(fallSpeed, GRAVITY);
		if(fallSpeed > GRAVITY_MAX) fallSpeed = GRAVITY_MAX;
	}
}

void updateLadder(){
	fallSpeed = 0;
	jumping = FALSE;
	falling = TRUE;
	if(controls.b && !jumping){
		fallSpeed = JUMP_SPEED;
		jumping = TRUE;
		falling = TRUE;
		onLadder = FALSE;
		SPR_setAnim(playerSprite, 1);
	}
	SPR_setAnim(playerSprite, 0);
}

void updateParallax(){
	if(pPos.x < lastX){
		pScroll1 = FIX16(0.03);
		pScroll2 = FIX16(0.06);
	} else if(pPos.x > lastX){
		pScroll1 = FIX16(-0.03);
		pScroll2 = FIX16(-0.06);
	} else {
		pScroll1 = 0;
		pScroll2 = 0;
	}
	lastX = pPos.x;
}

void updateMove(){
	moveSpeed = 0;
	if(controls.left || controls.right || controls.up || controls.down){
		if(onLadder){
			playerAngle = controls.left ? (controls.up ? 640 : (controls.down ? 384 : 512)) :
				(controls.right ? (controls.up ? 896 : (controls.down ? 128 : 0)) : (controls.up ? 768 : 256));
			moveSpeed = L_SPEED;
			SPR_setHFlip(playerSprite, controls.left ? 1 : 0);
		} else if(controls.left || controls.right){
			playerAngle = controls.left ? 512 : 0;
			if(!falling){
				SPR_setAnim(playerSprite, 1);
				if(moveClock % 10 == 0) SPR_nextFrame(playerSprite);
			}
			moveSpeed = P_SPEED;
			SPR_setHFlip(playerSprite, controls.left ? 1 : 0);
		}
		shotAngle = controls.left ? (controls.up ? 640 : (controls.down ? 384 : 512)) :
			(controls.right ? (controls.up ? 896 : (controls.down ? 128 : 0)) : (controls.up ? 768 : 256));
	} else if(!falling) SPR_setAnim(playerSprite, 0);
	if(moveSpeed > 0){
		pPos.x = fix16Add(pPos.x, fix16Mul(cosFix16(playerAngle), moveSpeed));
		pPos.y = fix16Add(pPos.y, fix16Mul(sinFix16(playerAngle), moveSpeed));
		moveClock++;
		if(moveClock >= 600) moveClock = 0;
	} else moveClock = 0;
	resetBounds();
	updateParallax();
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
		onLadder ? updateLadder() : updateJump();
		updateMove();
		updateBounds();
	}
}

void drawPlayer(){
	SPR_setPosition(playerSprite, fix16ToInt(pPos.x) - 16 + SPRITE_OFF_X, fix16ToInt(pPos.y) - 24 + SPRITE_OFF_Y);
}