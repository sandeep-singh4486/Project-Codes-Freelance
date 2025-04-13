void Heart_rate()
{
   serialOutput() ;
//     if (BPM >100)
//     {
//      BPM = 0;
//     }
//     else
//     {
//       BPM = BPM;
//  
//     }
//  Serial.println(BPM);
  if (QS == true) {    // A Heartbeat Was Found
    // BPM and IBI have been Determined
    // Quantified Self "QS" true when arduino finds a heartbeat
    fadeRate = 255;         // Makes the LED Fade Effect Happen
    // Set 'fadeRate' Variable to 255 to fade LED with pulse
    serialOutputWhenBeatHappens();   // A Beat Happened, Output that to serial.
    QS = false;                      // reset the Quantified Self flag for next time
  }

  ledFadeToBeat();                      // Makes the LED Fade Effect Happen
  delay(20);     
   String HR = String(BPM); // turn integer to string     
}

void ledFadeToBeat() {
  fadeRate -= 15;                         //  set LED fade value
  fadeRate = constrain(fadeRate, 0, 255); //  keep LED fade value from going into negative numbers!
//  analogWrite(fadePin, fadeRate);         //  fade LED
}


