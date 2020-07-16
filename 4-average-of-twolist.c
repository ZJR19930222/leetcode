#include <stdio.h>
int sum(int n,int *a,int m,int *b,int *num);
int split(int a[], int low, int high);
void fun(int *a, int low, int high);

int main() {
  int a1, a2, num;
  double result;
  int n1=0, n2=0;
  printf("Enter two number>>");
  scanf("%d %d",&a1, &a2);
  int list1[a1], list2[a2];
  printf("first array\n");
  while (n1<a1){
    printf("Enter a number>>");
    scanf("%d",&list1[n1++]);
  }
  fun(list1, 0, a1 - 1);
  printf("second array\n");
  while (n2<a2){
    printf("Enter a number>>");
    scanf("%d",&list2[n2++]);
  }
  fun(list2, 0, a2 - 1);
  int tmp=a1+a2;
  num = sum(a1, list1, a2, list2, &tmp);
  printf("%d\n",tmp);
  result = (double)num/tmp;
  printf("%.4f\n",result);
  return 0;
}
int sum(int n,int *a,int m,int *b,int *num){
  int total = 0;
  if (n==0){
    for (int i = 0; i < m; ++i) {
	total += b[i];
    }
  }else if (m==0){
    for (int i = 0; i < n; ++i) {
	total += a[i];
    }
  }else if (a[0]<b[0]) {
    total += a[0];
    total += sum(n-1,a+1, m, b, num);
  }else if (a[0]>b[0]) {
    total += b[0];
    total += sum(n,a, m-1, b+1, num);
  }else {
    *num -= 1;
    total += b[0];
    total += sum(n-1,a+1, m-1, b+1, num);
  }
  return total;
}
int split(int a[], int low, int high){
  int tmp = a[low];
  for (;;){
    while (tmp<a[high])
      high--;
    if (low >= high)
      break;
    a[low++] = a[high];
    while (tmp>a[low])
      low++;
    if (low >= high)
      break;
    a[high--] = a[low];
  }
  a[high] = tmp;
  return high;
}
void fun(int *a, int low, int high){
  int i;
  if (low>=high)
    return;
  i = split(a, low, high);
  fun(a, low, i - 1);
  fun(a, i + 1, high);
}
