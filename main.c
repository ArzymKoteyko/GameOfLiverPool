#include <stdio.h>

#define HEIGHT 50
#define WIDTH 50

// void createField(int board[HEIGHT][WIDTH]){
//     for (int i = 0; i < HEIGHT; i++){
//         for (int j = 0; j < WIDTH; j++){
//             printf(board[i][j] ? "*":" ");
//         }
//     }
// }
void printField(int** board){
    for (size_t i = 0; i < HEIGHT; i++) {
        for (size_t j = 0; j < WIDTH; j++) {
            printf(board[i][j]);
        }
    }
}
void createField(int** board){
    // *board = (int *)malloc(sizeof(int) * WIDTH * HEIGHT);
    *board = malloc(sizeof(int*) * WIDTH + sizeof(int) * WIDTH * HEIGHT);
    for (size_t i = 0; i < HEIGHT; i++) {
        for (size_t j = 0; j < WIDTH; j++) {
            (*board)[i * WIDTH + j] = rand() % 2;
        }
    }
    // *board = (int**)malloc(sizeof(int*) * width);
    // for (i = 0; i < width; i++) {
    //     (*board)[i] = (int*)malloc(sizeof(int) * height);
    // }
}

int main(){
    int* board = 0;

    createField(&board);
    printField(&board);
    return 0;
}