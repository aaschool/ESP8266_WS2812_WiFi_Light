# ESP8266 WS2812 WiFi Light

Arduino based ESP8266 + WS2812 (Neopixel) lighting control for dynamic lighting via WiFi.
 
## Installation
 
### Pre-requisites
 
The first dependency to install is the Arduino IDE. This can be accomplished by downloading the program directly from the Arduino website: [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software) for the relevant platform. 

On Debian GNU Linux or a Debian based linux distribution, you can use the `apt` command:

```
$ sudo apt install arduino
```
 
Run the arduino program from the command line:

```
$ arduino
```

or directly from the operating system.

In the Arduino IDE, inside `File/Preferences/Additional Boards Manager URLs` input, add the `https://arduino.esp8266.com/stable/package_esp8266com_index.json` URL.

#### ESP8266 board manager library

Restart the Arduino IDE and from the `Tools/Boards/Board Manager` window add the `esp8266` board library.

Please ensure that the esp8266 board library version is 2.7.4. Different versions might have compatibility issues 
with the code.

#### FastLED library

From `Tools/Manage Libraries` add the `FastLED` library.

Please ensure that the FastLED library version is 3.5.0. Different versions might have compatibility issues
with the code.
 
### Arduino ESP8266 code

Clone this repo with `git clone https://github.com/aaschool/ESP8266_WS2812_WiFi_Light.git` or [download the zip 
file](https://github.com/aaschool/ESP8266_WS2812_WiFi_Light/archive/refs/heads/main.zip) and extract it.

Connect the ESP8266 using a USB mini cable.

In the Arduino IDE, select the relevant ESP8266 board from the `Tools/Board` menu and the connected USB port. 

In the Arduino IDE, press the upload button to upload the code to the device.

## Use

Connect the ESP8266 and WS2812 components as shown in the diagram below:

![ESP8266 Wifi Lantern Schematic](ESP8266_Wifi_Lantern_Schematic.png)

Connect to the WiFi SSID you have chosen in the code and input the chosen password.

Additional options are commented directly in the code.

Input the IP address you have specified in the code into a browser and enjoy playing with the light!


