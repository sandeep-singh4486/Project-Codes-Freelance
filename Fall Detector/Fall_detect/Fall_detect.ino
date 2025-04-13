#include "PINS.h"

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  delay(1000);
  SeeedOled.init();  //initialze SEEED OLED display
  SeeedOled.clearDisplay();               // clear the screen and set start position to top left corner
  SeeedOled.setPageMode();
  SeeedOled.setBrightness(Brightness);
  SeeedOled.setTextXY(0, 0);
  SeeedOled.putString("   SMART CARING  ");
  debug.begin( 115200 );
  mySerial.begin(9600);
  delay(100);
  mySerial.println("AT");    //Sets the GSM Module in Text Mode
  pinMode(touch1, INPUT);
  pinMode(touch2, INPUT);
  pinMode(touch3, INPUT);
  pinMode(touch4, INPUT);
  pinMode(switch1, INPUT);
  interruptSetup();
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  GPS.sendCommand(PGCMD_ANTENNA);
  useInterrupt(true);
  sendDebug("AT");
  delay(5000);
  if (Serial.find("OK"))
  {
    debug.println("RECEIVED: OK\nData ready to sent!");
    Serial.println("OK");
    connectWiFi();
  }
  delay(1000);
}

uint32_t timer = millis();
void loop() {
  int mode = digitalRead(switch1);
  lcd_display();

  if (mode == HIGH)
  {

    Serial.print("HIGH");
    wifi();
  }
  else if (mode == LOW)
  {
    Serial.print("LOW");
    gsm();
  }

}




boolean connectWiFi()
{
  Serial.println("AT+CWMODE=1");//WiFi STA mode - if '3' it is both client and AP
  delay(2000);
  //Connect to Router with AT+CWJAP="SSID","Password";
  // Check if connected with AT+CWJAP?
  String cmd = "AT+CWJAP=\""; // Join accespoint
  cmd += SSID;
  cmd += "\",\"";
  cmd += PASS;
  cmd += "\"";
  sendDebug(cmd);
  delay(5000);
  if (Serial.find("OK"))
  {
    debug.println("RECEIVED: OK");
    return true;
  }
  else
  {
    debug.println("RECEIVED: Error");
    return false;
  }

  cmd = "AT+CIPMUX=0";// Set Single connection
  sendDebug( cmd );
  if ( Serial.find( "Error") )
  {
    debug.print( "RECEIVED: Error" );
    return false;
  }
}


