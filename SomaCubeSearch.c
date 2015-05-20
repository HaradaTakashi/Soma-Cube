#include<stdio.h>

typedef struct{
  int block[5][5][5];
}Box;

typedef struct{
  int block[3][3];
}Cube;

int count=0;

/*-----prototypes-----*/
Box initializebox(Box);
Cube selectcube(int);
void putcube(Box, int);
Cube makecubeL();
Cube makecubeT();
Cube makecubeA();
Cube makecubeB();
Cube makecubeP();
Cube makecubeZ();
Cube makecubeV();
int check_cube(Cube cube, Box box, int x, int y, int z);
Cube turncube(Cube, int, int);
Cube turn_T(Cube cube, int turn);
Cube turn_AB(Cube cube, int turn);
Cube turn_P(Cube cube, int turn);
Cube turn_Z(Cube cube, int turn);
Cube turn_V(Cube cube, int turn);
Cube turnx(Cube cube);
Cube turny(Cube cube);
Cube turnz(Cube cube);

/*-----main-----*/
int main(){
  Box  box;
  Cube  cube;

  //box初期化
  box = initializebox(box);
  //処理
  putcube(box,0);
  //出力
  printf("完成形の合計の数は「%d」です。\n", count);
}

/*-----fanctions-----*/
Box initializebox(Box box){
  int x, y, z;
  for(z = 0; z < 5; z++){
    for(y = 0; y < 5; y++){
      for(x = 0; x < 5; x++){
	if(x==0 || y==0 || z==0 || x==4 || y==4 || z==4)box.block[x][y][z] = 2; //5*5の外側はブロックを入らないようにしておく。
	else box.block[x][y][z] = 0; //5*5の内側はすべて空けておく
      }
    }
  }
  return box;
}

Cube selectcube(int i){
  Cube cube;
  //持ってくるブロックを選ぶ
  if(i == 0) cube = makecubeL();
  else if(i == 1) cube = makecubeT();
  else if(i == 2) cube = makecubeA();
  else if(i == 3) cube = makecubeB();
  else if(i == 4) cube = makecubeP();
  else if(i == 5) cube = makecubeZ();
  else if(i == 6) cube = makecubeV();

  return cube;
}

void putcube(Box box, int piecenumber){
  int x=1,y=1,z, turn, i, test;
  Box beforebox = box;
  Cube cube;

  cube = selectcube(piecenumber);  //入れるブロックを選んでくる。
  if(piecenumber==0){  //一つ目のブロック(L字型)は、置き方が2パターンしかない
    for(z = 1; z < 3; z++){
	box.block[x][y][z]=piecenumber+1;
	for(i=0; i<3; i++) box.block[cube.block[i][0]+x][cube.block[i][1]+y][cube.block[i][2]+z]=piecenumber+1;
	putcube(box, piecenumber+1);
	box = beforebox;
    }
  }else{
    //それ以外のブロックを順に入れていく。
    for(z = 1; z < 4; z++){
      for(y = 1; y < 4; y++){
	for(x = 1; x < 4; x++){
	  if(box.block[x][y][z]==0){ //ひとまず一個空いてるかどうか見る
	    for(turn = 0; turn < 12; turn++){ //ブロックを入るまで12通り(ひとつだけ8通り)回転させる
	      if(piecenumber==4 && turn > 7) break;
	      if(check_cube(cube, box, x, y, z)){ //今持っているブロックが入るか調べる。
		box.block[x][y][z]=piecenumber+1; //入るのであれば入れる。
		for(i=0; i<3; i++){
		  box.block[cube.block[i][0]+x][cube.block[i][1]+y][cube.block[i][2]+z]=piecenumber+1;
		}
		if(piecenumber+1 > 6) count++; //完成したらカウントを１足す。
		else putcube(box, piecenumber+1); //未完成ならば再帰させて次のブロックを入れていく。
		box = beforebox; //箱を入れる前の状態に戻す.
	      }
	      cube = turncube(cube, piecenumber, turn); //ブロックを回転させる
	    }
	    cube = selectcube(piecenumber); //入れるブロック回転前に戻す
	  }
	}
      }
    }
  }
}

//L字型 回転は24種類
Cube makecubeL(){
  Cube cube;

  cube.block[0][0]=1;
  cube.block[0][1]=0;
  cube.block[0][2]=0;
  cube.block[1][0]=2;
  cube.block[1][1]=0;
  cube.block[1][2]=0;
  cube.block[2][0]=0;
  cube.block[2][1]=0;
  cube.block[2][2]=1;

  return cube;
}

//T字型 回転は12種類
Cube makecubeT(){
  Cube cube;

  cube.block[0][0]=1;
  cube.block[0][1]=0;
  cube.block[0][2]=0;
  cube.block[1][0]=-1;
  cube.block[1][1]=0;
  cube.block[1][2]=0;
  cube.block[2][0]=0;
  cube.block[2][1]=0;
  cube.block[2][2]=1;

  return cube;
}

//A型(Bと対) 回転は12種類
Cube makecubeA(){
  Cube cube;

  cube.block[0][0]=1;
  cube.block[0][1]=0;
  cube.block[0][2]=0;
  cube.block[1][0]=0;
  cube.block[1][1]=-1;
  cube.block[1][2]=0;
  cube.block[2][0]=1;
  cube.block[2][1]=0;
  cube.block[2][2]=1;

  return cube;
}

//B型(Aと対) 回転は12種類
Cube makecubeB(){
  Cube cube;

  cube.block[0][0]=1;
  cube.block[0][1]=0;
  cube.block[0][2]=0;
  cube.block[1][0]=0;
  cube.block[1][1]=0;
  cube.block[1][2]=1;
  cube.block[2][0]=1;
  cube.block[2][1]=-1;
  cube.block[2][2]=0;

  return cube;
}

