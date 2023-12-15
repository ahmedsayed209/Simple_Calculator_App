/*
 * Gpio.h
 *
 *  Created on: Nov 20, 2023
 *      Author: Ahmed Sayed
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "std_types.h"
#include "Atmega32_Registers.h"

                             /* Define All Specs. Of PORT Numbers And Pins  */
#define PORT_NUMS 4
#define PINS_PER_PORT 8

      /* That Way We Define The Ports ID TO USE INSTEAD OF NUMBERS */
#define PORTA_ID 0
#define PORTB_ID 1
#define PORTC_ID 2
#define PORTD_ID 3

#define PIN0_ID 0
#define PIN1_ID 1
#define PIN2_ID 2
#define PIN3_ID 3
#define PIN4_ID 4
#define PIN5_ID 5
#define PIN6_ID 6
#define PIN7_ID 7

typedef enum
{
	PIN_INPUT,PIN_OUTPUT
}GPIO_PinDirection;

typedef enum
{
	PORT_INPUT,PORT_OUTPUT=0xff
}GPIO_PortDirection;

void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num,GPIO_PinDirection direction);

void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value);
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num);
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirection direction);
void GPIO_writePort(uint8 port_num, uint8 value);
uint8 GPIO_readPort(uint8 port_num);




#endif /* GPIO_H_ */
