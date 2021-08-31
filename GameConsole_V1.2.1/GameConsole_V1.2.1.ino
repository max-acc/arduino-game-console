//Pong V 1.2.1
//by Max Wenk
//
//http://aliencorporation.cf
//
//This is the second fully working version of this game.


//Including Libraries
#include <LedControl.h>

//Initialising the Joysticks
int joystickLeftX;
int joystickLeftY;
int joystickLeftButton;
int joystickRightX;
int joystickRightY;
int joystickRightButton;
bool joystickButtonsPressed;

//Initialising the Matrix
int DIN = 12;
int CS = 11;
int CLK = 10;
LedControl matrix = LedControl(DIN, CLK, CS, 4);

//Arranging the Display in the right order
int display01 = 2;
int display02 = 2;
int display03 = 1;
int display04 = 0;

//Initialising the variables for creating a highscore
int highscoreLeft;
int highscoreRight;
bool someoneScored = false;
int gameover = 0;
char colZero[3]  = {B01111100, B01000100, B01111100};
char colOne[3]   = {B00000000, B00100000, B01111100};
char colTwo[3]   = {B01110100, B01010100, B01011100};
char colThree[3] = {B01010100, B01010100, B01111100};
char colFour[3]  = {B01110000, B00010000, B01111100};
char colFive[3]  = {B01110100, B01010100, B01011100};

//Initialising the variables for choosing the game to play
//1 = Pong, 2 = Pong, 3 = Snake, 4 = PacMan
int gameName;

//Global Pong Variables
int calculateLeftBatPosition;
int calculateRightBatPosition;

bool ballGoLeft;
bool ballGoUp;
bool ballGoDown;

int ballPositionX;
int ballPositionY;


void setup() {
  Serial.begin(9600); //Starting the Serialmonitor

  //Resetting the matrix
  for (int i = 0; i < 4; i++) {
    matrix.shutdown(i, false);
    matrix.setIntensity(i, 8);
    matrix.clearDisplay(i);
  }
  //Choosing the game
  gameName = 1;
  switch (gameName) {
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
    default:
      break;
  }
}

void loop() {
  delay(500);
}

//Reading the Joysticks
void readJoysticks() {
  //Reading the values from the joysticks
  joystickLeftY = analogRead(A0);
  joystickLeftX = analogRead(A1);
  joystickLeftButton = analogRead(A2);
  joystickRightY = analogRead(A3);
  joystickRightX = analogRead(A4);
  joystickRightButton = analogRead(A5);
  //If one of the two joysticks is pressed, there will be one output
  if ((joystickLeftButton < 10) || (joystickRightButton < 20)) {
    joystickButtonsPressed = true;
  }
  else {
    joystickButtonsPressed = false;
  }
  Serial.print("ButtonsPressed:  ");  Serial.println(joystickButtonsPressed);
}

//Proving if the Joysticks work as intended
void proofJoysticks() {
  Serial.print("LeftX:  ");           Serial.println(joystickLeftX);
  Serial.print("LeftY:  ");           Serial.println(joystickLeftY);
  Serial.print("LeftButton:  ");      Serial.println(joystickLeftButton);
  Serial.print("RightX: ");           Serial.println(joystickRightX);
  Serial.print("RightY: ");           Serial.println(joystickRightY);
  Serial.print("RightButton:  ");     Serial.println(joystickRightButton);
  Serial.print("ButtonsPressed:  ");  Serial.println(joystickButtonsPressed);
  Serial.println("");
}

//Printing the highscore on the matrix
int printHighscore(int highscoreLeft, int highscoreRight) {
  matrix.clearDisplay(display01); //Clearing the display
  
  //Printing the highscore column by column
  for (int i = 0; i < 3; i++) {
    //Left highscore
    switch (highscoreLeft) {
      case 0:
        matrix.setColumn(display01, 0 + i, colZero[i]);
        break;
      case 1:
        matrix.setColumn(display01, 0 + i, colOne[i]);
        break;
      case 2:
        matrix.setColumn(display01, 0 + i, colTwo[i]);
        break;
      case 3:
        matrix.setColumn(display01, 0 + i, colThree[i]);
        break;
      case 4:
        matrix.setColumn(display01, 0 + i, colFour[i]);
        break;
      case 5:
        matrix.setColumn(display01, 0 + i, colFive[i]);
        break;
      default:
        break;
    }
    //Right highscore
    switch (highscoreRight) {
      case 0:
        matrix.setColumn(display01, 5 + i, colZero[i]);
        break;
      case 1:
        matrix.setColumn(display01, 5 + i, colOne[i]);
        break;
      case 2:
        matrix.setColumn(display01, 5 + i, colTwo[i]);
        break;
      case 3:
        matrix.setColumn(display01, 5 + i, colThree[i]);
        break;
      case 4:
        matrix.setColumn(display01, 5 + i, colFour[i]);
        break;
      case 5:
        matrix.setColumn(display01, 5 + i, colFive[i]);
        break;
      default:
        break;
    }
  }
  Serial.println(highscoreLeft);
  Serial.println(highscoreRight);
  //It will pause until one of the joysticks is pressed
  while (joystickButtonsPressed != true) {
    readJoysticks();
    delay(10);
  }
  joystickButtonsPressed = false;
  
  //If the left or right highscore is 5, the game will be cancelled otherwise it will run again
  if (highscoreLeft == 5 || highscoreRight == 5) {
    return 1; //Game will be cancelled
  }
  else {
    return 0; //Game will run again
  }
}

//Printing Game Over
void gameOver() {
  Serial.println("Game Over");
  matrix.clearDisplay(display01);
  matrix.setColumn(display01, 0, B01111100);
  matrix.setColumn(display01, 1, B01000100);
  matrix.setColumn(display01, 2, B01010100);
  matrix.setColumn(display01, 3, B01011100);
  matrix.setColumn(display01, 5, B01111100);
  matrix.setColumn(display01, 6, B01000100);
  matrix.setColumn(display01, 7, B01111100);
}

