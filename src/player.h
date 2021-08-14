// player

// movement

#define PLAYER_INIT_X FIX16(GAME_W / 2)
#define PLAYER_INIT_Y FIX16(18 * 9)

#define PLAYER_INIT_LEFT FIX16(4)
#define PLAYER_INIT_RIGHT fix16Sub(FIX16(GAME_W), PLAYER_INIT_LEFT)
#define PLAYER_INIT_TOP FIX16(16)
#define PLAYER_INIT_BOTTOM fix16Sub(FIX16(GAME_H), PLAYER_INIT_TOP)

#define PLAYER_LIMIT_MOVE_OFFSET -16
#define PLAYER_LIMIT_LEFT_MOVE FIX16(PLAYER_LIMIT_MOVE_OFFSET)
#define PLAYER_LIMIT_TOP_MOVE FIX16(PLAYER_LIMIT_MOVE_OFFSET)
#define PLAYER_LIMIT_RIGHT_MOVE FIX16(GAME_W - PLAYER_LIMIT_MOVE_OFFSET)
#define PLAYER_LIMIT_BOTTOM_MOVE FIX16(GAME_H - PLAYER_LIMIT_MOVE_OFFSET)

#define P_SPEED FIX16(1.75)
#define L_SPEED FIX16(1.5)
#define JUMP_SPEED FIX16(-4.25)

#define KILL_CLOCK_LIMIT 60

#define GRAVITY FIX16(0.25)
#define GRAVITY_MIN FIX16(0.1)
#define GRAVITY_MAX FIX16(4)

Vect2D_f16 pPos, playerVelocity;
Sprite* playerSprite;
s16 playerMoveClock, killClock, currentLives, currentBombs, playerAngle, playerAnim, moveClock;
fix16 moveSpeed, lastY, fallSpeed, lastX;

fix16 pDir;
Vect4D_f16 tempFree;

void loadMove(),
	updateJump(),
	updateLadder(),
	placeFree(s16, s16),
	updateParallax(),
	updateMove(),
	updateDead();


// collision

#define P_COL_OFF_X FIX16(8)
#define P_COL_OFF_X_WALL FIX16(9)
#define P_COL_OFF_Y FIX16(22)
#define P_COL_OFF_Y_WALL FIX16(23)

#define PLAYER_LIMIT_LEFT fix16Add(FIX16(16), P_COL_OFF_X)
#define PLAYER_LIMIT_TOP fix16Add(FIX16(16), P_COL_OFF_Y)
#define PLAYER_LIMIT_RIGHT fix16Sub(FIX16(GAME_W), PLAYER_LIMIT_LEFT)
#define PLAYER_LIMIT_BOTTOM fix16Sub(FIX16(GAME_H), PLAYER_LIMIT_TOP)

#define BLOCK_LAST_CHECK FIX16(GAME_W - 16)
#define BLOCK_Z_FIX FIX16(-4)

#define LADDER_OFF_X FIX16(4)
#define LADDER_OFF_Y FIX16(0)
#define LADDER_OFF_Z FIX16(12)

struct pHitStruct { bool x, y, w, z; };
struct pHitStruct pHit;

bool jumping, falling, onLadder;
Vect4D_f16 pCol, blockDist;
fix32 blockPDist;

void blockPBulletCol(s16),
	resetBounds(),
	blockPlayerCol(s16),
	ladderCol(s16),
	updateBounds();


// main loop

void loadPlayer(),
	updatePlayer(),
	drawPlayer();