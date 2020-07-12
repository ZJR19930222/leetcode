#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX 1000
/* 97-122
*rand()%26+97
*/
bool isP(char *p, int l);
int bisP(char *p);
int main(){
srand((unsigned)time(NULL));
char pString[MAX+1];
int ch;
for (int k=0;k<MAX;k++){
	ch = rand()%26 + 97;
	pString[k] = ch;
}
pString[MAX] = '\0';
int max=1,start=0,num;
for (int j=0;j<MAX;++j){
	if ((num=bisP(&pString[j]))>max){
		max = num;
		start = j;
	}
}
for (int k =0;k<max;++k){
	printf("%c",pString[k+start]);
}
printf("\n");
return 0;
}
bool isP(char *p, int l){
	bool flag = true;
	for (int i=0;i<=l/2;++i){
		if (*(p+l-1-i) != *(p+i)){
			flag = false;
			break;
		}
	}
	return flag;
}
int bisP(char *p){
	int max=1;
	int n=1;
	while (p[n] != '\0'){
		if (p[0] == p[n] && isP(p, n+1)){
			max = n+1;
		}
		n++;
	}
	return max;
}
