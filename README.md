# Description
This is PDA firmware for ESP32 Cheap Yellow Display. Inspired by Palm OS.

PDA is Personal Digital Assistant. Small handheld computer.

# Details
It uses internal Flash for files storage. FFat as filesystem.

You can add your own internal apps by modifying arduino code.

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
* File management (with viewing and editing support)
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
* Stopwatch
* Timer
* Breathing timer
* Brightness

# Touch sensor calibration
It uses three-dots linear calibration.

You touch three specific dots (should not be on one line).

Then it solves two systems of linear equations:

<code>
Ax * xt1 + Bx * yt1 + Cx = xs1
Ax * xt2 + Bx * yt2 + Cx = xs2
Ax * xt3 + Bx * yt3 + Cx = xs3

Ay * xt1 + By * yt1 + Cy = ys1
Ay * xt2 + By * yt2 + Cy = ys2
Ay * xt3 + By * yt3 + Cy = ys3

Ax, Bx, Cx, Ay, By, Cy - correction factors
(xt1, yt1), (xt2, yt2), (xt3, yt3) - touchscreen points
(xs1, ys1), (xs2, ys2), (xs3, ys3) - screen points
</code>

It could fix parallelogram distortions.

# To Do
* App icons
* Wi-Fi apps
* Gopher browser
* PIM apps (notes, todo, contacts, schedule, handwriting notes)
* SD support
* More games
* More apps
* More screensavers
* More settings

# Terms of use
You can modify code if you want. Bug reports and pull requests appreciated.
