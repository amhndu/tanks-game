Mini Tanks
=============

Project page : http://amhndu.github.io/Projects/mini-tanks.html

A turn-based, artillery game where you destroy other tanks to win in a fully destructible, procedurally generated terrain. Supports multiplayer with upto 8 local players.
This was inspired by Pocket Tanks and Scorched Earth.
Programmed in C++11 with SFML used for graphics.

Controls and Objective
------------------------
Use your mouse to click on the HUD or press R to set the Rotation of the turret, similarly set power by clicking the power bar (or by hovering the cursor above it and using your scroll wheel)  
Use Arrow Keys Left or Right to move the Tank.  
Click on "FIRE" on the HUD or press Space to fire.  
The objective is very simple, destroy other tanks and you win.

Source:
------------------------
[Github: amhndu/tanks-game](https://github.com/amhndu/tanks-game).

Screenshots
------------------------
![Screenshot 1](http://amhndu.github.io/Projects/screenshots/tanks0.jpg)
![Screenshot 2](http://amhndu.github.io/Projects/screenshots/tanks1.jpg)
![Screenshot 3](http://amhndu.github.io/Projects/screenshots/tanks2.jpg)
![Screenshot 4](http://amhndu.github.io/Projects/screenshots/tanks3.jpg)
![Screenshot 5](http://amhndu.github.io/Projects/screenshots/tanks4.jpg)

Video
-------------------------
[Youtube Video](http://www.youtube.com/watch?v=YbG_ej2fQKE)

Compiling
--------------------------
You need a C++11 compliant compiler and [SFML 2.0+](http://sfml-dev.org) to compile *Mini Tanks*. After you've downloaded the source and dependencies, you can use [cmake](http://cmake.org) to compile *Mini Tanks*.  
On any Linux distribution, these are the typical steps :  
```
$ git clone https://github.com/amhndu/tanks-game
$ cd tanks-game
$ cmake .
$ make
```
If you don't have cmake and don't wish to install it either, then you can simply compile Mini Tanks by compiling all the cpp files and then linking them with SFML using your IDE/compiler. e.g. With g++, you can enter this command :
```
$ g++ -o miniTanks *.cpp -std=c++11 -lsfml-graphics -lsfml-window -lsfml-system
```
Note : To compile on windows, you also need to link the sfml-main component.

Download
--------------------------
[Download the source](https://github.com/amhndu/tanks-game/archive/master.zip)
Executables :
Note : These are outdated by a few commits (which were only some fixes). It is recommended to compile Mini Tanks from source if you can.
[Linux 32-bit](https://www.dropbox.com/s/v4shlyt8j8odv4e/tanks-bin-linux32.tar.gz) (compiled using g++ 4.8.1)
[Windows 32-bit](https://www.dropbox.com/s/ixu8g65mszea4b4/tanks-bin-win32.zip) (compiled using VC 2013 and requires VC2013 redistributable)


Contact me
----------------------------
Email : amhndu --at-- gmail --period-- com
