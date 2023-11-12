#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

void titleDraw();
void gotoxy();
void init();

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


int main()
{
  printf("OSS Project1\n");
  printf("First GitHub Training\n");
  return 0;
}
