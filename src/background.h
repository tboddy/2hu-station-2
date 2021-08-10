// background

#define BG_W 32
#define BG_H 28

#define BG_SIZE FIX16(32)
#define BG_SIZE_NEG FIX16(-32)

#define BG_SPEED FIX16(0.1)
#define BG_SPEED_X FIX16(0.05)
#define BG_SPEED_Y FIX16(0.025)

#define BG_RAY_3 30
#define BG_RAY_4 31
#define BG_TREES_BOTTOM 32
#define BG_MOUNTAINS 33
#define BG_TREES BG_MOUNTAINS + 16

#define TREE_LINE 16
#define MOUNTAIN_LINE 10

#define BG_SCROLL_HEIGHT 9
#define BG_SCROLL_LIMIT FIX16(64)
#define BG_SCROLL_LIMIT_NEG FIX16(-64)

Vect2D_f16 bgPos, bgVel;
fix16 bgScrolls[BG_SCROLL_HEIGHT];
s16 bgScrollsRound[BG_SCROLL_HEIGHT];


fix16 pScroll1, pScroll2;

void loadRays(),
	loadTrees(),
	loadBottom(),
	updateBottom();


// ----------------------
// export
// ----------------------

void loadBackground(),
	updateBackground();