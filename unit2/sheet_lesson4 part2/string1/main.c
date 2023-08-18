#include"stdio.h"
int main(){
	printf("Enter string: ");
	fflush(stdin);
	fflush(stdout);
	char s[1000];
	gets(s);
	printf("Enter character to find frequancy:");
	fflush(stdin);
	fflush(stdout);
	char c;
	scanf("%c",&c);
	int count=0;
	for(int i=0 ; s[i]!='\0' ; i++){
		if(s[i]==c){
			count++;
		}
	}
	printf("Frequancy of %c=%d",c,count);
}
