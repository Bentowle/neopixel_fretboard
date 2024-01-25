# neopixel_fretboard
Arduino code to control neopixels embedded in the fret board using a piezo and a audio input 
a simple normally open buttonchanges color/modes . mode changes after cycling thru color options. 
4 files included.  1 mode, 2 modes, 3 mode and 4 modes. 
mode 1 leds react like a vu meter
mode 2 all leds on a single color, oppsing color acts as vu meter. 
mode 3 all leds are a single color. 
mode 4 color wave fade.

pin 6 is neopixel data . 
pin 2 is button, use normally open button, connect one leg to ground. 
a0 is the input for the piezo . 

led count is 12  based on normal fret markers for 24 fret  guitar/bass including 1st fret. 
led count can be changed to what every you want code will scale to it. 
