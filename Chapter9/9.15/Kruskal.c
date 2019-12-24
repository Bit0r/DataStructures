#include<stdio.h>
#include<stdbool.h>
#include<limits.h>
#include<stdlib.h>
#include<heapapi.h>
#include<string.h>

int n;
FILE *data,*in,*out;
typedef struct node{
    int w,v,d;
    struct node *next;
}Node;

void open(){
    in=fopen("in.txt","r");
    out=fopen("out.txt","w");
}
void close(){
    fclose(in);
    fclose(out);
}

void SizeMerge(int forest[],int root1,int root2){//按大小合并
    if(forest[root1]<forest[root2])//root1是一颗更大的树,则root1成为新树
        forest[root2]=root1;
    else{
        if(forest[root1]==forest[root2])//root1和root2是同样大的树
            forest[root2]+=forest[root1];//把root2当主树,同时大小增加root1的大小
        forest[root1]=root2;//合并两棵树,root2作为新树
    }
}
int Find(int forest[],int x){
    if(forest[x]<=0)//如果x是根,则直接返回
        return x;
    else//如果x不是根,则返回x的父节点的根,同时将x的父指针变为根指针
        return forest[x]=Find(forest,forest[x]);
}

void input(int graph[n+1][n+1]){//无向图用邻接矩阵更方便
    int i,j,d,w,v;
    for(i=0;i<=n;i++)
        for(j=0;j<=n;j++)
            graph[i][j]=INT_MAX;
    while (fscanf(in," %c %c%d",&v,&w,&d)==3){
        v=(char)v-'A'+1;
        w=(char)w-'A'+1;
        graph[v][w]=graph[w][v]=d;
    }
}

void output(Node *box,int graph[n+1][n+1]){
    Node *cur;
    for(cur=box;cur!=NULL;cur=cur->next)
        fprintf(out,"%c %c %d\n",(char)cur->w+'A'-1,(char)cur->v+'A'-1,cur->d);
}

bool findedge(int forest[n+1],int graph[n+1][n+1],int *u,int *v){
    int min=INT_MAX,i,j;
    for(i=1;i<=n;i++)
        for(j=1;j<i;j++)
            if(graph[i][j]<min&&Find(forest,i)!=Find(forest,j)){
                min=graph[i][j];
                *u=i;
                *v=j;
            }
    if(min==INT_MAX)
        return false;
    else
        return true;
}

Node *krusal(int graph[n+1][n+1]){
    int forest[n+1],w,v;
    Node *box=NULL,*pnew;
    memset(forest,-1,(n+1)*sizeof(int));
    forest[0]=0;
    while(findedge(forest,graph,&w,&v)){
        SizeMerge(forest,Find(forest,w),Find(forest,v));
        pnew=malloc(sizeof(Node));
        pnew->w=w;
        pnew->v=v;
        pnew->d=graph[w][v];
        pnew->next=box;
        box=pnew;
    }
    return box;
}

int main(){
    open();
    fscanf(in,"%d",&n);
    int graph[n+1][n+1];
    input(graph);
    Node *box=krusal(graph);
    output(box,graph);
    close();
    return 0;
}
