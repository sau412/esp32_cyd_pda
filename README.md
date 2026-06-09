# Description
This is PDA firmware for ESP32 Cheap Yellow Display. Inspired by Palm OS.

PDA is Personal Digital Assistant. Small handheld computer. Like smartphone without phone functions.

![CYD with keyboard on screen screenshot](Launcher.png)

# Details
* No additional hardware required. All you need is CYD
* But if you have a speaker it can beep on events
* It uses internal Flash for files storage. FFat as filesystem.
* You can add your own internal apps by modifying arduino code.

# Installation via web flasher
* https://sau412.github.io/esp32_cyd_pda/flash

# Required libraries
* TFT_eSPI - install via arduino library manager
* XPT2046_Touchscreen - install via arduino library manager

# Installation via Arduino IDE
* Install Arduino IDE
* Install Required libraries (see above)
* Replace User_Setup.h with a file from https://github.com/witnessmenow/ESP32-Cheap-Yellow-Display/blob/main/DisplayConfig/User_Setup.h
* Add ESP32 libraries 
* Board Selection: In the Arduino IDE, go to Tools > Board and select ESP32-2432S028R
* Set in Arduino IDE Tools - Partition scheme - No OTA (2 MP APP/2 MB FATFS)
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
* Touch sensor calibration
* TFT screen test
* Random number generator
* System info
* Password
* LED control
* Screensaver
* Stopwatch
* Timer
* Breathing timer
* Brightness
* Life (cellular automaton) - see https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life for details
* Clock stand
* Fuzzy clock
* Counter
* I2C Scanner
* Set clock and timezone
* View Fonts
* Make screenshot with BOOT button
* Application groups

## PIM apps
* Calculator
* Notes
* Books reader
* Contacts
* Todo
* Expenses
* Drawing (with saving BMP)
* Schedule

## Games
* Fifteen puzzle game - see https://en.wikipedia.org/wiki/15_puzzle for details
* Lights Off puzzle game - see https://en.wikipedia.org/wiki/Lights_Out_(game) for details
* Snake - see https://en.wikipedia.org/wiki/Snake_(video_game_genre) for details
* Turkish Kerchief Solitaire - see https://www.bvssolitaire.com/rules/turkish-kerchief.htm for details
* Memory Match - see https://en.wikipedia.org/wiki/Concentration_(card_game) for details
* Hanoi Towers - see https://en.wikipedia.org/wiki/Tower_of_Hanoi for details

## Wi-Fi
* Wi-Fi connection
* Gopher browser - see https://ru.wikipedia.org/wiki/Gopher for details
* Weather
* Chat
* File Server (for backups and file upload)

## Sound
* Piano

# Terms of use
You can modify code if you want. Bug reports and pull requests appreciated.

# Links
* Web Flasher: https://sau412.github.io/esp32_cyd_pda/flash
* Video presentation: https://www.youtube.com/watch?v=mXp3R2wKOIw
* Reddit post: https://www.reddit.com/r/esp32projects/comments/1tdrvur/esp32_cyd_pocket_digital_assistant/
* Reddit post: https://www.reddit.com/r/esp32/comments/1teoa28/esp32_cyd_pocket_digital_assistant/
* Reddit post: https://www.reddit.com/r/CheapYellowDisplay/comments/1tdryb3/esp32_cyd_pocket_digital_assistant/
