#include"stdio.h"
void main(){
	int num;
	printf("Enter number: ");
	fflush(stdin);
	fflush(stdout);
	scanf("%d",&num);
	int sum=0;
	for(int i=1 ; i<=num ; i++){
		sum+=i;
	}
	printf("sum = %d",sum);
}
