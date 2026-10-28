#ifndef SNAKE_H
#define SNAKE_H
#include<string>
#include<ncurses.h>
#include<iostream>
#include<random>
#include<chrono>
enum class Dir {up,down,left,right};

struct node{
    int x,y;
    node*next;
};

extern std::mt19937 gen;
extern bool alive;
extern node*food;
extern node*head;
extern node*tail;
extern int rows;
extern int cols;
extern Dir direction;
extern bool is_eat;

void initialize();

void update();//逐帧打印函数

void dead();//死亡函数

void print(const char*s);//游戏结束画面

void change_direction(const int&ch);//操控方向函数

void Snakemove();//运动函数


void generate_food();//生成食物

#endif
