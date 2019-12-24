#include<stdio.h>
#include<stdbool.h>
#include<limits.h>
#include<stdlib.h>

int n;
FILE *data,*in,*out;
typedef struct{
    bool known;
    int distance,path;
}Table;

void open(){
    in=fopen("in.txt","r");
    out=fopen("out.txt","w");
}
void close(){
    fclose(in);
    fclose(out);
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

void IniBox(Table box[n+1],int graph[n+1][n+1]){
    int i;
    for(i=0;i<=n;i++){
        box[i].known=false;
        box[i].distance=INT_MAX;
        box[i].path=0;
    }
    box[1].distance=box[1].path=0;
}

int findedge(Table box[n+1],int graph[n+1][n+1]){
    int i,j,v=0,d=INT_MAX;
    for(i=1;i<=n;i++)//遍历这张图
        for(j=1;j<=n;j++)
            if(box[i].known==true&&box[j].known==false&&d>graph[i][j]){//找出离树最近的点v
                v=j;
                d=graph[i][j];//更新最小距离
            }
    return v;//返回点v
}

void prime(Table box[n+1],int graph[n+1][n+1]){
    int v=1,w;//任取一点为第一个入树的点
    while(v){
        box[v].known=true;//将v加入这棵树
        for(w=1;w<=n;w++)//找出所有与v邻接且不在树上的点w
            if(graph[v][w]!=INT_MAX&&box[w].known==false&&box[w].distance>graph[v][w]){
                box[w].distance=graph[v][w];
                box[w].path=v;
            }
        v=findedge(box,graph);//选出离树最近的点v
    }
}

void output(Table box[n+1]){//输出到成图
    char v,w;
    for(int i=2;i<=n;i++){
        v=i+'A'-1;
        w=box[i].path+'A'-1;
        fprintf(out,"%c %c %d\n",v,w,box[i].distance);
    }
}

int main(){
    open();
    fscanf(in,"%d",&n);
    int graph[n+1][n+1];
    Table box[n+1];
    input(graph);
    IniBox(box,graph);
    prime(box,graph);
    output(box);
    close();
    return 0;
}