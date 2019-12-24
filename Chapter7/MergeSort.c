#include<stdio.h>
#include<string.h>

void Merge(int a[],int temparr[],int istart,int jstart,int end){
    int i=istart,j=jstart,k=0;
    while(i<jstart&&j<=end){
        if(a[i]<a[j]){
            temparr[k]=a[i];
            i++;
        }else{
            temparr[k]=a[j];
            j++;
        }
        k++;
    }
    if(i<jstart)//因为已经有库函数memcpy，所以复制操作就不自己写
        memcpy(temparr+k,a+i,(jstart-i)*sizeof(int));
    else
        memcpy(temparr+k,a+j,(end-j+1)*sizeof(int));
    memcpy(a+istart,temparr,(end-istart+1)*sizeof(int));
}

void MergeSort(int a[],int temparr[],int left,int right){
    if(left>=right)//如果只有一个数据，就不用排序了
        return;
    int center;
    center=(left+right)/2;
    MergeSort(a,temparr,left,center);//先将左边的一半排序
    MergeSort(a,temparr,center+1,right);//再将右边的一半排序
    Merge(a,temparr,left,center+1,right);//最后合并左右两个子序列
}

int main(){
    int i,n;
    scanf("%d",&n);
    int a[n],temparr[n];
    for(i=0;i<n;i++)
        scanf("%d",a+i);
    MergeSort(a,temparr,0,n-1);
    for(i=0;i<n;i++)
        printf("%d ",a[i]);
    return 0;
}