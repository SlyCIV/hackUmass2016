#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;
const int pinAdc = A0;

int cR;
int cG;
int cB;

const int quiet = 50;
const int loud = 150;
//const int loudThreshold;
const int knockThreshold = 500;
const int ARRAYSIZE = 100;
int soundLevels[ARRAYSIZE]; //int array of all the sound levels in the past 100ms
int soundIndex; //index of soundLevels array

int sLvl; //current sound level
int average;
int total;
String dots;
int dotsCount;


void setup() 
{
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);

    cR = 255;
    cG = 150;
    cB = 0;
    lcd.setRGB(cR, cG, cB);
    for(int i = 0; i < ARRAYSIZE; i++){
      soundLevels[i] = 0;
    }    
    sLvl = 0;
    average = 0;
    total = 0;
    Serial.begin(115200);

    dots = ".";
    dotsCount = 1;
    delay(1000);
}

void loop() 
{
    sLvl = analogRead(pinAdc);
    
    //lowpass filter
    if(sLvl < 70){
      sLvl = 70;
    }
    total = total - soundLevels[soundIndex];
    soundLevels[soundIndex] = sLvl; //Adds sound level to the array at index soundIndex
    total = total + soundLevels[soundIndex];
    average = total/ARRAYSIZE;
    
    if(average>loud){
      printTooLoud();
      Serial.println("loud");

      //clears array
      for(int i = 0; i < ARRAYSIZE; i++){
      soundLevels[i] = 0;
      }
      total = 0;
      average = 0;
    }

    Serial.println(sLvl);
    updateColor(sLvl);
    printStats();

    //causes the index to loop from 1 - 99;
    soundIndex++;
    if(soundIndex >= 100){
      soundIndex = 0;
    }
    delay(100);
}

void printStats(){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Sound Level: ");
    lcd.print(sLvl);
    
    // prints average
    lcd.setCursor(0, 1);
    lcd.print("Ave:");
    //if average is less then quiet then the average is still building up, so it prints a dots animation
    if(average < quiet){
      lcd.print(dots);
      dots = dots +('.');
      dotsCount++;
      if(dotsCount>4){
        dots = "."; 
        dotsCount=1;}
    }else{
      lcd.print(average);
    }
    
    //prints Index
    lcd.setCursor(8, 2);
    lcd.print("Ind:");
    lcd.print(soundIndex);
}

void printTooLoud(){
    lcd.clear();
    lcd.setRGB(255, 0, 0);//Sets color to red
    //lcd.print("Too damn loud!");

    for(int i = 0; i < 10; i++){
      printStats();
      lcd.setRGB(255, 255, 255);
      delay(50);
      lcd.setRGB(255, 0, 0);
      delay(50);
    }
}

void updateColor(int soundLevel){
    int colorVal = (255 * (sLvl-quiet))/(loud - quiet);
    
    cR = colorVal;
    cB = 255 - colorVal;
    cG = colorVal;
    
    if(cR > 255){cR = 255;}
    if(cG > 255){cG = 255;}
    if(cB > 255){cB = 255;}

    if(cR < 0){cR = 0;}
    if(cG < 0){cG = 0;}
    if(cB < 0){cB = 0;}
    
    lcd.setRGB(cR, cG, cB);
}
