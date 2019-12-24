#include<stdio.h>
#include<stdlib.h>

void input(int mat[51][51],int n){
    int u,v;
    while(2==scanf("%d%d",&u,&v))
        mat[u][v]=1;
}

void store(int box[],int mat[][51],int n){
    int i,j,s;
    for(j=1;j<=n;j++){
        for(i=1,s=0;i<=n;i++)
            if(mat[i][j]==1)
                s++;
        box[j]=s;
    }
}

void toposort(int box[],int mat[][51],int n){
    int i,j,k;
    for(i=1;i<=n;i++){//对n个点拓扑排序
        for(j=1;j<=n;j++)
            if(box[j]==0){//找出一个入度为0的点,并进行输出
                printf("%d ",j);
                break;
            }
        if(j==n+1){//找不到点，结束程序
            printf("图含有回路!");
            exit(EXIT_FAILURE);
        }
        box[j]=-1;//删除该点
        for(k=1;k<=n;k++)
            if(mat[j][k])
                box[k]--;
    }
}

int main(){
    int n,box[51]={0},mat[51][51]={0};
    scanf("%d",&n);
    input(mat,n);
    store(box,mat,n);
    toposort(box,mat,n);
    return 0;
}