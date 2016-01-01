class LED {
        public:
                int pin;
                bool activated;
                int maxPWM;
                int minPWM;
                int currentValue;

                void initialize(int arduinoPin, bool enabled, int minP, int maxP, int val) {
                        if (enabled) enable();
                        else disable();
			pin = arduinoPin;
                        maxPWM = maxP;
                        minPWM = minP;
                        currentValue = val;
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

