#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *SAMPLE="3429";
char TELLIST[8][5]={
  "abc",
  "def",
  "ghi",
  "jkl",
  "mno",
  "pqrs",
  "tuv",
  "wxyz"
};
int Convert(char ch);
int main()
{
  int num = 1;
  int len = strlen(SAMPLE);
  for (int i=0;i<len;i++){
    num *=Convert(SAMPLE[i]);
  }
  char pString[num][len+1];
  char *t=SAMPLE;
  register int count=1;
  int choice,dd;
  for (;t<&SAMPLE[len];t++){
    choice =*t-50;
    dd = t-SAMPLE;
    for (int i=0;i<num;i++){
      register int nn=(i/count)%Convert(*t);
      pString[i][dd]=TELLIST[choice][nn];
    }
    count *= Convert(*t);
  }
  for (int i=0;i<num;i++){
    pString[i][len]='\0';
    printf("%s\n",pString[i]);
  }
  return 0;
}
int Convert(char ch){
  if (ch=='7'||ch=='9'){
    return 4;
  }
  return 3;
}
