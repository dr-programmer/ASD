#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char *encrypt(const char * const str, const char * const key) {
	if(!str || !key) return NULL;
	char *result = (char *)calloc(strlen(str) + 1, sizeof(char));
	unsigned int keySize = strlen(key);
	for(unsigned int i = 0, j = 0; str[i] != '\0'; i++, j = (j + 1) % keySize) {
		result[i] = (str[i] + (key[j] - 'a' + 1) % 26 - 'a') % 26 + 'a';
	}
	return result;
}

char *deEncrypt(const char * const str, const char * const key) {
	if(!str || !key) return NULL;
	char *result = (char *)calloc(strlen(str) + 1, sizeof(char));
	unsigned int keySize = strlen(key);
	for(unsigned int i = 0, j = 0; str[i] != '\0'; i++, j = (j + 1) % keySize) {
		result[i] = (26 + str[i] - 'a' - (key[j] - 'a' + 1)) % 26 + 'a';
	}
	return result;
}

int main() {
	char str[] = "bananaz";
	char key[] = "key";
	char *encrypted = encrypt(str, key);
	puts(encrypted);
	char *deEncrypted = deEncrypt(encrypted, key);
	puts(deEncrypted);
	return 0;
}
