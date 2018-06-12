# esp8266
esp8266

For my CS49N final project, I programmed the ESP8266 WiFi module with the Raspberry Pi B+, and via a serial interface.
The first portion of the project consisted of the following:
 +Establish a serial connection to the ESP8266 module, to communicate "brute force", waiting for responeses from the module, encountered     many errors of the form: 
 +Troubleshoot the serial connection, 
  ++i.e. making sure the serial cable worked with other devices, ensured that the ESP8266 was responsive and functional
  ++modifying the baudrate over the serial connection, via tcsetattrb and tcgetattrb and the termios interface
 +Troubleshoot the connection to the serial cable, using linux terminal
  ++using sudo to open a file descriptor to the /dev/ttyUSB0 (for whatever reason the Ubuntu 16.04 LTS distro you cannot open a valid file    descriptor to the usb serial interface without being super user)
 +Most of the finalized code is in test.c
The second portion of the project (arguably the more difficult), was communicating with the Raspberry Pi B+ via the UART (TX/RX) communication channels to the ESP8266 module.
 +Note: It is crucial to establish a binary rendezvous between the Pi and the ESP8266 module such that you can read and write 
  without destroying the data packets that you are attempting to transmit or receive.
 +Error: A subtle detail to note: the default uart interface can be re-configured to both modify the baudrate and to change the way you interact with the tx/rx communication channels. 
 +Error: It is impossible to display the results from the Raspberry Pi and the ESP8266 communication, so it is necessary to construct some  way to display the values that you obtain (either via a display.c/.h definition and referring back to the Broadcomm specifications, or a more brute force way: via LEDs)
 +Note: Configuration of the gpio pins to display LEDs is crucial to success of the project, to verify the steps of the communication, else there is no way to know whether the Raspberry Pi can send further commands to the module.
 +Added functionality to the string library for the Raspberry Pi, i.e. functional utils: strstr(), strlen(), strncmp(), compare()
  in order to be able to conditionally test the return values from the Pi
 +Error: A large bug in the interface (see esp.c and esp.h) was fixed in the str.h implementation with the strstr() function, which causes buffer overflow and false positives when conditionally checking the return value from the ESP8266 module.
 
 
"AT"
"AT+CWMODE=1"
"AT+CWLAP" #list
"AT+CWJAP" #connect
"AT+CIFSR" #check IP
"AT+CIPMUX=1" #set connection mode
"AT+CIPSERVER=1,80" #open port
