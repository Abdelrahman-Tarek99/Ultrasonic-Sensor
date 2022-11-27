/******************************************************************************
 *
 * Module: project4
 *
 * File Name: project4.c
 *
 * Description: Source file for the project4 driver
 *
 * Author: Abdelrahman Tarek
 *
 *******************************************************************************/
#include "lcd.h"
#include "ultrasonic.h"
#include <avr/io.h>
int main(void) {
	Ultrasonic_init(); /* Intializing the UltraSonic*/
	LCD_init();/* Intializing the LCD*/
	LCD_displayString("Distance=     cm"); /*Diplaying On the LCD */
	SREG |= (1 << 7); /* Enabling the Intrupts*/
	uint32 Distance; /* Variable to Store the Calculated distance to show on Screen */
	while (1) {
		LCD_moveCursor(0, 10); /* Moving Cursor to Show the Distance value at the same place everytime */
		Distance = Ultrasonic_readDistance(); /*Start sending the ultrasonic signal  */
		if (Distance >=427) {
			LCD_intgerToString(Distance); /*Displaying zero out of the range of ultrasonic sensor
			as the sensor reading isn't accurate any more */
			LCD_displayString("   ");
			LCD_moveCursor(1, 0);
			LCD_displayString("OUT OF RANGE!!!!");
		} else if (Distance < 10) {
			LCD_intgerToString(Distance); /*Displaying the Distance */
			LCD_displayString("  ");
			LCD_moveCursor(1, 0);
			LCD_displayString("                ");
		} else if (Distance < 100) {
			LCD_intgerToString(Distance); /*Displaying the Distance */
			LCD_displayString(" ");
			LCD_moveCursor(1, 0);
			LCD_displayString("                ");
		} else {
			LCD_intgerToString(Distance); /*Displaying the Distance */
			LCD_moveCursor(1, 0);
			LCD_displayString("                ");
		}
	}
}

