** # PatternPlay **
PatternPlay is a game designed to help children develop pattern recognition skills, this project was made during the GJU/Uni Stuttgart Hackamed 2025, the challenge was to make a toy for chidren within the age of 2-4, that benefits them and gives feedback to a supposed therapist (The feedback here wasn't as much, more on that later)

** # How this work **

First, you need those items
- Arduino Nano
- 5 LEDS (This was a common cathode design)
- 5 switches (We did 3D Design a small piece for the switches to stay in, I will upload the folder but it is not the right size since the folder I got is a demo one)
- Buzzer
- A display to show results for the therapist (Here implemented simply using AdaFruit SSD1306)
- Wires (A lot)
- A small Stuffed toy (Our victim)

The code was made using C++ Arduino UNO, we tested and connected all components as shown in the Simulink Picture
![Images/Screenshot 2025-11-26 104712.png]


After that the code, we divided that into parts


** I. Libraries **
The libraries used in this project were mostly for the display, shown here
- Wire.h
- Adafruit_GFX.h
- Adafruit_SSD1306.h
All libraries are downloadable inside the Arduino app
(You also need to define the screen width and height, then write this down, I did not want to make a whole section for this one)

```
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
```

** II. Defining variables **
- we defined 6 Arrays, each corresponding to an element of the build as well as the sequences and frequencies.
- Other variables included a level counter, a streak counter, a boolean variable, average time.

** III. setUp **
Inside setup we implemented the following
- Incase the display failed to begin, a message is shown.
- Otherwise, the display is cleared, and the text is given properties.
- A message is shown indicating that a new round has begun.
- A for loop is implemented to give values to each pin
  ** In switches[i] we used INPUT_PULLUP since the LEDS are a common cathode.
- The buzzer is also given a mode.
- A small intro is made, the idea is to pull the kids attention towards the toy.
- Sequence and random are given values.

** IV. loop **
- We assume that the value of correct is true
- A sequence is shown.
- A for loop is implemented so that Memory is filled up, a function is called to detect switches.
- If momery does not equal the random sequence, the boolean function (correct) is set to false.
- EndTime is also taken, and the time is calculated by a simple substitution.
- If the boolean correct is true, the successFlash function is called (Check functions section below), time is added to an array and the game proceeds to next level.
- If level is more than 5, sequence and memory are restarted, average time is calculated and the showResultsScreen function is called.
- Level is restarted.
- If correct is equal to false, the errorFlash function is called and the level is restarted to 1.

** V. Functions **
*** setColor ****
This function sets LED colors to a given value, it was made for a commone cathode value.

*** waitForPress ***
This function is set to wait if any of the switches are set to LOW, indictating it was pressed.
** The switches we worked with are set to HIGH when unpressed and set to LOW when pressed.

*** showSequence ***
This function shows the sequence up to the level reached, it also plays a tone using the buzzer.

*** displayMessage ***
This function was used for the demo version, it shows a simple message

*** successfulFlash ***
This function lights the LEDS with green if a level is passed, it lights up the LEDS of the sequence.

*** errorFlash ***
This function lights the LEDS with Red if the sequence is wrong.

*** showResultsScreen ***

This function shows the average time as well as a streak of all the successful attemps the kid went through.

