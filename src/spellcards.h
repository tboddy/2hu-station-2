// spellcards

#define B_SPAWN_MOD FIX16(2)

bool spellBools[COUNT_INT];
s16 spellInts[COUNT_INT];
fix16 spellFixes[COUNT_INT];
Vect2D_f16 spellVectors[COUNT_INT];
s16 shotInterval, shotClock, shotAngle;
fix16 bSpawnY;

bool shooting;

void defaultShot(),
	ownerless(),
	obsession();


// main loop

void loadSpellcards(),
	updateSpellcards();