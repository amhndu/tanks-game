#miniTanks#
####(made by Amish Kumar Naidu)####

This is an artillery , turn-based 2d game I made, which is far from complete yet but it does have some gameplay.
It is inspired from Pocket Tanks and Scorched Earth.
It features a fully destructible procedurally generated terrain , generated using simplex noise.
SFML is used for Window creation,Graphics and Input.

###Controls and Objective###
Use mouse to click on the HUD to start setting Rotation(or press R) of the turret or power by moving your mouse left or right.
While setting rotation you'll see a cross hair helping you set the angle and
while setting power , the power gauge's outline will change from Black to Red.
Use Arrow Keys Left or Right to move the Tank.
Click on "FIRE" on the HUD or press Space to fire.
It is a very simple game , destroy other tanks and you win, with only one type of weapon.

###Source:###
[Github: amhndu/tanks-game](https://github.com/amhndu/tanks-game).

###Compiling:###
To compile you need a C++11 compiler and SFML 2.1.
Download the source or clone the repository from github :
https://github.com/amhndu/tanks-game
and use cmake (or cmake-gui) to produce make,nmake or whatever...

On a linux machine , these are the typical steps
```sh
$ git clone https://github.com/amhndu/tanks-game
    #Or otherwise only download the source w/o git files
    #wget https://github.com/amhndu/tanks-game/archive/master.zip and unzip
$ cd tanks-game
$ cmake .  #The dot it important
$ make
    #Now that it is compiled ,you can run it .
$ ./miniTanks
```

###Executables:###
These are outdated.
https://www.dropbox.com/s/ixu8g65mszea4b4/tanks-bin-win32.zip (compiled using g++ 4.8.1)
https://www.dropbox.com/s/v4shlyt8j8odv4e/tanks-bin-linux32.tar.gz (compiled using VC 2013 and requires VC2013 redistributable)
These are statically linked 32-bit executables.

###Video:###
[Youtube link](http://www.youtube.com/watch?v=YbG_ej2fQKE)

For any comments/advice or just to say hi :)

email me : amhndu@gmail.com
