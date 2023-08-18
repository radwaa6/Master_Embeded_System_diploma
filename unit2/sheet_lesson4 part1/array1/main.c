#include<stdio.h>
int main(){
	printf("Enter the element of 1th matrix\n");
	fflush(stdin);
	fflush(stdout);
	float arr1[2][2];
	float arr2[2][2];
	float c[2][2];
	for(int i=0 ; i<2 ; i++){
		for(int j=0 ; j<2 ;  j++){
		printf("Enter a%d%d:\n",i,j);
		fflush(stdin);
		fflush(stdout);
		scanf("%f",&arr1[i][j]);
	}
}
	printf("Enter the element of 2th matrix\n");
	for(int i=0 ; i<2 ; i++){
		for(int j=0 ; j<2 ; j++){
		printf("Enter a%d%d:\n",i,j);
		fflush(stdin);
		fflush(stdout);
		scanf("%f",&arr2[i][j]);
	}
}
	printf("Sum of matrix :\n");
	for(int i=0 ; i<2 ; i++){
		for(int j=0 ; j<2 ;j++){
		c[i][j]=arr1[i][j]+arr2[i][j];
		printf("%0.1f\t",c[i][j]);
		if(j==1){
			printf("\n");
		}
	}
}

}

