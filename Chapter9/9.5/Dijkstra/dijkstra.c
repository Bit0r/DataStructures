#include<stdio.h>
#include<stdbool.h>
#include<limits.h>
#include<stdlib.h>

typedef struct node{
    struct node *next;
    int num,distance;
}Node;
typedef struct{
    bool known;
    int distance,path;
}Table;

int input(Node *lst[],int n){
    int v,w,s;
    Node *pnew;
    for(int i=0;i<=n;i++)
        lst[i]=NULL;
    while(scanf("%d%d%d",&v,&w,&s)==3){
        pnew=malloc(sizeof(Node));
        pnew->num=w;
        pnew->distance=s;
        pnew->next=lst[v];
        lst[v]=pnew;
    }
    scanf("%d",&s);
    return s;
}

void IniTab(int s,Table box[],int n){
    int i;
    for(i=1;i<=n;i++){
        box[i].known=false;
        box[i].distance=INT_MAX;
        box[i].path=0;
    }
    box[s].distance=0;
}

int FindMin(Table box[],int n){
    int i,min=INT_MAX,t=0;
    for(i=1;i<=n;i++){
        if(box[i].known==false&&min>box[i].distance){
            t=i;
            min=box[i].distance;
        }
    }
    return t;
}

void dijkstra(Table box[],Node *lst[],int n){
    int v,w;
    Node *cur;
    while(0!=(v=FindMin(box,n))){
        box[v].known=true;
        for(cur=lst[v];cur!=NULL;cur=cur->next){
            w=cur->num;
            if(box[w].known==false){
                box[w].distance=box[v].distance+cur->distance;
                box[w].path=v;
            }
        }
    }
}

void printpath(Table box[],int source,int end){
    if(end==source)
        printf("%d",source);
    else{
        printpath(box,source,box[end].path);
        printf("->%d",end);
    }
}

void output(Table box[],int s,int n){
    for(int i=1;i<=n;i++){
        printpath(box,s,i);
        printf("(%d)\n",box[i].distance);
    }
}

int main(){
    int n,s;
    scanf("%d",&n);
    Table box[n+1];
    Node *lst[n+1];
    s=input(lst,n);
    IniTab(s,box,n);
    dijkstra(box,lst,n);
    output(box,s,n);
    return 0;
}
