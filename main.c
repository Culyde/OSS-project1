#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4

void titleDraw();
void gotoxy();
void init();
int menuDraw();
int keyControl();
void infoDraw();
void init() {
	system("mode con cols=56 lines=20 | title DINOGAME");
}

void titleDraw(){
	printf("\n\n\n");
	printf("               #######      ##    ##      ##    ######        ######          #         ##        ##  #########\n");
	printf("               ##     ##    ##    ## #    ##   ##    ##     ##     ##        ###        # #      # #  #\n");
	printf("               ##      ##   ##    ##  #   ##   ##    ##    ##       ##      ## ##       #  #    #  #  #\n");
	printf("               ##      ##   ##    ##   #  ##   ##    ##    ##              ##   ##      #   #  #   #  #########\n");
	printf("               ##      ##   ##    ##   #  ##   ##    ##    ##    #####    #########     #    ##    #  #\n");
	printf("               ##     ##    ##    ##    # ##   ##    ##     ##     ##    ##       ##    #          #  #\n");
	printf("               #######      ##    ##     ###    ######       #######    ##         ##   #          #  #########\n");
}

void gotoxy(int x, int y){
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들가져오기
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

int menuDraw() {
	int x = 50, y = 20;
	gotoxy(x, y);
	printf("   > GAME START");
	gotoxy(x, y+1);
	printf("     CHARCTERS");
	gotoxy(x+2, y+2);
	printf("    RECORDS");
	gotoxy(x + 2, y + 3);
	printf("   GAME RULE");
	gotoxy(x+2, y+4);
	printf("     EXIT");

	while (1) {
		int n = keyControl();
		switch (n) {
		case UP: {
			if (y > 20) {
				gotoxy(x+3, y);
				printf(" ");
				gotoxy(x+3, --y);
				printf(">");
			}
			break;
		}
		case DOWN: {
			if (y < 24) {
				gotoxy(x + 3, y);
				printf(" ");
				gotoxy(x + 3, ++y);
				printf(">");
			}
			break;
		}
		case SUBMIT: {
			return y - 20;
			}
		}
	}
}

int keyControl(){ //키를 컨트롤하는 함수
	char temp = getch();
	if(temp == 'w' || temp == 'W'){
		return UP;
	}
	else if(temp == 'a' || temp == 'A') {
		return LEFT;
	}
	else if(temp == 's' || temp == 'S') {
		return DOWN;
	}
	else if(temp == 'd' || temp == 'D') {
		return RIGHT;
	}
	else if (temp == ' ') { // 엔터키가 선택버튼
		return SUBMIT;
	}
}

void infoDraw() {
	system("cls");
	printf("\n\n");
	printf("                                                           [ 조작법 ]\n\n");
	printf("                                                        점프 : Space Bar\n\n");
	printf("                       다가오는 장애물을 점프를 통해 피하고 오래 살수록 점수가 높아지는 횡스크롤 게임입니다.\n\n\n\n");
	printf("                                스 페 이 스 바 를  누 르 면  메 인 화 면 으 로  이 동 합 니 다.");
	
	while (1) {
		if (keyControl() == SUBMIT) {
			break;
		}
	}
}

void charDraw() {
	system("cls");
	int x = 50, y = 5;
	gotoxy(x, y);
	printf("   > 티라노사우르스");
	gotoxy(x, y + 3);
	printf("     오리");
	gotoxy(x , y + 6);
	printf("     토끼");

	while (1) {
		int n = keyControl();
		switch (n) {
		case UP: {
			if (y > 5) {
				gotoxy(x + 3, y);
				printf(" ");
				gotoxy(x + 3, y-=3);
				printf(">");
			}
			break;
		}
		case DOWN: {
			if (y <  11) {
				gotoxy(x + 3, y);
				printf(" ");
				gotoxy(x + 3, y+=3);
				printf(">");
			}
			break;
		}
		case SUBMIT: {
			return 0;
			}
		}
	}
}

int main()
{
  int menuCode = menuDraw();
		if (menuCode == 0) {

			}
		else if (menuCode == 1) {
			charDraw();
		}
		else if (menuCode == 2) {

		}
		else if (menuCode == 3) {
			infoDraw();
		}
		else if (menuCode == 4) {
			return 0;
		}
		system("cls");
	
  titleDraw();
  menuDraw();
  keyControl();
  return 0;
}
