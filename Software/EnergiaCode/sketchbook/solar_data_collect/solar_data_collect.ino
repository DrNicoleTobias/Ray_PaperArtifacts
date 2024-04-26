/* Global Variable Definitions */
const uint8_t smoothSolarFactor = 100;
const uint8_t numOfSolars = 8;
const uint8_t solars[8] = {A7, A6, A5, A4, A8, A9, A13, A14};
uint32_t curSolarValues[8];

/* Initializations */
void setup() {
	Serial.begin(9600);
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
	// Smooth the solar data and print the data.
	for (i=0; i<numOfSolars; i++) {
		curSolarValues[i] /= smoothSolarFactor;
		Serial.print(curSolarValues[i]);
		if(i<numOfSolars-1) Serial.print(" ");
	}
	Serial.println();
}
