#include"stdio.h"
int main(){
	printf("Enter number of element :");
	fflush(stdin);
	fflush(stdout);
	int num;
	scanf("%d",&num);
	int arr[num];
	for(int i=0 ; i<num ; i++){
		scanf("%d",&arr[i]);
	}
	printf("Enter number to be searched : ");
	fflush(stdin);
	fflush(stdout);
	int ele;
	scanf("%d",&ele);
	for(int i=0 ; i<num ; i++){
		if(ele==arr[i]){
			printf("Number found in locatio:%d",i+1);
			break;
		}
	}

}
