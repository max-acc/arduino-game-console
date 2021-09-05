#include "LedControl.h"

int joystickLeftX = 0;
int joystickLeftY = 0;
int joystickRightX = 0;
int joystickRightY = 0;

int DIN = 12;
int CS = 11;
int CLK = 10;

LedControl lc=LedControl(DIN, CLK, CS, 4);
unsigned long delaytime=3000;

int display01 = 3;
int display02 = 2;
int display03 = 1;
int display04 = 0;

char batPosition[6] = { B11100000,
                        B01110000,
                        B00111000,
                        B00011100,
                        B00001110,
                        B00000111 };

int calculateLeftPosition = 0;
int calculateRightPosition = 0;

int ballPositionX = 3; 
int ballPositionY = 4;
bool ballGoLeft;
bool ballGoUp;
bool ballGoDown;

void setup() {
  Serial.begin(9600);

  for(int i=0;i<4;i++){
    lc.shutdown(i,false);
    lc.setIntensity(i,8);
    lc.clearDisplay(i);
  }
  
  readJoysticks();
  proofJoysticks();
  ballGoLeft = false;
  ballGoUp = true;
  ballGoDown = false;
}


void loop() {
  
  readJoysticks();
  proofJoysticks();
  leftBat(logicLeftJoysticks(joystickLeftX));
  rightBat(logicRightJoysticks(joystickRightX));
  moveBall();
  
  
  delay(500);
}


void readJoysticks() {
  joystickLeftX = analogRead(A0);
  joystickLeftY = analogRead(A1);
  joystickRightX = analogRead(A2);
  joystickRightY = analogRead(A3);
}

int logicLeftJoysticks(int joystickX) {
  if (joystickX < 200) {
    calculateLeftPosition += 1;
  }
  if (joystickX > 824) {
    calculateLeftPosition -= 1;
  }
  if (calculateLeftPosition < 0) {
    calculateLeftPosition = 0;
  }
  if (calculateLeftPosition > 5) {
    calculateLeftPosition = 5;
  }
  return calculateLeftPosition;
}

int logicRightJoysticks(int joystickX) {
  if (joystickX < 200) {
    calculateRightPosition += 1;
  }
  if (joystickX > 824) {
    calculateRightPosition -= 1;
  }
  if (calculateRightPosition < 0) {
    calculateRightPosition = 0;
  }
  if (calculateRightPosition > 5) {
    calculateRightPosition = 5;
  }
  return calculateRightPosition;
}

void proofJoysticks() {
  Serial.print("LeftX:  "); Serial.println(joystickLeftX);
  Serial.print("LeftY:  "); Serial.println(joystickLeftY);
  Serial.print("RightX: "); Serial.println(joystickRightX);
  Serial.print("RightY: "); Serial.println(joystickRightY);
  Serial.println();
}

void matrixArrange() {
  lc.setRow(display01, 0, B01111111);
  lc.setRow(display02, 1, B00111111);
  lc.setRow(display03, 2, B00011111);
  lc.setRow(display04, 3, B00001111);  
}

void leftBat(int xPosition) {
  lc.setColumn(display01, 0, batPosition[xPosition]);
}

void rightBat(int xPosition) {
  lc.setColumn(display01, 7, batPosition[xPosition]);
}

//Ballmovement
void moveBall() {
  lc.setLed(display01, ballPositionX, ballPositionY, false);
  
  //Ball Y Movement
  if (ballGoLeft == false) {
    ballPositionY +=1;
  }
  else {
    ballPositionY -= 1;
  }
  if (ballPositionY == 6) {
    ballGoLeft = true;
  }
  if (ballPositionY == 1) {
    ballGoLeft = false;
  }

  
  
  //Ball X Movement
  if (ballPositionX == 0) {
    ballGoUp = false;
    ballGoDown = true;
  }
  if (ballPositionX == 7) {
    ballGoUp = true;
    ballGoDown = false;
  }
  if (ballGoUp == true) {
    ballPositionX -= 1;
  }
  if (ballGoDown == true) {
    ballPositionX += 1;
  }

  //Ball X Movement in case of hiting a bat
  if (calculateLeftPosition == ballPositionX) {
    ballGoUp = true;
    ballGoDown = false;
  }
  if ((calculateLeftPosition + 2) == ballPositionX && ballPositionY == 1) {
    ballGoUp = false;
    ballGoDown = true;
  }
  lc.setLed(display01, ballPositionX, ballPositionY, true);
}
