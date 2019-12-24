#include<stdio.h>
#include<queue>
#include<limits.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct node{
    struct node *next;
    int num,distance;
}Node;
typedef struct{
    int distance,path;
}Table;

int input(Node *lst[],int n){
    int v,w,s;
    Node *pnew;
    for(int i=0;i<=n;i++)
        lst[i]=NULL;
    while(scanf("%d%d%d",&v,&w,&s)==3){
        pnew=(Node *)malloc(sizeof(Node));
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
        box[i].distance=INT_MAX;
        box[i].path=0;
    }
    box[s].distance=0;
}

void Unweighted(int s,Table box[],Node *lst[]){
    std::queue<int> q;
    Node *cur;
    int v,w;
    q.push(s);
    while(q.empty()==false){
        v=q.front();
        q.pop();
        for(cur=lst[v];cur!=NULL;cur=cur->next){
            w=cur->num;
            if(box[w].distance==INT_MAX){
                box[w].distance=box[v].distance+1;
                box[w].path=v;
                q.push(w);
            }
        }
    }
}

void PrintPath(Table box[],int s,int t){
    if(t==s){
        printf("%d",t);
    }else{
        PrintPath(box,s,box[t].path);
        printf("->%d",t);
    }
}

void output(int s,Table box[],int n){
    for(int i=1;i<=n;i++){
        PrintPath(box,s,i);
        printf("    (%d)\n",box[i].distance);
    }
}

int main(){
    int n,s;
    scanf("%d",&n);
    Table box[n+1];
    Node *lst[n+1];
    s=input(lst,n);
    IniTab(s,box,n);
    Unweighted(s,box,lst);
    output(s,box,n);
    return 0;
}
