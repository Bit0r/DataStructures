#include<stdio.h>
#include<limits.h>

typedef struct{
    int capacity;
    int size;
    int arr[100004];
}Heap;

void HeapIni(Heap *pheap,int n){
    int i;
    pheap->capacity=100004;
    pheap->arr[0]=INT_MAX;//将arr[0]设为一个非常大的值，减少shiftup的判断条件
    for(i=1;i<=n;i++)
        scanf("%d",&pheap->arr[i]);
    pheap->size=i-1;
}

void shiftfup(Heap *ph,int i){
    int x=ph->arr[i];
    for(;x>ph->arr[i/2];i/=2)//比较x和父节点的大小
        ph->arr[i]=ph->arr[i/2];//如果x比父节点大,则上浮
    ph->arr[i]=x;//将x填入空穴
}

void shiftdown(Heap *ph,int i){
    int x=ph->arr[i],child;
    for(;i*2<=ph->size;i=child){//先确定是否有左儿子
        child=i*2;
        if(child!=ph->size&&ph->arr[child+1]>ph->arr[child])
        //如果有右儿子,从两个儿子中选出较大的一个
            child++;
        if(x<ph->arr[child])//比较x和儿子的大小,如果儿子比x小则跳出循环
            ph->arr[i]=ph->arr[child];
        else
            break;
    }
    ph->arr[i]=x;//将x填入空穴
}

void shiftdown1(Heap *ph,int i){//这种下沉方式可以减少很多比较,详见练习7.40
    int x=ph->arr[i],child;
    for(;i*2<=ph->size;i=child){//先确定是否有左儿子
        child=i*2;
        if(child!=ph->size&&ph->arr[child+1]>ph->arr[child])
        //如果有右儿子,从两个儿子中选出较大的一个
            child++;
        ph->arr[i]=ph->arr[child];//不进行比较,直接进行下调
    }
    ph->arr[i]=x;//将x填入空穴
    shiftfup(ph,i);//再将新元进行上调,恢复堆序
}

void HeapBuild(Heap *ph){
    for(int i=ph->size/2;i>0;i--)
        shiftdown(ph,i);
}

void HeapSort(Heap *ph){
    int temp;
    while(ph->size){
        temp=ph->arr[ph->size];//交换堆顶和堆底的元素
        ph->arr[ph->size]=ph->arr[1];
        ph->arr[1]=temp;
        ph->size--;//将堆的最后一个元素出堆
        shiftdown1(ph,1);//调整堆顶的元素
    }
}

void output(int a[],int n){
    for(int i=1;i<=n;i++)
        printf("%d ",a[i]);
}

int main(){
    Heap test;
    int n;
    scanf("%d",&n);
    HeapIni(&test,n);
    HeapBuild(&test);
    HeapSort(&test);
    output(test.arr,n);
    return 0;
}
