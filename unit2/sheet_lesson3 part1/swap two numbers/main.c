#include"stdio.h"
void main(){
	double num1,num2,temp;
	printf("Enter value of a :");
	fflush(stdin);
	fflush(stdout);
	scanf("%lf",&num1);
	printf("Enter value of b :");
	fflush(stdin);
	fflush(stdout);
	scanf("%lf",&num2);
	temp=num1;
	num1=num2;
	num2=temp;
	printf("After swaping , value of a = %lf\n",num1);
	printf("After swaping , value of b = %lf ",num2);
}
