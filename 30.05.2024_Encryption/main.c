#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *cesar(const char * const str) {
	if(!str) return NULL;
	char *result = (char *)calloc(strlen(str) + 1, sizeof(char));
	for(unsigned int i = 0; str[i] != '\0'; i++) {
		if(str[i] == 'z') result[i] = str[i] - 25;
		else result[i] = str[i] + 1;
	}
	return result;
}

unsigned int fibonachi(unsigned int n) {
	if(n <= 1) return 1;
	else return fibonachi(n-1) + fibonachi(n-2);
}

char *complexCesar(const char * const str) {
	if(!str) return NULL;
	char *result = (char *)calloc(strlen(str) + 1, sizeof(char));
	for(unsigned int i = 0; str[i] != '\0'; i++) {
		unsigned int offset = fibonachi(i % 26);
		int push = str[i] + offset;
		if(push > 'z') push = 'a' + push - 'z' - 1;
		result[i] = push;
	}
	return result;
}

char *deEncrypt(const char * const str) {
	if(!str) return NULL;
	char *result = (char *)calloc(strlen(str) + 1, sizeof(char));
	for(unsigned int i = 0; str[i] != '\0'; i++) {
		if(str[i] == 'a') result[i] = str[i] + 25;
		else result[i] = str[i] - 1;
	}
	return result;
}

char *deComplexEncrypt(const char * const str) {
	if(!str) return NULL;
	char *result = (char *)calloc(strlen(str) + 1, sizeof(char));
	for(unsigned int i = 0; str[i] != '\0'; i++) {
		unsigned int offset = fibonachi(i % 26);
		char push = str[i] - offset;
		if(push < 'a') push = 'z' - ('a' - push) + 1;
		result[i] = push;
	}
	return result;
}

int main() {
	char str[100] = "abcz";
	char *encrypted = cesar(str);
	puts(encrypted);
	char *cEncrypted = complexCesar(str);
	puts(cEncrypted);
	char *de = deEncrypt(encrypted);
	puts(de);
	char *deC = deComplexEncrypt(cEncrypted);
	puts(deC);
	return 0;
}
