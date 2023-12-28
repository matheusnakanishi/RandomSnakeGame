#ifndef SNAKE_
#define SNAKE_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <Windows.h>

#define SIZE 20 //Matrix size

typedef struct node{
    int x;
    int y;
    struct node *next;
    struct node *previous;
} Node;

typedef struct{
    int size;
    Node *head;
    Node *tail;
} List;

void mapRead(int mat[SIZE][SIZE], const char *fileName);
void generateFruit(int mat[SIZE][SIZE], int amount);
List *createList();
Node *createNode(int a, int b);
void increaseSnake(List *snake, int x, int y);
void findStart(int mat[SIZE][SIZE], int *x, int *y);
bool checkBody(List *snake, int a, int b);
bool nextStep(int mat[SIZE][SIZE], List *snake);
void printMap(int mat[SIZE][SIZE], List *snake);
void game(int mat[SIZE][SIZE], List *snake);
void freeList(List *snake);

#endif