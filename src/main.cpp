#include<iostream>
#include "snake.h"
#include<unistd.h>
#include<ncurses.h>
int main(){
    initialize();
    update();
    int tick=0;
    const int move_interval=8;
    while(alive){
        int ch=getch();
        change_direction(ch);

        if(++tick>=move_interval){
            tick=0;
            Snakemove();
        }
        update();
        dead();
        usleep(10000);
    }
    print("Game Over");
    endwin();
    return 0;
}

	
