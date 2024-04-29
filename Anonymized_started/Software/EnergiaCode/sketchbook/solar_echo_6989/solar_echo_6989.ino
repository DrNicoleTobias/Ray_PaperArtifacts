#include <string.h>
#define trigPin 32				// Trigger pin to echo sensor
#define echoPin 33				// Output pin from echo sensor

/* Global Variable Definitions */
const uint8_t smoothSolarFactor = 100;
const uint8_t numOfSolars = 8;
const uint8_t updatePrev = 10;
const uint8_t solars[8] = {A7, A6, A5, A4, A8, A9, A13, A14};
uint32_t curSolarValues[8];
uint32_t curSolarValue = 0;
uint32_t prevSolarValue = 0;
uint8_t prevState = 0;					// 0 = decreasing, 1 = increasing
uint8_t updateCount = 0;
float percentSolarChange = 0.06;		// difference to detect with solar cells
double sensorHeight;

/* Initializations */
void setup() {
	Serial.begin(9600);
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
	sensorHeight = 83.5;			// height of echo sensor from floor (inches)
}

/* Execution Loop */
void loop() {
	uint8_t i, j;
	// Clear any existing solar values.
	for (i=0; i<numOfSolars; i++) {
		curSolarValues[i] = 0;
	}
	// Take data for each solar cell, smoothSolarFactor times.
	for(i=0; i<smoothSolarFactor; i++) {
		for (j=0; j<numOfSolars; j++) {
			curSolarValues[j] += analogRead(solars[j]);
		}
	}
	// Smooth the solar data.
	for (i=0; i<numOfSolars; i++) {
		curSolarValues[i] /= smoothSolarFactor;
	}
	// Add all solar data.
	for (i=0; i<numOfSolars; i++) {
		curSolarValue += curSolarValues[i];
	}
	// Average solar data.
	curSolarValue /= numOfSolars;
	// Current average is percentSolarChange less than previous average . . .
	if(curSolarValue < (prevSolarValue * (1.0 - percentSolarChange))) {
		// prevState was decreasing . . .
		if(!prevState) {
			fireEchoSensor();
		} else {
			prevState = 0;
		}
	}
	// Current average is percentSolarChange greater than previous average . . .
	if(curSolarValue > (prevSolarValue * (1.0 + percentSolarChange))) {
		// prevState was increasing . . .
		if(prevState) {
			fireEchoSensor();
		} else {
			prevState = 1;
		}
	}
	// Update prevSolarValue if it has been updatePrev times since last update.
	if(updateCount >= updatePrev) {
		prevSolarValue = curSolarValue;
		updateCount = 0;
	}
	// Print the current sensor average and increment the updateCount variable.
	Serial.println(curSolarValue);
	updateCount++;
}

void fireEchoSensor() {
	Serial.println("echo");
	digitalWrite(trigPin, LOW);
	delayMicroseconds(5);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);

	double distance;
	distance = pulseIn(echoPin, HIGH);
	distance *= 0.0001657;		// convert pulse width to meters
	distance *= 39.3701;			// convert meters to inches

	Serial.println();
	Serial.print(sensorHeight-distance);
	Serial.println(" in");
	Serial.println();
	delay(50);
}
