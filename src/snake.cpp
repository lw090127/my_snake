#include<iostream>
#include<cstring>
#include "snake.h"
#include<unistd.h>
#include<ncurses.h>
#include<random>
#include<chrono>

std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());

//全局变量初始化区
node*head=nullptr;
node*tail=nullptr;
int rows=0,cols=0;
Dir direction=Dir::right;
bool is_eat=false;
bool alive=true;
node*food=nullptr;

//各个函数区
void generate_food(){
        std::uniform_int_distribution<int>distx(5,rows-5);
        std::uniform_int_distribution<int>disty(5,cols-5);
        food=new node{distx(gen),disty(gen),nullptr};
};
void initialize(){
    initscr();
    if(!isatty(0)){endwin();return;}
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr,TRUE);
    if(has_colors()){
        start_color();
        init_pair(1,COLOR_BLUE,COLOR_BLACK);
        init_pair(2,COLOR_YELLOW,COLOR_BLACK);
        init_pair(3,COLOR_RED,COLOR_BLACK);
    }//设置颜色
    else{
        print("No colors");
    }
    getmaxyx(stdscr,rows,cols);
    if(rows<6||cols<6){endwin();return;}
    std::uniform_int_distribution<int> distX(1,rows-2);
    std::uniform_int_distribution<int> distY(4,cols-2);
    int random_x=distX(gen);
    int random_y=distY(gen);
    head=new node{random_x,random_y,nullptr};
    head->next=new node{random_x,random_y-1,nullptr};
    head->next->next=new node{random_x,random_y-2,nullptr};
    tail=head->next->next;
    generate_food();
    timeout(5);
}


void update(){
    erase();
    for(int i=0;i<rows;i++){
        mvaddch(i,0,'#');
        mvaddch(i,cols-1,'#');
    }
    for(int i=0;i<cols;i++)
    {
        mvaddch(0,i,'#');
        mvaddch(rows-1,i,'#');
    }
    if(!is_eat){
        attron(COLOR_PAIR(2));    
        mvaddch(food->x,food->y,'*');
        attroff(COLOR_PAIR(2));
    }
    node*p=head->next;
    while(p!=nullptr){
        attron(COLOR_PAIR(2));
        mvaddch(p->x,p->y,'o');
        attroff(COLOR_PAIR(2)); 
        p=p->next;
    }
    attron(COLOR_PAIR(2));
    mvaddch(head->x,head->y,'@');
    attroff(COLOR_PAIR(2));
    if(is_eat){
        is_eat=false;
        free(food);
        generate_food();
    }
    refresh();

};//清屏，画，刷新


void dead(){
    int h_x=head->x;
    int h_y=head->y;
    if(h_x<=1||h_y<=1||h_x>rows-1||h_y>cols-1)alive=false;
    node*p=head->next;
     while(p!=nullptr){
        if(p->x==h_x&&p->y==h_y){
            alive=false;
            return;
        }
        if(p->x>rows-1||p->y>cols-1){
            alive=false;
            return;
        }
        p=p->next;
    }
};

void print(const char*msg){
    int y=rows/2;
    int x=(cols-strlen(msg))/2;
    attron(COLOR_PAIR(3));
    mvprintw(y,x,"%s",msg);
    attroff(COLOR_PAIR(3));
    refresh();
    napms(2000);
}
    


void Snakemove(){
    int dx=0,dy=0;
    switch(direction){
    case Dir::left:
    	dy=-1;break;
    case Dir::right:
    	dy=1;break;
    case Dir::up:
    	dx=-1;break;
    case Dir::down:
    	dx=1;break;
}
    node*newhead=new node{(head)->x +dx,(head)->y +dy,head};
    head=newhead;
    if(head->x==food->x&&head->y==food->y){
        is_eat=true;
    }
    if(!is_eat){
    	node*temp=newhead;		
    	while(temp->next!=tail){
    		temp=temp->next;
    	    }
        node*oldtail=tail;
        tail=temp;
        tail->next=nullptr;
        delete oldtail;
    }
};


void change_direction(const int &ch){
	if(ch!=ERR){
		switch(ch){
		case KEY_UP: if(direction!=Dir::down)direction=Dir::up;break;
		case KEY_DOWN: if(direction!=Dir::up)direction=Dir::down;break;
		case KEY_LEFT:if(direction!=Dir::right)direction=Dir::left;break;
		case KEY_RIGHT:if(direction!=Dir::left)direction=Dir::right;break;
		case 'q':alive=false;return ;	
		}
    }
};
	
