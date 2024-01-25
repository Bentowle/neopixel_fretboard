#include <Adafruit_NeoPixel.h>

#define BUTTON_PIN   2
#define PIEZO_PIN    A0
#define LED_PIN      6
#define LED_COUNT    12

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int currentColor = 0;

void setup() {
    strip.begin();
    strip.show();
    pinMode(BUTTON_PIN, INPUT_PULLUP); // Configure the button pin as an input
}

void loop() {
    int piezoValue = analogRead(PIEZO_PIN);
    int ledLevel = map(piezoValue, 0, 1023, 0, LED_COUNT);

    // Check if the button has been pressed
    if (digitalRead(BUTTON_PIN) == LOW) {
        currentColor = (currentColor + 1) % 11; // Increment the color and wrap around at 11
        delay(200); // Debounce delay
    }

    uint32_t color;

    // Set the color based on the currentColor variable
    switch (currentColor) {
        case 0: color = strip.Color(255, 0, 0); break; // Red
        case 1: color = strip.Color(255, 165, 0); break; // Orange
        case 2: color = strip.Color(255, 255, 0); break; // Yellow
        case 3: color = strip.Color(0, 255, 0); break; // Green
        case 4: color = strip.Color(0, 255, 255); break; // Cyan
        case 5: color = strip.Color(0, 0, 255); break; // Blue
        case 6: color = strip.Color(128, 0, 128); break; // Purple
        case 7: color = strip.Color(255, 0, 255); break; // Magenta
        case 8: color = strip.Color(255, 105, 180); break; // Pink
        case 9: color = strip.Color(255, 255, 255); break; // White
        case 10: color = strip.Color(0, 0, 0); break; // Off
    }

    for(int i=0; i<LED_COUNT; i++) {
        if(i < ledLevel) {
            strip.setPixelColor(i, color);
        } else {
            strip.setPixelColor(i, strip.Color(0, 0, 0)); // Off
        }
    }

    strip.show();
}