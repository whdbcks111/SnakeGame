#pragma comment(lib, "winmm.lib")
#define _CRT_SECURE_NO_WARNINGS
#include <sys/timeb.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <math.h>
#include "console.h"
#include "game.h"

void main();
void mainScreen(int selected);
void howToGame();
void customizingScreen();
void start();
void gameOver();

void main() {
	srand((unsigned int)time(NULL));
	mainScreen(0);
}

void mainScreen(int selected) {
	setTitle(TITLE);
	cursorView(0);
	setConsoleSize(CONSOLE_WIDTH, CONSOLE_HEIGHT);
	setColor(0xf, 0x0);

	printCenter(-5, 0, "⊙⊙⊙⊙◆  ⊙⊙    ⊙    ⊙⊙⊙    ⊙    ⊙  ⊙⊙⊙⊙⊙", color1);
	printCenter(-5, 1, "⊙          ⊙  ⊙  ⊙  ⊙      ⊙  ⊙  ⊙    ⊙        ", color1);
	printCenter(-5, 2, "⊙⊙⊙⊙⊙  ⊙  ⊙  ⊙  ⊙⊙⊙⊙⊙  ⊙⊙      ⊙⊙⊙⊙⊙", color1);
	printCenter(-5, 3, "        ⊙  ⊙  ⊙  ⊙  ⊙      ⊙  ⊙  ⊙    ⊙        ", color1);
	printCenter(-5, 4, "⊙⊙⊙⊙⊙  ◆    ⊙⊙  ⊙      ⊙  ⊙    ⊙  ⊙⊙⊙⊙⊙", color1);

	printCenter(-5, 6, "  ⊙⊙⊙      ⊙⊙⊙    ⊙⊙  ⊙⊙  ⊙⊙⊙⊙⊙", color2);
	printCenter(-5, 7, "⊙      ⊙  ⊙      ⊙  ⊙  ⊙  ⊙  ⊙        ", color2);
	printCenter(-5, 8, "⊙          ⊙⊙⊙⊙⊙  ⊙  ⊙  ⊙  ⊙⊙⊙⊙⊙", color2);
	printCenter(-5, 9, "⊙    ◆    ⊙      ⊙  ⊙  ⊙  ⊙  ⊙        ", color2);
	printCenter(-5, 10, "⊙      ⊙  ⊙      ⊙  ⊙      ⊙  ⊙        ", color2);
	printCenter(-5, 11, "  ⊙⊙⊙⊙  ⊙      ⊙  ⊙      ◆  ⊙⊙⊙⊙⊙", color2);
	//큰 SNAKE GAME 문자 출력

	char scoreView[100];
	sprintf(scoreView, "최고점수 : %d", bestScore);
	printCenter(-1, 0, scoreView, 0x7);

	char btn[10][50];
	strcpy(btn[0], "게임 시작");
	strcpy(btn[1], "게임 방법");
	strcpy(btn[2], "뱀 색깔 및 모양 설정");
	char diffStr[100];
	char diffNames[3][20] = { "보통", "어려움", "매우 어려움" };
	sprintf(diffStr, "현재 난이도 : %s", diffNames[difficulty]);
	strcpy(btn[3], diffStr);
	strcpy(btn[4], "게임 종료");
	int key, select = selected, max_select = 4;
	char str[50];

	for (int i = 0; i <= max_select; i++) {
		sprintf(str, "    %s    ", btn[i]);
		printField(i, str, 0x8);
	}
	sprintf(str, "  > %s    ", btn[select]);
	printField(select, str, 0xf);

	printCenter(max_select + 1, 0, "방향키로 버튼을 선택하고 엔터를 누르세요.", 0x8);

	while (1) {
		if (_kbhit()) {
			cursorView(0);
			key = _getch();
			if (key == ARROW) {
				key = _getch();
				if (key == UP) {
					sprintf(str, "    %s    ", btn[select]);
					printField(select, str, 0x8);
					if (select == 0) select = max_select;
					else select--;
					sprintf(str, "  > %s    ", btn[select]);
					printField(select, str, 0xf);
				}
				else if (key == DOWN) {
					sprintf(str, "    %s    ", btn[select]);
					printField(select, str, 0x8);
					if (select == max_select) select = 0;
					else select++;
					sprintf(str, "  > %s    ", btn[select]);
					printField(select, str, 0xf);
				}
			}
			else if (key == ENTER) {
				switch (select) {
				case 0:
					start();
					break;
				case 1:
					howToGame();
					break;
				case 2:
					customizingScreen();
					break;
				case 3:
					difficulty = (difficulty + 1) % 3;
					mainScreen(3);
					break;
				default:
					break;
				}
				return;
			}
		}
	}
}

