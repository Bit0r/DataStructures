#include<stdio.h>
#include<string.h>
#define K 1024

void DepthMerge(int forest[],int root1,int root2){//按高度合并
    if(forest[root2]<forest[root1])//root2是一颗更深的树,则root2成为新树
        forest[root1]=root2;
    else{
        if(forest[root1]==forest[root2])//root1和root2是同样深的树
            forest[root1]--;//把root1当主树,同时深度+1
        forest[root2]=root1;//合并两棵树,root1作为新树
    }
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

int main(){
    int i,forest[K]={0},n,m,x,y,s;//初始所有树高均为0或者大小为1
    scanf("%d%d",&n,&m);
    //memset(forest,-1,n*sizeof(int));//把所有的树的大小设为-1
    for(i=0;i<m;i++){
        scanf("%d%d",&x,&y);
        x=Find(forest,x);//找到x的根
        y=Find(forest,y);//找到y的根
        if(x!=y)//如果两棵树不同,就合并这两棵树
            DepthMerge(forest,x,y);
            //SizeMerge(forest,x,y);
    }
    for(i=1,s=0;i<=n;i++)//扫描森林里有多少个根,既多少棵树
        if(forest[i]<=0)
            s++;
    printf("%d",s);
    return 0;
}
/* 测试数据：
10 9
1 2
3 4
5 2
4 6
2 6
8 7
9 7
1 6
2 4 */
