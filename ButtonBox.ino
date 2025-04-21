#include "Configuration.h"

const int NUM_THINGS = 53;


int leds[] = { WHITE_BUTTON_LED, GREEN_BUTTON_LED, YELLOW_BUTTON_LED, RED_BUTTON_LED, SQUARE_BUTTON_LED,
      BLUE_LED, GREEN_LED, YELLOW_LED, RED_LED, DUAL_LED_GREEN, DUAL_LED_RED};

int controls[] = { WHITE_BUTTON, GREEN_BUTTON, YELLOW_BUTTON, RED_BUTTON, SQUARE_BUTTON, SWITCH_UP, SWITCH_DOWN };

int buttons[] = { WHITE_BUTTON, GREEN_BUTTON, YELLOW_BUTTON, RED_BUTTON, SQUARE_BUTTON };
int switches[] = { SWITCH_UP, SWITCH_DOWN };

void setup() 
{
    unsigned long now = millis();

    initLeds(now);

    initControls(now);

    initSerial(now);

    initStatus(now);
}

void loop() 
{
  unsigned long now = millis();

  processControls(now);

  handleDimming(now);

  processSerial(now);

  processStatus(now);

  processLeds(now);
}

