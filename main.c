#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define HEIGHT 50
#define WIDTH 100

typedef enum { dead = 0, alive = 1 } state;

typedef struct iVector2 {
  int x;
  int y;
} iVec2;

typedef struct Mask {
  int **mask;
  int width;
  int height;
  iVec2 corner; // left upper corner
} Mask;

typedef struct Ceil {
  int state;
  Mask mask;
  iVec2 pos; // position {x, y}
} Ceil;

Ceil *newCeil(iVec2, state, Mask);
void deleteCeil(Ceil *);
int coutCeilNeighbours(Ceil ***, Ceil *);
void evolveCeil(Ceil ***, Ceil ***, Ceil *);

Mask createMask(void);

Ceil ***createField(void);
void populateField(Ceil ***, Mask);
void evolveField(Ceil ***, Ceil ***);
void printField(Ceil ***);
void deleteField(Ceil ***);

int main() {
  srand(time(NULL));
  Ceil ***field = createField();
  Ceil ***buffer = createField();
  Mask ceilMask = createMask();
  populateField(field, ceilMask);
  populateField(buffer, ceilMask);
  while (1) {
    printField(field);
    evolveField(field, buffer);
    Ceil ***swap = field;
    field = buffer;
    buffer = swap;
    usleep(500000);
  }
  deleteField(field);
  return 0;
}

Mask createMask(void) {
  int **rowMask = malloc(sizeof(int *) * WIDTH + sizeof(int) * WIDTH * HEIGHT);
  int *ptr = (int *)(rowMask + 3);
  for (int i = 0; i < 3; i++) {
    rowMask[i] = (ptr + 3 * i);
  }
  rowMask[0][0] = 1;
  rowMask[1][0] = 1;
  rowMask[2][0] = 1;
  rowMask[0][1] = 1;
  rowMask[1][1] = 0;
  rowMask[2][1] = 1;
  rowMask[0][2] = 1;
  rowMask[1][2] = 1;
  rowMask[2][2] = 1;
  Mask mask = {rowMask, 3, 3, {-1, -1}};
  return mask;
}

Ceil ***createField(void) {
  Ceil ***field =
      malloc(sizeof(Ceil **) * WIDTH + sizeof(Ceil *) * WIDTH * HEIGHT);
  Ceil **ptr = (Ceil **)(field + WIDTH);
  for (int i = 0; i < WIDTH; i++) {
    field[i] = (ptr + HEIGHT * i);
  }

  return field;
}

void populateField(Ceil ***field, Mask mask) {
  for (size_t y = 0; y < HEIGHT; y++) {
    for (size_t x = 0; x < WIDTH; x++) {
      iVec2 pos = {x, y};
      field[x][y] = newCeil(pos, rand() % 2, mask);
    }
  }
}

void evolveField(Ceil ***field, Ceil ***buffer) {
  for (size_t y = 0; y < HEIGHT; y++) {
    for (size_t x = 0; x < WIDTH; x++) {
      evolveCeil(field, buffer, field[x][y]);
    }
  }
}

void deleteField(Ceil ***field) { free(field); }

void printField(Ceil ***field) {
  for (size_t y = 0; y < HEIGHT; y++) {
    printf("\e[A");
  }
  for (size_t y = 0; y < HEIGHT; y++) {
    for (size_t x = 0; x < WIDTH; x++) {
      switch (field[x][y]->state) {
      case alive:
        printf("*");
        break;
      case dead:
        printf(" ");
        break;
      }
    }
    printf("\n");
  }
}

Ceil *newCeil(iVec2 pos, state state, Mask mask) {
  Ceil *ceil = malloc(sizeof(Ceil));
  ceil->pos = pos;
  ceil->state = state;
  ceil->mask = mask;
  return ceil;
}

void deleteCeil(Ceil *ceil) { free(ceil); }

int coutCeilNeighbours(Ceil ***field, Ceil *ceil) {
  int neighbours = 0;
  // u = x' // v = y'
  int u = 0, v = 0, x = 0, y = 0;
  fflush(stdout);
  for (u = 0; u < (ceil->mask.width); u++) {
    fflush(stdout);
    for (v = 0; v < (ceil->mask.height); v++) {
      x = (ceil->pos.x) + (ceil->mask.corner.x) + u;
      y = (ceil->pos.y) + (ceil->mask.corner.y) + v;
      fflush(stdout);
      if ((x > -1 && x < WIDTH && y > -1 && y < HEIGHT)) {
        neighbours += field[x][y]->state * ceil->mask.mask[u][v];
      }
    }
  }
  return neighbours;
}

void evolveCeil(Ceil ***field, Ceil ***buffer, Ceil *ceil) {
  int neighbours = coutCeilNeighbours(field, ceil);
  if (neighbours <= 2 && neighbours >= 5) {
    buffer[ceil->pos.x][ceil->pos.y]->state = dead;
  }
  else if (neighbours >= 3 && neighbours <= 4 && ceil->state == alive) {
    buffer[ceil->pos.x][ceil->pos.y]->state = alive;
  } else {
    buffer[ceil->pos.x][ceil->pos.y]->state = dead;
  }
}
