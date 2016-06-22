#!/bin/bash
#
#
#

## Settings when correct:
#speed 9600 baud; rows 0; columns 0; line = 0;
#intr = ^C; quit = ^\; erase = ^?; kill = ^H; eof = ^D; eol = <undef>; eol2 = <undef>; swtch = <undef>; start = ^Q; stop = ^S; susp = ^Z;
#rprnt = ^R; werase = ^W; lnext = ^V; flush = ^O; min = 100; time = 2;
#-parenb -parodd cs8 -hupcl -cstopb cread clocal -crtscts
#-ignbrk brkint ignpar -parmrk -inpck -istrip -inlcr -igncr -icrnl ixon -ixoff -iuclc -ixany -imaxbel -iutf8
#-opost -olcuc -ocrnl -onlcr -onocr -onlret -ofill -ofdel nl0 cr0 tab0 bs0 vt0 ff0
#-isig -icanon iexten -echo echoe echok -echonl -noflsh -xcase -tostop -echoprt echoctl echoke


SERIAL_PORT=/dev/ttyUSB0
BAUD_RATE=9600

#stty -F $SERIAL_PORT cs8 $BAUD_RATE ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts

stty -F $SERIAL_PORT cs8 $BAUD_RATE min 100 time 2 -parenb -parodd cs8 -hupcl -cstopb cread clocal -crtscts -ignbrk brkint ignpar -parmrk -inpck -istrip -inlcr -igncr -icrnl ixon -ixoff -iuclc -ixany -imaxbel -iutf8 -opost -olcuc -ocrnl -onlcr -onocr -onlret -ofill -ofdel nl0 cr0 tab0 bs0 vt0 ff0 -isig -icanon iexten -echo echoe echok -echonl -noflsh -xcase -tostop -echoprt echoctl echoke
