/*
 * keypad.h
 *
 *  Created on: Dec 9, 2023
 *      Author: Ahmed Sayed
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "std_types.h"


#define Keypad_Rows_Nums 4
#define Keypad_Cols_Nums 4
/*
 * ==========================================================
 */

#define Keypad_Rows_Port PORTA_ID
#define Keypad_Cols_Port PORTA_ID

/*
 * =============================================================
 */

#define Keypad_Rows_Pin PIN0_ID
#define Keypad_Cols_Pin PIN4_ID

/*
* ============================================================
*/


uint8 GET_PressedKey(void);



#endif /* KEYPAD_H_ */
