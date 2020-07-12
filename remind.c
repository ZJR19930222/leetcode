#include <stdio.h>
#include <string.h>

#define max_remind 30 /*最大提醒消息条数*/
#define max_messages 60 /*最大单条信息字符长度*/

int read_line(char *p,int n);

int main(void){
    char Reminders[max_remind][max_messages+3];
    char day_str[3],messages[max_messages+1];/* "23"需要用'2','3','\0'3个位置来存储，
    同理一个长度为max_messages的消息需要容器长度为max_messages+1 */
    int day, i,j, readnum=0;
    for (;;) {
        if (readnum==max_remind){
            printf("到达最大消息条数！");
            break;
        }
        printf("输入一条带日期的消息>>");
        scanf("%2d", &day);// 最多读入两位数字
        if (day==0){
            break;
        }
        sprintf(day_str,"%2d",day);//%2d表明这是右对齐的,方便我们做比较
        read_line(messages,max_messages);// 将消息写入到容器messages中去，值max_messages保证值不会越界
        for (i=0;i<readnum;i++){
            if (strcmp(day_str,Reminders[i])<0){
                break;
            }
        }
        for (j=readnum;j>i;j--){
            strcpy(Reminders[j],Reminders[j-1]);// 将大于day_str的消息从i位置开始往后面拷贝,腾出位置给新消息
        }
        strcpy(Reminders[i],day_str);// 将日期消息拷贝到i行
        strcat(Reminders[i],messages);// 将消息内容拼接起来
        readnum++;
    }
    printf("\n日期提示信息为:\n");
    for (int i = 0; i < readnum; i++)
    {
        printf("%s\n",Reminders[i]);
    }
    return 0;
}

int read_line(char *p,int n){
    int ch,i=0;
    while ((ch = getchar())!='\n')
    {
        if (i<n){
            *(p+(i++))=ch;
        }
    }
    *(p+i)='\0';
    return i;
}