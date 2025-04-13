//IOT BASED ENERGY METER
/*

  The circuit:
   LCD RS pin to digital pin 12
   LCD Enable pin to digital pin 11
   LCD D4 pin to digital pin 5
   LCD D5 pin to digital pin 4
   LCD D6 pin to digital pin 3
   LCD D7 pin to digital pin 2
   LCD R/W pin to ground
   LCD VSS pin to ground
   LCD VCC pin to 5V
   2.2K resistor:ends to +5V and ground wiper to LCD VO pin (pin 3)
*/
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

#define DEBUG FALSE //comment out to remove debug msgs

//*-- Hardware Serial
#define _baudrate 115200

//*-- Software Serial
//
#define _rxpin      2
#define _txpin      3
SoftwareSerial debug( _rxpin, _txpin ); // RX, TX

//*-- IoT Information
#define SSID "nandu"
#define PASS "7406050506"
#define IP "52.1.229.129" // ThingSpeak IP Address

// GET /update?key=[THINGSPEAK_KEY]&field1=[data 1]&field2=[data 2]...;
String GET = "GET /update?key=IH2NK2FBWGVNMIYI";

int currentPin = A1;              //Assign CT input
int Tamper_switch = A0;
double kilos = 0;
int peakPower = 0;
int buttonState = 0;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  //Assign LCD screen pins

void setup()
{
  pinMode(Tamper_switch, INPUT_PULLUP);
  lcd.begin(16, 2);             // columns, rows.  use 16,2 for a 16x2 LCD, etc.
  lcd.clear();
  lcd.setCursor(0, 0);          // set cursor to column 0, row 0 (the first row)
  lcd.print("IOT BASED ENERGY");
  lcd.setCursor(0, 1);          // set cursor to column 0, row 0 (the first row)
  lcd.print("METER UBDT EEE");
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
}

void loop()
{
  int current = 0;
  int maxCurrent = 0;
  int minCurrent = 1000;
  buttonState = digitalRead(Tamper_switch);
  for (int i = 0 ; i <= 200 ; i++) //Monitors and logs the current input for 200 cycles to determine max and min current
  {
    current = analogRead(currentPin);    //Reads current input
    if (current >= maxCurrent)
      maxCurrent = current;
    else if (current <= minCurrent)
      minCurrent = current;
  }
  if (maxCurrent <= 515)
  {
    maxCurrent = 515;
  }
  double RMSCurrent = ((maxCurrent - 515) * 0.707) / 70; //Calculates RMS current based on maximum value
  int RMSPower = 245 * RMSCurrent;  //Calculates RMS Power Assuming Voltage 220VAC, change to 110VAC accordingly
  if (RMSPower > peakPower)
  {
    peakPower = RMSPower;
  }
  kilos = kilos + (RMSPower * (2.05 / 60 / 60 / 1000)); //Calculate kilowatt hours used
  float bill= kilos*3;
  delay (2000);
  String CURRENT = String(RMSCurrent); // turn integer to string
  String POWER = String(RMSPower); // turn integer to string
  String ENERGY = String(kilos); // turn integer to string
  String BILL = String(bill); // turn integer to string
  String TAMPER = String(buttonState); // turn integer to string
  updateTS(TAMPER,CURRENT, POWER, ENERGY,BILL);
  delay(3000); //
  lcd.clear();
  lcd.setCursor(0, 0);          // Displays all current data
  lcd.print(RMSCurrent);
  lcd.print("A");
  lcd.setCursor(10, 0);
  lcd.print(RMSPower);
  lcd.print("W");
  lcd.setCursor(0, 1);
  lcd.print(kilos);
  lcd.print("kWh");
  lcd.setCursor(10, 1);
  lcd.print(250);
  lcd.print("V");
//  Serial.print(RMSCurrent);
//  Serial.println("A");
//  Serial.print(RMSPower);
//  Serial.println("W");
//  Serial.print(kilos);
//  Serial.println("kWh");
//  Serial.print(peakPower);
//  Serial.println("W");
}
void updateTS( String T, String I , String P, String E,String B)
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

  cmd = GET + "&field1=" + T + "&field2=" + I + "&field3=" + P +"&field4=" + E + "&field5=" + B +"\r\n";
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

