#include<EEPROM.h>
//#include <LiquidCrystal_I2C.h>
//LiquidCrystal_I2C lcd(0x27, 16, 2);
#define left_motor_forward 4
#define left_motor_backward 5
#define right_motor_forward 7
#define right_motor_backward 8
#define left_motor_speed 3
#define right_motor_speed 11
#define light 13
#define spl 13 //left motor speed coeficient
#define spr 13 //right motor speed coeficient
#define node_delay 135
#define stop_timer 60
#define u_turn_delay 175
#define brake_time 42
#define turn_brake 83
char side = 'r';
char flag = 's';
int pos;
char cross = 's';
byte path[50];
byte counter = 0;
uint32_t m1, m2;
int s[6];
int mid[6], maximum[6], minimum[6];
int base[6] = {1, 2, 4, 8, 16, 32}; //this is for binary to decimal conversion
int sensor; //this is to store final value after binary conversion
int sum = 0; //this is to store the count of detected sensor
void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 6; i++) {
    mid[i] = EEPROM.read(i) * 4;
    maximum[i] = EEPROM.read(i + 6) * 4;
    minimum[i] = EEPROM.read(i + 12) * 4;
    Serial.println(String(maximum[i]) + " " + String(mid[i]) + " " + String(minimum[i]));
  }
  pinMode(left_motor_forward, OUTPUT);
  pinMode(left_motor_backward, OUTPUT);
  pinMode(left_motor_speed, OUTPUT);
  pinMode(right_motor_forward, OUTPUT);
  pinMode(right_motor_backward, OUTPUT);
  pinMode(right_motor_speed, OUTPUT);
  pinMode(light, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  //lcd.init();
}
void loop() {
  int r = button_read();
  if (r != 0) {
    if (r == 1) maze_scan(0); //scan the maze and stop at the ending point
    else if (r == 2) maze_scan(1); //solve maze from ending point
    else if (r == 3) maze_solving(0); //solve maze from start
    else if (r == 4) maze_solving(1); //solve maze from ending point
  }
  r = button_read_2();
  if (r != 0) {
    if (r == 1) cal();
    //else if (r == 2) digital_reading();
    //else if (r == 3) analog_reading();
    else if (r == 2)motor(10 * spl, 10 * spr);
    else if (r == 3) for (byte i = 0; EEPROM.read(i + 30) != 5; i++) Serial.println(EEPROM.read(i + 30));
  }
}
/*

  void eeprom() {
  while (1) {
    lcd.backlight();
    lcd.setCursor(0, 0);
    for (int i = 0; i < 1; i++) {
      mid[i] = EEPROM.read(i) * 4;
      maximum[i] = EEPROM.read(i + 6) * 4;
      minimum[i] = EEPROM.read(i + 12) * 4;
      lcd.print(String(maximum[i]) + " " + String(mid[i]) + " " + String(minimum[i]));
    }
    lcd.setCursor(0, 1);
    for (int i = 1; i < 2; i++) {
      mid[i] = EEPROM.read(i) * 4;
      maximum[i] = EEPROM.read(i + 6) * 4;
      minimum[i] = EEPROM.read(i + 12) * 4;
      lcd.print(String(maximum[i]) + " " + String(mid[i]) + " " + String(minimum[i]));
    }
    delay(1000);
    lcd.setCursor(0, 0);
    for (int i = 2; i < 3; i++) {
      mid[i] = EEPROM.read(i) * 4;
      maximum[i] = EEPROM.read(i + 6) * 4;
      minimum[i] = EEPROM.read(i + 12) * 4;
      lcd.print(String(maximum[i]) + " " + String(mid[i]) + " " + String(minimum[i]));
    }
    lcd.setCursor(0, 1);
    for (int i = 3; i < 4; i++) {
      mid[i] = EEPROM.read(i) * 4;
      maximum[i] = EEPROM.read(i + 6) * 4;
      minimum[i] = EEPROM.read(i + 12) * 4;
      lcd.print(String(maximum[i]) + " " + String(mid[i]) + " " + String(minimum[i]));
    }
    delay(2000);
    lcd.setCursor(0, 0);
    for (int i = 4; i < 5; i++) {
      mid[i] = EEPROM.read(i) * 4;
      maximum[i] = EEPROM.read(i + 6) * 4;
      minimum[i] = EEPROM.read(i + 12) * 4;
      lcd.print(String(maximum[i]) + " " + String(mid[i]) + " " + String(minimum[i]));
    }
    lcd.setCursor(0, 1);
    for (int i = 5; i < 6; i++) {
      mid[i] = EEPROM.read(i) * 4;
      maximum[i] = EEPROM.read(i + 6) * 4;
      minimum[i] = EEPROM.read(i + 12) * 4;
      lcd.print(String(maximum[i]) + " " + String(mid[i]) + " " + String(minimum[i]));
    }
  }
  }*/
