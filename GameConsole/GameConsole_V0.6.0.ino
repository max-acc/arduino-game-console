//Pong V 1.6.0
//by Max Wenk
//
//http://aliencorporation.cf
//
//Final version including some readability changes



//Including libraries
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

//Setting up timestamps for multitasking
unsigned long lastMillisPongBall;
unsigned long lastMillisPongBat;

//Initialising the joysticks and the button
uint16_t joystickLeftY;
uint16_t joystickLeftX;
uint16_t joystickLeftButton;
uint16_t joystickRightY;
uint16_t joystickRightX;
uint16_t joystickRightButton;
uint8_t button = 7;
bool joystickBothUp;
bool joystickBothDown;
bool joystickBothLeft;
bool joystickBothRight;
bool joystickBothButtonsPressed;
bool buttonstatus = false;


//Initialising the matrices
const uint8_t matrixPin    = 6;
const uint8_t matrixWidth  = 8;
const uint8_t matrixHeight = 8;
const uint8_t matrixTilesX = 2;
const uint8_t matrixTilesY = 1;

//Standard variables for maybe later use
const uint8_t totalWidth  = matrixWidth * matrixTilesX;
const uint8_t totalHeight = matrixHeight * matrixTilesY;
const uint8_t totalPixels = totalWidth * totalHeight;
uint8_t matrixBrightness = 5;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(matrixWidth, matrixHeight, matrixTilesY, matrixTilesX, matrixPin,
  NEO_TILE_TOP   + NEO_TILE_LEFT   + NEO_TILE_ROWS   + NEO_TILE_PROGRESSIVE +
  NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB + NEO_KHZ800);

  
//Initialising the colors
//Basic colors
const uint16_t clearColor  = matrix.Color(0, 0, 0);
const uint16_t red         = matrix.Color(255, 0, 0);
const uint16_t green       = matrix.Color(0, 255, 0);
const uint16_t blue        = matrix.Color(0, 0, 255);
const uint16_t white       = matrix.Color(255, 255, 255);

//Pong colors
const uint16_t bluePong   = matrix.Color(76, 218, 255);
const uint16_t redPong    = matrix.Color(255, 0, 0);
const uint16_t whitePong  = matrix.Color(255, 255, 255);


