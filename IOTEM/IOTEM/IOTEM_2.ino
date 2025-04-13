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
#define SSID "smartmeter"
#define PASS "smartmeter"
#define IP "184.106.153.149" // ThingSpeak IP Address
#define TH 502
// GET /update?key=[THINGSPEAK_KEY]&field1=[data 1]&field2=[data 2]...;
String GET = "GET /update?key=MXVFMUYTFVXZEUQL";

int currentPin = A0;
int Tamper_switch = A1;
int peakPower = 0;
int buttonState = 0;

double Voltage = 0;


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  //Assign LCD screen pins

void setup()
{
  pinMode(Tamper_switch, INPUT_PULLUP);
  lcd.begin(16, 2);             // columns, rows.  use 16,2 for a 16x2 LCD, etc.
  lcd.clear();
  lcd.setCursor(0, 0);          // set cursor to column 0, row 0 (the first row)
  lcd.print("IOT BASED SMART");
  lcd.setCursor(0, 1);          // set cursor to column 0, row 0 (the first row)
  lcd.print("  ENERGY METER  ");
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
  int Voltage = 220;
  buttonState = digitalRead(Tamper_switch);
  for (int i = 0 ; i <= 200 ; i++) //Monitors and logs the current input for 200 cycles to determine max and min current
  {
    current = analogRead(currentPin);    //Reads current input
    if (current >= maxCurrent)
      maxCurrent = current;
    else if (current <= minCurrent)
      minCurrent = current;
  }
  if (maxCurrent <= TH)
  {
    maxCurrent = TH;
  }
  double RMSCurrent = ((maxCurrent - TH) * 0.707) / 86; //Calculates RMS current based on maximum value
  int RMSPower = 245 * RMSCurrent;  //Calculates RMS Power Assuming Voltage 220VAC, change to 110VAC accordingly
  if (RMSPower > peakPower)
  {
    peakPower = RMSPower;
  }
  int  kilos = kilos + (RMSPower * (2.05 / 60 / 60 / 1000)); //Calculate kilowatt hours used
  float bill = kilos * 3;

  String Main_CURRENT = String(RMSCurrent); // turn integer to string
  String Main_POWER = String(RMSPower); // turn integer to string
  String Main_Voltage = String(Voltage); // turn integer to string
  String ENERGY = String(kilos); // turn integer to string
  String BILL = String(bill);
  String TAMPER = String(buttonState);
  updateTS(Main_CURRENT, Main_Voltage, Main_POWER, ENERGY, BILL,TAMPER);
  delay(3000); //
  lcd.clear();
  lcd.setCursor(0, 0);          // Displays all current data
  lcd.print(RMSCurrent);
  lcd.print("A");
  lcd.setCursor(10, 0);
  lcd.print(RMSPower);
  lcd.print("W");
  lcd.setCursor(0, 1);
  //  lcd.print(Main_Voltage);
  //  lcd.print("V");
  lcd.print("220");
  lcd.print("V");
  lcd.setCursor(10, 1);
  lcd.print(kilos);
  lcd.print("kWh");
  //  Serial.print(RMSCurrent);
  //  Serial.println("A");
  //  Serial.print(RMSPower);
  //  Serial.println("W");
  //  Serial.print(Main_Voltage);
  //  Serial.println("V");


}
void updateTS( String MC, String MV , String MP, String KW, String B,String T)
{
  // ESP8666 Client
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

  cmd = GET + "&field1=" + MC + "&field2=" + MV + "&field3=" + MP + "&field4=" + KW + "&field5=" + B +"&field6=" + T + "\r\n";
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

int getVPP_1()
{
  int result1;

  int readValue1;             //value read from the sensor
  int maxValue1 = 0;          // store max value here
  int minValue1 = 1024;          // store min value here

  uint32_t start_time = millis();
  while ((millis() - start_time) < 1000) //sample for 1 Sec
  {
    readValue1 = analogRead(currentPin);
    // see if you have a new maxValue
    if (readValue1 > maxValue1)
    {
      /*record the maximum sensor value*/
      maxValue1 = readValue1;
    }
    if (readValue1 < minValue1)
    {
      /*record the maximum sensor value*/
      minValue1 = readValue1;
    }
  }
  int b = maxValue1 - minValue1;
  if (b >= 10)
  { result1 = ((b) * 256) / 1024;
  }
  else {
    result1 = 0;
  }
  // Subtract min from max
  //  Serial.print(b);
  //  Serial.print(maxValue1);
  //  Serial.println(minValue1);
  return result1;
}

