#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
srand((unsigned)time(NULL));
int num, sum;
scanf("%d %d",&num,&sum);
int array[num];
for (int i=0;i<num;++i){
	array[i]=rand()%(2*sum);
}
for (int i=0;i<num;++i){
	int x=array[i];
	for (int j=i+1;j<num;++j){
		if (x+array[j]==sum){
			printf("solution is %d and %d\n",x,array[j]);
			goto done;
		}
	}
}
printf("solution is not existed!\n");
done:
return 0;
}
