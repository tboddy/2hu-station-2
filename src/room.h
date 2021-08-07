// blocks

#define BLOCK2_YX 64
#define BLOCK2_XX 68
#define BLOCK2_C 72
#define BLOCK3_X 76
#define BLOCK4_X 80
#define BLOCK5_X 84
#define BLOCK6_X 88

#define BLOCK_CT 128
#define BLOCK_SZ FIX16(16)
#define BLOCK_OFF FIX16(8)

#define COL_BLOCK_CT 8
#define COL_BLOCK_OFF FIX16(6)
#define C_FIX FIX16(1)

struct block {
	bool active, dead;
	s16 type;
	Vect4D_f16 pos, col;
};
struct block blocks[BLOCK_CT];

bool needBlockCancel;

s16 blockTile;
s16 colPBlocks[COL_BLOCK_CT];
bool blockFlipH, blockFlipV;

void loadBlocks(),
	spawnBlock(s16, s16, s16, bool, bool, bool),
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


#define BLOCK_WIDTH ROOM_W / 2 - 2
#define BLOCK_HEIGHT ROOM_H / 2 - 2

s16 roomLayout[BLOCK_HEIGHT][BLOCK_WIDTH];
s16 currentRoomType;

void loadRoomBorder(bool, bool, bool, bool),
	loadRoomTiles(),
	loadRoomTop();


// ----------------------
// room movement
// ----------------------
struct openStr {bool x, y, w, z; };
struct openStr opens;
void *topRoom, *leftRoom, *rightRoom, *bottomRoom;

s16 roomEnemyX, roomEnemyY;

void nextRoom(s16);
void (*changeRoom)();


// ----------------------
// rooms
// ----------------------
void a1(), a2(), a3(), a4(), a5(), a6(), a7(), a8(), a9();


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