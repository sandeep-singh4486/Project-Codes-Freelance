#include <Arduino.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
#define LED D0
#define TH 522
#define USE_SERIAL Serial
#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;
String apiKey = "MXVFMUYTFVXZEUQL";     //  Enter your Write API key from ThingSpeak
const char *ssid =  "smartmeter";     // replace with your wifi ssid and wpa2 key
const char *pass =  "smartmeter";
const char* server = "api.thingspeak.com";


int currentPin = A0;
int Tamper_switch = D3;
int peakPower = 0;
int buttonState = 0;

double Voltage = 0;

WiFiClient client;

void setup()
{
  Serial.begin(115200);
  delay(10);
  pinMode(Tamper_switch, INPUT_PULLUP);
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);          // set cursor to column 0, row 0
  lcd.print("IOT BASED SMART ");
  lcd.setCursor(0, 1);          // set cursor to column 0, row 1
  lcd.print("METERING SYSTEM ");
  Serial.println("Connecting to ");
  Serial.println(ssid);
  pinMode(LED, OUTPUT);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  USE_SERIAL.begin(115200);
  USE_SERIAL.println();
  USE_SERIAL.println();
  USE_SERIAL.println();
  for (uint8_t t = 4; t > 0; t--) {
    USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
    USE_SERIAL.flush();
    delay(1000);
  }
  WiFiMulti.addAP(ssid, pass );
}

void loop()
{
//  digitalWrite(LED, HIGH);
//  delay(1000);
//  Serial.println("on");
//  digitalWrite(LED, LOW);
//  delay(1000);
//  Serial.println("off");
getVPP_1();
  Update_sensordata();

  delay(30000);
  app_control();

}
void Update_sensordata()
{

  int current = 0;
  int maxCurrent = 0;
  int minCurrent = 1000;
  int Voltage = 242;
  float  kilos = 1.2;
  float bill = 36.0;
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
  int RMSPower = 242 * RMSCurrent;  //Calculates RMS Power Assuming Voltage 220VAC, change to 110VAC accordingly
  if (RMSPower > peakPower)
  {
    peakPower = RMSPower;
  }
  //kilos = kilos + (RMSPower * (2.05 / 60 / 60 / 1000)); //Calculate kilowatt hours used
  kilos = kilos + (RMSPower * (2.05 / 1000));
  bill = bill + kilos * 3;
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
  lcd.print(Voltage);
  lcd.print("V");
  if (client.connect(server, 80))  //   "184.106.153.149" or api.thingspeak.com
  {

    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(RMSCurrent);
    postStr += "&field2=";
    postStr += String(Voltage);
    postStr += "&field3=";
    postStr += String(RMSPower);
    postStr += "&field4=";
    postStr += String(kilos);
    postStr += "&field5=";
    postStr += String(bill);
    postStr += "&field6=";
    postStr += String(buttonState);
    postStr += "\r\n\r\n";
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    Serial.print("current: ");
    Serial.print(RMSCurrent);
    Serial.print(" voltage: ");
    Serial.print(Voltage);
    Serial.print("volts: ");
    Serial.print(kilos);
    Serial.print(" Power: ");
    Serial.print(RMSPower);
    Serial.println(". Send to Thingspeak.");
     Serial.print(buttonState);
  }
  client.stop();

  Serial.println("Waiting...");

  // thingspeak needs minimum 15 sec delay between updates, i've set it to 30 seconds
  delay(15000);


}

void app_control() {
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    HTTPClient http;

    USE_SERIAL.print("[HTTP] begin...\n");
    // configure traged server and url
    //http.begin("https://192.168.1.12/test.html", "7a 9c f4 db 40 d3 62 5a 6e 21 bc 5c cc 66 c8 3e a1 45 59 38"); //HTTPS
    http.begin("http://api.thingspeak.com/channels/283992/feeds.json?results=1&api_key=AB1NCELLM1M7WMK2"); //HTTP

    USE_SERIAL.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        //USE_SERIAL.println(payload);
        int index = payload.indexOf("field3", 160);
        // USE_SERIAL.println(index);
        String newpayload = payload.substring(index + 9);
        String finalnumber = newpayload.substring(0, newpayload.indexOf("\""));
        // USE_SERIAL.println(newpayload);
        int finalIntNumber = finalnumber.toInt();
        //USE_SERIAL.println(finalIntNumber);
        if (finalIntNumber == 1)
        {
          digitalWrite(LED, HIGH);
//          lcd.clear();
//          lcd.setCursor(0, 0);          // set cursor to column 0, row 0
//          lcd.print("POWER DISCONNECT ");
//          lcd.setCursor(0, 1);          // set cursor to column 0, row 1
//          lcd.print("PAY BILL - KPTCL");
          // Serial.println("ON");
        }
        else if (finalIntNumber == 0)
        {
          digitalWrite(LED, LOW);
//          lcd.setCursor(0, 0);          // set cursor to column 0, row 0
//          lcd.print("POWER CONNECTED ");
//          lcd.setCursor(0, 1);          // set cursor to column 0, row 1
//          lcd.print("BILL PAYED KPTCL");
          // Serial.println("OFF");
        }

      } else {
        USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    }
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
  Serial.println(result1);
  return result1;
}

