#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*读入字符*/
char* read_line(void);

/*求得z变换的坐标*/
void Ztransformal(int len,int *x,int *y,int z);

int main(void){
  int row,count=0;
  printf("输入z(row)变量的值>>");
  scanf("%1d",&row);
  char ctemp = getchar();// 消耗掉回车符'\n'
  printf("输入字符串>>");
  char *pString = read_line();
  if (row == 1){
    printf("%s\n",pString);
    exit(EXIT_SUCCESS);
  }
  int len = strlen(pString);
  int column = ((len/(2*row-2))+1)*(row-1);
  char Array[row][column];
  for (int i=0;i<row;++i){
    for (int j=0;j<column;++j){
      Array[i][j] = ' ';
    }
  }
  int x,y;
  while (pString[count]!='\0'){
    Ztransformal(count,&x,&y,row);
    Array[y][x] = pString[count++];// 不要搞错x，y的位置！
  }
  for (int i=0;i<row;++i){
    for (int j=0;j<column;++j){
      printf("%c",Array[i][j]);
    }
    printf("\n");
  }
  char ZpString[len+1];
  count=0;
  for (int i=0;i<row;++i){
    for (int j=0;j<column;++j){
      if ((ctemp=Array[i][j])!=' '){
	ZpString[count++] = ctemp;
      }
    }
  }
  ZpString[len] = '\0';
  printf("%s\n",ZpString);
  return 0;
}
char* read_line(void){
  int BLOCK = 10;
  int count = 0;
  int ch;
  int contain = BLOCK;
  char *p= (char*)malloc(sizeof(char)*(contain+1));
  while ((ch=getchar())!='\n'){
    if (count == contain){
      contain += BLOCK;
      char *temp =(char*)malloc(sizeof(char)*(contain+1)); 
      for (int i=0;i<count;++i){
	temp[i] = p[i];
      }
      free(p);
      p = temp;
    }
    p[count++] = ch;
  }
  p[count] = '\0';
  return p;
}

void Ztransformal(int len,int *x,int *y,int z){
  int base = 2*z-2;
  int remind = len%base;
  int quotient = len/base;
  if (remind < z){
    *x = quotient*(z-1);
    *y = remind;
  } else {
    *x = quotient*(z-1) + remind-z+1;
    *y = z-1 - (remind-z+1);
  }
}
