

#include <Servo.h>  
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(15, 16, 4, 5, 6, 7);

Servo myservo;  // create servo object to control a servo
Servo myservor;  // create servo object to control a servo
Servo myservol;
                // a maximum of eight servo objects can be created 
int pos = 0;    // variable to store the servo position 
 
#define trigPin 13
#define echoPin 12
int buttonState = LOW;
int flag = 0;
int dir;
char data = 'S';
int cm;
int ir=0;
int count = 0;
int deg[] = {90, 150, 90, 40};
void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
    // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(0, 0);
  lcd.print("Welcome 2 b'bank");
  lcd.setCursor(0, 1);
  lcd.print("Enroll UR self");
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(2, HIGH);
  digitalWrite(7, HIGH);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  myservor.attach(10);  // attaches the servo on pin 10 to the servo object 
  myservol.attach(11);  // attaches the servo on pin 11 to the servo object 
  myservo.write(90);
  myservor.write(135);
  myservol.write(90); 
  stop();
}

void loop() 
{ 


for(int i=0; i<4; i++)
{
  if(flag == 0)
    pos = deg[i];
    Serial.println(pos);
    myservo.write(pos);
    delay(4000);
    cm = distance_sensor();
    Serial.println(cm);
     
if(pos == 90)
{
  sendsms();
    Serial.println("test");
    if( cm < 100)
    {
      //forward();
      if( cm <40 )
      {
        myservor.write(90);
        myservol.write(135);
        flag = 0;
            //delay(1000);
        delay(100);
        // clear the screen
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Plz pick, fill &");
        lcd.setCursor(7, 1);
        lcd.print("Drop");
        stop();
        delay(5000);
        myservor.write(135);
        myservol.write(90);
      }
      else
      {
        forward();
        flag = 1;
      }
    }
}
else if(pos == 150)
{
  sendsms();
  if( cm < 100)
  {
    right();
    Serial.println("right");
    delay(1000);
    stop();
    myservo.write(90);
  }
}
else if(pos == 40)
{
  sendsms();
  if(cm < 100)
  {
    left();
    Serial.println("left");
    delay(1000);
    stop();
    myservo.write(90);
  }
}
else
{
  Serial.println("stop");
}

}

}

int distance_sensor()
{
    long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  //Serial.println(distance);
  return distance;  
}
void left()
{
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  
}
void right()
{
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
}
void forward()
{
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
}
void stop()
{
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
} 
void sendsms()
{
  int ir = digitalRead(14);
  if( ir == HIGH)
  {
    //delay(1000);
    delay(100);
    // clear the screen
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Thank you for UR");
    lcd.setCursor(4, 1);
    lcd.print("Interest");
    count = count + 1;
    Serial.println(count);
    if(count == 5)
    {
      Serial.println("AT");
      delay(2000);
      Serial.println("AT+CMGF=1");
      delay(2000);
      Serial.println("AT+CMGS=\"9739060176\"");
      delay(2000);
      Serial.println(" drop box is full ");
      Serial.write(26);
      count = 0;
    }
   }

}

  
