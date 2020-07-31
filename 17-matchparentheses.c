#include <stdio.h>

#define la '('
#define ra ')'
#define LEN 100

char pString[LEN]; // 会自动被初始化
int Max_matchp(char *s);

int main()
{
  int count=0;
  int ch;
  while((ch=getchar())!='\n'){
    if (ch=='l')
      pString[count++]=la;
    else if (ch=='r')
      pString[count++]=ra;
  }
  printf("%s\n",pString);
  printf("%d\n",Max_matchp(pString));
  return 0;
}
int Max_matchp(char *s){// )())((()))()()()
  int count,grade,max=0;
  char *t=s,*start=s;
  do {
    count=0;
    grade=0;
    while (*t!='\0'){
      if (*t==la)
	grade++;
      else
	grade--;
      if (grade<0){
	if (count>max)
	  max = count;
	break;
      }
      else if (grade==0 && *(t+1)=='\0'){
	count++;
	if (count>max)
	  max = count;
	break;
      }
      /* *t-->) */
      count++;
      t++;
    }
    if (count==0){
      t=++start;
    }
    else{
      start=++t;
    }
  }while(*start!='\0');
 return max; 
}
