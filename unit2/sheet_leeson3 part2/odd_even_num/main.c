#include"stdio.h"
void main(){
	int  num;
	printf("Enter an integer you want to check:");
	fflush(stdin);
	fflush(stdout);
	scanf("%d",&num);
	if(num%2==0){
		printf("%d is Even",num);
	}else{
		printf("%d is Odd",num);
	}
}
