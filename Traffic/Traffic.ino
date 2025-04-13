#define Lane1_S1 A0
#define Lane1_S2 A1
#define Lane1_S3 A2
#define Lane2_S1 A3
#define Lane2_S2 A4
#define Lane2_S3 A5
#define Lane3_S1 A6
#define Lane3_S2 A7
#define Lane3_S3 A8
#define Lane1_R1 2
#define Lane1_G1 3
#define Lane1_B1 4
#define Lane2_R2 5
#define Lane2_G2 6
#define Lane2_B2 7
#define Lane3_R3 8
#define Lane3_G3 9
#define Lane3_B3 10
int Lane1_S1_Val = 0;
int Lane1_S2_Val = 0;
int Lane1_S3_Val = 0;
int Lane2_S1_Val = 0;
int Lane2_S2_Val = 0;
int Lane2_S3_Val = 0;
int Lane3_S1_Val = 0;
int Lane3_S2_Val = 0;
int Lane3_S3_Val = 0;
int Lane1_R1_pin = 2;
int Lane1_G1_pin = 3;
int Lane1_B1_pin = 4;
int Lane2_R2_pin = 5;
int Lane2_G2_pin = 6;
int Lane2_B2_pin = 7;
int Lane3_R3_pin = 8;
int Lane3_G3_pin = 9;
int Lane3_B3_pin = 10;
void setup()
{
  Serial.begin(9600);
  pinMode(Lane1_S1, INPUT);
  pinMode(Lane1_S2, INPUT);
  pinMode(Lane1_S3, INPUT);
  pinMode(Lane2_S1, INPUT);
  pinMode(Lane2_S2, INPUT);
  pinMode(Lane2_S3, INPUT);
  pinMode(Lane3_S1, INPUT);
  pinMode(Lane3_S2, INPUT);
  pinMode(Lane3_S3, INPUT);
  pinMode(Lane1_R1, OUTPUT);
  pinMode(Lane1_G1, OUTPUT);
  pinMode(Lane1_B1, OUTPUT);
  pinMode(Lane2_R2, OUTPUT);
  pinMode(Lane2_G2, OUTPUT);
  pinMode(Lane2_B2, OUTPUT);
  pinMode(Lane3_R3, OUTPUT);
  pinMode(Lane3_G3, OUTPUT);
  pinMode(Lane3_B3, OUTPUT);

}
void loop()
{
  IR_Read();
  //all lanes are high dense
  if ((Lane1_S1_Val == LOW && Lane1_S2_Val == LOW && Lane1_S3_Val == LOW) && (Lane2_S1_Val == LOW && Lane2_S2_Val == LOW && Lane2_S3_Val == LOW) && (Lane3_S1_Val == LOW &&
      Lane3_S2_Val == LOW && Lane3_S3_Val == LOW))
  {
    RGB_color_Lane1(255, 0, 0);

    RGB_color_Lane2(255, 255, 0);
    RGB_color_Lane3(0, 255, 0);
    delay(5000);
    RGB_color_Lane1(255, 255, 0);
    RGB_color_Lane2(0, 255, 0);
    RGB_color_Lane3(255, 0, 0);
    delay(5000);
    RGB_color_Lane1(0, 255, 0);
    RGB_color_Lane2(255, 0, 0);
    RGB_color_Lane3(255, 255, 0);
    delay(5000);
    //    lcd.setCursor(0,0);
    //  lcd.print("all lane are high dense");
  }
  //lane 1 and 2 are high dense
  else if ((Lane1_S1_Val == LOW && Lane1_S2_Val == LOW && Lane1_S3_Val == LOW) && (Lane2_S1_Val == LOW && Lane2_S2_Val == LOW && Lane2_S3_Val == LOW) && (Lane3_S1_Val == LOW &&
           Lane3_S2_Val == LOW && Lane3_S3_Val == HIGH))
  {
    RGB_color_Lane1(255, 0, 0);
    RGB_color_Lane2(255, 255, 0);
    RGB_color_Lane3(0, 255, 0);
    delay(5000);
    RGB_color_Lane1(255, 255, 0);
    RGB_color_Lane2(0, 255, 0);
    RGB_color_Lane3(255, 0, 0);
    delay(5000);
    RGB_color_Lane1(0, 255, 0);
    RGB_color_Lane2(255, 0, 0);
    RGB_color_Lane3(255, 255, 0);
    delay(4000);
    //    lcd.setCursor(0,0);
    //  lcd.print("lane 1 and 2 are high dense");
  }
  //lane 3 is high dense
  else if ((Lane1_S1_Val == LOW && Lane1_S2_Val == LOW && Lane1_S3_Val == LOW) && (Lane2_S1_Val == LOW && Lane2_S2_Val == LOW && Lane2_S3_Val == HIGH) && (Lane3_S1_Val == LOW &&
           Lane3_S2_Val == HIGH && Lane3_S3_Val == HIGH))
  {
    RGB_color_Lane1(255, 0, 0);
    RGB_color_Lane2(255, 255, 0);
    RGB_color_Lane3(0, 255, 0);
    delay(5000);
    RGB_color_Lane1(255, 255, 0);
    RGB_color_Lane2(0, 255, 0);
    RGB_color_Lane3(255, 0, 0);
    delay(4000);
    RGB_color_Lane1(0, 255, 0);
    RGB_color_Lane2(255, 0, 0);
    RGB_color_Lane3(255, 255, 0);
    delay(3000);
    //    lcd.setCursor(0,0);
    //  lcd.print("lane 1 is high dense");
  }
  //lane 1 and 3 is high dense
  else if ((Lane1_S1_Val == LOW && Lane1_S2_Val == LOW && Lane1_S3_Val == LOW) && (Lane2_S1_Val == LOW && Lane2_S2_Val == LOW && Lane2_S3_Val == HIGH) && (Lane3_S1_Val == LOW &&
           Lane3_S2_Val == LOW && Lane3_S3_Val == LOW))
  {
    RGB_color_Lane1(255, 0, 0);
    RGB_color_Lane2(255, 255, 0);
    RGB_color_Lane3(0, 255, 0);
    delay(5000);
    RGB_color_Lane1(255, 255, 0);
    RGB_color_Lane2(0, 255, 0);
    RGB_color_Lane3(255, 0, 0);
    delay(4000);
    RGB_color_Lane1(0, 255, 0);
    RGB_color_Lane2(255, 0, 0);
    RGB_color_Lane3(255, 255, 0);
    delay(5000);
    //    lcd.setCursor(0,0);
    //  lcd.print("lane 1 and 3 are high dense");
  }
  //lane 2 and 3 are high dense
  else if ((Lane1_S1_Val == LOW && Lane1_S2_Val == LOW && Lane1_S3_Val == HIGH) && (Lane2_S1_Val == LOW && Lane2_S2_Val == LOW && Lane2_S3_Val == LOW) && (Lane3_S1_Val == LOW &&
           Lane3_S2_Val == LOW && Lane3_S3_Val == LOW))
  {
    RGB_color_Lane1(255, 0, 0);
    RGB_color_Lane2(255, 255, 0);
    RGB_color_Lane3(0, 255, 0);
    delay(4000);
    RGB_color_Lane1(255, 255, 0);
    RGB_color_Lane2(0, 255, 0);
    RGB_color_Lane3(255, 0, 0);
    delay(5000);
    RGB_color_Lane1(0, 255, 0);
    RGB_color_Lane2(255, 0, 0);
    RGB_color_Lane3(255, 255, 0);
    delay(5000);
    //    lcd.setCursor(0,0);
    //  lcd.print("lane 2 and 3 are high dense");
  }
  //lane 2 is high dense
  else if ((Lane1_S1_Val == LOW && Lane1_S2_Val == LOW && Lane1_S3_Val == HIGH) && (Lane2_S1_Val == LOW && Lane2_S2_Val == LOW && Lane2_S3_Val == LOW) && (Lane3_S1_Val == LOW &&
           Lane3_S2_Val == LOW && Lane3_S3_Val == HIGH))
  {
    RGB_color_Lane1(255, 0, 0);
    RGB_color_Lane2(255, 255, 0);
    RGB_color_Lane3(0, 255, 0);
    delay(4000);
    RGB_color_Lane1(255, 255, 0);
    RGB_color_Lane2(0, 255, 0);
    RGB_color_Lane3(255, 0, 0);
    delay(5000);
    RGB_color_Lane1(0, 255, 0);
    RGB_color_Lane2(255, 0, 0);
    RGB_color_Lane3(255, 255, 0);
    delay(4000);

  }
  //lane 3 is high dense
  else if ((Lane1_S1_Val == LOW && Lane1_S2_Val == HIGH && Lane1_S3_Val == HIGH) && (Lane2_S1_Val == LOW && Lane2_S2_Val == LOW && Lane2_S3_Val == HIGH) && (Lane3_S1_Val == LOW &&
           Lane3_S2_Val == LOW && Lane3_S3_Val == LOW))
  {
    RGB_color_Lane1(255, 0, 0);
    RGB_color_Lane2(255, 255, 0);
    RGB_color_Lane3(0, 255, 0);
    delay(3000);
    RGB_color_Lane1(255, 255, 0);
    RGB_color_Lane2(0, 255, 0);
    RGB_color_Lane3(255, 0, 0);
    delay(4000);
    RGB_color_Lane1(0, 255, 0);
    RGB_color_Lane2(255, 0, 0);
    RGB_color_Lane3(255, 255, 0);
    delay(5000);
    //    lcd.setCursor(0,0);
    //  lcd.print("lane 3 is high dense");
  }

  //lane 1 and 2 is medium dense
  else if ((Lane1_S1_Val == LOW && Lane1_S2_Val == LOW && Lane1_S3_Val == HIGH) && (Lane2_S1_Val == LOW && Lane2_S2_Val == LOW && Lane2_S3_Val == HIGH) && (Lane3_S1_Val == LOW &&
           Lane3_S2_Val == HIGH && Lane3_S3_Val == HIGH))
  {
    RGB_color_Lane1(255, 0, 0);
    RGB_color_Lane2(255, 255, 0);
    RGB_color_Lane3(0, 255, 0);
    delay(4000);
    RGB_color_Lane1(255, 255, 0);
    RGB_color_Lane2(0, 255, 0);
    RGB_color_Lane3(255, 0, 0);
    delay(4000);
    RGB_color_Lane1(0, 255, 0);
    RGB_color_Lane2(255, 0, 0);
    RGB_color_Lane3(255, 255, 0);
    delay(3000);

  }
}
