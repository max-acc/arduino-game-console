//Pong V 1.5.0
//by Max Wenk
//
//http://aliencorporation.cf
//
//This is a release version of this game.


//Including libraries
#include <LedControl.h>

//Initialising hte joysticks
int joystickLeftY;
int joystickLeftX;
int joystickLeftButton;
int joystickRightY;
int joystickRightX;
int joystickRightButton;
bool joystickBothUp;
bool joystickBothDown;
bool joystickBothLeft;
bool joystickBothRight;
bool joystickBothButtonsPressed;

//Initialising the matrices
int DIN = 12;
int CS  = 11;
int CLK = 10;
LedControl matrix = LedControl(DIN, CLK, CS, 4);  //4 because 4 matrices are used

//Arranging the displays in the right order
int display01 = 3;
int display02 = 2;
int display03 = 1;
int display04 = 0;
int displayInUse = display01; //Just for default

//Initialising the variables for creating a highscore
int highscoreLeft;
int highscoreRight;
bool someoneScored = false; //Just for default
bool gameover = false;  //Just for default
char colZero[3]  = {B01111100, B01000100, B01111100}; //Outputs zero
char colOne[3]   = {B00000000, B00100000, B01111100}; //Outputs one
char colTwo[3]   = {B01011100, B01010100, B01110100}; //Outputs two
char colThree[3] = {B01010100, B01010100, B01111100}; //Outputs three
char colFour[3]  = {B01110000, B00010000, B01111100}; //Outputs four
char colFive[3]  = {B01110100, B01010100, B01011100}; //Outputs five

//Initialising the variables for choosing the game to play
//1 = Pong, 2 = Pong, 3 = Snake, 4 = PacMan
int gameName;


//Global Pong Variables
int leftBatPositionPong;
int rightBatPositionPong;

bool ballGoLeftPong;
bool ballGoUpPong;
bool ballGoDownPong;

int ballPositionXPong;
int ballPositionYPong;
//Creating a class to calculate and print the bats
class PongBat {
  //Setting up the variables
  int usingDisplay, yPosition, originalYPosition, xPosition;

  public:
  //Constructor for the bats
  PongBat(int yPositionGet, int xPositionGet) {
    yPosition = yPositionGet;
    xPosition = xPositionGet;
  }

  //Function for printing the bat
  void printBat(int yPositionJoystick) {
    originalYPosition = yPosition;
    yPosition = logicJoystick(yPositionJoystick);
    //Calculating on which display to print
    if (xPosition == 0) {
      usingDisplay = display01;
    }
    else {
      usingDisplay = display02;
    }
    if (originalYPosition != yPosition) {
      matrix.setColumn(usingDisplay, xPosition % 8, B00000000);     //Clearing the column to print the new bat position, but only if the bat position is not the same as before
    }
    
    //Printing the bat
    matrix.setLed(usingDisplay, yPosition - 1,  xPosition % 8, true);
    matrix.setLed(usingDisplay, yPosition,      xPosition % 8, true); 
    matrix.setLed(usingDisplay, yPosition + 1,  xPosition % 8, true);
  }

  //Function for calculating the bat position with the usage of the joysticks
  int logicJoystick(int yPositionJoystick) {
    //If the value of the left Joystick is lower than 200 the Joystick will be moved down by one unit
    if (yPositionJoystick < 200) {
      yPosition += 1;
    }
    //If the value of the left Joystick is higher than 823 the Joystick will be moved up by one unit
    if (yPositionJoystick > 824) {
      yPosition -= 1;
    }
  
    //If the Bat position is lower than 0 or higher than 5 the values get adjusted to values which are legit to use for printing the bat
    if (yPosition < 1) {
      yPosition = 1;
    }
    if (yPosition > 6) {
      yPosition = 6;
    }
    //The y position of the left bat will be returned
    return yPosition;
  }

  //Returning the y position
  int getYPosition() {
    return yPosition;
  }
  
};

void setup() {
  Serial.begin(9600); //Starting the serial monitor

  //Resetting the matrices
  for (int i = 0; i < matrix.getDeviceCount(); i++) {
    matrix.shutdown(i, false);
    matrix.setIntensity(i, 8);
    matrix.clearDisplay(i);
  }
}

