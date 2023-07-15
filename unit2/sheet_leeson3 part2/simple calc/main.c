#include"stdio.h"
void main(){
	char symp;
	double num1 , num2;
	printf("Enter operator either + or - or * or divide : ");
	fflush(stdin);
	fflush(stdout);
	scanf("%c",&symp);
	printf("Enter two number :");
	scanf("%lf %lf",&num1,&num2);
	switch(symp){
	case'+':
		printf("%lf + %lf = %lf ",num1,num2,num1+num2);
		break;
	case'-':
		printf("%lf - %lf = %lf",num1,num2,num1-num2);
		break;
	case'*':
		printf("%lf * %lf = %lf",num1,num2,num1*num2);
		break;
	case'/':
		printf("%lf / %lf = %lf",num1,num2,num1/num2);
		break;
	};
}
