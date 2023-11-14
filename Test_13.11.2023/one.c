#include <stdio.h>
#include <stdint.h>

//Pattern = 00

unsigned int count_pattern(uint16_t data) {
	unsigned int result = 0;
	data = ~data;
	while(data) {
		if(data & 3) result++;
		data >>= 2;
	}
	return result;
}

int main() {
	uint16_t data = 15;
	printf("%u \n", count_pattern(data));
}
