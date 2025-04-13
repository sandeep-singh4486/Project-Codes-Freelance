 void IR_Read()
  {
    //Dht_read();
   Lane1_S1_Val=digitalRead(Lane1_S1);
   Lane1_S2_Val=digitalRead(Lane1_S2);
   Lane1_S3_Val=digitalRead(Lane1_S3);
   Lane2_S1_Val=digitalRead(Lane2_S1);
   Lane2_S2_Val=digitalRead(Lane2_S2);
   Lane2_S3_Val=digitalRead(Lane2_S3);
   Lane3_S1_Val=digitalRead(Lane3_S1);
   Lane3_S2_Val=digitalRead(Lane3_S2);
  Lane3_S3_Val=digitalRead(Lane3_S3);
    }
  void RGB_color_Lane1(int Lane1_R1_Value,int Lane1_G1_Value,int Lane1_B1_Value)
  {
  analogWrite(Lane1_R1,Lane1_R1_Value);
  analogWrite(Lane1_G1,Lane1_G1_Value);
  analogWrite(Lane1_B1,Lane1_B1_Value);
  
  }
   void RGB_color_Lane2(int Lane2_R2_Value,int Lane2_G2_Value,int Lane2_B2_Value)
  {
  analogWrite(Lane2_R2,Lane2_R2_Value);
  analogWrite(Lane2_G2,Lane2_G2_Value);
  analogWrite(Lane2_B2,Lane2_B2_Value);
  
  }
   void RGB_color_Lane3(int Lane3_R3_Value,int Lane3_G3_Value,int Lane3_B3_Value)
  {
  analogWrite(Lane3_R3,Lane3_R3_Value);
  analogWrite(Lane3_G3,Lane3_G3_Value);
  analogWrite(Lane3_B3,Lane3_B3_Value);
  
  }
//  void Dht_read()
//  {
// byte temperature = 0;
//  byte humidity = 0;
//  int err = SimpleDHTErrSuccess;
//  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
//    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
//    return;
//  }
//  
//  Serial.print("Sample OK: ");
//  Serial.print((int)temperature); Serial.print(" *C, "); 
//  Serial.print((int)humidity); Serial.println(" H");
//  
//  // DHT11 sampling rate is 1HZ.
//  delay(1500);
//  }
