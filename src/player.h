// player

// shooting

#define PLAYER_SHOT_INTERVAL 10

s16 playerShotClock, shotAngle;

void spawnPlayerBullet(),
	loadShot(),
	updateShot();


// ----------------------
// movement
// ----------------------

#define PLAYER_INIT_X FIX16(GAME_W / 2)
#define PLAYER_INIT_Y FIX16(GAME_H / 2)

#define PLAYER_INIT_LEFT FIX16(-4)
#define PLAYER_INIT_RIGHT fix16Sub(FIX16(GAME_W), PLAYER_INIT_LEFT)
#define PLAYER_INIT_TOP PLAYER_INIT_LEFT
#define PLAYER_INIT_BOTTOM fix16Sub(FIX16(GAME_H), PLAYER_INIT_LEFT)

#define PLAYER_LIMIT_MOVE_OFFSET -8
#define PLAYER_LIMIT_LEFT_MOVE FIX16(PLAYER_LIMIT_MOVE_OFFSET)
#define PLAYER_LIMIT_TOP_MOVE FIX16(PLAYER_LIMIT_MOVE_OFFSET)
#define PLAYER_LIMIT_RIGHT_MOVE FIX16(GAME_W - PLAYER_LIMIT_MOVE_OFFSET)
#define PLAYER_LIMIT_BOTTOM_MOVE FIX16(GAME_H - PLAYER_LIMIT_MOVE_OFFSET)

#define P_SPEED FIX16(2)

#define KILL_CLOCK_LIMIT 60

#define GRAVITY FIX16(3.5)
#define JUMP_SET FIX16(2)
#define JUMP_MOD FIX16(0.05)

Vect2D_f16 pPos, playerVelocity;
Sprite* playerSprite;
s16 playerMoveClock, killClock, currentLives, currentBombs, playerAngle;
fix16 moveSpeed, lastY, jumpSpeed;

void loadMove(),
	updateJump(),
	updateMove(),
	updateDead();


// collision

#define P_COL_OFF_X FIX16(10)
#define P_COL_OFF_Y FIX16(22)

#define PLAYER_LIMIT_LEFT fix16Add(FIX16(16), P_COL_OFF_X)
#define PLAYER_LIMIT_TOP fix16Add(FIX16(16), P_COL_OFF_Y)
#define PLAYER_LIMIT_RIGHT fix16Sub(FIX16(GAME_W), PLAYER_LIMIT_LEFT)
#define PLAYER_LIMIT_BOTTOM fix16Sub(FIX16(GAME_H), PLAYER_LIMIT_TOP)

bool grounded;
Vect4D_f16 pCol;
s16 blockI;
s16 blockDistanceLeft, blockDistanceRight, blockDistanceTop, blockDistanceBottom;
s32 blockBulletDistance;

void blockPBulletCol(s16),
	resetBounds(),
	blockPlayerCol(s16),
	updateBounds();


// main loop

void loadPlayer(),
	updatePlayer(),
	drawPlayer();