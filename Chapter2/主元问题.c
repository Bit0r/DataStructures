#include<stdio.h>
#include<string.h>
#define K 1024

int a[K],b[K];

int elect(int n){
  int candidate,i,j;
  
  if(n<2){
    if(n==1)//如果只剩1个项,那它必定是该数组主元。否则就是被删光了，没有主元
      return a[0];
    else
      return -1;
  }
  
  if(n%2){
    candidate=elect(n-1);//不关心如何得到候选元，只关心候选元是什么
    if(candidate==-1)//注意到如果前N-1个元素中有主要元素，则最后一个元素对结果没有影响，否则最后一个元素可能是候选元，将它作为候选元
      return a[n-1];
    else
      return candidate;
  }
  
  for(i=1,j=0;i<n;i+=2)//确定候选元的方法，见39页
      if(a[i]==a[i-1])
        b[j++]=a[i];
  
  memcpy(a,b,j*sizeof(int));//拷贝前j项，而不拷贝整个数组，否则a[n-1]项会被覆盖
  return elect(j);//返回当选者
}

int main(){
  int i,result,n;
  scanf("%d",&n);
  for(i=0;i<n;i++)
    scanf("%d",&a[i]);
  result=elect(n);
  if(result!=-1)
    printf("%d",result);
  else
    puts("NO!");
  return 0;
}
