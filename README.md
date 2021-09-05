# Arduino_GameConsole

## Introduction
The original idea about this project was to play the game **Pong** on an arduino.  
The first problem was how to display the game. The easiest solution for this problem was to use an 8x8 one-color LED matrix (I used four LED matrix in a row because I had nothing else lying around), but a future improvement could be to use a RGB matrix (maybe 16x16).


## Progress

### Version 1.0
Goal: Building the game Pong.  
In this version the basic circuit to play the game has been constructed. Moreover the basic structure for making the game work has been developed.  
But accidently I messed up (I mixed up the x and y axis) and started all over again. So this is a non-working version.

### Version 1.1
This is the first fully working version of **Pong** on arduino.  
The game control is pretty intuitive. If you move the left or right joystick up or down, the left or right bat will move up or down. If the ball hits a bat on the upper side it will go up, if the ball hits a bat on the lower side it will go down and if the ball hits in the middle it will go straight to the other side. If the ball hits the upper or the lower part of the screen it will also change its y direction. If the ball hits the left or right side without a bat beeing behind the player who shot receives a point.  
Another big thing of this version is the highscore system: If one of the players scores a point the highscore will be printed. But the highscore only goes to three. If someone scores another point nothing will be printed. This will be solved in a future version.

### Version 1.2.0
This version was about improving efficiency of the code and providing a better documentation of the code.  
Accidentally the code was messed up again and the only solution for this problem was to develop a new version and write it all over again.  
Updated circiut

### Version 1.2.1
This version improves efficiency and readability of the code. The spawnpoint of the ball has also been updated. It will spawn now randomly on a position where it is makeable for both players to hit the ball. The highscore has been increased to five so the game takes longer. Those changes made the game more fun to play.

### Version 1.2.2
This version includes minor bug fixes and improvements referring to the bats and the highscore system (the 2 has been outputted in a wrong way). The bats are now pixel by pixel calculated and the ball is able to be at the same y-position as the bats.

### Version 1.3.0
This is the currently work-in-progress-version.  
This version includes the most significant changes according to usability and game play.  
It is now possible to select different difficulties. The overall difficulty has also increased.  
The difficulties you can choose are:    
- Easy: The ball bounces of in a normal way and the speed of the ball and bats increase slowly, but it won't get that fast.
- Medium: The ball bounces of in a normal way but the speed of the ball and bats increase faster and it will get pretty fast.
- Hard: The ball bounces off in a random direction and speed is equal to Easy.
- Super Hard: Super hard is a mix of Medium and Hard. The ball bounces off in random directions and it will get pretty fast.

## Roadmap

### Version 1.4.0
Preparing the program for version 2.0.  
It will be about renaming the variables and functions which are only referring to Pong.

### Version 2.0
Goal: Building the game TicTacToe.

### Version 3.0
Goal: Building the game Snake.

### Version 4.0
Goal: Building the game ConnectFour.

### Version 5.0
Goal: Building the game PacMan.
