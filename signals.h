#ifndef SIGNALS_H
#define SIGNALS_H

void ws2812b_zero()
{
	 asm volatile(
			"sbi 0x18, 0\n\t"
			"nop\n\t"
			"nop\n\t"
			"nop\n\t"
			"nop\n\t"
			"nop\n\t"
			"cbi 0x18, 0\n\t"
			"nop\n\t"
			"nop\n\t"
			"nop\n\t"
			"nop\n\t"
			"nop\n\t"
			"nop\n\t"
			"nop\n\t"
			"nop\n\t"
			);
}

void ws2812b_one()
{
	 asm volatile(
			"sbi 0x18, 0\n\t"
			"nop\n\t"
			"nop\n\t"
			"nop\n\t"
			"nop\n\t"
			"nop\n\t"
			"nop\n\t"
			"nop\n\t"
			"nop\n\t"
			"nop\n\t"
			"nop\n\t"
			"nop\n\t"
			"cbi 0x18, 0\n\t"
			);
}

// what the fuck
void ws2812b_latch()
{
	asm volatile("cbi 0x18, 0");  // make sure that PB0 is pulled low
	for (int i = 0; i < 250; i++)
		asm volatile("nop");
}

#endif
