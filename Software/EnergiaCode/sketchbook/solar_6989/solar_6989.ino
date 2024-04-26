#include <string.h>

/* NOTE: You are currently using orange-orange-red-gold resistors as a 		*
 *		 voltage divider on the solar cells. Maybe try a smaller one.		*/
/****************************************************************************/
/* Global Variable Definitions												*/
/****************************************************************************/
const uint8_t numOfSensors = 4;
const uint8_t smoothFactor = 100;
const uint8_t solar0 = A4;			// P8.7
const uint8_t solar1 = A5;			// P8.6
const uint8_t solar2 = A6;			// P8.5
const uint8_t solar3 = A7;			// P8.4
const uint8_t updatePrev = 10;
uint8_t prevState = 0;				// 0 = decreasing, 1 = increasing
uint8_t updateCount = 0;
uint16_t prevSensorValue = 0;

/****************************************************************************/
/* Initializations 															*/
/****************************************************************************/
void setup() {
	Serial.begin(9600);
	P9DIR |= BIT0;
	P9OUT &= ~BIT0;
}

/****************************************************************************/
/* Execution Loop 	 														*/
/****************************************************************************/
void loop() {

	/* 1. Read from the sensors and add this to the running sum *
	 *	  "curSensorValue". Repeat this "smoothFacter" times.	*/
	uint8_t i;
	uint32_t curSensorValue = 0;
	for(i = 0; i < smoothFactor; i++) {
		curSensorValue += analogRead(solar0);
		curSensorValue += analogRead(solar1);
		curSensorValue += analogRead(solar2);
		curSensorValue += analogRead(solar3);
	}

	/* 2. Average the sum based on the number of samples *
	 *	  taken for each sensor. 						 */
	curSensorValue /= (smoothFactor * numOfSensors);

	/* 3a. If the current average is less than X% of  *
	 *	   the previous average...					  */
	if(curSensorValue < (prevSensorValue * 0.93)) {
		/* ... and the previous state was decreasing, *
		 * then trigger the ultrasonic sensor.		  */
		if(!prevState) {
			Serial.println("read");
			P9OUT |= BIT0;
			delay(10);
			P9OUT &= ~BIT0;
		}
		/* Otherwise, set the previous state as decreasing. */
		else {
			prevState = 0;
		}
	}
	/* 3b. If the current averagte is greater than *
	 *	   Y% of the previous average... 		   */
	if(curSensorValue > (prevSensorValue * 1.07)) {
		/* ... and the previous state was increasing, *
		 * then trigger the ultrasonic sensor.		  */
		if(prevState) {
			Serial.println("echo");
			P9OUT |= BIT0;
			delay(10);
			P9OUT &= ~BIT0;
		}
		/* Otherwise, set the previous state as increasing. */
		else {
			prevState = 1;
		}
	}

	/* 4. If it has been "updatePrev" times since we last *
	 *	  updated the prevSensorValue, then update it.	  */
	if(updateCount >= updatePrev) {
		prevSensorValue = curSensorValue;
		updateCount = 0;
	}

	/* 5. Finally, print the current sensor average *
	 *	  and increment the updateCount variable.	*/
	Serial.println(curSensorValue);
	updateCount++;
}
