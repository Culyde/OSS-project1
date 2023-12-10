#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <mmsystem.h>
#include <time.h>
#pragma comment(lib, "winmm.lib")

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4

#define DINO_X 0
#define DINO_Y 15
#define TREE_X 94
#define TREE_Y 25
#define AIR_Y 13 // 공중 장애물 y 좌표

void setting();
void gotoxy(int, int);
void start();
int game(int);
void score(int);
int crashing();
int end(int);
int keyControl();
void reset();
void speedControl();
void pushpull();
void back_draw_city();
void back_draw_desert();
void back_draw_winter();

//공룡 관련 함수
void draw_Tyrano(int);
void draw_Duck(int);
void draw_rabbit(int);
void erase_dino();
void erase_foot();

//장애물 관련 함수
void tree();
void draw_tree();
void erase_tree();
void city();
void erase_city();
void draw_city();
void Snowman();
void draw_Snowman();
void erase_Snowman();
void airplain();
void draw_airplain();
void erase_airplain();

int treeX = TREE_X;
int dinoX = DINO_X;
int dinoY = DINO_Y;
int charChoise = 1; // 캐릭터를 선택했을 때 반환값을 저장하는 전역변수
int stageChoise = 1; // 스테이지를 선택했을 때 반환값을 저장하는 전역변수
int key = 0; //키보드 입력 받기
int now_score;
int last_score = 0;
int best_score = 0;
int temp;
int treeDecrement = 1;
//int random_number = 1;

