/*
 * ==========================================================================================================================
 *
 *                                             Simple Calculator Application
 *  Created by : Ahmed Sayed
 *  Drivers used :
 *  LCD
 *  GPIO
 *  KEYPAD
 *  INTERRUPT
 * ===========================================================================================================================
 */

#include "Keypad.h"
#include "Lcd.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Gpio.h"
/*
 * =========================================================================================================
 *
 *                                        Global Variables Definitions
 * =========================================================================================================
 */
#define Arr_Size 5
static volatile uint8 count_glo=0;
static volatile uint8 count_glo_2=0;
static volatile sint32 num1[Arr_Size];
static volatile sint32 num2[Arr_Size];
/*===========================================================================================================
 *
 *                                 Prototypes of functions used with in Application
 *    *Static functions : To avoid call this functions in another file*
 * ==========================================================================================================
 */
 static sint32 Sum_Function(void);
 static sint32 Minus_Function(void);
 static sint32 Multiplay_Function(void);
 static float Division_Function(void);
 /*===========================================================================================================
  *                       Function Definition : To Initialize The Calculator Every Time Call
  * ==========================================================================================================
  */
static void Initialize_Calculator(void)
{
	LCD_displayStringRowColumn(0,0,"Num1=");
	LCD_displayStringRowColumn(1,0,"Num2=");
	LCD_displayStringRowColumn(2,0,"Operation=");
	LCD_displayStringRowColumn(3,0,"Result=");
	Move_Cursor(0,6);
}
/*===========================================================================================================
 *                       Function Definition : To Reset  Calculator Every Time Call
 * ==========================================================================================================
 */
static void Reset_Calculator(void)
{
	    LCD_ClearScreen();
	    _delay_ms(50);
		Initialize_Calculator();

}
/*===========================================================================================================
 *                       Function Definition : To Initialize The External Interrupt (IN2)
 *
 * ==========================================================================================================
 */
static void Interrupt_Init()
{
	GPIO_setupPinDirection(PORTB_ID,PIN3_ID,PIN_INPUT);
	MCUCSR&=~(1<<ISC2);
	GICR|=(1<<INT2);
	SREG|=(1<<7);

}
/*============================================================================================================
 *          ISR FUNCTION : TO RESET CALCULATOR WHEN PRESS ON External Button connected on  (INT2 PIN )
 *
 * ===========================================================================================================
 */
ISR( INT2_vect)
 {
	Reset_Calculator();
 }

int main(void)
{
	uint8 operation;       /* Operation Variable to Read From User The Needed Operation Every Time  */
	uint8 count=0;         /*Counter Variable To Increment The Index of Array that carry digits */
	uint8 Equ='=';         /*Equal Variable Carry the ASCII OF  '='  */
	float result=0;        /* Result Variable that carry the final result of the operation  */
	LCD_init();            /*LCD_Initilization Function : To Initialize The LCD */
	Interrupt_Init();      /* Interrupt Initialize Mode  */
	Initialize_Calculator(); /*Calculator Initialization */

	for(;;)
	{
		for(count=0;count<Arr_Size;count++)
		{
		Move_Cursor(0,6+count);
		num1[count]=GET_PressedKey();    /* Read Every Time Key Pressed To Save Digits of first Number in Array num1 */
		LCD_IntgerToString(num1[count]); /*Display The Digits on LCD  */
		_delay_ms(450);
		if(Equ==GET_PressedKey()) /* Check on '=' If It Pressed : It will indicate that first number is scanned from user
		                                and move to second number    */
		{
			count_glo=count;      /* Save The Count Times To Used it in operation functions  */
			break;
		}
		}
		_delay_ms(250); /* Delay to Avoid Mistake In Numbers */

		for(count=0;count<Arr_Size;count++)
		{

		Move_Cursor(1,6+count);
		num2[count]=GET_PressedKey();  /* Read Every Time Key Pressed To Save Digits of first Number in Array num2 */
		LCD_IntgerToString(num2[count]); /*Display The Digits on LCD  */
		_delay_ms(450);
		if(Equ==GET_PressedKey()) /* Check on '=' If It Pressed : It will indicate that Second number is scanned from user and
		                             Move To THe Third Line that is operation */

		{
			count_glo_2=count; /* Save The Count Times To Used it in operation functions  */
			break;
		}

		}
		_delay_ms(500); /* Delay to Avoid Mistake In Numbers */

		operation=GET_PressedKey(); /* Scan The Operation From User { *,/,+,-} */
		Move_Cursor(2,13);
		LCD_DisplayCharchter(operation); /* Display The Operation on LCD Screen  */
		_delay_ms(550);

		switch(operation)
		{
		case '+':
			if(Equ==GET_PressedKey()) /* Check If User Press on Equal Operation: Here Will Not Moved Any Line it will Display Result */

			{
				Move_Cursor(3,8);
				result=Sum_Function(); /* Save The Return from Summation function In Result   */
				LCD_IntgerToString(result); /*Display The Result  */
			}
			break;
		case '-':
			if(Equ==GET_PressedKey()) /* Check If User Press on Equal Operation: Here Will Not Moved Any Line it will Display Result */
			{
				Move_Cursor(3,8);
				result=Minus_Function(); /* Save The Return from Difference function In Result   */
				LCD_IntgerToString(result); /*Display The Result */
			}
			break;

		case '*':
			if(Equ==GET_PressedKey()) /* Check If User Press on Equal Operation: Here Will Not Moved Any Line it will Display Result */
			{
				Move_Cursor(3,8);
				result=Multiplay_Function(); /* Save The Return from Multiplication function In Result   */
				LCD_IntgerToString(result); /*Display The Result */
			}
			break;
		case '/':
			if(Equ==GET_PressedKey()) /* Check If User Press on Equal Operation: Here Will Not Moved Any Line it will Display Result */
			{
				Move_Cursor(3,8);
				result=(float)Division_Function(); /* Save The Return from Division function In Result
				                                    *Casting The Return variable To Display Numbers after point * 	*/

				if(result=='e')      /* If The Return From Division_Function is 'e' It Means That Domainator Contains Zero   */
				{
					 LCD_ClearScreen();
					 _delay_ms(40);
					LCD_DisplayString("MATH_ERROR"); /* Display MATH ERORR TO USER BECUASE IT DIVIDE A NUMBER BY ZERO */
					_delay_ms(800);
					 LCD_ClearScreen();
					 Initialize_Calculator(); /* Initialize The Calculator Screen Again  */
				}
				else {
					LCD_FloatToString(result); /* If No Error Display The Result */
				}
			}
}

}
}

