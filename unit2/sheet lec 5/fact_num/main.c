#include"stdio.h"
int fact(int num){
	if(num==0){
		return 1;
	}
	return fact(num-1)*num;
}
void main(){
	int num;
	printf("Enter an positive number : \n",num);
	scanf("%d",&num);
	printf("factorial of %d = %d ",num,fact(num));
}
