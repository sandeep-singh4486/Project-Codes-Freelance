                    #include <LiquidCrystal.h>
                    #include <Servo.h>
                    
                    String readString;
                            
                  LiquidCrystal lcd( 12, 11, 5, 4, 3, 2);
                  
                    Servo            SERVO ;
                   void setup()
                  {
                    Serial.begin(9600);
                    analogReference(EXTERNAL);
                    lcd.begin(16, 2);
                    SERVO.attach(10);
                    lcd.clear();
                     lcd.setCursor(0,0);
                     lcd.print("Initializing....");
                     lcd.setCursor(0,1);
                     lcd.print("Sensors..:).Wait.");
                     //SERVO.write(90);
                   // Serial.println("AT\r"); //To check if GSM module is working
                    delay(2000);
                    //SERVO.write(0);
                    //Serial.println("AT+CMGF=1\r");
                    //delay(1000);// set the SMS mode to text
                    //Serial.println("AT+CNMI=1,1,0,0,0\r"); 
                    delay(1000); 
                    pinMode(6,OUTPUT);
                    pinMode(7,OUTPUT);
                    pinMode(8,OUTPUT);
                    pinMode(9,OUTPUT);
                    pinMode(13,INPUT);   
                  }
                  
                  void loop()
                  {
                   int TEMP_read = analogRead(0);                                                                              
                   float temp = ((4.3 * TEMP_read * 100.0) / 1024);
                   //float temp = (TEMP_read/ 1024)*5000;
                   //float cel= temp/10;
                   lcd.clear();
                   lcd.setCursor(0,0);
                   lcd.print("TempC:");
                   lcd.println(temp);
                   //Serial.println(TEMP_read);
                   //Serial.println(cel);
                   
                   int GAS_read = analogRead(1);
                   if(GAS_read >= 300)
                     {
                     lcd.setCursor(0,1);
                     lcd.print("Gas Detected");
                     delay(1000);
                     }
                   if(GAS_read <= 300)
                     {
                     lcd.setCursor(0,1);
                     lcd.print("Gas Not Detected");
                     delay(1000);
                     }
                     
                     int LDR_read = analogRead(2);
                     lcd.clear();
                     lcd.setCursor(0,0);
                     lcd.print("Light:");
                     lcd.print(LDR_read);
                     delay(1000);
                     
                     if(digitalRead(13) ==  HIGH)
                     {
                       //lcd.clear();
                       lcd.setCursor(0,1);
                       lcd.print("Motion Detected");
                       //Serial.println("Motion Detected");
                       delay(1000);
                     }
                     
                      while (Serial.available()) 
                     {
                       
                         delay(3);  
                            char c = Serial.read();
                            readString += c;     
                     }
                     delay(1000);
                     if (readString.length() >0) 
                     {
                       if(readString.indexOf("LOAD1ON") >=0)
                        {
                          LOAD1_ON();
                          readString = 0;
                        } 
                        
                          if(readString.indexOf("LOAD1OFF") >=0)
                            {
                              LOAD1_OFF();
                              readString =0;
                            }
                          if(readString.indexOf("LOAD2ON") >=0)
                            {
                              LOAD2_ON();
                              readString =0;
                            }
                            if(readString.indexOf("LOAD2OFF") >=0)
                            {
                              LOAD2_OFF();
                              readString =0;
                            }
                            if(readString.indexOf("LOAD3ON") >=0)
                            {
                              LOAD3_ON();
                              readString =0;
                            }
                            if(readString.indexOf("LOAD3OFF") >=0)
                            {
                              LOAD3_OFF();
                              readString =0;
                            }
                             if(readString.indexOf("LOAD4ON") >=0)
                            {
                              LOAD4_ON();
                              readString =0;
                            }
                             if(readString.indexOf("LOAD4OFF") >=0)
                            {
                              LOAD4_OFF();
                              readString =0;
                            }
                             if(readString.indexOf("DOPEN") >=0)
                            {
                              DOPEN();
                              readString =0;
                            }
                             if(readString.indexOf("DCLOSE") >=0)
                            {
                              DCLOSE();
                              readString =0;
                            }
                             if(readString.indexOf("STATUS") >=0)
                            {
                              TEMPERATURE();
                              GAS_Sensor();
                              PIR_Sensor();
                              LOADS_Status();
                            
                              readString =0;
                            }
                            if(readString.indexOf("status") >=0)
                            {
                              delay(1000);
                              Serial.println("AT+CMGS=\"9167433489\"\r");
                              delay(2000);
                              TEMPERATURE();
                              GAS_Sensor();
                              PIR_Sensor();
                              LOADS_Status();
                              delay(1000);
                              Serial.write(26);
                              delay(5000);
                              Serial.print("AT+CMGD=1");
                              Serial.println("\r");
                              delay(500);
                              readString =0;
                            }
                            if(readString.indexOf("+CMTI:") >=0)
                            {
                              SMS_Read();
                              
                            }
                     }
                 }
                  
                  
                   
                   void LOAD1_ON()
                   { 
                      digitalWrite(6,HIGH);
                      Serial.println("LOAD1=ON");
                      
                      return;
                   }
                   void LOAD1_OFF()
                   {
                       
                      digitalWrite(6,LOW);
                      Serial.println("LOAD1=OFF");
                      return;
                   }
                   void LOAD2_ON()
                   {
                      Serial.println("LOAD2=ON"); 
                      digitalWrite(7,HIGH);
                      return;
                   }
                   void LOAD2_OFF()
                   {
                       
                      digitalWrite(7,LOW);
                      Serial.println("LOAD2=OFF");
                      return;
                   }
                   void LOAD3_ON()
                   {
                       
                      digitalWrite(8,HIGH);
                      Serial.println("LOAD3=ON");
                      return;
                   }
                   void LOAD3_OFF()
                   {
                       
                      digitalWrite(8,LOW);
                      Serial.println("LOAD3=OFF");
                      return;
                   }
                   void LOAD4_ON()
                   {
                       
                      digitalWrite(9,HIGH);
                      Serial.println("LOAD4=ON");
                      return;
                   }
                   void LOAD4_OFF()
                   {
                      
                      digitalWrite(9,LOW);
                       Serial.println("LOAD4=OFF");
                      return;
                   }
                   void DCLOSE()
                   {
                      Serial.println("DOOR Closed"); 
                      SERVO.write(90);
                      delay(500);
                      return;
                   }
                   void DOPEN()
                   {
                      Serial.println("Door open");
                      SERVO.write(0);
                      delay(500);
                      return;
                   }
                   
                   
                   void TEMPERATURE()
                   {
                   int TEMP_read = analogRead(0);
                   float temp = ((4.68 * TEMP_read * 100.0) / 1024);                                                                                                                                                                                                                   
                   Serial.print("TempC:");
                   Serial.println(temp);
                   
                   delay(500);
                   return;
                   }
                   
                   void GAS_Sensor()
                   {
                   int GAS_read = analogRead(1);
                   
                   if(GAS_read >= 300)
                     {
                     Serial.println("Gas Detected");
                     //lcd.setCursor(0,1);
                     //lcd.print("Gas Detected");
                     //delay(500);
                     }
                   if(GAS_read <= 300)
                     {
                     Serial.println("Gas Not Detected");
                     //lcd.setCursor(0,1);
                     //lcd.print("Gas Not Detected");
                     //delay(500);
                     }
                     delay(500);
                     return;
                     
                   }
                   
                    void PIR_Sensor()
                    {
                   if(digitalRead(13) ==  HIGH)
                     {
                       Serial.println("Motion Detected");
                     }
                   else
                       {
                         Serial.println("NO Motion");
                       }
                       return;
                    }
                    
                    
                   void LOADS_Status()
                   {
                     if(digitalRead(6) == HIGH)
                     {
                        Serial.print("Load1=ON"); 
                     }  
                     else 
                     {
                       Serial.println("Load1=OFF");
                     }
                     if(digitalRead(7) == HIGH)
                       {
                         Serial.print("Load2=ON");
                       }
                       else
                       {
                         Serial.println("Load2=OFF");
                       }
                       if(digitalRead(8) == HIGH)
                       {
                         Serial.print("Load3=ON");
                       }
                       else
                       {
                         Serial.println("Load3=OFF");
                       }
                       if(digitalRead(9) == HIGH)
                       {
                         Serial.print("Load4=ON");
                       }
                       else
                       {
                         Serial.print("Load4=OFF");
                       }
                     return;
                   }  
                   void SMS_Read()
                   {
                       readString =0;
                       delay(500);
                      Serial.println("AT+CMGR=1\r");
                     delay(5000);
                     return;
                   }
