# TechClubArduinoDemo
Demo program for Dublin Jerome High School Computer Science Club. Includes instructions for recreating hardware configuration and documentation of program.
## Setup
1. The following parts are needed:
   - Arduino MEGA 2560 (any other Arduino should work, though)
   - Breadboard (minimum of 33 rows)
   - USB-A to USB-B cable (for uploading program to Arduino)
   - 19 male-to-male cables
   - 16x2 LCD (HD44780 chipset)
   - 3 1k Ohm resistors (optional - increases longevity of display)

2. Use the image below to connect the LCD according to the following instructions:
   - Ground -> Ground
   - +5V -> 5V power
   - Contrast control (VE) -> Pin 2
   - Register select (rs) -> Pin 3
   - Read/Write (rw) -> Pin 4
   - Enable -> Pin 5
   - Data 0 -> Pin 6
   - Data 1 -> Pin 7
   - Data 2 -> Pin 8
   - Data 3 -> Pin 9
   - Data 4 -> Pin 10
   - Data 5 -> Pin 11
   - Data 6 -> Pin 12
   - Data 7 -> Pin 13
   - LED +5V -> 5V power
   - LED negative -> Ground

![16x2 LCD pinout reference](https://www.electronicwings.com/public/images/user_images/images/Arduino/LCD/LCD16x2%20Pins.png)

3. Connect the potentiometer - you will have to look up the pinouts for your particular model:
   - 5V -> 5V
   - Signal -> Pin 14
   - Ground -> Ground

4. Download and install the [Arduino IDE](https://www.arduino.cc/en/software) ([direct link](https://downloads.arduino.cc/arduino-1.8.16-windows.exe)) on a laptop

5. Download the file [lcdDemo.ino](https://github.com/BlakeGroty/TechClubArduinoDemo/blob/main/lcdDemo.ino) or clone this repository

6. Open lcdDemo.ino using the Arduino IDE

7. [Upload the program](https://docs.arduino.cc/software/ide-v2/tutorials/getting-started/ide-v2-uploading-a-sketch)

8. Open the serial monitor and [set the line ending](https://arduinogetstarted.com/tutorials/arduino-serial-monitor) to "No line ending"

9. The demo is ready for use!
## Documentation
### Potentiometer
The potentiometer can be used to control the LCD contrast while the `useSerialNumbers` flag is set to `false`. The `useSerialNumbers` flag is set to `true` when a positive integer is entered into the serial monitor and reverts to `false` when `-1` is entered into the serial monitor. `useSerialNumbers` is `false` by default.

### Setting contrast via serial
LCD contrast can be set over serial by entering any positive integer into the serial monitor. Some values will result in nothing displaying on the LCD. After setting the contrast over serial, the potentiometer will not do anything. To use the potentiometer again, enter `-1` into the serial monitor.

### Changing text
The LCD's first line of text can be changed using serial by entering `-2` into the serial monitor. Enter the new text (max 16 characters). A "..." pattern will appear on the LCD while the new text is being entered. If the new text does not appear, make sure that the line ending is set to "No line ending." When the Arduino starts again, it will revert to the default text.
