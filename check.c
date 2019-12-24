#include<stdio.h>
#include<stdlib.h>

int input(FILE *,int []);
void compare(FILE *,int [],int);
void output(FILE *,int [],int);


int main(int argc,char *argv[]){
    FILE *in,*testdata,*out;
    if((in=fopen(argv[1],"r"))==NULL){
        puts("打开输入文件失败!");
        exit(EXIT_FAILURE);
    }
    if((out=fopen(argv[2],"w"))==NULL){
        puts("打开输出文件失败!");
        exit(EXIT_FAILURE);
    }
    if(EOF==fclose(in)){
        puts("关闭输入文件失败!");
        exit(EXIT_FAILURE);
    }
    if(EOF==fclose(out)){
        puts("关闭输出文件失败!");
        exit(EXIT_FAILURE);
    }
    return 0;
}

int input(FILE *in,int a[]){
    int n,i;
    fscanf(in,"%d",&n);
    for(i=0;i<n;i++)
        fscanf(in,"%d",a+i);
    return n;
}
void compare(FILE *testdata,int a[],int n){
    int i,temp;
    for(i=0;i<n;i++){
        fscanf(testdata,"%d",&temp);
        if(temp!=a[i]){
            printf("第%d个数不同,在文本中是%d,在数组中是%d",i,temp,a[i]);
            return;
        }
    }
}
void output(FILE *out,int a[],int n){
    int i;
    for(i=0;i<n;i++)
        fprintf(out,"%d ",a[i]);
}