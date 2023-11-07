#include <stdio.h>


/*
int main() {
	int a = 195, count = 0;
	while(a) {
		if(a & 1) count++;
		a >>= 1;
	}
	printf("Count of ones = %d\n", count);
	return 0;
}
*/
/*
int main() {
	int num = 195, count = 0;
	while(num) {
		// num & 3 == 3
		if(num & 2 && num & 1) count++;
		num >>= 1;
	}
	printf("Count of 11s = %d\n", count);
	return 0;
}
*/

int function(int num) {
	if(!num) return 0;
	else return (num & 1) + function(num >> 1);
}

int main() {
	int num = 195;
	printf("Number of ones = %d\n", function(num));
	return 0;
}
