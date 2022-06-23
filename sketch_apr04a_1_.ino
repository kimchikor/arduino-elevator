#include <hd44780.h>
#include <stdio.h>
#include <Wire.h>
#include <Stepper.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>
#include <Keypad.h>
const int stepsperRev = 2048;//스텝모터 돌아가는 정도 세팅 
hd44780_I2Cexp lcd;

Stepper stepper(stepsperRev,11,9,10,8);     
int one =2;
int two =3;
int thr =4;
int fl=1;//현재 층
const byte ROWS = 4; 
const byte COLS = 4; 
char hexaKeys[ROWS][COLS] = {
  {'0','1','2','3'},
  {'1','5','6','7'},
  {'2','9','a','b'},
  {'3','d','e','f'}
};
byte rowPins[ROWS] = { 22, 23, 24, 25 };
byte colPins[COLS] = {26, 27, 28, 29}; 
int a=0;
char customKey;

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
 
void setup() {
  //stepper.setSpeed(10);
  pinMode(one,INPUT);
  pinMode(two,INPUT);
  pinMode(thr,INPUT);
  lcd.begin(16,2);
  stepper.setSpeed(14);
  Serial.begin(9600);
  }

void keyPress();
void loop() {
    customKey = customKeypad.getKey();
  if(customKey){  //키 입력 신호가 있을때만 작동
    a=customKey-47;
  lcd.clear();
Serial.println(a);
  stepper.step(stepsperRev*(fl-a));
  fl=a;
  lcd.setCursor(7,0);
  lcd.print(fl);
  delay(10);
 
  }
}