void loop() {
  //Choosing the game you want to play
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
  delay(500);
}

//Reading the joysticks
void readJoysticks() {
  //Reading the values from the joysticks
  joystickLeftY = analogRead(A0);
  joystickLeftX = analogRead(A1);
  joystickLeftButton = analogRead(A2);
  joystickRightY = analogRead(A3);
  joystickRightX = analogRead(A4);
  joystickRightButton = analogRead(A5);
  
  //If one of the two joysticks is up, there will be one output
  if ((joystickLeftY <300) || (joystickRightY <300)) {
    joystickBothUp = true;
  }
  else {
    joystickBothUp = false;
  }
  
  //If one of the two joysticks is down, there will be one output
  if ((joystickLeftY > 724) || (joystickRightY > 724)) {
    joystickBothDown = true;
  }
  else {
    joystickBothDown = false;
  }

  //If one of the two joysticks is left, there will be one output
  if ((joystickLeftX <300) || (joystickRightX <300)) {
    joystickBothLeft = true;
  }
  else {
    joystickBothLeft = false;
  }

  //If one of the two joysticks is right, there will be one output
  if ((joystickLeftX > 724) || (joystickRightX > 724)) {
    joystickBothRight = true;
  }
  else {
    joystickBothRight = false;
  }
  
  //If one of the two joysticks buttons is pressed, there will be one output
  if ((joystickLeftButton < 5) || (joystickRightButton < 5)) {
    joystickBothButtonsPressed = true;
  }
  else {
    joystickBothButtonsPressed = false;
  }
}

//Proving if the joysticks work as intended
void proofJoysticks() {
  Serial.print("LeftX:        ");   Serial.println(joystickLeftX);
  Serial.print("LeftY:        ");   Serial.println(joystickLeftY);
  Serial.print("LeftButton:   ");   Serial.println(joystickLeftButton);
  Serial.print("RightX:       ");   Serial.println(joystickRightX);
  Serial.print("RightY:       ");   Serial.println(joystickRightY);
  Serial.print("RightButton:  ");   Serial.println(joystickRightButton);
  Serial.print("BothUp:     ");  Serial.println(joystickBothUp);
  Serial.print("BothDown:   ");  Serial.println(joystickBothDown);
  Serial.print("BothLeft:   ");  Serial.println(joystickBothLeft);
  Serial.print("BothRight:  ");  Serial.println(joystickBothRight);
  Serial.print("ButtonsPressed:  ");Serial.println(joystickBothButtonsPressed);
  Serial.println("");
}

//Function for clearing all displays
void clearDisplays() {
  for (int i = 0; i < matrix.getDeviceCount(); i++) { //matrix.getDiviceCount gets the number of the connected displays
    matrix.clearDisplay(i);
  }
}

//Function for calculating on which display to print
void calculateDisplayToUse(int xPosition) {
  if (xPosition < 8) {  //If the xPosition of the given point on the x axis is greater than 8 the left display is used ...
    displayInUse = display01;
  }
  else {  //... otherwise the right display is used
    displayInUse = display02;
  }
}

//Function for calculating a usable x position for the matrices (between 0 and 7)
int calculateXPixel (int xPosition) {
  return xPosition %= 8;
}