//Playing Pong
void playPong() {
  //Setting up Vaiables for Pong
  bool pong = true;
  int difficulty = 0;
  
  //Setting up Vaiables for the highscore
  someoneScored = false;
  gameover = 0;
  highscoreLeft = 0;
  highscoreRight = 0;

  //Setting up Vaiables for the bats
  calculateLeftBatPosition  = 2;
  calculateRightBatPosition = 2;

  //Initialising the different positions for the bats
  char batPosition[6] = { B11100000,
                          B01110000,
                          B00111000,
                          B00011100,
                          B00001110,
                          B00000111
                        };
  
  
  //Actually playing Pong
  spawnBall();

  while (pong == true) {
    readJoysticks();  //Reading the joysticks
    printBat(0, batPosition, logicLeftJoystick(joystickLeftY));   //Printing the bats at the right positions
    printBat(7, batPosition, logicRightJoystick(joystickRightY));
    moveBall(difficulty);   //Moving the ball (normal and when it collides)

    //If someone has scored a point, the highscore will be printed
    if (someoneScored == true) {
      someoneScored = false;
      gameover = printHighscore(highscoreLeft, highscoreRight);
      //If gameover is 1 (someone has scored 3 points) the game is over
      if (gameover == 1) {
        gameOver(); //Printing Game Over
        //The Game Over will be displayed as long as the joystick buttons arent pressed
        while (joystickButtonsPressed != true) {
          readJoysticks();
          delay(10);
        }
        joystickButtonsPressed = false;
        matrix.clearDisplay(display01);
        break;
      }
      spawnBall();
      matrix.clearDisplay(display01);      
    }
    delay(250);
  }
}

//Printing the bats
void printBat(int xPosition, char batPosition[], int yPosition) {
  matrix.setColumn(display01, xPosition, batPosition[yPosition]);
}

//Implementing the logic (for moving the Joystick) for left Joystick to play Pong
int logicLeftJoystick(int joystickY) {
  //If the value of the left Joystick is lower than 200 the Joystick will be moved down by one unit
  if (joystickY < 200) {
    calculateLeftBatPosition += 1;
  }
  //If the value of the left Joystick is higher than 823 the Joystick will be moved up by one unit
  if (joystickY > 824) {
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
int logicRightJoystick(int joystickY) {
  //If the value of the right Joystick is lower than 200 the Joystick will be moved down by one unit
  if (joystickY < 200) {
    calculateRightBatPosition += 1;
  }
  //If the value of the left Joystick is higher than 823 the Joystick will be moved up by one unit
  if (joystickY > 824) {
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

//Randomly spawn the ball
void spawnBall() {
  //Setting up Vaiables for the ball
  ballPositionX = random(3, 5);
  ballPositionY = random(1, 6);
  ballGoLeft = false;  //Just for default
  if (ballPositionX == 3) {
    ballGoLeft = false;
  }
  if (ballPositionX == 4) {
    ballGoLeft = true;
  }
  ballGoUp = false;
  ballGoDown = false;
  int ballDirection = random(1000) % 2 + 1;
  if (ballDirection == 1) {
    ballGoUp = true;
    ballGoDown = false;
  }
  if (ballDirection == 2) {
    ballGoUp = false;
    ballGoDown = true;
  }
}

//Logic for moving the ball
void moveBall(int difficulty) {
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


//Ball Y Movement
  //If the Ball is at the y position 0 or 7 the ball will turn into the other direction
  if (ballPositionY == 0) {
    ballGoUp = false;
    ballGoDown = true;
  }
  if (ballPositionY == 7) {
    ballGoUp = true;
    ballGoDown = false;
  }
  //Actually moving the ball on the y axis
  if (ballGoUp == true) {
    ballPositionY -= 1;
  }
  if (ballGoDown == true) {
    ballPositionY += 1;
  }

//Ball Y movement in case of hitting a ball on difficulty 0 and 1 (the ball will bounce of in a normal way)
  if (difficulty == 0 || difficulty == 1) {
    //If the upper part of the bat is hitted, the ball will go up
    if ((calculateLeftBatPosition == ballPositionY && ballPositionX == 1) || (calculateRightBatPosition == ballPositionY && ballPositionX == 6)) {
      ballGoUp = true;
      ballGoDown = false;
    }
    //If the middle part of the bat is hitted, the ball will go straight to the other side
    else if (((calculateLeftBatPosition + 1) == ballPositionY && ballPositionX == 1) || ((calculateRightBatPosition + 1) == ballPositionY && ballPositionX == 6)) {
      ballGoUp = false;
      ballGoDown = false;
    }
    //If the lower part of the bat is hitted, the ball will go down
    else if (((calculateLeftBatPosition + 2) == ballPositionY && ballPositionX == 1) || ((calculateRightBatPosition + 2) == ballPositionY && ballPositionX == 6)) {
      ballGoUp = false;
      ballGoDown = true;
    }
    //If the ball hit the left side when there is no bat behind, right scores a point
    else if (ballPositionX == 1) {
      highscoreRight += 1;
      someoneScored = true;
    }
    //If the ball hit the right side when there is no bat behind, left scores a point
    else if (ballPositionX == 6) {
      highscoreLeft += 1;
      someoneScored = true;
    }
  }

//Ball Y movement in case of hitting a ball on difficulty 2 and 3 (the ball will bounce of in a random way)
  if (difficulty == 2 || difficulty == 3) {

  }

  matrix.setLed(display01, ballPositionY, ballPositionX, true); //Actually moving the ball to the right place
}
