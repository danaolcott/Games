80's Style Video Games Built on the STM32F429 Discovery Board
-------------------------------------------------------------

Pong/Breakout
-------------
I called this pong but then was reminded that it more closely resembles the 80's style game Breakout.  The game is built on the STM32F429 Discovery board and implements the touchscreen to move the paddle, a user button to toggle between game modes, and DAC output for sound.  The object of the game is to bounce the ball off angry bird images to clear the screen.  The game speed increases each level.  Low level hardware drivers were auto generated using STCube tool and the project built using TrueStudio.

![alt text](https://raw.githubusercontent.com/danaolcott/Games/master/Source/images/20171121_094426.jpg)



Asteroids
--------
Mystery Machine vs Angry Birds!!  The game is built on the STM32F429 Discovery board.  Player ship is controlled using an analog or digital joystick.  The onboard user button is used to fire Scooby snacks at Angry Birds from the Mystery Machine.  Angry Birds randomly alter trajectory and the game speed increases with each level.  Game sounds output from the onboard DAC (PA5).  Low level hardware drivers were auto generated using STCube tool and the project built using TrueStudio.  The game is actually a lot of fun to play.  Sounds are generated from wav files converted to 8bit arrays.  The sound quality is a work in progress.

External Connections:
Joystick - Analog (See Joystick.h to configure)
- Vertical: PF6
- Horizontal: PC3

Joystick - Digital (See Joystick.h to configure)
- Left - PD2 (Add 10k pullup)
- Right - PD4 (Add 10k pullup)
- Up - PD5 (Add 10k pullup)
- Down - PD7 (Add 10k pullup)

Sound - DAC Output - PA5

![alt text](https://raw.githubusercontent.com/danaolcott/Games/master/Source/images/astroids.jpg)


