#define MAP_WIDTH 44
#define MAP_HEIGHT 44
#define ARROW 224
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ENTER 13
#define SPEED 15
#define MARGIN (60 + (50 - MAP_WIDTH))
#define CONSOLE_WIDTH (MAP_WIDTH * 2 + MARGIN)
#define CONSOLE_HEIGHT (MAP_HEIGHT + 4)
#define TITLE "SnakeGame"
#define PREVIEW_SNAKE_LEN 25
#define START_SNAKE_LEN 10

// 뱀 모양 및 색
int headColor = 0xa, color1 = 0xa, color2 = 0x3, colorChange = 4;
char headChar[2] = "◆", bodyChar[2] = "⊙";

// 아이템 모양 및 색
int itemColors[] = { 0x4, 0x7, 0x9 };
char itemShapes[][3] = { "◐", "※", "▨" };

int map[MAP_HEIGHT][MAP_WIDTH] = { 0 }; // 0: void | 1: snake | 2~: item/trap
int snake[2000][2] = { 0 }, snakeLen = 0;
int count, playTime, score = 0, stage, bestScore = 0;
int gotApple = 1000, gotWeb = -1, gotIce = 1000;
short vectorChanged = 0;
int speed = SPEED, originalSpeed = SPEED;
int difficulty = 0;

short push(int x, int y);
void shift();
void addSnakeLen(int count);
void printInfo(int line, char* str, int color);
void clearInfo(int line);
void printShape(int x, int y, char* str, int color);
void printCenter(int field, int line, char* str, int color);
void printCenterSnake(int field, int line, char* str);
void printField(int line, char* str, int color);
void clearGame();
void putItem(int itemKey);


void clearGame() {
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			map[i][j] = 0;
		}
	}
	score = 0;
	snakeLen = 0;
	vectorChanged = 0;
	speed = SPEED;
	originalSpeed = SPEED;
	gotApple = 1000;
	gotWeb = -1;
}

void putItem(int itemKey) {
	int x, y;
	do {
		x = rand() % (MAP_WIDTH - 2) + 1;
		y = rand() % (MAP_HEIGHT - 2) + 1;
	} while (map[y][x] == 1);
	map[y][x] = itemKey;
	printShape(x, y, itemShapes[itemKey - 2], itemColors[itemKey - 2]);
}

short push(int x, int y) {
	if (map[y][x] == 1) return 0;
	if (x < 0 || y < 0 || x >= MAP_WIDTH || y >= MAP_HEIGHT) return 0;
	snakeLen++;
	snake[snakeLen - 1][0] = x;
	snake[snakeLen - 1][1] = y;
	if (snakeLen >= 2)
		printShape(snake[snakeLen - 2][0], snake[snakeLen - 2][1], bodyChar, color1 + (count / colorChange % 2) * (color2 - color1));
	printShape(x, y, headChar, headColor);
	map[y][x] = 1;
	return 1;
}

void addSnakeLen(int count) {
	for (int i = snakeLen; i > 0; i--) {
		snake[i + count - 1][0] = snake[i - 1][0];
		snake[i + count - 1][1] = snake[i - 1][1];
	}
	int x = snake[0][0], y = snake[0][1];
	for (int i = 0; i < count; i++) {
		snake[i][0] = x;
		snake[i][1] = y;
	}
	snakeLen += count;
}

void shift() {
	if (snakeLen == 0) return;
	int x = snake[0][0], y = snake[0][1];
	map[y][x] = 0;
	printShape(x, y, "  ", 0x0);
	snakeLen--;
	for (int i = 0; i < (int)snakeLen; i++) {
		snake[i][0] = snake[i + 1][0];
		snake[i][1] = snake[i + 1][1];
	}
	snake[snakeLen][0] = 0;
	snake[snakeLen][1] = 0;
}

void printInfo(int line, char* str, int color) {
	setColor(color, 0x0);
	gotoxy(MAP_WIDTH * 2 + 7, 1 + line);
	printf("%s ", str);
}

void clearInfo(int line) {
	gotoxy(MAP_WIDTH * 2 + 7, 1 + line);
	for (int i = 0; i < MARGIN - 7; i++) printf(" ");
}

void printShape(int x, int y, char* str, int color) {
	gotoxy(4 + x * 2, 2 + y);
	setColor(color, 0x0);
	printf(str);
}

void printCenter(int field, int line, char* str, int color) {
	setColor(0xf, 0x0);
	int strLen;
	for (strLen = 0; str[strLen]; strLen++);
	gotoxy(CONSOLE_WIDTH / 2 - strLen / 2, CONSOLE_HEIGHT / 2 + field * 4 + line);
	setColor(color, 0x0);
	printf(str);
}

void printCenterSnake(int field, int line, char* str) {
	setColor(0xf, 0x0);
	int strLen;
	for (strLen = 0; str[strLen]; strLen++);
	strLen += 2 + PREVIEW_SNAKE_LEN * 2;
	gotoxy(CONSOLE_WIDTH / 2 - strLen / 2, CONSOLE_HEIGHT / 2 + field * 4 + line);
	printf("%s", str);
	setColor(headColor, 0);
	printf("%s", headChar);
	for (int j = 0; j < PREVIEW_SNAKE_LEN; j++) {
		setColor(color1 + (j / colorChange % 2) * (color2 - color1), 0);
		printf("%s", bodyChar);
	}
}

void printField(int line, char* str, int color) {
	setColor(0xf, 0x0);
	int strLen;
	for (strLen = 0; str[strLen]; strLen++);
	gotoxy(CONSOLE_WIDTH / 2 - strLen / 2 - 4, CONSOLE_HEIGHT / 2 + line * 4);
	printf("┌─");
	for (int i = 0; i < strLen; i++) {
		printf("─");
	}
	printf("┐ ");
	gotoxy(CONSOLE_WIDTH / 2 - strLen / 2 - 4, CONSOLE_HEIGHT / 2 + line * 4 + 1);
	printf("│ ");
	setColor(color, 0x0);
	printf(str);
	setColor(0xf, 0x0);
	printf("│ ");
	gotoxy(CONSOLE_WIDTH / 2 - strLen / 2 - 4, CONSOLE_HEIGHT / 2 + line * 4 + 2);
	printf("└─");
	for (int i = 0; i < strLen; i++) {
		printf("─");
	}
	printf("┘ ");
}