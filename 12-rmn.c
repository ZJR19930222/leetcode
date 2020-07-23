#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMBER 3999

#define MAX_LEN 20

char pString[MAX_LEN];

void NumToRoman(int num);

int main(){
  int num;
  scanf("%d",&num);
  if (num>MAX_NUMBER || num<=0)
    exit(EXIT_FAILURE);
  NumToRoman(num);
  printf("%s\n",pString);
  return 0;
}
void NumToRoman(int num){
  char *ps = pString;
  int i;
  int tmp=num;
  int digit=1;
  while (tmp>9){
    tmp /= 10;
    digit *=10;
  }
  while (digit>=1){
    tmp = num/digit;
    num %= digit;
    digit /=10;
    if (digit==100){
      for (i=0;i<tmp;i++)
	*ps++ = 'M';
    }
    else if (tmp==9 && digit==10){
      *ps++ = 'C';
      *ps++ = 'M';
    }
    else if (tmp>4 && digit==10){
      *ps++ = 'D';
      for (i=0;i<tmp-5;i++)
	*ps++ = 'C';
    }
    else if (tmp==4 && digit==10){
      *ps++ = 'C';
      *ps++ = 'D';
    }
    else if (digit==10){
      for (i=0;i<tmp;i++)
	*ps++ = 'C';
    }
    else if (tmp==9 && digit==1){
      *ps++ = 'X';
      *ps++ = 'C';
    }
    else if (tmp>4 && digit==1){
      *ps++ = 'L';
      for (i=0;i<tmp-5;i++)
	*ps++ = 'X';
    }
    else if (tmp==4 && digit==1){
      *ps++ = 'X';
      *ps++ = 'L';
    }
    else if (digit==1){
      for (i=0;i<tmp;i++)
	*ps++ = 'X';
    }
    else if (tmp==9 && digit==0){
      *ps++ = 'I';
      *ps++ = 'X';
    }
    else if (tmp>4 && digit==0){
      *ps++ = 'V';
      for (i=0;i<tmp-5;i++)
	*ps++ = 'I';
    }
    else if (tmp==4 && digit==0){
      *ps++ = 'I';
      *ps++ = 'V';
    }
    else {
      for (i=0;i<tmp;i++)
	*ps++ = 'I';
    }
  }
  *ps='\0';
}
