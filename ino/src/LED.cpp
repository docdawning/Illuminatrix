#include <WString.h>
class LED {
        public:
                int pin;
		String name;
                bool activated;
                int maxPWM;
                int minPWM;
                int currentValue;

                void initialize(String colorName, int arduinoPin, bool enabled, int minP, int maxP, int val) {
                        if (enabled) enable();
                        else disable();
			pin = arduinoPin;
                        maxPWM = maxP;
                        minPWM = minP;
                        currentValue = val;
			name = colorName;
                }

                void setValue(int newValue) {
                        if (newValue > maxPWM) currentValue = maxPWM;
                        else if (newValue < minPWM) currentValue = minPWM;
                        else currentValue = newValue;
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
};