void showSnakePreview() {
	printCenterSnake(1, 2, "뱀 미리보기 : ");
}

void customizingScreen() {
	cls();
	cursorView(0);
	printField(-5, "        커스터마이징        ", 0xf);

	printCenter(-3, 0, "■■■■ 현재 뱀 머리 부분 색깔 ■■■■", headColor);
	printCenter(-3, 2, "뱀의 머리 부분 색을 설정하시려면 1을 눌러주세요.", 0x7);

	printCenter(-2, 0, "■■■■ 현재 뱀 몸통 부분 첫번째 색깔 ■■■■", color1);
	printCenter(-2, 2, "뱀의 몸통 부분 첫번째 색을 설정하시려면 2를 눌러주세요.", 0x7);

	printCenter(-1, 0, "■■■■ 현재 뱀 몸통 부분 두번째 색깔 ■■■■", color2);
	printCenter(-1, 2, "뱀의 몸통 부분 두번째 색을 설정하시려면 3을 눌러주세요.", 0x7);

	char colorChangeStr[100];
	sprintf(colorChangeStr, "■■■■ 현재 뱀 몸통 색 간격 : %-2d ■■■■", colorChange);
	printCenter(0, 0, colorChangeStr, 0x7);
	printCenter(0, 2, "뱀의 몸통 색 간격을 설정하시려면 4을 눌러주세요.", 0x7);

	showSnakePreview();

	printCenter(2, 0, "완료하셨다면 엔터를 눌러 메인화면으로 이동할 수 있습니다.", 0x8);

	int key;
	while (1) {
		if (_kbhit()) {
			key = _getch();
			if (key == '1') {
				printCenter(-3, 2, "좌우 방향키로 색을 변경할 수 있습니다. 완료하셨다면 엔터를 눌러주세요.", 0x7);
				while (1) {
					if (_kbhit()) {
						key = _getch();
						if (key == ARROW) {
							key = _getch();
							if (key == LEFT) {
								headColor = (headColor + 13) % 15 + 1;
								printCenter(-3, 0, "■■■■ 현재 뱀 머리 부분 색깔 ■■■■", headColor);
								showSnakePreview();
							}
							else if (key == RIGHT) {
								headColor = (headColor) % 15 + 1;
								printCenter(-3, 0, "■■■■ 현재 뱀 머리 부분 색깔 ■■■■", headColor);
								showSnakePreview();
							}
						}
						else if (key == ENTER) {
							printCenter(-3, 2, "             뱀의 머리 부분 색을 설정하시려면 1을 눌러주세요.             ", 0x7);
							break;
						}
					}
				}
			}
			else if (key == '2') {
				printCenter(-2, 2, "좌우 방향키로 색을 변경할 수 있습니다. 완료하셨다면 엔터를 눌러주세요.", 0x7);
				while (1) {
					if (_kbhit()) {
						key = _getch();
						if (key == ARROW) {
							key = _getch();
							if (key == LEFT) {
								color1 = (color1 + 13) % 15 + 1;
								printCenter(-2, 0, "■■■■ 현재 뱀 몸통 부분 첫번째 색깔 ■■■■", color1);
								showSnakePreview();
							}
							else if (key == RIGHT) {
								color1 = (color1) % 15 + 1;
								printCenter(-2, 0, "■■■■ 현재 뱀 몸통 부분 첫번째 색깔 ■■■■", color1);
								showSnakePreview();
							}
						}
						else if (key == ENTER) {
							printCenter(-2, 2, "          뱀의 몸통 부분 첫번째 색을 설정하시려면 2를 눌러주세요.          ", 0x7);
							break;
						}
					}
				}
			}
			else if (key == '3') {
				printCenter(-1, 2, "좌우 방향키로 색을 변경할 수 있습니다. 완료하셨다면 엔터를 눌러주세요.", 0x7);
				while (1) {
					if (_kbhit()) {
						key = _getch();
						if (key == ARROW) {
							key = _getch();
							if (key == LEFT) {
								color2 = (color2 + 13) % 15 + 1;
								printCenter(-1, 0, "■■■■ 현재 뱀 몸통 부분 두번째 색깔 ■■■■", color2);
								showSnakePreview();
							}
							else if (key == RIGHT) {
								color2 = (color2) % 15 + 1;
								printCenter(-1, 0, "■■■■ 현재 뱀 몸통 부분 두번째 색깔 ■■■■", color2);
								showSnakePreview();
							}
						}
						else if (key == ENTER) {
							printCenter(-1, 2, "          뱀의 몸통 부분 두번째 색을 설정하시려면 3를 눌러주세요.          ", 0x7);
							break;
						}
					}
				}
			}
			else if (key == '4') {
				printCenter(0, 2, "좌우 방향키로 값을 변경할 수 있습니다. 완료하셨다면 엔터를 눌러주세요.", 0x7);
				while (1) {
					if (_kbhit()) {
						key = _getch();
						if (key == ARROW) {
							key = _getch();
							if (key == LEFT) {
								colorChange--;
								if (colorChange < 1) colorChange = 1;
								showSnakePreview();
								sprintf(colorChangeStr, "■■■■ 현재 뱀 몸통 색 간격 : %-2d ■■■■", colorChange);
								printCenter(0, 0, colorChangeStr, 0x7);
							}
							else if (key == RIGHT) {
								colorChange++;
								if (colorChange > 10) colorChange = 10;
								showSnakePreview();
								sprintf(colorChangeStr, "■■■■ 현재 뱀 몸통 색 간격 : %-2d ■■■■", colorChange);
								printCenter(0, 0, colorChangeStr, 0x7);
							}
						}
						else if (key == ENTER) {
							printCenter(0, 2, "             뱀의 몸통 색 간격을 설정하시려면 4을 눌러주세요.             ", 0x7);
							break;
						}
					}
				}
			}
			else if (key == ENTER) {
				mainScreen(0);
				return;
			}
		}
	}

	return;
}

