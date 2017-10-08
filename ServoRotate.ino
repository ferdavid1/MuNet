#include <Servo.h>

int servoPin=9;

Servo servo;

int servoAngle=0;

void setup() {
  Serial.begin(115200);
  servo.attach(servoPin);
}

void loop() {
  // put your main code here, to run repeatedly:
  servo.write(45);
  delay(100);
  servo.write(90);
  delay(100);

}
