void reading() {
  sensor = 0; //this is to refresh initial value
  sum = 0;
  for (int i = 0; i < 6; i++)  (i < 4) ? s[i] = analogRead(i) : s[i] = analogRead(i + 2);
  for (int i = 5; i >= 0; i--) {
    (s[i] > mid[i]) ? s[i] = 1 : s[i] = 0; //conditional statement. this is to convert analog value to digital. if you want to see real analog value, then comment it. but for line follow, you must uncomment it.
    sensor += s[i] * base[i]; //this is to merge all 6 values and imagine them in a single binary number. then i converted it into decimal number to use as final value. better search about base convertion
    sum += s[i]; //finds out total count of sensor
  }
}
void cal() {
  for (int i = 0; i < 6; i++) {
    maximum[i] = 0;
    minimum[i] = 1023;
  }
  motor(100, -100);
  for (int i = 0; i < 5000 ; i++) {
    for (int i = 0; i < 6; i++)  (i < 4) ? s[i] = analogRead(i) : s[i] = analogRead(i + 2);
    for (int i = 5 ; i >= 0 ; i--)
    {
      maximum[i] = max(maximum[i], s[i]);
      minimum[i] = min(minimum[i], s[i]);
    }
  }
  motor(0, 0);
  for (int i = 0; i < 6; i++) {
    mid[i] = (maximum[i] + minimum[i]) / 2;
    EEPROM.write(i, mid[i] / 4); delay(10);
    EEPROM.write(i + 6, maximum[i] / 4); delay(10);
    EEPROM.write(i + 12, minimum[i] / 4); delay(10);
  }
}
/*void digital_reading() {
  lcd.backlight();
  while (1) {
    reading();
    lcd.setCursor(0, 0);
    for (int i = 5 ; i >= 0 ; i--)
    lcd.print(String(s[i]) + " ");
  }
}
void analog_reading() {
  lcd.backlight();
  while (1) {
    lcd.setCursor(0, 0);
    for (int i = 0; i < 6; i++)  (i < 4) ? s[i] = analogRead(i) : s[i] = analogRead(i + 2);
    for (int i = 0; i < 3 ; i++) {
      lcd.print(String(s[i]) + " ");
    }
    lcd.setCursor(0, 1);
    for (int i = 3; i < 6 ; i++) {
      lcd.print(String(s[i]) + " ");
    }
  }
}*/
void recording() {
  for (byte i = 0;; i++) {
    EEPROM.write(i + 30, path[i]); delay(10);
    if (path[i] == 5) return;
  }
}
