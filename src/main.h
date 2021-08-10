// metrics

#define WIN_WIDTH 320
#define WIN_HEIGHT 224

#define GAME_W 32 * 8
#define GAME_H 26 * 8

#define COUNT_INT 8

#define LEAST_TILE 4
#define HALF_TILE 5
#define MOST_TILE 6
#define FULL_TILE 7


// frame offset

#define TILE_OFF_X 0
#define TILE_OFF_Y 2
#define SPRITE_OFF_X TILE_OFF_X * 8
#define SPRITE_OFF_Y TILE_OFF_Y * 8


// helpers

fix16 honeSpeed;
Vect2D_f16 hPos;
fix16 getDistance(Vect2D_f16, Vect2D_f16);
u16 sAttr();
void eUpdate(s16),
	eSuicide(s16),
	updateVelocity(s16, s16);
Vect2D_f16 hone(Vect2D_f16, Vect2D_f16, fix16, s16);


// state

s16 gameClock;
bool paused, gameOver;


// game

void loadGame(),
	updateGame(),
	loadResources();

int main();