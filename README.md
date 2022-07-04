# Dino Game!
## Longan Nano Board Project

### Introduction

This project originated from the CS110 course of ShanghaiTech University. This project has the interestingness that other projects do not have, and the sense of achievement after completion is also very fascinating. So I saved the code and tried to buy my own development boards and parts to explore further.

### Basic Info

#### Development Board Model
- Longan Nano Board

#### External Hardware
- Longan Nano Board dedicated screen (160*80 Resolution)
- 1 Paper shell
- 2 buttons (connect to the A0 and A1 port of the board)

#### Quick Setup
**Caution!** The whole project is implemented on Ubuntu 20.04. Running on Windows is theoretically possible if your coding environment is properly configured. Checking out the [official help document of Longan Nano Board](https://longan.sipeed.com/zh/) may be helpful.

##### Step 1: Environment Setup
First, since Longan Nano is based on RISC-V architecture and our PC is not, we have to do cross compile in order for our program to run on this board. Luckily, Longan Nano has official support for a third-party platform PlatformIO and it will handle all of these.

To install PlatformIO, make sure you have installed Python3 and pip3. Run this in command: (you may need to replace python with python3 or something)
```python -m pip install platformio```
You may download my project files as well.

##### Step 2: Test and Run
To compile the example Project, run this in project folder:
```python -m platformio run```
It may take quite a while when first run, as it will automatically install necessary dependencies. The output file will be .pio/build/sipeed-longan-nano/firmware.bin together with other files.

To download the executable file to the development board, you need to first connect the board to your computer via a Type-C cable; then follow the below steps to enter DFU mode of the board (so that you can download files to the board.)
- Hold BOOT0 button (and do not release)
- Hold RESET button (and do not release)
- Release RESET button
- Release BOOT0 button

It may require several attempts for this process to succeed. If done successfully, the screen of board will be frozen or become pure black, and you'll be able to detect this device via the following command:
```./dfu-util -l | grep 28e9:0189```
If there is some output, it means that your board has entered dfu mode successfully and is found by your computer. Please don't use the dfu-util provided by apt-get or PlatformIO, as it's known to have bugs.

Then, you can download the executable to the board:
```./dfu-util -a 0 --dfuse-address 0x08000000:leave -D .pio/build/sipeed-longan-nano/firmware.bin```
This command may raise an error such as "Error during download get_status" in the end; but it actually doesn't matter. If you meet some problems like "Permission denied" in the above steps, please use sudo.

After it's finished, press RESET button. Now you can see my work on the screen!

We've also provided you a Makefile in the example project folder (You may need to modify its first line). Run ```make``` to compile the source code and ```make download``` to download the executable to board.

##### Step 3: Wire Connection
To run my own project, you can connect the buttons according to the diagram below. 
![](https://s3.bmp.ovh/imgs/2022/07/04/5756895d4a74a12e.png)


##### Step 4: Do it yourself
You can call C functions in RISC-V, just like calling a RISC-V function; conversely you can also call a RISC-V function in C. To implement a RISC-V function that can be called via C, use a0-a7 as input parameters sequentially, and use a0 as output. For example:
```
// C code
int a = add(3, 4, 5); // a = 12

# RISC-V code
# ...
add t0, a0, a1  # a0 - 3, a1 - 4
add t0, t0, a2  # a2 - 5
mv a0, t0       # a0 - return value
# ...
ret
```
Another example for RISC-V code calling C functions:
```
# RISC-V code
li a0, 1;
li a1, 2;
jal sub      # a0 = -1 after this step

// C code
int sub(int a, int b) // a - 1, b - 2
{
	return a - b;
}
```
Most of RISC-V grammar here is the same as in Venus. You don't need to somehow "include" C headers in RISC-V files as PlatformIO will automatically detect and locate them.
Please read /src/lcd/lcd.c carefully. You'll definitely need many of those functions in your own project.
