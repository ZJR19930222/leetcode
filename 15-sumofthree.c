#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 20 // >=3
#define TRUPLES (((MAX_NUM-1)*MAX_NUM)/2)
int Sort(const void *a, const void *b);
int main(){
  int Array[MAX_NUM]={0};
  int Matrix[TRUPLES][3];
  for (int i=0;i<MAX_NUM;i++){
    printf("Enter a number(already %d)>>",i);
    scanf("%d",&Array[i]);
  }
  qsort(Array,MAX_NUM,sizeof(int),Sort);
  int i,j,k;
  int count=0;
  int m1=0,m2=0,m3=0;
  for (i=0;i<MAX_NUM;i++){
    if (m1){
      if (Array[i]==Array[i-1])
	continue;
    }
    else {
      m1++;
    }
    for (j=i+1;j<MAX_NUM;j++){
      if (m2){
	if (Array[j]==Array[j-1])
	  continue;
      }
      else {
	m2++;
      }
      for (k=j+1;k<MAX_NUM;k++){
	if (m3){
	  if (Array[k]==Array[k-1])
	    continue;
	}
	else {
	  m3++;
	}
	if (Array[i]+Array[j]+Array[k]==0){
	  Matrix[count][0] = Array[i];
	  Matrix[count][1] = Array[j];
	  Matrix[count++][2] = Array[k];
	}
      }
      m3=0;// third loop out
    }
    m2=0;// second loop out
  }
  printf("%d\n",count);
  for (i=0;i<count;i++)
    printf("[%d,%d,%d]\n",Matrix[i][0],Matrix[i][1],Matrix[i][2]);
  return 0;
}

int Sort(const void *a, const void *b){
  return *(int*)a-*(int*)b;
}
