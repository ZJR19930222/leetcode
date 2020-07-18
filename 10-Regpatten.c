#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NUM_MAX_MATCH 20
#define BLOCK 10
#define NL '\0'
#define STAR '*'
#define DOT '.'
#define SLASHES '\\'

struct MatchTerm {
  int len;
  char *pstring[NUM_MAX_MATCH];
};
char* Read_Line(void);
bool IsRegMatch(char *s, char *p);
char* DelErrorSlashes(char *p, int len);
struct MatchTerm ComplMatch(char *s, char *p);

int main(){
  char *String, *Patten;
  printf("\e[33mEnter target String\e[0m>>");
  String = Read_Line();
  printf("\e[33mEnter Patten String\e[0m>>");
  Patten = Read_Line();
  char *NewPatten = DelErrorSlashes(Patten, strlen(Patten));
  bool flag;
  flag=IsRegMatch(String,NewPatten);
  if (flag)
    printf("\e[36m匹配成功！\e[0m\n");
  else
    printf("\e[35m匹配失败！\e[0m\n");
  struct MatchTerm resultP;
  resultP=ComplMatch(String,NewPatten);
  int l = resultP.len;
  for (int i=0;i<l;++i){
    printf("\e[32m%s\e[0m\n",resultP.pstring[i]);
  }
  return 0;
}

bool IsRegMatch(char *s, char *p){
  bool result = false;
  if (*s==NL&&*p==NL)
    /*-----p='\0',s='\0'-----*/
    result=true;
  else if (*p!=NL){
      /*-----p = ###'\0',s = #####'\0' or '\0' -----*/
    if (*p==STAR){
      /*-----p = *#### -----*/
      result = IsRegMatch(s,p+1);
    }else if (*p==DOT&&*(p+1)==STAR){
      /*-----p=.*### ------*/
      for (;;){
	if (IsRegMatch(s,p+2)){
	  result=true;
	  break;
	}
	if (*(s++)==NL)
	  break;
      }
    }else if (*p==DOT&&*(p+1)!=STAR){
      /*-----p=.####------*/
      if (*s!=NL)
	result=IsRegMatch(s+1,p+1);
    }else if (*p==SLASHES&&*(p+1)==SLASHES&&*(p+2)==STAR){
      /*----p = \\* ------*/
      do {
	if (IsRegMatch(s,p+3)){
	  result=true;
	  break;
	}
      }while(*(s++)==SLASHES);
    }else if (*p==SLASHES&&*(p+1)==SLASHES&&*(p+2)!=STAR){
      /*-----p = \\A -----*/
      if (*s==SLASHES){
	result=IsRegMatch(s+1,p+2);
      }
    }else if (*p==SLASHES&&*(p+1)==STAR&&*(p+2)==STAR){
      /*-----p = \** -----*/
      do {
	if (IsRegMatch(s,p+3)){
	  result=true;
	  break;
	}
      }while(*(s++)==STAR);
    }else if (*p==SLASHES&&*(p+1)==STAR&&*(p+2)!=STAR){
      /*-----p = \*A -----*/
      if (*s==STAR){
	result=IsRegMatch(s+1,p+2);
      }
    }else if (*p==SLASHES&&*(p+1)==DOT&&*(p+2)==STAR){
      /*-----p = \.* -----*/
      do {
	if (IsRegMatch(s,p+3)){
	  result=true;
	  break;
	}
      }while(*(s++)==DOT);
    }else if (*p==SLASHES&&*(p+1)==DOT&&*(p+2)!=STAR){
      /*-----p = \.A -----*/
      if (*s==DOT){
	result=IsRegMatch(s+1,p+2);
      }
    }else if (*(p+1)==STAR){
      /*------p = A*-----*/
      do {
	if (IsRegMatch(s,p+2)){
	  result=true;
	  break;
	}
      }while(*(s++)==*p);
    }else if (*(p+1)!=STAR){
      /*------p = A##-----*/
      if (*s==*p){
	result=IsRegMatch(s+1,p+1);
      }
    }
  }
  return result;
}
char* Read_Line(void){
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

char* DelErrorSlashes(char *p, int len){
  char *t=(char*)malloc(sizeof(char)*(len+1));
  char *tmp=t;
  for (;;){
    if (*p==SLASHES&&*(p+1)==SLASHES){
      /*----\\----*/
      *(tmp++)=*(p++);
      *(tmp++)=*(p++);
    }else if (*p==SLASHES&&*(p+1)==STAR){
      /*----\*----*/
      *(tmp++)=*(p++);
      *(tmp++)=*(p++);
    }else if (*p==SLASHES&&*(p+1)==DOT){
      /*----\.----*/
      *(tmp++)=*(p++);
      *(tmp++)=*(p++);
    }else if (*p==SLASHES) {
      p++;
    }else {
      *(tmp++)=*(p++);
    }
    if (*p==NL)
      break;
  }
  *tmp=NL;
  return t;
}

struct MatchTerm ComplMatch(char *s, char *p){
  struct MatchTerm mt;
  char tmpch;
  char *t=s;
  bool flag;
  int count=0;
  int start=0;
  do {
    int end=0;
    bool ismt = false;
    for (int i=0;*t!=NL;i++){
      tmpch=*(++t);
      *t=NL;
      flag = IsRegMatch(s+start,p);
      *t=tmpch;
      if (flag){
	end=i;
	ismt=true;
      }
    }
    if (ismt){
      char *ctp=(char*)malloc(sizeof(char)*(end+2));
      for (int k=0;k<end+1;++k)
	ctp[k]=s[start+k];
      ctp[end+1]=NL;
      mt.pstring[count]=ctp;
      count++;
    }
    start += end+1;
    t=&s[start];
    if (*t==NL)
      break;
  }while(count<NUM_MAX_MATCH);
  mt.len=count;
  return mt;
}
