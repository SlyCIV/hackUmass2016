#include <memorysaver.h>
#include <UTFT.h>
#include <avr/pgmspace.h>

extern uint8_t BigFont[];

UTFT myGLCD(ITDB32S,A5,A4,A3,A2); //Creates the UTFT object

const int analogPin = 1;
const int tempPin = 3;
int sound = 0;
int knock = 0;

void setup(){
  Serial.begin(9600);
  pinMode(tempPin, INPUT);

  myGLCD.InitLCD(1); //Sets LCD to landscape mode
  myGLCD.setFont(BigFont); //Sets font to "SmallFont"
}

void loop() {

  sound = analogRead(analogPin);
  knock = digitalRead(tempPin);
  
  Serial.print("Sound: ");
  Serial.println(sound);
  Serial.print("knocker: ");
  Serial.println(knock);

  myGLCD.fillScr(0,0,0);
  myGLCD.setColor(255, 255, 255);
  myGLCD.print("Sound int: ",LEFT,200);
  myGLCD.printNum(sound, CENTER, 200);
  myGLCD.print("Knock int: ",LEFT,240);
  myGLCD.printNum(knock, CENTER, 240);

  myGLCD.drawRect(0,150,RIGHT,290);
  
  delay(800);

}

