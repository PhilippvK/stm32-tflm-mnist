# MNIST Example

This demo implements a simple handwriting recognizer, which can transcribe digits from 0 to 9 into characters. It uses a CNN architecture and can display the percent of confidence the CNN delivers for each of the 10 possible outputs.

Moreover, the input can be taken either from the touchscreen, enabling us to draw the digits ourselves, or from images showing digits loaded from the memory card.

## Build
### Project configuration
Firstly, you have to choose whether you want to use the board's touchscreen to draw and recognize digits real-time, or load pre-recorded samples from the SD card. You make this choice by setting **FAKE_TOUCH** on line 72 in ```CMakeLists.txt``` to either ON or OFF.
```
SET(FAKE_TOUCH OFF) # Use on board touchscreen
SET(FAKE_TOUCH ON) # Use samples from the SD card
```
By default, we are using the board's built-in touchscreen.
For actual samples and the required file structure, see the [media folder](../../media/README.md). 

Finally, simply run:
```
mkdir build
cd build
cmake -DTF_COMMIT=37c2bf5016fcbed261476386eced503e907cdc01 ..
make
make flash
```
For more details about build instruction, see [the main README](../../README.md).

You might have to run ```make flash``` several times if you get a deployment error.

### Rebuilding the project
It is mandatory to delete ```CMakeCache.txt``` before re-building your project. Moreover, you should delete the *_deps* folder under *build* before running ```cmake ..``` again.
