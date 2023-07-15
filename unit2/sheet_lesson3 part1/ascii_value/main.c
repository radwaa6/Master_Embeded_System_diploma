#include"stdio.h"
void main(){
	char alpha;
	printf("Enter a character:");
	fflush(stdin);
	fflush(stdout);
	scanf("%c",&alpha);
	int value=alpha;
	printf("ASCII value of  : %d",value);
}
