/******************************************************************************
 *
 * Module: ultrasonic
 *
 * File Name: ultrasonic.h
 *
 * Description: Source file for the ultrasonic driver
 *
 * Author: Abdelrahman Tarek
 *
 *******************************************************************************/
#include "icu.h"
#include "ultrasonic.h"
#include "gpio.h"
#include <util/delay.h>
/******************************************************************************
 * 1- Microcontroller needs to transmit at least 10 us trigger pulse to the HC-SR04 Trig Pin.
 * 2- After getting a trigger pulse, HC-SR04 automatically sends eight 40 kHz sound waves
 * and the microcontroller waits for rising edge output at the Echo pin.
 * 3- When the rising edge capture occurs at the Echo pin which is connected to an input of ATmega32,
 *  start Timer of ATmega16 and again wait for a falling edge on the Echo pin.
 * 4- As soon as the falling edge is captured at the Echo pin, the microcontroller reads the count of the Timer.
 *  This time count is used to calculate the distance to an object.
 *******************************************************************************/
uint32 distance = 0; /* to store the calculated value*/
uint8 counter = 0;/* to count the falling edge = (count=1)
 & the rising edge (means that the trigger has echo is recived ) (count=0)*/
uint32 Time_Capture = 0; /* to store the time captured from the icu "Echo" */

void Ultrasonic_init(void) {
	Icu_ConfigType Icu_ConfigType = { F_CPU_8, RISING }; /*Configuring the ICU with CPU/8 & Rising Edge */
	Icu_init(&Icu_ConfigType);/*Intializing the ICU */
	Icu_setCallBack(Ultrasonic_edgeProcessing);/*Intializing the ICU call back Fuinction to
	 point on Ultrasonic_edgeProcessing Function  */
	GPIO_setupPinDirection(ULTRA_TRIGGER_PORT_ID, ULTRA_TRIGGER_PIN_ID,
			PIN_OUTPUT); /* Setup the pin of th ultasonic pin PB5 to be output pin  */
}
void Ultrasonic_Trigger(void) {
	GPIO_writePin(ULTRA_TRIGGER_PORT_ID, ULTRA_TRIGGER_PIN_ID, LOGIC_HIGH);/* Sending the trigger pulse from the ultrasonic*/
	_delay_us(10); /* delay <10ms*/
	GPIO_writePin(ULTRA_TRIGGER_PORT_ID, ULTRA_TRIGGER_PIN_ID, LOGIC_LOW); /* reseting the ultrasonic to start again when recalling it again */
}
uint32 Ultrasonic_readDistance(void) {
	Ultrasonic_Trigger();/* Start sending the trigger pulse */

	distance = (uint32) ((float32) Time_Capture / 57.5);/* calculating the distance*/
	return distance;

}
void Ultrasonic_edgeProcessing(void) {
	counter++; /*incrementing the counter to be at First: Falling Edge Then to be Rising edge */
	if (counter == 1) {
		Icu_clearTimerValue(); //clear the timer
		Icu_setEdgeDetectionType(FALLING);

	} else if (counter == 2) {
		Time_Capture = Icu_getInputCaptureValue();
		Icu_setEdgeDetectionType(RISING);
		counter = 0;
	}
}
