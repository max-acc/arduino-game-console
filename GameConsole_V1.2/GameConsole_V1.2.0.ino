//Pong V 1.2
//by Max Wenk
//
//http://aliencorporation.cf
//
//This is the second non working version of this game.
int var = 1;

//Including Libraries
#include <LedControl.h>

//Initialising the Joysticks
int joystickLeftX;
int joystickLeftY;
int joystickLeftButton;
int joystickRightX;
int joystickRightY;
int joystickRightButton;

//Initialising the Matrix
int DIN = 12;
int CS = 11;
int CLK = 10;
LedControl matrix = LedControl(DIN, CLK, CS, 4);

//Arranging the Display in the right order
int display01 = 3;
int display02 = 2;
int display03 = 1;
int display04 = 0;

//Initialising the variables for creating a highscore
int highscoreLeft = 0;
int highscoreRight = 0;
char colZero[3]  = {B01111100, B01000100, B01111100};
char colOne[3]   = {B00000000, B00100000, B01111100};
char colTwo[3]   = {B01110100, B01010100, B01011100};
char colThree[3] = {B01111100, B01010100, B01010100};


void setup() {
  Serial.begin(9600); //Starting the Serialmonitor

  //Resetting the matrix
  for (int i = 0; i<4; i++) {
    matrix.shutdown(i, false);
    matrix.setIntensity(i, 8);
    matrix.clearDisplay(i);
  }
  
}


void loop() {
  readJoysticks();  //Reading the Joysticks
  proofJoysticks(); //Proving the Joysticks
  
  switch (var) {
    //Pong
    case 1:
      playPong();
      break;
    //TicTacToe
    case 2:
      break;
    //Snake
    case 3:
      break;
    //PacMan
    case 4:
      break;
    
  }
}

//Reading the Joysticks
void readJoysticks() {
  joystickLeftY = analogRead(A0);
  joystickLeftX = analogRead(A1);
  joystickLeftButton = analogRead(A2);
  joystickRightY = analogRead(A3);
  joystickRightX = analogRead(A4);
  joystickRightButton = analogRead(A5);
}

//Proving if the Joysticks work as intended
void proofJoysticks() {
  Serial.print("LeftX:  "); Serial.println(joystickLeftX);
  Serial.print("LeftY:  "); Serial.println(joystickLeftY);
  Serial.print("LeftButton:  "); Serial.println(joystickLeftButton);
  Serial.print("RightX: "); Serial.println(joystickRightX);
  Serial.print("RightY: "); Serial.println(joystickRightY);
  Serial.print("RightButton:  "); Serial.println(joystickRightButton);
}

//Pong
void playPong() {
  bool pong = true;
  bool buttonPressed = false;
  int difficulty;

  //Initialising the different positions for the bats
  char batPosition[6] = { B11100000,
                          B01110000,
                          B00111000,
                          B00011100,
                          B00001110,
                          B00000111};

  //Initialising the Variables for calculating the position of the bats
  int calculateLeftBatPosition, calculateRightBatPosition = 3;

  //Initialising the Variables to calculate the position of the ball
  int ballPositionX = 4; 
  int ballPositionY = 3;
  bool ballGoLeft = false;
  bool ballGoUp = false;
  bool ballGoDown = false;

  //Choosing the difficulty
  //0 = easy, 1 = medium, 2 = hard, 3 = super hard (only easy available)
  difficulty = 0;

  //Main structure for running the Pong Game
  while (pong == true) {
    readJoysticks();
    printBat(0, batPosition, logicLeftJoystick(calculateLeftBatPosition, joystickLeftY));
    printBat(7, batPosition, logicRightJoystick(calculateRightBatPosition, joystickRightY));
    moveBall(highscoreLeft, highscoreRight, buttonPressed, difficulty, ballPositionY, ballPositionX, ballGoLeft, ballGoUp, ballGoDown, calculateLeftBatPosition ,calculateRightBatPosition);
  }
  
}

//Printing the Bats
void printBat(int xPosition, char batPosition[], int yPosition) {
  matrix.setColumn(display01, xPosition, batPosition[yPosition]); //Selecting the display, declare x position, declare y position and print the bat from the char string above
}

//Implementing the logic (for moving the Joystick) for left Joystick to play Pong
int logicLeftJoystick(int calculateLeftBatPosition, int joystickY) {
  //If the value of the left Joystick is lower than 200 the Joystick will be moved down by one unit
  if (joystickY < 200) {
    calculateLeftBatPosition += 1;
  }
  //If the value of the left Joystick is higher than 823 the Joystick will be moved up by one unit
  if (joystickY > 823) {
    calculateLeftBatPosition -= 1;
  }
  //If the Bat position is lower than 0 or higher than 5 the values get adjusted to values which are legit to use for printing the bat
  if (calculateLeftBatPosition < 0) {
    calculateLeftBatPosition = 0;
  }
  if (calculateLeftBatPosition > 5) {
    calculateLeftBatPosition = 5;
  }
  //The y position of the left bat will be returned
  return calculateLeftBatPosition;
}