//Single Function for printing numbers or characters on the matrices
void drawCharacter(int8_t y, int8_t x, String character, uint16_t color, uint8_t width = 4) {
  //Printing numbers from zero to five; width = 4
  if(character == "0") {
    matrix.drawLine(y, x, y, x+2, color);
    matrix.drawLine(y+5, x, y+5, x+2, color);
    matrix.drawLine(y, x, y+5, x, color);
    matrix.drawLine(y, x+2, y+5, x+2, color);
  } else if(character == "1") {
    matrix.drawLine(y, x+1, y+5, x+1, color);
    matrix.drawLine(y+5, x, y+5, x+2, color);
    matrix.drawPixel(y+1, x, color);
  } else if(character == "2") {
    matrix.drawLine(y, x, y, x+2, color);
    matrix.drawLine(y, x+2, y+3, x+2, color);
    matrix.drawLine(y+3, x, y+3, x+2, color);
    matrix.drawLine(y+3, x, y+5, x, color);
    matrix.drawLine(y+5, x, y+5, x+2, color);
  } else if(character == "3") {
    matrix.drawLine(y, x, y, x+2, color);
    matrix.drawLine(y+3, x, y+3, x+2, color);
    matrix.drawLine(y+5, x, y+5, x+2, color);
    matrix.drawLine(y, x+2, y+5, x+2, color);
  } else if(character == "4") {
    matrix.drawLine(y, x, y+2, x, color);
    matrix.drawLine(y+3, x, y+3, x+1, color);
    matrix.drawLine(y+2, x+2, y+5, x+2, color);
  } else if(character == "5") {
    matrix.drawLine(y, x, y, x+2, color);
    matrix.drawLine(y, x, y+3, x, color);
    matrix.drawLine(y+3, x, y+3, x+2, color);
    matrix.drawLine(y+3, x+2, y+5, x+2, color);
    matrix.drawLine(y+5, x, y+5, x+2, color);
  }
  
  //Printing characters; width = 4
  else if(character == "E" && width == 4) {
    matrix.drawLine(y, x+1, y, x+3, color);
    matrix.drawLine(y+3, x+1, y+3, x+3, color);
    matrix.drawLine(y+5, x+1, y+5, x+3, color);
    matrix.drawLine(y, x, y+5, x, color);
  } else if(character == "M" && width == 4) {
    matrix.drawLine(y, x, y+5, x, color);
    matrix.drawLine(y+1, x+1, y+1, x+2, color);
    matrix.drawLine(y, x+3, y+5, x+3, color);
  } else if(character == "H" && width == 4) {
    matrix.drawLine(y, x, y+5, x, color);
    matrix.drawLine(y+3, x+1, y+3, x+2, color);
    matrix.drawLine(y, x+3, y+5, x+3, color);
  } else if(character == "S" && width == 4) {
    matrix.drawLine(y, x, y, x+3, color);
    matrix.drawLine(y, x, y+3, x, color);
    matrix.drawLine(y+3, x, y+3, x+2, color);
    matrix.drawLine(y+3, x+3, y+5, x+3, color);
    matrix.drawLine(y+5, x, y+5, x+2, color);
  }
  
  //Printing characters; width = 5
  else if(character == "G" && width == 5) {
    matrix.drawLine(y, x+1, y, x+4, color);
    matrix.drawLine(y+1, x, y+3, x, color);
    matrix.drawLine(y+4, x+1, y+4, x+4, color);
    matrix.drawLine(y+2, x+4, y+4, x+4, color);
    matrix.drawPixel(y+2, x+3, color);
  } else if(character == "A" && width == 5) {
    matrix.drawLine(y+2, x, y+4, x, color);
    matrix.drawLine(y+2, x+4, y+4, x+4, color);
    matrix.drawLine(y+3, x+1, y+3, x+3, color);
    matrix.drawPixel(y, x+2, color);
    matrix.drawPixel(y+1, x+1, color);
    matrix.drawPixel(y+1, x+3, color);
  } else if(character == "M" && width == 5) {
    matrix.drawLine(y, x, y+4, x, color);
    matrix.drawLine(y, x+4, y+4, x+4, color);
    matrix.drawPixel(y+1, x+1, color);
    matrix.drawPixel(y+1, x+3, color);
    matrix.drawPixel(y+2, x+2, color);
  } else if(character == "E" && width == 5) {
    matrix.drawLine(y, x, y+4, x, color);
    matrix.drawLine(y, x+1, y, x+4, color);
    matrix.drawLine(y+2, x+1, y+2, x+2, color);
    matrix.drawLine(y+4, x+1, y+4, x+4, color);
  } else if(character == "O" && width == 5) {
    matrix.drawLine(y+1, x, y+3, x, color);
    matrix.drawLine(y, x+1, y, x+3, color);
    matrix.drawLine(y+4, x+1, y+4, x+3, color);
    matrix.drawLine(y+1, x+4, y+3, x+4, color);
  } else if(character == "V" && width == 5) {
    matrix.drawLine(y, x, y+2, x, color);
    matrix.drawLine(y, x+4, y+2, x+4, color);
    matrix.drawPixel(y+3, x+1, color);
    matrix.drawPixel(y+3, x+3, color);
    matrix.drawPixel(y+4, x+2, color);
  } else if(character == "R" && width == 5) {
    matrix.drawLine(y, x, y+4, x, color);
    matrix.drawLine(y, x+1, y, x+3, color);
    matrix.drawLine(y+2, x+1, y+2, x+3, color);
    matrix.drawLine(y+3, x+4, y+4, x+4, color);
    matrix.drawPixel(y+1, x+4, color);
  }
}


//Initialising the variables for creating a highscore
uint8_t highscoreLeft;
uint8_t highscoreRight;
bool someoneScored;
bool gameover;


//Global Pong variables
uint8_t leftBatPositionPong;
uint8_t rightBatPositionPong;

bool ballGoLeftPong;
bool ballGoUpPong;
bool ballGoDownPong;

uint8_t ballPositionXPong;
uint8_t ballPositionYPong;

//Creating a class to calculate and print the bats
class PongBat {
  //Setting up the variables
  int8_t yPosition, originalYPosition, xPosition;
  uint16_t color;

