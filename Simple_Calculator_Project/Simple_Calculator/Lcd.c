/*
 * Lcd.c
 *
 *  Created on: Nov 22, 2023
 *      Author: Ahmed Sayed
 */

#include "Lcd.h"
#include <stdLib.h>
#include<stdio.h>
#include "Gpio.h"
#include "common_macros.h"
#include <util/delay.h>
/* =====================================================================================
 *                              Send_command function
 *  Description:
 *  It Used To Send Specific Commands For LCD
 *  Return : VOID
 *  ARGUMENTS : THE COMMAND OF LCD
 *  Steps To Send Command From Data-sheet (Ac_Charchtristics)
 * =====================================================================================
 */
void LCD_SendCommand(uint8 command)
{
	 GPIO_writePin(PORT_RS,RS_Pin,LOGIC_LOW); /* RS_PIN = ZERO FOR COMMAND REGISTER [FROM DATA_SHEET] */
	 _delay_ms(1);    /* Delay_for Tas  */
	 GPIO_writePin(PORT_EN,Enable_Pin,LOGIC_HIGH); /* LOGIC_HIGH For Enable_Pin */
	 _delay_ms(1);  /* T=Tpw-Tsdw -> 290-100=190 nanosecond */
#if(PORT_DATA_BUS_MODE==4)
	 GPIO_writePin(PORTD_ID,PIN_DATA_D4,GET_BIT(command,4)); /* Write On Each Pin The Most Significant 4-bit First Using GET_BIT MACRO */
	 GPIO_writePin(PORTD_ID,PIN_DATA_D5,GET_BIT(command,5)); /* Write On Each Pin The Most Significant 4-bit First Using GET_BIT MACRO */
	 GPIO_writePin(PORTD_ID,PIN_DATA_D6,GET_BIT(command,6)); /* Write On Each Pin The Most Significant 4-bit First Using GET_BIT MACRO */
	 GPIO_writePin(PORTD_ID,PIN_DATA_D7,GET_BIT(command,7)); /* Write On Each Pin The Most Significant 4-bit First Using GET_BIT MACRO */
	 _delay_ms(1); /* Tsdw Time */
	 GPIO_writePin(PORT_EN,Enable_Pin,LOGIC_LOW);
	 _delay_ms(1); /* Th Time To hold Data On Data_Bus  */
	 GPIO_writePin(PORT_EN,Enable_Pin,LOGIC_HIGH);
	 _delay_ms(1);/* T=Tpw-Tsdw -> 290-100=190 nanosecond */
	 GPIO_writePin(PORTD_ID,PIN_DATA_D4,GET_BIT(command,0));/* Write On Each Pin The LEAST Significant 4-bit First Using GET_BIT MACRO */
	 GPIO_writePin(PORTD_ID,PIN_DATA_D5,GET_BIT(command,1));/* Write On Each Pin The LEAST Significant 4-bit First Using GET_BIT MACRO */
	 GPIO_writePin(PORTD_ID,PIN_DATA_D6,GET_BIT(command,2));/* Write On Each Pin The LEAST Significant 4-bit First Using GET_BIT MACRO */
	 GPIO_writePin(PORTD_ID,PIN_DATA_D7,GET_BIT(command,3));/* Write On Each Pin The LEAST Significant 4-bit First Using GET_BIT MACRO */
	 _delay_ms(1); /* Tsdw Time */
	 GPIO_writePin(PORT_EN,Enable_Pin,LOGIC_LOW);
	 _delay_ms(1); /* Th Time To hold Data On Data_Bus  */

#elif(PORT_DATA_BUS_MODE==8)
	 GPIO_writePort(PORTC_ID,command);
	 _delay_ms(1); /* Tsdw Time */
	 GPIO_writePin(PORT_EN,Enable_Pin,LOGIC_LOW);
	 _delay_ms(1);/* Th Time To hold Data On Data_Bus  */
#endif
}
/* =====================================================================================
 *                             Display_Charchterfunction
 *  Description:
 *  It Used To Send characters For LCD
 *  Return : VOID
 *  ARGUMENTS : THE Asci Values of characters  for  LCD
 *  Steps To Display characters From Data-sheet (Ac_Charchtristics)
 * =====================================================================================
 */
