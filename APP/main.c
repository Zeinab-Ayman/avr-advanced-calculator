/*
 * main.c
 *
 *  Created on: Aug 16, 2026
 *      Author: Zeinab
 */

#include "../Serv/BIT_MATH.h"
#include "../Serv/STD_TYPES.h"
#include "../HAL/LCD/LCD_Init.h"
#include "../HAL/KPD/KPD_Init.h"
#include "OP.h"
#include <util/delay.h>

int main(){
	Init_KPD();
	Init_LCD4Bit();

	uint8 pressedKey;

	f32 nums[10];
	uint8 ops[10];

	uint8 noNums=0;
	uint8 noOps=0;

	f32 num=0;
	uint8 op=0;

	f32 result=0;

	uint8 flag =0;
	uint8 zeroError=0;

	uint8 charCount = 0;
	uint8 shiftCount = 0;
	while(1){

		pressedKey = KPD_u8GetPressedKey();

		if(pressedKey !=0){

			if(pressedKey >= '0' && pressedKey <= '9'){

				if(flag){
					LCD_vid4BitWriteCmd(LCD_CMD_CLEAR_DIS);
					_delay_ms(2);
					num = 0;
					flag=0;
				}

				LCD_vid4BitWriteChar(pressedKey);
				charCount++;
				if(charCount > 16){
					LCD_vid4BitWriteCmd(LCD_CMD_SHIFT_DIS_LEFT);
					shiftCount++;
				}
				num = num*10 + (pressedKey -'0');

			}

			else if(pressedKey == '+' || pressedKey == '-' || pressedKey == '*' || pressedKey == '/'){

				if(flag){
					LCD_vid4BitWriteCmd(LCD_CMD_CLEAR_DIS);
					_delay_ms(2);
					LCD_vid4BitWriteFloat(result);
					flag = 0;
					shiftCount = 0;
					charCount = 0;
				}

				LCD_vid4BitWriteChar(pressedKey);
				charCount++;
				if(charCount > 16){
					LCD_vid4BitWriteCmd(LCD_CMD_SHIFT_DIS_LEFT);
					shiftCount++;
				}

				op = pressedKey;
				ops[noOps]=op;
				noOps++;

				nums[noNums]=num;
				noNums++;

				num=0;
			}

			else if (pressedKey == '='){

				LCD_vid4BitGoto(1,shiftCount);
				_delay_ms(1);
			    LCD_vid4BitWriteChar(pressedKey);

				nums[noNums]=num;
				noNums++;

			    result = EvaluateExpression(nums,noNums,ops,noOps,&zeroError);

			    if(zeroError){
			    	LCD_vid4BitWriteStr((uint8*)" Error");
			    	num = 0;
			    	noNums = 0;
			    	noOps = 0;
			    	flag = 0;
			    	zeroError = 0;
			    	charCount = 0;
			    	shiftCount = 0;
			    }

			    else{
			    	LCD_vid4BitWriteFloat(result);

			    	num = result;
			    	noNums = 0;
			    	noOps = 0;
			    	flag = 1;
			    	charCount = 0;
			    	shiftCount = 0;
			    }
			}

			else if (pressedKey == 'C'){
			     LCD_vid4BitWriteCmd(LCD_CMD_CLEAR_DIS);
			     _delay_ms(2);

			     num = 0;
			     noNums = 0;
			     noOps = 0;
			     result = 0;
			     op = 0;
			     flag = 0;
			     charCount = 0;
			     shiftCount = 0;
			}
		}
	}
}
