/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <limits.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
int *location(int title);
int *a_start_path(int from, int to, int obstacle_bound);
void swap_two_dim_array(int row, int col, int row2, int col2);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            board[i][j] = i * d + j + 1;
        }
    }
    while(won()) {
        int move_rand_step = 100;
        while(move_rand_step) {
            int rand_tile = (int) (lrand48() % (d*d) + 1);
            if(move(rand_tile)) {
                move_rand_step--;
            }
        }
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    int under_line_size = d * 6 + (d+1);
    for (int i = 0; i < under_line_size; i++) {
        printf("\033[;1;31m-");
    }
    printf("\n");
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {  
            printf("\033[;1;31m| ");
            if (board[i][j] == d * d) {
                printf("\033[;1;32m    ");
            } else if (board[i][j] == (i * d + j + 1)) {
                printf("\033[;1;32m %2d ", board[i][j]);
            } else {
                printf("\033[;1;31m %2d ", board[i][j]);
            }
        }
        printf("\033[;1;31m| ");
        printf("\n");
    }
    for (int i = 0; i < under_line_size; i++) {
        printf("\033[;1;31m-");
    }
    printf("\n");
    printf("\033[;1;00m");
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    if (tile < 1 || tile > d * d) {
        return false;
    }
    int* empty_location = location(d*d);
    int* tile_location = location(tile);
    int empty_x = *empty_location, empty_y = *(empty_location+1);
    int tile_x = *tile_location, tile_y = *(tile_location+1);
    bool can_move = false;
    if (empty_x == tile_x) {
        can_move = abs(empty_y - tile_y) == 1;
        if (can_move) {
            swap_two_dim_array(empty_x,empty_y,tile_x,tile_y);
            return can_move;
        }
    }
    if (empty_y == tile_y) {
        can_move = abs(tile_x - empty_x) == 1;
        if (can_move) {
            swap_two_dim_array(empty_x,empty_y,tile_x,tile_y);
            return can_move;
        }
    }
    return false;
}

int *location(int tile) 
{
    int *res = malloc(2 * sizeof(int));
    for(int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            if(board[i][j] == tile) {
                *res = i;
                *(res + 1) = j;
                return res;
            }
        }
    }
    return res;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    bool is_won = true;
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            if (board[i][j] != i * d + j + 1) {
                is_won = false;
                return is_won;
            }
        }
    }
    return is_won;
}

void swap_two_dim_array(int row, int col, int row2, int col2)
{
    int tmp = board[row][col];
    board[row][col] = board[row2][col2];
    board[row2][col2] = tmp;
}

