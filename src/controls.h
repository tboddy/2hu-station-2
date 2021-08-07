struct controls {
	bool left, right, up, down, a, b, c, x, y, z, start, mode;
	s16 leftI, rightI;
};

struct controls controls;

void updateControls(u16, u16, u16);