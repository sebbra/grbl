
#include "grbl.h"
#ifdef CPU_MAP_CUSTOM_1284p

/*
#define SPI_DDR 	  DDRB
#define SPI_PIN 	  PINB
#define SPI_PORT	  PORTB
#define SPI_MOSI	  5
#define SPI_MISO	  6
#define SPI_CLK 	  7
#define SPI_SS	  4

STEP_DDR |= STEP_MASK;
STEPPERS_DISABLE_DDR |= 1<<STEPPERS_DISABLE_BIT;
DIRECTION_DDR |= DIRECTION_MASK;

*/


void spi_init()
{
		// Set SS as Output
		SPI_DDR |= (1 << SPI_SS);		
	  
		// Set SS to high so a connected chip will be "deselected" by default
		spi_disable();


		SPCR |= (1 << MSTR);
		SPCR |= (1 << SPE);

		SPCR |=  (SPI_MODE3 & SPI_MODE_MASK);
		spi_setClockDivider(SPI_CLOCK_DIV16);
			
		// Set direction register for SCK and MOSI pin.
		// MISO pin automatically overrides to INPUT.
		// By doing this AFTER enabling SPI, we avoid accidentally
		// clocking in a single bit since the lines go directly
		// from "input" to SPI control.
		// http://code.google.com/p/arduino/issues/detail?id=888
	  	SPI_DDR |= (1 << SPI_MOSI);
		SPI_DDR |= (1 << SPI_CLK);
		asm volatile("nop");

}


inline uint8_t spi_transfer(uint8_t data) {
  SPDR = data;
  asm volatile("nop");
  while (!(SPSR & (1 << SPIF))) ; // wait
  return SPDR;
}


inline void spi_enable()
{
  SPI_PORT &= ~(1 << SPI_SS);
  delay_us(1);
}


inline void spi_disable()

{
   delay_us(1);
   SPI_PORT |= (1 << SPI_SS);
   delay_us(1);

}

inline void spi_setClockDivider(uint8_t clockDiv) {
  SPCR = (SPCR & ~SPI_CLOCK_MASK) | (clockDiv & SPI_CLOCK_MASK);
  SPSR = (SPSR & ~SPI_2XCLOCK_MASK) | ((clockDiv >> 2) & SPI_2XCLOCK_MASK);
}




#endif



