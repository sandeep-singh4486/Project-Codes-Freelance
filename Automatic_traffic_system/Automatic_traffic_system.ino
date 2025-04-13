////please see the comment on every case
// you can consider any number cases u need
//else if (IR# == HIGH && IR# == HIGH)  #:number,high/low based on calibration
//
//
//

int red1=     2;
int green1=   3;
int red2=     4;
int green2=   5;
int red3=     6;
int green3=   7;
int buzzer=   8;
int value =HIGH;


void setup() {
  Serial.begin (9600);
pinMode(A0, INPUT);
pinMode(A1, INPUT);
pinMode(A2, INPUT);
pinMode(A3, INPUT);
pinMode(A4, INPUT);
pinMode(A5, INPUT);
pinMode(red1, OUTPUT);
pinMode(green1, OUTPUT);
pinMode(red2, OUTPUT);
pinMode(green2, OUTPUT);
pinMode(red3, OUTPUT);
pinMode(green3, OUTPUT);
pinMode(buzzer, OUTPUT);
}

void loop() 
{

 int IR1 = digitalRead(A0); // lane1 less density
  int IR2 = digitalRead(A1); // lane1 high density
  int IR3 = digitalRead(A2);//  lane2 less density
  int IR4 = digitalRead(A3);//  lane2 high density
  int IR5 = digitalRead(A4);//  lane3 less density
  int IR6 = digitalRead(A5);//  lane3 high density
// 
if(IR2 == HIGH) // CASE1: LANE1 HIGH DENSITY only
  {
    digitalWrite(red1, HIGH);
    digitalWrite(red2, LOW);
    digitalWrite(red3, LOW);
    digitalWrite(green1, LOW);
    digitalWrite(green2, HIGH);
    digitalWrite(green3, HIGH);
   Serial.println("Release lane1,close other");
  }
   else if (IR4 == HIGH)//CASE2: LANE2 HIGH DENSITY only
   {
    digitalWrite(red1, LOW);
    digitalWrite(red2, HIGH);
    digitalWrite(red3, LOW);
    digitalWrite(green1, HIGH);
    digitalWrite(green2, LOW);
    digitalWrite(green3, HIGH);
   Serial.println("Release lane2,close other lane");
  }
else if (IR6 == HIGH) //CASE3: LANE3 HIGH DENSITY only
{
    digitalWrite(red1, LOW);
    digitalWrite(red2, LOW);
    digitalWrite(red3, HIGH);
    digitalWrite(green1, HIGH);
    digitalWrite(green2, HIGH);
    digitalWrite(green3, LOW);
    Serial.println("Release lane3,close other lane");
}
 else if (IR2 == HIGH && IR4 == HIGH) // if lane one  and  lane2  has high density then
   {
     Serial.println("priority rule 1");
   digitalWrite(red1, HIGH);
    digitalWrite(red2, LOW);
    digitalWrite(red3, LOW);
    digitalWrite(green1, LOW);
    digitalWrite(green2, HIGH);
    digitalWrite(green3, HIGH);
     Serial.println("Release lane1,close other");
         delay(7000);
    digitalWrite(red1, LOW);
    digitalWrite(red2, LOW);
    digitalWrite(red3, HIGH);
    digitalWrite(green1, HIGH);
    digitalWrite(green2, HIGH);
    digitalWrite(green3, LOW);
     Serial.println("Release lane2,close other lane");
     delay(7000);
    digitalWrite(red1, HIGH);
    digitalWrite(red2, LOW);
    digitalWrite(red3, LOW);
    digitalWrite(green1, LOW);
    digitalWrite(green2, HIGH);
    digitalWrite(green3, HIGH);
      Serial.println("Release lane3,close other lane");
     delay(3000);
  }
else {
    Serial.println("sequential time");
    delay(500);
    digitalWrite(red1, HIGH);
    digitalWrite(red2, LOW);
    digitalWrite(red3, LOW);
    digitalWrite(green1, LOW);
    digitalWrite(green2, HIGH);
    digitalWrite(green3, HIGH);
     Serial.println("Release lane1,close other");
         delay(10000);
    digitalWrite(red1, LOW);
    digitalWrite(red2, LOW);
    digitalWrite(red3, HIGH);
    digitalWrite(green1, HIGH);
    digitalWrite(green2, HIGH);
    digitalWrite(green3, LOW);
     Serial.println("Release lane2,close other lane");
     delay(10000);
    digitalWrite(red1, HIGH);
    digitalWrite(red2, LOW);
    digitalWrite(red3, LOW);
    digitalWrite(green1, LOW);
    digitalWrite(green2, HIGH);
    digitalWrite(green3, HIGH);
      Serial.println("Release lane3,close other lane");
     delay(10000);
   
 }
}


