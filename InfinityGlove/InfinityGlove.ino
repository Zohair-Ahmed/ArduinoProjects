#include <Servo.h>

/*-----SERVOS-----*/
Servo c1r1;
int c1r1ServoPosition;

Servo c2r1;
int c2r1ServoPosition;

Servo c1r2;
int c1r2ServoPosition;

Servo c2r2;
int c2r2ServoPosition;

/*-----FLEXPINS-----*/
const int rightPinky = A0;
const int rightRing = A1;
const int rightMiddle = A2;
const int rightIndex = A3;

void setup() {

  c1r1.attach(11);
  c2r1.attach(10);
  c1r2.attach(9);
  c2r2.attach(8);

}

void loop() {

  rightPinkyControl();
  rightRingControl();
  rightMiddleControl();
  rightIndexControl();

}

void rightPinkyControl() {

  int rightPinkyFlexValue;

  rightPinkyFlexValue = analogRead(rightPinky);

  c1r1ServoPosition = map(rightPinkyFlexValue, 800, 900, 0, 180);
  c1r1ServoPosition = constrain(c1r1ServoPosition, 0, 180);

  c1r1.write(c1r1ServoPosition);

  delay(20);
}

void rightRingControl() {

  int rightRingFlexValue;

  rightRingFlexValue = analogRead(rightRing);

  c2r1ServoPosition = map(rightRingFlexValue, 800, 900, 0, 180);
  c2r1ServoPosition = constrain(c2r1ServoPosition, 0, 180);

  c2r1.write(c2r1ServoPosition);

  delay(20);
}

void rightMiddleControl() {

  int rightMiddleFlexValue;

  rightMiddleFlexValue = analogRead(rightMiddle);

  c1r2ServoPosition = map(rightMiddleFlexValue, 800, 900, 0, 180);
  c1r2ServoPosition = constrain(c1r2ServoPosition, 0, 180);

  c1r2.write(c1r2ServoPosition);

  delay(20);
}

void rightIndexControl() {

  int rightIndexFlexValue;

  rightIndexFlexValue = analogRead(rightIndex);

  c2r2ServoPosition = map(rightIndexFlexValue, 800, 900, 0, 180);
  c2r2ServoPosition = constrain(c2r2ServoPosition, 0, 180);

  c2r2.write(c2r2ServoPosition);

  delay(20);
}
