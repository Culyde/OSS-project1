#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

void titleDraw();
void gotoxy();
void init();
void menuDraw();

void init() {
	system("mode con cols=56 lines=20 | title DINOGAME");
}

void titleDraw(){
	printf("\n\n\n");
	printf("               #######      #    ##      #   ######        ########          #         ##        ##  #########\n");
	printf("               #      #     #    #  #    #  ##    ##     ###     ###        ###        # #      # #  #\n");
	printf("               #       #    #    #   #   #  ##    ##    ##                 ## ##       #  #    #  #  #\n");
	printf("               #       #    #    #    #  #  ##    ##   ###    #######     ##   ##      #   #  #   #  #########\n");
	printf("               #       #    #    #    #  #  ##    ##    ##    ## ###     #########     #    ##    #  #\n");
	printf("               #      #     #    #     # #  ##    ##     ###   ####     ##       ##    #          #  #\n");
	printf("               #######      #    #      ##   ######       #######      ##         ##   #          #  #########\n");
}

void gotoxy(int x, int y){
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들가져오기
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

void menuDraw() {
	gotoxy(50, 12);
	printf("> Game  start");
	gotoxy(52, 13);
	printf("  Records");
	gotoxy(52, 14);
	printf("  Game Rules");
	gotoxy(52, 15);
	printf("   EXIT   ");
}

int main()
{
  titleDraw();
  menuDraw();
  return 0;
}