//Printing the highscore and giving back a value if the game is over
bool printHighscore(int highscoreLeft, int highscoreRight) {
  clearDisplays();

  //Printing the highscore column by column
  for (int i = 0; i < 3; i++) {
    //Printing the left highscore on the left matrix
    displayInUse = display01;
    switch (highscoreLeft) {
      case 0:
        matrix.setColumn(displayInUse, calculateXPixel(1) + i, colZero[i]);
        break;
      case 1:
        matrix.setColumn(displayInUse, calculateXPixel(1) + i, colOne[i]);
        break;
      case 2:
        matrix.setColumn(displayInUse, calculateXPixel(1) + i, colTwo[i]);
        break;
      case 3:
        matrix.setColumn(displayInUse, calculateXPixel(1) + i, colThree[i]);
        break;
      case 4:
        matrix.setColumn(displayInUse, calculateXPixel(1) + i, colFour[i]);
        break;
      case 5:
        matrix.setColumn(displayInUse, calculateXPixel(1) + i, colFive[i]);
        break;
      default:
        break;
    }
    //Printing the right highscore on the right display
    displayInUse = display02;
    switch (highscoreRight) {
      case 0:
        matrix.setColumn(displayInUse, calculateXPixel(12) + i, colZero[i]);
        break;
      case 1:
        matrix.setColumn(displayInUse, calculateXPixel(12) + i, colOne[i]);
        break;
      case 2:
        matrix.setColumn(displayInUse, calculateXPixel(12) + i, colTwo[i]);
        break;
      case 3:
        matrix.setColumn(displayInUse, calculateXPixel(12) + i, colThree[i]);
        break;
      case 4:
        matrix.setColumn(displayInUse, calculateXPixel(12) + i, colFour[i]);
        break;
      case 5:
        matrix.setColumn(displayInUse, calculateXPixel(12) + i, colFive[i]);
        break;
      default:
        break;
    }
  }
  
  Serial.print("Left Highscore:   "); Serial.println(highscoreLeft);  //Printing the highscores in the serial monitor (just for debugging)  
  Serial.print("Right Highscore:  "); Serial.println(highscoreRight);

  //The highscore will be displayed until one of the joysticks buttons is pressed
  while (joystickBothButtonsPressed != true) {
    readJoysticks();
    delay(10);
  }
  joystickBothButtonsPressed = false;

  //If the left or the right highscore is 5, the game will be cancelled otherwise it will run again
  if (highscoreLeft >= 5 || highscoreRight >= 5) {
    delay(1500);
    gameOver(); //Printing game over until one of the joysticks buttons is pressed
    while (joystickBothButtonsPressed != true) {
      readJoysticks();
      delay(10);
    }
    joystickBothButtonsPressed = false;
    return true;  //The game will be cancelled
  }
  else {
    return false; //The game will run again
  }
}

//Printing Game Over
void gameOver() {
  Serial.println("Game Over");
  clearDisplays();
  displayInUse = display01;
  matrix.setColumn(displayInUse, 0, B01111100);
  matrix.setColumn(displayInUse, 1, B01000100);
  matrix.setColumn(displayInUse, 2, B01010100);
  matrix.setColumn(displayInUse, 3, B01011100);
  matrix.setColumn(displayInUse, 5, B01111100);
  matrix.setColumn(displayInUse, 6, B01000100);
  matrix.setColumn(displayInUse, 7, B01111100);
}


//Playing Pong
void playPong() {
  //Setting up variables for Pong
  bool pong = true;
  int pause = 200;  //Just for default
  int roundNumber = 0;  //Setting the round number to calculate the speed of the ball

  //Setting up variables for the highscore
  someoneScored = false;
  gameover = false;
  highscoreLeft = 0;
  highscoreRight = 0;

  //Setting up variables for the bats
  PongBat leftBat(2, 0);  //Creating the bat objects
  PongBat rightBat(2, 15);
  leftBatPositionPong = leftBat.getYPosition();
  rightBatPositionPong = rightBat.getYPosition();

  //Choosing the difficulty
  int difficulty = 4; //Just for default
  difficulty = PongChooseDifficulty(difficulty);

  //Setting everything up to play Pong
  clearDisplays();  //Clearing the displays
  PongSpawnBall();  //Spawning the ball
  leftBat.printBat(joystickLeftY);  //Printing the bats
  rightBat.printBat(joystickRightY);
  delay(1000);
  
  //Actually playing Pong
  while (pong == true) {
    roundNumber += 1; //Increasing the round number by one in every round
    readJoysticks();
    proofJoysticks();

    leftBat.printBat(joystickLeftY);  //Printing the left bat
    rightBat.printBat(joystickRightY);//Printing the right bat

    leftBatPositionPong  = leftBat.getYPosition();  //Getting the the y position of the left bat
    rightBatPositionPong = rightBat.getYPosition(); //Getting the the y position of the right bat

    PongMoveBall(difficulty); //Moving the ball (normal and when it collides) 

    //If someone scored a point the highscore will be printed and the game will maybe be over
    if (someoneScored == true) {
      someoneScored = false;
      gameover = printHighscore(highscoreLeft, highscoreRight);
      //If gamover is true the game is over
      if (gameover == true) {
        clearDisplays();
        pong = false;
        break;
      }

      //Resetting the important variables
      leftBatPositionPong = 2;
      rightBatPositionPong = 2;
      PongSpawnBall();
      roundNumber = 1;
      pause = 200;
      clearDisplays();
    }
    
    //Calculating the length of the pause
    pause = PongGameSpeed(pause, roundNumber, difficulty);
    delay(pause);
  }
}

