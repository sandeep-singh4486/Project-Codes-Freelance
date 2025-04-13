void wifi()
{
//  touch_wifi();
//  temperature();
//  Gps_wifi();
//  Heart_rate();
  int emergency=digitalRead(touch1);
  int imok=digitalRead(touch2);
  int healthassistance=digitalRead(touch3);
  int lostthepath=digitalRead(touch4);

  String TEMP=String(mpu6050.getTemp());
  String HR = String(BPM);
  String LAT = String(GPS.latitudeDegrees); // turn integer to string
  String LON = String(GPS.longitudeDegrees); // turn integer to string
  String EMER=String(emergency);
  String IMOK=String(imok);
  String HEAL=String(healthassistance);
  String LOST=String(lostthepath);
  updateTS(TEMP,HR, LAT, LON,EMER, IMOK, HEAL, LOST);
  }
  
  
  void updateTS( String TEM,String HRT, String LT, String LN, String EME, String IM, String HEA, String LOS )
{
  // ESP8266 Client
  String cmd = "AT+CIPSTART=\"TCP\",\"";// Setup TCP connection
  cmd += IP;
  cmd += "\",80";
  sendDebug(cmd);
  delay(2000);
  if ( Serial.find( "Error" ) )
  {
    debug.print( "RECEIVED: Error\nExit1" );
    return;
  }

  cmd = GET + "&field1=" + TEM + "&field2=" + HRT +"&field3=" + LT + "&field4=" + LN + "&field5=" + EME + "&field6=" + IM + "&field7=" + HEA + "&field8=" + LOS + "\r\n";
  Serial.print( "AT+CIPSEND=" );
  Serial.println( cmd.length() );
  if (Serial.find( ">" ) )
  {
    debug.print(">");
    debug.print(cmd);
    Serial.print(cmd);
  }
  else
  {
    sendDebug( "AT+CIPCLOSE" );//close TCP connection
  }
  if ( Serial.find("OK") )
  {
    debug.println( "RECEIVED: OK" );
  }
  else
  {
    debug.println( "RECEIVED: Error\nExit2" );
  }
}

void sendDebug(String cmd)
{
  debug.print("SEND: ");
  debug.println(cmd);
  Serial.println(cmd);
}

  
