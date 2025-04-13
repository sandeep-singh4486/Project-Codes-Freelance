#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Servo.h>
#include <SoftwareSerial.h>
Servo myservo1;
Servo myservo2;
#define DHTPIN1 A0
#define DHTPIN2 A1
#define DHTPIN3 A2
#define DHTPIN4 A3
#define ONE_WIRE_BUS A6
#define HB_sensor A7
//#define TempSensor A4
#define BedwetSensor 2
#define Sound_sensor 3

#define HX711_DT_1 4
#define HX711_SCK_1 5
#define HX711_DT_2 6
#define HX711_SCK_2 7
#define Heater 8
#define FAN 9
#define BUZZER 10
#define Prammotor_C1 6
#define Prammotor_C2 7
#define Incub_Temp 37
#define Baby_Temp 36
#define DHTTYPE DHT11   // DHT 11
#define On HIGH
#define Off LOW
DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);
DHT dht3(DHTPIN3, DHTTYPE);
DHT dht4(DHTPIN4, DHTTYPE);
#define DEBUG FALSE //comment out to remove debug msgs
#define _baudrate 115200
#define _rxpin      2
#define _txpin      3
SoftwareSerial debug( _rxpin, _txpin ); // RX, TX
String GET = "GET /update?key=DJJ16EQ3W6IAATJD";
LiquidCrystal_I2C lcd(0x27, 16, 2);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
// Variable Defination
int  Vin = 0;
float Temperature;
float TF;
float TC;
float h1 = 0;
float t1 = 0;
float h2 = 0;
float t2 = 0;
float h3 = 0;
float t3 = 0;
float h4 = 0;
float t4 = 0;
float hum_avg = 0;
float Temp_avg = 0;
int Bed_wet = 0;
int cry = 0;
int pos = 0;
int NO_sensor = 4;
#define PROCESSING_VISUALIZER 1
#define SERIAL_PLOTTER  2

//  Variables
//int pulsePin = 0;                 // Pulse Sensor purple wire connected to analog pin 0
int blinkPin = 13;                // pin to blink led at each beat
int fadePin = 5;                  // pin to do fancy classy fading blink at each beat
int fadeRate = 0;                 // used to fade LED on with PWM on fadePin

// Volatile Variables, used in the interrupt service routine!
volatile int BPM;                   // int that holds raw Analog in 0. updated every 2mS
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // int that holds the time interval between beats! Must be seeded!
volatile boolean Pulse = false;     // "True" when User's live heartbeat is detected. "False" when not a "live beat".
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.


static int outputType = SERIAL_PLOTTER;


void setup() {
   Serial.begin( _baudrate );
//  debug.begin( _baudrate );
//  sendDebug("AT");
//  delay(5000);
//  if (Serial.find("OK"))
//  {
//    debug.println("RECEIVED: OK\nData ready to sent!");
//    Serial.println("OK");
//    connectWiFi();
//  }
  myservo1.attach(9);
  myservo2.attach(10);
  pinMode(Heater, OUTPUT);
  pinMode(FAN, OUTPUT);
  pinMode(Prammotor_C1, OUTPUT);
  pinMode(Prammotor_C2, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  dht1.begin();
  dht2.begin();
  dht3.begin();
  dht4.begin();
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);          // set cursor to column 0, row 0
  lcd.print("  RNSIT IT DEPT ");
  lcd.setCursor(0, 1);          // set cursor to column 0, row 1
  lcd.print(" NICU INCUBATOR");
  Serial.print("CARE CHAMP UNIT");
  // interruptSetup();
}

void loop() {
  Temp_read();
}

//void Temp_read()
//{
//  sensors.requestTemperatures();  
//  TC = sensors.getTempCByIndex(0);
//   Serial.print(TC );
//  Serial.print(" *C ");
//
//
//}