//テトラ型 回転は8種類
Cube makecubeP(){
  Cube cube;

  cube.block[0][0]=1;
  cube.block[0][1]=0;
  cube.block[0][2]=0;
  cube.block[1][0]=0;
  cube.block[1][1]=-1;
  cube.block[1][2]=0;
  cube.block[2][0]=0;
  cube.block[2][1]=0;
  cube.block[2][2]=1;

  return cube;
}

//Z字型 回転は12種類
Cube makecubeZ(){
  Cube cube;

  cube.block[0][0]=0;
  cube.block[0][1]=0;
  cube.block[0][2]=1;
  cube.block[1][0]=0;
  cube.block[1][1]=-1;
  cube.block[1][2]=0;
  cube.block[2][0]=0;
  cube.block[2][1]=1;
  cube.block[2][2]=1;

  return cube;
}

//V字型 回転は12種類
Cube makecubeV(){
  Cube cube;

  cube.block[0][0]=1;
  cube.block[0][1]=0;
  cube.block[0][2]=0;
  cube.block[1][0]=0;
  cube.block[1][1]=0;
  cube.block[1][2]=1;
  cube.block[2][0]=0;
  cube.block[2][1]=0;
  cube.block[2][2]=0;

  return cube;
}

//持っているブロックが全部はまるか確かめる
int check_cube(Cube cube, Box box, int x, int y, int z){
  int i;
  //for(i=0; i<3; i++){
  //途中でハマらなくなったら抜ける
  if(box.block[cube.block[0][0]+x][cube.block[0][1]+y][cube.block[0][2]+z]==0&&
     box.block[cube.block[1][0]+x][cube.block[1][1]+y][cube.block[1][2]+z]==0&&
     box.block[cube.block[2][0]+x][cube.block[2][1]+y][cube.block[2][2]+z]==0){
    return 1;
  }
  return 0;
}

//ブロックを回転させる
Cube turncube(Cube cube, int number, int turn){
  if(number==1){
    cube = turn_T(cube, turn);
  }else if(number==2 || number==3){
    cube = turn_AB(cube, turn);
  }else if(number==4){
    cube = turn_P(cube, turn);
  }else if(number==5){
    cube = turn_Z(cube, turn);
  }else if(number==6){
    cube = turn_V(cube, turn);
  }
  return cube;
}

//T型の回転
Cube turn_T(Cube cube, int turn){
  if(turn < 1){
    cube = turnz(cube); //z軸回転
  }else if(turn == 1){
    cube = turny(cube); //y軸回転
  }else if(turn == 2){
    cube = turnx(cube); //x軸回転
  }else if(turn == 3){
    cube = turnz(cube); //z軸回転
  }else if(turn == 4){
    cube = turny(cube); //y軸回転
  }else if(turn == 5){
    cube = turnz(cube); //z軸回転
  }else if(turn == 6){
    cube = turnx(cube); //x軸回転
  }else if(turn == 7){
    cube = turnz(cube); //z軸回転
  }else if(turn == 8){
    cube = turny(cube); //y軸回転
  }else if(turn == 9){
    cube = turnx(cube); //x軸回転
  }else if(turn == 10){
    cube = turnz(cube); //z軸回転
  }
  return cube;
}

//A型の回転 & B型の回転
Cube turn_AB(Cube cube, int turn){
  if(turn%4 != 3) cube = turnz(cube); //z軸回転
  else cube = turny(cube); //y軸回転
  return cube;
}

//テトラ型の回転
Cube turn_P(Cube cube, int turn){
  if(turn%4 != 3){
    cube = turnz(cube); //z軸回転
  }else{
    cube = turnx(cube); //x軸回転
  }
  return cube;
}

//Z型の回転
Cube turn_Z(Cube cube, int turn){
  if(turn < 3){
    cube = turnz(cube); //z軸回転
  }else if(turn == 3){
    cube = turnx(cube); //x軸回転
  }else if(turn == 4){
    cube = turnz(cube); //z軸回転
  }else if(turn == 5){
    cube = turnx(cube); //x軸回転
  }else if(turn > 5 && turn < 9){
    cube = turnz(cube); //z軸回転
  }else if(turn == 9){
    cube = turny(cube); //y軸回転
    cube = turny(cube); //y軸回転
    cube = turny(cube); //y軸回転
  }else if(turn == 10){
    cube = turnz(cube); //z軸回転
  }
  return cube;
}


//V型の回転
Cube turn_V(Cube cube, int turn){
  if(turn%4 != 3) cube = turnz(cube); //z軸回転
  else if(turn == 3) cube = turny(cube); //y軸回転
  else if(turn == 7) cube = turnx(cube); //x軸回転
  return cube;
}

//x軸回転
Cube turnx(Cube cube){
  int i, temp;
  for(i=0; i<3; i++){
    temp = cube.block[i][1];
    cube.block[i][1]=cube.block[i][2];
    cube.block[i][2]=temp*(-1);
  }
  return cube;
}

//y軸回転
Cube turny(Cube cube){
  int i, temp;
  for(i=0; i<3; i++){
    temp = cube.block[i][0];
    cube.block[i][0]=cube.block[i][2];
    cube.block[i][2]=temp*(-1);
  } 
  return cube;
}

//z軸回転
Cube turnz(Cube cube){
  int i, temp;
   for(i=0; i<3; i++){
      temp = cube.block[i][0];
      cube.block[i][0]=cube.block[i][1];
      cube.block[i][1]=temp*(-1);
    }
   return cube;
}
