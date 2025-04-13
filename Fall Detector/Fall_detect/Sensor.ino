void lcd_display()
{
  mpu6050.update();
  SeeedOled.setBrightness(Brightness);
  SeeedOled.setTextXY(1, 0);
  SeeedOled.putString("Heart Rate=");
  // SeeedOled.putString(BPM);

}

void temperature()
{
  mpu6050.update();

  float tem = mpu6050.getTemp();
  String TEMP = String(mpu6050.getTemp());
  SeeedOled.setBrightness(Brightness);
  SeeedOled.setTextXY(2, 0);
  SeeedOled.putString("Body Temp=");
  SeeedOled.putString("tem");

}


