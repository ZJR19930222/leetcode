#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER 4 // Number of samples "298"

char TELLIST[8][5]={"abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"}; // translation table & 7,9 is special

int TrupNumber(char ch);// the number of members for 2~9

char (*TrupleChar(char *str,int num))[NUMBER+1]; // return a pointer of array,don't forget plus one to contain char '\0'

int main()
{
  char sample[NUMBER+1]="";
  printf("请输入%d个数字(1除外！)",NUMBER);
  int count=0;
  int num=1;
  char ch;
  do {
    scanf("%c",&ch);
    if (ch!='\n'&&ch!='1'){
      sample[count++]=ch;
      num *= TrupNumber(ch);
    }
  }while(count<NUMBER);
  char (*pString)[NUMBER+1]; // a pointer of array of NUMBER+1,don't forget number in []
  pString=TrupleChar(sample,num);
  for (int i=0;i<num;i++){
    printf("%s\n",*(pString+i));
  }
  return 0;
}
int TrupNumber(char ch){
  if (ch=='7'||ch=='9'){
    return 4;
  }
  return 3;
}
char (*TrupleChar(char *str,int num))[NUMBER+1]{
  char (*pString)[NUMBER+1]=(char(*)[NUMBER+1])malloc((NUMBER+1)*num);
  char *t=str;
  register int count=1;
  int choice,dd;
  int tt;
  for (;t<&str[NUMBER];t++){
    choice =*t-50;
    dd = t-str;
    tt=TrupNumber(*t);
    for (int i=0;i<num;i++){
      register int nn=(i/count)%tt;
      (*(pString+i))[dd]=TELLIST[choice][nn];// warning *(pString+i)[num] is incorrect
    }
    count *= tt;
  }
  for (int i=0;i<num;i++){
    (*(pString+i))[NUMBER]='\0';
  }
  return pString;
}
