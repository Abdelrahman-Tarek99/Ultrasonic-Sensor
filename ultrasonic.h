 /******************************************************************************
 *
 * Module: ultrasonic
 *
 * File Name: ultrasonic.h
 *
 * Description: Header file for the ultrasonic driver
 *
 * Author: Abdelrahman Tarek
 *
 *******************************************************************************/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ULTRA_TRIGGER_PORT_ID                   PORTB_ID
#define ULTRA_TRIGGER_PIN_ID                    PIN5_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void Ultrasonic_init(void);
void Ultrasonic_Trigger(void);
uint32 Ultrasonic_readDistance(void);
void Ultrasonic_edgeProcessing(void);




#endif /* ULTRASONIC_H_ */
