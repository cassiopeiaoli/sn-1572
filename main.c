#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include "signals.h"
#include "faces.h"
#include "util.h"

#define LEDs PB0
#define LEDs_Count 128
#define RED_OFFSET 8
#define GREEN_OFFSET 0
#define BLUE_OFFSET 16
#define BITS_COUNT 24
#define FRAME_TIME 30  // This corresponds to how many timer overflow have to happen before we increment the frame index
#define TIME_TO_PLAY 60 // this corresponds to how many timer overflows have to happen before we play an animation associated to the current frame

typedef enum CurrentAnimation {
	Default = 0,
	Error,
} current_animation_t;
						
// 0 - led off
// 1 - led blue
volatile uint8_t framebuffer[LEDs_Count];
volatile uint8_t frame_index = 0;  // this FUCKER tells us which frame of the animation we should be displayin rn
volatile bool frame_sent = false;
volatile uint8_t timer_counter = 0;  // how many times the overflow ISR was raised
volatile current_animation_t animation = Default;
volatile bool animation_played = false;
volatile bool animation_playing = false;
volatile bool mask_displayed = true;

ISR(TIMER0_OVF_vect) {
	timer_counter++;
	if (timer_counter >= FRAME_TIME) {
		timer_counter = 0;
		PORTB ^= (1 << PB1);
		frame_index++;
		frame_sent = false;
		if (frame_index >= 8) {
			frame_index = 0;
		}
	}
}

// Lyra: Cass, remember to rename other PORTB pins for clarity (and don't forget to actually use them in more places than one)
// Cass: shut the fuck up (im sorry, im /j'ing)
void setup()
{
	DDRB |= (1 << LEDs) | (1 << PB1);
	TCCR0B |= (1 << CS02) | (1 << CS00);  // /1024 prescaler ^^ 
	TCNT0 = 0;  // ababa????? isn't  dis  unncesecarrayry since  timer resets   on overflo? ~ ara
	TIMSK |= (1 << TOIE0);

	// Lets just initalize this buffer with all zeroes for safety sake
	for (uint8_t i = 0; i < LEDs_Count; i++)
		framebuffer[i] = 0;

	sei();
}

void face_to_framebuffer(const uint16_t face[8])
{
	cli();
	uint8_t framebuffer_index = 0;

	for (uint8_t i = 0; i < 8; i++) {
		uint16_t strip = face[i];

		if (i % 2 != 0) {
			strip = rev16(strip); 
		}

		for (uint8_t j = 0; j < 16; j++) {
			// Every other strip of LEDs is reversed so we need to reverse the order of a byte for that given strip 
			uint8_t bit = ((strip >> j) & 1);
			framebuffer[framebuffer_index] = bit;
			framebuffer_index++;
		}
	}
	sei();
}

void apply_mask(const uint16_t mask[9])
{
	cli();

	// we only replace LEDs that are defined as not-zero in a mask
	uint8_t picked_colour = mask[0];
	uint8_t framebuffer_index = 0;

	for (uint8_t i = 1; i < 8; i++) {
		uint16_t strip = mask[i];

		// reverse every other strip data since it is manufactured in a STUPID fucking SNAKE pattern ugh
		if (i % 2 != 0) {
			strip = rev16(strip); 
		}

		for (uint8_t j = 0; j < 16; j++) {
			int8_t bit = ((strip >> j) & 1);
			if (bit == 1) {
				framebuffer[framebuffer_index] = picked_colour;
				framebuffer_index++;
			} else {	
				framebuffer_index++;
			}
		}
	}
	sei();
}

void blank()
{
	for (int i = 0; i < BITS_COUNT; i++)
		ws2812b_zero();
}

void blue()
{
	for (int i = 0; i < BITS_COUNT; i++) {
		if (i > 19) {
			ws2812b_one();
		} else {
			ws2812b_zero();
		}
	}
}

void purple()
{
	for (int i = 0; i < BITS_COUNT; i++) {
		if ((i > 13 && i < 16) || (i > 21)) {
			ws2812b_one();
		} else {
			ws2812b_zero();
		}
	}
}

// im so sorry, god
void send_framebuffer()
{
	cli();
	for (int i = 0; i < LEDs_Count; i++) {
		switch (framebuffer[i]) {
			case 0:
				blank();
				break;
			case 1:
				blue();
				break;
			case 2:
				purple();
				break;
			default:
				blank();
				break;
		}
	}
	ws2812b_latch();
	frame_sent = true;
	sei();
}

int main()
{
	setup();
	while(1) {
		if (!frame_sent) {
			if (!animation_played) {
				face_to_framebuffer(shy2);
				if (mask_displayed) {
					apply_mask(small_blush_mask);
				}
			}
			send_framebuffer();
		}
	}
}
