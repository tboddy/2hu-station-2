// blocks

#define BLOCK2_YX 64
#define BLOCK2_XX 68
#define BLOCK2_C 72
#define BLOCK3_X 76
#define BLOCK4_X 80
#define BLOCK5_X 84
#define BLOCK6_X 88

#define BLOCK_M 4 // LOL
#define ROCK_BLUE_BOTTOM 88
#define ROCK_BLUE_TOP ROCK_BLUE_BOTTOM + BLOCK_M
#define ROCK_BLUE_RIGHT ROCK_BLUE_TOP + BLOCK_M
#define ROCK_BLUE_LEFT ROCK_BLUE_RIGHT + BLOCK_M
#define ROCK_BLUE_CORNERX ROCK_BLUE_LEFT + BLOCK_M
#define ROCK_BLUE_CORNERW ROCK_BLUE_CORNERX + BLOCK_M
#define ROCK_BLUE_CORNERY ROCK_BLUE_CORNERW + BLOCK_M
#define ROCK_BLUE_CORNERZ ROCK_BLUE_CORNERY + BLOCK_M
#define ROCK_BLUE_TOP_LEFT ROCK_BLUE_CORNERZ + BLOCK_M
#define ROCK_BLUE_TOP_RIGHT ROCK_BLUE_TOP_LEFT + BLOCK_M
#define ROCK_BLUE_BOTTOM_LEFT ROCK_BLUE_TOP_RIGHT + BLOCK_M
#define ROCK_BLUE_BOTTOM_RIGHT ROCK_BLUE_BOTTOM_LEFT + BLOCK_M
#define DOOR_GREEN ROCK_BLUE_BOTTOM_RIGHT + BLOCK_M
#define ROCK_BLUE_GRASS_MIDDLE DOOR_GREEN + BLOCK_M
#define ROCK_BLUE_GRASS_LEFT ROCK_BLUE_GRASS_MIDDLE + BLOCK_M
#define ROCK_BLUE_GRASS_RIGHT ROCK_BLUE_GRASS_LEFT + BLOCK_M
#define ROCK_BLUE_GRASS_X ROCK_BLUE_GRASS_RIGHT + BLOCK_M
#define ROCK_BLUE_GRASS_W ROCK_BLUE_GRASS_X + BLOCK_M
#define LADDER ROCK_BLUE_GRASS_W + BLOCK_M


#define BLOCK_CT 128
#define BLOCK_SZ FIX16(16)
#define BLOCK_OFF FIX16(8)

#define COL_BLOCK_OFF FIX16(6)
#define C_FIX FIX16(1)

struct block {
	bool active, dead, ladder;
	s16 type;
	Vect4D_f16 pos, col;
	Vect2D_f16 center;
};
struct block blocks[BLOCK_CT];

bool needBlockCancel;

s16 blockTile;
bool blockFlipH, blockFlipV;

Image *blockImg;

void spawnBlock(s16, s16, s16, bool),
	blockPlayerCollision(s16),
	updateBlocks(),
	removeBlocks();


// room types

#define ROOM_W 32
#define ROOM_H GAME_H / 8

#define DOOR_X_START 1
#define DOOR_X_END ROOM_W - DOOR_X_START - 2
#define DOOR_Y_START 1
#define DOOR_Y_END ROOM_H - DOOR_Y_START - 2

#define PLAYER_DOOR_X_START FIX16(2 * 8 + 8)
#define PLAYER_DOOR_X_END FIX16(26 * 8 + 8)
#define PLAYER_DOOR_Y_START FIX16(2 * 8 + 16 + 4)
#define PLAYER_DOOR_Y_END FIX16(12 * 8 - 4)


#define BLOCK_WIDTH ROOM_W / 2
#define BLOCK_HEIGHT ROOM_H / 2

s16 roomLayout[BLOCK_HEIGHT][BLOCK_WIDTH];
s16 currentRoomType;

void loadRoomBorder(bool, bool, bool, bool),
	loadRoomTiles(),
	loadRoomTop();


// room movement

struct openStr {bool x, y, w, z; };
struct openStr opens;
void *topRoom, *leftRoom, *rightRoom, *bottomRoom;
s16 changingRoom;

s16 roomEnemyX, roomEnemyY;

void nextRoom(s16),
	nextRoomPos();
void (*changeRoom)();


// ----------------------
// tiles
// ----------------------

s16 roomTileIndex;

void loadOverlay(),
	loadTiles();


// ----------------------
// export
// ----------------------

void loadRoom(),
	updateRoom();