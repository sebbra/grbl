/*
  cpu_map.h - CPU and pin mapping configuration file
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

/* The cpu_map.h files serve as a central pin mapping selection file for different processor
   types, i.e. AVR 328p or AVR Mega 2560. Each processor has its own pin mapping file.
   (i.e. cpu_map_atmega328p.h)  Grbl officially supports the Arduino Uno, but the 
   other supplied pin mappings are supplied by users, so your results may vary. */

// NOTE: With new processors, only add the define name and filename to use.

#ifndef cpu_map_h
#define cpu_map_h


#ifdef CPU_MAP_ATMEGA328P // (Arduino Uno) Officially supported by Grbl.
  #include "cpu_map/cpu_map_atmega328p.h"
#endif

#ifdef CPU_MAP_ATMEGA2560 // (Arduino Mega 2560) Working @EliteEng
  #include "cpu_map/cpu_map_atmega2560.h"
#endif

#ifdef CPU_MAP_ATMEGA1284P // 
  #include "cpu_map/cpu_map_atmega1284p.h"
#endif

#ifdef PIN_MAP_CUSTOM_SEBBRA
  
	#define ENABLE_SPINDEL_PWM
	
	  
	// Serial port pins
	#define SERIAL_RX USART_RX_vect
	#define SERIAL_UDRE USART_UDRE_vect
  
	// Define pin-assignments
	// NOTE: All step bit and direction pins must be on the same port.
	#define STEP_DDR       DDRC
	#define STEP_PORT      PORTC
	#define X_STEP_BIT         0  	//  A0
	#define Y_STEP_BIT         2  	//  A2
	#define Z_STEP_BIT         4  	//  A4
	#define STEP_MASK ((1<<X_STEP_BIT)|(1<<Y_STEP_BIT)|(1<<Z_STEP_BIT)) // All step bits
	
	#define DIRECTION_DDR	DDRC
	#define DIRECTION_PORT	PORTC
	#define X_DIRECTION_BIT    1 	//  A1
	#define Y_DIRECTION_BIT    3 	//  A3
	#define Z_DIRECTION_BIT    5 	//  A5
	#define DIRECTION_MASK ((1<<X_DIRECTION_BIT)|(1<<Y_DIRECTION_BIT)|(1<<Z_DIRECTION_BIT)) // All direction bits
	

	#define STEPPERS_DISABLE_DDR    DDRC
	#define STEPPERS_DISABLE_PORT   PORTC
	#define STEPPERS_DISABLE_BIT    6 	//  A6
	#define STEPPERS_DISABLE_MASK (1<<STEPPERS_DISABLE_BIT)

	// NOTE: All limit bit pins must be on the same port
	#define LIMIT_DDR       DDRD
	#define LIMIT_PIN       PIND
	#define LIMIT_PORT      PORTD
	#define X_LIMIT_BIT     2 		//  D2
	#define Y_LIMIT_BIT     3 		//  D3
	#define Z_LIMIT_BIT     4 		//  D4
	#define LIMIT_INT       PCIE0   // Pin change interrupt enable pin
	#define LIMIT_INT_vect  PCINT0_vect 
	#define LIMIT_PCMSK     PCMSK0 // Pin change interrupt register
	#define LIMIT_MASK ((1<<X_LIMIT_BIT)|(1<<Y_LIMIT_BIT)|(1<<Z_LIMIT_BIT)) // All limit bits

	#define SPINDLE_ENABLE_DDR   DDRB
	#define SPINDLE_ENABLE_PORT  PORTB
	#define SPINDLE_ENABLE_BIT   0 		//  D8

	#define SPINDLE_DIRECTION_DDR   DDRB
	#define SPINDLE_DIRECTION_PORT  PORTB
	#define SPINDLE_DIRECTION_BIT   2 	//  D10

	#define COOLANT_FLOOD_DDR   DDRB
	#define COOLANT_FLOOD_PORT  PORTB
	#define COOLANT_FLOOD_BIT   1  //  D9
	
	  // Define probe switch input pin.
	#define PROBE_DDR       DDRC
	#define PROBE_PIN       PINC
	#define PROBE_PORT      PORTC
	#define PROBE_BIT       7  		//  A7
	#define PROBE_MASK      (1<<PROBE_BIT)

	// NOTE: All pinouts pins must be on the same port
	#define CONTROL_DDR       DDRD
	#define CONTROL_PIN       PIND
	#define CONTROL_PORT      PORTD
	#define RESET_BIT        7  		//  D7
	#define FEED_HOLD_BIT    5  		//  D5
	#define SAFETY_DOOR_BIT  5  		//  D5
	#define CYCLE_START_BIT  6  		//  D6
	#define CONTROL_INT       PCIE1  // Pin change interrupt enable pin
	#define CONTROL_INT_vect  PCINT1_vect
	#define CONTROL_PCMSK     PCMSK1 // Pin change interrupt register	
	#define CONTROL_MASK ((1<<RESET_BIT)|(1<<FEED_HOLD_BIT)|(1<<CYCLE_START_BIT)|(1<<SAFETY_DOOR_BIT))
	
#endif


/* 
#ifdef CPU_MAP_CUSTOM_PROC
  // For a custom pin map or different processor, copy and edit one of the available cpu
  // map files and modify it to your needs. Make sure the defined name is also changed in
  // the config.h file.
#endif
*/

#endif
