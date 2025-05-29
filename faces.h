#ifndef FACES_H
#define FACES_H

/*
 * FACES / MASKS
 *
 * Each "face" is stored as eight 16-bit numbers, one means that an LED at
 * a given place will be turned ON, while zero means that a given LED will
 * be turned OFF. The default colour is blue.
 *
 * ===============================================================
 *
 * A "mask" is something applied on top of a face, like a silly little effect
 * of sorts (for example: blush)
 * It's stored as nine 16-bit numbers, where the first number is used to
 * determine the colour of said mask, otherwise it follows the same rules as 
 * faces.
 *
 * 1 - Red
 * 2 - Pink/Purple
 * 3 - White
 */

const uint16_t blush_mask[9] = {
		2,
		0b0000000000000000,
		0b0000010101010000,
		0b0000010101010000,
		0b0000101010100000,
		0b0000101010100000,
		0b0001010101000000,
		0b0001010101000000,
		0b0000000000000000,
};

const uint16_t small_blush_mask[9] = {
		2,
		0b0000000000000000,
		0b0000000000000000,
		0b0000000000000000,
		0b0000000000000000,
		0b0000000000000000,
		0b0011100000011100,
		0b0000000000000000,
		0b0000000000000000,
};

const uint16_t shy_face[8] = {
		0b0000000000000000,
		0b1100000000000011,
		0b0110000000000110,
		0b0011000000001100,
		0b0110000000000110,
		0b1100000000000011,
		0b0000000000000000,
		0b0000000000000000,
};

const uint16_t happy[8] = {
		0b0000000000000000,
		0b0001100000011000,
		0b0011110000111100,
		0b0110011001100110,
		0b0000000000000000,
		0b0000000000000000,
		0b0000000000000000,
		0b0000000000000000,
};

const uint16_t shy2[8] = {
		0b0000000000000000,
		0b0000000000000000,
		0b0111110000111110,
		0b0110000000110000,
		0b0000000000000000,
		0b0000000000000000,
		0b0000000000000000,
		0b0000000000000000,
};

const uint16_t confused[8] = {
		0b0000000000000000,
		0b0000000000000000,
		0b0000000000000000,
		0b0000000000000000,
		0b0000000000000000,
		0b0000000000000000,
		0b0000000000000000,
		0b0000000000000000,
};
#endif
