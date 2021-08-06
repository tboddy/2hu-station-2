// ----------------------
// background bottom
// ----------------------

#define BG_SIZE FIX16(32)
#define BG_SIZE_NEG FIX16(-32)

#define BG_SPEED FIX16(0.1)
#define BG_SPEED_X FIX16(0.05)
#define BG_SPEED_Y FIX16(0.025)

Vect2D_f16 bgPos, bgVel;

void loadBottom(),
	updateBottom();


// ----------------------
// export
// ----------------------

void loadBackground(),
	updateBackground();