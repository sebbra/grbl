
#include "grbl.h"
#ifdef CPU_MAP_CUSTOM_1284p

void spi_init()
{
		// Set SS as Output
		SPI_DDR |= (1 << SPI_SS);		
	  
		// Set SS to high so a connected chip will be "deselected" by default
		spi_disable();


		SPCR |= (1 << MSTR);
		SPCR |= (1 << SPE);
		SPCR |=  (SPI_MODE3 & SPI_MODE_MASK);
		spi_setClockDivider(SPI_CLOCK_DIV8);
			
		// Set direction register for SCK and MOSI pin
	  	SPI_DDR |= (1 << SPI_MOSI);
		SPI_DDR |= (1 << SPI_CLK);

}


inline uint8_t spi_transfer(uint8_t data) {
  SPDR = data;
  asm volatile("nop");
  while (!(SPSR & (1 << SPIF)));
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



