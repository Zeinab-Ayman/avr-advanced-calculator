/*
 * LCD_Prog.c
 *
 *  Created on: Aug 9, 2026
 *      Author: Zeinab
 */

#include"../../Serv/BIT_MATH.h"
#include"../../Serv/STD_TYPES.h"
#include"../../MCAL/DIO/DIO_Init.h"
#include <util/delay.h>
#include"LCD_Init.h"
#include"LCD_Config.h"

void Init_LCD4Bit(){
	uint8 i=0;
	for(i = 0; i < 4; i++){
		DIO_vidSetPinDir(LCD_Pins[i], OUTPUT_PIN);
	}
	DIO_vidSetPinDir(RS,OUTPUT_PIN);
	DIO_vidSetPinDir(E,OUTPUT_PIN);
	_delay_ms(40);
	DIO_vidSetPinVal(RS,LOW_PIN);
	for(i =0;i<4;i++){
		DIO_vidSetPinVal(LCD_Pins[i],GET_BIT(LCD_CMD_4BIT_MODE,(4+i)));
	}
	DIO_vidSetPinVal(E,HIGH_PIN);
	_delay_ms(1);
	DIO_vidSetPinVal(E,LOW_PIN);
	LCD_vid4BitWriteCmd(LCD_CMD_4BIT_MODE);
	_delay_ms(1);
	LCD_vid4BitWriteCmd(LCD_CMD_DISPLAY_ON);
	_delay_ms(1);
	LCD_vid4BitWriteCmd(LCD_CMD_CLEAR_DIS);
	_delay_ms(2);
	LCD_vid4BitWriteCmd(LCD_CMD_ENTRY_MODE_INC);
}
void LCD_vid4BitWriteCmd(uint8 u8CopyCMD){
    uint8 i = 0;
    DIO_vidSetPinVal(RS, LOW_PIN);

    for(i = 0; i < 4; i++){
        DIO_vidSetPinVal(LCD_Pins[i], GET_BIT(u8CopyCMD, (i + 4)));
    }
    DIO_vidSetPinVal(E, HIGH_PIN);
    _delay_ms(1);
    DIO_vidSetPinVal(E, LOW_PIN);

    _delay_ms(1);

    for(i = 0; i < 4; i++){
        DIO_vidSetPinVal(LCD_Pins[i], GET_BIT(u8CopyCMD, i));
    }
    DIO_vidSetPinVal(E, HIGH_PIN);
    _delay_ms(1);
    DIO_vidSetPinVal(E, LOW_PIN);

    _delay_ms(2);
}
void LCD_vid4BitWriteChar(uint8 u8CopyChar){
    uint8 i = 0;
    DIO_vidSetPinVal(RS, HIGH_PIN);

    for(i = 0; i < 4; i++){
        DIO_vidSetPinVal(LCD_Pins[i], GET_BIT(u8CopyChar, (i + 4)));
    }
    DIO_vidSetPinVal(E, HIGH_PIN);
    _delay_ms(1);
    DIO_vidSetPinVal(E, LOW_PIN);

    _delay_ms(1);

    for(i = 0; i < 4; i++){
        DIO_vidSetPinVal(LCD_Pins[i], GET_BIT(u8CopyChar, i));
    }
    DIO_vidSetPinVal(E, HIGH_PIN);
    _delay_ms(1);
    DIO_vidSetPinVal(E, LOW_PIN);

    _delay_ms(1);
}

void LCD_vid4BitWriteStr(uint8 *u8Str){
    uint8 i = 0;
    for(i = 0 ; u8Str[i] != '\0' ; i++){
        LCD_vid4BitWriteChar(u8Str[i]);
    }
}

void LCD_vid4BitWriteInt(sint32 s32CopyNumber){
    uint8 arr[10];
    sint8 i = 0;

    if (s32CopyNumber == 0) {
        LCD_vid4BitWriteChar('0');
        return;
    }
    if (s32CopyNumber < 0) {
        LCD_vid4BitWriteChar('-');
        s32CopyNumber = -s32CopyNumber;
    }
    while (s32CopyNumber > 0) {
        arr[i] = (s32CopyNumber % 10) + '0';
        s32CopyNumber /= 10;
        i++;
    }
    for (i = i - 1; i >= 0; i--) {
        LCD_vid4BitWriteChar(arr[i]);
    }
}

void LCD_vid4BitGoto(uint8 u8CopyRow, uint8 u8CopyCol){
    if (u8CopyRow == 0) {
        LCD_vid4BitWriteCmd(0x80 + u8CopyCol);
    }
    else if (u8CopyRow == 1) {
        LCD_vid4BitWriteCmd(0xC0 + u8CopyCol);
    }
}

void LCD_vid4BitWriteFloat(f32 num)
{
    if (num < 0)
    {
        LCD_vid4BitWriteChar('-');
        num = -num;
    }

    sint32 integerPart = (sint32)num;
    LCD_vid4BitWriteInt(integerPart);

    sint32 fraction = (sint32)((num - integerPart) * 100);

    if (fraction > 0)
    {
        LCD_vid4BitWriteChar('.');

        if (fraction < 10)
        {
            LCD_vid4BitWriteChar('0');
        }

        if (fraction % 10 == 0)
        {
            LCD_vid4BitWriteInt(fraction / 10);
        }
        else
        {
            LCD_vid4BitWriteInt(fraction);
        }
    }
}
