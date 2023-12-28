#include "randomSnake.h"

void mapRead(int mat[SIZE][SIZE], const char *fileName){
    FILE *file = fopen(fileName, "r");

    if (file){
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
                fscanf(file, "%d", &mat[i][j]);
        }
    }
    else{
        printf("Error opening file\n");
        exit(1);
    }
    fclose(file);
}

void generateFruit(int mat[SIZE][SIZE], int amount){
    int counter = 0, x, y;

    while (counter < amount){
        x = rand() % SIZE;
        y = rand() % SIZE;

        if (mat[x][y] == 0){
            mat[x][y] = 3;
            counter++;
        }
    }
}

List *createList(){
    List *newList = (List*)malloc(sizeof(List));
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;

    return newList;
}

Node *createNode(int a, int b){
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode){
        newNode->x = a;
        newNode->y = b;
        newNode->next = NULL;
        newNode->previous = NULL;
        return newNode;
    }
    else{
        printf("Memory allocation error\n");
        exit(1);
    }
}

void increaseSnake(List *snake, int x, int y){
    Node *newNode = createNode(x,y);

    if (snake->head == NULL) //Empty
        snake->head = newNode;
    else
        snake->tail->next = newNode;

    newNode->previous = snake->tail;
    snake->tail = newNode;
    snake->size++;
}

void findStart(int mat[SIZE][SIZE], int *x, int *y){
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (mat[i][j] == 2)
            {
                *x = i;
                *y = j;
                break;
            }
        }
    }
}

bool checkBody(List *snake, int a, int b){
    Node *aux = snake->head;

    while (aux){
        if (aux->x == a && aux->y == b)
            return false;

        aux = aux->next;
    }
    
    return true;
}

bool nextStep(int mat[SIZE][SIZE], List *snake){
    int a, b = -1;
    bool check0 = false, check1 = false, check2 = false, check3 = false;

    while (!check0 || !check1 || !check2 || !check3) {
        int r = rand() % 4;

        switch (r) {
        case 0:
            check0 = true;
            if (mat[snake->head->x][snake->head->y+1] != 1 && checkBody(snake, snake->head->x, snake->head->y+1)){ //Not wall and not body
                a = snake->head->x;
                b = snake->head->y+1;
            }
            break;
        case 1:
            check1 = true;
            if (mat[snake->head->x+1][snake->head->y] != 1 && checkBody(snake, snake->head->x+1, snake->head->y)){
                a = snake->head->x+1;
                b = snake->head->y;
            }
            break;
        case 2:
            check2 = true;
            if (mat[snake->head->x-1][snake->head->y] != 1 && checkBody(snake, snake->head->x-1, snake->head->y)){
                a = snake->head->x-1;
                b = snake->head->y;
                
            }
            break;
        case 3:
            check3 = true;
            if (mat[snake->head->x][snake->head->y-1] != 1 && checkBody(snake, snake->head->x, snake->head->y-1)){
                a = snake->head->x;
                b = snake->head->y-1;
            }
            break;
        }
    }
    
    if (b == -1) 
        return false;

    int tx = snake->tail->x;
    int ty = snake->tail->y;
        
    Node * aux = snake->tail;
        
    while (aux->previous){ //Moving the snake
        aux->x = aux->previous->x;
        aux->y = aux->previous->y;
        aux = aux->previous;
    }
    //Moving the head of snake
    snake->head->x = a;
    snake->head->y = b;

    if (mat[a][b] == 3){ //Fruit
        increaseSnake(snake, tx, ty);
        mat[a][b] = 0;
        generateFruit(mat, 1);
    }

    return true;    
}

void printMap(int mat[SIZE][SIZE], List *snake){
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++){
            if (mat[i][j] == 1)
                printf("%c ", 178);
            else if (snake->head->x == i && snake->head->y == j)
                printf("@ ");
            else if (!checkBody(snake, i, j))
                printf("%c ", 254);
            else if (mat[i][j] == 3)
                printf("%c ", 248);
            else
                printf("  ");
        }
        printf("\n");
    }
}

void game(int mat[SIZE][SIZE], List *snake){
    generateFruit(mat, 10);
    int x, y;
    findStart(mat, &x, &y);
    increaseSnake(snake, x, y);
    
    while (1) {
        if (nextStep(mat, snake)){ 
            system("cls");
            printMap(mat, snake);
            Sleep(250);
            
        }
        else {
            printf("\nSnake trapped\nGAME OVER\nscore: %d", snake->size);
            break;
        }
    }
}

void freeList(List *snake){
    Node *current = snake->head;

    while (current){ 
        Node *next = current->next;
        free(current);
        current = next;
    }

    free(snake);    
}