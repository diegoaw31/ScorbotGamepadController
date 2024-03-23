# ScorbotGamepadController

Two scripts are included in this project.

The first one, a Python file, reads the inputs coming from a Logitech Gamepad F710, makes the data uniform by using two letter key codes and two bytes integers in order to send them via a COMX port where an Arduino or similar should be located.

The second Arduino script, reads and processes those commands in order to properly operate an Scorbot robotic manipulator along the joint space domain.
