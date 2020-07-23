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
#define LP '['
#define RP ']'
#define PLUS '+'
#define EXP '-'
#define MAX_PATTEN 256

struct MatchTerm {
  int len;
  char *pstring[NUM_MAX_MATCH];
};
char* Read_Line(void);
bool IsRegMatch(char *s, char *p);
char* DelErrorSlashes(char *p, int len);
struct MatchTerm ComplMatch(char *s, char *p);
char* ExpPatten(char *p);

int main(){
  char *String, *Patten;
  printf("\e[33mEnter target String\e[0m>>");
  String = Read_Line();
  printf("\e[33mEnter Patten String\e[0m>>");
  Patten = Read_Line();
  char *NewPatten = ExpPatten(DelErrorSlashes(Patten, strlen(Patten)));
  printf("%s\n",NewPatten);
  
  bool flag;
  flag=IsRegMatch(String,NewPatten);
  if (flag)
    printf("\e[36m整体匹配成功！\e[0m\n");
  else
    printf("\e[35m整体匹配失败！\e[0m\n");
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
    }
    else if (*p==DOT&&*(p+1)==STAR){
      /*-----p=.*### ------*/
      for (;;){
	if (IsRegMatch(s,p+2)){
	  result=true;
	  break;
	}
	if (*(s++)==NL)
	  break;
      }
    }
    else if (*p==DOT&&*(p+1)!=STAR){
      /*-----p=.####------*/
      if (*s!=NL)
	result=IsRegMatch(s+1,p+1);
    }
    else if (*p==LP){
      int choice=0;
      while (*(p+choice+1)!=RP&&*(p+choice+1)!=NL){
	choice++;
      }
      if (*(p+choice+1)==RP&&*(p+choice+2)==STAR){
	char *t = s;
	for (int i=1;i<=choice;i++){
	  if (*t==*(p+i)){
	    do {
	      if (IsRegMatch(++t,p+choice+3)){
		result=true;
		break;
	      }
	    }while (*t==*(p+i));
	    break;
	  }
	}
	if (!result){
	  result=IsRegMatch(s,p+choice+3);
	}
      }else if (*(p+choice+1)==RP&&*(p+choice+2)==PLUS){
	char *t = s;
	bool flag;
	do {
	  flag=false;
	  if (IsRegMatch(t,p+choice+3)){
	    result=true;
	    break;
	  }
	  for (int i=1;i<=choice;i++){
	    if (*t==*(p+i)){
	      flag=true;
	      break;
	    }
	  }
	  t++;
	}while (flag);
	if (!result){
	  result=IsRegMatch(s,p+choice+3);
	}
      }
      else if (*(p+choice+1)==RP){
	for (int i=1;i<=choice;i++){
	  if (*s==*(p+i)){
	    result = IsRegMatch(s+1,p+choice+2);
	    break;
	  }
	}
      }
      else if (*(p+choice+1)==NL&&*(s+1)==NL){
	for (int i=1;i<=choice;i++){
	  if (*s==*(p+i)){
	    result = true;
	    break;
	  }
	}
      }
    }
    else if (*p==SLASHES&&*(p+1)==LP&&*(p+2)==STAR){
      /*----p = \[* ------*/
      do {
	if (IsRegMatch(s,p+3)){
	  result=true;
	  break;
	}
      }while(*(s++)==LP);
    }
    else if (*p==SLASHES&&*(p+1)==LP&&*(p+2)!=STAR){
      /*-----p = \[A -----*/
      if (*s==LP){
	result=IsRegMatch(s+1,p+2);
      }
    }
    else if (*p==SLASHES&&*(p+1)==PLUS){
      result=IsRegMatch(s,p+1);
    }
    /*else if (*p==SLASHES&&*(p+1)==RP&&*(p+2)==STAR){
      ----p = \]* ------
      do {
	if (IsRegMatch(s,p+3)){
	  result=true;
	  break;
	}
      }while(*(s++)==RP);
    }
    else if (*p==SLASHES&&*(p+1)==RP&&*(p+2)!=STAR){
      -----p = \]A -----
      if (*s==RP){
	result=IsRegMatch(s+1,p+2);
      }
    }*/
    else if (*p==SLASHES&&*(p+1)==SLASHES&&*(p+2)==STAR){
      /*----p = \\* ------*/
      do {
	if (IsRegMatch(s,p+3)){
	  result=true;
	  break;
	}
      }while(*(s++)==SLASHES);
    }
    else if (*p==SLASHES&&*(p+1)==SLASHES&&*(p+2)!=STAR){
      /*-----p = \\A -----*/
      if (*s==SLASHES){
	result=IsRegMatch(s+1,p+2);
      }
    }
    else if (*p==SLASHES&&*(p+1)==STAR&&*(p+2)==STAR){
      /*-----p = \** -----*/
      do {
	if (IsRegMatch(s,p+3)){
	  result=true;
	  break;
	}
      }while(*(s++)==STAR);
    }
    else if (*p==SLASHES&&*(p+1)==STAR&&*(p+2)!=STAR){
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
    if (*p==SLASHES && (*(p+1)==SLASHES || *(p+1)==STAR || *(p+1)==DOT || *(p+1)==LP|| *(p+1)==PLUS|| *(p+1)==RP)){
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
  char tmpch,*t=s;
  bool ismt;
  int end,count=0,start=0;
  do {
    end=0;
    ismt = false;
    for (int i=0;*t!=NL;i++){
      tmpch=*(++t);
      *t=NL;
      if (IsRegMatch(s+start,p)){
	end=i;
	ismt=true;
      }
      *t=tmpch;
    }
    if (ismt){
      char *ctp=(char*)malloc(sizeof(char)*(end+2));
      for (int k=0;k<end+1;++k)
	ctp[k]=s[start+k];
      ctp[end+1]=NL;
      mt.pstring[count++]=ctp;
    }
    start += end+1;
    t=&s[start];
    if (*t==NL)
      break;
  }while(count<NUM_MAX_MATCH);
  mt.len=count;
  return mt;
}
char* ExpPatten(char *p){
  char *ttm = (char*)malloc(sizeof(char)*(MAX_PATTEN+1));
  char *t = ttm;
  for (;;){
    if (*p==SLASHES&&*(p+1)==LP){
      *(t++)=*(p++);
      *(t++)=*(p++);
    }
    else if (*p==LP){
      *(t++)=*(p++);
      *(t++)=*(p++);
      while (*p!=RP && *p!=NL){
	if (*p==EXP && *(p+1)!=RP){
	  if (*(p+1)>*(p-1)){
	    for (char temp=*(p-1);temp<*(p+1);temp++){
	      *(t++)=temp+1;
	    }
	  }else {
	    for (char temp=*(p-1);temp>*(p+1);temp--){
	      *(t++)=temp-1;
	    }
	  }
	  p=p+2;
	}else {
	  *(t++)=*(p++);
	}
      }
    }
    else {
      *(t++)=*(p++);
    }
    if (*p==NL){
      *t=NL;
      break;
    }
  }
  return ttm;
}
