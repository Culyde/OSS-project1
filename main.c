#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

void titleDraw();
void gotoxy();
void init();
void menuDraw();
int keyControl();

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

void menuDraw() {
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
			return y - 12;
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

int main()
{
  titleDraw();
  menuDraw();
  return 0;
}
