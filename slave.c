/*
 * slave.c
 *
 *  Created on: Feb 12, 2020
 *      Author: Almalky
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
	/*Configure RS signal as an output*/
		Dio_vidSetPinDirection(Dio_PORTC, 0, Dio_Output);

		/*Configure R\W signal as an output*/
		Dio_vidSetPinDirection(Dio_PORTC, 1, Dio_Output);

		/*Configure Enable signal as an output*/
		Dio_vidSetPinDirection(Dio_PORTC, 2, Dio_Output);

		/*Configure Data-Port to output*/
		Dio_vidSetPortDirection(Dio_PORTD, Dio_Output);


		I2C_init();
		LCD_vidInit();
		I2C_SLAVE_Init(Slave_Write_Address);

		while (I2C_Slave_listen_READ()!=0);
		_delay_ms(3000);
		uint32_t u32Temperature = I2C_SLAVE_READ();

		LCD_vidGoTo(0,1);
		LCD_vidWriteString("Temperature:");
		LCD_vidPrintNumber(u32Temperature);


}



