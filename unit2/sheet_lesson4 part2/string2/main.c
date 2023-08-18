#include"stdio.h"
int main(){
	printf("Enter the string :");
	fflush(stdin);
	fflush(stdout);
	char s[1000];
	gets(s);
	int count=0;
	for(int i=0 ; s[i]!='\0' ; i++){
		count++;
	}
	printf("length of string :%d",count);
}