static sint32 Sum_Function(void)
{
	uint8 count=0;      /* Local Variable Counter To  Count The Array Digits To Convert Them into Number */
	sint32 res_num1=0;  /*Result Number1 : It will carry The Number of digits of Num1 */
	sint32 res_num2=0;  /*Result Number2 : It will carry The Number of digits of Num2 */
	for(count=0;count<=count_glo;count++) /* Count_glo is variable That Give Information About How Many Digits Scanned in Array */
	{
		/*
		 * Algorithm : if array {1,2,3} and need to get number
		 * step1: 0+1 as res_num1 at first =0 ,res_num1 will =1
		 * step 2 : 1*10 + 2 -> 12 ,now res_num1 = 12
		 * step 3 : 12*10 +3 -> 123 , Now Res_mum1=123
		 */
		res_num1=res_num1*10 + num1[count];
		_delay_ms(300);
	}
	for(count=0;count<=count_glo_2;count++)
	{
		res_num2=res_num2*10 + num2[count];
		_delay_ms(300);
	}

	return (res_num1+res_num2); /*Return The Summation of Res_num1 and num2 to Summation function */

}
static sint32 Minus_Function(void)
{
	uint8 count=0;
	sint32 res_num1=0;
	sint32 res_num2=0;
	for(count=0;count<=count_glo;count++)
	{
		res_num1=res_num1*10 + num1[count];
		_delay_ms(300);
	}
	for(count=0;count<=count_glo_2;count++)
	{
		res_num2=res_num2*10 + num2[count];
		_delay_ms(300);
	}

	return (res_num1-res_num2); /*Return The Difference of Res_num1 and num2 to Summation function */
}
static sint32 Multiplay_Function(void)
{
	uint8 count=0;
	sint32 res_num1=0;
	sint32 res_num2=0;
	for(count=0;count<=count_glo;count++)
	{
		res_num1=res_num1*10 + num1[count];
		_delay_ms(300);
	}
	for(count=0;count<=count_glo_2;count++)
	{
		res_num2=res_num2*10 + num2[count];
		_delay_ms(300);
	}

	return (res_num1*res_num2); /*Return The Multiplication of Res_num1 and num2 to Summation function */
}
static float Division_Function(void)
{
	uint8 count=0;
	sint32 res_num1=0;
	sint32 res_num2=0;
	for(count=0;count<=count_glo;count++)
	{
		res_num1=res_num1*10 + num1[count];
		_delay_ms(300);
	}
	for(count=0;count<=count_glo_2;count++)
	{
		res_num2=res_num2*10 + num2[count];
		_delay_ms(300);
	}
	if(res_num2==0)
	{
		return 'e';
	}

	return ((float)res_num1/res_num2); /*Return The Division of Res_num1 and num2 to Summation function */
}
