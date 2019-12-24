#include<stdio.h>

void InsSort(int [],int);
void ShellSort(int [],int);
void input(int [],int);
void output(int [],int);

int main(){
    int n;
    scanf("%d",&n);
    int a[n];
    input(a,n);
    ShellSort(a,n);
    output(a,n);
    return 0;
}

void InsSort(int a[],int n){
    int i,j,x;
    for(i=1;i<n;i++){
        x=a[i];
        for(j=i;j>0&&a[j-1]>x;j--)
            a[j]=a[j-1];
        a[j]=x;
    }
}

void ShellSort(int a[],int n){
    int i,j,increment,x;
    for(increment=n/2;increment>0;increment/=2){
        if(increment%2==0)//如果增量为偶数,则将其+1,这种增量更优
            increment++;
        for(i=increment;i<n;i++){//插入排序其实是增量为1的希尔排序
            x=a[i];
            for(j=i;j>=increment&&x<a[j-increment];j-=increment)
                a[j]=a[j-increment];
            a[j]=x;
        }
    }
}

void input(int a[],int n){
    int i;
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);
}
void output(int a[],int n){
    for(int i=0;i<n;i++)
        printf("%d ",a[i]);
}
