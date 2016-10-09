#include <SevSeg.h>

SevSeg sevseg;

const int analogPin = 1;
const int tempPin = 3;
const int threshHold = 300; //Sound threshold
const int increments = 30; //Size of array and stuff

int soundLevel = 0;
int count = 0;
int successcount = 30;
int total = 0;
int a[increments];
boolean once;

void setup() {
 byte numDigits = 4; 
 byte digitPins[] = {10, 11, 12, 13};
 byte segmentPins[] = {2, 3, 4, 5, 6, 7, 8, 9};

  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(90);
  
  Serial.begin(9600);
  //pinMode(tempPin, INPUT);

  fillArrayA();
}

void loop() {
  soundLevel = analogRead(analogPin);
  
  Serial.print("Sound: ");
  Serial.println(soundLevel);
  //Serial.print("knocker: ");
  //Serial.println(digitalRead(tempPin));

  sevseg.setNumber(flip(soundLevel) ,0);

  a[count] = thresh(soundLevel);
  count++;

  total = sumOfA();
  Serial.print("Total: ");
  Serial.println(total);

  if(count == 50){
    count = 0;
  }

  //Sounds our text if we're loud
  if(total == 10){
    Serial.println("Pattern: loud");
    delay(10000);
  }

  //Knock
  if(total <= 7 && total >= 4){
    successcount--;
    if(successcount == 0){
      Serial.println("Pattern: knock");
      delay(10000);
      successcount = 10;
    }
  }

  if(total == 0){
    successcount = 10;
  }

  //Maintains a value 
  for(int i = 0; i<10; i++){
  delay(1);
  sevseg.refreshDisplay();
  }
}

  
//Takes in input x and flips it. {1234} becomes {4321} (This code was written because our display was not working correctly)
int flip(int x){
  int a = x%10;
  x -= a;
  x /= 10;
  int b = x%10;
  x -= b;
  x /= 10;
  int c = x%10;
  x -= c;
  x /= 10;
  int d = x;
  return 1000 * a + 100 * b + 10 * c + d;
}

void fillArrayA(){
  for(int i = 0; i < increments; i++){
    a[i] = 0;
  }
}

//Rturns either 0 or 1 
int thresh(int input){
  if(input > threshHold){
    return 1;
  } else {
    return 0;
    }
}

//Adds up (counts) the values in the a array of 50 ints (either 0 or 1) and returns an int
int sumOfA(){
  int count = 0;
  for(int i = 0; i <increments; i++){
    count = count + a[i];
  }
  return count;
}
