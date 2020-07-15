#include <stdio.h>
#include <ctype.h>

#define INF_MAX 2147483647
#define INF_MIN -2147483648

int StrToNum(char ch);
int ReadNum(void);

int main(){
int num = ReadNum();
printf("%d\n",num);
return 0;
}

int StrToNum(char ch){
  int num;
  if (ch>='0' && ch<='9'){
    num = (int)ch - 48;
  } else {
    num = (int)ch + 10;
  }
  return num;
}
/* 43+45-*/
int ReadNum(void){
  int count=0, sum=0, flag=0, isOverFlow=0;
  int ch, t;
  int head;
  char sign = '+';
  printf("Enter string>>");
  while (isspace(ch=getchar()));
  do{
    t = StrToNum(ch);
    if (flag==0 && (t==53 || t==55)){
      sign = t==53?'+':'-';
    } else if (t>9){
      break;
    } else if (count==0 && t==0);
    else {
      if (count==0){
      }
      if ((count==9 && (sum>214748364||(sum == 214748364 && t>7))) || count>9){
	sum = sign=='-'?INF_MIN:INF_MAX;
	isOverFlow = 1;
	break;
      }
      sum = t + sum*10;
      count++;
    }
    ch = getchar();
    flag = 1;
  } while (ch != '\n');
  return isOverFlow?sum:(sign=='-'?(-1*sum):sum);
}
