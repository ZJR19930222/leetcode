#include <stdio.h>
#include <stdlib.h>

#define BLOCK 20
int* Read_Number(int *n);
int Max_Container(const int *ls, int len);
int main(){
  int length;
  int *list = Read_Number(&length);
  printf("%d\n",length);
  printf("%d\n",Max_Container(list,length));
  return 0;
}
int* Read_Number(int *n){
  int con = BLOCK;
  int k=0;
  int *p=(int*)malloc(sizeof(int)*con);
  int num;
  do {
    printf("Enter a number(-1 end)>>");
    scanf("%d",&num);
    if (num==-1)
      break;
    if (k>=con){
      // need expend container
      int *t=(int*)malloc(sizeof(int)*(con+BLOCK));
      for (int i=0;i<con;i++)
	t[i]=p[i];
      con += BLOCK;
      p=t;
    }
    p[k++]=num;
  } while (1);
  *n=k;
  return p;
}
int Max_Container(const int *ls, int len){
  int max=0;
  int preceding=0;
  for (int i=0;i<len;i++){
    if (ls[i]>preceding){
      preceding=ls[i];
      for (int j=i+1;j<len;j++){
	if (ls[i]<=ls[j]){
	  if (ls[i]*(j-i)>max)
	    max = ls[i]*(j-i);
	}
	else {
	  if (ls[j]*(j-i)>max)
	    max = ls[j]*(j-i);
	}
      }
    }
  }
  return max;
}
