# PolyTheremin Software

## Overview

This repo is software implementation of [PolyTheremin project](https://github.com/MiCyg/PolyTheremin) (Currently under development). I tested code on my [testing platform](https://github.com/MiCyg/PolyTheremin_Hardware) connected to four metal antennas.
This project implements a polyphonic theremin using the RP2040 microcontroller with FreeRTOS for real-time processing.


## Building

At first you must clone the repository and load all submodules (freertos and cmsis) by following commands:

```sh
git submodule init
git submodule update
```
Now there are some methods to build project


### VS Code Extension (recommended)

Following the official sdk documentation, install the [Raspberry Pi Pico VS Code extension](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf#vscode-extension). 
Now, you can clone repository and open them on visual Studio Code. Next step is import project on Raspberry Pi Pico badge. Select project location and click `Import` button. If you do not even use pico extension it may take around few minutes to install pico sdk.

![example of import project](doc/import_project.png)

after window reloading, the board configuration should be loaded as `polyTheremin_board`.

### Using cmake

Can you also build the project manually using cmake. Then, make a build folder and run `cmake` inside.

```sh
mkdir build
cd build
cmake ..
make
```

# Contribution 

If you want to participate with project to make it better, your help will be welcome! Feel free to make a pull request or create new issue. I do my best for create quite good code but code review can open my seens to other way.