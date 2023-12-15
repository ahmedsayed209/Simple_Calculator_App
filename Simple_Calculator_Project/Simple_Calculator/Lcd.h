/*
 * Lcd.h
 *
 *  Created on: Nov 22, 2023
 *      Author: Ahmed Sayed
 */

#ifndef LCD_H_
#define LCD_H_

#include "Std_Types.h"
   /* Initiate The Mode We Need To Use For LCD (4 Bit Mode | 8 Bit Mode) */
#define PORT_DATA_BUS_MODE 8
/* Check On The Mood If it within Range OR NOT  */
#if((PORT_DATA_BUS_MODE !=8) && (PORT_DATA_BUS_MODE !=4) )
#error "The Entered Mode is Wrong "
#endif


/* =====================================================================================
 *                               MODE Of Ports  For LCD
 * =====================================================================================
 */
#if(PORT_DATA_BUS_MODE==8)
#define PORT_DATA_BUS PORTC_ID /* This For The Data Bus Initialization PORT [ WHOLE PORT | 4 PINS FROM PORT]  */
#elif(PORT_DATA_BUS_MODE==4)



/* =====================================================================================
 *                               Common_Pins_Used For LCD
 * =====================================================================================
 */

#define PIN_DATA_D7   PIN7_ID /* First_PIN_4_BIT */
#define PIN_DATA_D6   PIN6_ID /* Second_PIN_4_BIT */
#define PIN_DATA_D5   PIN5_ID /* Third_PIN_4_BIT */
#define PIN_DATA_D4   PIN4_ID /*FOURTH_PIN_4_BIT */
#endif
#define PORT_RS      PORTD_ID /* PORT_OF_RS_PIN */
#define PORT_EN      PORTD_ID /*PORT_OF_ENABLE_PIN */
#define RS_Pin       PIN0_ID  /* PIN_OF_RS*/
#define Enable_Pin   PIN1_ID  /* PIN_OF_ENABLE*/
#define Row_Zero_Address    0 /* ADDRESS OF FIRST ROW IN LCD 16X2 FOR MOVE CURSOR FUNCTION */
#define Row_First_Address   1 /* ADDRESS OF SECOND ROW IN LCD 16X2 FOR MOVE CURSOR FUNCTION */
#define Row_Second_Address  2 /* ADDRESS OF THIRD ROW IN LCD 16X4 FOR MOVE CURSOR FUNCTION */
#define Row_Third_Address   3 /* ADDRESS OF FOURTH ROW IN LCD 16X4 FOR MOVE CURSOR FUNCTION */
/* =====================================================================================
 *                               Common_Addresses For LCD
 * =====================================================================================
 */
#define initiate_screen                     0X38
#define Cursor_off                          0x0C
#define Clear_Display                       0x01
#define Move_Cursor_Frist_Row               0x80
#define Move_Cursor_Second_Row              0xC0
#define Command_INITIATE_4_BIT_MODE         0x28
#define Command_Initiate_lcd_4_bit_mode_one 0x33
#define Command_Initiate_lcd_4_bit_mode_two 0x32
/* =====================================================================================
 *                               PROTO_TYPES OF FUNCTIONS For LCD
 * =====================================================================================
 */

void LCD_SendCommand(uint8 command);

void LCD_DisplayCharchter(uint8 data);

void LCD_DisplayString(const char *str);

void LCD_init(void);

void Move_Cursor(uint8 row,uint8 col);

void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *str);

void LCD_ClearScreen(void);

void LCD_IntgerToString(uint32 data);

void LCD_FloatToString(float32 data);

#endif /* LCD_H_ */
