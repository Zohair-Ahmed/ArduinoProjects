#include <DRV8835MotorShield.h>
int voltage = 12;

const int rightPhotoResistor = A0;
const int blueLEDPin = 11;
int rightPhotoResistorValue;

const int leftPhotoResistor = A2;
const int redLEDPin = 10;
int leftPhotoResistorValue;

const int button = 2;
int buttonPushCounter = 0;
int buttonState = 0;
int lastButtonState = 0;
int zero = 0;

#define LED_PIN 13
DRV8835MotorShield motors;

void setup() {

  pinMode(voltage, OUTPUT);
  digitalWrite(voltage, HIGH);

  pinMode (blueLEDPin, OUTPUT);
  pinMode (rightPhotoResistor, INPUT);

  pinMode (redLEDPin, OUTPUT);
  pinMode (leftPhotoResistor, INPUT);

  pinMode (button, INPUT);

  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  rightPhotoResistorValue = analogRead(rightPhotoResistor);
  leftPhotoResistorValue = analogRead(leftPhotoResistor);

  int min = 0;
  int max = 1023;

  int scaleRightPhotoResistorValue = map (rightPhotoResistorValue, min, max, 0, 255);
  int ledBrightnessOfBlueLEDPin = map (scaleRightPhotoResistorValue, min, max, 0, 255);
  int speedOfRightMotor = map (ledBrightnessOfBlueLEDPin, 0, 255, 0, 400);

  int scaleLeftPhotoResistorValue = map (leftPhotoResistorValue, min, max, 0, 255);
  int ledBrightnessOfRedLEDPin = map (scaleLeftPhotoResistorValue, min, max, 0, 255);
  int speedOfLeftMotor = map (ledBrightnessOfRedLEDPin, 0, 255, 0, 400);

  Serial.print("Blue Photo Resistor Value Scaled: ");
  Serial.print(scaleRightPhotoResistorValue);

  Serial.print("\t\tRed Photo Resistor Value Scaled: ");
  Serial.println(scaleLeftPhotoResistorValue);

  buttonState = digitalRead(button);

  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      buttonPushCounter++;
      Serial.print("Number of Button Pushes: ");
      Serial.println(buttonPushCounter);
    }
    delay(100);
  }
  lastButtonState = buttonState;

  switch (buttonPushCounter) {
    /*---NO EMOTION---*/
    case 0:
      motors.setM1Speed(0);
      motors.setM2Speed(0);
      analogWrite(blueLEDPin, 0);
      analogWrite(redLEDPin, 0);
      break;
    /*-------FEAR-------*/
    case 1:

      if (scaleRightPhotoResistorValue > 150) {
        motors.setM1Speed(300);
        motors.setM2Speed(50);
      } else if (scaleLeftPhotoResistorValue > 150) {
        motors.setM1Speed(50);
        motors.setM2Speed(300);
      } else {
        motors.setM1Speed(100);
        motors.setM2Speed(100);
      }
      analogWrite(blueLEDPin, HIGH);
      analogWrite(redLEDPin, LOW);
      break;

    /*-------LOVE-------*/
    case 2:
      if (scaleLeftPhotoResistorValue > 100) {
        motors.setM1Speed(300);
        motors.setM2Speed(100);
      } else if (scaleRightPhotoResistorValue > 100) {
        motors.setM1Speed(100);
        motors.setM2Speed(300);
      } else {
        motors.setM1Speed(100);
        motors.setM2Speed(100);
      }
      analogWrite(blueLEDPin, LOW);
      analogWrite(redLEDPin, HIGH);
      break;

    /*----AGGRESSION----*/

    case 3:
      if (scaleLeftPhotoResistorValue > 100) {
        motors.setM1Speed(300);
        motors.setM2Speed(100);
      }
      if (scaleLeftPhotoResistorValue > 150) {
        motors.setM1Speed(350);
        motors.setM2Speed(100);
      }
      if (scaleRightPhotoResistorValue > 100) {
        motors.setM1Speed(300);
        motors.setM2Speed(100);
      }
      if (scaleRightPhotoResistorValue > 150) {
        motors.setM1Speed(350);
        motors.setM2Speed(100);
      }
      analogWrite(blueLEDPin, HIGH);
      analogWrite(redLEDPin, HIGH);
      break;

    /*---CURIOUSITY---*/

    case 4:
      if (scaleLeftPhotoResistorValue > 100) {
        motors.setM1Speed(300);
        motors.setM2Speed(100);
      }
      if (scaleLeftPhotoResistorValue > 150) {
        motors.setM1Speed(350);
        motors.setM2Speed(100);
      }
      if (scaleLeftPhotoResistorValue > 200) {
        motors.setM1Speed(100);
        motors.setM2Speed(350);
      }
      if (scaleRightPhotoResistorValue > 100) {
        motors.setM1Speed(300);
        motors.setM2Speed(100);
      }
      if (scaleRightPhotoResistorValue > 150) {
        motors.setM1Speed(350);
        motors.setM2Speed(100);
      }
      if (scaleRightPhotoResistorValue > 200) {
        motors.setM1Speed(100);
        motors.setM2Speed(350);
      }
      break;

    default:
      if (buttonPushCounter > 4) {
        buttonPushCounter = 0;
        Serial.print("Number of Button Pushes: ");
        Serial.println(buttonPushCounter);
      }
  }
  delay(1);
}
