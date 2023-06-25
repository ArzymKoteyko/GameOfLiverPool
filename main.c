typedef enum {
    dead = 0,
    alive = 1
} state;

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

int main() {
    return 0;
}