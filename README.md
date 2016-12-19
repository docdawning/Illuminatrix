# Illuminatrix
<a href="https://hackaday.io/project/9191-illuminatrix">Illuminatrix</a> is an epic stateful lighting system for 3D printers. For instance, your printer will be lit dim-red when in "STANDBY", "GREEN" once an axis has been zeroed, pseudo-"WHITE" while printing, "YELLOW" when paused, "RED" if the print has failed, etc. These are default settings and can be changed at runtime.

## Demo
<i>Click the GIF below to see the detailed demo video on YouTube.</i>
[![Illuminatrix Demo](http://www.dawning.ca/wp-content/uploads/2016/01/IlluminatrixDemoDemo.gif)](https://youtu.be/np1gUWAG9M8)

## Software
Illuminatrix has two software components:
<UL>
<LI>An Arduino firmware</LI>
<LI>An Octoprint plugin</LI> 
</UL>

## Software Setup
This process is a work in progress 
<OL>
<LI>Go to this location and select the latest zip: https://github.com/docdawning/Illuminatrix/tree/master/Illuminatrix-octoprint-releases</LI>
<LI>Right-click on the "RAW" button and select "Copy Link Address"</LI>
<LI>Open your Octoprint interface, enter your settings and go in to the Plugin Manager</LI>
<LI>In the Plugin Manager, click the "Get More..." button. Paste the copied zip address in to the "... From URL" field and click "Install"</LI>
</OL>

## Hardware
Illuminatrix depends on a dedicated Arduino board to receive basic commands issued by the Octoprint plugin. Therefore you need an Arduino hooked-up to your Octoprint server. The PWM pins (3, 5 and 6) of the Arduino are used to drive your RGB LED(s). Small systems can have a single RGB LED connected directly to the Arduino PWM pins, though it's best to use the PWM pins to instead drive some transistors to switch on/off power from a dedicated source.

## Hardware Setup
1. Get an Arduino, power & connect it to your octoprint server via USB/Serial.
2. Attach an RGB LED to the lowest numbered PWM output pins on the Arduino. Or drive 3 transistors as off/on switches via the PWM pins.
3. Position the RGB LED(s) where you want.
4. Flash the Arduino using the upload script in the ino directory. Pay attention to modify the serial port name and arduino type, if necessary. Be particularly careful if you happen to be using the same type of Arduino as your printer motherboard, you don't want to accidentally flash your printer motherboard instead of your Illuminatrix Arduino.

## Illuminatrix Arduino Firmware
### Command-set
Here is a non-exhaustive list of the lighting commands the Illuminatrix Arduino firmware command-set supports:
 * ON
 * OFF
 * RED
 * GREEN
 * BLUE
 * LIGHTBLUE
 * PURPLE
 * YELLOW
 * CYCLEON
 * CYCLEWHITE <i>(This is a white-baised colour cycle routine)</i>
 * CYCLERED <i>Pulsates red</i>
 * CYCLEGREEN
 * CYCLEBLUE
 * SET [led # (0-2)] [pwm value (0-255)] [on/off (0,1)] 

The SET command lets you manually specific an LED pin # (0-2, typically), a pwm value (0-255) and an enable flag; 0 or 1. For example "SET 2 255 1" sets LED pin 2 to full brightness and enables it.

Commands are delimited by ';' characters, or carrige returns. Thus, in the Illuminatrix Octoprint plugin, you could chain commands, if it suits you. For example, you could set an event to run "SET 0 128 1;SET 1 128 1;SET 2 255 1;". That would set LEDs #0 and #1 to half PWM and LED #2 to full PWM brightness.
