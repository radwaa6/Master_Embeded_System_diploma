#include"stdio.h"
#include"string.h"
int main(){
	printf("Enter the string:");
	fflush(stdin);
	fflush(stdout);
	char s[1000];
	gets(s);
	int i=0;
	printf("Reverse string is :");
	for(i=strlen(s)-1 ; i>=0 ; i--){
		printf("%c",s[i]);
	}
}
