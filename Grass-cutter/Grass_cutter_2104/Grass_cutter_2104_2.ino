/*
* Ultrasonic Sensor HC-SR04 and Arduino Tutorial
*
* Crated by Dejan Nedelkovski,
* www.HowToMechatronics.com
*
*/
// defines pins numbers
const int trigPin = 7;
const int echoPin = 6;
const int trigPin1 = 9;
const int echoPin1 = 8;
#define M1_C1 2
#define M1_C2 3
#define M2_C1 4
#define M2_C2 5
#define Pump 8
// defines variables
long duration;
int distance,distance_g;
int left_right=0;
long int count_turn=0;
void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin1, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
pinMode(M1_C1, OUTPUT);
  pinMode(M1_C2, OUTPUT);
  pinMode(M2_C1, OUTPUT);
// pinMode(M2_C2, OUTPUT);
  pinMode(Pump, OUTPUT);
}
void loop() {
  forward();
  distance_sensor();
  distance_sensor1();
  count_turn=0;
 if(distance_g>30)//if (distance_g <= 1 || distance_g <= 10) 
 {

  Stop();
   if(left_right == 0)
    {
      //left_right=1;
      Right();
      delay(890);
    //  for(int i=0;i<100;i++)
    //  {
    //  forward();
    //  }
      //delay(00);
    //   Right ();
     //   delay(890);
     // count_turn++;
    }
    else
    {
      //left_right=0;
      Left ();
      delay(1150);
    //    for(int i=0;i<100;i++)
     // {
     // forward();
     // }
     // delay(500);
       //Left ();
       // delay(1150);
     // count_turn++;
    }
      distance_sensor1();
    if(distance_g>30) // if (distance_g <= 1 || distance_g <= 10) 
      {
        if(left_right == 0)
    {
      left_right=1;
     // Right();
     // delay(890);
     // for(int i=0;i<100;i++)
     // {
     // forward();
    //  }
      //delay(00);
       Left ();
        delay(2000);
        forward();
        delay(100);
        Left ();
        delay(1000);
     // count_turn++;
    }
    else
    {
      left_right=0;
      //Left ();
     // delay(1150);
    //    for(int i=0;i<100;i++)
     // {
     // forward();
     // }
     // delay(500);
       //Left ();
       // delay(1150);
     // count_turn++;
     Right();
     delay(1600);
      forward();
        delay(100);
        Right();
     delay(1600);
    }
      }
  
 }
 if (distance <= 1 || distance <= 10)
  {
    
    //left_right=!left_right;
  //  while(distance <= 1 || distance <= 30)
    {
    if(left_right == 0)
    {
      left_right=1;
      Right();
      delay(890);
      for(int i=0;i<100;i++)
      {
      forward();
      }
      //delay(00);
       Right ();
        delay(890);
     // count_turn++;
    }
    else
    {
      left_right=0;
      Left ();
      delay(1150);
        for(int i=0;i<100;i++)
      {
      forward();
      }
     // delay(500);
       Left ();
        delay(1150);
     // count_turn++;
    }
  // distance_sensor();
    }
    
    Stop();
  /*     if(left_right == 0)
    {
      Left();
     // count_turn++;
    }
    else
    {
      Right ();
      //count_turn++;
    }
 Serial.println(count_turn);
   
   // for(int x=0;x<count_turn;x++)
   // {
      for(int c=0;c<count_turn;c++)
      {
      delayMicroseconds(10);
         distance_sensor();
         if (distance <= 1 || distance <= 10)
         break;
      }
   // }
     Stop();
    */
  }
}

void distance_sensor()
{
 
 // Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("OBSTACLE ");
Serial.println(distance);
}
void distance_sensor1()
{
 
 // Clears the trigPin
digitalWrite(trigPin1, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin1, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin1, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin1, HIGH);
// Calculating the distance
distance_g= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
}
void forward()
{
  //analogWrite(M1_C1, 128);
    digitalWrite(M1_C1, LOW);
  digitalWrite(M1_C2, HIGH);
 // analogWrite(M2_C1, 128);
digitalWrite(M2_C1, LOW);
  digitalWrite(M2_C2, HIGH);
  
  Serial.println("forward ");
  
   
  // delay(5);
//digitalWrite(M1_C1, HIGH);
 //  digitalWrite(M2_C1, HIGH);
  // delay(5);
}
void Right()
{
  digitalWrite(M1_C1, HIGH);
  digitalWrite(M1_C2, LOW);
  delay(1);
  digitalWrite(M2_C1, LOW);
  digitalWrite(M2_C2, HIGH);
  Serial.println("Right ");

}
void Left ()
{
  digitalWrite(M2_C1, HIGH);
 digitalWrite(M2_C2, LOW);
 delay(1);
 digitalWrite(M1_C1, LOW);
 digitalWrite(M1_C2, HIGH);
  Serial.println("Left ");

}

void Stop()
{
  digitalWrite(M1_C1, HIGH);
  digitalWrite(M2_C1, HIGH);
  digitalWrite(M1_C2, HIGH);
  digitalWrite(M2_C2, HIGH);
  Serial.println("Stop ");

}
void Reverse()
{
  analogWrite(M1_C2, 0);
  digitalWrite(M1_C1, HIGH);
  analogWrite(M2_C2, 0);
  digitalWrite(M2_C1, HIGH);
  Serial.println("Reverse ");

}
void delayinseconds(long int x)
{
  for (int i=0;i<x;i++)
    for(int j=0;j<1000;j++)
    {
     delayMicroseconds(1);
    }
}

