#include"stdio.h"
#include<math.h>
int prim_num(int num){
int k=sqrt(num);
int flag=0;
for(int i=2 ; i<=k ; i++){
	if(num%i==0){
		flag=1;
		break;
	}
}
return flag;
}
void main(){
	int num1=2 , num2=16;
	printf("Enter two numbers :%d %d ",num1 , num2);
	for(int i=num1 ; i<=num2 ;i++){
		int f=prim_num(i);
		if(f==0){
			printf("%d",i);
		}
	}

}


