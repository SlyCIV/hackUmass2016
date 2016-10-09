#include <SevSeg.h>

SevSeg sevseg;

const int analogPin = 1;
const int tempPin = 3;
const int threshHold = 600; //Sound threshold
const int knockThreshHold = 550; //Knock threshold
const int increments = 50; //Size of array and stuff

int soundLevel = 0; //The sound level read from the mic
int count = 0;
int a[increments];
int knock = 0;
int strikes = 0;

void setup() {
 byte numDigits = 4; 
 byte digitPins[] = {10, 11, 12, 13};
 byte segmentPins[] = {2, 3, 4, 5, 6, 7, 8, 9};

  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(90);
  
  Serial.begin(9600);
  //pinMode(tempPin, INPUT);

  //fills array A with zeros
  fillArrayA();
}

void loop() {
  soundLevel = analogRead(analogPin);
  if(soundLevel>900 || soundLevel<200){
    soundLevel = 500;
  }
  a[count] = soundLevel;
  
  Serial.print("Sound: ");
  Serial.println(soundLevel);
  //Serial.print("Sound Average: ");
  //Serial.println(averageOfA());
  //Serial.print("knocker: ");
  //Serial.println(digitalRead(tempPin));

  if(soundLevel > 800){
    strikes++;
  }
  //Sends out text if we're loud
  if((averageOfA() > threshHold) || (strikes > 10)){
    strikes = 0;
    Serial.println("Pattern: loud");
    delay(1000);
  }

  //Sends out text if knock
  knock = knockAverageOfA();
  //Serial.print("Knock Average: ");
  //Serial.println(knock);
  if((knock > knockThreshHold) && (shortAverageOfA() < knockThreshHold-30)){
    Serial.println("Pattern: knock");
    delay(1000);
  }

  //Sends output to display
  sevseg.setNumber(flip(soundLevel),0);
  
  //Maintains a value on the screen and keeps a delay of 10ms 
  for(int i = 0; i<10; i++){
  delay(1);
  sevseg.refreshDisplay();
  }

  //increments the count variable
  count++;
  if(count == 50){
    count = 0;
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

int averageOfA(){
  int sum = 0;
  for(int i =0; i < 50; i++){
  sum = sum + a[i];
  }
  return (sum/50);
}

int knockAverageOfA(){
  int sum = 0;
  for(int i =10; i < 20; i++){
  sum = sum + a[i];
  }
  return (sum/10);
}

int shortAverageOfA(){
  int sum = 0;
  for(int i=0; i<10; i++){
    sum = sum +a[i];
  }
  for(int i=20; i<50; i++){
    sum = sum +a[i];
  }
  return (sum/45);
}

//Rturns either 0 or 1 
/*
int thresh(int input){
  if(input > threshHold){
    return 1;
  } else {
    return 0;
    }
}
*/

//Adds up (counts) the values in the a array of 50 ints (either 0 or 1) and returns an int
/*
int sumOfA(){
  int count = 0;
  for(int i = 0; i <increments; i++){
    count = count + a[i];
  }
  return count;
}
*/

