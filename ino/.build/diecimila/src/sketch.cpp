#include <Arduino.h>
#include "LED.cpp"
void refreshLEDs();
void setup();
void printLEDs();
void refreshLEDState(LED led);
void setLEDs(boolean state);
void setLED(String input);
void interpretInput(String input);
void handleInputIfNecessary();
void loop();
#line 1 "src/sketch.ino"
//**************************************************************//
//  Author: doc@dawning.ca
//**************************************************************//
using namespace std;
//#include "LED.cpp"

//##################################################################
//## Main Class ####################################################
//##################################################################


#define l_R    3    //PWM pin for RED
#define l_G    5    //PWM pin for GREEN
#define l_B    6    //PWM pin for BLUE
#define PWM_MAX	255
#define PWM_MIN 255	

#define BAUD_RATE	9600
#define CMD_BUF_LEN	8

#define DELAY_MOD_MULTIPLIER	250

//Function Prototypes////
void refreshLEDs();
void refreshLEDState(LED led);

//Globals////
int delayModifier;
LED LEDS[3];
String inputString;

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
	//setup PWM pins for output mode 
	pinMode(l_R, OUTPUT);
	pinMode(l_G, OUTPUT);
	pinMode(l_B, OUTPUT);

	//Setup for each LED record
	//L[X] = {pin, on/off, max, min, value}
	//LEDS[0] = {l_R, false, 255, 0, 200};
	//LEDS[1] = {l_G, false, 255, 0, 200};
	//LEDS[2] = {l_B, true, 255, 0, 255};
	//boolean enable, int minP, int maxP, int val) {
	LEDS[0].initialize(l_R, true, 0, 255, 96);
	LEDS[1].initialize(l_G, true, 0, 255, 200);
	LEDS[2].initialize(l_B, true, 0, 255, 180);

	delayModifier = 7;
	Serial.begin(BAUD_RATE);

	refreshLEDs();

	Serial.println("Hello world");
} //end setup


//##################################################################
//## Functions #####################################################
//##################################################################

void printLEDs() {
	for(int i=0;i<3;i++) {
		Serial.print("LED # ");
		Serial.print(i);
		Serial.print(" ");
		Serial.print(LEDS[i].currentValue);
		Serial.print(" ");
		Serial.println(LEDS[i].activated);
	}
}

void refreshLEDState(LED led) {
	if (led.activated) analogWrite(led.pin, led.currentValue);
	else analogWrite(led.pin, 0);
}

void setLEDs(boolean state){
	Serial.println("LED state changed");
	for (int i=0;i<3;i++) {
		LEDS[i].activated = state;
	}
}

void setLED(String input) {
	//SET LED# PWM-MOD ENABLE
	//"SET {0-2} {0-9} {0-1}"
	Serial.println(input);
	int led = input.charAt(4);
	int mod = 28*(int)input.charAt(6);
	if (input.charAt(8) == '1') LEDS[led].activated = true;
	else LEDS[led].activated = false;  
	LEDS[led].setValue(mod);

	Serial.print("Changing LED #");
	Serial.print(input[4]);
	Serial.print(", with modifier ");
	Serial.print(input[6]);
	Serial.print(", and state ");
	Serial.println(input[8]);
}

void interpretInput(String input) {
	if (inputString.startsWith("ON")) setLEDs(true);
	if (inputString.startsWith("OFF")) setLEDs(false);
	if (inputString.startsWith("SET")) setLED(inputString);

	printLEDs();
}

void handleInputIfNecessary() {
	char ch = ' ';

	if (Serial.available() > 0) {
		char ch = (char)Serial.read();
		inputString += ch;
		if (ch == '\r' || ch == ';') {
			interpretInput(inputString);
			inputString = "";
		}
	}
}


//Main
void loop() {
	refreshLEDs();
	handleInputIfNecessary();
	delay(250);
}