  public:
  //Constructor for the bats
  PongBat(int8_t yPositionGet, int8_t xPositionGet, uint16_t colorGet) {
    yPosition = yPositionGet;
    xPosition = xPositionGet;
    color = colorGet;
  }

  //Function for printing the bat
  void printBat(uint16_t yPositionJoystick) {
    originalYPosition = yPosition;
    yPosition = logicJoystick(yPositionJoystick);
    
    //if (originalYPosition != yPosition) {
      matrix.drawLine(0, xPosition, 7, xPosition, clearColor);  //Clearing the column to print the new bat position, but only if the bat position is not the same as before     
    //}
    
    //Printing the bat
    matrix.drawLine(yPosition, xPosition, yPosition+2, xPosition, color);
    matrix.show();
  }

  //Function for calculating the bat position with the usage of the joysticks
  uint8_t logicJoystick(uint16_t yPositionJoystick) {
    //If the value of the left Joystick is lower than 200 the Joystick will be moved down by one unit
    if (yPositionJoystick < 200) {
      yPosition += 1;
    }
    //If the value of the left Joystick is higher than 823 the Joystick will be moved up by one unit
    if (yPositionJoystick > 824) {
      yPosition -= 1;
    }
  
    //If the Bat position is lower than 0 or higher than 5 the values get adjusted to values which are legit to use for printing the bat
    if (yPosition < 0) {
      yPosition = 0;
    }
    if (yPosition > 5) {
      yPosition = 5;
    }
    //The y position of the left bat will be returned
    return yPosition;
  }

  //Returning the y position
  uint8_t getYPosition() {
    return yPosition;
  }
  //Returning the color
  uint16_t getColor() {
    return color;
  }
};


void setup() {
  Serial.begin(9600); //Starting the serial monitor

  //Initialising the timestamp
  lastMillisPongBall = millis();
  lastMillisPongBat = millis();
  
  //Setting up the matrices
  matrix.setBrightness(matrixBrightness);
  matrix.begin();
}

