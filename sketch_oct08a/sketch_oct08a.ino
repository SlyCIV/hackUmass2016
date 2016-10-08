const int analogPin = 1;
const int tempPin = 3;

void setup() {
  Serial.begin(9600);
  pinMode(tempPin, INPUT);
}

void loop() {
  Serial.print("Sound: ");
  Serial.println(analogRead(analogPin));
  Serial.print("knocker: ");
  Serial.println(digitalRead(tempPin));
  delay(800);
}

