#include"stdio.h"
void main(){
	double num;
	printf("Enter number:");
	fflush(stdin);
	fflush(stdout);
	scanf("%lf",&num);
	if(num>0){
		printf("%lf is positive",num);
	}else if(num<0){
		printf("%lf is negative",num);
	}else{
		printf("your entred zero");
	}
}
