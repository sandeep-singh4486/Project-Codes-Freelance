void touch_wifi()
{
     //int count=0;
  int emergency=digitalRead(touch1);
  int imok=digitalRead(touch2);
  int healthassistance=digitalRead(touch3);
  int lostthepath=digitalRead(touch4);

//  String EMER=String(emergency);
//  String IMOK=String(imok);
//  String HEAL=String(healthassistance);
//  String LOST=String(lostthepath);
  }


void touch_gsm()
{
     int count=0;
  int emergency=digitalRead(touch1);
  int imok=digitalRead(touch2);
  int healthassistance=digitalRead(touch3);
  int lostthepath=digitalRead(touch4);

    
  if(emergency==HIGH){
 mySerial.println("EMERGENCY");// The SMS text you want to send
 Gps_Gsm();
  mySerial.println((char)26);// ASCII code of CTRL+Z
 SeeedOled.setBrightness(Brightness);  
 SeeedOled.setTextXY(3,0);          
  SeeedOled.putString("  Emergency  "); 
  }
  
  else if(imok==HIGH)
  {
    mySerial.println("IM OK");
     mySerial.println((char)26);
    SeeedOled.setBrightness(Brightness);  
 SeeedOled.setTextXY(3,0);          
  SeeedOled.putString("    IM OK    "); 
  }

   else if(healthassistance==HIGH)
  {
    mySerial.println("Health assistance");
    Gps_Gsm();
     mySerial.println((char)26);
     SeeedOled.setBrightness(Brightness);  
 SeeedOled.setTextXY(3,0);          
  SeeedOled.putString("Health Assistance"); 
  }

   else if(lostthepath==HIGH)
  {
    mySerial.println("LOST THE PATH");
    Gps_Gsm();
     mySerial.println((char)26);
    SeeedOled.setBrightness(Brightness);  
 SeeedOled.setTextXY(3,0);          
  SeeedOled.putString("Lost the Path"); 
  }
  else
  {
// SeeedOled.setTextXY(3,0);          
//  SeeedOled.putString("               "); 
  }
}

