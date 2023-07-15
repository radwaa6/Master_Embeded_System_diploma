#include<stdio.h>
int main(){
	float num1, num2 ,product;
	printf("Enter two numbers :");
	fflush(stdin);
	fflush(stdout);
	scanf("%f %f",&num1,&num2);
	 product=num1*num2;
	printf("Product :%f",product);
}
