#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int * init();
void show(int * a);
void swap_with_empty(int * a, int be_moved_number);
void swap(int* a, int i, int j);
void god(int* a);
int moved_loc(int* a, int be_moved_number);
void moved_x(int *a, int cur, int emp, int left_x);
void moved_y(int *a, int cur, int emp, int left_y);
void moved_empty_to_special(int *a, int cur, int emp, int not_touch);
int rand_range(int min, int max);
void special_x_move(int *a, int desc, int src);
void special_y_move(int *a, int desc, int src);

int main(void) {
  int* p;
  p = init();
  show(p);
  while(1) {
    printf("move which: ");
    int moved;
    scanf("%d", &moved);
    if(moved == 100) {
      god(p);
    } else {
      swap_with_empty(p, moved);
    }
    moved = 0;
  }
}

int * init() {
  static int tmp[16];
  srand(time(NULL));
  for(int i = 0; i < 16; i++) {
    tmp[i] = i;
  }
  for(int j = 0; j < 50; j++) {
    int tmpx = rand_range(0,15);
    swap_with_empty(tmp, tmpx);
  }
  return tmp;
}

void swap_with_empty(int * a, int be_moved_number) {
  int i,j;
  if (be_moved_number < 1 || be_moved_number > 15) {
    printf("illegal location %d\n", be_moved_number);
    return;
  }
  i = moved_loc(a, 0);
  j = moved_loc(a,be_moved_number);
  int diff = abs(i - j);
  if ( (diff == 1 && (1 || i / 4 == j / 4)) || diff == 4 ) {
      swap(a, i, j);
      show(a);
      return;
  }
  printf("illegal move %d %d\n", i, j);
}

int moved_loc(int* a, int be_moved_number) {
  for(int loc = 0; loc < 16; loc ++) {
    if (a[loc] == be_moved_number) 
      return loc;
  }
  return -1;
}

void god(int* a) {
  for(int cur = 1; cur <= 15; cur++) {
    int cur_loc = moved_loc(a, cur); // be palced element now location
    int emp_loc = moved_loc(a, 0); // empty element now location
    int diff_loc = cur_loc - (cur - 1);  // be placed now location diff show location
    if (diff_loc == 0)
      continue;
    int x = diff_loc % 4;  // if < 0 means move right, > 0 means move left
    moved_x(a,cur_loc,emp_loc,x);
    cur_loc = moved_loc(a, cur); // re get element location
    emp_loc = moved_loc(a, 0); // re get empty location
    diff_loc = cur_loc - (cur - 1); // show be 4 times
    if (diff_loc == 0)
      continue;
    int y = (diff_loc / 4); // if > 0 move top , < 0 move down
    moved_y(a,cur_loc,emp_loc,y);
  }
}

void moved_x(int* a, int cur, int emp, int x_left) {
  if (x_left == 0)
    return; 
  int direct = x_left > 0 ? -1 : 1;
  int special = cur + direct; // move empty to cur around (left or right deceided by x_left)
  if (0 && (cur % 4 == 0 || emp % 4 == 0) && (special / 4 != direct / 4)) {
    int special_line = special / 4;
    int emp_line = special / 4;
    if (emp_line > special_line)
      emp -= 4;
    else
      emp += 4;
    swap_with_empty(a, emp);
  }
  moved_empty_to_special(a,special, emp, cur);
  swap_with_empty(a,a[cur]);
  moved_x(a, special, cur, x_left + direct);
}
void moved_y(int* a, int cur, int emp, int y_left) {
  if (y_left == 0)
    return;
  int direct = y_left > 0 ? -4 : 4;
  int special = cur + direct;
  moved_empty_to_special(a, special, emp, cur);
  swap_with_empty(a,a[cur]);
  moved_y(a,special, cur, y_left + direct / 4);
}

void moved_empty_to_special(int *a, int special, int emp, int not_touch) {
  int x = (emp % 4 - special % 4); // if x < 0, move right, x > 0, move left
  int y = (emp / 4 - special / 4); // if y < 0 move down, y > 0, move top
  int x_direct = x < 0 ? 1 : -1;
  int y_direct = y < 0 ? 4 : -4;
  while(x != 0 || y != 0) {
      while(x != 0) {
        int loc = emp + x_direct; // next empty place location
        if (loc == not_touch) {  // cat touch another source elements
	  special_x_move(a, special, emp);
	  x = 0;
          emp = loc; // emp now at new location
          break;
        }
        swap_with_empty(a, a[loc]); // move
        x += x_direct;
        emp = loc; // emp now at new location
      }
      while(y != 0) {
        int loc = emp + y_direct;
        if (loc == not_touch) {
	  special_y_move(a, special, emp);
          y = 0;
          emp = loc; // emp now at new location
          break;
        }
        swap_with_empty(a, a[loc]);
        y += y_direct / 4;
        emp = loc;
      }	 
  }
}

void special_x_move(int *a, int desc, int src) {
  int src_line_number = src / 4 + 1;
  int desc_line_number = desc / 4 + 1;
  int src_col_number = src % 4 + 1;
  int desc_col_number = desc % 4 + 1;
  int x_direct, y_direct;
  if (desc_col_number > src_col_number) {
    x_direct = 1;
  } else if (desc_col_number < src_col_number) {
    x_direct = -1;
  } else {
    x_direct = desc_col_number == 4 ? -1 : 1;
  }
  if (desc_line_number > src_line_number) {
    y_direct = 1;
  } else if (desc_line_number < src_line_number) {
    y_direct = -1;
  } else {
    y_direct = desc_line_number == 4 ? -1 : 1;
  }

  for (int i = 0; i <= 2; i++) {
    int tmp_loc = src + 4 * y_direct + x_direct * i;
    swap_with_empty(a, a[tmp_loc]);
    if (desc == tmp_loc) {
      return;
    }
  }
  swap_with_empty(a, a[desc]);
}

void special_y_move(int *a, int desc, int src) {
  int src_line_number = src / 4 + 1;
  int desc_line_number = desc / 4 + 1;
  int src_col_number = src % 4 + 1;
  int desc_col_number = desc % 4 + 1;
  int x_direct, y_direct;
  if (desc_col_number > src_col_number) {
    x_direct = 1;
  } else if (desc_col_number < src_col_number) {
    x_direct = -1;
  } else {
    x_direct = desc_col_number == 4 ? -1 : 1;
  }
  if (desc_line_number > src_line_number) {
    y_direct = 1;
  } else if (desc_line_number < src_line_number) {
    y_direct = -1;
  } else {
    y_direct = desc_line_number == 4 ? -1 : 1;
  }

  for (int i = 0; i <= 2; i ++) {
    int tmp_loc = src + 1 * x_direct + y_direct * 4 * i;
     swap_with_empty(a, a[tmp_loc]);
     if (desc == tmp_loc)
       return;
  }
  swap_with_empty(a, a[desc]);

}

void swap(int* a, int i, int j) {
  int temp = a[i];
  a[i] = a[j];
  a[j] = temp;
}

void show(int * a) {
  for(int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j ++) {
      if (a[i * 4 + j] == 0) {
        printf(" __ ");
      } else {
        printf(" %2d ", a[i * 4 + j]);
      }
    }
    printf("\n");
  }
  sleep(1);
}

int rand_range(int min, int max) {
  int diff = max - min;
  return (int)(((double)(diff+1)/RAND_MAX)*rand() + min);
}
