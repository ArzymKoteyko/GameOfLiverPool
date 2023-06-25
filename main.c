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

typedef enum {
    dead = 0,
    alive = 1
} state;

typedef struct Mask {
    int **mask;
    int width;
    int height;
} mask;

typedef struct Ceil {
    int state;
    int** mask;
    int maskWidth;
    int maskHeight;
} ceil;

ceil* newCeil(state state, int** mask, int maskWidth, int maskHieght) {
    ceil* ceil = malloc(sizeof(ceil));
    ceil->state = state;
    ceil->mask = mask;
    ceil->maskWidth = maskHieght;
    ceil->maskHeight = maskWidth;
    return ceil;
}

void deleteCeil(ceil* ceil) {
    free(ceil);
}

int coutNeighbours(ceil* ceil) {
    
}
int live(ceil* ceil);
