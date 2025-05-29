#ifndef UTIL_H
#define UTIL_H

uint16_t rev16(uint16_t x) {
	uint16_t result = 0;
	for (int i = 16-1; i >= 0; i--) {
		result += ((x&1) << i);
		x >>= 1;
	}
	return result;
}

#endif
