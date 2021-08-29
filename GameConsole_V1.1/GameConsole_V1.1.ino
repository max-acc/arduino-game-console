//Pong V 1.1
//by Max Wenk
//
//http://aliencorporation.cf
//
//This is the first working version of this game.

#include <LedControl.h>

int joystickLeftX = 0;
int joystickLeftY = 0;
int joystickRightX = 0;
int joystickRightY = 0;

int DIN = 12;
int CS = 11;
int CLK = 10;

LedControl lc=LedControl(DIN, CLK, CS, 4);
//Displayarrangement
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

int calculateLeftBatPosition = 0;
int calculateRightBatPosition = 0;


int ballPositionX = 4; 
int ballPositionY = 3;
bool ballGoLeft;
bool ballGoUp;
bool ballGoDown;
int pause = 250;

int highscoreLeft = 0;
int highscoreRight = 0;
char colZero[3]  = {B01111100, B01000100, B01111100};
char colOne[3]   = {B00000000, B00100000, B01111100};
char colTwo[3]   = {B01110100, B01010100, B01011100};
char colThree[3] = {B01111100, B01010100, B01010100};


void setup() {
  Serial.begin(9600);

  for(int i=0;i<4;i++){ //Initialising the matrix
    lc.shutdown(i,false);
    lc.setIntensity(i,8);
    lc.clearDisplay(i);
  }
  
  ballGoLeft = false;
  ballGoUp = true;
  ballGoDown = false;
}

void loop() {
  bool pong = true;
  lc.clearDisplay(display01);
  while (pong == true) {
    readJoysticks();
    proofJoysticks();
    leftBat(logicLeftJoysticks(joystickLeftY));
    rightBat(logicRightJoysticks(joystickRightY));
    moveBall();
    delay(50);
  }
}

//Reading the Joysticks
void readJoysticks() {
  joystickLeftY = analogRead(A0);
  joystickLeftX = analogRead(A1);
  joystickRightY = analogRead(A2);
  joystickRightX = analogRead(A3);
}

//Proving the Joysticks
void proofJoysticks() {
  Serial.print("LeftX:  "); Serial.println(joystickLeftX);
  Serial.print("LeftY:  "); Serial.println(joystickLeftY);
  Serial.print("RightX: "); Serial.println(joystickRightX);
  Serial.print("RightY: "); Serial.println(joystickRightY);
  Serial.println();
}

//Logic for the left joystick
int logicLeftJoysticks(int joystickY) {
  if (joystickY < 200) {
    calculateLeftBatPosition += 1;
  }
  if (joystickY > 824) {
    calculateLeftBatPosition -= 1;
  }
  if (calculateLeftBatPosition < 0) {
    calculateLeftBatPosition = 0;
  }
  if (calculateLeftBatPosition > 5) {
    calculateLeftBatPosition = 5;
  }
  return calculateLeftBatPosition;
}

//Logic for the right joystick
int logicRightJoysticks(int joystickY) {
  if (joystickY < 200) {
    calculateRightBatPosition += 1;
  }
  if (joystickY > 824) {
    calculateRightBatPosition -= 1;
  }
  if (calculateRightBatPosition < 0) {
    calculateRightBatPosition = 0;
  }
  if (calculateRightBatPosition > 5) {
    calculateRightBatPosition = 5;
  }
  return calculateRightBatPosition;
}

void leftBat(int yPosition) {
  lc.setColumn(display01, 0, batPosition[yPosition]);
}

void rightBat(int yPosition) {
  lc.setColumn(display01, 7, batPosition[yPosition]);
}


//Ballmovement
void moveBall() {
  lc.setLed(display01, ballPositionY, ballPositionX, false);

  //Ball X Movement
  if (ballGoLeft == true) {
    ballPositionX -= 1;
  }
  else {
    ballPositionX += 1;
  }
  if (ballPositionX == 6) {
    ballGoLeft = true;
  }
  if (ballPositionX == 1) {
    ballGoLeft = false;
  }

  //Ball Y Movement
  if (ballPositionY == 0) {
    ballGoUp = false;
    ballGoDown = true;
  }
  if (ballPositionY == 7) {
    ballGoUp = true;
    ballGoDown = false;
  }
  if (ballGoUp == true) {
    ballPositionY -= 1;
  }
  if (ballGoDown == true) {
    ballPositionY += 1;
  }

  //Ball Y Movement in case of hiting the left bat
  if (calculateLeftBatPosition == ballPositionY && ballPositionX == 1) {
    ballGoUp = true;
    ballGoDown = false;
  }
  else if ((calculateLeftBatPosition + 1) == ballPositionY && ballPositionX == 1) {
    ballGoUp = false;
    ballGoDown = false;
  }
  else if ((calculateLeftBatPosition + 2) == ballPositionY && ballPositionX == 1) {
    ballGoUp = false;
    ballGoDown = true;
  }
  else if (ballPositionX == 1) {
    highscoreLeft +=1;
    endgame();
  }
  //Ball Y Movement in case of hiting the right bat
  if (calculateRightBatPosition == ballPositionY && ballPositionX == 6) {
    ballGoUp = true;
    ballGoDown = false;
  }
  else if ((calculateRightBatPosition + 1) == ballPositionY && ballPositionX == 6) {
    ballGoUp = false;
    ballGoDown = false;
  }
  else if ((calculateRightBatPosition + 2) == ballPositionY && ballPositionX == 6) {
    ballGoUp = false;
    ballGoDown = true;
  }
  else if (ballPositionX == 6) {
    highscoreRight +=1;
    endgame();
  }
  
  lc.setLed(display01, ballPositionY, ballPositionX, true); 
}

void endgame() {
  printHighscore();
  delay(2000);
  lc.clearDisplay(display01);
}

void printHighscore() {
  lc.clearDisplay(display01);
  if (highscoreLeft == 0) {
    for (int i = 0; i < 3; i++) {
      lc.setColumn(display01, 0+i, colZero[i]);
    }
  }
  else if (highscoreLeft == 1) {
    for (int i = 0; i < 3; i++) {
      lc.setColumn(display01, 0+i, colOne[i]);
    }
  }
  else if (highscoreLeft == 2) {
    for (int i = 0; i < 3; i++) {
      lc.setColumn(display01, 0+i, colTwo[i]);
    }
  }
  else if (highscoreLeft == 3) {
    for (int i = 0; i < 3; i++) {
      lc.setColumn(display01, 0+i, colThree[i]);
    }
  }
  if (highscoreRight == 0) {
    for (int i = 0; i < 3; i++) {
      lc.setColumn(display01, 5+i, colZero[i]);
    }
  }
  else if (highscoreRight == 1) {
    for (int i = 0; i < 3; i++) {
      lc.setColumn(display01, 5+i, colOne[i]);
    }
  }
  else if (highscoreRight == 2) {
    for (int i = 0; i < 3; i++) {
      lc.setColumn(display01, 5+i, colTwo[i]);
    }
  }
  else if (highscoreRight == 3) {
    for (int i = 0; i < 3; i++) {
      lc.setColumn(display01, 5+i, colThree[i]);
    }
  }
}
