
#define M1_C1 2
#define M1_C2 3
#define M2_C1 4
#define M2_C2 5
int pin = 0;
void setup() {
  // initialize serial communication:
  Serial.begin(38400);
  pinMode(M1_C1, OUTPUT);
  pinMode(M1_C2, OUTPUT);
  pinMode(M2_C1, OUTPUT);
  pinMode(M2_C2, OUTPUT);
  pinMode(13, OUTPUT);

}

void loop() {
  // read the sensor:
  if (Serial.available() > 0) {
    int inByte = Serial.read();
    // do something different depending on the character received.
    // The switch statement expects single number values for each case; in this
    // example, though, you're using single quotes to tell the controller to get
    // the ASCII value for the character. For example 'a' = 97, 'b' = 98,
    // and so forth:

    switch (inByte) {
      case 'a':
        digitalWrite(M1_C1, LOW);
        digitalWrite(M1_C2, HIGH);
        digitalWrite(M2_C1, LOW);
        digitalWrite(M2_C2, HIGH);
        digitalWrite(13, HIGH);
        
        break;
      case 'b':
        digitalWrite(M1_C1, HIGH);
        digitalWrite(M1_C2, LOW);
        delay(1);
        digitalWrite(M2_C1, LOW);
        digitalWrite(M2_C2, HIGH);
        digitalWrite(13, LOW);
        break;
      case 'c':
        digitalWrite(M2_C1, HIGH);
        digitalWrite(M2_C2, LOW);
        delay(1);
        digitalWrite(M1_C1, LOW);
        digitalWrite(M1_C2, HIGH);
        break;
      case 'd':
        analogWrite(M1_C2, 0);
        digitalWrite(M1_C1, HIGH);
        analogWrite(M2_C2, 0);
        digitalWrite(M2_C1, HIGH);
        break;
      default:
        digitalWrite(M1_C1, HIGH);
        digitalWrite(M2_C1, HIGH);
        digitalWrite(M1_C2, HIGH);
        digitalWrite(M2_C2, HIGH);
    }
  }
}


