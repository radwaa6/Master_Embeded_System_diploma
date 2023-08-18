#include"stdio.h"
int main(){
	printf("Enter the number of data :");
	fflush(stdin);
	fflush(stdout);
	int size;
	scanf("%d",&size);
	float arr[size];
	double sum=0;
	for(int i=0 ; i<size ; i++){
		printf("Enter number : ");
		fflush(stdin);
		fflush(stdout);
		scanf("%f",&arr[i]);
        sum+=arr[i];
	}
	printf("Average = %.2lf",sum/size);
}
