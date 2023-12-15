/*
 * Gpio.c
 *
 *  Created on: Nov 20, 2023
 *      Author: Ahmed Sayed
 */
#include "Gpio.h"
#include "common_macros.h"

void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num,GPIO_PinDirection direction)
{
	if (port_num>PORT_NUMS || pin_num > PINS_PER_PORT)
	{
		/*  NOTHING */
	}
	else
	{
		switch(port_num)
		{
			case PORTA_ID:
				if (direction == PIN_OUTPUT)
				{
					SET_BIT(DDRA_REG,pin_num);
				}
				else if(direction == PIN_INPUT)
				{
					CLEAR_BIT(DDRA_REG,pin_num);
				}
				break;
			case PORTB_ID:
				if (direction == PIN_OUTPUT)
				{
					SET_BIT(DDRB_REG,pin_num);
				}
				else if(direction == PIN_INPUT)
				{
					CLEAR_BIT(DDRB_REG,pin_num);
				}
				break;
			case PORTC_ID:
				if (direction == PIN_OUTPUT)
				{
					SET_BIT(DDRC_REG,pin_num);
				}
				else if(direction == PIN_INPUT)
				{
					CLEAR_BIT(DDRC_REG,pin_num);
				}
				break;
			case PORTD_ID:
				if (direction == PIN_OUTPUT)
				{
					SET_BIT(DDRD_REG,pin_num);
				}
				else if(direction == PIN_INPUT)
				{
					CLEAR_BIT(DDRD_REG,pin_num);
				}
				break;
		}
	}
}
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value)
{
	if (port_num > PORT_NUMS || pin_num >PINS_PER_PORT)
	{

	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			if(value==LOGIC_HIGH)
			{
				SET_BIT(PORTA_REG,pin_num);
			}
			else if(value==LOGIC_LOW)
			{
				CLEAR_BIT(PORTA_REG,pin_num);
			}
			break;
		case PORTB_ID:
			if(value==LOGIC_HIGH)
			{
				SET_BIT(PORTB_REG,pin_num);
			}
			else if(value==LOGIC_LOW)
			{
				CLEAR_BIT(PORTB_REG,pin_num);
			}
			break;
		case PORTC_ID:
			if(value==LOGIC_HIGH)
			{
				SET_BIT(PORTC_REG,pin_num);
			}
			else if(value==LOGIC_LOW)
			{
				CLEAR_BIT(PORTC_REG,pin_num);
			}
			break;
		case PORTD_ID:
			if(value==LOGIC_HIGH)
			{
				SET_BIT(PORTD_REG,pin_num);
			}
			else if(value==LOGIC_LOW)
			{
				CLEAR_BIT(PORTD_REG,pin_num);
			}
			break;
		}
	}
}
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num)
{
	uint8 PIN_value=LOGIC_LOW;
	if (port_num > PORT_NUMS || pin_num >PINS_PER_PORT)
	{

	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			if(BIT_IS_SET(PINA_REG,pin_num))
			{
				PIN_value=LOGIC_HIGH;
			}
			else
			{
				PIN_value=LOGIC_LOW;
			}
			break;
		case PORTB_ID:
			if(BIT_IS_SET(PINB_REG,pin_num))
			{
				PIN_value=LOGIC_HIGH;
			}
			else
			{
				PIN_value=LOGIC_LOW;
			}
			break;
			if(BIT_IS_SET(PINC_REG,pin_num))
			{
				PIN_value=LOGIC_HIGH;
			}
			else
			{
				PIN_value=LOGIC_LOW;
			}
			break;
			if(BIT_IS_SET(PIND_REG,pin_num))
			{
				PIN_value=LOGIC_HIGH;
			}
			else
			{
				PIN_value=LOGIC_LOW;
			}
			break;
		}
	}
	return PIN_value;
}
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirection direction)
{
	if(port_num >PORT_NUMS)
	{

	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			if(direction == PORT_OUTPUT)
			{
				DDRA_REG=PORT_OUTPUT;
			}
			else
			{
				DDRA_REG=PORT_INPUT;
			}
			break;
		case PORTB_ID:
				if(direction == PORT_OUTPUT)
				{
					DDRB_REG=PORT_OUTPUT;
				}
				else
				{
					DDRB_REG=PORT_INPUT;
				}
				break;
		case PORTC_ID:
				if(direction == PORT_OUTPUT)
				{
					DDRC_REG=PORT_OUTPUT;
				}
				else
				{
					DDRC_REG=PORT_INPUT;
				}
				break;
		case PORTD_ID:
				if(direction == PORT_OUTPUT)
				{
					DDRD_REG=PORT_OUTPUT;
				}
				else
				{
					DDRD_REG=PORT_INPUT;
				}
				break;

	}
	}
}
void GPIO_writePort(uint8 port_num, uint8 value)
{
	if(port_num >PORT_NUMS)
	{

	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			PORTA_REG=value;
			break;
		case PORTB_ID:
			PORTB_REG=value;
			break;
		case PORTC_ID:
			PORTC_REG=value;
			break;
		case PORTD_ID:
			PORTD_REG=value;
			break;
		}
	}
}
uint8 GPIO_readPort(uint8 port_num)
{
	uint8 PORT_VALUE;
	if(port_num >PORT_NUMS)
	{
		return 0;
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			PORT_VALUE=PINA_REG;
			break;
		case PORTB_ID:
			PORT_VALUE=PINB_REG;
			break;
		case PORTC_ID:
			PORT_VALUE=PINC_REG;
			break;
		case PORTD_ID:
			PORT_VALUE=PIND_REG;
			break;

		}
	}
	return PORT_VALUE;

}

