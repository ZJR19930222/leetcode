#include <stdio.h>
#include <stdbool.h>

int reverse(int a);

int main(){
  printf("请输入一个数-2147483648<=d<2147483648:");
  int num;
  scanf("%d",&num);
  int result = reverse(num);
  printf("%d\n",result);
  return 0;
}

int reverse(int a){
  bool sign = a<0?true:false;
  if (sign)
    a = -1*a;
  int digit = 1, t = a;
  while (t>9){
    t /=10;
    digit *=10;
  }
  int head = a%10, di = digit;
  for (t=0;a>0;){
    di /=10;
    a /=10;
    t += (a%10)*di;
  }
  if ((digit>100000000 && head>2) || (head==2 && t>147483648)){
    t = 0;
  } else {
    t = t + head*digit;
    t = sign?(-1*t):t;
  }
  return t;
}
