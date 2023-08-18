#include"stdio.h"
int main(){
	printf("Enter rows and columns of matrix: \n");
	fflush(stdin);
	fflush(stdout);
	int rows,columns;
	scanf("%d%d",&rows,&columns);
	int arr[rows][columns];
	for(int i=0 ; i<rows; i++){
		for(int j=0 ; j<columns ; j++){
			printf("Enter element of a%d%d:",i,j);
			fflush(stdin);
			fflush(stdout);
			scanf("%d",&arr[i][j]);
		}
	}
	printf("Entered matrix:\n");
	for(int i=0 ; i<rows; i++){
		for(int j=0 ; j<columns ; j++){
			printf("%d  ",arr[i][j]);
			if(j==columns-1){
				printf("\n\n");
			}
		}
	}
	printf("Trnsposed matrix:\n");
	for(int i=0 ; i<columns; i++){
		for(int j=0 ; j<rows ; j++){
			printf("%d  ",arr[j][i]);
			if(j==rows-1){
				printf("\n\n");
			}
		}
	}
}
