/*
 * keypad.c
 *
 *  Created on: Dec 9, 2023
 *      Author: Ahmed Sayed
 */


#include "Keypad.h"
#include "Gpio.h"

#if(Keypad_Cols_Nums==4)
static uint8 Keypad_Matrix_four_col (uint8 Map_Button);
#elif(Keypad_Cols_Nums==3)
static uint8 Keypad_Mapping4x3(uint8 Map_Button);
#endif


uint8 GET_PressedKey(void)
{
	uint8 row,col=0;
	GPIO_setupPinDirection(Keypad_Rows_Port,Keypad_Rows_Pin,PIN_INPUT);
	GPIO_setupPinDirection(Keypad_Rows_Port,Keypad_Rows_Pin+1,PIN_INPUT);
	GPIO_setupPinDirection(Keypad_Rows_Port,Keypad_Rows_Pin+2,PIN_INPUT);
	GPIO_setupPinDirection(Keypad_Rows_Port,Keypad_Rows_Pin+3,PIN_INPUT);

	GPIO_setupPinDirection(Keypad_Cols_Port,Keypad_Cols_Pin,PIN_INPUT);
	GPIO_setupPinDirection(Keypad_Cols_Port,Keypad_Cols_Pin+1,PIN_INPUT);
	GPIO_setupPinDirection(Keypad_Cols_Port,Keypad_Cols_Pin+2,PIN_INPUT);
#if (Keypad_Cols_Nums==4)
	GPIO_setupPinDirection(Keypad_Cols_Port,Keypad_Cols_Pin+3,PIN_INPUT);
#endif


for(;;)
{
	for (row=0;row<Keypad_Rows_Nums;row++)
	{
		GPIO_setupPinDirection(Keypad_Rows_Port,Keypad_Rows_Pin+row,PIN_OUTPUT);
		GPIO_writePin(Keypad_Rows_Port,Keypad_Rows_Pin+row,LOGIC_LOW);

		for(col=0;col<Keypad_Cols_Nums;col++)
		{
			if (GPIO_readPin(Keypad_Cols_Port,Keypad_Cols_Pin+col)==LOGIC_LOW)
			{
#if(Keypad_Cols_Nums==4)
				return Keypad_Matrix_four_col(((row*Keypad_Cols_Nums)+col+1));
#elif(Keypad_Cols_Nums==3)
				Keypad_Mapping4x3( ((row*Keypad_Cols_Nums)+col+1));
				return ;
#endif

			}
		}
		GPIO_setupPinDirection(Keypad_Rows_Port,Keypad_Rows_Pin+row,PIN_INPUT);
	}
}
}


#if(Keypad_Cols_Nums==4)

static uint8 Keypad_Matrix_four_col(uint8 Map_Button)
{
	uint8 ButtonNumber=0;

    switch(Map_Button)
	{
	case 1: ButtonNumber=7;
	break;
	case 2: ButtonNumber=8;
	break;
	case 3:ButtonNumber=9;
	break;
	case 4:ButtonNumber='/';
	break;
	case 5:ButtonNumber=4;
	break;
	case 6:ButtonNumber=5;
	break;
	case 7:ButtonNumber=6;
	break;
	case 8:ButtonNumber='*';
	break;
	case 9:ButtonNumber=1;
	break;
	case 10:ButtonNumber=2;
	break;
	case 11:ButtonNumber=3;
	break;
	case 12:ButtonNumber='-';
	break;
	case 13:ButtonNumber='!';
	break;
	case 14:ButtonNumber=0;
	break;
	case 15:ButtonNumber='=';
	break;
	case 16:ButtonNumber='+';
	break;
	}
	return ButtonNumber;
}


#elif(Keypad_Cols_Nums==3)
static uint8 Keypad_Mapping4x3(uint8 Map_Button)
{
	uint8 ButtonNumber=0;
	switch(Map_Button)
	{
	case 10:ButtonNumber='*';
	break;
	case 11:ButtonNumber=0;
	break;
	case 12:ButtonNumber='#';
	break;
	}

	return ButtonNumber;
}

}
#endif
