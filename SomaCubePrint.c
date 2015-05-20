#include<stdio.h>

typedef struct{
  int block[5][5][5];
}Box;

/*-----prototypes-----*/
void printbox(Box);

/*-----fanctions-----*/

//箱の状態を出力する。
void printbox(Box box){
  int x, y, z;
  for(z = 1; z < 4; z++){
    printf("%d 段目\n", z+1);
    for(y = 1; y < 4; y++){
      for(x = 1; x < 4; x++){
	if(box.block[x][y][z] == 0) printf("|  |");
	else if(box.block[x][y][z] == 1) printf("| 1|");
	else if(box.block[x][y][z] == 2) printf("| 2|");
	else if(box.block[x][y][z] == 3) printf("| 3|");
	else if(box.block[x][y][z] == 4) printf("| 4|");
	else if(box.block[x][y][z] == 5) printf("| 5|");
	else if(box.block[x][y][z] == 6) printf("| 6|");
	else if(box.block[x][y][z] == 7) printf("| 7|");
      }
      printf("\n");
    }
  }
}
