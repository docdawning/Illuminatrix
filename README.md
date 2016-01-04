# Illuminatrix
Illuminatrix is a smart lighting system intended for use in 3D printing. By default, your printer will be lit dim-red when in "STANDBY", "GREEN" once an axis has been zeroed, pseudio-"WHITE" while printing, "YELLOW" when paused, "RED" if the print has failed, etc.

## Demo
[![Illuminatrix Demo](http://www.dawning.ca/wp-content/uploads/2016/01/IlluminatrixDemoGif.gif)](https://www.youtube.com/embed/iWDjNnod_Ak)
<BR /><i>Click the above GIF to see the detailed demo video on YouTube.</i>


## Software
Illuminatrix has two software components, an Octoprint Plugin and an Arduino firmware. 

## Hardware
Illuminatrix depends on a dedicated Arduino board to receive basic commands issued by the Octoprint plugin. Therefore you need an Arduino hooked-up to your Octoprint server. The PWM pins of the Arduino are used to drive your RGB LED(s). Small systems can have the RGB LED connected directly to the Arduino PWM pins, though it's best to use the PWM pins to instead drive some transistors to switch on/off power from a dedicated source.
