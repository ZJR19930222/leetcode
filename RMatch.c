#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BLOCK 20
#define MAX_MATCH_TERM 200
#define MAX_PATTEN_EXPAND 256
#define NL '\0'
#define STAR '*'
#define DOT '.'
#define SLASH '\\'
#define LP '['
#define RP ']'
#define PLUS '+'
#define SUBTR '-'

typedef struct MatchTerm {
  int len;
  char *pstring[MAX_MATCH_TERM];
} mt;

char* Read_Line(void);

bool IsMatch(char *s, char *p);

char* DelErrorSlash(char *p, int len);

char* ExpPatten(char *p);

mt ComplMatch(char *s, char *p);

void CheckError(const char *p);

int main(void){
  char *String, *Patten;
  printf("\e[33mEnter target String\e[0m>>");
  String = Read_Line();
  printf("\e[33mEnter Patten String\e[0m>>");
  Patten = Read_Line();

  char *NewPatten = DelErrorSlash(Patten, strlen(Patten));
  CheckError(NewPatten);
  NewPatten = ExpPatten(NewPatten);
  printf("%s\n",NewPatten);
  
  bool flag;
  flag=IsMatch(String,NewPatten);
  if (flag)
    printf("\e[36m整体匹配成功！\e[0m\n");
  else
    printf("\e[35m整体匹配失败！\e[0m\n");
  mt resultP;
  resultP=ComplMatch(String,NewPatten);
  int l = resultP.len;
  for (int i=0;i<l;++i){
    printf("\e[32m%s\e[0m\n",resultP.pstring[i]);
  }
  return 0;
}

char* Read_Line(void){
  int con=BLOCK, n=0, ch;
  char* p=malloc(con+1);
  while ((ch=getchar()) != '\n'){
    if (n == con){
      con += BLOCK;
      char* t = malloc(con+1);
      for (int k=0;k < n;k++)
	t[k]=p[k];
      free(p);
      p=t;
    }
    p[n++]=ch;
  }
  p[n]='\0';
  return p;
}

char* DelErrorSlash(char *p, int len){
  char *q=malloc(len+1);
  char ch, *t=q;
  while (*p != NL){
    if (*p == SLASH){
      ch = *(p+1);
      switch (ch){
	case SLASH:
	case DOT:
	case STAR:
	case PLUS:
	case LP:
	case RP:
	  *t++=*p++;
	  *t++=*p++;
	  break;
	default:
	  p++;
      }
    }
    else
      *t++=*p++;
  }
  *t=NL;
  return q;
}

bool IsMatch(char *s, char *p){
  bool fi = false;
  if (*s==NL && *p==NL)// string='\0',patten='\0'
    fi = true;
  else if (*p != NL){
    // patten=###'\0', string='\0' or ###'\0'
    if (*p==STAR)
      // patten=*###
      fi = IsMatch(s,p+1);
    else if (*p==DOT && *(p+1)==STAR){
      // patten=.*###
      do{
	if (IsMatch(s,p+2)){
	  fi = true;
	  break;
	}
      }while (*s++ != NL);
    }
    else if (*p==DOT){
      // patten=.###
      if (*s != NL)
	fi = IsMatch(s+1,p+1);
    }
    else if (*p==LP){
      // patten=[#####]###
      int n=1;
      while (*(p+n) != RP)
	n++;
      // [123...](n)
      if (*(p+n+1)==STAR){
	// [123..](n)*(n+1)
	char *t = s;
	for (int i=1;i<n;i++){
	  if (*t==*(p+i)){
	    // string = A###,patten=[123..A(i)..]*###
	    do{
	      if (IsMatch(++t,p+n+2)){
		fi = true;
		break;
	      }
	    }while (*t==*(p+i));
	    break;
	  }
	}
	if (!fi)
	  fi = IsMatch(s,p+n+2);
      }
      else if (*(p+n+1)==PLUS){
	// string=##A###,patten=[123..A...]+###
	bool flag;
	int i;
	do{
	  flag=false;
	  if (IsMatch(s,p+n+2)){
	    fi = true;
	    break;
	  }
	  // string=##A###,patten=[123..A...]+###
	  for (i=1;i<n;i++){
	    if (*s==*(p+i)){
	      flag=true;
	      break;
	    }
	  }
	  s++;
	}while (flag);
      }
      else {
	for (int i=1;i<n;i++){
	  if (*s==*(p+i)){
	    fi = IsMatch(s+1,p+n+1);
	    break;
	  }
	}
      }
    }
    else if (*p==SLASH && *(p+2)==STAR){
      do{
	if (IsMatch(s,p+3)){
	  fi = true;
	  break;
	}
      }while (*s++==*p+1);
    }
    else if (*p==SLASH){
      if (*s==*(p+1))
	fi = IsMatch(s+1,p+2);
    }
    else if (*(p+1)==STAR){
      do{
	if (IsMatch(s,p+2)){
	  fi = true;
	  break;
	}
      }while (*s++==*p);
    }
    else {
      if (*s==*p)
	fi = IsMatch(s+1,p+1);
    }
  }
  return fi;
}

mt ComplMatch(char *s, char *p){ 
  mt result;
  char ch, *t;
  int end, count=0;
  do {
    t=s;
    end=0;
    while (*t++ != NL){
      ch=*t;
      *t=NL;
      if (IsMatch(s,p))
	end=t-s;
      *t=ch;
    }
    if (end){
      char *tt=(char*)malloc(sizeof(char)*(end+1));
      for (int k=0;k<end;++k)
	tt[k]=s[k];
      tt[end]=NL;
      result.pstring[count++]=tt;
    }
    s = s + (end>1?end:1);
    if (*s==NL)
      break;
  }while(count<MAX_MATCH_TERM);
  result.len=count;
  return result;
}

char* ExpPatten(char *p){
  char *q=malloc(MAX_PATTEN_EXPAND+1);
  char *t =q;
  for (;;){
    if (*p==SLASH){
      *t++=*p++;
      *t++=*p++;
    }
    else if (*p==LP){
      *t++=*p++;
      *t++=*p++;
      // t=[#&,p=[#&
      while (*p!=RP){
	if (*p==SUBTR && *(p+1)!=RP){
	  // p=[##-#...]
	  if (*(p+1)>*(p-1)){
	    for (char temp=*(p-1);temp<*(p+1);temp++){
	      *t++=temp+1;
	    }
	  }
	  else {
	    for (char temp=*(p-1);temp>*(p+1);temp--){
	      *t++=temp-1;
	    }
	  }
	  p=p+2;
	}
	else {
	  *t++=*p++;
	}
      }
    }
    else {
      *t++=*p++;
    }
    if (*p==NL){
      *t=NL;
      break;
    }
  }
  return q;
}

void CheckError(const char *p){
  int n=0;
  int count = 0;
  while(p[n] != NL){
    if (p[n]==SLASH)
      n++;
    else if (p[n]==LP)
      count++;
    else if (p[n]==RP && count!=0)
      count--;
    n++;
  }
  if (count > 0){
    printf("some [ is not matched with ]\n");
    exit(EXIT_FAILURE);
  }
}

