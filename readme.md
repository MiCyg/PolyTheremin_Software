# PolyTheremin Software  

## Overview  

This repository contains the software implementation of the [PolyTheremin project](https://github.com/MiCyg/PolyTheremin) (Currently under development). The code has been tested on my [testing platform](https://github.com/MiCyg/PolyTheremin_Hardware), connected to four metal antennas.  

This project implements a polyphonic theremin using the RP2040 microcontroller, with FreeRTOS and CMSIS-DSP library for matrix operations.  

![PolyTheremin under development](doc/PolyTheremin_testPlatform.png)

Instrument is currently under development.


## Functionalities

- [X] Detect fingers by antennas
- [X] Scale frequency to music range
- [X] Generate sound depend to fingers distances
- [X] Use button to change sound
- [ ] Auto scaling
- [ ] Uploading custom waves
- [ ] Increase detectors distance

## Frequency detector

Frequency detection made by counting timer between each signal period. On change a signal state, the counter starts counting to next rising edge. Then, interrupt copy counter value to proper pointer in memory. 

![Frequency detector](doc/freq_det.png)

In other way, DMA get values from this pointer to make input buffer. After end dma transmission, them calls a interrupt every `FREQ_DET_DMA_BUFFER_NUM` numbers of transfers. 
Buffer created in that way can be averaged and analysing to proper oscillators frequencies.

## Capacitive Touch Calibration  

Each antenna generates a digital square wave signal with a frequency ranging from 400 kHz to 600 kHz. These signals are processed by the `het_generator` module, which quantizes them to create a beating signal with a beat frequency above 10 kHz.  

To calibrate, measure the base frequency of each antenna and define `HET_GENX_FREQ` for each channel with an additional offset around 20kHz.  

For example, if the measured base frequencies are:  

```
ANTENNA 0: 530000 Hz  
ANTENNA 1: 614000 Hz  
ANTENNA 2: 520000 Hz  
ANTENNA 3: 510000 Hz  
```  

You should set:  

```c  
#define HET_GEN0_FREQ 550000  
#define HET_GEN1_FREQ 634000  
#define HET_GEN2_FREQ 540000  
#define HET_GEN3_FREQ 530000  
```  

I know this method is a bit tricky, but for now, it's the best approach I have. Improving the calibration process is on my to-do list for the future. 😊

## Oscillators

Program contains four independent oscillators mixed up by `dds` module. Each oscillator, get samples from wavetable list on proper frequency set by phase accumulator value.
For creating my own waves I use [Wave table generator](http://www.gaudi.ch/WaveGenerator/).
And my own scripts for sreated sine wave and some them combinations also.



## Building  

First, you need to clone the repository and initialize all submodules (FreeRTOS and CMSIS) using the following commands:  

```sh  
git submodule init  
git submodule update  
```  

There are several ways to build the project.  

### VS Code Extension (Recommended)  

Following the official SDK documentation, install the [Raspberry Pi Pico VS Code extension](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf#vscode-extension).  

Then, clone the repository and open it in Visual Studio Code. Next, import the project using the Raspberry Pi Pico badge. Select the project location and click the `Import` button. If you haven’t installed the Pico SDK yet, the extension may take a few minutes to download and set it up.  

![Example of project import](doc/import_project.png)  

After reloading the window, the board configuration should be loaded as `polyTheremin_board`.  

### Using CMake  

You can also build the project manually using CMake. Create a build folder and run `cmake` inside it:  

```sh  
mkdir build  
cd build  
cmake ..  
make  
```  

## Contribution  

If you'd like to contribute to the project, your help is welcome! Feel free to submit a pull request or create a new issue. I strive to write good code, but code reviews can provide valuable insights and improvements.  
