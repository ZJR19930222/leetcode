#include <stdio.h>
#include <stdbool.h>

bool IsPalindrome(int num);

int main(){
  int num;
  scanf("%d",&num);
  bool flag = IsPalindrome(num);
  if (flag)
    printf("true\n");
  else
    printf("false\n");
}

bool IsPalindrome(int num){
  bool flag = true;
  if (num<0)
    flag = false;
  int t=num;
  int digit;
  int head,end;
  for (digit=1;t>9;digit*=10,t /=10);
  for (int di=1;digit>di;di*=10,digit/=10){
    head = (num/digit)%10;
    end = (num/di)%10;
    if (head != end){
      flag = false;
      break;
    }
  }
  return flag;
}
