# TM1637-LED-Controller-with-NTP
Display the time (and more) on this 4-digit LED with just 2 wires - see video #94 at https://www.youtube.com/RalphBacon 

The Arduino IDE (version 1.6.8) pre-configured for the ESPDuino can be found here:
http://en.doit.am/espduino.php (293Mb so too large to store in my GitHub)

There are two libraries here: use the SevenSegment library with the NTPClock2 sketches (there's two, to be used together). Use the TM1637Display library with the TM1637_4_digit_LED.ino example sketch.

Finally a follow up to video #43 in which I describe how multiplexing in 7-segment LEDs work. I was supposed to continue that with this video, oh well, a year late is better than not doing it at all!

Just to add interest we discuss how to get the time from the internet (not so trivial or reliable) using a Network Time Protocol (NTP) server. We've covered this before in video #75 (using an Arduino Ethernet shield) but here we use a  much more powerful µController, the ESP8266-13E as used in the EspDuino board, an UNO-sized replacement (more or less).

You can download a version of the Arduino IDE with it all configured and ready to go for an ESPDuino using the links below NO FURTHER CONFIGURATION REQUIRED - this can be used in parallel with your existing Arduino IDE.

All the sketches are included too, as well as copies of the libraries I've used (these have an irritating habit of either disappearing or being changed so they no longer work with some sketches, so at least you have the identical library that I used in my sketch and therefore you will know the sketch will run correctly!)


LINKS
==
Here's a link to the ESPDuino board (no, I don't get commission!) and even better, it includes a link to the special version of the Arduino IDE with instructions.  
https://www.banggood.com/ESPDuino-Development-Board-ESP-13-WiFi-UNO-R3-from-ESP8266-p-1023370.html 

---

If you like this video please give it a thumbs up, share it and if you're not already subscribed please do so :)

My channel is here:
------------------------------------------------------------------
https://www.youtube.com/c/RalphBacon
------------------------------------------------------------------ 
How can I remember this? Memory tip: "See" Ralph Bacon, geddit?
[You can also use this link: https://www.youtube.com/RalphBacon]
