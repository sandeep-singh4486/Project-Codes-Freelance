// sensor pin mapping
#define PIR   4 // digital read
#define LDR1 16
#define LDR2 5
#define TEMP A0
#define Select_switch 12


// load pin mapping
// ESP8266
#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;
//


#define Light1  0
#define Light2  2
#define FAN     14



// condition mapping
#define ON  HIGH
#define OFF  LOW

// initial values
int PIRval = 0;
int GAS_read = 0;
int LDRVal1;
int LDRVal2;
int buttonState = 0;

void setup() {
  USE_SERIAL.begin(115200);
  USE_SERIAL.println();
  USE_SERIAL.println();
  USE_SERIAL.println();
  for (uint8_t t = 4; t > 0; t--) {
    USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
    USE_SERIAL.flush();
    delay(1000);
  }
  WiFiMulti.addAP("suma", "sumapranuda");

  pinMode(Light1, OUTPUT);//HALL
  pinMode(Light2, OUTPUT);//ROOM
  pinMode(FAN, OUTPUT); //FAN
  pinMode(Select_switch, INPUT_PULLUP);
  pinMode(PIR, INPUT); // OCCUPANCY
}
void loop()
{
  buttonState = digitalRead(Select_switch);
  if (buttonState == HIGH)
  {
    sensor_control();
  } else {

    app_control();
  }
  //sensor_control();// devices controlled based on sensor
  //app_control();// please write the code for app controlled using esp8266
}
void app_control() {
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    HTTPClient http;

    USE_SERIAL.print("[HTTP] begin...\n");
    // configure traged server and url
    //http.begin("https://192.168.1.12/test.html", "7a 9c f4 db 40 d3 62 5a 6e 21 bc 5c cc 66 c8 3e a1 45 59 38"); //HTTPS
    http.begin("http://api.thingspeak.com/channels/247080/feeds.json?results=1&api_key=P4I466FTQYJHIW0Z"); //HTTP

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
        int index = payload.indexOf("field1", 160);
        // USE_SERIAL.println(index);
        String newpayload = payload.substring(index + 9);
        String finalnumber = newpayload.substring(0, newpayload.indexOf("\""));
        // USE_SERIAL.println(newpayload);
        int finalIntNumber = finalnumber.toInt();
        // USE_SERIAL.println(finalIntNumber);
        if (finalIntNumber == 1)
        {
          digitalWrite(Light1, ON);
        }
        else if (finalIntNumber == 2)
        {
          digitalWrite(Light1, OFF);
        }


        int index2 = payload.indexOf("field2", 160);
        //USE_SERIAL.println(index2);
        String newpayload2 = payload.substring(index2 + 9);
        String finalnumber2 = newpayload2.substring(0, newpayload2.indexOf("\""));
        //USE_SERIAL.println(newpayload2);
        int finalIntNumber2 = finalnumber2.toInt();

        if (finalIntNumber2 == 1)
        {
          digitalWrite(Light2, ON);
        }
        else if (finalIntNumber2 == 2)
        {
          digitalWrite(Light2, OFF);
        }

        USE_SERIAL.println(payload);
        int index3 = payload.indexOf("field3", 200);
        USE_SERIAL.println(index3);
        String newpayload3 = payload.substring(index3 + 9);
        String finalnumber3 = newpayload3.substring(0, newpayload3.indexOf("\""));
        USE_SERIAL.println(newpayload3);
        int finalIntNumber3 = finalnumber3.toInt();
        USE_SERIAL.println(finalIntNumber3);
        if (finalIntNumber3 == 1)
        {
          Serial.println("Iam here..........");
          digitalWrite(FAN, HIGH);
        }
        else if (finalIntNumber3 == 2)
        {
          digitalWrite(FAN, LOW);
        }

      }
    } else {
      USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }

  delay(10000);
}
void sensor_control() {
  Serial.println("SENSOR BASED CONTROL");
  Hall_light();
  Room_light();
  Fan();
}

// FOR PIR_SENSOR CODE READ LDR VALUE AND PUT CONDITION
void Hall_light()
{
  int PIRval = digitalRead(PIR);
  int LDRVal1 = digitalRead(LDR1);
  if (PIRval ==  HIGH && LDRVal1 == 0 )
  {
    digitalWrite(Light1, ON);
    Serial.println("Hall Light On");
    delay(500);
    Serial.println(PIRval);
    Serial.println(LDRVal1);

  }
  else
  {
    digitalWrite(Light1, OFF);
    Serial.println("Hall Light OFF");
    delay(500);
    Serial.println(PIRval);
    Serial.println(LDRVal1);
  }
  return;
}
void Room_light()
{
  int PIRval = digitalRead(PIR);
  int LDRVal2 = digitalRead(LDR2);
  if (PIRval ==  HIGH && LDRVal2 == 0 )
  {
    digitalWrite(Light2, ON);
    // Serial.println(PIRval);
    delay(500);
    Serial.println("Room Light On");
    Serial.println(PIRval);
    Serial.println(LDRVal2);
  }
  else
  {
    digitalWrite(Light2, OFF);
    delay(500);
    Serial.println("Room Light OFF");
    Serial.println(PIRval);
    Serial.println(LDRVal2);
  }
  return;
}
void Fan()
{
  int PIRval = digitalRead(PIR);
  int TEMPval = analogRead(TEMP);
  int temp = ((TEMPval * 285) / 1024);
  //int temp = ((4.68 * TEMPval * 100.0) / 1024);
  if (PIRval ==  HIGH && temp >= 30 )
  {
    digitalWrite(FAN, ON);
    Serial.println(PIRval);
    Serial.println(temp);
    Serial.println("FAN On");
    delay(2000);
  }
  else
  {
    digitalWrite(FAN, OFF);
    Serial.println(PIRval);
    Serial.println(temp);
    Serial.println("FAN OFF");
    delay(2000);
  }
  return;
}

