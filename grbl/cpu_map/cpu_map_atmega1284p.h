/*
  cpu_map_atmega1284p.h - CPU and pin mapping configuration file
  Part of Grbl

  Copyright (c) 2012-2015 Sungeun K. Jeon

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

/* Grbl officially supports the Arduino Uno, but the other supplied pin mappings are
   supplied by users, so your results may vary. This cpu_map file serves as a central
   pin mapping settings file for AVR 328p used on the Arduino Uno.  */
   
#ifdef GRBL_PLATFORM
#error "cpu_map already defined: GRBL_PLATFORM=" GRBL_PLATFORM
#endif


#define GRBL_PLATFORM "Atmega1284p"


  // Define serial port pins and interrupt vectors.
  #define SERIAL_RX     USART0_RX_vect
  #define SERIAL_UDRE   USART0_UDRE_vect

  #define ENABLE_M7

  // Define step pulse output pins. NOTE: All step bit pins must be on the same port.
  #define STEP_DDR        DDRD
  #define STEP_PORT       PORTD
  #define X_STEP_BIT      2  
  #define Y_STEP_BIT      3  
  #define Z_STEP_BIT      4  
  #define STEP_MASK       ((1<<X_STEP_BIT)|(1<<Y_STEP_BIT)|(1<<Z_STEP_BIT)) // All step bits

  // Define step direction output pins. NOTE: All direction pins must be on the same port.
  #define DIRECTION_DDR     DDRD
  #define DIRECTION_PORT    PORTD
  #define X_DIRECTION_BIT   5  
  #define Y_DIRECTION_BIT   6 
  #define Z_DIRECTION_BIT   7 
  #define DIRECTION_MASK    ((1<<X_DIRECTION_BIT)|(1<<Y_DIRECTION_BIT)|(1<<Z_DIRECTION_BIT)) // All direction bits

  // Define stepper driver enable/disable output pin.
  #define STEPPERS_DISABLE_DDR    DDRA
  #define STEPPERS_DISABLE_PORT   PORTA
  #define STEPPERS_DISABLE_BIT    0 
  #define STEPPERS_DISABLE_MASK   (1<<STEPPERS_DISABLE_BIT)

  // Define homing/hard limit switch input pins and limit interrupt vectors. 
  // NOTE: All limit bit pins must be on the same port, but not on a port with other input pins (CONTROL).
  #define LIMIT_DDR        DDRB
  #define LIMIT_PIN        PINB
  #define LIMIT_PORT       PORTB
  #define X_LIMIT_BIT      1  
  #define Y_LIMIT_BIT      2  
  #define Z_LIMIT_BIT      3  

  #define LIMIT_MASK       ((1<<X_LIMIT_BIT)|(1<<Y_LIMIT_BIT)|(1<<Z_LIMIT_BIT)) // All limit bits
  #define LIMIT_INT        PCIE0  // Pin change interrupt enable pin
  #define LIMIT_INT_vect   PCINT0_vect 
  #define LIMIT_PCMSK      PCMSK0 // Pin change interrupt register

  // Define spindle enable and spindle direction output pins.
  #define SPINDLE_ENABLE_DDR      DDRA
  #define SPINDLE_ENABLE_PORT     PORTA
  #define SPINDLE_ENABLE_BIT      1  
  
  #define SPINDLE_DIRECTION_DDR   DDRA
  #define SPINDLE_DIRECTION_PORT  PORTA
  #define SPINDLE_DIRECTION_BIT   4  
  
  
  // Define flood and mist coolant enable output pins.
  // NOTE: Uno analog pins 4 and 5 are reserved for an i2c interface, and may be installed at
  // a later date if flash and memory space allows.
  #define COOLANT_FLOOD_DDR   DDRA
  #define COOLANT_FLOOD_PORT  PORTA
  #define COOLANT_FLOOD_BIT   2  
  
  #define COOLANT_MIST_DDR    DDRA
  #define COOLANT_MIST_PORT   PORTA
  #define COOLANT_MIST_BIT    3 
 

  // Define user-control controls (cycle start, reset, feed hold) input pins.
  // NOTE: All CONTROLs pins must be on the same port and not on a port with other input pins (limits).
  #define CONTROL_DDR       DDRC
  #define CONTROL_PIN       PINC
  #define CONTROL_PORT      PORTC
  #define RESET_BIT         3  
  #define FEED_HOLD_BIT     4  
  #define CYCLE_START_BIT   2  
  #define SAFETY_DOOR_BIT   4  //  NOTE: Safety door is shared with feed hold. Enabled by config define.
  #define CONTROL_INT       PCIE1  // Pin change interrupt enable pin
  #define CONTROL_INT_vect  PCINT1_vect
  #define CONTROL_PCMSK     PCMSK1 // Pin change interrupt register
  #define CONTROL_MASK ((1<<RESET_BIT)|(1<<FEED_HOLD_BIT)|(1<<CYCLE_START_BIT)|(1<<SAFETY_DOOR_BIT))
  
  // Define probe switch input pin.
  #define PROBE_DDR       DDRC
  #define PROBE_PIN       PINC
  #define PROBE_PORT      PORTC
  #define PROBE_BIT       7 
  #define PROBE_MASK      (1<<PROBE_BIT)

  // Define SPI-Interface
  #define SPI_DDR		DDRB
  #define SPI_PIN		PINB
  #define SPI_PORT		PORTB
  #define SPI_MOSI		5
  #define SPI_MISO		6
  #define SPI_CLK		7
  #define SPI_SS		4

