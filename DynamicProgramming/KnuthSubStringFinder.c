#include <stdio.h>
char pattern[] = "ABCDABD"; //abcdabcabcd
char text[] = "ABC ABCDAB ABCDABCDABDE";
int a[9];
void prefix(){
	int i=1,j=0;
	a[0] = 0;
	int len = sizeof(pattern)/sizeof(char);
	while(i<len){
		if(pattern[i] == pattern[j]){
			if(j == 0){
				a[i] = 1;
			} else {
				a[i] = a[i-1] + 1;
			}
			i++;j++;
		} else {
			if(j > 0){
				j = 0;
			} else {
				a[i] = 0;
				i++;
			}
		}
	}
}

int main(void) {
 	int textLength = sizeof(text)/sizeof(char) - 1;
	int patternLength = sizeof(pattern)/sizeof(char) - 1;
	int  m = 0;
	int i = 0;
	prefix();
	while(m < textLength && i < patternLength){
		if(text[m] == pattern[i]){
			m++;i++;
		} else {
			if(i == 0){
				m++;
			} else {
				i = a[i - 1];
			}
		}
	}
	if(i == patternLength){
		printf("String Found at %d", m - patternLength);
	} else {
		printf("String not found");
	}
	return 0;
}