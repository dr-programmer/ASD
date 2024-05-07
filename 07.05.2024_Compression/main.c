#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *compress(const char *str) {
	unsigned int strLen = strlen(str) + 1;
	char *temp = (char *)calloc(strLen, sizeof(char));
	char current = str[0];
	unsigned int count = 1;
	for(unsigned int i = 1; i < strLen; i++) {
		if(current == str[i]) {
			count++;
			continue;
		}
		char adding[128] = {0};
		if(count != 1) {
			sprintf(adding, "%u", count);
		}
		unsigned int len = strlen(adding);
		adding[len] = current;
		adding[len+1] = '\0';
		strcat(temp, adding);
		current = str[i];
		count = 1;
	}
	return temp;
}

char *decompress(const char *str) {
	unsigned int strLen = strlen(str) + 1;
	char *temp = (char *)calloc(strLen + 100, sizeof(char));
	unsigned int num = 0, tempPos = 0;
	char current = '\0';
	for(unsigned int i = 0; str[i] != '\0'; i++) {
		current = str[i];
		if(current >= '0' && current <= '9') {
			num *= 10;
			num += current - '0';
			continue;
		}
		num = num == 0 ? 1 : num;
		for(unsigned int j = 0; j < num; j++) {
			temp[tempPos++] = current;
		}
		num = 0;
	}
	temp[tempPos] = '\0';
	return temp;
}

int main() {
	char *str = "abaabbabbb";
	char *compressed = compress(str);
	printf("%s \n", compressed);
	char *decompressed = decompress(compressed);
	printf("%s \n", decompressed);
	return 0;
}
