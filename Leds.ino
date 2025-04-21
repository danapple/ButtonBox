const int POSITIVE_FADE = 5;
const int NEGATIVE_FADE = -2;

int maxBrightness = 255;

int brightness[NUM_THINGS];
int commandedBrightness[NUM_THINGS];
unsigned long lastChange[NUM_THINGS];
boolean brightnessChanged = false;
boolean displayingBrightnessChange = false;
unsigned long brightnessChangedAt = 0;

#define signum(x) ((x) < 0 ? -1 : ((x) > 0 ? 1 : 0))

void initLeds(unsigned long now) {
    for (int led = 0; led < sizeof(leds) / sizeof(int); led++) {
          pinMode(leds[led], OUTPUT);
          analogWrite(leds[led], 0);
          commandedBrightness[led] = 0;
          brightness[led] = 0;
    }
}

void processLeds(unsigned long now) 
{
  if (brightnessChanged) 
  {
    brightnessChangedAt = now;
    brightnessChanged = false;
    for (int led = 0; led < sizeof(leds) / sizeof(int); led++)
    {
      int pinNumber = leds[led];
      analogWrite(pinNumber, maxBrightness);
    }
    displayingBrightnessChange = true;
    return;
  }

  if (displayingBrightnessChange && brightnessChangedAt < now - 500) 
  {
      for (int led = 0; led < sizeof(leds) / sizeof(int); led++) 
      {
          int pinNumber = leds[led];
          analogWrite(pinNumber, brightness[pinNumber]);
      }
      displayingBrightnessChange = false;
      return;
  }

  for (int i = 0; i < sizeof(leds) / sizeof(int); i++) 
  {
    int pinNumber = leds[i];

    int requestedBrightness = min(commandedBrightness[pinNumber], maxBrightness);

    int direction = signum(requestedBrightness - brightness[pinNumber]);

    if (direction != 0 && now - lastChange[pinNumber] > (direction > 0 ? 1 : 2)) 
    {
      int fade = direction > 0 ? POSITIVE_FADE : NEGATIVE_FADE;
      int newBrightness = brightness[pinNumber] + fade;
      newBrightness = max(0, newBrightness);
      newBrightness = min(maxBrightness, newBrightness);
      brightness[pinNumber] = newBrightness;
      analogWrite(pinNumber, newBrightness);
      lastChange[pinNumber] = now;
    }
  }
}


void brighter() 
{
  maxBrightness *= 2;
  if (maxBrightness > 255) 
  {
    maxBrightness = 255;
  }
  brightnessChanged = true;
}

void dimmer() {
  maxBrightness /= 2;
  if (maxBrightness < 3) 
  {
    maxBrightness = 3;
  }
  brightnessChanged = true;
}