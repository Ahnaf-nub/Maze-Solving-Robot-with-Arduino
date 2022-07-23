int button_read() {
  int cl = 0;
p:  int t = 0;
  if (digitalRead(2) == 0) {
    digitalWrite(light, HIGH);
    while (digitalRead(2) == 0) {
      delay(1); t++;
    }
    digitalWrite(light, LOW);
    if (t > 15) {
      t = 0; cl++;
      while (digitalRead(2) == HIGH) {
        delay(1); t++;
        if (t > 1000) return cl;
      }
      goto p;
    }
  }
  return cl;
}
int button_read_2() {
  int cl = 0;
p:  int t = 0;
  if (digitalRead(12) == 0) {
    digitalWrite(light, HIGH);
    while (digitalRead(12) == 0) {
      delay(1); t++;
    }
    digitalWrite(light, LOW);
    if (t > 15) {
      t = 0; cl++;
      while (digitalRead(12) == HIGH) {
        delay(1); t++;
        if (t > 1000) return cl;
      }
      goto p;
    }
  }
  return cl;
}
