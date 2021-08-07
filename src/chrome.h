// frame

#define FRAME_WIDTH 32
#define FRAME_HEIGHT 28

#define FRAME_TILE_1 25
#define FRAME_TILE_2 26
#define FRAME_TILE_3 27
#define FRAME_TILE_4 28

#define FRAME_OFF_Y TILE_OFF_Y
#define FRAME_OFF_Z FRAME_HEIGHT - 2
#define FRAME_OFF_X 0
#define FRAME_OFF_W 31

s16 frameTile, frameV, frameH;

void loadFrame();


// hud

#define SCORE_X 2
#define SCORE_Y 1
#define LIVES_X 29
#define LIVES_Y 1

s16 chromeLives, livesX, livesY;

void loadScore(),
	updateLives();


// export

void loadChrome(),
	updateChrome();