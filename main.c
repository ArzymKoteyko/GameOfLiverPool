#include <stdio.h>
#include <stdlib.h>

#define HEIGHT 30
#define WIDTH 50

typedef enum { dead = 0, alive = 1 } state;

typedef struct Mask {
  int **mask;
  int width;
  int height;
} mask;

typedef struct Ceil {
  int state;
  mask mask;
} ceil;

ceil *newCeil(state, mask);
void deleteCeil(ceil *);
int coutNeighbours(ceil *ceil);
int live(ceil *ceil);

ceil ***createField(void);
void deleteField(ceil ***);
void printField(ceil ***);

int main() {
  ceil ***field = createField();
  printField(field);
  deleteField(field);
  return 0;
}

ceil ***createField(void) {
  int rowMask[3][3] = {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};
  mask mask = {(int **)rowMask, 3, 3};
  ceil ***field =
      malloc(sizeof(ceil **) * WIDTH + sizeof(ceil *) * WIDTH * HEIGHT);
  ceil **ptr = (ceil **)(field + WIDTH);
  for (int i = 0; i < WIDTH; i++) {
    field[i] = (ptr + HEIGHT * i);
  }
  for (size_t y = 0; y < HEIGHT; y++) {
    for (size_t x = 0; x < WIDTH; x++) {
      field[x][y] = newCeil(rand() % 2, mask);
    }
  }
  return field;
}

void deleteField(ceil ***field) { free(field); }

void printField(ceil ***field) {
  for (size_t y = 0; y < HEIGHT; y++) {
    for (size_t x = 0; x < WIDTH; x++) {
      printf("%i", field[x][y]->state);
    }
    printf("\n");
  }
}

ceil *newCeil(state state, mask mask) {
  ceil *ceil = malloc(sizeof(ceil));
  ceil->state = state;
  ceil->mask = mask;
  return ceil;
}

void deleteCeil(ceil *ceil) { free(ceil); }

int coutNeighbours(ceil *ceil) {}