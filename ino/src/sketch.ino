//**************************************************************//
//  Author: doc@dawning.ca
//**************************************************************//
using namespace std;
#include "LED.cpp"


//##################################################################
//## Main Class ####################################################
//##################################################################

#define l_R    3    //PWM pin for RED
#define l_G    5    //PWM pin for GREEN
#define l_B    6    //PWM pin for BLUE

#define BAUD_RATE	9600
#define NUMBER_OF_SPACES_BEFORE_PWM_IN_SET_CMD		2
#define NUMBER_OF_SPACES_BEFORE_STATUS_IN_SET_CMD	3
#define NUMBER_OF_SPACES_BEFORE_LED_NUMBER_IN_SET_CMD	1

//Function Prototypes////
void refreshLEDs();
void refreshLEDState(LED led);

//Globals////
LED LEDS[3];
String inputString;
boolean hypnoOrb;


//##################################################################
//## Init functions ################################################
//##################################################################
void refreshLEDs() {
	for(int i=0;i<3;i++) {
		refreshLEDState(LEDS[i]);
	}
}

//Arduino's firmware start of execution
void setup() {
	//Setup for each LED record
	LEDS[0].initialize(l_R, true, 16, 255, 96);
	LEDS[1].initialize(l_G, true, 0, 255, 200);
	LEDS[2].initialize(l_B, true, 0, 255, 180);

	Serial.begin(BAUD_RATE);
	hypnoOrb = false;

	Serial.println("Illuminatrix greets you.");
} //end setup


//##################################################################
//## Functions #####################################################
//##################################################################

void printLEDs() {
	for(int i=0;i<3;i++) {
		Serial.print("LED # ");
		Serial.print(i);
		Serial.print(", value: ");
		Serial.print(LEDS[i].getValue());
		Serial.print(", state: ");
		Serial.println(LEDS[i].activated);
	}
}

void refreshLEDState(LED led) {
	if (led.activated) analogWrite(led.pin, led.getValue());
	else analogWrite(led.pin, led.minPWM);
}

void setLEDs(boolean state){
	Serial.println("LED state changed");
	for (int i=0;i<3;i++) {
		LEDS[i].activated = state;
	}
}

char* findSpaceDelimitedSubstring(String input, int numberOfLeadingSpaces) {
	int start = 0;
	int end = 0;
	int spacesObserved = 0;

	//find the start of the substring
	for (int i=0;i<input.length();i++) {
		start++;
		if (input.charAt(i) == ' ') {
			spacesObserved++;
			if (spacesObserved >= numberOfLeadingSpaces) i = input.length();
		}
	}

	//find the end of the substring
	end=start;
	for (int i=start;i<input.length();i++) {
		if (input.charAt(i) == ' ') {
			i=input.length();
		} else {
			start++;
		}
	}
	char charBuf[input.length()];
	input.substring(start,end).toCharArray(charBuf, input.length());
	return charBuf;
}

void setLED(String input) {
	//SET LED# PWM-MOD ENABLE
	//"SET {0-2} {0-9} {0-1}"
	int mode = atoi(findSpaceDelimitedSubstring(input, NUMBER_OF_SPACES_BEFORE_PWM_IN_SET_CMD));
	int ledNumber = atoi(findSpaceDelimitedSubstring(input, NUMBER_OF_SPACES_BEFORE_LED_NUMBER_IN_SET_CMD));
	int status = atoi(findSpaceDelimitedSubstring(input, NUMBER_OF_SPACES_BEFORE_STATUS_IN_SET_CMD));
	LED* led = &LEDS[ledNumber];
	if (status > 0) led->enable();
	else led->disable();
	led->setValue(mode);

	Serial.print("Changed LED #");
	Serial.print(ledNumber);
	Serial.print(", with mode ");
	Serial.print(mode);
	Serial.print(", and status ");
	Serial.println(status);
}

void interpretInput(String input) {
	if (inputString.startsWith("ON")) setLEDs(true);
	if (inputString.startsWith("OFF")) setLEDs(false);
	if (inputString.startsWith("SET")) setLED(inputString);
	if (inputString.startsWith("CYCLEON")) hypnoOrb=true;
	if (inputString.startsWith("CYCLEOFF")) hypnoOrb=false;
	printLEDs();
}

void serviceInputIfNecessary() {
	char ch = ' ';

	if (Serial.available() > 0) {
		char ch = (char)Serial.read();
		inputString += ch;
		Serial.print(ch);
		if (ch == '\r' || ch == ';') {
			Serial.print('\n');
			interpretInput(inputString);
			inputString = "";
		}
	}
}

void serviceHypnoOrbIfNecessary() {

}

//Main
void loop() {
	refreshLEDs();
	serviceInputIfNecessary();
	serviceHypnoOrbIfNecessary();
	delay(10);
}
