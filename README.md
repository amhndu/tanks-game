#Mini Tanks#

This is an artillery, turn-based 2d game I made, which is far from complete yet but with mininal gameplay.  
It is inspired from Pocket Tanks and Scorched Earth.  
It features a fully destructible procedurally generated terrain, generated using simplex noise.  
SFML is used for Window creation, Graphics and Input.

###Controls and Objective###
Use your mouse to click on the HUD or press R to set the Rotation of the turret, similarly set power by clicking the power bar (or by hovering the cursor above it and using your scroll wheel)  
Use Arrow Keys Left or Right to move the Tank.  
Click on "FIRE" on the HUD or press Space to fire.  
The objective is very simple, destroy other tanks and you win.

###Source:###
[Github: amhndu/tanks-game](https://github.com/amhndu/tanks-game).

###Compiling:###
To compile you need a C++11 compiler and SFML 2.1.  
Download the source or clone the repository from github :
https://github.com/amhndu/tanks-game
and use cmake (or cmake-gui) to produce makefiles and/or project files.  

On a linux machine, these are the typical steps
```sh
$ git clone https://github.com/amhndu/tanks-game
    #Or otherwise download the source w/o git files and the entire history with:
    #wget https://github.com/amhndu/tanks-game/archive/master.zip
    #and then unzip
$ cd tanks-game
$ cmake .  #The dot it important
$ make
    #Now that it is compiled, you can run it .
$ ./miniTanks
```

###Executables:###
These are outdated by a few commits (which were only some fixes).
https://www.dropbox.com/s/ixu8g65mszea4b4/tanks-bin-win32.zip (compiled using g++ 4.8.1)
https://www.dropbox.com/s/v4shlyt8j8odv4e/tanks-bin-linux32.tar.gz (compiled using VC 2013 and requires VC2013 redistributable)
These are statically linked 32-bit executables.

###Video:###
[Youtube Video](http://www.youtube.com/watch?v=YbG_ej2fQKE)

###License
No rights reserved but in the unlikely event that you use anything, please drop me a [mail](mailto:amhndu@gmail.com).

###Contact me
email : amhndu@gmail.com
