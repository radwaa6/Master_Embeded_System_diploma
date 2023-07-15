#include"stdio.h"
void main(){
	char symp;
	int value=symp;
	printf("Enter character :");
	fflush(stdin);
	fflush(stdout);
	scanf("%c",&symp);
	if((symp>='a'&&symp<='z')||(symp>='A'&&symp<='Z')){
		printf("%c is an alphabet",symp);
	}else{
		printf("%c is not an alphabet ",symp);
	}
}
