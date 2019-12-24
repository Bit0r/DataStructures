#include<stdio.h>

void swap(int *px,int *py){
	int temp=*px;
	*px=*py;
	*py=temp;
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

void ShellSort(int a[],int n){
    int i,j,increment,x;
    for(increment=n/2;increment>0;increment/=2){
        if(increment%2==0)//如果增量为偶数,则将其+1,这种增量更优
            increment++;
        for(i=increment;i<n;i++){
            x=a[i];
            for(j=i;j>=increment&&x<a[j-increment];j-=increment)
                a[j]=a[j-increment];
            a[j]=x;
        }
    }
}

int median3(int a[],int left,int right){
	int center=(left+right)/2;
	if(a[left]>a[center])
		swap(&a[left],&a[center]);
	if(a[left]>a[right])
		swap(&a[left],&a[right]);
	if(a[center]>a[right])
		swap(&a[center],&a[right]);
	swap(&a[center],&a[right-1]);
	return a[right-1];
}

void QuickSort(int a[],int left,int right){
	if(left+100>right){
		ShellSort(a+left,right-left+1);
		return;
	}
	int i=left,j=right-1,pivot=median3(a,left,right);
	while(1){
		while(a[++i]<pivot)
			continue;
		while(a[--j]>pivot)
			continue;
		if(i<j)
			swap(&a[i],&a[j]);
		else
			break;
	}
	swap(&a[i],&a[right-1]);
	QuickSort(a,left,i-1);
	QuickSort(a,i+1,right);
}

int main(){
	int n;
	scanf("%d",&n);
	int a[n];
	input(a,n);
	QuickSort(a,0,n-1);
	output(a,n);
	return 0;
}