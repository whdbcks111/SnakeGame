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

	printCenter(-5, 0, "����������  ����    ��    ������    ��    ��  ����������", color1);
	printCenter(-5, 1, "��          ��  ��  ��  ��      ��  ��  ��    ��        ", color1);
	printCenter(-5, 2, "����������  ��  ��  ��  ����������  ����      ����������", color1);
	printCenter(-5, 3, "        ��  ��  ��  ��  ��      ��  ��  ��    ��        ", color1);
	printCenter(-5, 4, "����������  ��    ����  ��      ��  ��    ��  ����������", color1);

	printCenter(-5, 6, "  ������      ������    ����  ����  ����������", color2);
	printCenter(-5, 7, "��      ��  ��      ��  ��  ��  ��  ��        ", color2);
	printCenter(-5, 8, "��          ����������  ��  ��  ��  ����������", color2);
	printCenter(-5, 9, "��    ��    ��      ��  ��  ��  ��  ��        ", color2);
	printCenter(-5, 10, "��      ��  ��      ��  ��      ��  ��        ", color2);
	printCenter(-5, 11, "  ��������  ��      ��  ��      ��  ����������", color2);
	//ū SNAKE GAME ���� ���

	char scoreView[100];
	sprintf(scoreView, "�ְ����� : %d", bestScore);
	printCenter(-1, 0, scoreView, 0x7);

	char btn[10][50];
	strcpy(btn[0], "���� ����");
	strcpy(btn[1], "���� ���");
	strcpy(btn[2], "�� ���� �� ��� ����");
	char diffStr[100];
	char diffNames[3][20] = { "����", "�����", "�ſ� �����" };
	sprintf(diffStr, "���� ���̵� : %s", diffNames[difficulty]);
	strcpy(btn[3], diffStr);
	strcpy(btn[4], "���� ����");
	int key, select = selected, max_select = 4;
	char str[50];

	for (int i = 0; i <= max_select; i++) {
		sprintf(str, "    %s    ", btn[i]);
		printField(i, str, 0x8);
	}
	sprintf(str, "  > %s    ", btn[select]);
	printField(select, str, 0xf);

	printCenter(max_select + 1, 0, "����Ű�� ��ư�� �����ϰ� ���͸� ��������.", 0x8);

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
	printCenterSnake(1, 2, "�� �̸����� : ");
}

