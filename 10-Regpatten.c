#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BLOCK 10
#define nt '\0'
#define star '*'
#define dot '.'
#define slashes '\\'

char* read_line(void);
bool RegPatten(char *s, char *p);
char* CheckSlashes(char *p, int len);

int main(){
  char *String, *Patten;
  printf("Enter target String>>");
  String = read_line();
  printf("Enter Patten String>>");
  Patten = read_line();
//printf("%s\n",String);
//printf("%s\n",Patten);
  char *NewPatten = CheckSlashes(Patten, strlen(Patten));
//printf("%s\n",NewPatten);
  bool flag;
  flag=RegPatten(String,NewPatten);
  if (flag)
    printf("匹配成功！\n");
  else
    printf("匹配失败！\n");
  return 0;
}

bool RegPatten(char *s, char *p){
  bool result = true;
  if (*s==nt&&*p==nt);
      /*-----p='\0',s='\0'-----*/
  else if (*p!=nt){
      /*-----p = ###'\0',s = #####'\0' or '\0' -----*/
    if (*p==star){
      /*-----p = *#### -----*/
      result = RegPatten(s,p+1);
    }else if (*p==dot&&*(p+1)==star){
      /*-----p=.*### ------*/
      result=false;
      for (;;){
	if (RegPatten(s,p+2)){
	  result=true;
	  break;
	}
	if (*(s++)==nt)
	  break;
      }
    }else if (*p==dot&&*(p+1)!=star){
      /*-----p=.####------*/
      if (*s==nt)
	result = false;
      else
	result=RegPatten(s+1,p+1);
    }else if (*p==slashes&&*(p+1)==slashes&&*(p+2)==star){
      /*----p = \\* ------*/
      result=false;
      do {
	if (RegPatten(s,p+3)){
	  result=true;
	  break;
	}
      }while(*(s++)==slashes);
    }else if (*p==slashes&&*(p+1)==slashes&&*(p+2)!=star){
      /*-----p = \\A -----*/
      if (*s==slashes){
	result=RegPatten(s+1,p+2);
      }else {
	result=false;
      }
    }else if (*p==slashes&&*(p+1)==star&&*(p+2)==star){
      /*-----p = \** -----*/
      result=false;
      do {
	if (RegPatten(s,p+3)){
	  result=true;
	  break;
	}
      }while(*(s++)==star);
    }else if (*p==slashes&&*(p+1)==star&&*(p+2)!=star){
      /*-----p = \*A -----*/
      if (*s==star){
	result=RegPatten(s+1,p+2);
      }else {
	result=false;
      }
    }else if (*p==slashes&&*(p+1)==dot&&*(p+2)==star){
      /*-----p = \.* -----*/
      result=false;
      do {
	if (RegPatten(s,p+3)){
	  result=true;
	  break;
	}
      }while(*(s++)==dot);
    }else if (*p==slashes&&*(p+1)==dot&&*(p+2)!=star){
      /*-----p = \.A -----*/
      if (*s==dot){
	result=RegPatten(s+1,p+2);
      }else {
	result=false;
      }
    }else if (*(p+1)==star){
      /*------p = A*-----*/
      result=false;
      do {
	if (RegPatten(s,p+2)){
	  result=true;
	  break;
	}
      }while(*(s++)==*p);
    }else if (*(p+1)!=star){
      /*------p = A##-----*/
      if (*s==*p){
	result=RegPatten(s+1,p+1);
      }else {
	result=false;
      }
    }
  }
  else {
    /*----- p='\0',s=##'\0' -----*/
    result=false;
  }
  return result;
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

char* CheckSlashes(char *p, int len){
  char *t=(char*)malloc(sizeof(char)*(len+1));
  char *tmp=t;
  for (;;){
    if (*p==slashes&&*(p+1)==slashes){
      /*----\\----*/
      *(tmp++)=*(p++);
      *(tmp++)=*(p++);
    }else if (*p==slashes&&*(p+1)==star){
      /*----\*----*/
      *(tmp++)=*(p++);
      *(tmp++)=*(p++);
    }else if (*p==slashes&&*(p+1)==dot){
      /*----\.----*/
      *(tmp++)=*(p++);
      *(tmp++)=*(p++);
    }else if (*p==slashes) {
      p++;
    }else {
      *(tmp++)=*(p++);
    }
    if (*p==nt)
      break;
  }
  *tmp=nt;
  return t;
}
