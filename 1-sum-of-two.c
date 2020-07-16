#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){
  srand((unsigned)time(NULL));
  int num, sum;
  scanf("%d %d",&num,&sum);
  int array[num];
  for (int i=0;i<num;++i){
    array[i]=rand()%(2*sum);
  }
  for (int i=0;i<num;++i){
    for (int j=i+1;j<num;++j){
      if (array[i] + array[j] == sum){
	printf("solution is %d and %d\n",array[i],array[j]);
	goto done;
      }
    }
  }
  printf("solution is not existed!\n");
  done:
  return 0;
}
