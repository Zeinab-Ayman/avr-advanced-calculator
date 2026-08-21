/*
 * KPD_Prog.c
 *
 *  Created on: Aug 16, 2026
 *      Author: Zeinab
 */

#include"../../Serv/BIT_MATH.h"
#include"../../Serv/STD_TYPES.h"
#include"../../MCAL/DIO/DIO_Init.h"
#include <util/delay.h>
#include"KPD_Init.h"
#include"KPD_Config.h"

void Init_KPD(){
	uint8 i;
	for(i=0;i<NoRows;i++){
		DIO_vidSetPinDir(rowPins[i],INPUT_PIN);
		DIO_vidSetPinVal(rowPins[i],HIGH_PIN);
	}
	for(i=0;i<NoCols;i++){
		DIO_vidSetPinDir(colPins[i],OUTPUT_PIN);
		DIO_vidSetPinVal(colPins[i],HIGH_PIN);
	}
}

uint8 KPD_u8GetPressedKey(){
	uint8 u8PinState = HIGH_PIN;
	uint8 u8KPDPressedKey  = 0;
	uint8 i,j;
	for(i=0;i<NoCols;i++){
		DIO_vidSetPinVal(colPins[i],LOW_PIN);
		for(j=0;j<NoRows;j++){
			u8PinState = DIO_u8GetPinVal(rowPins[j]);
			if(u8PinState == LOW_PIN){
				while (DIO_u8GetPinVal(rowPins[j]) == LOW_PIN);
				_delay_ms(20);
				u8KPDPressedKey = KPDPattern[j][i];
				DIO_vidSetPinVal(colPins[i],HIGH_PIN);
				return u8KPDPressedKey;
			}
		}
		DIO_vidSetPinVal(colPins[i],HIGH_PIN);
	}
	return u8KPDPressedKey;
}

