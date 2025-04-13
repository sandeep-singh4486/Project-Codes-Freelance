#ifndef _PINS_H_
#define _PINS_H_
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <Wire.h> 
#include <SeeedOLED.h>
#include <avr/pgmspace.h>
#include <stdlib.h>
#include <MPU6050_tockn.h>
MPU6050 mpu6050(Wire);
#define _rxpin      2
#define _txpin      3
//#define SSID "dhruva"
//#define PASS "dhruva111"
SoftwareSerial debug( _rxpin, _txpin );
SoftwareSerial mySerial1(8, 9);
SoftwareSerial mySerial(10, 11); // gsm rx=11 gsm tx= 10
//   Connect the GPS TX (transmit) pin to Digital 8
//   Connect the GPS RX (receive) pin to Digital 9
Adafruit_GPS GPS(&mySerial1);
#define GPSECHO  false
boolean usingInterrupt = false;
void useInterrupt(boolean);
#define IP "184.106.153.149" // ThingSpeak IP Address
String GET = "GET /update?key=JHBZUVVN47MVDXGY";// GET /update?key=[THINGSPEAK_KEY]&field1=[data 1]&field2=[data 2]...;
#define SSID "dhruva"
#define PASS "dhruva111"

#define PROCESSING_VISUALIZER 1
#define SERIAL_PLOTTER  2
// int LAT=0;
// int LON=0;
//  Variables
int pulsePin = 0;                 // Pulse Sensor purple wire connected to analog pin 0
//int blinkPin = 13;                // pin to blink led at each beat
//int fadePin = 5;                  // pin to do fancy classy fading blink at each beat
int fadeRate = 0;                 // used to fade LED on with PWM on fadePin
// Volatile Variables, used in the interrupt service routine!
volatile int BPM,BPM1;                   // int that holds raw Analog in 0. updated every 2mS
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // int that holds the time interval between beats! Must be seeded!
volatile boolean Pulse = false;     // "True" when User's live heartbeat is detected. "False" when not a "live beat".
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.
static int outputType = SERIAL_PLOTTER;

#define touch1 4
#define touch2 5
#define touch3 6
#define touch4 7
#define switch1 12
unsigned char Brightness = 255; 

#endif /* _PINS_H_ */
