/*

 * main.c
 *
 *  Created on: Feb 12, 2020
 *      Author:Mohamed Mahmoud ALMALKY
 *
 */

#include "avr/delay.h"
#include "HAL/LCD/Inc/LCD.h"
#include "MCAL/ADC/Inc/ADc.h"
#include "MCAL/ADC/Inc/ADc.h"
#include "MCAL/DIO/Inc/Dio.h"
#include "MCAL/I2c/inc/i2c.h"

#define Slave_Write_Address		0x20
#define Slave_Read_Address		0x21

void main (void)
{

	I2C_init();

	Dio_vidSetPinDirection(Dio_PORTA,0,Dio_Input);
	ADC_vidInit();
	uint16_t u16Digital;
	uint32_t u32Volts;
	uint32_t u32Temperature;

	while(1){
		_delay_ms(5);
		u16Digital = ADC_u16ReadChannel(1);

		u32Volts = ((uint32_t)u16Digital * 5000) / 1024;
		u32Temperature = u32Volts / 10;


		I2C_START();
		I2C_WRITE_address(Slave_Write_Address);
		_delay_ms(100);

		I2C_MASTER_WRITE((uint8_t)u32Temperature);
		_delay_ms(50);
		I2C_STOP();
	}


}

