#include <LiquidCrystal.h>
#include <Servo.h>

/*-------------------------BUTTONS------------------------*/
const int nickelButton = 13;
int nickelButtonPushCounter = 0.00;
int nickelButtonState = 0;
int nickelLastButtonState = 0;

const int dimeButton = 12;
int dimeButtonPushCounter = 0.00;
int dimeButtonState = 0;
int dimeLastButtonState = 0;

const int quarterButton = 11;
int quarterButtonPushCounter = 0.00;
int quarterButtonState = 0;
int quarterLastButtonState = 0;

const int loonieButton = 10;
int loonieButtonPushCounter = 0.00;
int loonieButtonState = 0;
int loonieLastButtonState = 0;

const int toonieButton = 9;
int toonieButtonPushCounter = 0.00;
int toonieButtonState = 0;
int toonieLastButtonState = 0;

const int totalButton = 8;
float totalButtonPushCounter = 0.00;
int totalButtonState = 0;
int totalLastButtonState = 0;

/*------------------------SERVOS------------------------*/
Servo nickelServo;
int nickelPos = 90;

Servo dimeServo;
int dimePos = 90;

Servo quarterServo;
int quarterPos = 90;

Servo loonieServo;
int looniePos = 90;

Servo toonieServo;
int tooniePos = 90;

/*------------------------LCD------------------------*/
LiquidCrystal lcd (36, 34, 32, 30, 28, 26);

String welcome = "";

/*------------------------RESET------------------------*/
void(* resetFunc) (void) = 0;

void setup() {

  pinMode (nickelButton, INPUT);
  pinMode (dimeButton, INPUT);
  pinMode (quarterButton, INPUT);
  pinMode (loonieButton, INPUT);
  pinMode (toonieButton, INPUT);

  pinMode (totalButton, INPUT);

  nickelServo.attach(2);
  dimeServo.attach(3);
  quarterServo.attach(4);
  loonieServo.attach(5);
  toonieServo.attach(6);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("$ PTM MACHINE $");
  delay(2000);
  lcd.clear();
}

void loop() {
  
  nickels();
  dimes();
  quarters();
  loonies();
  toonies();

  total();
}

/*-------------------------BUTTONS------------------------*/
void nickels() {
  
  nickelButtonState = digitalRead(nickelButton);
  welcome = "# of Nickels:";
  lcd.setCursor(0, 0);

  if (nickelButtonState != nickelLastButtonState) {
    if (nickelButtonState == HIGH) {
      lcd.clear();
      nickelButtonPushCounter++;
      lcd.print(welcome);
      lcd.setCursor(0, 1);
      lcd.print(nickelButtonPushCounter);
    }
    delay(100);
  }
  nickelLastButtonState = nickelButtonState;
}

void dimes() {
  
  dimeButtonState = digitalRead(dimeButton);
  welcome = "# of Dimes:";
  lcd.setCursor(0, 0);

  if (dimeButtonState != dimeLastButtonState) {
    if (dimeButtonState == HIGH) {
      dimeButtonPushCounter++;
      lcd.clear();
      lcd.print(welcome);
      lcd.setCursor(0, 1);
      lcd.print(dimeButtonPushCounter);
    }
    delay(100);
  }
  dimeLastButtonState = dimeButtonState;
}

void quarters() {
  
  quarterButtonState = digitalRead(quarterButton);
  welcome = "# of Quarters:";
  lcd.setCursor(0, 0);

  if (quarterButtonState != quarterLastButtonState) {
    if (quarterButtonState == HIGH) {
      quarterButtonPushCounter++;
      lcd.clear();
      lcd.print(welcome);
      lcd.setCursor(0, 1);
      lcd.print(quarterButtonPushCounter);
    }
    delay(100);
  }
  quarterLastButtonState = quarterButtonState;
}

void loonies() {
  
  loonieButtonState = digitalRead(loonieButton);
  welcome = "# of Loonies:";

  if (loonieButtonState != loonieLastButtonState) {
    if (loonieButtonState == HIGH) {
      loonieButtonPushCounter++;
      lcd.clear();
      lcd.print(welcome);
      lcd.setCursor(0, 1);
      lcd.print(loonieButtonPushCounter);
    }
    delay(100);
  }
  loonieLastButtonState = loonieButtonState;
}

void toonies() {
  
  toonieButtonState = digitalRead(toonieButton);
  welcome = "# of Toonies:";

  if (toonieButtonState != toonieLastButtonState) {
    if (toonieButtonState == HIGH) {
      toonieButtonPushCounter++;
      lcd.clear();
      lcd.print("# of Toonies: ");
      lcd.setCursor(0, 1);
      lcd.print(toonieButtonPushCounter);
    }
    delay(100);
  }
  toonieLastButtonState = toonieButtonState;
}

void total() {

  totalButtonState = digitalRead(totalButton);
  welcome = "Your Total: ";

  if (totalButtonState == HIGH) {
    lcd.print("Your Total: ");
    totalButtonPushCounter = (0.05 * nickelButtonPushCounter) + (0.1 * dimeButtonPushCounter) +
                             (0.25 * quarterButtonPushCounter) + (loonieButtonPushCounter) + (2 * toonieButtonPushCounter);


    lcd.setCursor(0, 1);
    lcd.print(totalButtonPushCounter);

    delay(100);
    lcd.setCursor(5, 1);
    
    nickelServoMotor();
    dimeServoMotor();
    quarterServoMotor();
    loonieServoMotor();
    toonieServoMotor();

    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("SPEND      ");
    lcd.setCursor(4, 1);
    lcd.print("WISELY :)     ");

    delay (3000);

    resetFunc();
  }
  delay(100);
}

/*------------------------SERVOS------------------------*/
void nickelServoMotor() {
  for (int i = 0; i <= nickelButtonPushCounter - 1; i++) {
    for (nickelPos = 0; nickelPos <= 90; nickelPos += 1) {
      nickelServo.write(nickelPos);
      delay(15);
    }
  }
  nickelServo.write(90);
}

void dimeServoMotor() {
  for (int i = 0; i <= dimeButtonPushCounter - 1; i++) {
    for (dimePos = 0; dimePos <= 90; dimePos += 1) {
      dimeServo.write(dimePos);
      delay(15);
    }
  }
  dimeServo.write(90);
}

void quarterServoMotor() {
  for (int i = 0; i <= quarterButtonPushCounter - 1; i++) {
    for (quarterPos = 0; quarterPos <= 90; quarterPos += 1) {
      quarterServo.write(quarterPos);
      delay(15);
    }
  }
  quarterServo.write(90);
}

void loonieServoMotor() {
  for (int i = 0; i <= loonieButtonPushCounter - 1; i++) {
    for (looniePos = 0; looniePos <= 100; looniePos += 1) {
      loonieServo.write(looniePos);
      delay(15);
    }
  }
  loonieServo.write(100);
}

void toonieServoMotor() {
  for (int i = 0; i <= toonieButtonPushCounter - 1; i++) {
    for (tooniePos = 0; tooniePos <= 90; tooniePos += 1) {
      toonieServo.write(tooniePos);
      delay(15);
    }
  }
  toonieServo.write(90);
}
