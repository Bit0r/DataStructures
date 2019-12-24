#include<stdio.h>
#include<stdlib.h>

void PrintOut(int);
void PrintDigit(unsigned int);

int main(){
	int n;
	scanf("%d",&n);
	PrintOut(n);
	return 0;
}

void PrintOut(int n){
	if(n<0){
		putchar('-');
		n=-n;
	}
	if(n>9)
		PrintOut(n/10);
	PrintDigit(n%10);
}

void PrintDigit(unsigned int n){
	if(n>9){
		fputs("Only one digit is allowed to print at a time",stderr);
		exit(EXIT_FAILURE);
	}
	printf("%d",n);
}
