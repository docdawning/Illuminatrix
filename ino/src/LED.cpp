#include <WString.h>
#include "Arduino.h"
class LED {
        public:
                int pin;
		String name;
                bool activated;
                int maxPWM;
                int minPWM;
                int currentValue;
		int targetValue;
		int cyclesPerTargetStep;
		int cyclesSinceTargetStep;
		int pwmDeltaForStep;

                void initialize(String colorName, int arduinoPin, bool enabled, int minP, int maxP, int val) {
                        if (enabled) enable();
                        else disable();
			pin = arduinoPin;
                        maxPWM = maxP;
                        minPWM = minP;
                        targetValue = 0;
			name = colorName;
			cyclesPerTargetStep = 30;
			cyclesSinceTargetStep = 0;
			pwmDeltaForStep = 1;
                }

                void setValue(int newValue) {
                        if (newValue > maxPWM) currentValue = maxPWM;
                        else if (newValue < minPWM) currentValue = minPWM;
                        else currentValue = newValue;
			targetValue = currentValue;
                }

		void setTarget(int target) {
			if (target < minPWM) targetValue = minPWM;
			else if (target > maxPWM) targetValue = maxPWM;
			else targetValue = target;
		}

		int getValue() {
			return currentValue;
		}

                void enable() {
                        activated = true;
                }

                void disable() {
                        activated = false;
                }

		void refreshLED() {
			/* factors
				activated
				maxPwm
				minPwm
				currentValue
				targetValue
			*/

			if (activated) {
				int target = currentValue;
				
				if (currentValue != targetValue) {
					//adjust target towards targetValue if is time, else tick
					if (cyclesSinceTargetStep >= cyclesPerTargetStep) {
						cyclesSinceTargetStep = 0;
					
						//alter target towards targetValue
						if (target < targetValue) {
							target = target + pwmDeltaForStep;
							if (target > maxPWM) target = maxPWM;
						} else if (target > targetValue) {
							target = target - pwmDeltaForStep;
							if (target < minPWM) target = minPWM;
						}
					} else {
						cyclesSinceTargetStep++;
					}
				}

				analogWrite(pin, target);
				currentValue = target;
			}	
			else {
				analogWrite(pin, 0);
			}
		}
};

