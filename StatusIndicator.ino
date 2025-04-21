void initStatus(unsigned long now) 
{
  commandedBrightness[DUAL_LED_GREEN] = 0;
  commandedBrightness[DUAL_LED_RED] = 0;
}

void processStatus(unsigned long now) 
{
  if (lastPingTime < now - 500) 
  {
    commandedBrightness[DUAL_LED_GREEN] = 0;
    commandedBrightness[DUAL_LED_RED] = 255;
  }
  else 
  {
    commandedBrightness[DUAL_LED_GREEN] = 255;
    commandedBrightness[DUAL_LED_RED] = 0;
  }
}