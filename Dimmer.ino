
boolean handleDimming(unsigned long now)
{
  for (int i = 0; i < sizeof(switches) / sizeof(int); i++) {
    int pinNumber = switches[i];
    if (controlChanged[pinNumber] && controlStates[pinNumber] == LOW)
    {
      switch (pinNumber) {
        case SWITCH_UP:
        {
          brighter();
          return true;
        }
        case SWITCH_DOWN:
        {
          dimmer();
          return true;
        }
      }
    }
  }
  return false;
}