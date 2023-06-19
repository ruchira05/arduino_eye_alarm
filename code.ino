#include "SoftwareSerial.h"
#include <LiquidCrystal.h>
const int rs = 7, en = 9, d4 = 8, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
SoftwareSerial serial_connection(2, 3);//Create a serial connection with TX and RX on these pins
int led_pin = 11;
#define switch A0
char inChar=-1;//Initialie the first character as nothing
int count =0;
void setup()
{
  lcd.begin(16, 2);
  pinMode(11, OUTPUT);
  Serial.begin(9600);//Initialize communications to the serial monitor in the Arduino IDE
  Serial.println("Started");//Tell the serial monitor that the sketch has started.
  lcd.setCursor(1 , 0 );
  lcd.print("Project Name");
  delay(1000);
}
void loop()
{
  byte byte_count=serial_connection.available();//This gets the number of bytes that were sent by the python script
  if(byte_count)//If there are any bytes then deal with them
  {
    Serial.println("Incoming Data");//Signal to the monitor that something is happening
    inChar=serial_connection.read();//Read one byte
    while(inChar == '1'){
      digitalWrite(led_pin,LOW);
      clr(2);
      lcd.setCursor(1 , 1 );
      lcd.print("Drive Safe");
      // delay(1000);
      inChar=serial_connection.read();//Read one byte
      while(inChar != '1' && count < 10){
        inChar=serial_connection.read();//Read one byte
        delay(200);
        count++;
        Serial.println(count);
      }
      count = 0;
    }
    Serial.println(inChar);//Print to the monitor what was detected
  }
  while (1){
    digitalWrite(led_pin, HIGH);
    clr(2);
    lcd.setCursor(1 , 1 );
    lcd.print("SLEEP WARNING!");
    int val = digitalRead(switch);
    delay(20);
    if(val == HIGH)
      break;
  } 
}
void clr(int x) {
  lcd.setCursor(7, x-1);
  lcd.setCursor(0,x-1);
  lcd.print("                   ");
}
