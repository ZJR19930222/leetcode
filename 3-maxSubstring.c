#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK 10

char* read_line(void);
char* maxSubstring(const char p[]);

int main(){
  char *pString, *pResult;
  printf("Enter your string>>");
  pString = read_line();
  pResult = maxSubstring(pString);
  printf("MaxLength substring is '%s' and length is %lu\n",pResult, strlen(pResult));
  return 0;
}

char* read_line(void){
  int contain = BLOCK;
  int count = 0;
  int ch;
  char *p = (char*)malloc(sizeof(char)*(contain+1));
  while ((ch=getchar()) != '\n'){
    /*extend contain dynamically*/
    if (count == contain){
      contain += BLOCK;
      char *temp = (char*)malloc(sizeof(char)*(contain+1));
      for (int k=0;k < count;k++){
	temp[k] = p[k];
      }
      free(p);
      p = temp;
    }
    p[count++] = ch;
  }
  p[count] = '\0';
  return p;
}

char* maxSubstring(const char p[]){
  int max = 0, count = 0, start = 0;
  int k, q;
  do{
    for (k=start;k < count;++k){
      if (p[k] == p[count] || p[count] == '\0'){
	if (count - start > max){
	  max = count-start;
	  q = start;
	}
	start = k+1;
	break;
      }
    }
  } while (p[++count-1] != '\0');
  char *temp = (char*)malloc(sizeof(char)*(max + 1));
  for (int i=0;i<max;++i){
    temp[i] = p[q + i];
  }
  temp[max] = '\0';
  return temp;
}
