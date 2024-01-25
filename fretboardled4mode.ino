#include <Adafruit_NeoPixel.h>

#define BUTTON_PIN   2
#define LED_PIN      6
#define LED_COUNT   12
#define SOUND_PIN   A0

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int mode = 0;
int currentColor = 0;
int ledLevel = 0;
float scalingFactor = 0.5; // Adjust this value to change the sensitivity

void setup() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
}

void loop() {
    int soundLevel = analogRead(SOUND_PIN);
    ledLevel = map(soundLevel * scalingFactor, 0, 1023, 0, LED_COUNT);

    if (digitalRead(BUTTON_PIN) == LOW) {
        if (mode != 3) {
            currentColor = (currentColor + 1) % 11; // Increment the color and wrap around at 11
            if (currentColor == 0) {
                mode = (mode + 1) % 5; // Switch mode when we cycle through all colors, now with 5 modes
            }
        } else {
            mode = (mode + 1) % 5; // Switch mode when we cycle through all colors, now with 5 modes
        }
        delay(200); // Debounce delay
    }

    uint32_t color;
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
        if(mode == 0) {
            if(i < ledLevel) {
                strip.setPixelColor(i, color);
            } else {
                strip.setPixelColor(i, strip.Color(0, 0, 0)); // Off
            }
        } else if(mode == 1) {
            strip.setPixelColor(i, color); // All LEDs on
            if(i == ledLevel) {
                strip.setPixelColor(i, invertColor(color)); // Volume LED in contrasting color
            }
        } else if(mode == 2) {
            strip.setPixelColor(i, color); // All LEDs on, no sound level
        } else if(mode == 3) {
            unsigned long time = millis(); // Get the current time in milliseconds
            int hue = (i * 192 + time / 50) % 192; // Calculate hue for color wave, using 75% of the hues
            uint32_t waveColor = strip.ColorHSV(hue * 49152 / 192); // Convert hue to RGB color, limiting the hue range to 75%
            strip.setPixelColor(i, waveColor);
            strip.show();
            delay(50); // Add a delay to create a wave effect
        }
    }

    if(mode != 3) {
        strip.show();
    }
}

uint32_t invertColor(uint32_t color) {
    uint8_t r = (uint8_t)(color >> 16);
    uint8_t g = (uint8_t)(color >>  8);
    uint8_t b = (uint8_t)color;
    return strip.Color(255 - r, 255 - g, 255 - b);
}