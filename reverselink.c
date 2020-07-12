#include <stdio.h>
#include <stdlib.h>

#define TOTAL 3

typedef struct _node {
    int value;
    struct _node *next;
} Node;

Node* create_link(int num);
void link_print(Node* p);
Node* combine_link(Node* a, Node* b);

int main(void){
    Node *q,*p,*c;
    q=create_link(TOTAL);
    printf("输入第二个数字\n");
    p=create_link(4);
    c=combine_link(q,p);
    link_print(c);
}

Node* create_link(int num){
    Node *head=NULL; // 用来记录逆向链表的头部
    int number;
    int count=0;
    do{
        count++;
        printf("请输入数字>>");
        scanf("%d",&number);
        Node *temp = (Node*)malloc(sizeof(Node));
        temp->next=head;
        temp->value=number;
        head=temp;
    } while (count < num);
    return head;
}
void link_print(Node* q){
    int number = 1;
    for (;;++number){
	printf("第%d个节点值:%d\n",number,q->value);
	if (!(q->next)) {
	break;
	}else {
	q=q->next;
	}
    }
}
Node* combine_link(Node* a, Node* b){
    Node *head=NULL,*end=NULL; // 用来记录链表的头部和尾部
    int number;
    int addition=0;
    do{
        number = a->value + b->value + addition;
        addition = number/10;
        number = number%10;
        Node *temp = (Node*)malloc(sizeof(Node));
        temp->next = NULL;
        temp->value = number;
        if (end){
            end->next = temp;
        }else
        {
            head=temp;
        }
        end=temp;
        a=a->next;
        b=b->next;
    } while (a && b);
    if ( addition ){
        Node *temp = (Node*)malloc(sizeof(Node));// 将溢出的高位存储
        temp->next = NULL;
        temp->value = addition;
        end->next = temp;
    }
    return head;
}