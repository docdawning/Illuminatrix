# Illuminatrix
Illuminatrix is a stateful lighting system for 3D printers. For instance, your printer will be lit dim-red when in "STANDBY", "GREEN" once an axis has been zeroed, pseudo-"WHITE" while printing, "YELLOW" when paused, "RED" if the print has failed, etc. Obviously these are default settings.

## Demo
<i>Click the below GIF to see the detailed demo video on YouTube.</i>
[![Illuminatrix Demo](http://www.dawning.ca/wp-content/uploads/2016/01/IlluminatrixDemoDemo.gif)](https://www.youtube.com/embed/iWDjNnod_Ak)

## Software
Illuminatrix has two software components, an Octoprint Plugin and an Arduino firmware. 

## Hardware
Illuminatrix depends on a dedicated Arduino board to receive basic commands issued by the Octoprint plugin. Therefore you need an Arduino hooked-up to your Octoprint server. The PWM pins of the Arduino are used to drive your RGB LED(s). Small systems can have the RGB LED connected directly to the Arduino PWM pins, though it's best to use the PWM pins to instead drive some transistors to switch on/off power from a dedicated source.

## Hardware Setup
1. Get an Arduino, power & connect it to your octoprint server via USB.
2. Attach an RGB LED to the lowest numbered PWM output pins on the Ardino. Or drive 3 transistors as off/on switches via the PWM pins.
3. Position the RGB LED(s) where you want.
4. Flash the Arduino using the upload script in the ino directory. Pay attention to modify the serial port name and arduino type, if necessary. Be particularly careful if you happen to be using the same type of Arduino as your printer motherboard, you don't want to accidentally flash your printer motherboard instead of your Illuminatrix Arduino.

## Octoprint Plugin Installation
Copy/link the plugin directory to your Octoprint plugin directory.

## Illuminatrix Arduino Firmware
### Command-set
Here is a non-exhaustive list of the lighting commands the Illuminatrix Arduino firmware command-set supports:
 * ON
 * OFF
 * RED
 * GREEN
 * BLUE
 * PURPLE
 * YELLOW
 * CYCLEON
 * CYCLEWHITE <i>(This is a white-baised colour cycle routine)</i>
 * SET [led #] [pwm value] [0|1] 

The SET command lets you manually specific an LED pin # (0-2, typically), a pwm value (0-255) and an enable flag; 0 or 1. For example "SET 2 255 1" sets LED pin 2 to full brightness and enables it.

Commands are delimited by ';' characters, or carrige returns. Thus, in the Illuminatrix Octoprint plugin, you could chain commands, if it suits you. For example, you could set an event to run "SET 0 128 1;SET 1 128 1;SET 2 255 1;". That would set LEDs #0 and #1 to half PWM and LED #2 to full.