//Implementing the logic (for moving the Joystick) for right Joystick to play Pong
int logicRightJoystick(int calculateRightBatPosition, int joystickY) {
  //If the value of the right Joystick is lower than 200 the Joystick will be moved down by one unit
  if (joystickY < 200) {
    calculateRightBatPosition += 1;
  }
  //If the value of the left Joystick is higher than 823 the Joystick will be moved up by one unit
  if (joystickY > 823) {
    calculateRightBatPosition -= 1;
  }
  //If the Bat position is lower than 0 or higher than 5 the values get adjusted to values which are legit to use for printing the bat
  if (calculateRightBatPosition < 0) {
    calculateRightBatPosition = 0;
  }
  if (calculateRightBatPosition > 5) {
    calculateRightBatPosition = 5;
  }
  //The y position of the right bat will be returned
  return calculateRightBatPosition;
}

//Logic for moving the ball
void moveBall(int highscoreLeft, int highscoreRight, int buttonPressed, int difficulty, int ballPositionY, int ballPositionX, int ballGoLeft, int ballGoUp, int ballGoDown, int calculateLeftBatPosition, int calculateRightBatPosition) {
  matrix.setLed(display01, ballPositionY, ballPositionX, false);  //Clearing the old ball position

//Ball X movement
  //The ball will travel to the left as long as the variable is true, otherwise it will go to the right
  if (ballGoLeft == true) {
    ballPositionX -= 1;
  }
  else {
    ballPositionX += 1;
  }
  //If the ball is at position 1 or 6 the ball will turn
  if (ballPositionX == 6) {
    ballGoLeft = true;
  }
  if (ballPositionX == 1) {
    ballGoLeft = false;
  }

//Ball Y movement
  //If the Ball is at the y position 0 or 7 the ball will turn into the other direction
  if (ballPositionY == 0) {
    ballGoUp = false;
    ballGoDown = true;
  }
  if (ballPositionY == 7) {
    ballGoUp = true;
    ballGoDown = false;
  }
  //Logic for actually moving the ball
  if (ballGoUp = true) {
    ballPositionY -= 1;
  }
  if (ballGoDown = true) {
    ballPositionY += 1;
  }

  //Ball Y movement in case of hitting a ball on difficulty 0 and 1 (the ball will bounce of in a normal way)
  if (difficulty == 0 || difficulty == 1) {
    
    if ((calculateLeftBatPosition || calculateRightBatPosition) == ballPositionY && ballPositionX == (1 || 6)) {
      ballGoUp = true;
      ballGoDown = false;
    }
    
    else if (((calculateLeftBatPosition + 1) || (calculateRightBatPosition + 1)) == ballPositionY && ballPositionX == (1 || 6)) {
      ballGoUp = false;
      ballGoDown = false;
    }
    
    else if (((calculateLeftBatPosition + 2) || (calculateRightBatPosition + 2)) == ballPositionY && ballPositionX == (1 || 6)) {
      ballGoUp = false;
      ballGoDown = true;
    }
    
    else if (ballPositionX == 1) {
      highscoreLeft +=1;
      endgame(highscoreLeft, highscoreRight, buttonPressed);
    }
    else if (ballPositionX == 6) {
      highscoreRight +=1;
      endgame(highscoreLeft, highscoreRight, buttonPressed);
    }
  }

  //Ball Y movement in case of hitting a ball on difficulty 2 and 3 (the ball will bounce of in a random way)
  if (difficulty == 2 || difficulty == 3) {
     
  }
  matrix.setLed(display01, ballPositionY, ballPositionX, true); //Actually printing the ball
}

void endgame(int highscoreLeft, int highscoreRight, int buttonPressed) {
  printHighscore(highscoreLeft, highscoreRight);
  while(buttonPressed != true) {
    if ((joystickLeftButton || joystickRightButton) < 20) {
      buttonPressed = true;
      delay(10);
    }
  }
  matrix.clearDisplay(display01);
}

void printHighscore(int highscoreLeft, int highscoreRight) {
  matrix.clearDisplay(display01);
  int j = 0;
won:
  for (int i = 0; i<3; i++) {
    switch (highscoreLeft) {
      case 0:
        matrix.setColumn(display01, 0+i, colZero[i]);
        break;
      case 1:
        matrix.setColumn(display01, 0+i, colOne[i]);
        break;
      case 2:
        matrix.setColumn(display01, 0+i, colTwo[i]);
        break;
      case 3:
        matrix.setColumn(display01, 0+i, colThree[i]);
        while (j < 3) {
          delay(500);
          matrix.clearDisplay(display01);
          delay(400);
          j++;
          goto won;
        }
        break;
      default:
        break;
    }
    
    switch (highscoreRight) {
      case 0:
        matrix.setColumn(display01, 5+i, colZero[i]);
        break;
      case 1:
        matrix.setColumn(display01, 5+i, colOne[i]);
        break;
      case 2:
        matrix.setColumn(display01, 5+i, colTwo[i]);
        break;
      case 3:
        matrix.setColumn(display01, 5+i, colThree[i]);
        while (j < 3) {
          delay(500);
          matrix.clearDisplay(display01);
          delay(400);
          j++;
          goto won;
        }
        break;
      default:
        break;
    }
  }
}
