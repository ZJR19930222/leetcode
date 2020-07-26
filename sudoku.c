#include <stdio.h>
#include <time.h>

void sdk(int board[9][9]);
int ck(int board[9][9], int row, int col, int num);
int fill(int board[9][9], int row, int col);
void sdk_print(int board[9][9]);
int main(){
  int board[9][9];
  sdk(board);
  clock_t start = clock();
  int flag = fill(board,0,0);
  if (flag)
    sdk_print(board);
  else{
    printf("no solution!\n");
    sdk_print(board);
  }
  printf("time spend>>%g sec.\n",(clock()-start)/(double)CLOCKS_PER_SEC);
  return 0;
}

void sdk(int board[9][9]){
  for (int i=0;i<9;i++){
    printf("Enter %dth row(9)>>",i+1);
    for (int k=0;k<9;k++)
      scanf("%1d",&board[i][k]);
  }
}

void sdk_print(int board[9][9]){
  for (int i=0;i<9;i++){
    for (int j=0;j<9;j++){
      printf("|%d",board[i][j]);
    }
    printf("|\n");
  }
}

int ck(int board[9][9], int row, int col, int num){
  for (int i=0;i<9;i++){
    if (board[row][i]==num || board[i][col]==num)
      return 0;
  }
  for (int i=0;i<3;i++){
    for (int j=0;j<3;j++){
      if (board[(row/3)*3+i][(col/3)*3+j] == num)
	return 0;
    }
  }
  return 1;
}

int fill(int board[9][9], int row, int col){
  if (col == 9){
    row++;
    col=0;
    if (row == 9)
      return 1;
  }
  if (board[row][col]!=0)
    return fill(board,row,col+1);
  else
    for (int i=1;i<=9;i++){
      if (ck(board,row,col,i)){
	board[row][col]=i;
	if (fill(board,row,col+1))
	  return 1;
	else
	  board[row][col]=0;
      }
    }
  return 0;
}
