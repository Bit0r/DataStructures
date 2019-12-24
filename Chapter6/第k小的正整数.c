#include<stdio.h>
#include<limits.h>

typedef struct{
    int capacity;
    int size;
    int arr[10004];
}Heap;

void HeapIni(Heap *pheap,int n){
    int i;
    pheap->capacity=10004;
    pheap->arr[0]=INT_MIN;
    for(i=1;i<=n;i++)
        scanf("%d",&pheap->arr[i]);
    pheap->size=i-1;
}

void shiftfup(Heap *ph,int i){
    int x=ph->arr[i];
    for(;x<ph->arr[i/2];i/=2)//比较x和父节点的大小
        ph->arr[i]=ph->arr[i/2];//如果x比父节点小,则空穴上移
    ph->arr[i]=x;//将x填入空穴
}

void shiftdown(Heap *ph,int i){
    int x=ph->arr[i],child;
    for(;i*2<=ph->size;i=child){//先确定是否有左儿子
        child=i*2;
        if(child!=ph->size&&ph->arr[child+1]<ph->arr[child])
        //如果有右儿子,从两个儿子中选出较小的一个
            child++;
        if(x>ph->arr[child])//比较x和儿子的大小,如果儿子比x大则跳出循环
            ph->arr[i]=ph->arr[child];
        else
            break;
    }
    ph->arr[i]=x;//将x填入空穴
}

void HeapIns(Heap *ph,int x){
    if(ph->size==ph->capacity)
        return;
    ph->size++;
    ph->arr[ph->size]=x;
    shiftfup(ph,ph->size);
}

int HeapDel(Heap *ph){
    if(ph->size==0)
        return 9999999;
    int min=ph->arr[1];
    ph->arr[1]=ph->arr[ph->size];
    ph->size--;
    shiftdown(ph,1);
    return min;
}

void HeapBuild(Heap *ph){
    for(int i=ph->size/2;i>0;i--)
        shiftdown(ph,i);
}

int main(){
    int n,k,f1=0,f2=9999;
    Heap test;
    scanf("%d%d",&n,&k);
    HeapIni(&test,n);
    HeapBuild(&test);
    for(int i=0;f1!=9999999&&i<k;){
        f1=HeapDel(&test);
        if(f1!=f2){
            f2=f1;
            i++;
        }
    }
    if(f1==9999999)
        puts("NO RESULT");
    else
        printf("%d",f2);
    return 0;
}
