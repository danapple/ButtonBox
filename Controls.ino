
unsigned long lastFlip[53];

boolean lastRead[53];
int controlStates[53];
boolean controlChanged[53];

void initControls(unsigned long now) 
{
  for (int control = 0; control < sizeof(controls) / sizeof(int); control++)
  {
    int pinNumber = controls[control];
    pinMode(pinNumber, INPUT_PULLUP);
    controlStates[pinNumber] = HIGH;
    lastFlip[pinNumber] = now;
  }
}

void processControls(unsigned long now) 
{  
  for (int i = 0; i < sizeof(controls) / sizeof(int); i++) {
    int pinNumber = controls[i];
    int readAs = digitalRead(pinNumber);  
    controlChanged[pinNumber] = false;

    if (readAs != lastRead[pinNumber]) {
      lastRead[pinNumber] = readAs;
      lastFlip[pinNumber] = now;
    } else if (lastFlip[pinNumber] < now - 50) {
      if (controlStates[pinNumber] != readAs) {
        controlStates[pinNumber] = readAs;
        controlChanged[pinNumber] = true;
        sendByte(now, pinNumber | (readAs == HIGH ? 0x80 : 0));
      }
    }
  }
}