void loop() {
  matrix.clear();  
  readJoysticks();
  uint8_t gameName = 1;
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


//Reading the joysticks and buttons
void readJoysticks() {
  //Reading the values from the joysticks
  joystickLeftY = analogRead(A0);
  joystickLeftX = analogRead(A1);
  joystickLeftButton = analogRead(A2);
  joystickRightY = analogRead(A3);
  joystickRightX = analogRead(A4);
  joystickRightButton = analogRead(A5);
  buttonstatus = digitalRead(button);
  
  //If one of the two joysticks is up, there will be one output
  if ((joystickLeftY <300) || (joystickRightY <300)) {
    joystickBothUp = true;
  }
  else {
    joystickBothUp = false;
  }
  
  //If one of the two joysticks is down, there will be one output
  if ((joystickLeftY >724) || (joystickRightY >724)) {
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
  if ((joystickLeftX >724) || (joystickRightX >724)) {
    joystickBothRight = true;
  }
  else {
    joystickBothRight = false;
  }
  
  //If one of the two joysticks buttons is pressed, there will be one output
  if ((joystickLeftButton <90) || (joystickRightButton <90)) {
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

//Printing the highscore for mulitplayer games
bool printHighscoreMultiplayer(const uint16_t leftPlayerColor, const uint16_t rightPlayerColor) {
  matrix.clear();
  //Printing the left highscore on the left display
  switch (highscoreLeft) {
    case 0:
      drawCharacter(1, 2, "0", leftPlayerColor);
      break;
    case 1:
      drawCharacter(1, 2, "1", leftPlayerColor);
      break;
    case 2:
      drawCharacter(1, 2, "2", leftPlayerColor);
      break;
    case 3:
      drawCharacter(1, 2, "3", leftPlayerColor);
      break;
    case 4:
      drawCharacter(1, 2, "4", leftPlayerColor);
      break;
    case 5:
      drawCharacter(1, 2, "5", leftPlayerColor);
      break;
    default:
      break;
  }
  //Printing the right highscore on the right display
  switch (highscoreRight) {
    case 0:
      drawCharacter(1, 11, "0", rightPlayerColor);
      break;
    case 1:
      drawCharacter(1, 11, "1", rightPlayerColor);
      break;
    case 2:
      drawCharacter(1, 11, "2", rightPlayerColor);
      break;
    case 3:
      drawCharacter(1, 11, "3", rightPlayerColor);
      break;
    case 4:
      drawCharacter(1, 11, "4", rightPlayerColor);
      break;
    case 5:
      drawCharacter(1, 10, "5", rightPlayerColor);
      break;
    default:
      break;
  }
  matrix.show();
  Serial.print("Left Highscore:   "); Serial.println(highscoreLeft);  //Printing the highscores in the serial monitor (just for debugging)  
  Serial.print("Right Highscore:  "); Serial.println(highscoreRight);

  //The highscore will be displayed until the button is pressed
  while (buttonstatus != true) {
    readJoysticks();
    delay(10);
  }
  buttonstatus = false;

  //If the left or the right highscore is 5, the game will be cancelled otherwise it will run again
  if (highscoreLeft >= 5 || highscoreRight >= 5) {
    delay(1500);
    gameOver(); //Printing game over until one of the joysticks buttons is pressed
    matrix.show();
    while (buttonstatus != true) {
      readJoysticks();
      delay(10);
    }
    buttonstatus = false;
    return true;  //The game will be cancelled
  }
  else {
    return false; //The game will run again
  }
}

//Resetting the highscore
void resetHighscore() {
  highscoreLeft  = 0;
  highscoreRight = 0;
  someoneScored = false;
  gameover = false;
}

//Printing Game Over
void gameOver() {
  //Animation for Game Over
  matrix.clear();
  int8_t originalXPosition = 0;
  for (int8_t i = 16; i > -50; i--) {
    matrix.clear();
    drawCharacter(1, originalXPosition + i,          "G", whitePong, 5);
    drawCharacter(1, originalXPosition + i + 6,      "A", whitePong, 5);
    drawCharacter(1, originalXPosition + i + 12,     "M", whitePong, 5);
    drawCharacter(1, originalXPosition + i + 18,     "E", whitePong, 5);
    drawCharacter(1, originalXPosition + i + 26,     "O", whitePong, 5);
    drawCharacter(1, originalXPosition + i + 32,     "V", whitePong, 5);
    drawCharacter(1, originalXPosition + i + 38,     "E", whitePong, 5);
    drawCharacter(1, originalXPosition + i + 44,     "R", whitePong, 5);
    matrix.show();
    delay(100);
  }
  
  //End display for showing Game Over
  matrix.clear();
  drawCharacter(1, 2, "G", white, 5);
  drawCharacter(1, 9, "G", white, 5);
  matrix.show();
}

//Clearing a single display
void clearLeftDisplay() {
  matrix.fillRect(0, 0, 8, 8, clearColor);
}
void clearRightDisplay() {
  matrix.fillRect(0, 8, 8, 8, clearColor);
}

//Playing Pong
void playPong() {
  //Setting up vaiables for Pong
  bool pong = true; //Just for default
  uint16_t pause = 300;
  uint8_t roundNumber = 0;
  resetHighscore();
  
  //Creating the bat objects and setting up variables for the bats
  PongBat leftBat(2, 0, bluePong);
  PongBat rightBat(2, 15, redPong);
  leftBatPositionPong = leftBat.getYPosition();
  rightBatPositionPong = rightBat.getYPosition();

  //Choosing the difficulty
  int8_t difficulty = 4; //Just for default
  difficulty = PongChooseDifficulty(difficulty);

  //Setting everything up to play Pong
  matrix.clear();
  PongSpawnBall();
  leftBat.printBat(joystickLeftY);
  rightBat.printBat(joystickRightY);
  delay(1000);
  lastMillisPongBall = millis();
  lastMillisPongBat = millis();

  //Actually playing Pong
  while (pong == true) {
    
    readJoysticks();

    //The bats will only get redrawn every 50 milliseconds because without it would be unplayable
    if ((millis() - lastMillisPongBat) >= 50) {
      leftBat.printBat(joystickLeftY);  //Printing the left bat
      rightBat.printBat(joystickRightY);//Printing the right bat
      lastMillisPongBat = millis();
    }

    leftBatPositionPong  = leftBat.getYPosition();  //Getting the the y position of the left bat
    rightBatPositionPong = rightBat.getYPosition(); //Getting the the y position of the right bat
    
    //The ball will not been recalculated and redrawn until the pause has ended
    if ((millis() - lastMillisPongBall) >= pause) {
      PongMoveBall(difficulty); //Moving the ball (normal and when it collides) 
      lastMillisPongBall = millis();
      roundNumber += 1; //Increasing the round number by one in every round (the round number only can get calculated after the ball has moved)
      //Calculating the length of the pause
      pause = PongGameSpeed(pause, roundNumber, difficulty);
    }
    

    //If someone scored a point the highscore will be printed and the game will maybe be over
    if (someoneScored == true) {
      someoneScored = false;
      gameover = printHighscoreMultiplayer(leftBat.getColor(), rightBat.getColor());
      //If gamover is true the game is over
      if (gameover == true) {
        matrix.clear();
        pong = false;
        break;
      }

      //Resetting the important variables
      leftBatPositionPong = 2;
      rightBatPositionPong = 2;
      PongSpawnBall();
      roundNumber = 1;
      pause = 200;
      matrix.clear();
    }
  } 
}

//Function for returning the difficulty
uint8_t PongChooseDifficulty(int8_t difficulty) {
  matrix.clear();
  int8_t originalDifficulty;
  int8_t xPosition = 2;
  int8_t originalXPosition;
  //Difficulty: 0 = Easy; 1 = Medium; 2 = Hard; 3 = Super Hard
  
  while (difficulty > 3) {
    matrix.clear();
    difficulty = 0; //Just for default
    //As long as no button is pressed, the difficulty is chooseable
    while (buttonstatus != true) {
      matrix.clear();
      originalDifficulty = difficulty;
      originalXPosition = xPosition;
      readJoysticks();
      //If the left or the right joystick is on the left, the difficulty decrease
      if ((joystickLeftX <300) || (joystickRightX <300)) {
        difficulty -= 1;
      }
      //If the left or the right joystick is on the right, the difficulty increase
      else if ((joystickLeftX > 724) || (joystickRightX > 724)) {
        difficulty += 1;
      }
      //Logic for preventing the code of unexpected output
      if (difficulty <= 0) {
        difficulty = 0;
      }
      if (difficulty >= 3) {
        difficulty = 3;
      }
      
      //Setting the x position for outputting the difficulty on the matrices
      switch (difficulty) {
        case 0:
          xPosition = 2;
          break;
        case 1:
          xPosition = -4;
          break;
        case 2:
          xPosition = -10;
          break;
        case 3:
          xPosition = -16;
          break;
      }
      //Only if the the choosen difficulty has changed, the difficulty will be reprinted on the matrices (prevents from annoying display flickering)
      if (originalDifficulty != difficulty) {
        while (originalXPosition != xPosition) {
          matrix.clear();
          //Animating the characters when they go to the right
          if (originalXPosition < xPosition) {
            originalXPosition += 1;
            drawCharacter(1, originalXPosition,     "E", whitePong);
            drawCharacter(1, originalXPosition + 6, "M", whitePong);
            drawCharacter(1, originalXPosition + 12,"H", whitePong);
            drawCharacter(1, originalXPosition + 18,"S", whitePong);
          }
          //Animating the characters when they go to the left
          if (originalXPosition > xPosition) {
            originalXPosition -= 1;
            drawCharacter(1, originalXPosition,     "E", whitePong);
            drawCharacter(1, originalXPosition + 6, "M", whitePong);
            drawCharacter(1, originalXPosition + 12,"H", whitePong);
            drawCharacter(1, originalXPosition + 18,"S", whitePong);
          }
          clearRightDisplay();
          matrix.show();
          delay(50);
        }
      }
      //Printing characters after they have been animated
      matrix.clear();
      drawCharacter(1, xPosition,      "E", whitePong);
      drawCharacter(1, xPosition + 6,  "M", whitePong);
      drawCharacter(1, xPosition + 12, "H", whitePong);
      drawCharacter(1, xPosition + 18, "S", whitePong);
      clearRightDisplay();
      matrix.show();
      delay(100);
    }
    buttonstatus = false;
  }
  matrix.clear();
    return difficulty;  //Returning the difficulty
}

//Function for spawning the ball randomly
void PongSpawnBall() {
  //Setting up variables for the ball
  ballPositionXPong = random(6, 10); //Getting a random x position between 6 and 9 (including)
  ballPositionYPong = random(1, 6); //Getting a random y position between 1 and 5 (including)
  
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

  matrix.drawPixel(ballPositionYPong, ballPositionXPong, whitePong); //Printing the ball for the first time
  matrix.show();
}

//Function for moving the ball
void PongMoveBall(uint8_t difficulty) {
  matrix.drawPixel(ballPositionYPong, ballPositionXPong, clearColor);  //Clearing the old ball position

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
    if (((leftBatPositionPong + 2 == ballPositionYPong) || (leftBatPositionPong == ballPositionYPong) || (leftBatPositionPong + 1 == ballPositionYPong)) && (ballPositionXPong == 1)) {
      ballGoLeftPong = false;
    }
    //Logic for moving the ball from the right to the left
    else if (((rightBatPositionPong + 2 == ballPositionYPong) || (rightBatPositionPong == ballPositionYPong) || (rightBatPositionPong + 1 == ballPositionYPong)) && (ballPositionXPong == 14)) {
      ballGoLeftPong = true;
    }
    
  //Ball Y movement on difficulty 0 and 1 (the ball will bounce of in a normal way)
    if (difficulty == 0 || difficulty == 1) {
      //Logic for moving the ball when it hits the upper part of the bats
      if (((leftBatPositionPong == ballPositionYPong) && (ballPositionXPong == 1)) || ((rightBatPositionPong == ballPositionYPong) && (ballPositionXPong == 14))) {
        ballGoUpPong = true;
        ballGoDownPong = false;
      }
      //Logic for moving the ball when it hits the middle part of the bats
      else if (((leftBatPositionPong + 1 == ballPositionYPong) && (ballPositionXPong == 1)) || ((rightBatPositionPong + 1 == ballPositionYPong) && (ballPositionXPong == 14))) {
        ballGoUpPong = false;
        ballGoDownPong = false;
      }
      //Logic for moving the ball when it hits the lower part of the bats
      else if (((leftBatPositionPong + 2 == ballPositionYPong) && (ballPositionXPong == 1)) || ((rightBatPositionPong + 2 == ballPositionYPong) && (ballPositionXPong == 14))) {
        ballGoUpPong = false;
        ballGoDownPong = true;
      }
    }

  //Ball Y movement on difficulty 2 and 3 (the ball will bounce of in a random way)
    if (difficulty == 2 || difficulty == 3) {
      uint8_t ballDirection = random(999) % 3 + 1; //Calculating a random number between 1 and 2 and 3
      if ((((leftBatPositionPong + 2 == ballPositionYPong) || (leftBatPositionPong == ballPositionYPong) || (leftBatPositionPong + 1 == ballPositionYPong)) && (ballPositionXPong == 1)) || (((rightBatPositionPong + 2 == ballPositionYPong) || (rightBatPositionPong == ballPositionYPong) || (rightBatPositionPong + 1 == ballPositionYPong)) && (ballPositionXPong == 14))) {
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
  
  matrix.drawPixel(ballPositionYPong, ballPositionXPong, whitePong); //Actually moving the ball to the right place 
  matrix.show();
}

//Function for calculating and returning the pause
uint16_t PongGameSpeed(uint16_t pause, uint8_t roundNumber, uint8_t difficulty) {
  //If the ball has moved 12 times the gamespeed will increase
  if ((roundNumber % 12) == 0) {
    //If the difficulty is 0 (Easy), the pause will be decreased by 10 until the speed is 80
    if (difficulty == 0) {
      if (pause >= 70) {
        pause -= 10; 
      }
    }
    //If the difficulty is 1 (Medium), the pause will be decreased by 20 until the speed is 60
    if (difficulty == 1) {
      if (pause > 60) {
        pause -= 20; 
      }
    }
    //If the difficulty is 2 (Hard), the pause will be decreased by 10 until the speed is 90
    if (difficulty == 2) {
      if (pause >= 100) {
        pause -= 10; 
      }
    }
    //If the difficulty is 3 (Super Hard), the pause will be decreased by 20 until the speed is 60
    if (difficulty == 3) {
      if (pause > 60) {
        pause -= 20; 
      }
    }
  }
  //The length of the pause will be returned
  return pause;
}