void pushpull() {
    PlaySound(TEXT("dinogamebgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void titleDraw() {
    printf("\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    printf("         +=======================================================================================================+\n\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    printf("             #######      ##    ##      ##    ######        ######          #         ###        ###  #########\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    printf("             ##     ##    ##    ## #    ##   ##    ##     ##     ##        ###        ## ##    ## ##  ##\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    printf("             ##      ##   ##    ##  #   ##   ##    ##    ##       ##      ## ##       ##  ##  ##  ##  ##\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    printf("             ##      ##   ##    ##   #  ##   ##    ##    ##              ##   ##      ##   ####   ##  #########\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    printf("             ##      ##   ##    ##   #  ##   ##    ##    ##    #####    #########     ##    ##    ##  ##\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    printf("             ##     ##    ##    ##    # ##   ##    ##     ##     ##    ##       ##    ##          ##  ##\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    printf("             #######      ##    ##     ###    ######       #######    ##         ##   ##          ##  #########\n\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    printf("         +=======================================================================================================+\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void gotoxy(int x, int y) {
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
    printf(" |     GAME RULE     |");
    gotoxy(x - 5, y + 4);
    printf(" |     E X I T       |");
    gotoxy(x - 5, y + 5);
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
            if (y < 24) {
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

int keyControl() {
    char temp = _getch();

    if (temp == 'w' || temp == 'W') {
        return UP;
    }
    else if (temp == 'a' || temp == 'A') {
        return LEFT;
    }
    else if (temp == 's' || temp == 'S') {
        return DOWN;
    }
    else if (temp == 'd' || temp == 'D') {
        return RIGHT;
    }
    else if (temp == ' ') { // 엔터키가 선택버튼
        return SUBMIT;
    }
}

void infoDraw() {
    system("cls");
    printf("\n\n");
    printf("                                                          [ 조작법 ]\n\n");
    printf("                                                       점프 : Space Bar\n\n");
    printf("                       다가오는 장애물을 점프를 통해 피하고 오래 살수록 점수가 높아지는 횡스크롤 게임입니다.\n\n\n\n");
    printf("                             [ 스 페 이 스 바 를  누 르 면  메 인 화 면 으 로  이 동 합 니 다. ]");

    while (1) {
        if (keyControl() == SUBMIT) {
            break;
        }
    }
}

int infoStages() {
    system("cls");
    int x = 13, y = 10;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    gotoxy(12, 0);         printf("             ---------------------------------------------------------------------------");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    gotoxy(12, 1);         printf("                      ######  ########    ###     ######   ########  ######  ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    gotoxy(12, 2);         printf("                     ##    ##    ##      ## ##   ##    ##  ##       ##    ## ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    gotoxy(12, 3);         printf("                     ##          ##     ##   ##  ##        ##       ##       ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    gotoxy(12, 4);         printf("                      ######     ##    ##     ## ##   #### ######    ######  ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    gotoxy(12, 5);         printf("                           ##    ##    ######### ##    ##  ##             ## ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    gotoxy(12, 6);         printf("                           ##    ##    ##     ## ##    ##  ##       ##    ## ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    gotoxy(12, 7);         printf("                      ######     ##    ##     ##  ######   ########  ######  ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    gotoxy(12, 8);         printf("             ---------------------------------------------------------------------------");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

    gotoxy(13, y + 2);            printf("> 1. 사막");
    gotoxy(6, dinoY);          printf("            /\\\n");
    gotoxy(6, dinoY + 1);       printf("           /__\\\n");
    gotoxy(6, dinoY + 2);      printf("          /____\\\n");
    gotoxy(6, dinoY + 3);      printf("         /______\\\n");
    gotoxy(6, dinoY + 4);      printf("        /________\\\n");
    gotoxy(6, dinoY + 5);      printf("       /__________\\\n");
    gotoxy(6, dinoY + 6);      printf("      /____________\\\n");
    gotoxy(6, dinoY + 7);      printf("     /______________\\\n");
    gotoxy(6, dinoY + 8);      printf("    /________________\\\n");


    gotoxy(51, y + 2);         printf("    2. 겨울");
    gotoxy(37, dinoY);          printf("     *     *   *   *    *   *        *    *\n");
    gotoxy(36, dinoY + 1);       printf("*  *    *   *       |  *   *    *      *\n");
    gotoxy(40, dinoY + 2);           printf("*  *   *   *   / \\      *    *        *\n");
    gotoxy(37, dinoY + 3);        printf("     *   *  *  * /   \\  *      *     * \n");
    gotoxy(39, dinoY + 4);          printf("*    *    *   /     \\  *     *   *  *  \n");
    gotoxy(36, dinoY + 5);       printf(" *  *    *      /       \\   *     *    *   \n");
    gotoxy(37, dinoY + 6);        printf("  *    *    * /         \\ *   *   *  ");
    gotoxy(36, dinoY + 7);       printf("*    *   *    /^-^-^-^-^-^\\   *  *    *    \n");
    gotoxy(37, dinoY + 8);       printf("                   || \n");
    gotoxy(37, dinoY + 9);       printf("                   ||\n");
    gotoxy(38, dinoY + 10);       printf("                  JJ\n");



    gotoxy(92, y + 2);            printf("   3. 도시");
    gotoxy(88, dinoY);          printf("            ____\n");
    gotoxy(89, dinoY + 1);       printf("___________|  |__\n");
    gotoxy(88, dinoY + 2);      printf("/_________________\\\n");
    gotoxy(87, dinoY + 3);     printf("/___________________\\\n");
    gotoxy(86, dinoY + 4);    printf("/_____________________\\\n");
    gotoxy(88, dinoY + 5);      printf("|   ___     ___   |\n");
    gotoxy(88, dinoY + 6);      printf("|  |___|   |___|  |\n");
    gotoxy(88, dinoY + 7);      printf("|   ___     ___   |\n");
    gotoxy(88, dinoY + 8);      printf("|  |___|   |___|  |\n");
    gotoxy(88, dinoY + 9);      printf("|_________________|\n");

    while (1) {
        int n = keyControl();
        switch (n) {
        case RIGHT: {
            if (x < 93 && x >= 13) {
                gotoxy(x, y + 2);
                printf(" ");
                gotoxy(x += 40, y + 2);
                printf(">");
            }
            break;
        }
        case LEFT: {
            if (x <= 93 && x > 13) {
                gotoxy(x, y + 2);
                printf(" ");
                gotoxy(x -= 40, y + 2);
                printf(">");
            }
            break;
        }
        case SUBMIT: {
            system("cls");
            if (x == 13) {
                gotoxy(47, 5);
                printf("사막 맵을 선택하셨습니다.");
                gotoxy(28, 10);
                printf("[ 스 페 이 스 바 를  누 르 면  처 음 화 면 으 로  돌 아 갑 니 다. ]");
                gotoxy(50, dinoY);          printf("         ## \n");
                gotoxy(50, dinoY + 1);      printf("       # ## # \n");
                gotoxy(50, dinoY + 2);      printf("       ######  \n");
                gotoxy(50, dinoY + 3);      printf("         ##    \n");
                gotoxy(50, dinoY + 4);      printf("         ##    ");


                if (keyControl() == SUBMIT)
                    return stageChoise = 1;
            }
            else if (x == 53) {
                gotoxy(47, 5);
                printf("겨울 맵을 선택하셨습니다.");
                gotoxy(28, 10);
                printf("[ 스 페 이 스 바 를  누 르 면  처 음 화 면 으 로  돌 아 갑 니 다. ]");
                gotoxy(47, dinoY);          printf("         _==_\n");
                gotoxy(47, dinoY + 1);      printf("        (o o )\n");
                gotoxy(47, dinoY + 2);      printf("        =(  )=\n");
                gotoxy(47, dinoY + 3);      printf("        (    ) \n");
                gotoxy(47, dinoY + 4);      printf("       (      ) \n");

                if (keyControl() == SUBMIT)
                    return stageChoise = 2;
            }
            else if (x == 93) {
                gotoxy(47, 5);
                printf("도시 맵을 선택하셨습니다.");
                gotoxy(28, 10);
                printf("[ 스 페 이 스 바 를  누 르 면  처 음 화 면 으 로  돌 아 갑 니 다. ]");
                gotoxy(47, dinoY);          printf("       ____      \n");
                gotoxy(47, dinoY + 1);      printf("      /    \\   \n");
                gotoxy(47, dinoY + 2);      printf("      ------    \n");
                gotoxy(47, dinoY + 3);      printf("       |##| \n");
                gotoxy(47, dinoY + 4);      printf("       |  |  \n");
                if (keyControl() == SUBMIT)
                    return stageChoise = 3;
            }
        }
        }
    }
}

int charDraw() {
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int x = 13, y = 10;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    gotoxy(12, 0);         printf("----------------------------------------------------------------------------------------------");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    gotoxy(12, 1);         printf(" #####   ##     ##    ###    ########     ###     ######  ######## ######## ########   ######");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    gotoxy(12, 2);         printf("##    ## ##     ##   ## ##   ##     ##   ## ##   ##    ##    ##    ##       ##     ## ##    ##");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    gotoxy(12, 3);         printf("##       ##     ##  ##   ##  ##     ##  ##   ##  ##          ##    ##       ##     ## ##   ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    gotoxy(12, 4);         printf("##       ######### ##     ## ########  ##     ## ##          ##    #######  #######    #######");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    gotoxy(12, 5);         printf("##       ##     ## ######### ##   ##   ######### ##          ##    ##       ##   ##         ##");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    gotoxy(12, 6);         printf("##    ## ##     ## ##     ## ##    ##  ##     ## ##    ##    ##    ##       ##    ##  ##    ##");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    gotoxy(12, 7);         printf(" #####   ##     ## ##     ## ##     ## ##     ##  ######     ##    ######## ##     ##  ######");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    gotoxy(12, 8);         printf("----------------------------------------------------------------------------------------------");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

    gotoxy(13, y + 2);          printf("> 1. 티라노");
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
    gotoxy(11, dinoY);          printf("        $$$$$$$ \n");
    gotoxy(11, dinoY + 1);      printf("       $$ $$$$$$\n");
    gotoxy(11, dinoY + 2);      printf("       $$$$$$$$$\n");
    gotoxy(11, dinoY + 3);      printf("$      $$$      \n");
    gotoxy(11, dinoY + 4);      printf("$$     $$$$$$$  \n");
    gotoxy(11, dinoY + 5);      printf("$$$   $$$$$     \n");
    gotoxy(11, dinoY + 6);      printf(" $$  $$$$$$$$$$ \n");
    gotoxy(11, dinoY + 7);      printf(" $$$$$$$$$$$    \n");
    gotoxy(11, dinoY + 8);      printf("  $$$$$$$$$$    \n");
    gotoxy(11, dinoY + 9);      printf("    $$$$$$$$    \n");
    gotoxy(11, dinoY + 10);     printf("     $$$$$$     \n");
    gotoxy(11, dinoY + 11);     printf("     $    $$$    \n");
    gotoxy(11, dinoY + 12);     printf("     $$          ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

    gotoxy(53, y + 2);         printf("  2. 오리");
    gotoxy(47, dinoY - 1);      printf("           $$$$$\n");
    gotoxy(47, dinoY);          printf("          $$$$$$$\n");
    gotoxy(47, dinoY + 1);      printf("          $$ $$$$$\n");
    gotoxy(47, dinoY + 2);      printf("          $$$$$\033[33m$$$$$$$\033[0m\n");
    gotoxy(47, dinoY + 3);      printf("          $$$$$\033[33m$$$$$$\033[0m\n");
    gotoxy(47, dinoY + 4);      printf("     *    $$$$$\n");
    gotoxy(47, dinoY + 5);      printf("     $     $$$$$\n");
    gotoxy(47, dinoY + 6);      printf("     $$     $$$$$\n");
    gotoxy(47, dinoY + 7);      printf("     $$$$$$$$$$$$$\n");
    gotoxy(47, dinoY + 8);      printf("      $$$$$$$$$$$$\n");
    gotoxy(47, dinoY + 9);      printf("      $$$$$$$$$$$$\n");
    gotoxy(47, dinoY + 10);     printf("       $$$$$$$$$$\n");
    gotoxy(47, dinoY + 11);     printf("         $$$$$$$\n");
    gotoxy(47, dinoY + 12);     printf("          \033[33m$    $$\033[0m\n");
    gotoxy(47, dinoY + 13);     printf("          \033[33m$$\033[0m");

    gotoxy(93, y + 2);          printf("  3. 토끼");
    gotoxy(88, dinoY - 1);      printf("       $\033[1;35m$\033[0m $\033[1;35m$\033[0m  \n");
    gotoxy(88, dinoY);          printf("       $\033[1;35m$\033[0m $\033[1;35m$\033[0m  \n");
    gotoxy(88, dinoY + 1);      printf("       $\033[1;35m$\033[0m $\033[1;35m$\033[0m  \n");
    gotoxy(88, dinoY + 2);      printf("       $\033[1;35m$\033[0m $\033[1;35m$\033[0m   \n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    gotoxy(88, dinoY + 3);      printf("       $$$$$$$  \n");
    gotoxy(88, dinoY + 4);      printf("      $$$$ $$$$ \n");
    gotoxy(88, dinoY + 5);      printf("      $$$$$$$$ \n");
    gotoxy(88, dinoY + 6);      printf("     $$$$$$$  \n");
    gotoxy(88, dinoY + 7);      printf("$$  $$$$$$$$$$$$\n");
    gotoxy(88, dinoY + 8);      printf("$$$$$$$$$$$$\n");
    gotoxy(88, dinoY + 9);      printf("$$$$$$$$$$$\n");
    gotoxy(88, dinoY + 10);     printf(" $$$$$$$$$$\n");
    gotoxy(88, dinoY + 11);     printf("   $$$$$$$\n");
    gotoxy(88, dinoY + 12);     printf("    $    $$$\n");
    gotoxy(88, dinoY + 13);     printf("    $$    ");
    while (1) {
        int n = keyControl();
        switch (n) {
        case RIGHT: {
            if (x < 93 && x >= 13) {
                gotoxy(x, y + 2);
                printf(" ");
                gotoxy(x += 40, y + 2);
                printf(">");
            }
            break;
        }
        case LEFT: {
            if (x <= 93 && x > 13) {
                gotoxy(x, y + 2);
                printf(" ");
                gotoxy(x -= 40, y + 2);
                printf(">");
            }
            break;
        }
        case SUBMIT: {
            system("cls");
            if (x == 13) {
                gotoxy(47, 5);
                printf("티라노를 선택하셨습니다.");
                gotoxy(28, 10);
                printf("[ 스 페 이 스 바 를  누 르 면  처 음 화 면 으 로  돌 아 갑 니 다. ]");
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
                gotoxy(47, dinoY);          printf("        $$$$$$$ \n");
                gotoxy(47, dinoY + 1);      printf("       $$ $$$$$$\n");
                gotoxy(47, dinoY + 2);      printf("       $$$$$$$$$\n");
                gotoxy(47, dinoY + 3);      printf("$      $$$      \n");
                gotoxy(47, dinoY + 4);      printf("$$     $$$$$$$  \n");
                gotoxy(47, dinoY + 5);      printf("$$$   $$$$$     \n");
                gotoxy(47, dinoY + 6);      printf(" $$  $$$$$$$$$$ \n");
                gotoxy(47, dinoY + 7);      printf(" $$$$$$$$$$$    \n");
                gotoxy(47, dinoY + 8);      printf("  $$$$$$$$$$    \n");
                gotoxy(47, dinoY + 9);      printf("    $$$$$$$$    \n");
                gotoxy(47, dinoY + 10);     printf("     $$$$$$     \n");
                gotoxy(47, dinoY + 11);     printf("     $    $$$    \n");
                gotoxy(47, dinoY + 12);     printf("     $$          ");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

                if (keyControl() == SUBMIT)
                    return charChoise = 1;
            }
            else if (x == 53) {
                gotoxy(47, 5);
                printf("오리를 선택하셨습니다.");
                gotoxy(28, 10);
                printf("[ 스 페 이 스 바 를  누 르 면  처 음 화 면 으 로  돌 아 갑 니 다. ]");
                               gotoxy(47, dinoY);          printf("         $$$$$\n");
                gotoxy(47, dinoY + 1);      printf("        $$$$$$$\n");
                gotoxy(47, dinoY + 2);      printf("        $$ $$$$$\n");
                gotoxy(47, dinoY + 3);      printf("        $$$$$\033[33m$$$$$$$\033[0m\n");
                gotoxy(47, dinoY + 4);      printf("        $$$$$\033[33m$$$$$$\033[0m\n");
                gotoxy(47, dinoY + 5);      printf("   *    $$$$$\n");
                gotoxy(47, dinoY + 6);      printf("   $     $$$$$\n");
                gotoxy(47, dinoY + 7);      printf("   $$     $$$$$\n");
                gotoxy(47, dinoY + 8);      printf("   $$$$$$$$$$$$$\n");
                gotoxy(47, dinoY + 9);      printf("    $$$$$$$$$$$$\n");
                gotoxy(47, dinoY + 10);     printf("    $$$$$$$$$$$$\n");
                gotoxy(47, dinoY + 11);     printf("     $$$$$$$$$$\n");
                gotoxy(47, dinoY + 12);     printf("       $$$$$$$\n");
                gotoxy(47, dinoY + 13);     printf("        \033[33m$    $$\033[0m\n");
                gotoxy(47, dinoY + 14);     printf("        \033[33m$$\033[0m");
                if (keyControl() == SUBMIT)
                    return charChoise = 2;
            }
            else if (x == 93) {
                gotoxy(47, 5);
                printf("토끼를 선택하셨습니다.");
                gotoxy(28, 10);
                printf("[ 스 페 이 스 바 를  누 르 면  처 음 화 면 으 로  돌 아 갑 니 다. ]");
                gotoxy(47, dinoY);          printf("          $\033[1;35m$\033[0m $\033[1;35m$\033[0m  \n");
                gotoxy(47, dinoY + 1);      printf("          $\033[1;35m$\033[0m $\033[1;35m$\033[0m  \n");
                gotoxy(47, dinoY + 2);      printf("          $\033[1;35m$\033[0m $\033[1;35m$\033[0m  \n");
                gotoxy(47, dinoY + 3);      printf("          $\033[1;35m$\033[0m $\033[1;35m$\033[0m  \n");
                gotoxy(47, dinoY + 4);      printf("          $$$$$$$  \n");
                gotoxy(47, dinoY + 5);      printf("         $$$$ $$$$ \n");
                gotoxy(47, dinoY + 6);      printf("         $$$$$$$$ \n");
                gotoxy(47, dinoY + 7);      printf("        $$$$$$$  \n");
                gotoxy(47, dinoY + 8);      printf("   $$  $$$$$$$$$$$$\n");
                gotoxy(47, dinoY + 9);      printf("   $$$$$$$$$$$$\n");
                gotoxy(47, dinoY + 10);     printf("    $$$$$$$$$$$\n");
                gotoxy(47, dinoY + 11);     printf("     $$$$$$$$$$\n");
                gotoxy(47, dinoY + 12);     printf("      $$$$$$$$\n");
                gotoxy(47, dinoY + 13);    printf("        $    $$$\n");
                gotoxy(47, dinoY + 14);    printf("        $$    ");
                if (keyControl() == SUBMIT)
                    return charChoise = 3;
            }
        }
        }
    }
}

int game(int tic) { //게임화면 메인 요소
    //srand(time(NULL));
    reset();
    score(tic);
    gotoxy(65, 0);
    printf("                     ");
    gotoxy(65, 1);
    printf("# Best Score : %d /", best_score);
    if (stageChoise == 1) {
        back_draw_desert();
        tree();
    }
    else if (stageChoise == 2) {
        back_draw_winter();
        Snowman();
    }
    else if (stageChoise == 3) {
        back_draw_city();
        //if(treeX <= 0)
        //random_number = rand() % 2; // 0 또는 1 중 하나의 값을 랜덤으로 생성

        //if (random_number == 0) {
        city(); // city 함수 실행
        //}
        //else {
        //    airplain(); // airplain 함수 실행
        //}
    }

    if (charChoise == 1)
        draw_Tyrano(tic);

    else if (charChoise == 2)
        draw_Duck(tic);

    else if (charChoise == 3)
        draw_rabbit(tic);

    Sleep(20); //0.02초 딜레이 예상
    tic++;

    return tic;
}

int crashing() {
    if (charChoise == 1) {
        if (stageChoise == 1) {
            if ((/*뒤에 닿는 판정*/dinoX + 2 <= treeX + 2 && /*앞에닿는 판정*/ dinoX + 16 >= treeX + 2) && dinoY + 12 >= TREE_Y + 2)
                return -1;
        }
        else if (stageChoise == 2) {
            if ((dinoX <= treeX + 2 && dinoX + 15 >= treeX + 2) && dinoY + 12 >= TREE_Y + 2)
                return -1;
        }
        else if (stageChoise == 3) {
            if ((dinoX + 2 <= treeX + 2 && dinoX + 15 >= treeX + 2) && dinoY + 12 >= TREE_Y + 2)
                return -1;
        }
    }
    if (charChoise == 2) {
        if (stageChoise == 1) {
            if ((dinoX + 2 <= treeX + 2 && dinoX + 16 >= treeX + 2) && dinoY + 12 >= TREE_Y + 2)
                return -1;
        }
        else if (stageChoise == 2) {
            if ((dinoX + 2 <= treeX + 2 && dinoX + 16 >= treeX + 2) && dinoY + 12 >= TREE_Y + 2)
                return -1;
        }
        else if (stageChoise == 3) {
            if ((dinoX + 2 <= treeX + 2 && dinoX + 16 >= treeX + 2) && dinoY + 12 >= TREE_Y + 2)
                return -1;
        }
    }
    if (charChoise == 3) {
        if (stageChoise == 1) {
            if ((dinoX + 2 <= treeX + 2 && dinoX + 13 >= treeX + 2) && dinoY + 12 >= TREE_Y + 2)
                return -1;
        }
        else if (stageChoise == 2) {
            if ((dinoX + 2 <= treeX + 2 && dinoX + 13 >= treeX + 2) && dinoY + 12 >= TREE_Y + 2)
                return -1;
        }
        else if (stageChoise == 3) {
            if ((dinoX + 2 <= treeX + 2 && dinoX + 13 >= treeX + 2) && dinoY + 12 >= TREE_Y + 2)
                return -1;
        }
    }
    else
        return 0;
}

void reset(void) {

    FILE* file = fopen("score.dat", "rt"); // score.dat파일을 연결 
    if (file == 0) { //파일이 없으면 걍 최고점수에 0을 넣음 
        best_score = 0;
    }
    else {
        fscanf(file, "%d", &best_score); // 파일이 열리면 최고점수를 불러옴 
        fclose(file); //파일 닫음 
    }
    now_score = 0;
}

void draw_Tyrano(int tic) {//티라노 그리기
    int toc = tic % 8;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
    //몸통
    gotoxy(dinoX, dinoY + 2);      printf("          $$$$$$$ \n");
    gotoxy(dinoX, dinoY + 3);      printf("         $$ $$$$$$$\n");
    gotoxy(dinoX, dinoY + 4);      printf("         $$$$$$$$$$\n");
    gotoxy(dinoX, dinoY + 5);      printf("  $       $$$$      \n");
    gotoxy(dinoX, dinoY + 6);      printf("  $$     $$$$$$$$  \n");
    gotoxy(dinoX, dinoY + 7);      printf("  $$$   $$$$$$     \n");
    gotoxy(dinoX, dinoY + 8);      printf("   $$  $$$$$$$$$$$ \n");
    gotoxy(dinoX, dinoY + 9);      printf("   $$$$$$$$$$$$ \n");
    gotoxy(dinoX, dinoY + 10);     printf("    $$$$$$$$$$$ \n");
    gotoxy(dinoX, dinoY + 11);     printf("      $$$$$$$$$\n");
    gotoxy(dinoX, dinoY + 12);     printf("       $$$$$$$\n");

    if (toc >= 0 && toc <= 3) //4tic 동안 유지
    {
        erase_foot();
        gotoxy(dinoX, dinoY + 13); //발 그리기
        printf("       $    $$$\n");
        printf("       $$     ");
    }
    else
    {
        erase_foot();
        gotoxy(dinoX, dinoY + 13); //발 그리기
        printf("       $$$  $  \n");
        printf("            $$");
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void draw_rabbit(int tic) { //토끼 그리기

    int toc = tic % 8;

    //몸통
    gotoxy(dinoX, dinoY);          printf("        $\033[1;35m$\033[0m $\033[1;35m$\033[0m  \n");
    gotoxy(dinoX, dinoY + 1);      printf("        $\033[1;35m$\033[0m $\033[1;35m$\033[0m  \n");
    gotoxy(dinoX, dinoY + 2);      printf("        $\033[1;35m$\033[0m $\033[1;35m$\033[0m  \n");
    gotoxy(dinoX, dinoY + 3);      printf("        $\033[1;35m$\033[0m $\033[1;35m$\033[0m  \n");
    gotoxy(dinoX, dinoY + 4);      printf("        $$$$$$  \n");
    gotoxy(dinoX, dinoY + 5);      printf("       $$$ $$$$ \n");
    gotoxy(dinoX, dinoY + 6);      printf("       $$$$$$$ \n");
    gotoxy(dinoX, dinoY + 7);      printf("      $$$$$$  \n");
    gotoxy(dinoX, dinoY + 8);      printf(" $$  $$$$$$$$$$$\n");
    gotoxy(dinoX, dinoY + 9);      printf(" $$$$$$$$$$$\n");
    gotoxy(dinoX, dinoY + 10);     printf("  $$$$$$$$$$\n");
    gotoxy(dinoX, dinoY + 11);     printf("   $$$$$$$$$\n");
    gotoxy(dinoX, dinoY + 12);     printf("    $$$$$$$$\n");

    //발 구르기 구현
    if (toc >= 0 && toc <= 3) //4tic 동안 유지
    {
        erase_foot();
        gotoxy(dinoX, dinoY + 13); //발 그리기
        printf("     $    $$$\n");
        printf("     $$    ");
    }
    else
    {
        erase_foot();
        gotoxy(dinoX, dinoY + 13); //발 그리기
        printf("     $$$  $   \n");
        printf("          $$");
    }
}

void draw_Duck(int tic) { //오리 그리기

    int toc = tic % 8;

    //몸통
    gotoxy(dinoX, dinoY);          printf("          $$$$$\n");
    gotoxy(dinoX, dinoY + 1);      printf("         $$$$$$$\n");
    gotoxy(dinoX, dinoY + 2);      printf("         $$ $$$$$\n");
    gotoxy(dinoX, dinoY + 3);      printf("         $$$$$\033[33m$$$$$$$\033[0m\n");
    gotoxy(dinoX, dinoY + 4);      printf("         $$$$$\033[33m$$$$$$\033[0m\n");
    gotoxy(dinoX, dinoY + 5);      printf("    *    $$$$$\n");
    gotoxy(dinoX, dinoY + 6);      printf("    $     $$$$$\n");
    gotoxy(dinoX, dinoY + 7);      printf("    $$     $$$$$\n");
    gotoxy(dinoX, dinoY + 8);      printf("    $$$$$$$$$$$$$\n");
    gotoxy(dinoX, dinoY + 9);      printf("     $$$$$$$$$$$$\n");
    gotoxy(dinoX, dinoY + 10);     printf("     $$$$$$$$$$$$\n");
    gotoxy(dinoX, dinoY + 11);     printf("      $$$$$$$$$$\n");
    gotoxy(dinoX, dinoY + 12);     printf("        $$$$$$$\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);


    //발 구르기 구현
    if (toc >= 0 && toc <= 3) //4tic 동안 유지
    {
        erase_foot();
        gotoxy(dinoX, dinoY + 13); //발 그리기
        printf("         $    $$\n");
        printf("         $$");
    }
    else
    {
        erase_foot();
        gotoxy(dinoX, dinoY + 13); //발 그리기
        printf("         $$  $\n");
        printf("              $$");
    }
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void erase_foot() { //발 지우기
    gotoxy(dinoX, dinoY + 13);
    printf("                 \n");
    printf("                 ");

}

void erase_dino() { //공룡 지우기
    for (int i = 0; i < 24; i++) {
        gotoxy(dinoX, 6 + i);
        printf("                             ");
    }
    erase_foot();
}

void back_draw_desert() {
    printf("\n\n");
    /*gotoxy(0, 4);*/  printf("        *       *                      *                *         *                *             *             *\n");
    /*gotoxy(0, 5);*/  printf("*                       *        *                  *                                         /\\       *        \n");
    /*gotoxy(0, 6);*/  printf("      *         *                          *               *             *                   /__\\           *       \n");
    /*gotoxy(0, 7);*/  printf("             /\\                   *                      ___                           *    /____\\             *\n");
    /*gotoxy(0, 8);*/  printf("            /__\\               __                       /   \\                              /______\\                 \n");
    /*gotoxy(0, 9);*/  printf("           /____\\             /--\\                     /_   _\\                            /________\\               \n");
    /*gotoxy(0, 10);*/ printf("          /______\\           /____\\                     /   \\                            /__________\\             \n");
    /*gotoxy(0, 11);*/ printf("_________/________\\_________/______\\___________________|_____|__________________________/____________\\_____________\n");
}

void draw_tree() { //나무 그리기
    gotoxy(treeX + 2, TREE_Y);          printf("##\n");
    gotoxy(treeX, TREE_Y + 1);        printf("# ## #\n");
    gotoxy(treeX, TREE_Y + 2);        printf("######\n");
    gotoxy(treeX + 2, TREE_Y + 3);      printf("##\n");
    gotoxy(treeX + 2, TREE_Y + 4);      printf("##");
}

void erase_tree() { //나무 지우기
    if (temp < 950) {
        gotoxy(treeX + 3, TREE_Y);        printf("   \n");
        gotoxy(treeX + 1, TREE_Y + 1);   printf("       \n");
        gotoxy(treeX + 1, TREE_Y + 2);   printf("       \n");
        gotoxy(treeX + 3, TREE_Y + 3);     printf("   \n");
        gotoxy(treeX + 3, TREE_Y + 4);      printf("   ");
    }
    else if (temp >= 950 && temp < 1350) {
        gotoxy(treeX + 3, TREE_Y);        printf("      \n");
        gotoxy(treeX + 1, TREE_Y + 1);   printf("          \n");
        gotoxy(treeX + 1, TREE_Y + 2);   printf("          \n");
        gotoxy(treeX + 3, TREE_Y + 3);     printf("      \n");
        gotoxy(treeX + 3, TREE_Y + 4);      printf("      ");
    }
    else if (temp >= 1350) {
        gotoxy(treeX + 3, TREE_Y);        printf("       \n");
        gotoxy(treeX + 1, TREE_Y + 1);   printf("           \n");
        gotoxy(treeX + 1, TREE_Y + 2);   printf("           \n");
        gotoxy(treeX + 3, TREE_Y + 3);     printf("       \n");
        gotoxy(treeX + 3, TREE_Y + 4);      printf("       ");
    }
}

void tree() { //나무 오른쪽에서 왼쪽으로 이동

    treeX -= treeDecrement; //왼쪽으로 한 칸 이동
    erase_tree(); //지우고
    draw_tree(); //그리기

    speedControl();
}

void speedControl() {
    if (treeX <= 0)
        treeX = TREE_X; //나무가 왼쪽 끝으로 이동하면 초기화
    if (temp == 550) {
        treeDecrement = 2; //속도 증가
    }
    if (temp == 950) {
        treeDecrement = 3; //속도 증가
    }
    if (temp == 1350) {
        treeDecrement = 4; //속도 증가
    }
    if (temp == 1850) {
        treeDecrement = 5; //속도 증가
    }
}

void back_draw_city() {
    printf("\n\n");
    /*gotoxy(0, 4);*/  printf("                                                                           |\n");
    /*gotoxy(0, 5);*/  printf("                                               __                         | |              |            __\n");
    /*gotoxy(0, 6);*/  printf("                                              |  |    /\\                 /   \\      _     ===          |  |    /\\\n");
    /*gotoxy(0, 7);*/  printf("         /\\             _      __         __  |  |   |  |   =            |   |     /_\\   |   |     __  |  |   |  |   = \n");
    /*gotoxy(0, 8);*/  printf("        |  |  _  __    | | __ |  |  _    |  |_|  |   |  |  | |    __     |   |    |   |  |   |    |  |_|  |   |  |  | |\n");
    /*gotoxy(0, 9);*/  printf("   _    |  | | ||  |   | ||  ||  | | |   |   _   |   |  |  | |   |  |    |   |    |   |  |   |    |   _   |   |  |  | |\n");
    /*gotoxy(0, 10);*/ printf("  | |   |  | | ||  |   | ||  ||  | | |   |  | |  |   |  |  | |   |  |   _|   |_   |   |  |   |    |  | |  |   |  |  | |\n");
    /*gotoxy(0, 11);*/ printf("__| |___|  |_| ||  |___| ||  ||  |_| |___|  |_|  |___|  |__| |___|  |__/       \\__|   |__|   |____|  |_|  |___|  |__| |_\n");
}

void draw_city() { //집 그리기
    gotoxy(treeX + 2, TREE_Y);           printf("____\n");
    gotoxy(treeX + 1, TREE_Y + 1);      printf("/    \\\n");
    gotoxy(treeX + 1, TREE_Y + 2);      printf("------\n");
    gotoxy(treeX + 2, TREE_Y + 3);       printf("|##|\n");
    gotoxy(treeX + 2, TREE_Y + 4);       printf("|  |");
}

void erase_city() { //집 지우기
    if (temp < 950) {
        gotoxy(treeX + 3, TREE_Y);         printf("     \n");
        gotoxy(treeX + 2, TREE_Y + 1);    printf("        \n");
        gotoxy(treeX + 2, TREE_Y + 2);    printf("       \n");
        gotoxy(treeX + 3, TREE_Y + 3);     printf("     \n");
        gotoxy(treeX + 3, TREE_Y + 4);     printf("     ");
    }
    else if (temp >= 950 && temp < 1350) {
        gotoxy(treeX + 3, TREE_Y);         printf("      \n");
        gotoxy(treeX + 2, TREE_Y + 1);    printf("         \n");
        gotoxy(treeX + 2, TREE_Y + 2);    printf("        \n");
        gotoxy(treeX + 3, TREE_Y + 3);     printf("      \n");
        gotoxy(treeX + 3, TREE_Y + 4);     printf("      ");
    }
    else if (temp >= 1350) {
        gotoxy(treeX + 3, TREE_Y);         printf("        \n");
        gotoxy(treeX + 2, TREE_Y + 1);    printf("           \n");
        gotoxy(treeX + 2, TREE_Y + 2);    printf("          \n");
        gotoxy(treeX + 3, TREE_Y + 3);     printf("        \n");
        gotoxy(treeX + 3, TREE_Y + 4);     printf("        ");
    }
}

void city() { //집 오른쪽에서 왼쪽으로 이동

    treeX -= treeDecrement; //왼쪽으로 한 칸 이동
    erase_city(); //지우고
    draw_city(); //그리기

    speedControl();
}

void back_draw_winter() {
    printf("\n\n");
    /*gotoxy(0, 4);*/  printf("        *       *                      *                *         *                *              *             *\n");
    /*gotoxy(0, 5);*/  printf("*                       *        *                  *                       *          *      *       *     *     \n");
    /*gotoxy(0, 6);*/  printf(" *        *      *       *       *      *          *      *        *       *              *          *            *  * \n");
    /*gotoxy(0, 7);*/  printf("  *                 *       *      *     *                   /\\       *         *  /\\ *        *         *    *      * \n");
    /*gotoxy(0, 8);*/  printf("      * /\\    *     __=__   *     *        _|_  *     *     /  \\          *       /  \\       *    __|__          _|_ * \n");
    /*gotoxy(0, 9);*/  printf(" *     /  \\      *  (o o)            *    ('v')    *       /    \\   *          * /    \\  *        (o o)   *     ('v') \n");
    /*gotoxy(0, 10);*/ printf("   *  /____\\   *    -(  )-   *    *    *  //=\\\\       *   /______\\      *       /______\\     *    -(  )-    *   //=\\\\ \n");
    /*gotoxy(0, 11);*/ printf("________||__________(    )________________(\\ /)_____________ ||____________________||_____________(   )_________(\\ /)___\n");
}

void draw_Snowman() { //눈사람 그리기
    gotoxy(treeX + 2, TREE_Y);            printf("_==_\n");
    gotoxy(treeX + 1, TREE_Y + 1);       printf("(o<o )\n");
    gotoxy(treeX + 1, TREE_Y + 2);       printf("=(   )=\n");
    gotoxy(treeX + 2, TREE_Y + 3);        printf("(    )\n");
    gotoxy(treeX + 1, TREE_Y + 4);       printf("(      )");
}

void erase_Snowman() { //눈사람 지우기
    if (temp < 950) {
        gotoxy(treeX + 3, TREE_Y);         printf("       \n");
        gotoxy(treeX + 2, TREE_Y + 1);    printf("         \n");
        gotoxy(treeX + 2, TREE_Y + 2);    printf("          \n");
        gotoxy(treeX + 2, TREE_Y + 3);    printf("         \n");
        gotoxy(treeX + 2, TREE_Y + 4);    printf("          ");
    }
    else if (temp >= 950 && temp < 1350) {
        gotoxy(treeX + 3, TREE_Y);         printf("      \n");
        gotoxy(treeX + 2, TREE_Y + 1);    printf("         \n");
        gotoxy(treeX + 2, TREE_Y + 2);    printf("         \n");
        gotoxy(treeX + 3, TREE_Y + 3);     printf("        \n");
        gotoxy(treeX + 2, TREE_Y + 4);    printf("           ");
    }
    else if (temp >= 1350) {
        gotoxy(treeX + 3, TREE_Y);         printf("        \n");
        gotoxy(treeX + 2, TREE_Y + 1);    printf("           \n");
        gotoxy(treeX + 2, TREE_Y + 2);    printf("           \n");
        gotoxy(treeX + 3, TREE_Y + 3);     printf("         \n");
        gotoxy(treeX + 2, TREE_Y + 4);    printf("            ");
    }
}
void Snowman() { //눈사람 오른쪽에서 왼쪽으로 이동

    treeX -= treeDecrement; //왼쪽으로 한 칸 이동
    erase_Snowman(); //지우고
    draw_Snowman(); //그리기

    speedControl();
}

void draw_airplain() {
    gotoxy(treeX + 2, AIR_Y);           printf("           _    \n");
    gotoxy(treeX + 2, AIR_Y + 1);       printf("         / /   _\n");
    gotoxy(treeX + 2, AIR_Y + 2);       printf("  ______/_/___//\n");
    gotoxy(treeX + 2, AIR_Y + 3);       printf("/______  ____()\n");
    gotoxy(treeX + 2, AIR_Y + 4);       printf("      \\ \\\n");
    gotoxy(treeX + 2, AIR_Y + 5);       printf("       \\_\\ ");
}
void erase_airplain() {
    if (temp < 950) {
        gotoxy(treeX + 3, AIR_Y);        printf("                  \n");
        gotoxy(treeX + 3, AIR_Y + 1);    printf("                  \n");
        gotoxy(treeX + 3, AIR_Y + 2);    printf("                  \n");
        gotoxy(treeX + 3, AIR_Y + 3);    printf("                 \n");
        gotoxy(treeX + 3, AIR_Y + 4);    printf("               \n");
        gotoxy(treeX + 3, AIR_Y + 5);    printf("               \n");
    }
    else if (temp >= 950 && temp < 1350) {
        gotoxy(treeX + 3, AIR_Y);        printf("                   \n");
        gotoxy(treeX + 3, AIR_Y + 1);    printf("                   \n");
        gotoxy(treeX + 3, AIR_Y + 2);    printf("                   \n");
        gotoxy(treeX + 3, AIR_Y + 3);    printf("                  \n");
        gotoxy(treeX + 3, AIR_Y + 4);    printf("                \n");
        gotoxy(treeX + 3, AIR_Y + 5);    printf("                \n");
    }
    else if (temp >= 1350) {
        gotoxy(treeX + 3, AIR_Y);        printf("                    \n");
        gotoxy(treeX + 3, AIR_Y + 1);    printf("                    \n");
        gotoxy(treeX + 3, AIR_Y + 2);    printf("                    \n");
        gotoxy(treeX + 3, AIR_Y + 3);    printf("                   \n");
        gotoxy(treeX + 3, AIR_Y + 4);    printf("                 \n");
        gotoxy(treeX + 3, AIR_Y + 5);    printf("                 \n");
    }
}
void airplain() {

    treeX -= treeDecrement;
    erase_airplain();
    draw_airplain();

    speedControl();
}


void setting() {
    //콘솔창 설정
    system("title DinoSaur Game");

    //커서 설정
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConsoleCursor;
    ConsoleCursor.dwSize = 1;
    ConsoleCursor.bVisible = 0; //커서 숨김
    SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

void start() { //시작 화면
    pushpull();
    while (1) {

        gotoxy(30, 10);
        printf("Press 'Space bar' to start the game");

        if (charChoise == 1)
            draw_Tyrano(0);

        else if (charChoise == 2)
            draw_Duck(0);

        else if (charChoise == 3)
            draw_rabbit(0);

        if (_kbhit()) {
            key = _getch();
            if (key == 32) { //'스페이스 바' 입력 확인
                system("cls");
                break;
            }
        }
    }
}

void score(int tic) { //점수 출력
    gotoxy(86, 0);
    printf("               ");
    gotoxy(86, 1);
    printf(" # Score : %d", tic / 5 * 10); // tic/5 당 10점      //필드 폭 4칸 확보 (n천점까지)
    temp = tic / 5 * 10;
}

int end(int tic) { //엔딩 화면
    system("cls");
    int a = 10;
    gotoxy(a, a);       printf(" #####      ##    ##   ##  #######            #####    ##  ##  #######   ######  \n");
    gotoxy(a, a + 1);   printf("##   ##    ####   ### ###   ##  ##           ##   ##   ##  ##   ##  ##   ##  ##  \n");
    gotoxy(a, a + 2);   printf("##        ##  ##  #######   ##               ##   ##   ##  ##   ##       ##  ##  \n");
    gotoxy(a, a + 3);   printf("##        ######  ## # ##   ####             ##   ##   ##  ##   ####     #####   \n");
    gotoxy(a, a + 4);   printf("##  ###   ##  ##  ##   ##   ##               ##   ##   ##  ##   ##       ####    \n");
    gotoxy(a, a + 5);   printf("##   ##   ##  ##  ##   ##   ##  ##           ##   ##    ####    ##  ##   ## ##   \n");
    gotoxy(a, a + 6);   printf(" #####    ##  ##  ##   ##  #######            #####      ##    #######   ###  ## \n");

    gotoxy(40, 20);
    printf("final score : %4d", tic / 5 * 10); //최종 점수

    now_score = tic / 5 * 10;
    last_score = now_score; //게임점수를 옮김 

    if (now_score > best_score) { //최고기록 갱신시 
        FILE* file = fopen("score.dat", "wt"); //score.dat에 점수 저장                

        gotoxy(36, 22); printf("   ★★★ BEST SCORE! ★★★     ");

        if (file == 0) { //파일 에러메세지  
            gotoxy(0, 0);
            printf("FILE ERROR: SYSTEM CANNOT WRITE BEST SCORE ON \"SCORE.DAT\"");
        }
        else {
            fprintf(file, "%d", now_score);
            fclose(file);
        }
    }

    return 0;
}

int main() {

    setting();

    while (1) {
        titleDraw();
        int menuCode = menuDraw();
        if (menuCode == 0) {

            system("cls");
            int tic = 0; //게임 내 시간 단위이자 점수 결정 요소
            int crash = 0; //충돌 체크

            start();

            while (1) {

                tic = game(tic);

                //'스페이스 바' 누르면 점프
                if (_kbhit()) {
                    key = _getch();
                    if (key == 32 && dinoY - 15 == 0) { //'스페이스 바'가 눌리고 공룡이 바닥에 있을 때

                        int h = 0; //점프 높이 초기화

                        while (h < 9) { //y축으로 8칸 상승
                            erase_dino();
                            dinoY--;
                            tic = game(tic);
                            crash = crashing();
                            if (crash == -1)
                                break;
                            h++;
                        }

                        while (h > 0) { //y축으로 8칸 하강
                            tic = game(tic);
                            crash = crashing();
                            if (crash == -1)
                                break;
                            dinoY++;
                            erase_dino();
                            h--;
                        }
                    }
                }
                crash = crashing();
                if (crash == -1) { //충돌 시 탈출
                    PlaySound(NULL, 0, 0);
                    break;
                }
            }

            end(tic);
            while (getchar() != '\n');
            treeX = TREE_X; //장애물 위치 초기화
            treeDecrement = 1; //속도 초기화
        }
        else if (menuCode == 1) {
            charDraw();
        }
        else if (menuCode == 2) {
            infoStages();
        }
        else if (menuCode == 3) {
            infoDraw();
        }
        else if (menuCode == 4) {
            return 0;
        }
        system("cls");
    }

    menuDraw();
    keyControl();
    return 0;
}