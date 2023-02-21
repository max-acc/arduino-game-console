# Arduino GameConsole 

Version 1.0.0-r is now realeased. 

## Introduction
**Arduino GameConsole** is a code project with the goal of builing a game console with an Arduino.  
The orignal idea was to bring the game **Pong** on the Arduino (v1.0).  
The future approach is to bring more retro-ish games like **TicTacToe**, **Snake** or **PacMan** on Arduino.  
Below aren't all versions listed. If you want to see every version with every minor change, take a look at the releases.  


## How to get started
First you have to download the files with the code and the circuit. After that you have to download the libraries (choose from below). After you downloaded everything and rebuild the circuit, you are able to play **Pong**.  
When you compiled the program on the Arduino and started it, you have to choose the difficulty you want to play on and the game will start.  
Until v0.5.0 you can use the [LedControl](https://github.com/wayoda/LedControl) lib. For later versions you have to use the Adafruit libs ([NeoMatrix](https://github.com/adafruit/Adafruit_NeoMatrix), [NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel), [GFX](https://github.com/adafruit/Adafruit-GFX-Library))


## Progress

### Version 0
The primary goal of this version is to buid the game **Pong**.  
In this version the basic circuit has been constructed. Moreover the basic structure for making the game work has been developed.  
But accidently I messed up (I mixed up the x and y axis) and started all over again. So this is a non-working version.

### Version 0.1
This is the first fully working version of **Pong** on Arduino.  
The game control is pretty intuitive. If you move the left or right joystick up or down, the left or right bat will move up or down. If the ball hits a bat on the upper side it will go up, if the ball hits a bat on the lower side it will go down and if the ball hits in the middle it will go straight to the other side. If the ball hits the upper or the lower part of the screen it will also change its y direction. And if the ball hits the left or right side without a bat beeing behind, the player who shot receives a point.  
Another big thing of this version is the highscore system: If one of the players scores a point, the highscore will be printed. But the highscore only goes to three. If someone scores another point nothing will be printed. This will be solved in a future version.

### Version 0.2.1
This version is the second fully working version. The major changes in this version are about readability and efficiency referring to using functions multiple times and seperating functions from others to achieve a more global usage. Another thing is that the circuit has changed to use the joysticks buttons.  
Minor changes are about the ball spawnpoint and the highscore system. The ball  will spawn now randomly on a position where it is makeable for both players to hit the ball. The highscore has been increased to five, so the game takes longer, and if one of the players reaches five points, the game will be over (the message "GO" or "Game Over" will be printed). Those messages will be printed as long as none of the joystick's buttons is pressed.

### Version 0.3.0 (Full version for single color matrix)
This version includes the most significant changes according to usability and game play.  
The overall difficulty has been increased and it is now possible to choose the difficulty you want to play.  
If one of the joysticks gets moved to the left or the right the selection of the difficulties changes. If the difficulty is choosen the difficulty gets confirmed by a press on one of the joystick's buttons.    
The difficulties you can choose are:    
- Easy: The ball bounces off in a normal way and the speed of the ball and bats increase slowly, but it won't get that fast.
- Medium: The ball bounces off in a normal way but the speed of the ball and bats increase faster and it will get pretty fast.
- Hard: The ball bounces off in a random direction and speed is equal to Easy.
- Super Hard: Super hard is a mix of Medium and Hard. The ball bounces off in random directions and it will get pretty fast.  

Minor changes refer to small bugs fixes like the hihgscore system (the 2 has been outputtet in a wrong way as five xD) and improvements referring to the bats, which are now pixel by pixel calculated so the ball is able to be at the same y position as the bat which has caused unpleasant ball movements before (to achieve this the complete logic for the ball had to be changed).

### Version 0.5.0 (Full version for dual single color matrices)
A lot has changed since the last release (v0.3.0).  
One of the biggest changes according to the game is, that it is now possible to play the game on two instead of one matrices. The game is mostly optimized for both displays so both get used in an equal way, for example the left highscore gets displayed on the left matrix and the right highscore on the right display. The ball also moves accurate across both displays.  
There are also a lot of changes according to the bats! The bats are now objects (OOP) and get calculated and printed in this way. This makes the program more efficient and readable. The bats also only get redrawn if they really change, so its easier for your eyes. Furthermore the position of the bats are now calculated by the middle point and not the top one. This is a more logical.  
Another thing that changed is the overall difficulty. Because the display size has increased by 100% the game speed had to be adjusted. Moreover the whole code was rewritten and a lot of functions and variables had been renamed in a more logical way. There are also new variables and functions for better and more efficient navigation. The program is now also better commented.

### Version 0.6.0 (Full version for dual RGB matrices)
I thought that v0.3.0 brought the most significant changes, but I was wrong.  
This is the version with the most significant changes by a big margin. Why, here is why!  
The single color displays had been upgraded to RGB colors (so everything is faster and you are a better gamer while playing the game). The next big change is that the code now performs multitasking. Before the update you had to wait one iteration of the game to move the bats. Now you haven't!  
The overall efficiency and readability of the code has also been improved due to better variable renaming and more efficient variable declaration.  
The transitions on the display are now animated.

### Version 1.0
Version 1.0 is the complete version for the game Pong. After this point of time, there won't be any major changes to the game.  
With this Version it is possible to play Pong with two players on two RGB matrices.

## Roadmap

### Version 2.0
Goal: Building Conway's Game of Life.

### Version 3.0
Goal: Building the game TicTacToe.

### Version 4.0
Goal: Building the game Snake.

### Version 5.0
Goal: Building the game ConnectFour.

### Version 6.0
Goal: Building the game PacMan.
