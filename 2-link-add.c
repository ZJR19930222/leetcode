#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL 3
typedef struct _node {
  int value;
  struct _node *next;
} Node;

Node* create_node(int num);
void node_print(Node *a);
Node* conbime_node(Node *a, Node *b);
int main(){
  Node *a,*b;
  a=create_node(TOTAL);
  printf("输入第二个数字\n");
  b=create_node(TOTAL);
  node_print(conbime_node(a,b));
  return 0;
}
Node* create_node(int num){
  Node *head=NULL;
  int counts=0,n;
  printf("输入一个数字>>");
  do {
    scanf("%1d",&n);
    Node *tmp=(Node*)malloc(sizeof(Node));
    tmp->next=head;
    tmp->value=n;
    head = tmp;
  } while (++counts < num );
  return head;
}
void node_print(Node *a){
  for (int i=0;;++i){
    printf("第%d个节点值为%d\n",i+1,a->value);
    if (a->next){
      a=a->next;
    }else{
      break;
    }
  }
}
Node* conbime_node(Node *a, Node *b){
  int counts=0,addition=0,num;
  Node *head=NULL,*end=NULL;
  do {
    num=a->value+b->value+addition;
    addition=num/10;
    num %=10;
    Node *tmp=(Node*)malloc(sizeof(Node));
    tmp->next=NULL;
    tmp->value=num;
    if (end){
      end->next=tmp;
    }else{
      head=tmp;
    }
    end=tmp;
    a=a->next;
    b=b->next;
  }while (a&&b);
  if (addition){
    Node *tmp=(Node*)malloc(sizeof(Node));
    tmp->next=NULL;
    tmp->value=addition;
    end->next=tmp;
  }
  return head;
}
