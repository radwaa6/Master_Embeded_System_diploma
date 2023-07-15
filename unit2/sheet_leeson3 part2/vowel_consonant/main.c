#include"stdio.h"
void main(){
	char alpha;
	int lower_case,upper_case;
	printf("Enter an alphabet:");
	fflush(stdin);
	fflush(stdout);
	scanf("%c",&alpha);
	lower_case=(alpha=='a'||alpha=='e'||alpha=='i'||alpha=='o'||alpha=='u');
	upper_case=(alpha=='A'||alpha=='E'||alpha=='I'||alpha=='O'||alpha=='U');
	if(lower_case||upper_case){
		printf("%c is vowel",alpha);
	}else{
		printf("%c is consonant",alpha);
	}
}
