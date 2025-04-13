// sensor pin mapping
#define GAS A0  // analog read
#define PIR   2 // digital read
#define LDR1   A1
#define LDR2   A2
#define TEMP  A3
#define Intrud 3

// load pin mapping

#define Light1  6
#define Light2  7
#define FAN     8
#define gasBUZZER 9
#define IntBUZZER 10

// condition mapping
#define ON  HIGH
#define OFF  LOW

// initial values
int PIRval = 0;
int GAS_read = 0;
int LDRVal1;
int LDRVal2;


void setup() {
  Serial.begin(9600);

  pinMode(Light1, OUTPUT);//HALL
  pinMode(Light2, OUTPUT);//ROOM
  pinMode(gasBUZZER, OUTPUT);//GAS
  pinMode(IntBUZZER, OUTPUT);//GATE ALARM
  pinMode(Intrud, INPUT);//GATE SENSE
  pinMode(PIR, INPUT); // OCCUPANCY
}
void loop()
{
  sensor_control();// devices controlled based on sensor
  //App_control();// please write the code for app controlled using esp8266
}
void sensor_control() {
  GAS_DETECT();
  Hall_light();
  Room_light();
  Fan();
  Intrud_DETECT();
}
void GAS_DETECT()
{
  // sensorValue = analogRead(GAS);
  // GAS_read = map(sensorValue,0, 1023, 0, 255);
  GAS_read = map( analogRead(GAS), 0, 1023, 0, 255);
  if (GAS_read >= 120)
  {
    Serial.println("Gas Detected");
    //lcd.setCursor(0,1);
    //lcd.print("Gas Detected");
    delay(500);
    Serial.println(GAS_read);
    digitalWrite(gasBUZZER, ON);
  }
  else
  {
    Serial.println("Gas Not Detected");
    digitalWrite(gasBUZZER, OFF);
    //lcd.setCursor(0,1);
    //lcd.print("Gas Not Detected");
    delay(500);
    Serial.println(GAS_read);
  }
  delay(500);
  return;
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
  }
  else
  {
    digitalWrite(Light1, OFF);
    Serial.println("Hall Light OFF");
    delay(500);
    Serial.println(PIRval);
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
  }
  else
  {
    digitalWrite(Light2, OFF);
    delay(500);
    Serial.println("Room Light OFF");
    Serial.println(PIRval);
  }
  return;
}
void Fan()
{
  int PIRval = digitalRead(PIR);
  int TEMPval = analogRead(TEMP);
  int temp = ((4.68 * TEMPval * 100.0) / 1024);
  if (PIRval ==  HIGH && temp >= 30 )
  {
    digitalWrite(FAN, ON);
    Serial.println("PIR_read");
    Serial.println(PIRval);
    delay(500);
    Serial.println("FAN On");
    Serial.println("temp");
    Serial.println(temp);

  }
  else
  {
    digitalWrite(FAN, OFF);
    delay(500);
    Serial.println("PIR_read");
    Serial.println(PIRval);
    Serial.println("FAN OFF");
    Serial.println("temp");
    Serial.println(temp);
  }
  return;
}
void Intrud_DETECT()
{

  int IR_read = digitalRead(Intrud);
  if (IR_read == HIGH)
  {
    Serial.println("IR_read");
    Serial.println(IR_read);
    digitalWrite(IntBUZZER, ON);
  }
  else
  {
    digitalWrite(IntBUZZER, OFF);
    Serial.println("IR_read");
    Serial.println(IR_read);
  }
  delay(500);
  return;
}

