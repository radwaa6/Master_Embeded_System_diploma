#include"stdio.h"
void main(){
	double num1 , num2 , num3;
	double largest_num;
printf("Enter tree numbers :");
fflush(stdin);
fflush(stdout);
scanf("%lf %lf %lf",&num1,&num2,&num3);
if(num1>num2&&num1>num3){
	largest_num=num1;
}else if(num2>num1&&num2>num3){
	largest_num=num2;
}else{
	largest_num=num3;
}
printf(" is largest=%lf ",largest_num);
}
