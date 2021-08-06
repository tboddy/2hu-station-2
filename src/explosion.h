// explosion

#define EXPLOSION_DUMP_X WIN_WIDTH + 32
#define EXPLOSION_DUMP_Y WIN_HEIGHT + 64

#define EXP_OFF 12
#define EXPLOSION_LIMIT 9

#define EXP_COUNT 10

struct explosion {
	bool active;
	s16 clock;
	Vect2D_f16 pos;
	Sprite* image;
};
struct explosion explosions[EXP_COUNT];


// spawn

Sprite *expImg;
void spawnExplosion(Vect2D_f16, bool);


// update

void updateExplosion(s16);


// main loop

void updateExplosions();