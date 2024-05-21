#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARR_SIZE 128
#define HASH_SIZE 1024

unsigned int hash_function(const char * const str) {
	if(!str) return -1;
	return str[0] - 'a';
}

struct Node {
	const char * str;
	unsigned int index;
	struct Node *next;
};

struct Node *createNode(const char * const str) {
	struct Node *temp = (struct Node *)calloc(1, sizeof(struct Node));
	temp->str = str;
	return temp;
}

struct Node *push(struct Node *head, const char * const str) {
	if(!str) return NULL;
	struct Node *temp = createNode(str);
	temp->next = head;
	return temp;
}

struct Node *match(struct Node *head, const char * const str) {
	if(!str || !head) return NULL;
	for(unsigned int i = 0;; i++) {
		//printf(">>>head->str[i] = %c | haed->str[i+1] = %c | str[i] = %c | str[i+1] = %c \n", 
		//		head->str[i], head->str[i+1], str[i], str[i+1]);
		if(head->str[i] == str[i] && head->str[i+1] == '\0') return head;
		else if(head->str[i] != str[i]) break;
	}
	return match(head->next, str);
}

struct Node *hashMap[HASH_SIZE] = {0};

void pushToMap(const char * const str) {
	if(!str) return;
	unsigned int index = hash_function(str);
	static unsigned int indexG = 0;
	hashMap[index] = push(hashMap[index], str);
	hashMap[index]->index = indexG++;
}

unsigned int *lzw(const char * const str) {
	if(!str) return NULL;
	char *temp_str = (char *)str;
	unsigned int *result = (unsigned int *)calloc(HASH_SIZE, sizeof(unsigned int));
	unsigned int i;
	for(i = 0; *temp_str != '\0'; i++) {
		unsigned int index = hash_function(temp_str);
		printf("index = %d \n", index);
		struct Node *matched = match(hashMap[index], temp_str);
		printf("matched->index = %u \n", matched->index);
		result[i] = matched->index;
		char *arr = (char *)calloc(10, sizeof(char));
		unsigned int len = strlen(matched->str);
		for(unsigned int j = 0; j < len; j++) {
			arr[j] = matched->str[j];
		}
		printf("matched->str = %s \n", matched->str);
		printf("len = %d \n", len);
		arr[len] = *(temp_str += len);
		printf("temp_str = %s \n", temp_str);
		arr[len+1] = '\0';
		printf("to push arr = %s \n \n", arr);
		pushToMap(arr);
	}
	result[i] = -1;
	return result;
}

char *lzwDecompress(const unsigned int * const compressed) {
	if(!compressed) return NULL;
	char *table[HASH_SIZE] = {0};
	char temp[52] = {0};
	for(unsigned int i = 0; i < 26; i++) {
		temp[i * 2] = 'a' + i;
		temp[i * 2 + 1] = '\0';
		table[i] = temp + i * 2;
		//printf("table[i] = %s \n", table[i]);
	}
	char *result = (char *)calloc(ARR_SIZE, sizeof(char));
	for(unsigned int i = 0; compressed[i] != -1; i++) {
		static unsigned int index = 26;
		strcat(result, table[compressed[i]]);
		puts(result);
		puts(table[compressed[i]]);
		printf("compressed[i] = %u \n", compressed[i]);
		if(compressed[i+1] == -1) break;
		table[index] = (char *)calloc(10, sizeof(char));
		strcat(table[index], table[compressed[i]]);
		char temp_char = table[compressed[i+1]][1];
		table[compressed[i+1]][1] = '\0';
		strcat(table[index], table[compressed[i+1]]);
		table[compressed[i+1]][1] = temp_char;
		printf("table[index] = %s and index = %u \n", table[index], index);
		++index;
	}
	printf("\n");
	return result;
}

int main() {
	char temp[52] = {0};
	for(unsigned int i = 0; i < 26; i++) {
		temp[i * 2] = 'a' + i;
		temp[i * 2 + 1] = '\0';
		pushToMap(temp+i*2);
	}
	char str[ARR_SIZE] = "alabalabala";
	unsigned int *compressed = lzw(str);
	for(unsigned int i = 0; compressed[i] != -1; i++) {
		printf("%d ", compressed[i]);
	}
	printf("\n \n");
	const char *decompressed = lzwDecompress(compressed);
	puts(decompressed);
	return 0;
}
