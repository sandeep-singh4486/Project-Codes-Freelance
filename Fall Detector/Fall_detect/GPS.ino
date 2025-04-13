SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();
#ifdef UDR0
  if (GPSECHO)
    if (c) UDR0 = c;
#endif
}

void useInterrupt(boolean v) {
  if (v) {

    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    usingInterrupt = true;
  } else {
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
  }
}
//uint32_t timer = millis();

void Gps_wifi()
{
  String LAT = String(GPS.latitudeDegrees); // turn integer to string
  String LON = String(GPS.longitudeDegrees); // turn integer to string
  if (! usingInterrupt) {
    char c = GPS.read();
    if (GPSECHO)
      if (c) Serial.print(c);
  }

  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA()))
      return;
  }

  if (timer > millis())  timer = millis();

  if (millis() - timer > 2000)
  {
    timer = millis();
    if (GPS.fix) {
      delay(100);

      debug.print(GPS.latitudeDegrees, 4);
      debug.print(", ");
      debug.println(GPS.longitudeDegrees, 4);
      delay(100);
    }
  }
  }

void Gps_Gsm()
{
   if (! usingInterrupt) {
    char c = GPS.read();
    if (GPSECHO)
      if (c) Serial.print(c);
  }

  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA()))
      return;
  }

  if (timer > millis())  timer = millis();

  if (millis() - timer > 2000)
  {
    timer = millis();
    if (GPS.fix) {
      delay(100);
      mySerial.println("AT");
       delay(10000);  // Delay of 1000 milli seconds or 1 second
      mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
      delay(10000);  // Delay of 1000 milli seconds or 1 second
      mySerial.println("AT+CMGS=\"+919591716440\"\r"); // Replace x with mobile number
      mySerial.println("Need Help");// The SMS text you want to send
      mySerial.println("my latitude and longitude are");// The SMS text you want to send
     // delay(100);
      mySerial.print(GPS.latitudeDegrees, 4);
      mySerial.print(", ");
      mySerial.println(GPS.longitudeDegrees, 4);
      mySerial.println((char)26);// ASCII code of CTRL+Z
    }
  }
  }
  
