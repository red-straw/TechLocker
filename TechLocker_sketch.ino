#include <Servo.h>
const int speakerPin = 2;
const int ledPin = 13;
Servo sl;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(speakerPin, OUTPUT);
  sl.attach(8);
}

void loop() {
  if (Serial.available() > 0) {
    String inputString = Serial.readStringUntil('\n');
    if (inputString == "TechLocker" && !digitalRead(ledPin)) {
      rotateWheel();
    } 
    else if (inputString == "TechUnLocker" && digitalRead(ledPin)) {
      rotateWheelReverse();
    }
  }
}

void rotateWheel() {
  sl.write(1300);
  delay(350);
  sl.write(1500);
  tone(speakerPin, 523, 500); delay(100);
  tone(speakerPin, 587, 500); delay(100);
  tone(speakerPin, 659, 500); delay(100);
  digitalWrite(ledPin, HIGH);
}

void rotateWheelReverse() {
  sl.write(1700);
  delay(350);
  sl.write(1500);
  tone(speakerPin, 659, 500); delay(100);
  tone(speakerPin, 587, 500); delay(100);
  tone(speakerPin, 523, 500); delay(100);
  digitalWrite(ledPin, LOW);
} 