void howToGame() {
	cls();
	cursorView(0);
	printField(-5, "        게임 방법        ", 0xf);

	printCenter(-3, 0, "1. 조작 방법", 0x6);
	printCenter(-3, 2, "- 방향키를 누르면 뱀의 방향이 바뀝니다.", 0x7);

	printCenter(-3, 5, "2. 게임 오버 조건", 0x6);
	printCenter(-3, 7, "- 뱀의 머리가 자리 몸통에 닿으면 게임이 오버됩니다.", 0x7);
	printCenter(-3, 8, "- 뱀이 벽에 충돌하면 게임이 오버됩니다.", 0x7);

	printCenter(-3, 11, "3. 게임 방법 및 아이템/장애물 설명", 0x6);
	printCenter(-3, 13, "- 사과(◐)를 먹으면 꼬리가 길어지고 속도가 빨라지며, 점수를 많이 얻고 다음 스테이지로 넘어갑니다.", 0x7);
	printCenter(-3, 14, "- 거미줄(※)을 밟으면 일시적으로 속도가 50% 느려지고 점수가 일부 깎입니다.", 0x7);
	printCenter(-3, 15, "- 얼음(▨)을 밟으면 미끄러져서 방향이 바뀝니다.", 0x7);
	printCenter(-3, 16, "- 이 외에도 많은 요소들이 있습니다. 최대한 오래 버텨서 가장 많은 점수를 획득해보세요!", 0x7);

	printCenter(-3, 20, "메인화면으로 돌아가시려면 엔터를 눌러주세요.", 0x8);
	setColor(0x0, 0x0);
	while (1) {
		if (_kbhit()) { //엔터 입력 대기
			if (_getch() == ENTER) break;
		}
	}
	setColor(0xf, 0x0);
	mainScreen(0);
}