void customizingScreen() {
	cls();
	cursorView(0);
	printField(-5, "        Ŀ���͸���¡        ", 0xf);

	printCenter(-3, 0, "����� ���� �� �Ӹ� �κ� ���� �����", headColor);
	printCenter(-3, 2, "���� �Ӹ� �κ� ���� �����Ͻ÷��� 1�� �����ּ���.", 0x7);

	printCenter(-2, 0, "����� ���� �� ���� �κ� ù��° ���� �����", color1);
	printCenter(-2, 2, "���� ���� �κ� ù��° ���� �����Ͻ÷��� 2�� �����ּ���.", 0x7);

	printCenter(-1, 0, "����� ���� �� ���� �κ� �ι�° ���� �����", color2);
	printCenter(-1, 2, "���� ���� �κ� �ι�° ���� �����Ͻ÷��� 3�� �����ּ���.", 0x7);

	char colorChangeStr[100];
	sprintf(colorChangeStr, "����� ���� �� ���� �� ���� : %-2d �����", colorChange);
	printCenter(0, 0, colorChangeStr, 0x7);
	printCenter(0, 2, "���� ���� �� ������ �����Ͻ÷��� 4�� �����ּ���.", 0x7);

	showSnakePreview();

	printCenter(2, 0, "�Ϸ��ϼ̴ٸ� ���͸� ���� ����ȭ������ �̵��� �� �ֽ��ϴ�.", 0x8);

	int key;
	while (1) {
		if (_kbhit()) {
			key = _getch();
			if (key == '1') {
				printCenter(-3, 2, "�¿� ����Ű�� ���� ������ �� �ֽ��ϴ�. �Ϸ��ϼ̴ٸ� ���͸� �����ּ���.", 0x7);
				while (1) {
					if (_kbhit()) {
						key = _getch();
						if (key == ARROW) {
							key = _getch();
							if (key == LEFT) {
								headColor = (headColor + 13) % 15 + 1;
								printCenter(-3, 0, "����� ���� �� �Ӹ� �κ� ���� �����", headColor);
								showSnakePreview();
							}
							else if (key == RIGHT) {
								headColor = (headColor) % 15 + 1;
								printCenter(-3, 0, "����� ���� �� �Ӹ� �κ� ���� �����", headColor);
								showSnakePreview();
							}
						}
						else if (key == ENTER) {
							printCenter(-3, 2, "             ���� �Ӹ� �κ� ���� �����Ͻ÷��� 1�� �����ּ���.             ", 0x7);
							break;
						}
					}
				}
			}
			else if (key == '2') {
				printCenter(-2, 2, "�¿� ����Ű�� ���� ������ �� �ֽ��ϴ�. �Ϸ��ϼ̴ٸ� ���͸� �����ּ���.", 0x7);
				while (1) {
					if (_kbhit()) {
						key = _getch();
						if (key == ARROW) {
							key = _getch();
							if (key == LEFT) {
								color1 = (color1 + 13) % 15 + 1;
								printCenter(-2, 0, "����� ���� �� ���� �κ� ù��° ���� �����", color1);
								showSnakePreview();
							}
							else if (key == RIGHT) {
								color1 = (color1) % 15 + 1;
								printCenter(-2, 0, "����� ���� �� ���� �κ� ù��° ���� �����", color1);
								showSnakePreview();
							}
						}
						else if (key == ENTER) {
							printCenter(-2, 2, "          ���� ���� �κ� ù��° ���� �����Ͻ÷��� 2�� �����ּ���.          ", 0x7);
							break;
						}
					}
				}
			}
			else if (key == '3') {
				printCenter(-1, 2, "�¿� ����Ű�� ���� ������ �� �ֽ��ϴ�. �Ϸ��ϼ̴ٸ� ���͸� �����ּ���.", 0x7);
				while (1) {
					if (_kbhit()) {
						key = _getch();
						if (key == ARROW) {
							key = _getch();
							if (key == LEFT) {
								color2 = (color2 + 13) % 15 + 1;
								printCenter(-1, 0, "����� ���� �� ���� �κ� �ι�° ���� �����", color2);
								showSnakePreview();
							}
							else if (key == RIGHT) {
								color2 = (color2) % 15 + 1;
								printCenter(-1, 0, "����� ���� �� ���� �κ� �ι�° ���� �����", color2);
								showSnakePreview();
							}
						}
						else if (key == ENTER) {
							printCenter(-1, 2, "          ���� ���� �κ� �ι�° ���� �����Ͻ÷��� 3�� �����ּ���.          ", 0x7);
							break;
						}
					}
				}
			}
			else if (key == '4') {
				printCenter(0, 2, "�¿� ����Ű�� ���� ������ �� �ֽ��ϴ�. �Ϸ��ϼ̴ٸ� ���͸� �����ּ���.", 0x7);
				while (1) {
					if (_kbhit()) {
						key = _getch();
						if (key == ARROW) {
							key = _getch();
							if (key == LEFT) {
								colorChange--;
								if (colorChange < 1) colorChange = 1;
								showSnakePreview();
								sprintf(colorChangeStr, "����� ���� �� ���� �� ���� : %-2d �����", colorChange);
								printCenter(0, 0, colorChangeStr, 0x7);
							}
							else if (key == RIGHT) {
								colorChange++;
								if (colorChange > 10) colorChange = 10;
								showSnakePreview();
								sprintf(colorChangeStr, "����� ���� �� ���� �� ���� : %-2d �����", colorChange);
								printCenter(0, 0, colorChangeStr, 0x7);
							}
						}
						else if (key == ENTER) {
							printCenter(0, 2, "             ���� ���� �� ������ �����Ͻ÷��� 4�� �����ּ���.             ", 0x7);
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
	printField(-5, "        ���� ���        ", 0xf);

	printCenter(-3, 0, "1. ���� ���", 0x6);
	printCenter(-3, 2, "- ����Ű�� ������ ���� ������ �ٲ�ϴ�.", 0x7);

	printCenter(-3, 5, "2. ���� ���� ����", 0x6);
	printCenter(-3, 7, "- ���� �Ӹ��� �ڸ� ���뿡 ������ ������ �����˴ϴ�.", 0x7);
	printCenter(-3, 8, "- ���� ���� �浹�ϸ� ������ �����˴ϴ�.", 0x7);

	printCenter(-3, 11, "3. ���� ��� �� ������/��ֹ� ����", 0x6);
	printCenter(-3, 13, "- ���(��)�� ������ ������ ������� �ӵ��� ��������, ������ ���� ��� ���� ���������� �Ѿ�ϴ�.", 0x7);
	printCenter(-3, 14, "- �Ź���(��)�� ������ �Ͻ������� �ӵ��� 50% �������� ������ �Ϻ� ���Դϴ�.", 0x7);
	printCenter(-3, 15, "- ����(��)�� ������ �̲������� ������ �ٲ�ϴ�.", 0x7);
	printCenter(-3, 16, "- �� �ܿ��� ���� ��ҵ��� �ֽ��ϴ�. �ִ��� ���� ���߼� ���� ���� ������ ȹ���غ�����!", 0x7);

	printCenter(-3, 20, "����ȭ������ ���ư��÷��� ���͸� �����ּ���.", 0x8);
	setColor(0x0, 0x0);
	while (1) {
		if (_kbhit()) { //���� �Է� ���
			if (_getch() == ENTER) break;
		}
	}
	setColor(0xf, 0x0);
	mainScreen(0);
}

void gameOver() {
	Sleep(500); //�� �׾����� �����ֱ� ���� ���ð�
	cls();
	setColor(0xf, 0x0);
	printCenter(0, -2, "-- ���� ����! --", 0xf);
	char scoreView[50];
	sprintf(scoreView, "���� : %d", score);
	printCenter(0, 0, scoreView, 0x6);
	if (score > bestScore) {
		bestScore = score;
		printCenter(0, 3, "�ְ��� ����!", 0x8);
	}
	sprintf(scoreView, " �ְ����� : %d  ", bestScore);
	printCenter(0, 1, scoreView, 0x6);
	clearGame();
	setColor(0x7, 0x0);
	Sleep(1000);
	printCenter(0, 5, "�������� ���ư����� ���͸� ��������", 0x8);
	while (1) {
		if (_kbhit()) { //���� �Է� ���
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
	//�� �׵θ� �׸���
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
	//���۽� (1, 1) ��ǥ���� �� ����
	for (int i = 0; i < START_SNAKE_LEN; i++) {
		push(i, 0);
	}
	//���� �ʱ�ȭ
	count = 0;
	playTime = 0;
	score = 0;
	stage = 1;
	int x, y, vecX = 1, vecY = 0;
	int key;
	DWORD startTime, execTime = 0;
	//���̵��� ���� ���� ��ȭ
	switch (difficulty) {
	case 1: //�����
		originalSpeed += 4;
		for (int i = 0; i < 5; i++) push(START_SNAKE_LEN + i, 0);
		break;
	case 2: //�ſ� �����
		originalSpeed += 10;
		for (int i = 0; i < 8; i++) push(START_SNAKE_LEN + i, 0);
		break;
	default: //���� (�⺻��)
		break;
	}
	//��� 1�� ����
	putItem(2);
	while (1) {
		Sleep(max(0, 10 - (int)execTime));
		playTime += 10;
		startTime = timeGetTime();

		//������ ��ܿ� ���� ���
		printInfo(0, "������������������ ���� ������������������ ������������������ �ð� ������������������", 0xf);
		char scoreView[50];
		int playSec = playTime / 1000;
		int hours = playSec / 3600;
		int mins = playSec / 60 % 60;
		int secs = playSec % 60;
		sprintf(scoreView, "�� %20d �� ��       %2d:%2d:%-8d ��", score, hours, mins, secs);
		printInfo(1, scoreView, 0xf);
		printInfo(2, "������������������������������������������������ ������������������������������������������������", 0xf);

		printInfo(3, "�������������� �������� �������������� �������������� �ְ����� ��������������", 0xf);
		sprintf(scoreView, "�� %20d �� �� %20d ��", stage, bestScore);
		printInfo(4, scoreView, 0xf);
		printInfo(5, "������������������������������������������������ ������������������������������������������������", 0xf);

		if (!vectorChanged && _kbhit()) {
			//����Ű ���� �κ�
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

		//�ӵ� ���� �κ�
		speed = originalSpeed;
		if (playTime - gotWeb < 3000 && gotWeb != -1) {
			//�Ź��� ��� ���� 3�ʰ�
			speed /= 2; //�ӵ� 50% ����
		}


		if (playTime - gotWeb == 1000) {
			//�Ź��� ��� ���� 1�� ��
			clearInfo(8);
		}

		if (playTime - gotWeb == 1000) {
			//���� ��� ���� 1�� ��
			clearInfo(9);
		}

		if (playTime - gotApple == 1000) {
			//��� ���� �� 1�� ��
			clearInfo(7);
		}

		if (playTime % 1000 == 0) score++; //1�ʸ��� ���� 1 ����

		if (playTime % (1000 / speed) < 10) {
			//�� �̵� �κ�
			count++; //�����϶����� count ����
			x = snake[snakeLen - 1][0];
			y = snake[snakeLen - 1][1];
			int item = map[y + vecY][x + vecX];
			short result = push(x + vecX, y + vecY);
			if (result == 0) {
				//�� �浹
				gameOver();
			}
			shift();
			if (item == 2) {
				//��� ����
				printInfo(7, " ����� �Ծ���!", 0xc);
				gotApple = playTime;
				//��� ���� �� �⺻ 10��������(���̵��� ���� 8, 6)���� �ӵ� 1 ����
				if (stage % (10 - difficulty * 2) == 0) originalSpeed += 1;
				addSnakeLen(1 + difficulty); //��� ���� �� ���� �⺻������ 1(���̵��� ���� 2, 3) ����
				score += 400 + rand() % 11;
				if (stage <= 5) putItem(3); //5�������� ���������� �� ���������� �Ź��� 1�� ����
				else if (stage > 5 && stage % 2 == 0) putItem(3); //5�������� ���ĺ��� 2������������ �Ź��� 1�� ����
				if (stage >= 20 - difficulty * 5 && stage % 4 == 0) putItem(4); //�⺻ 20��������(���̵��� ���� 15, 10) ���ĺ��� 4������������ ���� 1�� ����
				putItem(2);
				stage++;
			}
			else if (item == 3) {
				//�Ź��� ����
				printInfo(8, " �Ź����� ��Ҵ�.", 0x7);
				gotWeb = playTime;
				score = (int)((double)score * 0.99);
			}
			else if (item == 4) {
				//���� ����
				printInfo(9, " ������ ��� �̲�������.", 0x9);
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
			//�� �� �������� ������ �ٽ� �ٲ� �� ����.
			//�ʹ� ������ ������ �ٲ� �� ������ �� �ٲ���µ� �ٲ�ɷ� �ν��� �ؼ� ������ �ڷ� �ٲٴ°� �� ������ ��찡 ����
		}

		execTime = timeGetTime() - startTime;
	}
}