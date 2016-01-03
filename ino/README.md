Here are the arduino components for Illuminatrix.

This is to be used entirely from the Linux command line. Use/adapt the build script to compile for your Ardino. Note you may need change the serial port (/dev/ttyUSB0 here). Also the Arduino machine type could be commonly adjusted. Further, you may want to edit the PWM pins used in the sketch.

Note that typically when firing commands at your Arduino, it'll just reset the firmware, which sucks for this application.

You can setup the serial port sufficiently between reboots by using `screen /dev/ttyUSB0` (then close screen). I'll find a better solution soon, I hope.