void gameOver() {
	Sleep(500); //왜 죽었는지 보여주기 위한 대기시간
	cls();
	setColor(0xf, 0x0);
	printCenter(0, -2, "-- 게임 오버! --", 0xf);
	char scoreView[50];
	sprintf(scoreView, "점수 : %d", score);
	printCenter(0, 0, scoreView, 0x6);
	if (score > bestScore) {
		bestScore = score;
		printCenter(0, 3, "최고기록 갱신!", 0x8);
	}
	sprintf(scoreView, " 최고점수 : %d  ", bestScore);
	printCenter(0, 1, scoreView, 0x6);
	clearGame();
	setColor(0x7, 0x0);
	Sleep(1000);
	printCenter(0, 5, "메인으로 돌아가려면 엔터를 누르세요", 0x8);
	while (1) {
		if (_kbhit()) { //엔터 입력 대기
			if (_getch() == ENTER) {
				mainScreen(0);
				return;
			}
		}
	}
}

void start() {
	cls();
	setColor(0xf, 0xf);
	//맵 테두리 그리기
	for (int i = 2; i < MAP_WIDTH + 2; i++) {
		gotoxy(i * 2, MAP_HEIGHT + 2);
		printf("  ");
		gotoxy(i * 2, 1);
		printf("  ");
	}
	for (int i = 1; i < MAP_HEIGHT + 3; i++) {
		gotoxy(MAP_WIDTH * 2 + 4, i);
		printf("  ");
		gotoxy(2, i);
		printf("  ");
	}
	//시작시 (1, 1) 좌표부터 뱀 생성
	for (int i = 0; i < START_SNAKE_LEN; i++) {
		push(i, 0);
	}
	//변수 초기화
	count = 0;
	playTime = 0;
	score = 0;
	stage = 1;
	int x, y, vecX = 1, vecY = 0;
	int key;
	DWORD startTime, execTime = 0;
	//난이도에 따른 변수 변화
	switch (difficulty) {
	case 1: //어려움
		originalSpeed += 4;
		for (int i = 0; i < 5; i++) push(START_SNAKE_LEN + i, 0);
		break;
	case 2: //매우 어려움
		originalSpeed += 10;
		for (int i = 0; i < 8; i++) push(START_SNAKE_LEN + i, 0);
		break;
	default: //보통 (기본값)
		break;
	}
	//사과 1개 생성
	putItem(2);
	while (1) {
		Sleep(max(0, 10 - (int)execTime));
		playTime += 10;
		startTime = timeGetTime();

		//오른쪽 상단에 정보 출력
		printInfo(0, "┌──────── 점수 ────────┐ ┌──────── 시간 ────────┐", 0xf);
		char scoreView[50];
		int playSec = playTime / 1000;
		int hours = playSec / 3600;
		int mins = playSec / 60 % 60;
		int secs = playSec % 60;
		sprintf(scoreView, "│ %20d │ │       %2d:%2d:%-8d │", score, hours, mins, secs);
		printInfo(1, scoreView, 0xf);
		printInfo(2, "└──────────────────────┘ └──────────────────────┘", 0xf);

		printInfo(3, "┌────── 스테이지 ──────┐ ┌────── 최고점수 ──────┐", 0xf);
		sprintf(scoreView, "│ %20d │ │ %20d │", stage, bestScore);
		printInfo(4, scoreView, 0xf);
		printInfo(5, "└──────────────────────┘ └──────────────────────┘", 0xf);

		if (!vectorChanged && _kbhit()) {
			//방향키 감지 부분
			key = _getch();
			if (key == ARROW) {
				key = _getch();
				if (key == UP && vecY != 1) {
					vecY = -1;
					vecX = 0;
				}
				else if (key == DOWN && vecY != -1) {
					vecY = 1;
					vecX = 0;
				}
				else if (key == LEFT && vecX != 1) {
					vecX = -1;
					vecY = 0;
				}
				else if (key == RIGHT && vecX != -1) {
					vecX = 1;
					vecY = 0;
				}
				vectorChanged = 1;
			}
		}

		//속도 제어 부분
		speed = originalSpeed;
		if (playTime - gotWeb < 3000 && gotWeb != -1) {
			//거미줄 밟고 나서 3초간
			speed /= 2; //속도 50% 감소
		}


		if (playTime - gotWeb == 1000) {
			//거미줄 밟고 나서 1초 뒤
			clearInfo(8);
		}

		if (playTime - gotWeb == 1000) {
			//얼음 밟고 나서 1초 뒤
			clearInfo(9);
		}

		if (playTime - gotApple == 1000) {
			//사과 섭취 후 1초 뒤
			clearInfo(7);
		}

		if (playTime % 1000 == 0) score++; //1초마다 점수 1 증가

		if (playTime % (1000 / speed) < 10) {
			//뱀 이동 부분
			count++; //움직일때마다 count 증가
			x = snake[snakeLen - 1][0];
			y = snake[snakeLen - 1][1];
			int item = map[y + vecY][x + vecX];
			short result = push(x + vecX, y + vecY);
			if (result == 0) {
				//뱀 충돌
				gameOver();
			}
			shift();
			if (item == 2) {
				//사과 섭취
				printInfo(7, " 사과를 먹었다!", 0xc);
				gotApple = playTime;
				//사과 섭취 시 기본 10스테이지(난이도에 따라서 8, 6)마다 속도 1 증가
				if (stage % (10 - difficulty * 2) == 0) originalSpeed += 1;
				addSnakeLen(1 + difficulty); //사과 섭취 시 길이 기본적으로 1(난이도에 따라서 2, 3) 증가
				score += 400 + rand() % 11;
				if (stage <= 5) putItem(3); //5스테이지 이전동안은 한 스테이지당 거미줄 1개 생성
				else if (stage > 5 && stage % 2 == 0) putItem(3); //5스테이지 이후부턴 2스테이지마다 거미줄 1개 생성
				if (stage >= 20 - difficulty * 5 && stage % 4 == 0) putItem(4); //기본 20스테이지(난이도에 따라서 15, 10) 이후부터 4스테이지마다 얼음 1개 생성
				putItem(2);
				stage++;
			}
			else if (item == 3) {
				//거미줄 밟음
				printInfo(8, " 거미줄을 밟았다.", 0x7);
				gotWeb = playTime;
				score = (int)((double)score * 0.99);
			}
			else if (item == 4) {
				//얼음 밟음
				printInfo(9, " 얼음을 밟아 미끄러졌다.", 0x9);
				gotIce = playTime;
				if (vecX) {
					vecX = 0;
					vecY = rand() % 2;
					if (!vecY) vecY = -1;
				}
				else if (vecY) {
					vecY = 0;
					vecX = rand() % 2;
					if (!vecX) vecX = -1;
				}
				vectorChanged = 1;
			}
			vectorChanged = 0;
			//한 번 움직여야 방향을 다시 바꿀 수 있음.
			//너무 빠르게 방향을 바꿀 때 방향이 안 바뀌었는데 바뀐걸로 인식을 해서 방향을 뒤로 바꾸는게 안 막히는 경우가 있음
		}

		execTime = timeGetTime() - startTime;
	}
}