#define CS_MOVE 1
#define CS_ENTER 2

#define SC_MOVE 1
#define SC_ENTER 2

#define KEY_DOWN 1
#define KEY_UP 2
#define KEY_LEFT 3
#define KEY_RIGHT 4

struct CS_Enter {
	char size;
	char type;
	int x;
	int y;
};

struct SC_Enter {
	char size;
	char type;
	char id;
	int x;
	int y;
};

struct CS_MOVE_packet{
	char size;
	char type;
	char dir;
	char id;
};

struct SC_MOVE_packet {
	char size;
	char type;
	char id;
	int width;
	int height;
};