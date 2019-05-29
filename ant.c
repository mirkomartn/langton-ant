// An implementation of Langton's ant on a 10x10 grid.
// Gašper Š.

#include <stdio.h>

#define TRUE -1
#define FALSE 0
#define ROWSIZE 10
#define SURFSIZE (ROWSIZE * ROWSIZE)
#define ANT_WHITE 2
#define ANT_BLACK 3
#define WEST 0
#define NORTH 1
#define EAST 2
#define SOUTH 3

typedef struct Ants {
    int position;
    int direction;
} Ant;

void print_surface(int *surface);
void get_input(int *x, int *y, int *n);
void set_ant(Ant *ant, int *surface);
int move_n(Ant *ant, int n, int *surface);
void move_ant(Ant *ant);

int main() {
	// the white cells are represented with 0s and black cells with 1s
    int x, y, n, surface[SURFSIZE] = {0};
    Ant ant;
    Ant *ant_ptr = &ant;

	// initialize ant as specified in the instructions, I use a vector to represent the surface matrix
    get_input(&x, &y, &n);
    ant.direction = WEST;
    ant.position = (y * ROWSIZE) + x;

    // call move_n user-given n times, if ant dies, this will return 0, else 1
    // depending on the cell color on which the ant ends up, it will be either marked with an A or a
    if (move_n(ant_ptr, n, surface)) {
        surface[ant_ptr->position] = (surface[ant_ptr->position]) ? ANT_BLACK : ANT_WHITE;
    }

    print_surface(surface);
}

void get_input(int *x, int *y, int *n) {
    printf("Enter number of turns: ");
    scanf("%d", n);
    printf("Enter start position (0 indexed): ");
    scanf("%d %d", x, y);
}


// tries to call set_ant and move_ant n times, if ant's position is outside the surface, it returns 0, else it returns 1
int move_n(Ant *ant, int n, int *surface) {
    for(int i=0; i < n; i++) {
        set_ant(ant, surface);
        move_ant(ant);
        if ((ant->position > SURFSIZE) || (ant->position < 0)) return FALSE;
    }
    return TRUE;
}

// depending on the color of the cell, the ant either "turns left" or "turns right" by substracting or adding 1, respectively
// e.g. if ant is facing WEST (0), turning to the right its new direction is NORTH (1) -- the direction is checked with modulo
// (see move_ant switch argument), afterwards the color of the cell is flipped

void set_ant(Ant *ant, int *surface) {
    surface[ant->position] ? (ant->direction)-- : (ant->direction)++;
    surface[ant->position] = surface[ant->position] ? 0 : 1;
}

// (direction + 4 % 4) will always be an integer between 0 and 3, marking the current direction of the ant when updating the
// position of the ant, one has to be careful of the pecularities of using a "flattened" matrix representation, specifically
// when moving to the WEST or EAST, one has to check that the ant is not on an edge of the matrix, if this is the case, the
// ternary operator is such that the new position value will cause the move_n to return FALSE (0)

void move_ant(Ant *ant) {
    switch(((ant->direction + 4) % 4)) {
        case WEST:
            ant->position -= (ant->position % ROWSIZE) ? 1 : 100;
            break;
        case EAST:
            ant->position += ((ant->position + 1) % ROWSIZE) ? 1 : 100;
            break;
        case NORTH:
            ant->position -= ROWSIZE;
            break;
        case SOUTH:
            ant->position += ROWSIZE;
            break;
    }
}

void print_surface(int *surface) {
    for(int i = 0; i < SURFSIZE; i++) {
        if (!surface[i]) {
            printf(".");
        } else if (surface[i] == ANT_WHITE) {
            printf("a");
        } else if (surface[i] == ANT_BLACK) {
            printf("A");
        } else {
            printf("#");
        }
        if (!((i + 1) % ROWSIZE)) printf("\n");
    }
}

