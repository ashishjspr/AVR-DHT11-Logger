#define F_CPU 16000000UL

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>

#include "dht.h"
#include "LCD16x2_4bit.h"

int main(void)
{
	lcdinit();
	lcd_clear();

	char printbuff[8];

	int8_t temperature = 0;
	int8_t humidity = 0;
	int address=0;
	DDRA = 0x00;    //Set port a as input
	PORTA=0xFF;

	while (1)
	{
		//=====================================Logging Onto EEPROM

		if (PINA == 0xFE) //If switch PA0 is pressed(grounded)
		{
			
			if (address<4096)
			{


		if (dht_gettemperaturehumidity(&temperature, &humidity) != -1)
		{
			lcd_clear();
			dtostrf(temperature, 3, 2, printbuff);
			lcd_gotoxy(0,0);	lcd_print("Temp");
			lcd_gotoxy(9,0);	lcd_print(printbuff);
			lcd_gotoxy(13,0);	lcd_print("C");
			eeprom_write_byte((const uint8_t *)address,temperature);
			address++;

			dtostrf(humidity, 3, 2, printbuff);
			lcd_gotoxy(0,1);	lcd_print("Humidity");
			lcd_gotoxy(9,1);	lcd_print(printbuff);
			lcd_gotoxy(13,1);	lcd_print("%RH");
			eeprom_write_byte((const uint8_t *)address,humidity);
			address++;
		}
		else
		{
			lcd_clear();
			lcd_gotoxy(0,0);	lcd_print("DHT is not connected");
		}
			}
	}	
	
	
	//==========================================Retrieval On LCD
	
	if (PINA == 0xFD) //If switch PA1 is pressed(grounded)
	{
		if(address >= 0)
		{
			lcd_clear();
			
			address--;
			humidity=eeprom_read_byte((const uint8_t *)address);
			dtostrf(humidity, 3, 2, printbuff);
			lcd_gotoxy(0,1);	lcd_print("Humidity");
			lcd_gotoxy(9,1);	lcd_print(printbuff);
			lcd_gotoxy(13,1);	lcd_print("%RH");
			
			address--;
			temperature=eeprom_read_byte((const uint8_t *)address);
			dtostrf(temperature, 3, 2, printbuff);
			lcd_gotoxy(0,0);	lcd_print("Temp");
			lcd_gotoxy(9,0);	lcd_print(printbuff);
			lcd_gotoxy(13,0);	lcd_print("C");
			
		}
	
		_delay_ms(2000);
	}
	}	
	return 0;
}