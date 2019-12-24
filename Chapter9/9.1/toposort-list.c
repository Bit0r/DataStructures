#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    struct node *next;
    int num;
}Node;

void input(Node *lst[],int n){
    int v,m;
    Node *pnew;
    while(scanf("%d%d",&v,&m)==2){
        pnew=malloc(sizeof(Node));
        pnew->num=m;
        pnew->next=lst[v];
        lst[v]=pnew;
    }
}

void store(int box[],Node *lst[],int n){
    int i;
    Node *cur;
    for(i=1;i<=n;i++){
        for(cur=lst[i];cur!=NULL;cur=cur->next)
            box[cur->num]++;
    }
}

void toposort(int box[],Node *lst[],int n){
    int i,j;
    Node *cur;
    for(i=1;i<=n;i++){//对n个点拓扑排序
        for(j=1;j<=n;j++){//找出一个入度为0的点，并进行输出
            if(box[j]==0){
                printf("%d ",j);
                break;
            }
        }
        if(j==n+1){//有回路，无法进行拓扑排序
            printf("图含有回路!");
            exit(EXIT_FAILURE);
        }
        box[j]=-1;//删除该点
        for(cur=lst[j];cur!=NULL;cur=cur->next)
            box[cur->num]--;
    }
}

int main(){
    int n,box[512]={0};
    Node *lst[512]={NULL};
    scanf("%d",&n);
    input(lst,n);//将输入储存到邻接表
    store(box,lst,n);//将邻接表中所有点的入度储存到盒子里
    toposort(box,lst,n);//利用入度信息进行拓扑排序
    return 0;
}