// bullets

#define BULLET_COUNT 64

#define BULLET_LIMIT_X FIX16(16)
#define BULLET_LIMIT_W FIX16(GAME_W - 16)
#define BULLET_LIMIT_Y FIX16(16)
#define BULLET_LIMIT_Z FIX16(GAME_H - 16)

s16 bulletCount;

struct bulletStruct {
	bool active, grazed, player;
	Vect2D_f16 pos, vel, off;
	Vect4D_f16 bounds;
	fix16 speed;
	Sprite* image;
	s16 clock, angle;
	bool bools[COUNT_INT];
	s16 ints[COUNT_INT];
	fix16 fixes[COUNT_INT];
	void (*updater)(s16);
	void (*suicide)(s16);
	Vect2D_f16 vectors[COUNT_INT];
};

struct bulletSpawner {
	bool player;
	fix16 speed, pX, pY, vX, vY;
	s16 angle, type;
	bool bools[COUNT_INT];
	s16 ints[COUNT_INT];
	fix16 fixes[COUNT_INT];
	Vect2D_f16 vectors[COUNT_INT];
};

struct bulletStruct bullets[BULLET_COUNT];
bool killBullets;
s16 killBulletsClock;


// spawn

Sprite *bulletImg;
void spawnBullet(struct bulletSpawner spawner, void(*updater), void(*suicide));


// collision

s32 bulletColDist;

void checkBulletCol(s16),
	destroyBullet(s16),
	updateKillBullets(),
	clearBullets(),
	blockBulletCol(s16);
	

// main loop

void updateBullet(s16),
	updateBullets();