#include"stdio.h"
void main(){
	int num;
	int fact=1;
	printf("Enter number :");
	fflush(stdin);
	fflush(stdout);
	scanf("%d",&num);
	if(num<0){
		printf("Erro!!! Factorial of negative number does not exsist ");
	}else{
		for(int i=1 ; i<num ; i++){
			fact*=i;
		}
	}
	printf("Factorial = %d",fact);
}
