// enemies

#define ENEMY_COUNT 16

struct enemy {
	bool active;
	bool bools[COUNT_INT];
	s16 clock, angle, off, type;
	s16 ints[COUNT_INT];
	Vect2D_f16 pos, vel;
	fix16 speed;
	fix16 fixes[COUNT_INT];
	Sprite* image;
	s32 collisionOffset;
	void (*updater)(s16);
};

struct enemySpawner {
	bool hFlip, vFlip;
	bool bools[COUNT_INT];
	s16 type, angle;
	s16 ints[COUNT_INT];
	fix16 x, y, speed, velocityX, velocityY;
	fix16 fixes[COUNT_INT];
};

struct enemy enemies[ENEMY_COUNT];

Sprite *enemyImg;

void spawnEnemy(struct enemySpawner, void *),
	updateEnemy(s16),
	drawEnemy(s16),
	clearEnemies();


// main loop

void updateEnemies();