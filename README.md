# Description
This is PDA firmware for ESP32 Cheap Yellow Display. Inspired by Palm OS.
PDA is Personal Digital Assistant. Small handheld computer.

# Details
It uses internal Flash for files storage. FFat as filesystem.
You can add your own internal apps by modifying arduino code. Function samples provided.

# Installation
Add ESP32 CYD support for arduino.
Change one file (?)
Set arduino settings

# First run
Format internal flash for FFat
Calibrate sensor
Done!

# Usage
Touch and hold title to exit app.
For screensavers touch and hold anywhere to exit.

# Applications/Functions
* File management
* Touch sensor calibration
* TFT screen test
* Random number generator
* System info
* Password
* Drawing (without saving)
* LED control
* Calculator
* Fifteen puzzle game
* Screensaver

# Touch sensor calibration
It uses three-dots linear calibration.
You touch three specific dots.
It solves system of linear equations:
A * xt1 + B * yt1 + C =
It could fix

# To Do
* App icons
* Wi-Fi apps
* Gopher browser
* PIM apps (notes, todo, contacts, schedule, handwriting notes)
* More games
* More apps
* More screensavers
More settings

