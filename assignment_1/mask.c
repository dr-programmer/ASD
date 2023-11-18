#include <stdio.h>

typedef unsigned char byte;

struct Mask {
	byte one;
	byte two;
	byte three;
	byte four;
};

unsigned int power(unsigned int num, unsigned int pow) {
	if(pow == 0) return 1;
	return num * power(num, pow-1);
}

unsigned int get_net_size(struct Mask mask) {
	int result; byte value;
	if(mask.one != 255) { result = 3; value = mask.one; }
	else if(mask.two != 255) { result = 2; value = mask.two; }
	else if(mask.three != 255) { result = 1; value = mask.three; }
	else { result = 0; value = mask.four; }
	result = ((byte)(~value) + 1) * power(256, result) - 1;
	return (result>>1)<<1;
}

unsigned int get_net_size_v2(struct Mask mask) {
	struct Mask temp = {mask.four, mask.three, mask.two, mask.one};
	unsigned int result = *(int *)&temp;
	return (~result>>1)<<1;
}

int main() {
	struct Mask test = {255, 255, 255, 248};
	printf("Result = %u\n", get_net_size(test));
	printf("Result = %u\n", get_net_size_v2(test));
	return 0;
}
