/*
 * Atmega32_Registers.h
 *
 *  Created on: Nov 19, 2023
 *      Author: Ahmed Sayed
 */

#ifndef ATMEGA32_REGISTERS_H_
#define ATMEGA32_REGISTERS_H_

/*
typedef union
{
	uint8 Byte;
	struct
	{
		uint8 BIT0:1;
		uint8 BIT1:1;
		uint8 BIT2:1;
		uint8 BIT3:1;
		uint8 BIT4:1;
		uint8 BIT5:1;
		uint8 BIT6:1;
		uint8 BIT7:1;

	}Bits;
}Reg_bits;
*/
                                             /* PORTS Registers Definition  */

/* PORTA_REGISTERS */
#ifndef PORTA_REG
#define PORTA_REG  (*(volatile uint8  *const) 0x003B)
#define DDRA_REG   (*(volatile uint8  *const)0x003A)
#define PINA_REG   (*(volatile const uint8  *const)0x0039)
#endif
/* PORTB_REGISTERS */
#ifndef PORTB_REG
#define PORTB_REG  (*(volatile uint8  *const )0x0038)
#define DDRB_REG   (*(volatile uint8  *const)0x0037)
#define PINB_REG   (*(volatile const uint8  *const)0x0036)
#endif
/* PORTC_REGISTERS */
#ifndef PORTC_REG
#define PORTC_REG  (*(volatile uint8  * const)0x0035)
#define DDRC_REG   (*(volatile uint8  *const)0x0034)
#define PINC_REG   (*(volatile const uint8  *const)0x0033)
#endif
/* PORTD_REGISTERS */
#ifndef PORTD_REG
#define PORTD_REG  (*(volatile uint8  *const )0x0032)
#define DDRD_REG   (*(volatile uint8  *const)0x0031)
#define PIND_REG   (*(volatile const uint8  *const)0x0030)
#endif





#endif /* ATMEGA32_REGISTERS_H_ */