void LCD_DisplayCharchter(uint8 data)
{
	 GPIO_writePin(PORT_RS,RS_Pin,LOGIC_HIGH); /* RS_PIN = ONE FOR Display REGISTER [FROM DATA_SHEET] */
	 _delay_ms(1); /* Delay_for Tas  */
	 GPIO_writePin(PORT_EN,Enable_Pin,LOGIC_HIGH); /* LOGIC_HIGH For Enable_Pin */
	 _delay_ms(1); /* T=Tpw-Tsdw -> 290-100=190 nanosecond */
#if (PORT_DATA_BUS_MODE==4)
	 GPIO_writePin(PORTD_ID,PIN_DATA_D4,GET_BIT(data,4));/* Write On Each Pin The Most Significant 4-bit First Using GET_BIT MACRO */
	 GPIO_writePin(PORTD_ID,PIN_DATA_D5,GET_BIT(data,5));/* Write On Each Pin The Most Significant 4-bit First Using GET_BIT MACRO */
	 GPIO_writePin(PORTD_ID,PIN_DATA_D6,GET_BIT(data,6));/* Write On Each Pin The Most Significant 4-bit First Using GET_BIT MACRO */
	 GPIO_writePin(PORTD_ID,PIN_DATA_D7,GET_BIT(data,7));/* Write On Each Pin The Most Significant 4-bit First Using GET_BIT MACRO */
	 _delay_ms(1);/* Tsdw Time */
	 GPIO_writePin(PORT_EN,Enable_Pin,LOGIC_LOW);
	 _delay_ms(1);/* Th Time To hold Data On Data_Bus  */
	 GPIO_writePin(PORT_EN,Enable_Pin,LOGIC_HIGH);
	 _delay_ms(1);/* T=Tpw-Tsdw -> 290-100=190 nanosecond */
	 GPIO_writePin(PORTD_ID,PIN_DATA_D4,GET_BIT(data,0));/* Write On Each Pin The LEAST Significant 4-bit First Using GET_BIT MACRO */
	 GPIO_writePin(PORTD_ID,PIN_DATA_D5,GET_BIT(data,1));/* Write On Each Pin The LEAST Significant 4-bit First Using GET_BIT MACRO */
	 GPIO_writePin(PORTD_ID,PIN_DATA_D6,GET_BIT(data,2));/* Write On Each Pin The LEAST Significant 4-bit First Using GET_BIT MACRO */
	 GPIO_writePin(PORTD_ID,PIN_DATA_D7,GET_BIT(data,3));/* Write On Each Pin The LEAST Significant 4-bit First Using GET_BIT MACRO */
	 _delay_ms(1);/* Tsdw Time */
	 GPIO_writePin(PORT_EN,Enable_Pin,LOGIC_LOW);
	 _delay_ms(1);/* Th Time To hold Data On Data_Bus  */
#elif(PORT_DATA_BUS_MODE==8)
	 GPIO_writePort(PORTC_ID,data);
	 _delay_ms(1); /* Tsdw Time */
	 GPIO_writePin(PORT_EN,Enable_Pin,LOGIC_LOW);
	 _delay_ms(1);/* Th Time To hold Data On Data_Bus  */
#endif
}
/* =====================================================================================
 *                             Initialization of Lcd function
 *  Description:
 *  It Used To Initialize of LCD
 *  Return : VOID
 *  ARGUMENTS :Void
 * =====================================================================================
 */
void LCD_init(void)
{
	GPIO_setupPinDirection(PORT_RS,RS_Pin,PIN_OUTPUT);  /* Set Direction Rs_Pin As Output Pin */
	GPIO_setupPinDirection(PORT_EN,Enable_Pin,PIN_OUTPUT);/* Set Direction Enable_Pin As Output Pin */
	 _delay_ms(20);
#if (PORT_DATA_BUS_MODE==4)
	 GPIO_setupPinDirection(PORTD_ID,PIN_DATA_D7,PIN_OUTPUT);/* Set Direction PORT Pin D7 As Output Pin */
	 GPIO_setupPinDirection(PORTD_ID,PIN_DATA_D6,PIN_OUTPUT);/* Set Direction PORT Pin D6 As Output Pin */
	 GPIO_setupPinDirection(PORTD_ID,PIN_DATA_D5,PIN_OUTPUT);/* Set Direction PORT Pin D5 As Output Pin */
	 GPIO_setupPinDirection(PORTD_ID,PIN_DATA_D4,PIN_OUTPUT);/* Set Direction PORT Pin D5 As Output Pin */
	 LCD_SendCommand(Command_Initiate_lcd_4_bit_mode_one); /* Send Command To Transfer To 4-bit Mode  */
	 LCD_SendCommand(Command_Initiate_lcd_4_bit_mode_two); /* Send Command To Transfer To 4-bit Mode  */
	 LCD_SendCommand(Command_INITIATE_4_BIT_MODE); /* Send Command To Initiate To 4-bit Mode  */
#elif(PORT_DATA_BUS_MODE==8)
	GPIO_setupPortDirection(PORT_DATA_BUS,PORT_OUTPUT);

	LCD_SendCommand(initiate_screen);/* Send Command To Initiate To 8-bit Mode  */

#endif

	LCD_SendCommand(Cursor_off); /* Send Command To Initiate The Screen To Work With The Same Order  */
	LCD_SendCommand(Clear_Display); /* Send Command To Initiate The Screen To Work With The Same Order  */

}

void LCD_DisplayString(const char *str)  /* Here We define char instead of uint8 because the pointer to char used signed not unsigned \
to avoid warnings */
{
	uint8 i=0;
	while(str[i]!='\0')
	{
		LCD_DisplayCharchter(str[i]);
		i++;
	}
}

void Move_Cursor(uint8 row,uint8 col) /* The DIscuss In tHE NOTEBOOK */
{
	switch(row)
	{
	case Row_Zero_Address:
		LCD_SendCommand((col+0x00)|Move_Cursor_Frist_Row);
		break;
	case Row_First_Address:
		LCD_SendCommand((col+0x40)|Move_Cursor_Frist_Row);
		break;
	case Row_Second_Address:
		LCD_SendCommand((col+0x10)|Move_Cursor_Frist_Row);
		break;
	case Row_Third_Address:
		LCD_SendCommand((col+0x50)|Move_Cursor_Frist_Row);
		break;
	}

}
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *str)
{
	Move_Cursor(row,col);
	LCD_DisplayString(str);
}

void LCD_ClearScreen(void)
{
	/* IF need to clear screen and write in first row and col will return automatic not need to call move cursor*/
	LCD_SendCommand(Clear_Display);
}
void LCD_IntgerToString(uint32 data) /* The DIscuss In tHE NOTEBOOK */
{
	char buff[16];
	itoa(data,buff,10);
	LCD_DisplayString(buff);
}
void LCD_FloatToString(float32 data)  /* The DIscuss In tHE NOTEBOOK */
{
	char buff[30];
	dtostrf(data,1,4,buff);
	LCD_DisplayString(buff);
}

