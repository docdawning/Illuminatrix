# Illuminatrix
Illuminatrix is a smart lighting system intended for use in 3D printing. By default, your printer will be lit dim-red when in "STANDBY", "GREEN" once an axis has been zeroed, pseudio-"WHITE" while printing, "YELLOW" when paused, "RED" if the print has failed, etc.

## Demo
<iframe width="560" height="315" src="https://www.youtube.com/embed/iWDjNnod_Ak" frameborder="0" allowfullscreen></iframe>

## Software
Illuminatrix has two software components, an Octoprint Plugin and an Arduino firmware. 

## Hardware
Illuminatrix depends on a dedicated Arduino board to receive basic commands issued by the Octoprint plugin. Therefore you need an Arduino hooked-up to your Octoprint server. The PWM pins of the Arduino are used to drive your RGB LED(s). Small systems can have the RGB LED connected directly to the Arduino PWM pins, though it's best to use the PWM pins to instead drive some transistors to switch on/off power from a dedicated source.
