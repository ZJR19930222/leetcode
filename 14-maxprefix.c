#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BLOCK 20
#define ITERM 200
char* Max_Prefix(char *pString[], int len);
int main(){
  char ch;
  int i, con, count=0;
  char *pString[ITERM];
  bool flag = true;
  do{
    con=BLOCK;
    char *p = malloc(con+1);
    if (!p){
      printf("malloc failure\n");
      exit(EXIT_FAILURE);
    }
    i=0;
    printf("Enter your string(q exit)>>");
    while((ch=getchar())!='\n'){
      if (i>=con){
	// expand contain
	con += BLOCK;
	char *t = malloc(con+1);
	if (!t){
	  printf("malloc failure\n");
	  exit(EXIT_FAILURE);
	}
	for (int k=0;k<i;k++)
	  t[k]=p[k];
	free(p);
	p=t;
      }
      p[i++]=ch;
    }
    p[i]='\0';
    if (strcmp(p,"q")==0)
      flag=false;
    else
      pString[count++]=p;
  }while(count<ITERM && flag);
  printf("%d\n",count);
  printf("%s\n",Max_Prefix(pString,count));
  return 0;
}
char* Max_Prefix(char *pString[], int len){
  int i,j;
  char ch;
  for (i=0;;i++){
    for (j=0;j<len-1;j++){
      if (pString[j][i]!=pString[j+1][i])
	goto done;
      else if (pString[0][i]=='\0')
	goto done;
    }
  }
  done:
  j=0;
  char *p=malloc(i+1);
  for (;j<i;j++)
    p[j]=pString[0][j];
  p[i]='\0';
  return p;
}
