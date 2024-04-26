#include <string.h>

/* Global Variable Definitions */
const uint8_t smoothFactor = 100;
const uint8_t numOfSolars = 8;
const uint8_t updatePrev = 10;
const uint8_t solars[8] = {A7, A6, A5, A4, A8, A9, A13, A14};
uint32_t curSolarValues[8];
uint32_t curSolarValue = 0;
uint32_t prevSolarValue = 0;
uint8_t prevState = 0;
uint8_t updateCount = 0;

/* Initializations */
void setup() {
	Serial.begin(9600);
	P4DIR |= BIT0;
	P4OUT &= ~BIT0;
}

/* Execution Loop */
void loop() {
    /* add all sensor data together as a running sum, smoothFactor times */
    uint8_t i, j;
    for (i=0; i<numOfSolars; i++)
        curSolarValues[i] = 0;
    for(i=0; i<smoothFactor; i++) {
        for (j=0; j<numOfSolars; j++)
            curSolarValues[j] += analogRead(solars[j]);
    }
    /* average the sum based on the number of samples taken */
    for (i=0; i<numOfSolars; i++) {
        curSolarValues[i] /= smoothFactor;
//        Serial.print(" ");
//        Serial.print(curSolarValues[i]);
//        Serial.print(" ");
    }
//    Serial.println();
    for (i=0; i<numOfSolars; i++)
        curSolarValue += curSolarValues[i];
    curSolarValue /= numOfSolars;
    /* Current average X% less than previous average . . . */
    if(curSolarValue < (prevSolarValue * 0.95)) {
        /* prevState was decreasing . . . */
        if(!prevState) {
            /* fire the ultrasonic sensor */
            Serial.println("echo");
            P4OUT |= BIT0;
            delay(10);
            P4OUT &= ~BIT0;
        } else
            prevState = 0;  // set prevState = "decreasing"
    }
    /* Current average X% greater than previous average . . . */
    if(curSolarValue > (prevSolarValue * 1.05)) {
        /* prevState was increasing . . . */
        if(prevState) {
            /* fire the ultrasonic sensor */
            Serial.println("echo");
            P4OUT |= BIT0;
            delay(10);
            P4OUT &= ~BIT0;
        } else
            prevState = 1;  // set prevState = "increasing"
    }
    /* 4. If it has been "updatePrev" times since we last *
	 *	  updated the prevSolarValue, then update it.	  */
	if(updateCount >= updatePrev) {
		prevSolarValue = curSolarValue;
		updateCount = 0;
	}
	/* 5. Finally, print the current sensor average *
	 *	  and increment the updateCount variable.	*/
	Serial.println(curSolarValue);
	updateCount++;
}
