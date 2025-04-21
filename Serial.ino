
unsigned long lastPingTime = 0;

void initSerial(unsigned long now) {
  Serial.begin(9600);
}

void processSerial(unsigned long now) {
  if (Serial.available() > 0) 
  {
    byte incomingByte = Serial.read();
    lastPingTime = now;
    if (incomingByte != 255) 
    {
      commandedBrightness[incomingByte & 0x7f] = incomingByte & 0x80 ? 0 : 255;
    }
  }
}

void sendByte(unsigned long now, byte byteToSend) {
  Serial.write(byteToSend);
}
