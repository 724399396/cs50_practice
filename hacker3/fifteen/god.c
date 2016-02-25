#include <stdlib.h>
#include <cs50.h>

int lowest(int open_set[],double values[]);
bool is_empty(int array[]);
void init_array(int array[]);
void remove_from_array(int array[], int vlaue);
void add_to_array(int array[], int value);
int *neighbor(int location, int obstacle[]);
bool contains(int array[], int value);
double distance(int a, int b);
int *reconstruct_path(int came_from[], int currenct);



int lowest(int open_set[],double values[])
{
    double min = DBL_MAX;
    int x = -1;
    for(int i = 0; i < (int)sizeof(open_set) / sizeof(open_set[0]); i++) {
        double current = values[open_set[i]];
        if (current < min) {
            min = current;
            x = i;
        }
    }
    return x;
}

int main(void)
{
    double  v[5] = {1.2,3.1,0.5,1.4};
    int o[3] = {2,3};
    printf("%d\n", lowest(o,v));
}

/*
void swap_two_dim_array(int row, int col, int row2, int col2)
{
    int tmp = board[row][col];
    board[row][col] = board[row2][col2];
    board[row2][col2] = tmp;
}

int *a_start_path(int from, int to, int obstacle_bound)
{
    int closed_set[d*d], open_set[d*d], came_from[d*d];
    init_array(closed_set);
    init_array(open_set);
    double g_score[d*d], f_score[d*d], h_score[d*d];
    open_set[0] = from;
    g_score[0] = 0;
    for(int i = 0; i < d*d; i++) {
        int row_distance = abs(i % d - to % d);
        int col_distance = abs(i / d - to / d);
        h_score[i] = distance(row_distance,col_distance);
        f_score[i] = h_score[i];
    }
    int obstacle[from];
    for(int i = 0; i <= obstacle_bound; i++) {
        obstacle[i] = i;
    }
    
    while (!is_empty(open_set)) {
        int lowest = lowerst(open_set, f_score);
        if (lowest == to) {
            return reconstruct_path(came_from,to);
        }
        remove_from_array(open_set, lowest);
        add_to_array(closed_set, lowest);
        int* neighbors = neighbor(lowest, obstacle);
        for(int i = 0; i < d * d; i++){
            if(neighbors[i] == -1){
                continue;
            }
            if(contains(closed_set, neighbors[i])) {
                continue;
            }
            double tentative_g_score = g_score[lowest] + distance(lowest,neighbors[i]);
            if(!contains(open_set,neighbors[i])){
                add_to_array(open_set, neighbors[i]);
            } else if (tentative_g_score >= g_score[neighbors[i]]) {
                continue;
            }
            came_from[neighbors[i]] = lowest;
            g_score[neighbors[i]] = tentative_g_score;
            f_score[neighbors[i]] = g_score[neighbors[i]] + distance(neighbors[i], to);
        }
    }
    
    return NULL;
}



bool is_empty(int array[])
{
    for(int i = 0; i < d * d; i++) {
        if (array[i] != 0) {
            return false;
        }
    }
    return true;
}

void init_array(int array[])
{
    for(int i = 0; i < d * d; i++) {
        array[i] = 0;    
    }
}

void remove_from_array(int array[], int value)
{
    array[value] = 0;
}

void add_to_array(int array[], int value)
{
    array[value] = value;
}

int *neighbor(int location, int obstacle[])
{
    int row = location / d;
    int col = location % d;
    int *res = malloc(d*d*sizeof(int));
    for (int j = 0; j < d * d; j++) {
        res[j] = -1;
    }
    int i = 0;
    if (col > 0) {
        res[i++] = location - 1;
        if (row > 0) {
            res[i++] = location - d - 1;
        }
        if (row < d - 1) {
            res[i++] = location + d - 1;
        }
    }
    if (col < d - 1) {
        res[i++] = location + 1;
          if (row > 0) {
            res[i++] = location - d + 1;
        }
        if (row < d - 1) {
            res[i++] = location + d + 1;
        }
        
    }
   if (row > 0) {
        res[i++] = location - d;
    }
    if (row < d - 1) {
        res[i++] = location + d;
    }
    for(int j = 0; j < i; j++) {
        if(contains(obstacle,res[j])) {
            res[j] = -1;
        }
    }
    return res;
}

bool contains(int *array, int value)
{
    for(int i = 0; i < (int)sizeof(array); i++) {
        if (value == array[i]) {
            return true;
        }
    }
    return false;
}

double distance(int a, int b)
{
    return sqrt(pow(a,2) + pow(b,2));
}

int *reconstruct_path(int came_from[], int currenct)
{
    return NULL;
}
*/