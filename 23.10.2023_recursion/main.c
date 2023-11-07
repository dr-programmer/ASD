#include <stdio.h>

int factoriel(int num) {
	if(num <= 1) return 1;
	else return num * factoriel(num-1);
}

int fibonachi(int num) {
	if(num <= 0) return 0;
	else if(num == 1) return 1;
	else return fibonachi(num-1) + fibonachi(num-2);
}

int bsearch(int *arr, int start, int end, int search) {
	if(start > end) return -1;
	int index = (start + end) / 2;
	if(arr[index] == search) return index;
	else if(arr[index] < search) return bsearch(arr, index+1, end, search);
	else return bsearch(arr, start, index-1, search);
}

int palindrome(char *arr, int start, int end) {
	if(start > end) return 1;
	else if(arr[start] != arr[end]) return -1;
	else return palindrome(arr, start+1, end-1);
}

int isSorted(int *arr, int max, int index, int size) {
	if(index+1 >= size) return 1;
	else if(max > arr[index]) return -1;
	else return isSorted(arr, arr[index], index+1, size);
}

double power(double num, int pow) {
	if(pow == 0) return 1;
	else if(pow < 0) return (1/num) * power(num, pow+1);
	else return num * power(num, pow-1);
}

int main() {
	int temp = 6;
	printf("Factoriel: %d\n", factoriel(temp));

	int a = 6;
	printf("Fibonachi: %d\n", fibonachi(a));

	int arr[] = {1, 3, 5, 7, 9, 10, 13, 16};
	printf("Bsearch index = %d\n", bsearch(arr, 0, 7, 13));

	char str[] = "abannaba";
	printf("Palindrome: %d\n", palindrome(str, 0, 7));

	int check[] = {1, 2, 3, 4, 5, 6, 7};
	printf("Is sorted: %d\n", isSorted(check, check[0], 0, 7));

	int number = 5, pow = -1;
	printf("Power: %lf\n", power(number, pow));
	return 0;
}
