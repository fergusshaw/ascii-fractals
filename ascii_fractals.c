#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
  int x;
  int y;
} point;


void print_char(char c, point position, point dims, char display_grid[dims.x][dims.y]);
void print_grid(point dims, char **display_grid);
point add_point(point a, point b);
void sierpinski_carpet(char **current_pattern, int dimensions);


int main(int argc, char* argv[]){

  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  
  int window_height = w.ws_row;
  int window_length = w.ws_col;
  
  point dims = {window_length, window_height};
  point mid_point = {window_length / 2, window_height / 2};
  
  char display_grid[window_height][window_length];
  
  memset(display_grid, ' ', sizeof(display_grid));

  char **arr = malloc(3);
  if (arr == NULL){printf("array alloc fucked out\n"); exit(1);}

  //CHATGPT CODE FOR TESTING!! GET RID OF !! CHURC HRU 
  
  arr[0] = malloc(4 * sizeof(char));  // 3 chars + 1 for the null-terminator
  arr[1] = malloc(4 * sizeof(char));
  arr[2] = malloc(4 * sizeof(char));

  // Check if memory allocation for rows succeeded
  for (int i = 0; i < 3; i++) {
      if (arr[i] == NULL) {
          printf("Memory allocation for row %d failed!\n", i);
          return 1;
      }
  }

  // Initialize the 2D array with values
  arr[0][0] = '#'; arr[0][1] = '#'; arr[0][2] = '#'; arr[0][3] = '\0';
  arr[1][0] = '#'; arr[1][1] = ' '; arr[1][2] = '#'; arr[1][3] = '\0';
  arr[2][0] = '#'; arr[2][1] = '#'; arr[2][2] = '#'; arr[2][3] = '\0';


  sierpinski_carpet(arr, 3);
  
  //printf("terminal is %d rows and %d columns\nmidpoint is %d, %d\n", 
   //      window_height, window_length, mid_point.x, mid_point.y);

  return 0;
}

point add_point(point a, point b){
  point new_point = {a.x + b.x, a.y + b.y};
  return new_point;
}

void sierpinski_carpet(char **current_pattern, int dimensions){
  int new_dims = dimensions * 8;

  char **new_pattern = (char **)malloc(new_dims);
  if (new_pattern == NULL){
    printf("new array allocation did not work\n");
    exit(1);
  }
  
  for (int i = 0; i < new_dims; i++){
    new_pattern[i] = malloc(new_dims);
    if (new_pattern[i] == NULL){
      printf("new row %d alloc failed\n", i);
      exit(1);
    }
  }

  memset(new_pattern, ' ', sizeof(new_pattern));

  for (int new_row = 0; new_row < 3; new_row++){
    for (int new_col = 0; new_col < 3; new_col++){

      for (int row = 0; row < dimensions; row++){
        for (int col = 0; col < dimensions; col++){

          new_pattern[row+new_row][col+new_col] = current_pattern[row][col];
        }
      }

    }
   }

  free(current_pattern);
  point dims = {dimensions, dimensions};
  print_grid(dims, new_pattern);
  free(new_pattern);
  
}

void print_char(char c, point position, point dims, char display_grid[dims.y][dims.x]){
  
  display_grid[position.y][position.x] = c;
  //print_grid(dims, display_grid);

}

void print_grid(point dims, char **display_grid){
  for (int row = 0; row < dims.y; row++){
    for (int col = 0; col < dims.x; col++){
      printf("%c", display_grid[row][col]);
    }
    printf("\n");
  }
}
