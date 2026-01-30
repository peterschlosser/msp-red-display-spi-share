Project:    ILI9341-XPT2046-unoR3
Desc:       A simple project for TFT 240x320 "Red Display" on the Arduino AVR platform.

The INO file lives in the ~/repo/Arduino project folder where Arduino IDE pulls from it's shared libraries folder.

    ~/repo/Arduino/ILI9341-XPT2046-unoR3/ILI9341-XPT2046-unoR3.ino

The main.cpp in the ~/repo/PlatformIO project folder, includes the INO file with an #include directive.  But maintains it's own set of libraries.

Procedure

1. we add the include path directive to the platformio.ini file:

    build_flags =
        -I../../Arduino/ILI9341-XPT2046-unoR3

2. then in main.cpp, we include the INO file:

    #include "ILI9341-XPT2046-unoR3.ino"
