#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 32

int main(){
    int a[N],i,temp,j,x=5;
    srand(time(NULL));//初始化种子
    for(i=0;i<N;i++)
        a[i]=i+x;//生成一个x到N+x的数组序列
    for(i=1;i<N;i++){
        j=rand()%N;//生成0到N的随机数
        temp=a[i];//将a[i]与随机的a[j]交换
        a[i]=a[j];
        a[j]=temp;
    }
    for(i=0;i<N;i++)
        printf("%d ",a[i]);
    return 0;
}
