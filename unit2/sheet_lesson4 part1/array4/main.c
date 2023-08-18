#include"stdio.h"
int main(){
	printf("Enter number of element :\n");
	fflush(stdin);
	fflush(stdout);
	int num;
	scanf("%d",&num);
	int arr[num];
	for(int i=0 ; i<num ; i++){
		fflush(stdin);
		fflush(stdout);
		scanf("%d",&arr[i]);
	}
	printf("Enter element to be insert :\n");
	int ele;
	fflush(stdin);
	fflush(stdout);
	scanf("%d",&ele);
	printf("Enter the location:\n");
	int loc;
	fflush(stdin);
	fflush(stdout);
	scanf("%d",&loc);
for(int i=num ; i>=loc ; i--){
	arr[i]=arr[i-1];
}
num++;
arr[loc-1]=ele;
for(int i=0 ; i<num ; i++){
	printf("%d",arr[i]);
}
}
