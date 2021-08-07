#include <genesis.h>
#include "controls.h"

void updateControls(u16 joy, u16 changed, u16 state){
	if(joy == JOY_1){
		if(changed){}
		controls.left = (state & BUTTON_LEFT);
		controls.leftI = (state & BUTTON_LEFT) ? 1 : 0;
		controls.right = (state & BUTTON_RIGHT);
		controls.leftI = (state & BUTTON_RIGHT) ? 1 : 0;
		controls.up = (state & BUTTON_UP);
		controls.down = (state & BUTTON_DOWN);
		controls.a = (state & BUTTON_A);
		controls.b = (state & BUTTON_B);
		controls.c = (state & BUTTON_C);
		controls.start = (state & BUTTON_START);
	}
}