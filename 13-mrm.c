#include <stdio.h>

/*I-1,V-5,X-10,L-50,C-100,D-500,M-1000*/
/*MMMDCCCLXXXVIII*/
#define LIMIT 15

int mrm(char *s);

int main(){
  char pString[16]="";
  char ch;
  int count=0;
  while((ch=getchar()) != '\n' && count<LIMIT){
    pString[count++] = ch;
  }
  printf("%d\n",mrm(pString));
  return 0;
}

int mrm(char *s){
  char *t=s;
  int sum=0;
  while(*t != '\0'){
    if (*t=='M')
      sum += 1000;
    else if (*t=='D')
      sum += 500;
    else if (*t=='L')
      sum += 50;
    else if (*t=='V')
      sum += 5;
    else if (*t=='C' && (*(t+1)=='M' || *(t+1)=='D'))
      sum -= 100;
    else if (*t=='C')
      sum += 100;
    else if (*t=='X' && (*(t+1)=='C' || *(t+1)=='L'))
      sum -= 10;
    else if (*t=='X')
      sum += 10;
    else if (*t=='I' && (*(t+1)=='X' || *(t+1)=='V'))
      sum -= 1;
    else
      sum += 1;
    t++;
  }
  if (sum>3999)
    return 0;
  else
    return sum;
}
