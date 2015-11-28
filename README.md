laptopAngle
==========
`laptopAngle` measures the value and angle from a "joystick" using SDL.
Some laptops sport an accelerometer that are joystick-like inputs,
  so this let you use the angle of your laptop to trigger some events
  like suspend (so the battery never dies warming your bag).

This project is a straightfoward modification of sdl-jstest by
  Ingo Ruhnke (github.com/Grumbel)

Requirements
------------

* cmake
* libsdl1


Compilation
-----------
    mkdir build && cd build
    cmake ..
    make

Getting the correct angle
-------------------------
I don't think that accelerometer orientation is standard, so if
  you get wrong values that vary according to the angle, you need
  to check the geometry a bit. It should be easy once you recognize
  the vertical axis.
