#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_LEN 20

int lst[MAX_LEN];
int ThreeClose(int num);
int main(){
  srand((unsigned)time(NULL));
  for (int i=0;i<MAX_LEN;i++)
    lst[i]=rand()%(MAX_LEN/2)-MAX_LEN/4;
  int num;
  printf("Enter a number>>");
  scanf("%d", &num);
  clock_t start = clock();
  int result = ThreeClose(num);
  printf("result=%d\n",result);
  for (int i=0;i<MAX_LEN;i++)
    printf("%d\n",lst[i]);
  printf("time spend>>%g sec.\n",(clock()-start)/(double)CLOCKS_PER_SEC);
  return 0;
}

int ThreeClose(int num){
  int tmp = lst[0]+lst[1]+lst[2];
  int diff = abs(tmp-num);
  for (int i=0;i<MAX_LEN;i++){
  for (int j=i+1;j<MAX_LEN;j++){
  for (int k=j+1;k<MAX_LEN;k++){
    if (diff==0){
      return num;
    }
    else if (abs(lst[i]+lst[j]+lst[k]-num)<diff){
      tmp = lst[i]+lst[j]+lst[k];
      diff = abs(tmp-num);
    }
  }
  }
  }
  return tmp;
}
