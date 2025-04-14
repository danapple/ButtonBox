#include "Configuration.h"

unsigned long lastChange = millis();
const int POSITIVE_FADE = 5;
const int NEGATIVE_FADE = -2;
const int NUM_THINGS = 53;

int fade = POSITIVE_FADE;
int brightness = 0;

unsigned long lastPeak = millis();

int maxBrightness = 255;

int leds[] = { WHITE_BUTTON_LED, GREEN_BUTTON_LED, YELLOW_BUTTON_LED, RED_BUTTON_LED, SQUARE_BUTTON_LED,
      BLUE_LED, GREEN_LED, YELLOW_LED, RED_LED, DUAL_LED_GREEN, DUAL_LED_RED};

int controls[] = { WHITE_BUTTON, GREEN_BUTTON, YELLOW_BUTTON, RED_BUTTON, SQUARE_BUTTON, SWITCH_UP, SWITCH_DOWN };

int buttons[] = { WHITE_BUTTON, GREEN_BUTTON, YELLOW_BUTTON, RED_BUTTON, SQUARE_BUTTON };
int switches[] = { SWITCH_UP, SWITCH_DOWN };

void setup() {
    unsigned long now = millis();

    for (int led = 0; led < sizeof(leds) / sizeof(int); led++) {
          pinMode(leds[led], OUTPUT);
          analogWrite(leds[led], 0);
    }
    initControls(now);

    lastChange = now;
}

int ledIndex = 0;
int currentLed = WHITE_BUTTON_LED;
int currentOpposite = leds[5];

boolean hitLedPeak = false;
unsigned long brightnessChangedAt = millis();
boolean displayingBrightnessChange = false;

void loop() {
  unsigned long now = millis();

  processControls(now);

  boolean brightnessChanged = handleDimming(now);

  processLeds(now);

  if (brightnessChanged) {
    brightnessChangedAt = now;
  }

  if (brightnessChangedAt > now - 500) {
    displayingBrightnessChange = true;
    for (int led = 0; led < sizeof(leds) / sizeof(int); led++) {
        int pinNumber = leds[led];
        analogWrite(pinNumber, maxBrightness);
    }
    return;
  } else if (displayingBrightnessChange) {
    for (int led = 0; led < sizeof(leds) / sizeof(int); led++) {
        int pinNumber = leds[led];
        analogWrite(pinNumber, 0);
    }
    displayingBrightnessChange = false;
  }
  if (now - lastPeak < 2000) {
    return;
  }
  if (now - lastChange > (fade > 0 ? 1 : 2)) {
    brightness += fade;
    if (brightness > maxBrightness) {
      brightness = maxBrightness;
      fade = NEGATIVE_FADE;
      lastPeak = now;
      hitLedPeak = true;
    }
    if (brightness <= 0) {
      brightness = 0;
      fade = POSITIVE_FADE;
      lastPeak = now;
    }
    analogWrite(currentLed, brightness);
    analogWrite(DUAL_LED_RED, brightness);

    if (hitLedPeak) {
      analogWrite(currentOpposite, maxBrightness - brightness);
    }

    lastChange = now;
  }

}

void changeLed(unsigned long now, int ledInd) {
    analogWrite(currentLed, 0);
    analogWrite(currentOpposite, 0);

    brightness = 0;
    lastPeak = now;
    fade = POSITIVE_FADE;
    lastChange = now;
    lastPeak = 0;
    hitLedPeak = false;

    currentLed = leds[ledInd % (sizeof(leds) / sizeof(int))];
    currentOpposite = leds[(ledInd + 5) % (sizeof(leds) / sizeof(int))];


    for (int i = 0; i < (sizeof(leds) / sizeof(int)); i++) {
        int led = leds[i];
        if (led != currentLed) {
          analogWrite(led, 0);
        }
      }
  }

void brighter() {
  maxBrightness *= 2;
  if (maxBrightness > 255) {
    maxBrightness = 255;
  }
}

void dimmer() {
  maxBrightness /= 2;
  if (maxBrightness < 3) {
    maxBrightness = 3;
  }
}


