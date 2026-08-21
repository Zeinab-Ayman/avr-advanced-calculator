/*
 * KPD_Config.c
 *
 *  Created on: Aug 16, 2026
 *      Author: Zeinab
 */


#include "../../Serv/STD_TYPES.h"
#include "../../MCAL/DIO/dio_init.h"
#include "KPD_Config.h"


uint8 KPDPattern[NoRows][NoCols]={{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'C','0','=','+'}};

uint8 rowPins[NoRows]={PB4,PB5,PB6,PB7};
uint8 colPins[NoCols]={PD4,PD5,PD6,PD7};