//Function for returning the difficulty
int PongChooseDifficulty(int difficulty) {
  clearDisplays();
  int originalDifficulty;
  //Difficulty: 0 = Easy; 1 = Medium; 2 = Hard; 3 = Super Hard
  char colEasy[5]       = {B01111100, B01010100, B01010100, B01010100, B01010100};
  char colMedium[5]     = {B01111100, B00100000, B00010000, B00100000, B01111100};
  char colHard[5]       = {B01111100, B00010000, B00010000, B00010000, B01111100};
  char colSuperHard[5]  = {B01110100, B01010100, B01010100, B01010100, B01011100};
  
  while (difficulty > 3) {
    difficulty = 0;
    while (joystickBothButtonsPressed != true) {
      originalDifficulty = difficulty;
      readJoysticks();
      if ((joystickLeftX <300) || (joystickRightX <300)) {
        difficulty -= 1;
      }
      else if ((joystickLeftX > 724) || (joystickRightX > 724)) {
        difficulty += 1;
      }
      if (difficulty <= 0) {
        difficulty = 0;
      }
      if (difficulty >= 3) {
        difficulty = 3;
      }
      if (originalDifficulty != difficulty) {
        clearDisplays(); //Clearing both displays
      }
      displayInUse = display01;
      for (int i = 0; i < 5; i++) {
        switch (difficulty) {
          case 0:
            matrix.setColumn(displayInUse, 1 + i, colEasy[i]);
            difficulty = 0;
            break;
          case 1:
            matrix.setColumn(displayInUse, 1 + i, colMedium[i]);
            difficulty = 1;
            break;
          case 2:
            matrix.setColumn(displayInUse, 1 + i, colHard[i]);
            difficulty = 2;
            break;
          case 3:
            matrix.setColumn(displayInUse, 1 + i, colSuperHard[i]);
            difficulty = 3;
            break;
        }
      }
      delay(100);
    }
    joystickBothButtonsPressed = false;
  }
  return difficulty;
}

//Function for spawning the ball randomly
void PongSpawnBall() {
  //Setting up variables for the ball
  ballPositionXPong = random(6, 10); //Getting a random x position between 6 and 9 (including)
  ballPositionYPong = random(1, 6); //Getting a random y position between 1 and 5 (including)
  
  calculateDisplayToUse(ballPositionXPong);
  ballGoLeftPong = false; //Just for default
  //If the ball is on the left side of the display it will go to the right
  if (ballPositionXPong == 6 || ballPositionXPong == 7) {
    ballGoLeftPong = false;
  }
  //If the ball is on the right side of the display it will go to the left
  if (ballPositionXPong == 8 || ballPositionXPong == 9) {
    ballGoLeftPong = true;
  }
  
  ballGoUpPong = false;   //Just for default
  ballGoDownPong = false;

  matrix.setLed(displayInUse, ballPositionYPong, calculateXPixel(ballPositionXPong), true); //Printing the ball for the first time
}

