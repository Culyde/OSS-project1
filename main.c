#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4

#define dinoX 0
#define dinoY 15

void titleDraw();
void gotoxy();
void init();
int menuDraw();
int keyControl();
void infoDraw();
void init() {
	system("mode con cols=56 lines=20 | title DINOGAME");
}

void titleDraw() {
    printf("\n\n\n");
    printf("           +=======================================================================================================+\n\n");
    printf("               #######      ##    ##      ##    ######        ######          #         ##        ##  #########\n");
    printf("               ##     ##    ##    ## #    ##   ##    ##     ##     ##        ###        # #      # #  ##\n");
    printf("               ##      ##   ##    ##  #   ##   ##    ##    ##       ##      ## ##       #  #    #  #  ##\n");
    printf("               ##      ##   ##    ##   #  ##   ##    ##    ##              ##   ##      #   #  #   #  #########\n");
    printf("               ##      ##   ##    ##   #  ##   ##    ##    ##    #####    #########     #    ##    #  ##\n");
    printf("               ##     ##    ##    ##    # ##   ##    ##     ##     ##    ##       ##    #          #  ##\n");
    printf("               #######      ##    ##     ###    ######       #######    ##         ##   #          #  #########\n\n");
    printf("           +=======================================================================================================+\n");
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
    gotoxy(x - 5, y - 3);
    printf(" +-------------------+\n");
    gotoxy(x - 5, y - 2);
    printf(" |     MAIN MENU     |\n");
    gotoxy(x - 5, y - 1);
    printf(" +-------------------+\n");
    gotoxy(x - 5, y);
    printf(" |   > GAME START    |");
    gotoxy(x - 5, y + 1);
    printf(" |     CHARACTERS    |");
    gotoxy(x - 5, y + 2);
    printf(" |     STAGES        |");
    gotoxy(x - 5, y + 3);
    printf(" |     RECORDS       |");
    gotoxy(x - 5, y + 4);
    printf(" |     GAME RULE     |");
    gotoxy(x - 5, y + 5);
    printf(" |     E X I T       |");
    gotoxy(x - 5, y + 6);
    printf(" +-------------------+");

    while (1) {
        int n = keyControl();
        switch (n) {
        case UP: {
            if (y > 20) {
                gotoxy(x, y);
                printf(" ");
                gotoxy(x, --y);
                printf(">");
            }
            break;
        }
        case DOWN: {
            if (y < 25) {
                gotoxy(x, y);
                printf(" ");
                gotoxy(x, ++y);
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

	int charDraw() {
	system("cls");
	int x = 30, y = 10;
	gotoxy(x, y);
	printf("> 티라노");
	gotoxy(25, dinoY);			printf("        $$$$$$$ \n");
	gotoxy(25, dinoY + 1);		printf("       $$ $$$$$$\n");
	gotoxy(25, dinoY + 2);		printf("       $$$$$$$$$\n");
	gotoxy(25, dinoY + 3);		printf("$      $$$      \n");
	gotoxy(25, dinoY + 4);		printf("$$     $$$$$$$  \n");
	gotoxy(25, dinoY + 5);		printf("$$$   $$$$$     \n");
	gotoxy(25, dinoY + 6);		printf(" $$  $$$$$$$$$$ \n");
	gotoxy(25, dinoY + 7);		printf(" $$$$$$$$$$$    \n");
	gotoxy(25, dinoY + 8);		printf("  $$$$$$$$$$    \n");
	gotoxy(25, dinoY + 9);		printf("    $$$$$$$$    \n");
	gotoxy(25, dinoY + 10);		printf("     $$$$$$     \n");
	gotoxy(25, dinoY + 11);		printf("     $    $$$    \n");
	gotoxy(25, dinoY + 12);		printf("     $$          ");
	
	gotoxy(x + 20, y);
	printf("   오리");
	gotoxy(47, dinoY);			printf("       ■■■■■\n");
	gotoxy(47, dinoY + 1);		printf("      ■■■■■■■\n");
	gotoxy(47, dinoY + 2);		printf("      ■■ ■■■■■\n");
	gotoxy(47, dinoY + 3);		printf("      ■■■■■■■■■■■■■\n");
	gotoxy(47, dinoY + 4);		printf("      ■■■■■■■■■■■■\n");
	gotoxy(47, dinoY + 5);		printf("*     ■■■■■\n");
	gotoxy(47, dinoY + 6);		printf("■      ■■■■■\n");
	gotoxy(47, dinoY + 7);		printf("■■      ■■■■■\n");
	gotoxy(47, dinoY + 8);		printf("■■■■■■■■■■■■■■\n");
	gotoxy(47, dinoY + 9);		printf("■■■■■■■■■■■■■■■\n");
	gotoxy(47, dinoY + 10);		printf("■■■■■■■■■■■■■■\n");
	gotoxy(47, dinoY + 11);		printf("  ■■■■■■■■■■■■\n");
	gotoxy(47, dinoY + 12);		printf("    ■■■■■■■\n");
	gotoxy(x + 40, y);
	printf("   토끼");
	gotoxy(x + 38, dinoY);			printf("       ## ##     \n");
	gotoxy(x + 38, dinoY + 1);		printf("       ## ##    \n");
	gotoxy(x + 38, dinoY + 2);		printf("       #####   \n");
	gotoxy(x + 38, dinoY + 3);		printf("      ### ####  \n");
	gotoxy(x + 38, dinoY + 4);		printf("      ########   \n");
	gotoxy(x + 38, dinoY + 5);		printf("     ######     \n");
	gotoxy(x + 38, dinoY + 6);		printf("##  ###########\n");
	gotoxy(x + 38, dinoY + 7);		printf("###########    \n");
	gotoxy(x + 38, dinoY + 8);		printf(" ##########    \n");
	gotoxy(x + 38, dinoY + 9);		printf("   ########    \n");
	gotoxy(x + 38, dinoY + 10);		printf("    #    ###    \n");
	gotoxy(x + 38, dinoY + 11);		printf("    ##          ");

	while (1) {
		int n = keyControl();
		switch (n) {
		case RIGHT: {
			if (x < 70 && x >= 30) {
				gotoxy(x , y);
				printf(" ");
				gotoxy(x += 20, y);
				printf(">");
			}
			break;
		}
		case LEFT: {
			if (x <= 70 && x > 30){
				gotoxy(x , y);
				printf(" ");
				gotoxy(x -= 20, y);
				printf(">");
			}
			break;
		}
		case SUBMIT: {
			system("cls");
			if (x == 30) {
				gotoxy(47, 10);
				printf("티라노를 선택하셨습니다.");
				gotoxy(28, 14);
				printf("[ 스 페 이 스 바 를  누 르 면  처 음 화 면 으 로  돌 아 갑 니 다. ]");
				if(keyControl()== SUBMIT)
				return 1;
			}
			else if (x == 50) {
				gotoxy(47, 10);
				printf("오리를 선택하셨습니다.");
				gotoxy(28, 14);
				printf("[ 스 페 이 스 바 를  누 르 면  처 음 화 면 으 로  돌 아 갑 니 다. ]");
				if (keyControl() == SUBMIT)
					return 2;
			}
			else if (x == 70) {
				gotoxy(47, 10);
				printf("토끼를 선택하셨습니다.");
				gotoxy(28, 14);
				printf("[ 스 페 이 스 바 를  누 르 면  처 음 화 면 으 로  돌 아 갑 니 다. ]");
				if (keyControl() == SUBMIT)
					return 3;
			}
			}
		}
	}
}


int main()
{
  titleDraw();
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
	

  menuDraw();
  keyControl();
  return 0;
}
