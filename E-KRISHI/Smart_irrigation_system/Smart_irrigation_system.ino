/*
   Library inclusion
*/
#include "DHT.h"
#include <Wire.h>
//#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
/*
  Pin defination
  LCD SDA A4
  LCD SCL A5
**/
#define DHTPIN A0
#define SoilSensor A1
#define RainSensor A3
#define TheftSwitch A7
#define WaterPump 13
#define Buzzer 5
#define DEBUG FALSE //comment out to remove debug msgs
#define _baudrate 115200//*-- Hardware Serial
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

//*-- Software Serial
#define _rxpin      2
#define _txpin      3
SoftwareSerial debug( _rxpin, _txpin ); // RX, TX

//*-- IoT Information
#define SSID "nandu"
#define PASS "7406050506"
#define IP "184.106.153.149" // ThingSpeak IP Address
String GET = "GET /update?key=QI44ZGS0AT02PLAU";// GET /update?key=[THINGSPEAK_KEY]&field1=[data 1]&field2=[data 2]...;

DHT dht(DHTPIN, DHTTYPE);
//LiquidCrystal_I2C lcd(0x27, 16, 2);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
SoftwareSerial mySerial(3, 2);
// Variable Defination
int TamperState = 0;
int RainState = 0;
int Soilmoisture_value = 0;
int dry = 1020;
int Wet_comp = 263;
float h =  0;
float t =  0;
float f =  0;
float hif =  0;
float hic =  0;
int Soilsensor_value = 0;
void setup() {
  pinMode(TheftSwitch, INPUT_PULLUP);
  pinMode(WaterPump, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  lcd.begin(16, 2); 
//  lcd.backlight();// Turn on the blacklight and print a message.
  lcd.clear();
  lcd.setCursor(0, 0);          // set cursor to column 0, row 0
  lcd.print("IOT BASED SMART ");
  lcd.setCursor(0, 1);          // set cursor to column 0, row 1
  lcd.print("IRRIGATION SYSTM");
  Serial.begin( _baudrate );
  debug.begin( _baudrate );
  sendDebug("AT");
  delay(5000);
  if (Serial.find("OK"))
  {
    debug.println("RECEIVED: OK\nData ready to sent!");
    Serial.println("OK");
    connectWiFi();
  }
  dht.begin();
  
  Serial.print("System initialised");
}
void loop() {
  TamperState = digitalRead(TheftSwitch);
  RainState = digitalRead(RainSensor);
  Soilsensor_value = analogRead(SoilSensor);
  Soilmoisture_value = map(Soilsensor_value, dry, Wet_comp, 0, 100);
  h = dht.readHumidity(); // Read temperature as Celsius (the default)
  t = dht.readTemperature(); // Read temperature as Fahrenheit (isFahrenheit = true)
  f = dht.readTemperature(true); // put your main code here, to run repeatedly:
//  if (isnan(h) || isnan(t) || isnan(f)) {
//    Serial.println("Failed to read from DHT sensor!");
//    return;
//  }
  hif = dht.computeHeatIndex(f, h); // Compute heat index in Celsius (isFahreheit = false)
  hic = dht.computeHeatIndex(t, h, false);
  String HUMIDITY = String(h); // turn integer to string
  String TEMP = String(t); // turn integer to string
  String RAIN = String(RainState); // turn integer to string
  String SOIL = String(Soilmoisture_value); // turn integer to string
  String TAMPER = String(TamperState);

  //Serial.print("Soilsensor_value: "); Serial.println(Soilsensor_value);
  delay (2000);
  lcd.clear();
  lcd.setCursor(0, 0);          // Displays all current data
  lcd.print(t);
  lcd.print("*C");
  lcd.setCursor(10, 0);
  lcd.print(h);
  lcd.print("%");
  lcd.setCursor(0, 1);          // Displays all current data
  lcd.print("Rain=");
  lcd.print(RainState);
  Serial.print("Humidity: "); Serial.print(h);
  Serial.print(" %\t"); Serial.print("Temperature: ");
  Serial.print(t); Serial.print(" *C ");
  Serial.print(f); Serial.print(" *F\t");
  Serial.print("Heat index: "); Serial.print(hic);
  Serial.print(" *C "); Serial.print(hif);
  Serial.println(" *F");
  Serial.print("Soilmoisture_value: "); Serial.println(Soilmoisture_value);
  if (RainState == LOW && Soilmoisture_value <= 50 )
  {
    digitalWrite(WaterPump, HIGH);
    Serial.print("PUMP ON: ");
    Serial.print(RainState);

  }
  else
  {
    digitalWrite(WaterPump, LOW);
    Serial.print("PUMP OFF ");
    Serial.print(RainState);
  }
  updateTS(TAMPER, HUMIDITY, TEMP, RAIN, SOIL);
  Debug();
}
void updateTS( String T, String H , String C, String R, String M)
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

  cmd = GET + "&field1=" + T + "&field2=" + H + "&field3=" + C + "&field4=" + R + "&field5=" + M + "\r\n";
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
void Debug()
{
  debug.print("Humidity: "); Serial.print(h);
  debug.print(" %\t"); Serial.print("Temperature: ");
  debug.print(t); Serial.print(" *C ");
  debug.print(f); Serial.print(" *F\t");
  debug.print("Heat index: "); Serial.print(hic);
  debug.print(" *C "); Serial.print(hif);
  debug.println(" *F");
  debug.print("Rain_value: "); Serial.println(RainState);
  debug.print("Soilmoisture_value: "); debug.println(Soilmoisture_value);
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