//Function for moving the ball
void PongMoveBall(int difficulty) {
  calculateDisplayToUse(ballPositionXPong); //Getting the display which should be cleared
  matrix.setLed(displayInUse, ballPositionYPong, calculateXPixel(ballPositionXPong), false);  //Clearing the old ball position

  //If the dont hit one of the bats, someone has scored a point
  if (ballPositionXPong == 0) {
    highscoreRight += 1;
    someoneScored = true;
  }
  else if (ballPositionXPong == 15) {
    highscoreLeft += 1;
    someoneScored = true;
  }
  
  //Precalculation for the ball position
  else {
  //Ball x movement
    //Logic for moving the ball from the left to the right
    if (((leftBatPositionPong - 1 == ballPositionYPong) || (leftBatPositionPong == ballPositionYPong) || (leftBatPositionPong + 1 == ballPositionYPong)) && (ballPositionXPong == 1)) {
      ballGoLeftPong = false;
    }
    //Logic for moving the ball from the right to the left
    else if (((rightBatPositionPong - 1 == ballPositionYPong) || (rightBatPositionPong == ballPositionYPong) || (rightBatPositionPong + 1 == ballPositionYPong)) && (ballPositionXPong == 14)) {
      ballGoLeftPong = true;
    }
    
  //Ball Y movement on difficulty 0 and 1 (the ball will bounce of in a normal way)
    if (difficulty == 0 || difficulty == 1) {
      //Logic for moving the ball when it hits the upper part of the bats
      if (((leftBatPositionPong - 1 == ballPositionYPong) && (ballPositionXPong == 1)) || ((rightBatPositionPong - 1 == ballPositionYPong) && (ballPositionXPong == 14))) {
        ballGoUpPong = true;
        ballGoDownPong = false;
      }
      //Logic for moving the ball when it hits the middle part of the bats
      else if (((leftBatPositionPong == ballPositionYPong) && (ballPositionXPong == 1)) || ((rightBatPositionPong == ballPositionYPong) && (ballPositionXPong == 14))) {
        ballGoUpPong = false;
        ballGoDownPong = false;
      }
      //Logic for moving the ball when it hits the lower part of the bats
      else if (((leftBatPositionPong + 1 == ballPositionYPong) && (ballPositionXPong == 1)) || ((rightBatPositionPong + 1 == ballPositionYPong) && (ballPositionXPong == 14))) {
        ballGoUpPong = false;
        ballGoDownPong = true;
      }
    }

  //Ball Y movement on difficulty 2 and 3 (the ball will bounce of in a random way)
    if (difficulty == 2 || difficulty == 3) {
      int ballDirection = random(999) % 3 + 1; //Calculating a random number between 1 and 2 and 3
      if ((((leftBatPositionPong - 1 == ballPositionYPong) || (leftBatPositionPong == ballPositionYPong) || (leftBatPositionPong + 1 == ballPositionYPong)) && (ballPositionXPong == 1)) || (((rightBatPositionPong - 1 == ballPositionYPong) || (rightBatPositionPong == ballPositionYPong) || (rightBatPositionPong + 1 == ballPositionYPong)) && (ballPositionXPong == 14))) {
        //If ballDirection is 1 the ball will go up
        if (ballDirection == 1) {
          ballGoUpPong = true;
          ballGoDownPong = false;
        }
        //If ballDirection is 2 the ball will go straight to the other side
        if (ballDirection == 2) {
          ballGoUpPong = false;
          ballGoDownPong = false;
        }
        //If ballDirection is 3 the ball will go down
        if (ballDirection == 3) {
          ballGoUpPong = false;
          ballGoDownPong = true;
        }
      }
    }
     
    //If the ball hits the upper side of the display it will go down again
    if (ballPositionYPong == 0) {
      ballGoUpPong = false;
      ballGoDownPong = true;
    }
    //If the ball hits the lower side of the display it will go up again
    else if (ballPositionYPong == 7) {
      ballGoUpPong = true;
      ballGoDownPong = false;
    }
  }


  //Actual logic for moving the ball
  if (ballGoLeftPong == true) {
    ballPositionXPong -= 1;
  }
  else if (ballGoLeftPong == false) {
    ballPositionXPong += 1;
  }
  if (ballGoUpPong == true) {
    ballPositionYPong -= 1;
  }
  if (ballGoDownPong == true) {
    ballPositionYPong += 1;
  }
  
  calculateDisplayToUse(ballPositionXPong); //Getting the display on which should be printed
  matrix.setLed(displayInUse, ballPositionYPong, calculateXPixel(ballPositionXPong), true); //Actually moving the ball to the right place 
}

//Function for calculating the pause
int PongGameSpeed(int pause, int roundNumber, int difficulty) {
  if ((roundNumber % 12) == 0) {
    if (difficulty == 0) {
      if (pause >= 100) {
        pause -= 10; 
      }
    }
    if (difficulty == 1) {
      if (pause > 20) {
        pause -= 20; 
      }
    }
    if (difficulty == 2) {
      if (pause >= 100) {
        pause -= 10; 
      }
    }
    if (difficulty == 3) {
      if (pause > 20) {
        pause -= 20; 
      }
    }
  }

  return pause;
}
