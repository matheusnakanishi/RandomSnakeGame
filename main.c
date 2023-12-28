#include "randomSnake.h"

int main(){
    srand(time(NULL));

    int mat[SIZE][SIZE];
    List *snake = createList();
    char fileName[20] = "map20.txt"; 

    mapRead(mat, fileName);
    game(mat, snake);
    freeList(snake);

    return 0;
}