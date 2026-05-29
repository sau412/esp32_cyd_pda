# Description
This is PDA firmware for ESP32 Cheap Yellow Display. Inspired by Palm OS.

PDA is Personal Digital Assistant. Small handheld computer. Like smartphone without phone functions.

![CYD with keyboard on screen photo](CYD_keyboard_photo.jpg)

# Details
* No additional hardware required. All you need is CYD
* It uses internal Flash for files storage. FFat as filesystem.
* You can add your own internal apps by modifying arduino code.

# Installation via web flasher
* https://sau412.github.io/esp32_cyd_pda/flash

# Required libraries
* TFT_eSPI - install via arduino library manager
* XPT2046_Touchscreen - install via arduino library manager

# Installation via Arduino
* Install Arduino IDE
* Install Required libraries (see above)
* Replace User_Setup.h with a file from https://github.com/witnessmenow/ESP32-Cheap-Yellow-Display/blob/main/DisplayConfig/User_Setup.h
* Add ESP32 libraries 
* Board Selection: In the Arduino IDE, go to Tools > Board and select ESP32-2432S028R
* Set in Arduino IDE Tools - Partition scheme - Default 4 Mb with FFat (1.2 MP APP/1.5 MB FATFS)
* Compile and upload
* Done

Check instructions at https://randomnerdtutorials.com/cheap-yellow-display-esp32-2432s028r/ if you have troubles.

# First run
* Calibrate sensor screen - calibration data stored in a /Settings/Calibration
* Format internal storage as FFat when asked
* Done

# Usage
* Tap app name to launch this app
* Touch and hold app title more than 1 second to exit app
* Tap buttons in app to perform actions
* For screensavers touch and hold anywhere to exit
* To force perform calibration on start hold touchscreen during reboot
* You can set password in Security app. Password asked when power on. Password stored in a plaintext, no encryption

# Applications/Functions
* File management (with viewing and editing support)
* Notes
* Touch sensor calibration
* TFT screen test
* Random number generator
* System info
* Password
* LED control
* Calculator
* Fifteen puzzle game
* Screensaver
* Stopwatch
* Timer
* Breathing timer
* Brightness
* Lights Off puzzle game
* Life (Cellular automaton)
* Wi-Fi connection
* Clock stand
* Gopher browser
* Fuzzy clock
* Weather
* Chat
* Books reader
* Counter
* I2C Scanner
* Set clock and timezone
* Contacts
* Todo
* Expenses
* Drawing (with saving)

# Touch sensor calibration
It uses three-dots linear calibration.

You touch three specific dots (should not be on one line).

Then it solves two systems of linear equations:

````
Ax * xt1 + Bx * yt1 + Cx = xs1
Ax * xt2 + Bx * yt2 + Cx = xs2
Ax * xt3 + Bx * yt3 + Cx = xs3

Ay * xt1 + By * yt1 + Cy = ys1
Ay * xt2 + By * yt2 + Cy = ys2
Ay * xt3 + By * yt3 + Cy = ys3

Ax, Bx, Cx, Ay, By, Cy - correction factors
(xt1, yt1), (xt2, yt2), (xt3, yt3) - touchscreen points
(xs1, ys1), (xs2, ys2), (xs3, ys3) - screen points
````

It could fix parallelogram distortions.

# To Do
* Schedule app
* SD support
* More games
* More apps
* More screensavers
* More settings

# Terms of use
You can modify code if you want. Bug reports and pull requests appreciated.

# Links
* Web Flasher: https://sau412.github.io/esp32_cyd_pda/flash
* Video presentation: https://www.youtube.com/watch?v=mXp3R2wKOIw
* Reddit post: https://www.reddit.com/r/esp32projects/comments/1tdrvur/esp32_cyd_pocket_digital_assistant/
* Reddit post: https://www.reddit.com/r/esp32/comments/1teoa28/esp32_cyd_pocket_digital_assistant/
* Reddit post: https://www.reddit.com/r/CheapYellowDisplay/comments/1tdryb3/esp32_cyd_pocket_digital_assistant/
