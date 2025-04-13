void Temp_read()
{
  sensors.requestTemperatures();  
  TC = sensors.getTempCByIndex(0);
   Serial.print(TC );
  Serial.print(" *C ");
//  Vin = analogRead(TempSensor);
//  float mv = (Vin / 1024.0) * 5000;
//  TC = mv / 10;
//  TF = (TC * 9) / 5 + 32;

}
void IncTemp_read()
{
  h1 = dht1.readHumidity();
  t1 = dht1.readTemperature();
  h2 = dht2.readHumidity();
  t2 = dht2.readTemperature();
  h3 = dht3.readHumidity();
  t3 = dht3.readTemperature();
  h4 = dht3.readHumidity();
  t4 = dht3.readTemperature();
  hum_avg = ((h1 + h2 + h3 + h4) / NO_sensor);
  Temp_avg = ((t1 + t2 + t3 + t4) / NO_sensor);

}
void servo_motion1()
{
  for (pos = 0; pos <= 180; pos += 1) {
    // in steps of 1 degree
    myservo1.write(pos);
    delay(15);
  }
}
void servo_motion2(){
  for (pos = 180; pos >= 0; pos -= 1) {
    myservo1.write(pos);
    delay(15);
  }
}
void forward()
{
  digitalWrite(Prammotor_C1, HIGH);
  digitalWrite(Prammotor_C2, LOW);
  Serial.println("forward ");

}
void Reverse()
{
  digitalWrite(Prammotor_C1, LOW);
  digitalWrite(Prammotor_C2, HIGH);
  Serial.println("Reverse ");

}
void Stop()
{
  digitalWrite(Prammotor_C1, LOW);
  digitalWrite(Prammotor_C2, LOW);
  Serial.println("Stop ");

}
void Serial_Print()
{
  Serial.print("Baby Temp= " );
  Serial.print(TC );
  Serial.print(" *C ");
  //  Serial.print(" Temp= " );
  //  Serial.print(TF ); Serial.print(" *F ");
  Serial.print("Humidity: ");
  Serial.print(hum_avg);
  Serial.println(" %\t");
  Serial.print("Temperature: ");
  Serial.print(Temp_avg);
  Serial.println(" *C ");
}
void LCD_Print()
{
  lcd.clear();
  lcd.setCursor(0, 0);          // Displays all current data
  lcd.print(Temp_avg);
  lcd.print("*C");
  lcd.setCursor(10, 0);
  lcd.print(hum_avg);
  lcd.print("%");
  lcd.setCursor(0, 1);          // Displays all current data
  lcd.print(TC);
  lcd.print("*c");
  lcd.setCursor(10, 1);          // Displays all current data
  lcd.print("BED");
}
void Pulse_read()
{
  serialOutput() ;

  if (QS == true) {    // A Heartbeat Was Found
    // BPM and IBI have been Determined
    // Quantified Self "QS" true when arduino finds a heartbeat
    fadeRate = 255;         // Makes the LED Fade Effect Happen
    // Set 'fadeRate' Variable to 255 to fade LED with pulse
    serialOutputWhenBeatHappens();   // A Beat Happened, Output that to serial.
    QS = false;                      // reset the Quantified Self flag for next time
  }

  ledFadeToBeat();                      // Makes the LED Fade Effect Happen
  delay(20);                             //  take a break
}
void ledFadeToBeat() {
  fadeRate -= 15;                         //  set LED fade value
  fadeRate = constrain(fadeRate, 0, 255); //  keep LED fade value from going into negative numbers!
  analogWrite(fadePin, fadeRate);         //  fade LED
}
