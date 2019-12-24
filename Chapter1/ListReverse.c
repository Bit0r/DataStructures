#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node *next;
}Node;
typedef struct{
    Node *front;
    Node *rear;
}List;

void Build(List *pl){
    int i;
    Node *pnew=malloc(sizeof(Node));
    pnew->data=0;
    pl->front=pl->rear=pnew;
    for(i=1;i<15;i++){
        pnew=malloc(sizeof(Node));
        pnew->data=i;
        pl->rear->next=pnew;
        pl->rear=pnew;
    }
    pl->rear->next=NULL;
}

/* 
1.设该函数能将以h开头的链反转
2.如果h开头的链只有一个或没有，则链的前后都是该节点
3.将h->next开头的链反序，则front为h->next，rear为最后一个
4.将h移到rear之后，同时更新rear
*/
void Reverse(List *pl,Node *h){
    if(h==NULL||h->next==NULL){
        pl->front=pl->rear=h;
    }else{
        Reverse(pl,h->next);
        pl->rear->next=h;
        pl->rear=h;
        h->next=NULL;
    }
}

void Print(List *pl){
    Node *cur;
    for(cur=pl->front;cur!=NULL;cur=cur->next)
        printf("%d ",cur->data);
}

int main(){
    List test;
    Build(&test);
    Reverse(&test,test.front);
    Print(&test);
    return 0;
}